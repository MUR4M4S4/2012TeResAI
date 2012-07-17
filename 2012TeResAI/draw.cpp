/*�S�I�u�W�F�N�g��`�悷��֐��ł��B*/

#include "Data.h"

void draw(int stage[WIDTH][HEIGHT],AI_T ai[AI_NUM],Tagger tagger){
	//����stage�ɂ��������ă}�b�v�̕`��
	for(int i=0;i<WIDTH;i++){
		for(int j=0;j<HEIGHT;j++){
			//DrawFormatString(i*20+10,j*20+10,GetColor(255,255,0),"%d",stage[i][j]);
			if(stage[i][j]==1){//�ǂ����ɔ��������`�Ƃ��Ă��܂��B
				DrawBox(20*i,20*j,20*(i+1),20*(j+1),GetColor(255,255,255),1);
			}
		}
	}
	//AI�̕`��
	for(int i=0;i<AI_NUM;i++){
		DrawCircle(ai[i].s_x,ai[i].s_y,5,GetColor(255,0,0),1);
		DrawBox(BOX*ai[i].x,BOX*ai[i].y,BOX*(ai[i].x+1),BOX*(ai[i].y+1),GetColor(255,0,0),0);
		DrawBox(BOX*(ai[i].x-VISIBLE),BOX*(ai[i].y-VISIBLE),BOX*(ai[i].x+VISIBLE+1),BOX*(ai[i].y+VISIBLE+1),GetColor(255,255,0),0);//AI�̎��E�i�m�F�p�j
	}
	//�S�̕`��
	
	DrawCircle(tagger.s_x,tagger.s_y,10,GetColor(0,0,255),1);
	DrawBox(BOX*tagger.x,BOX*tagger.y,BOX*(tagger.x+1),BOX*(tagger.y+1),GetColor(255,0,0),0);
}