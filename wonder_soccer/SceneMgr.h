#pragma once

typedef enum {
	eScene_Start,
	eScene_Game,
	eScene_Config
}eScene;

//更新
void SceneMgr_Update();
//描画
void SceneMgr_Draw();
//引数 nextSceneにシーンを変更
void SceneMgr_ChangeScene(eScene nextScene);