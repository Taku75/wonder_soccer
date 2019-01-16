#pragma once

#include "Task.h"
#include "IStateChanger.h"

class StateMgr : public Task, IStateChanger
{
private:
	Task * mState;    //シーン管理変数
	eState mNextState;    //次のシーン管理変数

public:
	StateMgr();
	void Initialize() override;//初期化
	void Finalize() override;//終了処理
	void Update() override;//更新
	void Draw() override;//描画

						 // 引数 nextScene にシーンを変更する
	void ChangeState(eState NextState) override;

};