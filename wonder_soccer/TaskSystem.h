#pragma once
#include <windows.h>
#include <map>
#include <memory>

using namespace std;

/////////////////////////////////////////////////
// ITaskBase �C���^�[�t�F�C�X
//
//    �X�V���\�b�h�̒�
////////////////////////////////////////
interface ITaskBase
{
protected:
	bool m_bUsageFlag;	// �^�X�N�L���t���O�itrue�łȂ��ƃ^�X�N�������Ȃ��Ƃ��܂��j

public:
	virtual ~ITaskBase() {};
	// �X�V����
	virtual bool Update() = 0;

	// �^�X�N�̏�Ԃ����Z�b�g����
	virtual void Reset() = 0;

	// ���݂̏�Ԃ��擾����
	bool CheckUsageFlag() { return m_bUsageFlag; }

	// �X�V�����������Ă��邩�`�F�b�N����
	virtual bool AllowUpdate() { return true; }
};






/////////////////////////////////////////////////
// IDrawTask �C���^�[�t�F�C�X
//
//    �`�惁�\�b�h�t���X�V���\�b�h�̒�
////////////////////////////////////////////////
interface IDrawTask : public ITaskBase
{
public:
	virtual bool Draw() = 0;
	virtual ~IDrawTask() {};
};






/////////////////////////////////////////////////
// ITaskSystem �C���^�[�t�F�C�X
//
//    �^�X�N�V�X�e���̃��\�b�h��
////////////////////////////////////////
typedef map< DWORD, shared_ptr<ITaskBase> > TASK_MAP;
typedef pair< DWORD, shared_ptr<ITaskBase> > TASK_PAIR;
typedef DWORD TASKID;
interface ITaskSystem
{
protected:
	TASK_MAP m_mapTask;		// �^�X�N�i�[�}�b�v
	TASK_MAP m_mapActTask;	// �������^�X�N�i�[�}�b�v

public:
	ITaskSystem() {}
	virtual ~ITaskSystem() {}

	// �V�X�e��������������
	virtual bool Init() = 0;

	// �V�X�e�����X�V����
	virtual bool UpdateTask()
	{
		// �������̃^�X�N���X�V����
		TASK_MAP::iterator it;
		for (it = m_mapActTask.begin(); it != m_mapActTask.end(); it++)
			(*it).second->Update();
		return true;
	}

	// �^�X�N��o�^����
	virtual bool RegistTask(TASKID taskid, shared_ptr<ITaskBase> &spTask, bool DoActive)
	{
		if (m_mapTask.insert(TASK_PAIR(taskid, spTask)).second == false)
			return false;
		if (DoActive)
			return SwitchTask(taskid);
		return true;
	}


	// �^�X�N�̃A�N�e�B�u�E��A�N�e�B�u��؂�ւ���
	virtual bool SwitchTask(TASKID TaskID, bool DoActive = true)
	{
		// TaskID�̐l���������Ă��邩�`�F�b�N
		TASK_MAP::iterator it = m_mapActTask.find(TaskID);

		// TaskID������A�N�e�B�u�ɂ���
		if (DoActive && it == m_mapActTask.end())
		{
			// TaskID���񂪑��݂��Ă��邩�`�F�b�N
			TASK_MAP::iterator RegIt = m_mapTask.find(TaskID);
			if (RegIt != m_mapTask.end())
			{
				//-- TaskID��������������� --//
				m_mapActTask.insert(TASK_PAIR(TaskID, RegIt->second));   // ����������
			}
			return true;
		}

		// TaskID������A�N�e�B�u�ɂ���
		if (!DoActive && it != m_mapActTask.end()) {
			// �}�b�v����̍폜���
			m_mapActTask.erase(it);
			return true;
		}
		return false;
	}
};