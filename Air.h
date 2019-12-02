//��C�N���X
class Air{
private:
	double x;		//x���W
	double y;		//y���W
	double vx;		//x�����̑��x
	double vy;		//y�����̑��x

	double Fx;		//x�����̗�
	double Fy;		//y�����̗�
	double m;		//�d��

	double dx;		//x�����̍���
	double dy;		//y�����̍���

	bool initFlag;	//�������t���O(ture�ŏ����ς�)

public:
	//�f�t�H���g�R���X�g���N�^
	Air(void);
	//�R���X�g���N�^(�p�x�Ə����x�Əd�����w��)
	void AirInit(int deg,double v0,double m);
	
	//�v�Z�֐�(��R�W��,�����W��)
	void Calc(double Cd);

	//�����v�Z
	void reflect(double ex,double ey);
	//�ǂ̌v�Z
	void Kabe(double ex,double distance);

	//x���W�̃Q�b�^�[
	double getx();

	//y���W�̃Q�b�^�[
	double gety();

	//dx�̃Q�b�^�[
	double getdx();
	//dy�̃Q�b�^�[
	double getdy();
	//initFlag�̃Q�b�^�[
	bool getInitFlag();
	//initFlag�̃Z�b�^�[
	void setInitFlag(bool flag);

	//��ʕ\��
	void view(void);
};