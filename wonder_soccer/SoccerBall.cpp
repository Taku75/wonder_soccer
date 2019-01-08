#include "SoccerBall.h"

SoccerBall::SoccerBall()
{
	handle = MV1LoadModel("./Model/Soccer ball/Soccer Ball Low.blend.x");
	Pos = VGet(-28.5f, 0.15f, 0.0f);
	Scale = VGet(0.30f, 0.30f, 0.30f);
	rpy = VGet(0.0f, 0.0f, 0.0f);
	MV1SetScale(handle, Scale);
	MV1SetPosition(handle, Pos);
	MV1SetRotationXYZ(handle, rpy);
	vPos = VGet(0.0f, 0.0f, 0.0f);
}

SoccerBall::~SoccerBall()
{

}

void SoccerBall::Initialize()
{

}

void SoccerBall::Update()
{

}

void SoccerBall::Draw()
{
	MV1DrawModel(handle);
}

void SoccerBall::Finalize()
{

}