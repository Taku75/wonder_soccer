#include "State_Initial.h"
#include "DxLib.h"
#include "Obj.h"
static int font_handle;
static bool serial_flag;
void State_Initial::Initialize()
{
	font_handle = CreateFontToHandle(NULL, 40, -1, -1);
	serial_flag = false;
	box = 'I';
	kicker_ser.write(&box, 1);
}

void State_Initial::Update()
{
	if (kicker_ser.available() > 0)
	{
		auto v = kicker_ser.read();
		if (v[0] == 'O')
		{
			serial_flag = true;
		}
	}
	if (CheckHitKey(KEY_INPUT_2) != 0)
	{
		mStateChanger->ChangeState(eState_kick);
	}
	if(serial_flag)
	{
		mStateChanger->ChangeState(eState_kick);
	}
}

void State_Initial::Draw()
{
	playerModel->Draw();
	keeper->Draw();
	soccerBall->Draw();
	soccerGoal->Draw();
	soccerGround->Draw();
	DrawBox(20, 90, 620, 120, GetColor(255, 255, 255), TRUE);
	DrawLineBox(20, 90, 620, 120, GetColor(100, 100, 100));
	DrawString(40, 100, "キッカーデバイスの真ん中のボタンを押して初期化を行ってください", GetColor(0,0,0));
	DrawString(430, 440, "残り球数", GetColor(255, 255, 255));
	for (int i = 0; i < remain; i++)
	{
		ballhandle[i].x = 500 + i * 20;
		ballhandle[i].Draw();
	}
	for (int i = 0; i < 5; i++)
	{
		if (score[i] != 2)
		{
			if (score[i]==1)
				DrawStringToHandle(200+i*50, 20, "〇", GetColor(255, 0, 0), font_handle);
			if (score[i]==0)
				DrawStringToHandle(200+i*50, 20, "×", GetColor(0, 0, 255), font_handle);
		}
	}
}

void State_Initial::Finalize()
{

}
