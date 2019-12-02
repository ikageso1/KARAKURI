#pragma once
#include <stdio.h>
#include <math.h>
#include "DxLib.h"
#include "Color.hpp"
#include "Air.h"

//�}�N��
#define dt 0.017			//��������
#define PI 3.1415926535	//�~����
#define g 9.80665		//�d�͉����x

//�f�t�H���g�R���X�g���N�^
Air::Air(){
	x = 0.0;
	y = 0.0;
	vx = 0.0;
	vy = 0.0;
	Air::m =0.0;
	Air::initFlag = false;
}
//�R���X�g���N�^���ǂ�(�p�x�Ə����x�Əd�����w��)
void Air::AirInit(int deg,double v0,double m){
	//���W�̏�����
	x = 0.0;
	y = 0.0;
	dx = 0.0;
	dy = 0.0;

	vx = v0 * cos(deg/180.0*PI);	//x�����̏����x
	vy = v0 * sin(deg/180.0*PI);	//y�����̏����x

	Air::m = m;		//�d���̏�����
	initFlag = true;	//�������t���O
}
	
//�v�Z�֐�(��R�W��,�����W��)
void Air::Calc(double Cd){
	double v = hypot(vx,vy);	//���x
	double AirFx = -Cd * v * vx;	//x�����̋�C��R
	double AirFy = -Cd * v * vy;	//y�����̋�C��R

	Fx = AirFx;				//x�����̗͂���
	Fy = -g*m + AirFy;		//y�����̗͂���

	double ax = Fx / m;		//x�����̉����x
	double ay = Fy / m;		//y�����̉����x

	//x���W�̌v�Z
	dx = vx * dt;
	x += dx;
	vx += ax * dt;

	//y���W�̌v�Z
	dy = vy * dt;
	y += dy;
	vy += ay * dt;
}

//�����v�Z
void Air::reflect(double ex,double ey){
	vx *= ex;
	vy *= -ey;
}
//�ǂ̌v�Z
void Air::Kabe(double ex,double distance){
	if(x>distance){
		x = distance;	//x��ǂ̋����ɂ��ǂ�
		vx *= -ex;
	}
}

//x���W�̃Q�b�^�[
double Air::getx(){	
	return x;
}

//y���W�̃Q�b�^�[
double Air::gety(){
	return y;
}

//dx�̃Q�b�^�[
double Air::getdx(){
	return dx;
}

//dy�̃Q�b�^�[
double Air::getdy(){
	return dy;
}

//�������t���O�̃Q�b�^�[
bool Air::getInitFlag(){
	return Air::initFlag;
}

//�������t���O�̃Z�b�^�[
void Air::setInitFlag(bool flag){
	Air::initFlag = flag;
}

//��ʕ\��
void Air::view(void){
	DrawFormatString(400,100,BLACK,"x���W:%.3f,y���W:%.3f",x,y);
	DrawFormatString(400,120,BLACK,"vy:%.3f vx:%.3f",vy,vx);
	DrawFormatString(400,140,BLACK,"dy:%.3f dx:%.3f",dy,dx);
	DrawFormatString(400,160,BLACK,"initFkag %d",initFlag);
}