#pragma once

#include "Model.h"

class Keeper : public BaseModel
{
public:
	Keeper();
	~Keeper();
	void setPos(VECTOR _pos);
	virtual void Initialize() override;    //�������������I�[�o�[���C�h�B
	virtual void Finalize() override;        //�I���������I�[�o�[���C�h�B
	virtual void Update() override;        //�X�V�������I�[�o�[���C�h�B
	virtual void Draw() override;
};