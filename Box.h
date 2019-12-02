#pragma once


typedef struct{
	double X;
	double Y;
}Pos;
//ブロック列挙体
typedef enum{	
	None,
	Normal,
	Goal,
	Needle,
	Bane,
	Start
}BlockKind_t;
//ステージの当たり判定ボックス構造体
struct MapBox_t{
	Pos leftUp;
	Pos rightDown;
	BlockKind_t blockKind;		//ブロックの種類

	MapBox_t(void){};
	MapBox_t(int x,int y,int width,int height,BlockKind_t blockKind){
		leftUp.X = x;
		leftUp.Y = y;
		rightDown.X = x+width;
		rightDown.Y = y+height;
		MapBox_t::blockKind = blockKind;
	};
};
//当たり判定の構造体
struct HitFlag_t{
	bool left;
	bool right;
	bool up;
	bool down;
	HitFlag_t(){
		left = false;
		right = false;
		up = false;
		down = false;
	};
};