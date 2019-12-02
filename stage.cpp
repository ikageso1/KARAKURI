#pragma once
#include "DxLib.h"
#include "Stage.h"
#include "Unit.h"
#include "Color.hpp"
#include <string.h>
#include <fstream>

extern bool HandaFlag;
extern bool is60HzSwitch;	//�t���b�V�����[�g��60Hz�ł���
//�������O���
namespace{
	int normalBlockGraphic;		//�u���b�N
	int goalBlockGraphic;		//�S�[��
	int needleBlockGraphic;		//�Ƃ�
	int baneBlockGraphic;
}

//�f�t�H���g�R���X�g���N�^
Stage::Stage(void){
	Stage::stageNum = 1;//�X�e�[�W����1�ŏ�����
}

//�R���X�g���N�^
Stage::Stage(int stageNum){
	Stage::stageNum = stageNum;	//�X�e�[�W�i���o�[
	Stage::goalFlag = false;	//�S�[���t���O������
}

//�X�e�[�W�̍쐬
int Stage::CreateStage(unsigned int zanki){
	char String[256];
	int retu = 0;
	//�u���b�N�摜�̌���
	normalBlockGraphic = LoadGraph("Source/Normal.png");
	goalBlockGraphic = LoadGraph("Source/Goal.png");
	needleBlockGraphic = LoadGraph("Source/toge.png");
	baneBlockGraphic = LoadGraph("Source/Bane.png");

	if(HandaFlag){
		//�u���b�N�摜�̌���
		normalBlockGraphic = LoadGraph("Source/Secret/Normal.png");
	}
	ClearDrawScreen();
	SetFontSize(40);
	DrawFormatString(400,400,BLACK,"Stage%d",stageNum);
	DrawFormatString(400,450,BLACK,"�c�@:%d",zanki);
	ScreenFlip();
	SetFontSize(20);
	WaitTimer(500);
	//�}�b�v�̓ǂݍ���
	ReadMap();

	return 0;
}

//�}�b�v�̓ǂݍ���
int	Stage::ReadMap(){
	std::ifstream mapfile;
	//�t�@�C�����J��
	switch(stageNum){
	case 1:
		mapfile = std::ifstream( "Source/Stage/stage1.csv",ios::out);
		break;
	case 2:
		mapfile = std::ifstream( "Source/Stage/stage2.csv",ios::out);
		break;
	case 3:
		mapfile = std::ifstream( "Source/Stage/stage3.csv",ios::out);
		break;
	case 4:
		mapfile = std::ifstream( "Source/Stage/stage4.csv",ios::out);
		break;
	case 5:
		mapfile = std::ifstream( "Source/Stage/stage5.csv",ios::out);
		break;
	case 6:
		mapfile = std::ifstream( "Source/Stage/stage6.csv",ios::out);
		break;
	case 7:
		mapfile = std::ifstream( "Source/Stage/stage7.csv",ios::out);
		break;
	case 8:
		mapfile = std::ifstream( "Source/Stage/stage8.csv",ios::out);
		break;
	case STAGE_NUM+1:
		mapfile = std::ifstream( "StageEditer/editmap.csv",ios::out);
		break;

	}
	//�t�@�C���G���[����
	if(!mapfile){
		throw 1;
	}
	
	//�}�b�v�ǂݍ���
	for(int y=0;y<MAP_LENGTH;y++){
		for(int x=0;x<MAP_WIDTH;x++){
			int data=0;		//�}�b�v�f�[�^�ϐ���錾
			mapfile >> data;	//�f�[�^����
			if(data!=None){
				MapBox_t newBox;
				newBox.leftUp.X = 0 + MAP_PIXEL * x;			//�����x���W
				newBox.leftUp.Y = 0 + MAP_PIXEL * y;			//�����y���W
				newBox.rightDown.X = newBox.leftUp.X + MAP_PIXEL;	//�E����x���W
				newBox.rightDown.Y = newBox.leftUp.Y + MAP_PIXEL;	//�E����y���W
				newBox.blockKind = (BlockKind_t)data;
				mapData.push_back(newBox);
			}
		}
	}
	return 0;
}

//�X�e�[�W�̃Q�b�^�[
list<MapBox_t> Stage::GetMapData(void){
	return mapData;
}

//�X�e�[�W�\��
void Stage::show(void){
	list<MapBox_t>::iterator temp = mapData.begin();
	for(unsigned int i=0;i<mapData.size();i++){
		int x = (int)((*temp).leftUp.X);
		int y = (int)((*temp).leftUp.Y);
		switch((*temp).blockKind){
		case Normal:	//�u���b�N
			DrawGraph(x,y,normalBlockGraphic,FALSE);
			break;
		case Goal:		//�S�[��
			DrawGraph(x,y,goalBlockGraphic,FALSE);
			break;
		case Needle:	//�Ƃ�
			DrawGraph(x,y,needleBlockGraphic,FALSE);
			break;
		case Bane:
			DrawGraph(x,y,baneBlockGraphic,FALSE);
			break;
		}
		temp++;
	}
}


