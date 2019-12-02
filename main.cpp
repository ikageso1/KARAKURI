#include "DxLib.h"
#include "Unit.h"
#include "Stage.h"
#include "Game.h"
#include "Color.hpp"
#include <string>
using namespace std;

//プロトタイプ宣言
void Title(void);
int Menu(void);
int Option(unsigned int *zanki);
int reflesh(void);			//リフレッシュレートの設定

//グローバル変数
bool is60HzSwitch;	//フラッシュレートが60Hzである
bool HandaFlag = false;		//隠し要素フラグ
//無名名前空間
namespace{
	struct gamemode{
		//ゲームモード列挙体
		enum enum_t{
			SINGLE,
			MULTI,
			OPTION,
			END
		};
	};

	struct optionmode{
		//オプションでの設定値列挙体
		enum enum_t{
			FULLSCREEN,
			ZANKI,
			SECRET,
			END
		};
	};
}
//メイン関数
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
						 LPSTR lpCmdLine, int nCmdShow )
{	
	unsigned int zanki = 3;			//初期設定の残機数
	SetGraphMode(800,600,16);
	ChangeWindowMode(TRUE);
	SetBackgroundColor(255,255,255) ;		//背景を白に設定
	SetWindowText("KARAKURI");			//タイトル名の設定

	if( DxLib_Init() == -1 )	// ＤＸライブラリ初期化処理
	{
		return -1;
	}

	ColorInit();		//色定数を初期化
	SetDrawScreen( DX_SCREEN_BACK ) ;	// 描画先画面を裏画面にセット
	try{
		while(true){
			reflesh();
			Title();		//タイトル画面

			//ゲームモード選択
			switch(Menu()){
				//はじめから
			case gamemode::SINGLE:
				SinglePlay(zanki);	//ゲーム開始
				break;
				//マルチプレイ
			case gamemode::MULTI:
				MultiPlay(zanki);
				break;
				//おぷしょん
			case gamemode::OPTION:
				Option(&zanki);
				break;
				//しゅうりょう
			case gamemode::END:
				throw "ESC";
				break;
			}
		}
	}
	//ESCでの例外処理
	catch(char *a){
		ClearDrawScreen();
		SetFontSize(20);
		DrawFormatString(500,500,BLACK,"終了します");
		ScreenFlip();
		WaitTimer(500);
	}
	//プロセスメッセージによる例外処理
	catch(int a){
	}
	InitGraph() ;		// 全グラフィックを初期化
	DxLib_End() ;		// ＤＸライブラリ使用の終了処理
	return 0;
}

//タイトル
void Title(void){
	int titleGraphic = LoadGraph("Source/title.bmp");		//タイトル画面のロード

	while(true){
		ClearDrawScreen();
		int keyBuf = GetJoypadInputState(DX_INPUT_KEY_PAD1);	//キー状態格納
		if(ProcessMessage()==-1){	//エラーでのループ脱出
			throw 100;
			break;
		}
		if(keyBuf & PAD_INPUT_9){	//ESCでのループ脱出
			throw "ESC";
			break;
		}
		if(keyBuf & PAD_INPUT_10){		//スペースキーで抜ける
			break;
		}

		DrawGraph(0,0,titleGraphic,FALSE);		//描写
		ScreenFlip();
	}
}

//メニュー
int Menu(void){
	int cursor=0;	//カーソル
	int keyBuf;		//キー
	string mozi[]={"はじめから","ステージセレクト","オプション","終了"};
	const int MODE_NUMBER = 4;


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
		if(keyBuf & PAD_INPUT_3){	//決定 (1ボタン or Zキー)
			break;
		}

		//選択肢移動
		if(keyBuf & PAD_INPUT_UP && cursor > 0){		//上
			cursor -= 1;
			WaitTimer(85);
		}

		if(keyBuf & PAD_INPUT_DOWN && cursor < MODE_NUMBER-1){	//下
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
		DrawFormatString(100,50,BLACK,"○ボタン（Cキー)で決定");
		DrawFormatString(100,100,BLACK,"×ボタン(Xキー)でジャンプ");
		ScreenFlip();	//画面適用
	}
	return cursor;
}

