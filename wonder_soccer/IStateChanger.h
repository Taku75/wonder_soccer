#pragma once
typedef enum
{
	eState_Serial,    //���j���[���
	eState_Initial,    //�Q�[�����
	eState_kick,
	eState_None,    //����
} eState;

//�V�[����ύX���邽�߂̃C���^�[�t�F�C�X�N���X
class IStateChanger
{
public:
	virtual ~IStateChanger() {};
	virtual void ChangeState(eState NextState) = 0;//�w��V�[���ɕύX����
};