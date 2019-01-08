#include "SoccorGround.h"

SoccerGround::SoccerGround()
{
	handle = MV1LoadModel("./Model/Soccer field/Soccer Grount Base high optimised.blend.x");
	texhandle = LoadGraph("./Model/Soccer field/Soccer Grount Base high Grassllllow.png");
	MV1SetTextureGraphHandle(handle, 0, texhandle, TRUE);
	Pos = VGet(0.0f, 12.5f, 0.0f);
	Scale = VGet(9.0f, 9.0f, 9.0f);
	rpy = VGet(DX_PI_F / 2.0f, 0.0f, 0.0f);
	MV1SetScale(handle, Scale);
	MV1SetPosition(handle, Pos);
	MV1SetRotationXYZ(handle, rpy);
}

SoccerGround::~SoccerGround()
{

}

void SoccerGround::Initialize()
{

}

void SoccerGround::Update()
{

}

void SoccerGround::Draw()
{
	MV1DrawModel(handle);
}

void SoccerGround::Finalize()
{

}