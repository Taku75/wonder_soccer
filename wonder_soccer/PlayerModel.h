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
	virtual void Initialize() override;    //�������������I�[�o�[���C�h�B
	virtual void Finalize() override;        //�I���������I�[�o�[���C�h�B
	virtual void Update() override;        //�X�V�������I�[�o�[���C�h�B
	virtual void Draw() override;            //�`�揈�����I�[�o�[���C�h�B
	void Clear();
};