#include "StateMgr.h"
#include "State_Serial.h"
#include "State_Initial.h"
#include "State_Kick.h"

StateMgr::StateMgr() : mNextState(eState_None)
{
	mState = (Task*) new State_Serial(this);
}

void StateMgr::Initialize()
{
	mState->Initialize();
}

void StateMgr::Update()
{
	if (mNextState != eState_None)
	{    //次のシーンがセットされていたら
		mState->Finalize();//現在のシーンの終了処理を実行
		delete mState;
		switch (mNextState)
		{       //シーンによって処理を分岐
		case eState_Serial:        //次の画面がメニューなら
			mState = (Task*) new State_Serial(this);   //メニュー画面のインスタンスを生成する
			break;//以下略

		case eState_Initial:
			mState = (Task*) new State_Initial(this);
			break;

		case eState_kick:
			mState = (Task*) new State_Kick(this);
		}
		mNextState = eState_None;    //次のシーン情報をクリア
		mState->Initialize();    //シーンを初期化
	}

	mState->Update();
}

void StateMgr::Draw()
{
	mState->Draw();
}

void StateMgr::Finalize()
{
	mState->Finalize();
}

void StateMgr::ChangeState(eState NextState)
{
	mNextState = NextState;
}