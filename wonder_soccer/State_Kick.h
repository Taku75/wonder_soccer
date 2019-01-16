#pragma once
#pragma once

#include "Task.h"
#include "IStateChanger.h"

class State_Kick : public Task
{
	IStateChanger *mStateChanger;
public:
	State_Kick(IStateChanger *changer) { mStateChanger = changer; }
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Finalize() override;
};