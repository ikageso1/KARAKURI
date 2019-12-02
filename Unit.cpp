#include "DxLib.h"
#include "Unit.h"
#include <string>
#include "Color.hpp"
using namespace std;

//���t���b�V�����[�g��60Hz�ł���(�O���ϐ�)
extern bool is60HzSwitch;	

//�R���X�g���N�^
Unit::Unit(TCHAR* graph,unsigned int zanki){
	Air air = Air();
	//�摜�̃��[�h
	Unit::graphic = LoadGraph(graph);
	//�����t���O�𗧂Ă�
	aliveFlag = true;
	//�c�@�̏�����
	Unit::unitZanki = zanki;
	//x���W��y���W0�ŏ�����
	Unit::pos.X = 0;
	Unit::pos.Y = 0;
	//�����x��0�ŏ�����
	Unit::a.X = 0;
	Unit::a.Y = 0;
	//�W�����v�t���O������
	Unit::janpFlag = false;
	//�����蔻��t���O������
	Unit::hitFlag.down = false;
	Unit::hitFlag.up = false;
	Unit::hitFlag.left = false;
	Unit::hitFlag.right = false;
	//�����蔻��̏�����
	SetHitBox();
}

//�摜�ύX
void Unit::ChangeGraphic(TCHAR* graph){
	//�摜�̃��[�h
	Unit::graphic = LoadGraph(graph);
}

//��ʕ\��
void Unit::show(void){
	DrawGraph((int)(pos.X),(int)(pos.Y),graphic,TRUE);
	//�f�o�b�O�p
	//DrawFormatString(100,50,BLACK,"%d:%d:%d:%d",hitFlag.up,hitFlag.down,hitFlag.right,hitFlag.left);
}

//�ړ�
void Unit::move(int Key){
	if(hitFlag.down == false){				//��������ڒn
		if(Unit::janpFlag==true){			//�W�����v���Ȃ�
			Unit::janp(30);				//90�x�W�����v����
		}
		else{									//�W�����v���łȂ�
			if(air.getInitFlag() ==false){		//����������ĂȂ�
				janpInit(true);
			}
			else{								//�W�����v���ł���
				air.Calc(0.0);						//�d�͌v�Z
				Unit::pos.X += air.getdx();
				Unit::pos.Y -= air.getdy();
				if(::is60HzSwitch == true){			//60Hz�Ȃ�Γ����4�{��
					air.Calc(0.0);					//�v�Z
					Unit::pos.X += air.getdx();
					Unit::pos.Y -= air.getdy();
					air.Calc(0.0);					//�v�Z
					Unit::pos.X += air.getdx();
					Unit::pos.Y -= air.getdy();
				}
			}
		}
	}
	else{									//�������ڒn
		//�n�ʂɂ����Ƃ��̃W�����v�t���O����������
		Unit::janpFlag = false;				//�W�����v�t���O��߂�
		air.AirInit(90,0.0,10.0);			//�d��(��)�̏�����
		Unit::air.setInitFlag(false);		//�d�͐���N���X�𖢏������ɖ߂�
		
		if(hitFlag.right==false){			//�E������ڒn
			if(Key & PAD_INPUT_RIGHT){		//�E�ړ�
				Unit::pos.X += 0.5;
				if(is60HzSwitch == true){	//60Hz�Ȃ�Γ����4�{��
					Unit::pos.X +=1.0;
				}
			}
		}
		if(hitFlag.left == false){			//��������ڒn
			if(Key & PAD_INPUT_LEFT){		//���ړ�
				Unit::pos.X-= 0.5;
				if(is60HzSwitch == true){	//60Hz�Ȃ�Γ����4�{��
					Unit::pos.X -=1.0;
				}
			}
		}
		if(hitFlag.up == false){			//�������ڒn
			if(Key & PAD_INPUT_2){			//�~�{�^��(x�L�[)�������ꂽ�ꍇ
				Unit::janpFlag = true;		//�W�����v�t���O�𗧂Ă�
				if(Key & PAD_INPUT_RIGHT){
					janp(45);
				}
				else if(Key & PAD_INPUT_LEFT){
					janp(135);
				}
				else{
					janp(90);
				}
			}
		}
	}

	return;
}

