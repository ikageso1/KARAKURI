#include "DxLib.h"
#include "Unit.h"
#include "Stage.h"
#include "Game.h"
#include "Color.hpp"
#include <string>
using namespace std;

//�v���g�^�C�v�錾
void Title(void);
int Menu(void);
int Option(unsigned int *zanki);
int reflesh(void);			//���t���b�V�����[�g�̐ݒ�

//�O���[�o���ϐ�
bool is60HzSwitch;	//�t���b�V�����[�g��60Hz�ł���
bool HandaFlag = false;		//�B���v�f�t���O
//�������O���
namespace{
	struct gamemode{
		//�Q�[�����[�h�񋓑�
		enum enum_t{
			SINGLE,
			MULTI,
			OPTION,
			END
		};
	};

	struct optionmode{
		//�I�v�V�����ł̐ݒ�l�񋓑�
		enum enum_t{
			FULLSCREEN,
			ZANKI,
			SECRET,
			END
		};
	};
}
//���C���֐�
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
						 LPSTR lpCmdLine, int nCmdShow )
{	
	unsigned int zanki = 3;			//�����ݒ�̎c�@��
	SetGraphMode(800,600,16);
	ChangeWindowMode(TRUE);
	SetBackgroundColor(255,255,255) ;		//�w�i�𔒂ɐݒ�
	SetWindowText("KARAKURI");			//�^�C�g�����̐ݒ�

	if( DxLib_Init() == -1 )	// �c�w���C�u��������������
	{
		return -1;
	}

	ColorInit();		//�F�萔��������
	SetDrawScreen( DX_SCREEN_BACK ) ;	// �`����ʂ𗠉�ʂɃZ�b�g
	try{
		while(true){
			reflesh();
			Title();		//�^�C�g�����

			//�Q�[�����[�h�I��
			switch(Menu()){
				//�͂��߂���
			case gamemode::SINGLE:
				SinglePlay(zanki);	//�Q�[���J�n
				break;
				//�}���`�v���C
			case gamemode::MULTI:
				MultiPlay(zanki);
				break;
				//���Ղ����
			case gamemode::OPTION:
				Option(&zanki);
				break;
				//���イ��傤
			case gamemode::END:
				throw "ESC";
				break;
			}
		}
	}
	//ESC�ł̗�O����
	catch(char *a){
		ClearDrawScreen();
		SetFontSize(20);
		DrawFormatString(500,500,BLACK,"�I�����܂�");
		ScreenFlip();
		WaitTimer(500);
	}
	//�v���Z�X���b�Z�[�W�ɂ���O����
	catch(int a){
	}
	InitGraph() ;		// �S�O���t�B�b�N��������
	DxLib_End() ;		// �c�w���C�u�����g�p�̏I������
	return 0;
}

//�^�C�g��
void Title(void){
	int titleGraphic = LoadGraph("Source/title.bmp");		//�^�C�g����ʂ̃��[�h

	while(true){
		ClearDrawScreen();
		int keyBuf = GetJoypadInputState(DX_INPUT_KEY_PAD1);	//�L�[��Ԋi�[
		if(ProcessMessage()==-1){	//�G���[�ł̃��[�v�E�o
			throw 100;
			break;
		}
		if(keyBuf & PAD_INPUT_9){	//ESC�ł̃��[�v�E�o
			throw "ESC";
			break;
		}
		if(keyBuf & PAD_INPUT_10){		//�X�y�[�X�L�[�Ŕ�����
			break;
		}

		DrawGraph(0,0,titleGraphic,FALSE);		//�`��
		ScreenFlip();
	}
}

//���j���[
int Menu(void){
	int cursor=0;	//�J�[�\��
	int keyBuf;		//�L�[
	string mozi[]={"�͂��߂���","�X�e�[�W�Z���N�g","�I�v�V����","�I��"};
	const int MODE_NUMBER = 4;


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
		if(keyBuf & PAD_INPUT_3){	//���� (1�{�^�� or Z�L�[)
			break;
		}

		//�I�����ړ�
		if(keyBuf & PAD_INPUT_UP && cursor > 0){		//��
			cursor -= 1;
			WaitTimer(85);
		}

		if(keyBuf & PAD_INPUT_DOWN && cursor < MODE_NUMBER-1){	//��
			cursor += 1;
			WaitTimer(85);
		}
		for(int i=0;i<MODE_NUMBER;i++){
			if(i==cursor){
				DrawFormatString(300,400+40*i,RED,mozi[i].c_str());
			}
			else {
				DrawFormatString(300,400+40*i,BLACK,mozi[i].c_str());
			}
		}
		DrawFormatString(100,50,BLACK,"���{�^���iC�L�[)�Ō���");
		DrawFormatString(100,100,BLACK,"�~�{�^��(X�L�[)�ŃW�����v");
		ScreenFlip();	//��ʓK�p
	}
	return cursor;
}

