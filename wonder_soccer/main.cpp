#include "DxLib.h"
#include "SceneMgr.h"
#include "Keyboard.h"
#include "Obj.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//SetWindowText("wonder goal");
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); 
	keeper = new Keeper();
	soccerBall = new SoccerBall();
	soccerGoal = new SoccerGoal();
	soccerGround = new SoccerGround();
	playerModel = new PlayerModel();
	remain = 5;
	ballhandle = new BallGraph[remain];
	score = new int[remain];
	SceneMgr sceneMgr;
	sceneMgr.Initialize();
	SetCameraPositionAndTarget_UpVecY(VGet(-22.105957f, 4.128867f, -0.00f), VGet(-36.225117f, 0.146609f, -0.00f));
	SetCameraNearFar(0.293217f, 73.304352f);


	SetLightEnable(FALSE);
	SetGlobalAmbientLight(GetColorF(0.200f, 0.200f, 0.200f, 0.0f));

	int Light0Handle = CreateDirLightHandle(VGet(-0.896f, -0.444f, -0.005f));
	SetLightDifColorHandle(Light0Handle, GetColorF(1.000f, 1.000f, 1.000f, 1.000f));
	SetLightSpcColorHandle(Light0Handle, GetColorF(0.500f, 0.500f, 0.500f, 0.000f));
	SetLightAmbColorHandle(Light0Handle, GetColorF(0.000f, 0.000f, 0.000f, 0.000f));

	int Light1Handle = CreateDirLightHandle(VGet(0.100f, -0.995f, 0.000f));
	SetLightDifColorHandle(Light1Handle, GetColorF(1.000f, 1.000f, 1.000f, 1.000f));
	SetLightSpcColorHandle(Light1Handle, GetColorF(0.500f, 0.500f, 0.500f, 0.000f));
	SetLightAmbColorHandle(Light1Handle, GetColorF(0.000f, 0.000f, 0.000f, 0.000f));

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{
		fps.Update();
		Keyboard_Update();
		sceneMgr.Update();  //çXêV
		sceneMgr.Draw();    //ï`âÊ
		fps.Wait();
	}

	sceneMgr.Finalize();

	DxLib_End();
	return 0;
}