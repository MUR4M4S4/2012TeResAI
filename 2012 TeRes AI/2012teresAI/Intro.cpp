/*�����������I�[�v�j���O��*/
//21th june�@tao31�ҏW

#include "Data.h"

void intro(){

	int gametitle;
	gametitle = LoadGraph("media\\test.bmp");

	DrawGraph(0,0,gametitle,FALSE);

	ScreenFlip();

	//DrawString(200,240,"2012 Chohu Festival",GetColor(255,255,255),0);
	DrawString(200,270,"ENTRY AI",GetColor(125,255,205),0);

	//test �f��
	DrawString(200,290,"AI_name",GetColor(0,255,205),0);
	DrawCircle(300,300,5,GetColor(255,0,0),1);
	/*//�{���͉��̂ق��ŃG���g���[��\������\��AI_T ai[]
	for(int i= 0; i < AI_NUM ;i++, ai++){
	DrawString(200,240,ai->name,GetColor(0,255,255),0);
	DrawGraph( 300 , 290+i*10 , ai->Graph , FALSE ) ;
	}*/
	
	
	
	WaitKey();

}