#include "Game.h"
#include "SceneMgr.h"
#include "DxLib.h"

//�X�V
void Game_Update()
{
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) 
	{	//Esc�L�[��������Ă�����
		SceneMgr_ChangeScene(eScene_Start);//�V�[�������j���[�ɕύX
	}
}

//�`��
void Game_Draw() 
{
	DrawString(0, 0, "�Q�[����ʂł��B", GetColor(255, 255, 255));
	DrawString(0, 20, "Esc�L�[�������ƃX�^�[�g��ʂɖ߂�܂��B", GetColor(255, 255, 255));
}