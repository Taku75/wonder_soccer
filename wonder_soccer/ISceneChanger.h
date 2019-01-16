#pragma once
typedef enum 
{
	eScene_Start,    //���j���[���
	eScene_Game,    //�Q�[�����
	eScene_Result,
	eScene_None,    //����
} eScene;

//�V�[����ύX���邽�߂̃C���^�[�t�F�C�X�N���X
class ISceneChanger 
{
public:
	virtual ~ISceneChanger() = 0;
	virtual void ChangeScene(eScene NextScene) = 0;//�w��V�[���ɕύX����
};