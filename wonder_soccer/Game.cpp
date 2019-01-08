#include "Game.h"
#include "DxLib.h"

Game::Game(ISceneChanger* changer) : BaseScene(changer) 
{
}

//������
void Game::Initialize() 
{
}

//�X�V
void Game::Update() 
{
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) 
	{	 //Esc�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_Start);//�V�[�������j���[�ɕύX
	}
}

//�`��
void Game::Draw() 
{
	BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
	DrawString(0, 0, "�Q�[����ʂł��B", GetColor(255, 255, 255));
	DrawString(0, 20, "Esc�L�[�������ƃ��j���[��ʂɖ߂�܂��B", GetColor(255, 255, 255));
}