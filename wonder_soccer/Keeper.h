#pragma once

#include "Model.h"

class Keeper : public BaseModel
{
public:
	Keeper();
	~Keeper();
	void setPos(VECTOR _pos);
	virtual void Initialize() override;    //初期化処理をオーバーライド。
	virtual void Finalize() override;        //終了処理をオーバーライド。
	virtual void Update() override;        //更新処理をオーバーライド。
	virtual void Draw() override;
};