//オプション
int Option(unsigned int *zanki){
	int cursor =0;	//カーソル変数
	int keyBuf;	//キー変数
	/*定数*/	
	const int pixel = 40;		//文字表示定数
	const int xPoint = 300;		//文字表示のx座標
	const int yPoint = 400;		//文字表示のy座標
	while(true){
		ClearDrawScreen();
		keyBuf = GetJoypadInputState(DX_INPUT_KEY_PAD1);	//キー状態を格納
		if(ProcessMessage()==-1){	//エラーでのループ脱出
			throw 100;
			break;
		}
		if(keyBuf & PAD_INPUT_9){	//ESCでのループ脱出
			throw "ESC";
			break;
		}
		if(keyBuf & PAD_INPUT_UP && cursor > optionmode::FULLSCREEN){		//上
			cursor -= 1;
			WaitTimer(85);
		}

		if(keyBuf & PAD_INPUT_DOWN && cursor < optionmode::END){	//下
			cursor += 1;
			WaitTimer(85);
		}

		//画面表示
		if(cursor == optionmode::FULLSCREEN){
			DrawFormatString(xPoint,yPoint+pixel*optionmode::FULLSCREEN,RED,"フルスクリーン⇔ウィンドウモード");
			if(keyBuf & PAD_INPUT_RIGHT){
				ChangeWindowMode(TRUE);
				SetDrawScreen( DX_SCREEN_BACK ) ;	// 描画先画面を裏画面にセット
			}
			if(keyBuf & PAD_INPUT_LEFT){
				ChangeWindowMode(FALSE);
				SetDrawScreen( DX_SCREEN_BACK ) ;
			}
		}
		else DrawFormatString(xPoint,yPoint+pixel*optionmode::FULLSCREEN,BLACK,"フルスクリーン⇔ウィンドウモード");

		if(cursor == optionmode::ZANKI ){
			DrawFormatString(xPoint,yPoint+pixel*optionmode::ZANKI,RED,"残機数:%d",*zanki);
			//残機数の調整
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
		else DrawFormatString(xPoint,yPoint+pixel*optionmode::ZANKI,BLACK,"残機数:%d",*zanki);

		if(cursor == optionmode::SECRET ){
			DrawFormatString(xPoint,yPoint+pixel*optionmode::SECRET,RED,"隠しモード");
			if(keyBuf & PAD_INPUT_3){
				while(true){
					if(ProcessMessage()==-1){	//エラーでのループ脱出
						throw 100;
						break;
					}
					if(keyBuf & PAD_INPUT_9){	//ESCでのループ脱出
						throw "ESC";
						break;
					}
					ClearDrawScreen();
					DrawFormatString(200,200,BLACK,"スペースで抜ける");
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
						DrawFormatString(200,200,BLACK,"設定完了!");
						ScreenFlip();
						WaitTimer(1000);
						break;
					}

				}
			}
		}
		else DrawFormatString(xPoint,yPoint+pixel*optionmode::SECRET,BLACK,"隠しモード");

		if(cursor == optionmode::END){
			DrawFormatString(xPoint,yPoint+pixel*gamemode::END,RED,"終了");
			if(keyBuf & PAD_INPUT_3){
				break;
			}
		}
		else DrawFormatString(xPoint,yPoint+pixel*gamemode::END,BLACK,"終了");
		ScreenFlip();

	}
	return 0;
}

//リフレッシュレート調節
int reflesh(){
	int FrameTime, ScreenFlipCount, StartTime ;

	// ScreenFlip を実行した回数を数えるカウンタを初期化
	ScreenFlipCount = 0 ;

	// 画面が１回更新されるまで待つ
	ScreenFlip() ;

	// 計測開始時刻を保存
	StartTime = GetNowCount() ;

	// 1秒間に実行できる ScreenFlip の回数を計測
	while(true)
	{
		// 画面が１回更新されるまで待つ
		ScreenFlip() ;

		// 計測開始から1秒経過していたらループから抜ける
		if( GetNowCount() - StartTime >= 1000 )
			break ;

		// ScreenFlip を実行した回数をインクリメント
		ScreenFlipCount ++ ;
	}
	//リフレッシュレートが90Hz以下ならば
	if(ScreenFlipCount < 90){
		is60HzSwitch = true;		//おそらく、60Hz
	}
	else{
		is60HzSwitch = false;		//おそらく、120Hz
	}
	// ScreenFlip を実行した回数と計測時間から画面一回更新辺りの時間を算出する
	FrameTime = ScreenFlipCount ;
	//デバック用
	//	DrawFormatString(200,200,BLACK,"%d",FrameTime);
	//	ScreenFlip();
	//	WaitKey();
	return 0;
}