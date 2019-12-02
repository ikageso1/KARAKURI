#pragma once
#include <stdio.h>
#include <math.h>
#include "DxLib.h"
#include "Color.hpp"
#include "Air.h"

//マクロ
#define dt 0.017			//微小時間
#define PI 3.1415926535	//円周率
#define g 9.80665		//重力加速度

//デフォルトコンストラクタ
Air::Air(){
	x = 0.0;
	y = 0.0;
	vx = 0.0;
	vy = 0.0;
	Air::m =0.0;
	Air::initFlag = false;
}
//コンストラクタもどき(角度と初速度と重さを指定)
void Air::AirInit(int deg,double v0,double m){
	//座標の初期化
	x = 0.0;
	y = 0.0;
	dx = 0.0;
	dy = 0.0;

	vx = v0 * cos(deg/180.0*PI);	//x方向の初速度
	vy = v0 * sin(deg/180.0*PI);	//y方向の初速度

	Air::m = m;		//重さの初期化
	initFlag = true;	//初期化フラグ
}
	
//計算関数(抵抗係数,反発係数)
void Air::Calc(double Cd){
	double v = hypot(vx,vy);	//速度
	double AirFx = -Cd * v * vx;	//x方向の空気抵抗
	double AirFy = -Cd * v * vy;	//y方向の空気抵抗

	Fx = AirFx;				//x方向の力を代入
	Fy = -g*m + AirFy;		//y方向の力を代入

	double ax = Fx / m;		//x方向の加速度
	double ay = Fy / m;		//y方向の加速度

	//x座標の計算
	dx = vx * dt;
	x += dx;
	vx += ax * dt;

	//y座標の計算
	dy = vy * dt;
	y += dy;
	vy += ay * dt;
}

//反発計算
void Air::reflect(double ex,double ey){
	vx *= ex;
	vy *= -ey;
}
//壁の計算
void Air::Kabe(double ex,double distance){
	if(x>distance){
		x = distance;	//xを壁の距離にもどす
		vx *= -ex;
	}
}

//x座標のゲッター
double Air::getx(){	
	return x;
}

//y座標のゲッター
double Air::gety(){
	return y;
}

//dxのゲッター
double Air::getdx(){
	return dx;
}

//dyのゲッター
double Air::getdy(){
	return dy;
}

//初期化フラグのゲッター
bool Air::getInitFlag(){
	return Air::initFlag;
}

//初期化フラグのセッター
void Air::setInitFlag(bool flag){
	Air::initFlag = flag;
}

//画面表示
void Air::view(void){
	DrawFormatString(400,100,BLACK,"x座標:%.3f,y座標:%.3f",x,y);
	DrawFormatString(400,120,BLACK,"vy:%.3f vx:%.3f",vy,vx);
	DrawFormatString(400,140,BLACK,"dy:%.3f dx:%.3f",dy,dx);
	DrawFormatString(400,160,BLACK,"initFkag %d",initFlag);
}