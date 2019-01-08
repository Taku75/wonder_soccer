#include "Start.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Keyboard.h"
#include "SoccorGround.h"
#include "ObjectFactory.h"
#include "SoccerGoal.h"
#include "SoccerBall.h"
#include "CharCenter.h"

const static int GAME_Y = 240;    //�u�Q�[���v������y�ʒu
const static int CONFIG_Y = 300;    //�u�ݒ�v������y�ʒu
const static int ScreenX = 640;
const static char* GAME_SENT = "�Q�[���X�^�[�g";
const static char* CONFIG_SENT = "�ݒ�";
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
static int *config_handle;
static int soccoer_ball_handle;
static int cousor_se_handle;
static int detect_se_handle;
static SoccerGround *soccerGround;
static SoccerGoal *soccerGoal;
static SoccerBall *soccerBall;

Start::Start(ISceneChanger* changer) : BaseScene(changer)
{

}

//������
void Start::Initialize()
{
	FontHandle = CreateFontToHandle("Lucida Handwriting", 48, 7, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	no_select_handle = CreateFontToHandle(NULL, 24, -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	select_handle = CreateFontToHandle(NULL, 30, -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	soccoer_ball_handle = LoadGraph("./Graph/soccer_ball.png");
	game_handle = &select_handle;
	config_handle = &no_select_handle;
	cousor_se_handle = LoadSoundMem("./Music/cursor2.mp3");
	detect_se_handle = LoadSoundMem("./Music/decision7.mp3");
	soccerGround = new SoccerGround();
	soccerGoal = new SoccerGoal();
	soccerBall = new SoccerBall();
}

 //�X�V
void Start::Update()
{
	if (Keyboard_Get(KEY_INPUT_DOWN) == 1) 
	{	//���L�[��������Ă�����
		NowSelect = (NowSelect + 1) % eStart_Num;//�I����Ԃ��������
		PlaySoundMem(cousor_se_handle, DX_PLAYTYPE_BACK);
	}

	if (Keyboard_Get(KEY_INPUT_UP) == 1) 
	{	//��L�[��������Ă�����
		NowSelect = (NowSelect + (eStart_Num - 1)) % eStart_Num;//�I����Ԃ���グ��
		PlaySoundMem(cousor_se_handle, DX_PLAYTYPE_BACK);
	}
	if (Keyboard_Get(KEY_INPUT_RETURN) == 1) 
	{	//�G���^�[�L�[�������ꂽ��
		switch (NowSelect) 
		{	//���ݑI�𒆂̏�Ԃɂ���ď����𕪊�
			case eStart_Game://�Q�[���I�𒆂Ȃ�
				PlaySoundMem(detect_se_handle, DX_PLAYTYPE_NORMAL);
				mSceneChanger->ChangeScene(eScene_Game);//�V�[�����Q�[����ʂɕύX
				break;

			case eStart_Config://�ݒ�I�𒆂Ȃ�
				PlaySoundMem(detect_se_handle, DX_PLAYTYPE_NORMAL);
				mSceneChanger->ChangeScene(eScene_Config);//�V�[����ݒ��ʂɕύX
				break;
		}
	}
	soccerGround->Update();
	soccerGoal->Update();
	soccerBall->Update();
	SetLightEnable(FALSE);
	SetGlobalAmbientLight(GetColorF(0.000f, 0.000f, 0.000f, 0.0f));


	int Light1Handle = CreatePointLightHandle(VGet(1.374f, 29.322f, 0.000f), 2000.000f, 1.000f, 0.000f, 0.000f);
	SetLightDifColorHandle(Light1Handle, GetColorF(1.000f, 1.000f, 1.000f, 1.000f));
	SetLightSpcColorHandle(Light1Handle, GetColorF(0.500f, 0.500f, 0.500f, 0.000f));
	SetLightAmbColorHandle(Light1Handle, GetColorF(0.000f, 0.000f, 0.000f, 0.000f));


	SetCameraPositionAndTarget_UpVecY(VGet(-18.588196f, 1.612696f, -0.000f), VGet(-36.191231f, 1.612696f, -0.000f));
	SetCameraNearFar(0.293217f, 73.304352f);

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
	draw_string_center(0, 640, 100, 200, TITLE, GetColor(255, 0, 255), FontHandle);
	draw_string_center(0, 640, GAME_Y, 480, GAME_SENT, GetColor(255, 255, 255), *game_handle);
	draw_string_center(0, 640, CONFIG_Y, 480,CONFIG_SENT, GetColor(255, 255, 255), *config_handle);
	int y = 0;
	switch (NowSelect) 
	{	//���݂̑I����Ԃɏ]���ď����𕪊�
		case eStart_Game://�Q�[���I�𒆂Ȃ�
			y = GAME_Y;    //�Q�[���̍��W���i�[
			game_handle = &select_handle;
			config_handle = &no_select_handle;
			DrawExtendGraph(150, y, 180, y + 30, soccoer_ball_handle, TRUE);
			DrawExtendGraph(460, y, 490, y + 30, soccoer_ball_handle, TRUE);
			break;

		case eStart_Config://�ݒ�I�𒆂Ȃ�
			y = CONFIG_Y;    //�ݒ�̍��W���i�[
			game_handle = &no_select_handle;
			config_handle = &select_handle;
			DrawExtendGraph(230, y, 260, y + 30, soccoer_ball_handle, TRUE);
			DrawExtendGraph(380, y, 410, y + 30, soccoer_ball_handle, TRUE);
			break;
	}
	//DrawBox(195, y, 510, y + 30, GetColor(255, 255, 0), FALSE);
	//DrawString(250, y, "��", GetColor(255, 255, 255));
}

