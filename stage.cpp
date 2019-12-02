#pragma once
#include "DxLib.h"
#include "Stage.h"
#include "Unit.h"
#include "Color.hpp"
#include <string.h>
#include <fstream>

extern bool HandaFlag;
extern bool is60HzSwitch;	//フラッシュレートが60Hzである
//無名名前空間
namespace{
	int normalBlockGraphic;		//ブロック
	int goalBlockGraphic;		//ゴール
	int needleBlockGraphic;		//とげ
	int baneBlockGraphic;
}

//デフォルトコンストラクタ
Stage::Stage(void){
	Stage::stageNum = 1;//ステージ数を1で初期化
}

//コンストラクタ
Stage::Stage(int stageNum){
	Stage::stageNum = stageNum;	//ステージナンバー
	Stage::goalFlag = false;	//ゴールフラグ初期化
}

//ステージの作成
int Stage::CreateStage(unsigned int zanki){
	char String[256];
	int retu = 0;
	//ブロック画像の決定
	normalBlockGraphic = LoadGraph("Source/Normal.png");
	goalBlockGraphic = LoadGraph("Source/Goal.png");
	needleBlockGraphic = LoadGraph("Source/toge.png");
	baneBlockGraphic = LoadGraph("Source/Bane.png");

	if(HandaFlag){
		//ブロック画像の決定
		normalBlockGraphic = LoadGraph("Source/Secret/Normal.png");
	}
	ClearDrawScreen();
	SetFontSize(40);
	DrawFormatString(400,400,BLACK,"Stage%d",stageNum);
	DrawFormatString(400,450,BLACK,"残機:%d",zanki);
	ScreenFlip();
	SetFontSize(20);
	WaitTimer(500);
	//マップの読み込み
	ReadMap();

	return 0;
}

//マップの読み込み
int	Stage::ReadMap(){
	std::ifstream mapfile;
	//ファイルを開く
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
	//ファイルエラー処理
	if(!mapfile){
		throw 1;
	}
	
	//マップ読み込み
	for(int y=0;y<MAP_LENGTH;y++){
		for(int x=0;x<MAP_WIDTH;x++){
			int data=0;		//マップデータ変数を宣言
			mapfile >> data;	//データを代入
			if(data!=None){
				MapBox_t newBox;
				newBox.leftUp.X = 0 + MAP_PIXEL * x;			//左上のx座標
				newBox.leftUp.Y = 0 + MAP_PIXEL * y;			//左上のy座標
				newBox.rightDown.X = newBox.leftUp.X + MAP_PIXEL;	//右下のx座標
				newBox.rightDown.Y = newBox.leftUp.Y + MAP_PIXEL;	//右下のy座標
				newBox.blockKind = (BlockKind_t)data;
				mapData.push_back(newBox);
			}
		}
	}
	return 0;
}

//ステージのゲッター
list<MapBox_t> Stage::GetMapData(void){
	return mapData;
}

//ステージ表示
void Stage::show(void){
	list<MapBox_t>::iterator temp = mapData.begin();
	for(unsigned int i=0;i<mapData.size();i++){
		int x = (int)((*temp).leftUp.X);
		int y = (int)((*temp).leftUp.Y);
		switch((*temp).blockKind){
		case Normal:	//ブロック
			DrawGraph(x,y,normalBlockGraphic,FALSE);
			break;
		case Goal:		//ゴール
			DrawGraph(x,y,goalBlockGraphic,FALSE);
			break;
		case Needle:	//とげ
			DrawGraph(x,y,needleBlockGraphic,FALSE);
			break;
		case Bane:
			DrawGraph(x,y,baneBlockGraphic,FALSE);
			break;
		}
		temp++;
	}
}


//当たり判定チェック
bool Stage::CheckHitBox(Unit* player){
	list<MapBox_t> temp = GetMapData();
	list<MapBox_t>::iterator stageBlockPos;		//ステージの障害物ブロックのイテレータ
	list<MapBox_t>::iterator hitBoxPos;		//ユニット自身の当たり判定ブロックのイテレータ
	//当たり判定初期化
	player->hitFlagInit();
	double playerX =player->getX();
	double playerY = player->getY();
	stageBlockPos = temp.begin();	//障害物ブロックの要素を最初にセットする
	for(unsigned int i=0;i<temp.size();i++){
		hitBoxPos = player->getHitBox();	//当たり判定ブロックの要素を最初にセット
		for(unsigned int j=0;j<player->getHitBoxSize();j++){
			//x座標が枠内である
			if( (*stageBlockPos).leftUp.X +3 <=  playerX + (*hitBoxPos).rightDown.X &&
				playerX+ (*hitBoxPos).leftUp.X <= (*stageBlockPos).rightDown.X -3){
				//上が接触
				if(  playerY + (*hitBoxPos).leftUp.Y <= (*stageBlockPos).rightDown.Y &&
					(*stageBlockPos).rightDown.Y <= playerY + (*hitBoxPos).rightDown.Y ){
						//上に行き過ぎた分を差し戻す
						player->setY( (*stageBlockPos).leftUp.Y + (*hitBoxPos).rightDown.Y );
						switch((*stageBlockPos).blockKind){
						case Normal:
							player->setHitFlagUp(true);
							break;	
						case Goal:
							goalFlag = true;	//ゴールフラグを設定する。
							break;
						}
				}
				//下が接触
				if( playerY + (*hitBoxPos).leftUp.Y <= (*stageBlockPos).leftUp.Y  && 
					(*stageBlockPos).leftUp.Y <= playerY + (*hitBoxPos).rightDown.Y ) {
						//下に行き過ぎた分を差し戻す
						player->setY( (*stageBlockPos).leftUp.Y - (*hitBoxPos).rightDown.Y );	
						switch((*stageBlockPos).blockKind){
						case Normal:
							player->setHitFlagDown(true);
							break;
						case Goal:
							Stage::goalFlag = true;
							goalFlag = true;	//ゴールフラグを設定する。
							break;
						case Needle:		//とげ
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
							player->setAliveFlag(false);		//死亡
							break;
						case Bane:
							player->setHitFlagDown(true);
							break;
						}
						
				}
			}
			//y座標が枠内である
			else if((*stageBlockPos).leftUp.Y +1 <= playerY + (*hitBoxPos).rightDown.Y  && 
				playerY + (*hitBoxPos).leftUp.Y  <= (*stageBlockPos).rightDown.Y -1){
				//右が接触
				if( playerX + (*hitBoxPos).leftUp.X <= (*stageBlockPos).leftUp.X &&
					(*stageBlockPos).leftUp.X <= playerX +(*hitBoxPos).rightDown.X ){
						//右に行き過ぎた分を差し戻す
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
				//左が接触
				if(playerX + (*hitBoxPos).leftUp.X <= (*stageBlockPos).rightDown.X &&
					(*stageBlockPos).rightDown.X <= playerX + (*hitBoxPos).rightDown.X ) {
						//左に行き過ぎた分を差し戻す
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