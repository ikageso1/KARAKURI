#pragma once
#define MAP_LENGTH 12
#define MAP_WIDTH 16
#define MAP_PIXEL 50
#define STAGE_NUM 10			//ステージ数
#include <list>
#include "Unit.h"
using namespace std;



class Stage{
private:
	bool goalFlag;			//ゴールフラグ
	list<MapBox_t> mapData;	//マップ障害物の当たり判定
	int stageNum;			//ステージ番号
	int ReadMap(void);		//マップ読み込み関数
public:
	Stage(void);						//デフォルトコンストラクタ
	Stage(int);							//int引数つきコンストラクタ
	int CreateStage(unsigned int);				//マップ作成関数
	list<MapBox_t> GetMapData(void);	//マップデータのゲッター
	void show(void);					//マップ表示
	bool CheckHitBox(Unit*);			//当たり判定チェック
	bool getGoalFlag();					//ゴールフラグのゲッター
};