#pragma once
#include "DxLib.h"
#include "Model.h"

class SoccerBall : public BaseModel
{
protected:
	VECTOR vPos;
public:
	SoccerBall();
	~SoccerBall();
	virtual void Initialize() override;    //初期化処理をオーバーライド。
	virtual void Finalize() override;        //終了処理をオーバーライド。
	virtual void Update() override;        //更新処理をオーバーライド。
	virtual void Draw() override;            //描画処理をオーバーライド。
};