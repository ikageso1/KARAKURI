#include "Color.hpp"
#include "DxLib.h"
//ƒOƒ[ƒoƒ‹•Ï”
int BLACK;	//•
int WHITE;	//”’
int RED;	//Ô
int BLUE;	//Â
int GREEN;	//—Î
int PINK;	//“

void ColorInit(void){
	BLACK = GetColor(0,0,0);
	WHITE = GetColor(255,255,255);
	RED	  = GetColor(255,0,0);
	GREEN = GetColor(0,255,0);
	BLUE = GetColor(0,0,255);
	PINK = GetColor(255,0,255);
	return;
}