//�����蔻��`�F�b�N
bool Stage::CheckHitBox(Unit* player){
	list<MapBox_t> temp = GetMapData();
	list<MapBox_t>::iterator stageBlockPos;		//�X�e�[�W�̏�Q���u���b�N�̃C�e���[�^
	list<MapBox_t>::iterator hitBoxPos;		//���j�b�g���g�̓����蔻��u���b�N�̃C�e���[�^
	//�����蔻�菉����
	player->hitFlagInit();
	double playerX =player->getX();
	double playerY = player->getY();
	stageBlockPos = temp.begin();	//��Q���u���b�N�̗v�f���ŏ��ɃZ�b�g����
	for(unsigned int i=0;i<temp.size();i++){
		hitBoxPos = player->getHitBox();	//�����蔻��u���b�N�̗v�f���ŏ��ɃZ�b�g
		for(unsigned int j=0;j<player->getHitBoxSize();j++){
			//x���W���g���ł���
			if( (*stageBlockPos).leftUp.X +3 <=  playerX + (*hitBoxPos).rightDown.X &&
				playerX+ (*hitBoxPos).leftUp.X <= (*stageBlockPos).rightDown.X -3){
				//�オ�ڐG
				if(  playerY + (*hitBoxPos).leftUp.Y <= (*stageBlockPos).rightDown.Y &&
					(*stageBlockPos).rightDown.Y <= playerY + (*hitBoxPos).rightDown.Y ){
						//��ɍs���߂������������߂�
						player->setY( (*stageBlockPos).leftUp.Y + (*hitBoxPos).rightDown.Y );
						switch((*stageBlockPos).blockKind){
						case Normal:
							player->setHitFlagUp(true);
							break;	
						case Goal:
							goalFlag = true;	//�S�[���t���O��ݒ肷��B
							break;
						}
				}
				//�����ڐG
				if( playerY + (*hitBoxPos).leftUp.Y <= (*stageBlockPos).leftUp.Y  && 
					(*stageBlockPos).leftUp.Y <= playerY + (*hitBoxPos).rightDown.Y ) {
						//���ɍs���߂������������߂�
						player->setY( (*stageBlockPos).leftUp.Y - (*hitBoxPos).rightDown.Y );	
						switch((*stageBlockPos).blockKind){
						case Normal:
							player->setHitFlagDown(true);
							break;
						case Goal:
							Stage::goalFlag = true;
							goalFlag = true;	//�S�[���t���O��ݒ肷��B
							break;
						case Needle:		//�Ƃ�
							//player->setHitFlagDown(true);
							player->janpInit(false);
							for(int i=0;i<100;i++){
								ClearDrawScreen();
								show();
								player->janp(90);
								if(::is60HzSwitch==true){
									player->janp(90);
									player->janp(90);
								}
								player->show();
								ScreenFlip();
							}
							player->setAliveFlag(false);		//���S
							break;
						case Bane:
							player->setHitFlagDown(true);
							break;
						}
						
				}
			}
			//y���W���g���ł���
			else if((*stageBlockPos).leftUp.Y +1 <= playerY + (*hitBoxPos).rightDown.Y  && 
				playerY + (*hitBoxPos).leftUp.Y  <= (*stageBlockPos).rightDown.Y -1){
				//�E���ڐG
				if( playerX + (*hitBoxPos).leftUp.X <= (*stageBlockPos).leftUp.X &&
					(*stageBlockPos).leftUp.X <= playerX +(*hitBoxPos).rightDown.X ){
						//�E�ɍs���߂������������߂�
						player->setX( (*stageBlockPos).leftUp.X - (*hitBoxPos).rightDown.X );
						switch((*stageBlockPos).blockKind){
						case Normal:
							player->setHitFlagRight(true);
							break;
						case Goal:
							goalFlag = true;
							break;
						case Bane:
							player->refrect();
							break;
						}
						
				}
				//�����ڐG
				if(playerX + (*hitBoxPos).leftUp.X <= (*stageBlockPos).rightDown.X &&
					(*stageBlockPos).rightDown.X <= playerX + (*hitBoxPos).rightDown.X ) {
						//���ɍs���߂������������߂�
						player->setX( (*stageBlockPos).rightDown.X );	
						switch((*stageBlockPos).blockKind){
						case Normal:
							player->setHitFlagLeft(true);
							break;
						case Goal:
							goalFlag = true;
							break;
						case Bane:
							player->refrect();
							break;
						}
						
				}
			}
			hitBoxPos++;
		}
		stageBlockPos++;
	}
	return true;
}

bool Stage::getGoalFlag(){
	return goalFlag;
}