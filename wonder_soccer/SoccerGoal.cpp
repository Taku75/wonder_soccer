#include "SoccerGoal.h"

SoccerGoal::SoccerGoal()
{
	handle = MV1LoadModel("./Model/Soccer goal/goal low optimised.blend.x");
	MV1SetTextureGraphHandle(handle, 0, texhandle, TRUE);
	Pos = VGet(-43.7f, 0.0f, 0.0f);
	Scale = VGet(0.48f, 0.48f, 0.48f);
	rpy = VGet(0.0f, DX_PI_F / 2.0f, DX_PI_F * 3 / 2.0f);
	MV1SetScale(handle,Scale);
	MV1SetPosition(handle, Pos);
	MV1SetRotationXYZ(handle, rpy);
}

SoccerGoal::~SoccerGoal()
{
	MV1DeleteModel(handle);
}

void SoccerGoal::Initialize()
{

}

void SoccerGoal::Update()
{

}

void SoccerGoal::Draw()
{
	MV1DrawModel(handle);
}

void SoccerGoal::Finalize()
{
	
}