#include "DxLib.h"
#include "Game.h"
#include <string>
#include "Color.hpp"
using namespace std;
//リフレッシュレートが60Hzである(外部変数)
extern bool is60HzSwitch;	
extern bool HandaFlag;
//ゲームのシステム中枢
bool GameSystem(Stage,Unit*);

//
bool SinglePlay(unsigned int zanki){
	Unit player = Unit("Source/Player.png",zanki);	//プレイヤーオブジェクト生成
	if(HandaFlag){
		player.ChangeGraphic("Source/Secret/Player.png");
	}
	for(int i=0;i<STAGE_NUM;i++){
		Stage stage = Stage(i+1);
		stage.CreateStage(player.getZanki());	//ステージ作成
		if( !(GameSystem(stage,&player)) ){
			//ゲームオーバー
			if(player.CheckGameOver()){	
				ClearDrawScreen();
				DrawFormatString(500,500,BLACK,"ゲームオーバー");
				ScreenFlip();
				WaitTimer(500);
				return false;
			}
			i--;
		}
		//プレイヤーのx,y座標を初期化
		player.setX(0.0);
		player.setY(0.0);
		//ジャンプの初期化
		player.janpInit(true);
		player.setAliveFlag(true);
	}
	return true;
}

//
bool MultiPlay(unsigned int zanki){
	Unit player = Unit("Source/player.png",zanki);	//プレイヤーオブジェクト生成
	if(HandaFlag){
		player.ChangeGraphic("Source/Secret/Player.png");
	}
	
	int cursor=-1;	//カーソル
	int keyBuf;		//キー

	SetFontSize(30);	//フォントサイズ調整
	while(true){
		ClearDrawScreen();
		keyBuf = GetJoypadInputState(DX_INPUT_KEY_PAD1);	//キー状態格納
		if(ProcessMessage()==-1){	//エラーでのループ脱出
			throw 100;
			break;
		}
		if(keyBuf & PAD_INPUT_9){	//ESCでのループ脱出
			throw "ESC";
			break;
		}
		if(keyBuf & PAD_INPUT_3 && cursor != -1){	//決定 (1ボタン or Zキー)
			break;
		}
		//選択肢移動
		if(keyBuf & PAD_INPUT_UP && cursor >0 ){		//上
			cursor -= 1;
			WaitTimer(85);
		}
		if(keyBuf & PAD_INPUT_DOWN && cursor <STAGE_NUM){	//下
			cursor += 1;
			WaitTimer(85);
		}
		DrawFormatString(300,50,BLACK,"ステージセレクト"); 
		for(int i=0;i<STAGE_NUM+1;i++){
			if(i==cursor){
				DrawFormatString(300,100+40*i,RED,"ステージ%d",i+1);
			}
			else if(i==STAGE_NUM){
				DrawFormatString(300,100+40*i,PINK,"えでぃっとまっぷ");
			}
			else {
				DrawFormatString(300,100+40*i,BLACK,"ステージ%d",i+1);
			}
		}
		ScreenFlip();	//画面適用
	}

	bool isContinue = true;		//ゲーム続行フラグ（やり直し）
	do{
		if(ProcessMessage()==-1){	//エラーでのループ脱出
			throw 100;
			break;
		}
		if(keyBuf & PAD_INPUT_9){	//ESCでのループ脱出
			throw "ESC";
			break;
		}

		Stage stage = Stage(cursor+1);
		stage.CreateStage(player.getZanki());	//ステージ作成
		if( !(GameSystem(stage,&player)) ){
			//ゲームオーバー
			if(player.CheckGameOver()){	
				ClearDrawScreen();
				DrawFormatString(500,500,BLACK,"ゲームオーバー");
				ScreenFlip();
				WaitTimer(500);
				return false;
			}
		}
		else{
			isContinue = false;
		}
		//プレイヤーのx,y座標を初期化
		player.setX(0.0);
		player.setY(0.0);
		//ジャンプの初期化
		player.janpInit(true);
		player.setAliveFlag(true);
	}while(isContinue);
	return true;
}
//ゲームシステム
bool GameSystem(Stage stage,Unit* player){
	while(true){
		int keyBuf;	//キーの格納変数
		keyBuf = GetJoypadInputState(DX_INPUT_KEY_PAD1);	//キー状態格納
		if(ProcessMessage()==-1){	//エラーでのループ脱出
			throw 100;
			break;
		}
		if(keyBuf & PAD_INPUT_9){	//ESCでのループ脱出
			throw "ESC";
			break;
		}
		//キャラクタの移動
		player->move(keyBuf);
		//画面の消去
		ClearDrawScreen();
		//当たり判定
		stage.CheckHitBox(player);
		//リフレッシュレートの速度調整
		if(is60HzSwitch == true){
			//キャラクタの移動
			player->move(keyBuf);
			//当たり判定
			stage.CheckHitBox(player);
		}
		//画面表示
		player->show();
		//(テスト版)ステージの表示
		stage.show();

		//死亡処理
		if(player->CheckAlive()==false){
			player->decZanki();
			return false;
		}
		//画面適用
		ScreenFlip();
		//ゴール時のループ脱出
		if(stage.getGoalFlag() == true){
			ClearDrawScreen();
			DrawFormatString(500,500,BLACK,"くりあー");
			ScreenFlip();
			WaitTimer(500);
			break;
		}
	}
	return true;
}