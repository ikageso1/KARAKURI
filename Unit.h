#pragma once
#include <string>
#include <list>
#include "Box.h"
#include "Air.h"
using namespace std;

class Unit{
private:
	Pos pos;				//���W
	Pos a;					//�����x
	int unitZanki;			//�c�@
	int graphic;			//�摜
	list<MapBox_t> hitBox;	//�����蔻��̔�
	HitFlag_t hitFlag;		//�����蔻��t���O
	bool janpFlag;			//�W�����v�t���O
	bool aliveFlag;			//�����t���O
	Air air;				//��C��R�I�u�W�F�N�g
	void SetHitBox(void);	//�����蔻��ݒ�֐�
public:
	//�R���X�g���N�^
	Unit(TCHAR* graph,unsigned int zanki);
	//�摜�ύX
	void ChangeGraphic(TCHAR* graph);
	//�摜�̕\��
	void show(void);
	//���͂ɂ���Ĉړ�����
	void move(int);
	//�W�����v�֐�
	void janp(int deg);
	//�W�����v�t���O�������֐�
	void janpInit(bool);
	//air�֐��̒���
	void viewAir(void);
	//�S�[���t���O
	bool GetGoalFlag(void);
	//�����蔻��t���O������
	void hitFlagInit();
	//�����蔻��̃Q�b�^�[
	list<MapBox_t>::iterator getHitBox();
	//�����蔻��̗v�f���̃Q�b�^�[
	int getHitBoxSize();
	//�����t���O�̃Z�b�^�[
	void setAliveFlag(bool);
	//�����`�F�b�N�֐�
	bool CheckAlive();
	//�Q�[���I�[�o�[�`�F�b�N�֐�
	bool CheckGameOver();
	//�c�@�̃f�N�������g�֐�
	void decZanki();
	//�c�@�̃Q�b�^�[
	unsigned int getZanki();
	//�΂˂ɂ�锽��
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