//�����蔻�����
void Unit::SetHitBox(void){
	MapBox_t temp = MapBox_t(0,0,50,50,Goal);
	Unit::hitBox.push_back(temp);
}

//�W�����v
void Unit::janp(int deg){
	//���������Ȃ��
	if(Unit::air.getInitFlag() == false){

		air.AirInit(deg,50.0,0.5);			//�������֐�
		air.Calc(0.0);						//��C��R�Ȃ��Ōv�Z
		Unit::pos.X += air.getdx();
		Unit::pos.Y -= air.getdy();
		air.Calc(0.0);
		Unit::pos.X += air.getdx();
		Unit::pos.Y -= air.getdy();

	}	
	else{									//�������ς�
		//�v�Z
		if(hitFlag.down == true){				//�n�ʂɂ����Ȃ��
				Unit::janpFlag = false;				//�W�����v�t���O��߂�
				Unit::air.setInitFlag(false);		//���������ɖ߂�
		}
		else{							//�n�ʂɂ��܂��ĂȂ���
			air.Calc(0.0);				//�v�Z
			Unit::pos.X += air.getdx();
			Unit::pos.Y -= air.getdy();
			air.Calc(0.0);				//�v�Z
			Unit::pos.X += air.getdx();
			Unit::pos.Y -= air.getdy();
			if(::is60HzSwitch == true){	//60Hz�Ȃ�Γ����3�{��
				air.Calc(0.0);				//�v�Z
				Unit::pos.X += air.getdx();
				Unit::pos.Y -= air.getdy();
				air.Calc(0.0);				//�v�Z
				Unit::pos.X += air.getdx();
				Unit::pos.Y -= air.getdy();
			}
		}
	}	


}

//�W�����v�������֐�
void Unit::janpInit(bool flag){
	air.AirInit(90,0.0,10.0);		//�d�͂̏�����
	air.setInitFlag(flag);			//�������t���O�𗧂Ă�	
}

void Unit::setAliveFlag(bool flag){
	aliveFlag = flag;
}
//�����`�F�b�N�֐�
bool Unit::CheckAlive(){
	//���W��800�ȏ�i�������j�𒴂��Ă�����
	if(pos.Y > 800){
		aliveFlag = false;
	}
	return aliveFlag;
}

//�c�@�f�N�������g
void Unit::decZanki(){
	unitZanki--;
}
//�Q�[���I�[�o�[�`�F�b�N�֐�
bool Unit::CheckGameOver(){
	if(unitZanki < 0){
		return true; 
	}
	else{
		return false;
	}
}

unsigned int Unit::getZanki(){
	return unitZanki;
}
//�f�o�b�N�pair�֐��e�X�g
void Unit::viewAir(){
	air.view();
	DrawFormatString(400,180,BLACK,"playerX %.3f",pos.X);
}

//�����蔻�菉����
void Unit::hitFlagInit(){
	Unit::hitFlag.down = false;
	Unit::hitFlag.left = false;
	Unit::hitFlag.right = false;
	Unit::hitFlag.up = false;
}

//�����蔻��̃Q�b�^�[
list<MapBox_t>::iterator Unit::getHitBox(){
	return hitBox.begin();
}

//�����蔻��̗v�f���̃Q�b�^�[
int Unit::getHitBoxSize(){
	return hitBox.size();
}

//�΂˂ɂ�锽��
void Unit::refrect(){
	air.reflect(-1.0,-1.0);
}

//x�̃Q�b�^�[
double Unit::getX(){
	return pos.X;
}
//y�̃Q�b�^�[
double Unit::getY(){
	return pos.Y;
}
//x�̃Z�b�^�[
void Unit::setX(double x){
	pos.X = x;
}
//y�̃Z�b�^�[
void Unit::setY(double y){
	pos.Y = y;
}


//�E�̓����蔻��̃Z�b�^�[
void Unit::setHitFlagRight(bool flag){
	hitFlag.right = flag;
}
//���̓����蔻��̃Z�b�^�[
void Unit::setHitFlagLeft(bool flag){
	hitFlag.left = flag;
}
//��̓����蔻��̃Z�b�^�[
void Unit::setHitFlagUp(bool flag){
	hitFlag.up = flag;
}
//���̓����蔻��̃Z�b�^�[
void Unit::setHitFlagDown(bool flag){
	hitFlag.down = true;
}