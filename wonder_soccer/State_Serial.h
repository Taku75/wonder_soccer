#pragma once
#include "Task.h"
#include "IStateChanger.h"

class State_Serial : public Task
{
	IStateChanger *mStateChanger;
public:
	State_Serial(IStateChanger *changer){ mStateChanger = changer; }
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize() override;
};