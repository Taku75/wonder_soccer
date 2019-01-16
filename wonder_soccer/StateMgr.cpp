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
	{    //���̃V�[�����Z�b�g����Ă�����
		mState->Finalize();//���݂̃V�[���̏I�����������s
		delete mState;
		switch (mNextState)
		{       //�V�[���ɂ���ď����𕪊�
		case eState_Serial:        //���̉�ʂ����j���[�Ȃ�
			mState = (Task*) new State_Serial(this);   //���j���[��ʂ̃C���X�^���X�𐶐�����
			break;//�ȉ���

		case eState_Initial:
			mState = (Task*) new State_Initial(this);
			break;

		case eState_kick:
			mState = (Task*) new State_Kick(this);
		}
		mNextState = eState_None;    //���̃V�[�������N���A
		mState->Initialize();    //�V�[����������
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