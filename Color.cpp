#include "Color.hpp"
#include "DxLib.h"
//�O���[�o���ϐ�
int BLACK;	//��
int WHITE;	//��
int RED;	//��
int BLUE;	//��
int GREEN;	//��
int PINK;	//��

void ColorInit(void){
	BLACK = GetColor(0,0,0);
	WHITE = GetColor(255,255,255);
	RED	  = GetColor(255,0,0);
	GREEN = GetColor(0,255,0);
	BLUE = GetColor(0,0,255);
	PINK = GetColor(255,0,255);
	return;
}