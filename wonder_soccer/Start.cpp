#include "Start.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Keyboard.h"
#include "CharCenter.h"
#include "Obj.h"

const static int GAME_Y = 240;    //「ゲーム」文字のy位置
const static int CONFIG_Y = 300;    //「設定」文字のy位置
const static int ScreenX = 640;
const static char* GAME_SENT = "Press Enter Key";
const static char* TITLE = "WONDER GOOL";

typedef enum
{
	eStart_Game,        //ゲーム
	eStart_Config,    //設定

	eStart_Num,        //本項目の数
} eStart;

static int NowSelect = eStart_Game;    //現在の選択状態(初期はゲーム選択中)
static int FontHandle; //フォントハンドル
static int no_select_handle;
static int select_handle;
static int *game_handle;
//Keeper *keeper;

Start::Start(ISceneChanger* changer) : BaseScene(changer)
{

}

//初期化
void Start::Initialize()
{
	for (int i = 0; i < remain; i++)
	{
		score[i] = 2;
	}
	FontHandle = CreateFontToHandle("Lucida Handwriting", 48, 7, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	no_select_handle = CreateFontToHandle(NULL, 24, -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	select_handle = CreateFontToHandle(NULL, 30, -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	playerModel->Clear();
	game_handle = &select_handle;
	cousor_se_handle = LoadSoundMem("./Music/cursor2.mp3");
	detect_se_handle = LoadSoundMem("./Music/decision7.mp3");
	playerModel->Clear();
}

 //更新
void Start::Update()
{
	if (Keyboard_Get(KEY_INPUT_RETURN) == 1) 
	{	//エンターキーが押されたら
			PlaySoundMem(detect_se_handle, DX_PLAYTYPE_NORMAL);
			mSceneChanger->ChangeScene(eScene_Game);//シーンをゲーム画面に変更
	}
	soccerGround->Update();
	soccerGoal->Update();
	soccerBall->Update();
	playerModel->Update();
	keeper->Update();
}

//描画
void Start::Draw()
{
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
	soccerGround->Draw();
	soccerGoal->Draw();
	soccerBall->Draw();
	playerModel->Clear();
	playerModel->Draw();
	keeper->Draw();
	draw_string_center(0, 640, 100, 200, TITLE, GetColor(255, 255, 255), FontHandle);
	draw_string_center(0, 640, GAME_Y, 480, GAME_SENT, GetColor(255, 255, 255), *game_handle);
}

