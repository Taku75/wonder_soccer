#pragma once

#include "Task.h"
#include "DxLib.h"
#include <iostream>
#include <map>

class BaseModel : public Task
{
protected:
	VECTOR Pos;
	VECTOR rpy;
	VECTOR Scale;
	int handle;
	int texhandle;
public:
	BaseModel() {};
	virtual ~BaseModel() {};
	virtual void Initialize() override = 0;    //初期化処理をオーバーライド。
	virtual void Finalize() override = 0;        //終了処理をオーバーライド。
	virtual void Update() override = 0;        //更新処理をオーバーライド。
	virtual void Draw() override = 0;            //描画処理をオーバーライド。

};