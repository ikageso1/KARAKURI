#pragma once
#include "Unit.h"
#include "Stage.h"


bool SinglePlay(unsigned int zanki);	//シングルプレイ作成関数

/*戻り値:trueならプレイヤー1の勝利,falseならプレイヤー2の勝利*/
bool MultiPlay(unsigned int zanki);		//マルチプレイ作成関数