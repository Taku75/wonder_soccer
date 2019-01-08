#pragma once

#include <list>
#include <map>
#include <memory>

using namespace std;

typedef size_t OBJID; //�I�u�W�F�N�gID
typedef size_t ELEMID;//�v�fID

/***�I�u�W�F�N�g�t�@�N�g����{�C���^�[�t�F�C�X***/
class IOBjectFactory
{
public:
	virtual bool Optimaize() = 0;
	virtual void ClearAll() = 0;
};

/***�t�@�N�g���}�l�[�W����{�N���X***/
class CFactoryManager
{
protected:
	static list<IOBjectFactory*> m_pFactoryList;
protected:
	CFactoryManager(){}

public:
	virtual ~CFactoryManager(){}

	//�I�u�W�F�N�g�������\�b�h(�V���O���g��)
	static CFactoryManager &Instance()
	{
		static CFactoryManager inst;
		return inst;
	}

	//�t�@�N�g���I�u�W�F�N�g��o�^
	bool RegistFactory(IOBjectFactory* ptr)
	{
		m_pFactoryList.push_back(ptr);
		return true;
	}

	//�e�t�@�N�g���ɍœK�����w������
	virtual bool Optimaize()
	{
		list<IOBjectFactory*>::iterator it;
		for (it = m_pFactoryList.begin(); it != m_pFactoryList.end(); it++)
		{
			(*it)->Optimaize();
		}
		return true;
	}

	//�S�t�@�N�g���ɃN���A���߂��o��
	virtual bool ClearAll()
	{
		list<IOBjectFactory*>::iterator it;
		for (it = m_pFactoryList.begin(); it != m_pFactoryList.end(); it++)
		{
			(*it)->ClearAll();
		}
		return true;
	}
};
list<IOBjectFactory*> CFactoryManager::m_pFactoryList;//static�ȃ������Ɋm��

/***�I�u�W�F�N�g�t�@�N�g����{�N���X***/
class CObjectFactory : public IOBjectFactory
{
protected:
	CObjectFactory()
	{
		// ���̊�{�N���X�Ńt�@�N�g���}�l�[�W���Ɏ��g��o�^���܂�
		// ����͔h���N���X���V���O���g���Ŏ������鎖��z�肵�Ă��܂�
		CFactoryManager::Instance().RegistFactory(this);
	}
};

/***�X�}�[�g�|�C���^�e���v���[�g�V���O���g���t�@�N�g���N���X***/
template<class T>
class CGeneralFactory : public CObjectFactory
{
	typedef pair<ELEMID, shared_ptr<T>> ELEMPAIR;//�v�f�y�A
	typedef map<ELEMID, shared_ptr<T>> ELEMMAP;//�v�f�}�b�v
	typedef shared_ptr<ELEMMAP> SPELEMMAP;//�v�f�}�b�v�̃X�}�[�g�|�C���^
	typedef pair<OBJID, SPELEMMAP> OBJIDPAIR;//�I�u�W�F�N�g�y�A
	typedef map< OBJID, SPELEMMAP > OBJIDMAP;	// �I�u�W�F�N�g�}�b�v
	
	typename OBJIDMAP m_IDMap;	// �I�u�W�F�N�g�i�[�}�b�v

protected:
	CGeneralFactory(){}

public:
	virtual ~CGeneralFactory() {};

	//�V���O���g���I�u�W�F�N�g���擾
	static CGeneralFactory<T> &Instance()
	{
		static CGeneralFactory<T> inst;
		return inst;
	}

	//�I�u�W�F�N�g�𐶐�����
	OBJID Create(OBJID id, size_t elem, shared_ptr<T> &spOut)
	{
		//�I�u�W�F�N�gID�`�F�b�N
		
		typename OBJIDMAP::iterator ObjID = m_IDMap.find(id);
		if (ObjID == m_IDMap.end())
		{
			// �V����ID���v�f�}�b�v���쐬���ăI�u�W�F�N�g��o�^
			shared_ptr<T> spNewObj(CreateNewObj());
			ELEMPAIR NewElemPair(elem, spNewObj);

			// �V�I�u�W�F�N�gID�Ɨv�f�}�b�v���I�u�W�F�N�g�}�b�v�ɒǉ�
			SPELEMMAP NewElemMap(new map<ELEMID, shared_ptr<T> >);
			NewElemMap->insert(NewElemPair);
			OBJIDPAIR ObjPair(id, NewElemMap);
			m_IDMap.insert(ObjPair);
			spOut = spNewObj;
			return id;
		}

		//�v�fID�̃`�F�b�N
		typename ELEMMAP::iterator it = (*ObjID).second->find(elem);
		if (it = (*ObjID).second->end())
		{
			// �V�K�쐬
			shared_ptr<T> spNewObj(CreateNewObj());
			ELEMPAIR NewPair(elem, spNewObj);
			(*ObjID).second->insert(NewPair);
			spOut = spNewObj;
		}
		else
		{
			// �����I�u�W�F�N�g�̎Q�Ɠn��
			spOut = it->second;
		}
		return id;

	}
	// �}�b�v���œK������
	bool Optimaize()
	{
		// �Q�ƃJ�E���g��1�̃I�u�W�F�N�g�͎�菜��
		typename OBJIDMAP::iterator ObjIt;
		for (ObjIt = m_IDMap.begin(); ObjIt != m_IDMap.end();)
		{
			typename ELEMMAP::iterator it;
			for (it = ObjIt->second->begin(); it != ObjIt->second->end();)
			{
				if (*(*it).second.GetRefPtr() != 1) {
					it++;
					continue;
				}
				// �폜�Ώ�
				it = ObjIt->second->erase(it);
			}

			// �v�f����0�̃I�u�W�F�N�gID�͎�菜��
			if (ObjIt->second->size() == 0)
			{
				ObjIt = m_IDMap.erase(ObjIt);
				continue;
			}
			ObjIt++;
		}
		return true;
	}


	// ���݂̐����I�u�W�F�N�g�����Z�o
	virtual size_t Size()
	{
		size_t sz = 0;
		typename OBJIDMAP::iterator ObjIt;
		for (ObjIt = m_IDMap.begin(); ObjIt != m_IDMap.end(); ObjIt++) {
			sz += ObjIt->second->size();
		}
		return sz;
	}

	// �S�I�u�W�F�N�g�N���A
	virtual void ClearAll()
	{
		m_IDMap.clear();
	}

protected:
	// �V�����I�u�W�F�N�g�𐶐�
	virtual T* CreateNewObj() { return new T; };
};