//�I�v�V����
int Option(unsigned int *zanki){
	int cursor =0;	//�J�[�\���ϐ�
	int keyBuf;	//�L�[�ϐ�
	/*�萔*/	
	const int pixel = 40;		//�����\���萔
	const int xPoint = 300;		//�����\����x���W
	const int yPoint = 400;		//�����\����y���W
	while(true){
		ClearDrawScreen();
		keyBuf = GetJoypadInputState(DX_INPUT_KEY_PAD1);	//�L�[��Ԃ��i�[
		if(ProcessMessage()==-1){	//�G���[�ł̃��[�v�E�o
			throw 100;
			break;
		}
		if(keyBuf & PAD_INPUT_9){	//ESC�ł̃��[�v�E�o
			throw "ESC";
			break;
		}
		if(keyBuf & PAD_INPUT_UP && cursor > optionmode::FULLSCREEN){		//��
			cursor -= 1;
			WaitTimer(85);
		}

		if(keyBuf & PAD_INPUT_DOWN && cursor < optionmode::END){	//��
			cursor += 1;
			WaitTimer(85);
		}

		//��ʕ\��
		if(cursor == optionmode::FULLSCREEN){
			DrawFormatString(xPoint,yPoint+pixel*optionmode::FULLSCREEN,RED,"�t���X�N���[���̃E�B���h�E���[�h");
			if(keyBuf & PAD_INPUT_RIGHT){
				ChangeWindowMode(TRUE);
				SetDrawScreen( DX_SCREEN_BACK ) ;	// �`����ʂ𗠉�ʂɃZ�b�g
			}
			if(keyBuf & PAD_INPUT_LEFT){
				ChangeWindowMode(FALSE);
				SetDrawScreen( DX_SCREEN_BACK ) ;
			}
		}
		else DrawFormatString(xPoint,yPoint+pixel*optionmode::FULLSCREEN,BLACK,"�t���X�N���[���̃E�B���h�E���[�h");

		if(cursor == optionmode::ZANKI ){
			DrawFormatString(xPoint,yPoint+pixel*optionmode::ZANKI,RED,"�c�@��:%d",*zanki);
			//�c�@���̒���
			if(keyBuf & PAD_INPUT_RIGHT){
				if(*zanki<99){
					(*zanki)++;
					WaitTimer(85);
				}
			}
			if(keyBuf & PAD_INPUT_LEFT){
				if(*zanki>1){
					(*zanki)--;
					WaitTimer(85);
				}
			}
		}
		else DrawFormatString(xPoint,yPoint+pixel*optionmode::ZANKI,BLACK,"�c�@��:%d",*zanki);

		if(cursor == optionmode::SECRET ){
			DrawFormatString(xPoint,yPoint+pixel*optionmode::SECRET,RED,"�B�����[�h");
			if(keyBuf & PAD_INPUT_3){
				while(true){
					if(ProcessMessage()==-1){	//�G���[�ł̃��[�v�E�o
						throw 100;
						break;
					}
					if(keyBuf & PAD_INPUT_9){	//ESC�ł̃��[�v�E�o
						throw "ESC";
						break;
					}
					ClearDrawScreen();
					DrawFormatString(200,200,BLACK,"�X�y�[�X�Ŕ�����");
					ScreenFlip();
					if(CheckHitKey(KEY_INPUT_SPACE)){
						break;
					}
					int O = CheckHitKey(KEY_INPUT_O);
					int T = CheckHitKey(KEY_INPUT_T);
					int I = CheckHitKey(KEY_INPUT_I);
					if(O && T && I){
						HandaFlag = true;
						ClearDrawScreen();
						DrawFormatString(200,200,BLACK,"�ݒ芮��!");
						ScreenFlip();
						WaitTimer(1000);
						break;
					}

				}
			}
		}
		else DrawFormatString(xPoint,yPoint+pixel*optionmode::SECRET,BLACK,"�B�����[�h");

		if(cursor == optionmode::END){
			DrawFormatString(xPoint,yPoint+pixel*gamemode::END,RED,"�I��");
			if(keyBuf & PAD_INPUT_3){
				break;
			}
		}
		else DrawFormatString(xPoint,yPoint+pixel*gamemode::END,BLACK,"�I��");
		ScreenFlip();

	}
	return 0;
}

//���t���b�V�����[�g����
int reflesh(){
	int FrameTime, ScreenFlipCount, StartTime ;

	// ScreenFlip �����s�����񐔂𐔂���J�E���^��������
	ScreenFlipCount = 0 ;

	// ��ʂ��P��X�V�����܂ő҂�
	ScreenFlip() ;

	// �v���J�n������ۑ�
	StartTime = GetNowCount() ;

	// 1�b�ԂɎ��s�ł��� ScreenFlip �̉񐔂��v��
	while(true)
	{
		// ��ʂ��P��X�V�����܂ő҂�
		ScreenFlip() ;

		// �v���J�n����1�b�o�߂��Ă����烋�[�v���甲����
		if( GetNowCount() - StartTime >= 1000 )
			break ;

		// ScreenFlip �����s�����񐔂��C���N�������g
		ScreenFlipCount ++ ;
	}
	//���t���b�V�����[�g��90Hz�ȉ��Ȃ��
	if(ScreenFlipCount < 90){
		is60HzSwitch = true;		//�����炭�A60Hz
	}
	else{
		is60HzSwitch = false;		//�����炭�A120Hz
	}
	// ScreenFlip �����s�����񐔂ƌv�����Ԃ����ʈ��X�V�ӂ�̎��Ԃ��Z�o����
	FrameTime = ScreenFlipCount ;
	//�f�o�b�N�p
	//	DrawFormatString(200,200,BLACK,"%d",FrameTime);
	//	ScreenFlip();
	//	WaitKey();
	return 0;
}