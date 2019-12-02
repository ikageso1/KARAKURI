//空気クラス
class Air{
private:
	double x;		//x座標
	double y;		//y座標
	double vx;		//x方向の速度
	double vy;		//y方向の速度

	double Fx;		//x方向の力
	double Fy;		//y方向の力
	double m;		//重さ

	double dx;		//x方向の差分
	double dy;		//y方向の差分

	bool initFlag;	//初期化フラグ(tureで初期済み)

public:
	//デフォルトコンストラクタ
	Air(void);
	//コンストラクタ(角度と初速度と重さを指定)
	void AirInit(int deg,double v0,double m);
	
	//計算関数(抵抗係数,反発係数)
	void Calc(double Cd);

	//反発計算
	void reflect(double ex,double ey);
	//壁の計算
	void Kabe(double ex,double distance);

	//x座標のゲッター
	double getx();

	//y座標のゲッター
	double gety();

	//dxのゲッター
	double getdx();
	//dyのゲッター
	double getdy();
	//initFlagのゲッター
	bool getInitFlag();
	//initFlagのセッター
	void setInitFlag(bool flag);

	//画面表示
	void view(void);
};