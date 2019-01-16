#include "Result.h"
#include "DxLib.h"
#include "Obj.h"
//#include "CharCenter.h"

static int score_handle;
static int sound_handle;
Result::Result(ISceneChanger* changer) : BaseScene(changer)
{
}

//‰Šú‰»
void Result::Initialize()
{
	score_handle = CreateFontToHandle("Lucida Handwriting", 48, 7, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	sound_handle = LoadSoundMem("./Music/SNES-Soccer01-06(Whistle).mp3");
	PlaySoundMem(sound_handle, DX_PLAYTYPE_BACK);
}

//XV
void Result::Update()
{
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		mSceneChanger->ChangeScene(eScene_Start);
	}
}

//•`‰æ
void Result::Draw()
{
	playerModel->Draw();
	keeper->Draw();
	soccerBall->Draw();
	soccerGoal->Draw();
	soccerGround->Draw();
	DrawBox(190, 190, 460, 280, GetColor(255, 255, 255), TRUE);
	DrawLineBox(190, 190, 460, 280, GetColor(100, 100, 100));
	int point = 0;
	for (int i = 0; i < 5; i++)
	{
		point += score[i];
	}
	DrawFormatStringFToHandle(190, 210, GetColor(255, 0, 0), score_handle, "Score : %d", point);
}