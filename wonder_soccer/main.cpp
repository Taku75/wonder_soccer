#include "DxLib.h"
#include "SceneMgr.h"
#include "Keyboard.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); 
	SceneMgr sceneMgr;
	sceneMgr.Initialize();

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{
		Keyboard_Update();
		sceneMgr.Update();  //�X�V
		sceneMgr.Draw();    //�`��

	}

	sceneMgr.Finalize();

	DxLib_End();
	return 0;
}