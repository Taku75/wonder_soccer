#pragma once
#include "DxLib.h"
#include "Model.h"

class SoccerGoal : public BaseModel
{
public:
	SoccerGoal();
	~SoccerGoal();
	virtual void Initialize() override;    //�������������I�[�o�[���C�h�B
	virtual void Finalize() override;        //�I���������I�[�o�[���C�h�B
	virtual void Update() override;        //�X�V�������I�[�o�[���C�h�B
	virtual void Draw() override;            //�`�揈�����I�[�o�[���C�h�B
};