#pragma once

#include <list>
#include <map>
#include <memory>

using namespace std;

typedef size_t OBJID; //オブジェクトID
typedef size_t ELEMID;//要素ID

/***オブジェクトファクトリ基本インターフェイス***/
class IOBjectFactory
{
public:
	virtual bool Optimaize() = 0;
	virtual void ClearAll() = 0;
};

/***ファクトリマネージャ基本クラス***/
class CFactoryManager
{
protected:
	static list<IOBjectFactory*> m_pFactoryList;
protected:
	CFactoryManager(){}

public:
	virtual ~CFactoryManager(){}

	//オブジェクト生成メソッド(シングルトン)
	static CFactoryManager &Instance()
	{
		static CFactoryManager inst;
		return inst;
	}

	//ファクトリオブジェクトを登録
	bool RegistFactory(IOBjectFactory* ptr)
	{
		m_pFactoryList.push_back(ptr);
		return true;
	}

	//各ファクトリに最適化を指示する
	virtual bool Optimaize()
	{
		list<IOBjectFactory*>::iterator it;
		for (it = m_pFactoryList.begin(); it != m_pFactoryList.end(); it++)
		{
			(*it)->Optimaize();
		}
		return true;
	}

	//全ファクトリにクリア命令を出す
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
list<IOBjectFactory*> CFactoryManager::m_pFactoryList;//staticなメモリに確保

/***オブジェクトファクトリ基本クラス***/
class CObjectFactory : public IOBjectFactory
{
protected:
	CObjectFactory()
	{
		// この基本クラスでファクトリマネージャに自身を登録します
		// これは派生クラスをシングルトンで実装する事を想定しています
		CFactoryManager::Instance().RegistFactory(this);
	}
};

/***スマートポインタテンプレートシングルトンファクトリクラス***/
template<class T>
class CGeneralFactory : public CObjectFactory
{
	typedef pair<ELEMID, shared_ptr<T>> ELEMPAIR;//要素ペア
	typedef map<ELEMID, shared_ptr<T>> ELEMMAP;//要素マップ
	typedef shared_ptr<ELEMMAP> SPELEMMAP;//要素マップのスマートポインタ
	typedef pair<OBJID, SPELEMMAP> OBJIDPAIR;//オブジェクトペア
	typedef map< OBJID, SPELEMMAP > OBJIDMAP;	// オブジェクトマップ
	
	typename OBJIDMAP m_IDMap;	// オブジェクト格納マップ

protected:
	CGeneralFactory(){}

public:
	virtual ~CGeneralFactory() {};

	//シングルトンオブジェクトを取得
	static CGeneralFactory<T> &Instance()
	{
		static CGeneralFactory<T> inst;
		return inst;
	}

	//オブジェクトを生成する
	OBJID Create(OBJID id, size_t elem, shared_ptr<T> &spOut)
	{
		//オブジェクトIDチェック
		
		typename OBJIDMAP::iterator ObjID = m_IDMap.find(id);
		if (ObjID == m_IDMap.end())
		{
			// 新しいID内要素マップを作成してオブジェクトを登録
			shared_ptr<T> spNewObj(CreateNewObj());
			ELEMPAIR NewElemPair(elem, spNewObj);

			// 新オブジェクトIDと要素マップをオブジェクトマップに追加
			SPELEMMAP NewElemMap(new map<ELEMID, shared_ptr<T> >);
			NewElemMap->insert(NewElemPair);
			OBJIDPAIR ObjPair(id, NewElemMap);
			m_IDMap.insert(ObjPair);
			spOut = spNewObj;
			return id;
		}

		//要素IDのチェック
		typename ELEMMAP::iterator it = (*ObjID).second->find(elem);
		if (it = (*ObjID).second->end())
		{
			// 新規作成
			shared_ptr<T> spNewObj(CreateNewObj());
			ELEMPAIR NewPair(elem, spNewObj);
			(*ObjID).second->insert(NewPair);
			spOut = spNewObj;
		}
		else
		{
			// 既存オブジェクトの参照渡し
			spOut = it->second;
		}
		return id;

	}
	// マップを最適化する
	bool Optimaize()
	{
		// 参照カウントが1のオブジェクトは取り除く
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
				// 削除対象
				it = ObjIt->second->erase(it);
			}

			// 要素数が0のオブジェクトIDは取り除く
			if (ObjIt->second->size() == 0)
			{
				ObjIt = m_IDMap.erase(ObjIt);
				continue;
			}
			ObjIt++;
		}
		return true;
	}


	// 現在の生成オブジェクト数を算出
	virtual size_t Size()
	{
		size_t sz = 0;
		typename OBJIDMAP::iterator ObjIt;
		for (ObjIt = m_IDMap.begin(); ObjIt != m_IDMap.end(); ObjIt++) {
			sz += ObjIt->second->size();
		}
		return sz;
	}

	// 全オブジェクトクリア
	virtual void ClearAll()
	{
		m_IDMap.clear();
	}

protected:
	// 新しいオブジェクトを生成
	virtual T* CreateNewObj() { return new T; };
};