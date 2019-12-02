#pragma once
#define MAP_LENGTH 12
#define MAP_WIDTH 16
#define MAP_PIXEL 50
#define STAGE_NUM 10			//�X�e�[�W��
#include <list>
#include "Unit.h"
using namespace std;



class Stage{
private:
	bool goalFlag;			//�S�[���t���O
	list<MapBox_t> mapData;	//�}�b�v��Q���̓����蔻��
	int stageNum;			//�X�e�[�W�ԍ�
	int ReadMap(void);		//�}�b�v�ǂݍ��݊֐�
public:
	Stage(void);						//�f�t�H���g�R���X�g���N�^
	Stage(int);							//int�������R���X�g���N�^
	int CreateStage(unsigned int);				//�}�b�v�쐬�֐�
	list<MapBox_t> GetMapData(void);	//�}�b�v�f�[�^�̃Q�b�^�[
	void show(void);					//�}�b�v�\��
	bool CheckHitBox(Unit*);			//�����蔻��`�F�b�N
	bool getGoalFlag();					//�S�[���t���O�̃Q�b�^�[
};