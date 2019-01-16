#pragma once

#include "Task.h"
#include "IStateChanger.h"

class State_Initial : public Task
{
	IStateChanger *mStateChanger;
public:
	State_Initial(IStateChanger *changer) { mStateChanger = changer; }
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize() override;
};