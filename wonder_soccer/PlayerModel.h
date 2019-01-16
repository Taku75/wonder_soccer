#pragma once
#include "Model.h"

class PlayerModel : public BaseModel
{
protected:
	int AttachIndex;
	float TotalTime, PlayTime;

public:
	BOOL action;
	PlayerModel();
	~PlayerModel();
	virtual void Initialize() override;    //初期化処理をオーバーライド。
	virtual void Finalize() override;        //終了処理をオーバーライド。
	virtual void Update() override;        //更新処理をオーバーライド。
	virtual void Draw() override;            //描画処理をオーバーライド。
	void Clear();
};