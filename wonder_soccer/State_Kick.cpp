#include "State_Kick.h"
#include "DxLib.h"
#include "Obj.h"

static bool sendFlag;
static int font_handle;
static int Whistle_handle;
static int Shoot_handle;
static int goal_handle;
static int no_goal_handle;
static int audience_handle;

void State_Kick::Initialize()
{
	font_handle = CreateFontToHandle(NULL, 40, -1, -1);
	Whistle_handle = LoadSoundMem("./Music/SNES-Soccer01-07(Whistle).mp3");
	Shoot_handle = LoadSoundMem("./Music/SNES-Soccer01-01(Shoot).mp3");
	goal_handle = LoadSoundMem("./Music/people_people-stadium-cheer1.mp3");
	audience_handle = LoadSoundMem("./Music/soccer_audience.mp3");
	no_goal_handle = LoadSoundMem("./Music/people_people-stadium-cheer2.mp3");
	PlaySoundMem(audience_handle, DX_PLAYTYPE_LOOP);
	PlaySoundMem(Whistle_handle, DX_PLAYTYPE_BACK);
	addi = 0;
	ini = true;
	x = -28.0f;
	y = 0;
	z = 0; angleX = 0.f; angleY = 0.f;
	t = 0;
	playerModel->Clear();
	sendFlag = false;
	box = 'R';
	kicker_ser.write(&box, 1);
	vx = -1.0f*(float)(rand() % 8 + 10); vy = (float)(rand() % 5); vz = (float)(rand() % 3);
}

void State_Kick::Update()
{
	if (kicker_ser.available() >= 12 && !sendFlag)
	{
		auto readResult = kicker_ser.read();
		if (readResult.size() >= 12) { sendFlag = true; }
		vvx.binaly[0] = readResult[3];
		vvx.binaly[1] = readResult[2];
		vvx.binaly[2] = readResult[1];
		vvx.binaly[3] = readResult[0];
		vvy.binaly[0] = readResult[7];
		vvy.binaly[1] = readResult[6];
		vvy.binaly[2] = readResult[5];
		vvy.binaly[3] = readResult[4];
		vvz.binaly[0] = readResult[11];
		vvz.binaly[1] = readResult[10];
		vvz.binaly[2] = readResult[9];
		vvz.binaly[3] = readResult[8];
		vx = vvx.data; vy = vvy.data; vz = vvz.data;
	}
	if (sendFlag)
		playerModel->Update();
	if (CheckHitKey(KEY_INPUT_3))
		playerModel->Update();

	int8_t z_bun = 0;
	uint8_t y_bun = 0;
	/*if (keeper.available() > 1)
	{
	auto pos = keeper.read();
	z_bun = pos[0];
	y_bun = pos[1];
	}*/
	/*z_bun = (float)(rand() % 256 - 128);
	y_bun = (float)(rand() % 256);
	hz = dz * z_bun;
	hy = dy * y_bun;
	*/
	if (CheckHitKey(KEY_INPUT_UP))
	{
	hy += 2*dy;
	}
	if(CheckHitKey(KEY_INPUT_DOWN))
	{
	hy -= 2*dy;
	}
	if(CheckHitKey(KEY_INPUT_LEFT))
	{
	hz -= 2*dz;
	}
	if(CheckHitKey(KEY_INPUT_RIGHT))
	{
	hz += 2*dz;
	}
	// 指定位置にモデルを配置
	if (playerModel->action) {//二秒待ってから→fpsを定義する時間
		if(t == 0)
			PlaySoundMem(Shoot_handle, DX_PLAYTYPE_BACK);
					 //t += 1.0f / fps.mFps;
		t += 1.0f / 60.0f;
		if (t > 10) { ini = false; }

		if (x > -41.8) {	//ゴールについた時の条件
			x += vx * (1.0f / fps.mFps);
			z += vz * (1.0f / fps.mFps);
			angleX -= DX_PI_F / 90;
			if (CheckHitKey(KEY_INPUT_Z))
			{
				//if (z > -9 && z < 9)
				z += vz * (1.0f / fps.mFps);
				angleY += 0.99f*DX_PI_F / 90;
			}
			if (CheckHitKey(KEY_INPUT_C))
			{
				//if(z>-9&&z<9)
				z -= vz * (1.0f / fps.mFps);
				angleY += 0.99f*DX_PI_F / 90;
			}
		}
		if (y >= 0)	//地面よりも高い時の条件

			y = vy * t - 0.4f*9.8*t*t + 1.0f;

		else {

			vx = 0.998f*vx;
			vz = 0.998f*vz;
		}

		if (x <= -39 && x >= -39.3)
		{
			if (y >= hy - 0.3 && y <= hy + 0.7 && z >= hz - 0.5 && z <= hz + 0.5)
			{
				vx = -vx;

				PlaySoundMem(no_goal_handle, DX_PLAYTYPE_BACK);
				box = 'F';
			}
		}

		if (x <= -39.5)
		{
			addi++;

			if (y <= 3.1 && z >= -3.0 && 3.0 >= z) {
				//con = 'CON';
				if (addi == 1) {
					box = 'G';

					PlaySoundMem(goal_handle, DX_PLAYTYPE_BACK);
				}
			}
			//ゴールポストの判定
			else if (y<3.5 && z <= 3.5&& z >3.0 || y < 3.5 && ref && z >= -3.5&&z < -3.0 || y < 3.5 && y>3.1 && -3.5 <= z && z <= 3.5)
			{
				vx = -vx;
				ref = false;
				if (addi == 1) {
					box = 'F';
					PlaySoundMem(no_goal_handle, DX_PLAYTYPE_BACK);
				}

			}

			else
			{
				if (addi == 1) {
					box = 'F';
					PlaySoundMem(no_goal_handle, DX_PLAYTYPE_BACK);
				}

			}
			/*if (addi > 300) {
			ini = false;
			addi = 0;
			sleep = 0;
			}*/
		}
		else if (vx < vvx.data*0.55) {
			if (addi == 1) {
				box = 'F';
				addi += 120;
			}
		}
		if (box == 'G' || box == 'F') {
			addi++;
		}

		if (addi > 300) {
			ini = false;
			addi = 0;
			sleep = 0;
		}
		if (box == 'G')
		{
			score[5 - remain] = 1;
		}
		if(box == 'F')
		{
			score[5 - remain] = 0;
		}

	}
	else {
		sleep++;//カウントして
	}

	if (!ini)
	{
		remain--;
		StopSoundMem(audience_handle);
		mStateChanger->ChangeState(eState_Initial);
	}
	//playerModel->Update();
	soccerBall->setPos(VGet(x, y, z));
	soccerBall->setrpy(VGet(angleX, angleY, 0.0f));
	keeper->setPos(VGet(-40.5f, hy, hz));
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "x=%.1f y=%.1f z=%.1f", x, y, z);
	//DrawFormatString(0, 20, GetColor(255, 255, 255), "%.1f", fps.mFps);
}

void State_Kick::Draw()
{
	playerModel->Draw();
	keeper->Draw();
	soccerBall->Draw();
	soccerGoal->Draw();
	soccerGround->Draw();
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
				DrawStringToHandle(200 + i * 50, 20, "〇", GetColor(255, 0, 0), font_handle);
			if (score[i]==0)
				DrawStringToHandle(200 + i * 50, 20, "×", GetColor(0, 0, 255), font_handle);
		}
	}
}

void State_Kick::Finalize()
{

}
