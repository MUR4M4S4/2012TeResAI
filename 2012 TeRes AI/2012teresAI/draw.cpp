/*�S�I�u�W�F�N�g��`�悷��֐��ł��B*/

#include "Data.h"

	

void draw(int stage[WIDTH][HEIGHT],AI_T ai[AI_NUM],Tagger tagger){


	//����stage�ɂ��������ă}�b�v�̕`��
	int stageGraph = LoadGraph("Stage_image\\kabe0.png"); //�ǂ̉摜�ǂݍ���
	for(int i=0;i<WIDTH;i++){
		for(int j=0;j<HEIGHT;j++){
			if(i==WIDTH/2 || j==HEIGHT/2){//7/27 zero: �\����L��`���Ă�����Ƃ�������
				DrawBox(20*i,20*j,20*(i+1),20*(j+1),GetColor(100,100,250),0);
			}
			if(stage[i][j]==1){//�ǂ����ɔ��������`�Ƃ��Ă��܂��B//�y�̕ǂɂ��܂����B
//				DrawBox(20*i,20*j,20*(i+1),20*(j+1),GetColor(255,255,255),1);//�l�p�̕`��
				DrawRotaGraph((20*i)+10,(20*j)+10,1.0,0.0,stageGraph,FALSE,FALSE);//�ǂݍ��񂾕ǉ摜�\��
			}
		}
	}
	//AI�̕`��
	for(int i=0;i<AI_NUM;i++){
		DrawRotaGraph(ai[i].s_x,ai[i].s_y,1,0,ai[i].Graph,TRUE,FALSE);//�ǂݍ��񂾉摜�\��
		//DrawCircle(ai[i].s_x,ai[i].s_y,5,GetColor(255,0,0),1);//�_�\��
		DrawBox(BOX*ai[i].x,BOX*ai[i].y,BOX*(ai[i].x+1),BOX*(ai[i].y+1),GetColor(255,0,0),0);
		DrawBox(BOX*(ai[i].x-VISIBLE),BOX*(ai[i].y-VISIBLE),BOX*(ai[i].x+VISIBLE+1),BOX*(ai[i].y+VISIBLE+1),GetColor(255,255,0),0);//AI�̎��E�i�m�F�p�j
	}
	//�S�̕`��
	
	//DrawRotaGraph(tagger.s_x,tagger.s_y,1,0,tagger.Graph,TRUE,FALSE);//�ǂݍ��񂾉摜�\�� //���͐S���o�Ă��ĕ|������R�����g�A�E�g
	DrawCircle(tagger.s_x,tagger.s_y,10,GetColor(0,0,255),1);
	DrawBox(BOX*tagger.x,BOX*tagger.y,BOX*(tagger.x+1),BOX*(tagger.y+1),GetColor(255,0,0),0);
	/*�}�b�v�f�[�^�\��
	for(int i=0;i<WIDTH;i++){
		for(int j=0;j<HEIGHT;j++){
			DrawFormatString(i*20,j*20,GetColor(0,255,0),"%d",stage[i][j]);
		}
	}
	*/
	//�S���蓮���������\��
    char Buf[ 256 ] ;
	GetHitKeyStateAll( Buf ) ;
	if( Buf[ KEY_INPUT_A ] == 1 ) {
		const char* str = strcat(tagger.name , "�S�蓮���[�h"); //������A��
		DrawString( 15, 15, str ,GetColor(255,0,255) );
	}else {
		const char* str = strcat(tagger.name , "�SAI���[�h"); //������A��
		DrawString( 15, 15, str ,GetColor(255,0,255) );
	}
}