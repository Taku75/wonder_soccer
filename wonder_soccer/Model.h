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
	virtual void Initialize() override = 0;    //�������������I�[�o�[���C�h�B
	virtual void Finalize() override = 0;        //�I���������I�[�o�[���C�h�B
	virtual void Update() override = 0;        //�X�V�������I�[�o�[���C�h�B
	virtual void Draw() override = 0;            //�`�揈�����I�[�o�[���C�h�B

};