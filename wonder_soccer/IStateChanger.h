#pragma once
typedef enum
{
	eState_Serial,    //メニュー画面
	eState_Initial,    //ゲーム画面
	eState_kick,
	eState_None,    //無し
} eState;

//シーンを変更するためのインターフェイスクラス
class IStateChanger
{
public:
	virtual ~IStateChanger() {};
	virtual void ChangeState(eState NextState) = 0;//指定シーンに変更する
};