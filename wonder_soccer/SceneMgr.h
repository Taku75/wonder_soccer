#pragma once

typedef enum {
	eScene_Start,
	eScene_Game,
	eScene_Config
}eScene;

//�X�V
void SceneMgr_Update();
//�`��
void SceneMgr_Draw();
//���� nextScene�ɃV�[����ύX
void SceneMgr_ChangeScene(eScene nextScene);