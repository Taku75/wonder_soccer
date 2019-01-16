#include "Keeper.h"

Keeper::Keeper()
{
	handle = MV1LoadModel("./Model/soccer keeper/Soccer man Hand only.blend.x");
	Pos = VGet(-40.5f, 1.5f, 0.0f);
	Scale = VGet(0.7f, 0.7f, 0.7f);
	rpy = VGet(0.0f, 3 * DX_PI_F / 2.0f, 0.0f);
	MV1SetScale(handle, Scale);
	MV1SetPosition(handle, Pos);
	MV1SetRotationXYZ(handle, rpy);
}

void Keeper::setPos(VECTOR _pos)
{
	Pos = _pos;
	MV1SetPosition(handle, Pos);
}

Keeper::~Keeper()
{
	MV1DeleteModel(handle);
}

void Keeper::Initialize()
{

}

void Keeper::Update()
{

}

void Keeper::Draw()
{
	MV1DrawModel(handle);
}

void Keeper::Finalize()
{

}