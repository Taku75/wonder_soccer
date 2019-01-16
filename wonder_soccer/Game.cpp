#include "Game.h"
#include "DxLib.h"
#include "Obj.h"
Game::Game(ISceneChanger* changer) : BaseScene(changer) 
{
	stateMgr = new StateMgr();
}

//初期化
void Game::Initialize() 
{
	playerModel->Clear();
	stateMgr->Initialize();
}

//更新
void Game::Update() 
{
	stateMgr->Update();
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0)
	{	 //Escキーが押されていたら
		mSceneChanger->ChangeScene(eScene_Start);//シーンをメニューに変更
	}
	if (remain <= 0)
	{
		remain = 5;
		mSceneChanger->ChangeScene(eScene_Result);
	}
}

//描画
void Game::Draw() 
{
	stateMgr->Draw();
	//BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
	//DrawString(0, 0, "ゲーム画面です。", GetColor(255, 255, 255));
	//DrawString(0, 20, "Escキーを押すとメニュー画面に戻ります。", GetColor(255, 255, 255));
}