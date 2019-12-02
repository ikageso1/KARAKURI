#include "DxLib.h"
#include "Unit.h"
#include <string>
#include "Color.hpp"
using namespace std;

//リフレッシュレートが60Hzである(外部変数)
extern bool is60HzSwitch;	

//コンストラクタ
Unit::Unit(TCHAR* graph,unsigned int zanki){
	Air air = Air();
	//画像のロード
	Unit::graphic = LoadGraph(graph);
	//生存フラグを立てる
	aliveFlag = true;
	//残機の初期化
	Unit::unitZanki = zanki;
	//x座標とy座標0で初期化
	Unit::pos.X = 0;
	Unit::pos.Y = 0;
	//加速度を0で初期化
	Unit::a.X = 0;
	Unit::a.Y = 0;
	//ジャンプフラグ初期化
	Unit::janpFlag = false;
	//あたり判定フラグ初期化
	Unit::hitFlag.down = false;
	Unit::hitFlag.up = false;
	Unit::hitFlag.left = false;
	Unit::hitFlag.right = false;
	//当たり判定の初期化
	SetHitBox();
}

//画像変更
void Unit::ChangeGraphic(TCHAR* graph){
	//画像のロード
	Unit::graphic = LoadGraph(graph);
}

//画面表示
void Unit::show(void){
	DrawGraph((int)(pos.X),(int)(pos.Y),graphic,TRUE);
	//デバッグ用
	//DrawFormatString(100,50,BLACK,"%d:%d:%d:%d",hitFlag.up,hitFlag.down,hitFlag.right,hitFlag.left);
}

//移動
void Unit::move(int Key){
	if(hitFlag.down == false){				//下方向非接地
		if(Unit::janpFlag==true){			//ジャンプ中なら
			Unit::janp(30);				//90度ジャンプ処理
		}
		else{									//ジャンプ中でない
			if(air.getInitFlag() ==false){		//初期化されてない
				janpInit(true);
			}
			else{								//ジャンプ中である
				air.Calc(0.0);						//重力計算
				Unit::pos.X += air.getdx();
				Unit::pos.Y -= air.getdy();
				if(::is60HzSwitch == true){			//60Hzならば動作を4倍速
					air.Calc(0.0);					//計算
					Unit::pos.X += air.getdx();
					Unit::pos.Y -= air.getdy();
					air.Calc(0.0);					//計算
					Unit::pos.X += air.getdx();
					Unit::pos.Y -= air.getdy();
				}
			}
		}
	}
	else{									//下方向接地
		//地面についたときのジャンプフラグ初期化処理
		Unit::janpFlag = false;				//ジャンプフラグを戻す
		air.AirInit(90,0.0,10.0);			//重力(改)の初期化
		Unit::air.setInitFlag(false);		//重力制御クラスを未初期化に戻す
		
		if(hitFlag.right==false){			//右方向非接地
			if(Key & PAD_INPUT_RIGHT){		//右移動
				Unit::pos.X += 0.5;
				if(is60HzSwitch == true){	//60Hzならば動作を4倍速
					Unit::pos.X +=1.0;
				}
			}
		}
		if(hitFlag.left == false){			//左方向非接地
			if(Key & PAD_INPUT_LEFT){		//左移動
				Unit::pos.X-= 0.5;
				if(is60HzSwitch == true){	//60Hzならば動作を4倍速
					Unit::pos.X -=1.0;
				}
			}
		}
		if(hitFlag.up == false){			//上方向非接地
			if(Key & PAD_INPUT_2){			//×ボタン(xキー)が押された場合
				Unit::janpFlag = true;		//ジャンプフラグを立てる
				if(Key & PAD_INPUT_RIGHT){
					janp(45);
				}
				else if(Key & PAD_INPUT_LEFT){
					janp(135);
				}
				else{
					janp(90);
				}
			}
		}
	}

	return;
}

