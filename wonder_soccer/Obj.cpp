#include "Obj.h"
#include "Serial.h"

Keeper *keeper;
SoccerBall *soccerBall;
SoccerGoal *soccerGoal;
PlayerModel *playerModel;
SoccerGround *soccerGround;
int cousor_se_handle;
int detect_se_handle;
BallGraph *ballhandle;

Serial kicker_ser;
Serial keeper_ser;

Fps fps;
float vx = -5.0f, vy = 10.0f, vz = -5.0f, t = 0.0f;
float x = -28.0f, y = 0, z = 0, angle = 0, speed = 1;
int  Grassllllow = 0;
int readResult = 0;
int ovx = 0, ovy = 0, ovz = 0;

unsigned char box = 'S';

bool ini;
bool ref = true;

int addi = 0;

int  remain = 5;
int g = 0;
int sleep = 0;
float angleX = 0.f, angleY = 0.f;

float r = 10.0f;

float tx = -30.0f;

float cx = tx, cy = 0.0f, cz = r;

int thy = 15;
int thz = 15;
float dz = 6.0f / 256.0f;
float dy = 3.1f / 256.0f;
float hz, hy = 0.0f;

uf vvx;
uf vvy;
uf vvz;

BOOL kickaction = FALSE;
const char *String = 0;
int *score;