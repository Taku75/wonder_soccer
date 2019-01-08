#pragma once
#include <windows.h>
#include <map>
#include <memory>

using namespace std;

/////////////////////////////////////////////////
// ITaskBase インターフェイス
//
//    更新メソッドの提供
////////////////////////////////////////
interface ITaskBase
{
protected:
	bool m_bUsageFlag;	// タスク有効フラグ（trueでないとタスクが働かないとします）

public:
	virtual ~ITaskBase() {};
	// 更新する
	virtual bool Update() = 0;

	// タスクの状態をリセットする
	virtual void Reset() = 0;

	// 現在の状態を取得する
	bool CheckUsageFlag() { return m_bUsageFlag; }

	// 更新条件が揃っているかチェックする
	virtual bool AllowUpdate() { return true; }
};






/////////////////////////////////////////////////
// IDrawTask インターフェイス
//
//    描画メソッド付き更新メソッドの提供
////////////////////////////////////////////////
interface IDrawTask : public ITaskBase
{
public:
	virtual bool Draw() = 0;
	virtual ~IDrawTask() {};
};






/////////////////////////////////////////////////
// ITaskSystem インターフェイス
//
//    タスクシステムのメソッド提供
////////////////////////////////////////
typedef map< DWORD, shared_ptr<ITaskBase> > TASK_MAP;
typedef pair< DWORD, shared_ptr<ITaskBase> > TASK_PAIR;
typedef DWORD TASKID;
interface ITaskSystem
{
protected:
	TASK_MAP m_mapTask;		// タスク格納マップ
	TASK_MAP m_mapActTask;	// 活動中タスク格納マップ

public:
	ITaskSystem() {}
	virtual ~ITaskSystem() {}

	// システムを初期化する
	virtual bool Init() = 0;

	// システムを更新する
	virtual bool UpdateTask()
	{
		// 活動中のタスクを更新する
		TASK_MAP::iterator it;
		for (it = m_mapActTask.begin(); it != m_mapActTask.end(); it++)
			(*it).second->Update();
		return true;
	}

	// タスクを登録する
	virtual bool RegistTask(TASKID taskid, shared_ptr<ITaskBase> &spTask, bool DoActive)
	{
		if (m_mapTask.insert(TASK_PAIR(taskid, spTask)).second == false)
			return false;
		if (DoActive)
			return SwitchTask(taskid);
		return true;
	}


	// タスクのアクティブ・非アクティブを切り替える
	virtual bool SwitchTask(TASKID TaskID, bool DoActive = true)
	{
		// TaskIDの人が活動しているかチェック
		TASK_MAP::iterator it = m_mapActTask.find(TaskID);

		// TaskIDさんをアクティブにする
		if (DoActive && it == m_mapActTask.end())
		{
			// TaskIDさんが存在しているかチェック
			TASK_MAP::iterator RegIt = m_mapTask.find(TaskID);
			if (RegIt != m_mapTask.end())
			{
				//-- TaskIDさんを活動させる --//
				m_mapActTask.insert(TASK_PAIR(TaskID, RegIt->second));   // 活動させる
			}
			return true;
		}

		// TaskIDさんを非アクティブにする
		if (!DoActive && it != m_mapActTask.end()) {
			// マップからの削除作業
			m_mapActTask.erase(it);
			return true;
		}
		return false;
	}
};