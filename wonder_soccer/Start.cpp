#include "Start.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Keyboard.h"
#include "CharCenter.h"
#include "Obj.h"

const static int GAME_Y = 240;    //�u�Q�[���v������y�ʒu
const static int CONFIG_Y = 300;    //�u�ݒ�v������y�ʒu
const static int ScreenX = 640;
const static char* GAME_SENT = "Press Enter Key";
const static char* TITLE = "WONDER GOOL";

typedef enum
{
	eStart_Game,        //�Q�[��
	eStart_Config,    //�ݒ�

	eStart_Num,        //�{���ڂ̐�
} eStart;

static int NowSelect = eStart_Game;    //���݂̑I�����(�����̓Q�[���I��)
static int FontHandle; //�t�H���g�n���h��
static int no_select_handle;
static int select_handle;
static int *game_handle;
//Keeper *keeper;

Start::Start(ISceneChanger* changer) : BaseScene(changer)
{

}

//������
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

 //�X�V
void Start::Update()
{
	if (Keyboard_Get(KEY_INPUT_RETURN) == 1) 
	{	//�G���^�[�L�[�������ꂽ��
			PlaySoundMem(detect_se_handle, DX_PLAYTYPE_NORMAL);
			mSceneChanger->ChangeScene(eScene_Game);//�V�[�����Q�[����ʂɕύX
	}
	soccerGround->Update();
	soccerGoal->Update();
	soccerBall->Update();
	playerModel->Update();
	keeper->Update();
}

//�`��
void Start::Draw()
{
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
	soccerGround->Draw();
	soccerGoal->Draw();
	soccerBall->Draw();
	playerModel->Clear();
	playerModel->Draw();
	keeper->Draw();
	draw_string_center(0, 640, 100, 200, TITLE, GetColor(255, 255, 255), FontHandle);
	draw_string_center(0, 640, GAME_Y, 480, GAME_SENT, GetColor(255, 255, 255), *game_handle);
}

