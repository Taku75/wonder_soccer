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
	void setPos(VECTOR _pos);
	void setrpy(VECTOR _rpy);
	virtual void Initialize() override;    //�������������I�[�o�[���C�h�B
	virtual void Finalize() override;        //�I���������I�[�o�[���C�h�B
	virtual void Update() override;        //�X�V�������I�[�o�[���C�h�B
	virtual void Draw() override;            //�`�揈�����I�[�o�[���C�h�B
};

class BallGraph
{
	int handle;
public:
	BallGraph();
	void Update();
	void Draw();
	int x, y;
};