//あたり判定入力
void Unit::SetHitBox(void){
	MapBox_t temp = MapBox_t(0,0,50,50,Goal);
	Unit::hitBox.push_back(temp);
}

//ジャンプ
void Unit::janp(int deg){
	//未初期化ならば
	if(Unit::air.getInitFlag() == false){

		air.AirInit(deg,50.0,0.5);			//初期化関数
		air.Calc(0.0);						//空気抵抗なしで計算
		Unit::pos.X += air.getdx();
		Unit::pos.Y -= air.getdy();
		air.Calc(0.0);
		Unit::pos.X += air.getdx();
		Unit::pos.Y -= air.getdy();

	}	
	else{									//初期化済み
		//計算
		if(hitFlag.down == true){				//地面についたならば
				Unit::janpFlag = false;				//ジャンプフラグを戻す
				Unit::air.setInitFlag(false);		//未初期化に戻す
		}
		else{							//地面にうまってないお
			air.Calc(0.0);				//計算
			Unit::pos.X += air.getdx();
			Unit::pos.Y -= air.getdy();
			air.Calc(0.0);				//計算
			Unit::pos.X += air.getdx();
			Unit::pos.Y -= air.getdy();
			if(::is60HzSwitch == true){	//60Hzならば動作を3倍速
				air.Calc(0.0);				//計算
				Unit::pos.X += air.getdx();
				Unit::pos.Y -= air.getdy();
				air.Calc(0.0);				//計算
				Unit::pos.X += air.getdx();
				Unit::pos.Y -= air.getdy();
			}
		}
	}	


}

//ジャンプ初期化関数
void Unit::janpInit(bool flag){
	air.AirInit(90,0.0,10.0);		//重力の初期化
	air.setInitFlag(flag);			//初期化フラグを立てる	
}

void Unit::setAliveFlag(bool flag){
	aliveFlag = flag;
}
//生存チェック関数
bool Unit::CheckAlive(){
	//座標が800以上（下方向）を超えていたら
	if(pos.Y > 800){
		aliveFlag = false;
	}
	return aliveFlag;
}

//残機デクリメント
void Unit::decZanki(){
	unitZanki--;
}
//ゲームオーバーチェック関数
bool Unit::CheckGameOver(){
	if(unitZanki < 0){
		return true; 
	}
	else{
		return false;
	}
}

unsigned int Unit::getZanki(){
	return unitZanki;
}
//デバック用air関数テスト
void Unit::viewAir(){
	air.view();
	DrawFormatString(400,180,BLACK,"playerX %.3f",pos.X);
}

//当たり判定初期化
void Unit::hitFlagInit(){
	Unit::hitFlag.down = false;
	Unit::hitFlag.left = false;
	Unit::hitFlag.right = false;
	Unit::hitFlag.up = false;
}

//当たり判定のゲッター
list<MapBox_t>::iterator Unit::getHitBox(){
	return hitBox.begin();
}

//当たり判定の要素数のゲッター
int Unit::getHitBoxSize(){
	return hitBox.size();
}

//ばねによる反射
void Unit::refrect(){
	air.reflect(-1.0,-1.0);
}

//xのゲッター
double Unit::getX(){
	return pos.X;
}
//yのゲッター
double Unit::getY(){
	return pos.Y;
}
//xのセッター
void Unit::setX(double x){
	pos.X = x;
}
//yのセッター
void Unit::setY(double y){
	pos.Y = y;
}


//右の当たり判定のセッター
void Unit::setHitFlagRight(bool flag){
	hitFlag.right = flag;
}
//左の当たり判定のセッター
void Unit::setHitFlagLeft(bool flag){
	hitFlag.left = flag;
}
//上の当たり判定のセッター
void Unit::setHitFlagUp(bool flag){
	hitFlag.up = flag;
}
//下の当たり判定のセッター
void Unit::setHitFlagDown(bool flag){
	hitFlag.down = true;
}