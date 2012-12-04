/**********************************************************
	AI�̃T���v��
**********************************************************/

#include "Data.h"


/**********************************************************
	���������ɌĂ΂��֐�
**********************************************************/
void taoaiInit(AI_T &myAi)
{
	myAi.Graph = LoadGraph("AI_image\\blue.png");
	strcpy_s(myAi.name, "taoai");
}


/**********************************************************
	AI�̍s����Ԃ��֐�
**********************************************************/
#define Base 2*VISIBLE+1
Action taoai(int view[2*VISIBLE+1][2*VISIBLE+1])//8/25:zero:�ǋL
{

	//Action act[3];

	bool danger = false;
	int area;
	int tx,ty;

	for(int i = 0;i < Base;i++){
		for(int j =0;j < Base;j++){
			if(view[i][j] == 3){
				danger = true;
				tx = i;
				ty = j;
			}
		}
	}

	if(danger){
		if(tx<VISIBLE){
			if(ty<VISIBLE){
				return S;
			}else{
				return E;
			}
		}else{
			if(ty < VISIBLE){
				return N;
			}else{
				return W;
			}
		}
	}
	return STOP;
}