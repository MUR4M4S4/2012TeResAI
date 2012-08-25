/**********************************************************
	AI�̃T���v��
**********************************************************/

#include "Data.h"


/**********************************************************
	���������ɌĂ΂��֐�
**********************************************************/
void aiTestInit(AI_T &myAi)
{
	myAi.Graph = LoadGraph("AI_image\\red.png");
	strcpy_s(myAi.name, "aiTest");
}


/**********************************************************
	AI�̍s����Ԃ��֐�
**********************************************************/
Action aiTest(int view[2*VISIBLE+1][2*VISIBLE+1])//8/25:zero:�ǋL
{
	int r;
	int cx=VISIBLE,cy=VISIBLE;
	int danger=0;
	double direct;
	double  PI=3.141592;
	int tx,ty;

	for(int i=0;i<2*VISIBLE+1;i++){
		for(int j=0;j<2*VISIBLE+1;j++){
			if(view[i][j]==3){
				tx=i;
				ty=j;
				danger=1;
				int dx=cx-i;
				int dy=cy-j;
				if(dx==0){
					if(dy>=0){
						direct=90;
					}else{
						direct=-90;
					}
				}else{
					double t=dy/dx;
					if(dx>0){
						direct=atan(t)/PI*180;
					}
					else{
						direct=atan(t)/PI*180+180;
					}
				}
			}
		}
	}

	if(danger==0){
		int r=GetRand(4);
		switch(r%4){
		case 0:
			if(view[cx][cy-1]!=1)
			return N;
			break;
		case 1:
			if(view[cx+1][cy]!=1)
			return E;
			break;
		case 2:
			if(view[cx][cy+1]!=1)
			return S;
			break;
		case 3:
			if(view[cx-1][cy]!=1)
			return W;
			break;
		}
	}
	else{
		if(direct<-45){
			if(view[cx][cy-1]!=1)
				return N;
			else{
				if(view[cx-1][cy]!=1){
					return W;
				}
				else{
					return E;
				}
			}	
		}
		else if(direct<45){
			if(view[cx-1][cy]!=1)
				return E;
			else{
				if(view[cx][cy-1]!=1){
					return N;
				}
				else{
					return S;
				}
			}
		}
		else if(direct<135){
			if(view[cx][cy+1]!=1)
				return S;
			else{
				if(view[cx+1][cy]!=1){
					return E;
				}
				else{
					return W;
				}
			}
		}
		else if(direct<225){
			if(view[cx-1][cy]!=1)
				return W;
			else{
				if(view[cx][cy+1]!=1){
					return S;
				}
				else{
					return N;
				}
			}
		}
		else{
			if(view[cx][cy-1]!=1)
				return N;
			else{
				if(view[cx-1][cy]!=1){
					return W;
				}
				else{
					return E;
				}
			}
		}
		return STOP;
	}
}
