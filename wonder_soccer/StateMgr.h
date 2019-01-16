#pragma once

#include "Task.h"
#include "IStateChanger.h"

class StateMgr : public Task, IStateChanger
{
private:
	Task * mState;    //�V�[���Ǘ��ϐ�
	eState mNextState;    //���̃V�[���Ǘ��ϐ�

public:
	StateMgr();
	void Initialize() override;//������
	void Finalize() override;//�I������
	void Update() override;//�X�V
	void Draw() override;//�`��

						 // ���� nextScene �ɃV�[����ύX����
	void ChangeState(eState NextState) override;

};