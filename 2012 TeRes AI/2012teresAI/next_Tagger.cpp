/*�����o�ϐ�act�����������ċS�̎��̍s�������߂�֐��ł��B*/
#include "Data.h"


Action next_Tagger(Tagger tagger,int Stage[WIDTH][HEIGHT]){
	int r;
	int cx=tagger.x,cy=tagger.y;

	//�L�[��������Ă��邩�ǂ���
	char Buf[ 256 ] ;
	GetHitKeyStateAll( Buf ) ;

	if( Buf[ KEY_INPUT_A ] == 0 ){//A��������Ă��Ȃ�
		r=GetRand(4);
		switch(r%4){
		case 0:
			if(Stage[cx][cy-1]!=1)
				return N;
			break;
		case 1:
			if(Stage[cx+1][cy]!=1)
				return E;
			break;
		case 2:
			if(Stage[cx][cy+1]!=1)
				return S;
			break;
		case 3:
			if(Stage[cx-1][cy]!=1)
				return W;
			break;
		}
	}
	else{//A��������Ă���
		if( Buf[ KEY_INPUT_N ] == 1 )//N��������Ă���
			return N;
		else if( Buf[ KEY_INPUT_E ] == 1 )//�d���������Ă���
			return E;
		else if( Buf[ KEY_INPUT_S ] == 1 )//S��������Ă���
			return S;
		else if( Buf[ KEY_INPUT_W ] == 1 )//W��������Ă���
			return W;
		else 
			return STOP;//����������Ă��Ȃ�
	}
	return STOP;

}