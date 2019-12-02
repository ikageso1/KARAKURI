#pragma once
#include <string>
#include <list>
#include "Box.h"
#include "Air.h"
using namespace std;

class Unit{
private:
	Pos pos;				//座標
	Pos a;					//加速度
	int unitZanki;			//残機
	int graphic;			//画像
	list<MapBox_t> hitBox;	//当たり判定の箱
	HitFlag_t hitFlag;		//あたり判定フラグ
	bool janpFlag;			//ジャンプフラグ
	bool aliveFlag;			//生存フラグ
	Air air;				//空気抵抗オブジェクト
	void SetHitBox(void);	//当たり判定設定関数
public:
	//コンストラクタ
	Unit(TCHAR* graph,unsigned int zanki);
	//画像変更
	void ChangeGraphic(TCHAR* graph);
	//画像の表示
	void show(void);
	//入力によって移動する
	void move(int);
	//ジャンプ関数
	void janp(int deg);
	//ジャンプフラグ初期化関数
	void janpInit(bool);
	//air関数の調査
	void viewAir(void);
	//ゴールフラグ
	bool GetGoalFlag(void);
	//当たり判定フラグ初期化
	void hitFlagInit();
	//当たり判定のゲッター
	list<MapBox_t>::iterator getHitBox();
	//当たり判定の要素数のゲッター
	int getHitBoxSize();
	//生存フラグのセッター
	void setAliveFlag(bool);
	//生存チェック関数
	bool CheckAlive();
	//ゲームオーバーチェック関数
	bool CheckGameOver();
	//残機のデクリメント関数
	void decZanki();
	//残機のゲッター
	unsigned int getZanki();
	//ばねによる反射
	void refrect();
	//
	double getX();
	double getY();
	void setX(double);
	void setY(double);
	void setHitFlagRight(bool);
	void setHitFlagLeft(bool);
	void setHitFlagUp(bool);
	void setHitFlagDown(bool);
};