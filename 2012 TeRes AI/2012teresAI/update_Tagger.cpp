//�S�̍X�V(AI�Ɠ���)�������S���Q�{�̃y�[�X�ōX�V
#include "Data.h"

void update_Tagger(Tagger *tagger,int Stage[WIDTH][HEIGHT]){

	tagger->step+=4;
	switch(tagger->act){
	case N:
		tagger->s_y-=4;
		break;
	case E:
		tagger->s_x+=4;
		break;
	case S:
		tagger->s_y+=4;
		break;
	case W:
		tagger->s_x-=4;
		break;
	case STOP:
		tagger->act=STOP; //	toshi : AI�Ɏ~�܂�Ƃ����I�������Ȃ������̂Œǉ�
	default:
		break;
	}
	tagger->x=tagger->s_x/BOX;
	tagger->y=tagger->s_y/BOX;
	
	if(Stage[tagger->x][tagger->y]==1){
		switch(tagger->act){//7/27 zero:�Փˌ�̍��W��i�s�����Ō��肷��悤�ɏC��
		case N:
			tagger->y++;
			break;
		case E:
			tagger->x--;
			break;
		case S:
			tagger->y--;
			break;
		case W:
			tagger->x++;
			break;
		default:
			break;
		}
		tagger->act=STOP;
		tagger->s_x=(tagger->x+0.5)*BOX;
		tagger->s_y=(tagger->y+0.5)*BOX;
	}

	if(tagger->step==BOX){
		tagger->act=STOP;
		tagger->step=0;
	}

}