#pragma once

#include "BaseScene.h"
#include "ISceneChanger.h"
#include "StateMgr.h"

//ゲーム画面クラス
class Result : public BaseScene
{
	StateMgr *stateMgr;
public:
	Result(ISceneChanger* changer);
	void Initialize() override;    //初期化処理をオーバーライド。
								   //void Finalize() override;        //終了処理をオーバーライド。
	void Update() override;        //更新処理をオーバーライド。
	void Draw() override;            //描画処理をオーバーライド。

};
