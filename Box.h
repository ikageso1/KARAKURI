#pragma once


typedef struct{
	double X;
	double Y;
}Pos;
//�u���b�N�񋓑�
typedef enum{	
	None,
	Normal,
	Goal,
	Needle,
	Bane,
	Start
}BlockKind_t;
//�X�e�[�W�̓����蔻��{�b�N�X�\����
struct MapBox_t{
	Pos leftUp;
	Pos rightDown;
	BlockKind_t blockKind;		//�u���b�N�̎��

	MapBox_t(void){};
	MapBox_t(int x,int y,int width,int height,BlockKind_t blockKind){
		leftUp.X = x;
		leftUp.Y = y;
		rightDown.X = x+width;
		rightDown.Y = y+height;
		MapBox_t::blockKind = blockKind;
	};
};
//�����蔻��̍\����
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