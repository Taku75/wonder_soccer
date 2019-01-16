#include "PlayerModel.h"

PlayerModel::PlayerModel()
{
	handle = MV1LoadModel("./Model/Soccer man/Soccer man low polygon riged animeblend.mv1");
	AttachIndex = MV1AttachAnim(handle, 0, -1, FALSE);
	TotalTime = MV1GetAttachAnimTotalTime(handle, AttachIndex);
	PlayTime = 0.0f;
	Pos = VGet(-25.0f, 0.0f, 0.0f);
	Scale = VGet(0.0025f, 0.0025f, 0.0025f);
	rpy = VGet(0.0f, DX_PI_F * 3 / 2.0f, 0.0f);
	MV1SetScale(handle, Scale);
	MV1SetPosition(handle, Pos);
	MV1SetRotationXYZ(handle, rpy);
}

PlayerModel::~PlayerModel()
{

}

void PlayerModel::Initialize()
{

}

void PlayerModel::Update()
{
	if (PlayTime <= TotalTime)
	{
		//PlayTime += (1.0f / fps.mFps) * 30;
		PlayTime += (1.0f / 60.0f) * 30;
		if (PlayTime >= TotalTime - 10.0f)
		{
			//PlayTime = 0.0f;
			action = TRUE;
		}
		MV1SetAttachAnimTime(handle, AttachIndex, PlayTime);
	}
}

void PlayerModel::Draw()
{
	MV1DrawFrame(handle, 127);
}

void PlayerModel::Finalize()
{

}

void PlayerModel::Clear()
{
	PlayTime = 0.0f;
	action = FALSE;
	MV1SetAttachAnimTime(handle, AttachIndex, PlayTime);
}