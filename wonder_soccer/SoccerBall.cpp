#include "SoccerBall.h"

SoccerBall::SoccerBall()
{
	handle = MV1LoadModel("./Model/Soccer ball/Soccer Ball Low.blend.x");
	Pos = VGet(-28.0f, 0.0f, 0.0f);
	Scale = VGet(0.20f, 0.20f, 0.20f);
	rpy = VGet(0.0f, 0.0f, 0.0f);
	MV1SetScale(handle, Scale);
	MV1SetPosition(handle, Pos);
	MV1SetRotationXYZ(handle, rpy);
	vPos = VGet(0.0f, 0.0f, 0.0f);
}

void SoccerBall::setPos(VECTOR _pos)
{
	Pos = _pos;
	MV1SetPosition(handle, Pos);
}

void SoccerBall::setrpy(VECTOR _rpy)
{
	rpy = _rpy;
	MV1SetRotationXYZ(handle, rpy);
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


BallGraph::BallGraph()
{
	handle = LoadGraph("./Graph/soccer_ball.png");
	x = 0; y = 430;
}

void BallGraph::Update()
{

}

void BallGraph::Draw()
{
	DrawExtendGraph(x, y, x + 30, y + 30, handle, TRUE);
}