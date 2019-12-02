#include "DxLib.h"
#include "Game.h"
#include <string>
#include "Color.hpp"
using namespace std;
//���t���b�V�����[�g��60Hz�ł���(�O���ϐ�)
extern bool is60HzSwitch;	
extern bool HandaFlag;
//�Q�[���̃V�X�e������
bool GameSystem(Stage,Unit*);

//
bool SinglePlay(unsigned int zanki){
	Unit player = Unit("Source/Player.png",zanki);	//�v���C���[�I�u�W�F�N�g����
	if(HandaFlag){
		player.ChangeGraphic("Source/Secret/Player.png");
	}
	for(int i=0;i<STAGE_NUM;i++){
		Stage stage = Stage(i+1);
		stage.CreateStage(player.getZanki());	//�X�e�[�W�쐬
		if( !(GameSystem(stage,&player)) ){
			//�Q�[���I�[�o�[
			if(player.CheckGameOver()){	
				ClearDrawScreen();
				DrawFormatString(500,500,BLACK,"�Q�[���I�[�o�[");
				ScreenFlip();
				WaitTimer(500);
				return false;
			}
			i--;
		}
		//�v���C���[��x,y���W��������
		player.setX(0.0);
		player.setY(0.0);
		//�W�����v�̏�����
		player.janpInit(true);
		player.setAliveFlag(true);
	}
	return true;
}

//
bool MultiPlay(unsigned int zanki){
	Unit player = Unit("Source/player.png",zanki);	//�v���C���[�I�u�W�F�N�g����
	if(HandaFlag){
		player.ChangeGraphic("Source/Secret/Player.png");
	}
	
	int cursor=-1;	//�J�[�\��
	int keyBuf;		//�L�[

	SetFontSize(30);	//�t�H���g�T�C�Y����
	while(true){
		ClearDrawScreen();
		keyBuf = GetJoypadInputState(DX_INPUT_KEY_PAD1);	//�L�[��Ԋi�[
		if(ProcessMessage()==-1){	//�G���[�ł̃��[�v�E�o
			throw 100;
			break;
		}
		if(keyBuf & PAD_INPUT_9){	//ESC�ł̃��[�v�E�o
			throw "ESC";
			break;
		}
		if(keyBuf & PAD_INPUT_3 && cursor != -1){	//���� (1�{�^�� or Z�L�[)
			break;
		}
		//�I�����ړ�
		if(keyBuf & PAD_INPUT_UP && cursor >0 ){		//��
			cursor -= 1;
			WaitTimer(85);
		}
		if(keyBuf & PAD_INPUT_DOWN && cursor <STAGE_NUM){	//��
			cursor += 1;
			WaitTimer(85);
		}
		DrawFormatString(300,50,BLACK,"�X�e�[�W�Z���N�g"); 
		for(int i=0;i<STAGE_NUM+1;i++){
			if(i==cursor){
				DrawFormatString(300,100+40*i,RED,"�X�e�[�W%d",i+1);
			}
			else if(i==STAGE_NUM){
				DrawFormatString(300,100+40*i,PINK,"���ł����Ƃ܂���");
			}
			else {
				DrawFormatString(300,100+40*i,BLACK,"�X�e�[�W%d",i+1);
			}
		}
		ScreenFlip();	//��ʓK�p
	}

	bool isContinue = true;		//�Q�[�����s�t���O�i��蒼���j
	do{
		if(ProcessMessage()==-1){	//�G���[�ł̃��[�v�E�o
			throw 100;
			break;
		}
		if(keyBuf & PAD_INPUT_9){	//ESC�ł̃��[�v�E�o
			throw "ESC";
			break;
		}

		Stage stage = Stage(cursor+1);
		stage.CreateStage(player.getZanki());	//�X�e�[�W�쐬
		if( !(GameSystem(stage,&player)) ){
			//�Q�[���I�[�o�[
			if(player.CheckGameOver()){	
				ClearDrawScreen();
				DrawFormatString(500,500,BLACK,"�Q�[���I�[�o�[");
				ScreenFlip();
				WaitTimer(500);
				return false;
			}
		}
		else{
			isContinue = false;
		}
		//�v���C���[��x,y���W��������
		player.setX(0.0);
		player.setY(0.0);
		//�W�����v�̏�����
		player.janpInit(true);
		player.setAliveFlag(true);
	}while(isContinue);
	return true;
}
//�Q�[���V�X�e��
bool GameSystem(Stage stage,Unit* player){
	while(true){
		int keyBuf;	//�L�[�̊i�[�ϐ�
		keyBuf = GetJoypadInputState(DX_INPUT_KEY_PAD1);	//�L�[��Ԋi�[
		if(ProcessMessage()==-1){	//�G���[�ł̃��[�v�E�o
			throw 100;
			break;
		}
		if(keyBuf & PAD_INPUT_9){	//ESC�ł̃��[�v�E�o
			throw "ESC";
			break;
		}
		//�L�����N�^�̈ړ�
		player->move(keyBuf);
		//��ʂ̏���
		ClearDrawScreen();
		//�����蔻��
		stage.CheckHitBox(player);
		//���t���b�V�����[�g�̑��x����
		if(is60HzSwitch == true){
			//�L�����N�^�̈ړ�
			player->move(keyBuf);
			//�����蔻��
			stage.CheckHitBox(player);
		}
		//��ʕ\��
		player->show();
		//(�e�X�g��)�X�e�[�W�̕\��
		stage.show();

		//���S����
		if(player->CheckAlive()==false){
			player->decZanki();
			return false;
		}
		//��ʓK�p
		ScreenFlip();
		//�S�[�����̃��[�v�E�o
		if(stage.getGoalFlag() == true){
			ClearDrawScreen();
			DrawFormatString(500,500,BLACK,"���肠�[");
			ScreenFlip();
			WaitTimer(500);
			break;
		}
	}
	return true;
}