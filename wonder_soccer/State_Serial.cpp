#include "State_Serial.h"
#include "DxLib.h"
#include "Obj.h"

static bool serial_flag;
void State_Serial::Initialize()
{
	serial_flag = false;
	playerModel->Clear();
}

void State_Serial::Update()
{
	box = 'S';			//X押したらループ抜けてSが入る。
	auto list = getSerialList();
	for (const auto info : list)
	{
		if (!kicker_ser.isOpened())
		{
			if (kicker_ser.open(info))
			{
				unsigned char c = 'S';
				kicker_ser.write(&c, 1);
				Sleep(1000);
				if (kicker_ser.available() > 0) {
					auto v = kicker_ser.read();
					if (v[0] != 'k')
					{
						kicker_ser.close();
					}
				}
				else
				{
					kicker_ser.close();
				}
			}
		}
		if (!keeper_ser.isOpened())
		{
			if (keeper_ser.open(info))
			{
				unsigned char c = 'S';
				keeper_ser.write(&c, 1);
				Sleep(1000);
				if (keeper_ser.available() > 0) {
					auto v = keeper_ser.read();
					if (v[0] != 'K')
					{
						keeper_ser.close();
					}
				}
				else
				{
					keeper_ser.close();
				}
			}
		}
	}

	if (keeper_ser.isOpened() && kicker_ser.isOpened())
	{
		serial_flag = true;
	}

	if (serial_flag)
	{	
		mStateChanger->ChangeState(eState_Initial);
	}
	if (CheckHitKey(KEY_INPUT_1))
	{
		mStateChanger->ChangeState(eState_Initial);
	}
}

void State_Serial::Draw()
{
	playerModel->Draw();
	keeper->Draw();
	soccerBall->Draw();
	soccerGoal->Draw();
	soccerGround->Draw();
	if (!serial_flag)
		DrawString(200, 10, "デバイスが接続されていません", GetColor(0,0,0));
}

void State_Serial::Finalize()
{

}
