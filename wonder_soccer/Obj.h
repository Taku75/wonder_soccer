#pragma once
#include "Keeper.h"
#include "SoccerBall.h"
#include "SoccerGoal.h"
#include "SoccorGround.h"
#include "PlayerModel.h"
#include "Fps.h"
#include "Serial.h"

extern Keeper *keeper;
extern SoccerBall *soccerBall;
extern SoccerGoal *soccerGoal;
extern PlayerModel *playerModel;
extern SoccerGround *soccerGround;
extern int cousor_se_handle;
extern int detect_se_handle;
extern BallGraph *ballhandle;
extern int *score;

extern Serial kicker_ser;
extern Serial keeper_ser;
extern Fps fps;
extern float vx, vy, vz, t;
extern float x, y, z, angle, speed;
extern int  Grassllllow;
extern int readResult;
extern int ovx, ovy, ovz;

extern unsigned char box;

extern bool ini;
extern bool ref;

extern int addi;

extern int  remain;
extern int g;
extern int sleep;
extern float angleX , angleY;

extern float r;

extern float tx;

extern float cx, cy, cz;

extern int thy;
extern int thz;
extern float dz;
extern float dy;
extern float hz, hy;

extern const char *String;

union uf
{
	float data;
	byte binaly[4];
};

extern uf vvx;
extern uf vvy;
extern uf vvz;