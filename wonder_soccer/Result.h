#pragma once

#include "BaseScene.h"
#include "ISceneChanger.h"
#include "StateMgr.h"

//�Q�[����ʃN���X
class Result : public BaseScene
{
	StateMgr *stateMgr;
public:
	Result(ISceneChanger* changer);
	void Initialize() override;    //�������������I�[�o�[���C�h�B
								   //void Finalize() override;        //�I���������I�[�o�[���C�h�B
	void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Draw() override;            //�`�揈�����I�[�o�[���C�h�B

};