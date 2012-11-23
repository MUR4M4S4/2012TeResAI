/**********************************************************
	AI�̃T���v��
**********************************************************/

#include "Data.h"

/**********************************************************
	���������ɌĂ΂��֐�
**********************************************************/
void kuzumiInit(AI_T &myAi)
{
	myAi.Graph = LoadGraph("AI_image\\ika.png");  //�摜�̐ݒ�
	strcpy_s(myAi.name, "kuzumi");  //������AI�̖��O�ݒ�
}


/**********************************************************
	AI�̍s����Ԃ��֐�
**********************************************************/
#define KZ_STEPMAX 100
Action kuzumi(int view[2*VISIBLE+1][2*VISIBLE+1])
{
	// ������悤�̕ϐ�
	static stack *st = (stack*)malloc(sizeof(stack));
	static int initFlag = 1;
	static int bfview[5][5] = {-1};

	/* ���E��2�l����� */
	int myStep[2*VISIBLE+1][2*VISIBLE+1];
	int taggerStep[2*VISIBLE+1][2*VISIBLE+1];
	for(int i=0; i<2*VISIBLE+1; i++)		// 2�l����tagger�̔c��
		for(int j=0; j<2*VISIBLE+1; j++)	// (way or wall)
		{
			switch(view[i][j])
			{
			case 3:
				myStep[i][j] = 0;
				taggerStep[i][j] = 1;
				break;
			case 0:
			case 2:
				myStep[i][j] = 0;
				taggerStep[i][j] = 0;
				break;
			case 1:
				myStep[i][j] = -1;
				taggerStep[i][j] = -1;
			}
		}
	myStep[VISIBLE][VISIBLE] = 1;			// �����̑������P�Ƃ���

	for(int i=0; i<5; i++)
		for(int j=0; j<5; j++)
			if(bfview[i][j] != myStep[VISIBLE-2+i][VISIBLE-2+j])
			{
				initFlag = 1;
				goto init;
			}

init:
	if(initFlag)
	{
		initFlag = 0;
		st->count = 0;
	}

	if(st->count > 0)
	{
		Action ret = pop(st);
		int nextVx=0, nextVy=0;
		if(ret == N)
			nextVy--;
		else if(ret == S)
			nextVy++;
		else if(ret == E)
			nextVx++;
		else if(ret == W)
			nextVx--;
		for(int i=0; i<5; i++)
			for(int j=0; j<5; j++)
			{
				bfview[i][j] = myStep[VISIBLE-2+i+nextVx][VISIBLE-2+j+nextVy];
				if(bfview[i][j] != -1)
					bfview[i][j] = 0;
			}
		bfview[2][2] = 1;
		return ret;
	}


	/* �}�X���Ƃ̎����ƃI�j�̋��������߂� */
	for(int step=1; step<KZ_STEPMAX; step++)
	{
		for(int i=0; i<2*VISIBLE+1; i++)
			for(int j=0; j<2*VISIBLE+1; j++)
			{
				if(myStep[i][j] == step)
				{
					if(myStep[i+1][j] == 0)
						myStep[i+1][j] = step+1;
					if(myStep[i-1][j] == 0)
						myStep[i-1][j] = step+1;
					if(myStep[i][j-1] == 0)
						myStep[i][j-1] = step+1;
					if(myStep[i][j+1] == 0)
						myStep[i][j+1] = step+1;
				}
				if(taggerStep[i][j] == step)
				{
					if(taggerStep[i+1][j] == 0)
						taggerStep[i+1][j] = step+1;
					if(taggerStep[i-1][j] == 0)
						taggerStep[i-1][j] = step+1;
					if(taggerStep[i][j-1] == 0)
						taggerStep[i][j-1] = step+1;
					if(taggerStep[i][j+1] == 0)
						taggerStep[i][j+1] = step+1;
				}
			}
	}
	for(int i=0; i<2*VISIBLE+1; i++)
		for(int j=0; j<2*VISIBLE+1; j++)
		{
			if(myStep[i][j] == 0)
				myStep[i][j] = -1;
			if(taggerStep[i][j] == 0)
				taggerStep[i][j] = -1;
		}

	if(taggerStep[VISIBLE][VISIBLE] > 0) // ������͈͂Ŏ����Ɏ肪�͂�
	{
		int runX=VISIBLE, runY=VISIBLE; //���ݒn����ɂ���
		int distance=taggerStep[VISIBLE][VISIBLE] - myStep[VISIBLE][VISIBLE];
		for(int i=0; i<2*VISIBLE+1; i++)
			for(int j=0; j<2*VISIBLE+1; j++)
				if(myStep[i][j]>0 && taggerStep[i][j]>0) // �ǂ�������B�ł���ꏊ�ɂ���
				{
					int tmp = taggerStep[i][j] - myStep[i][j];
					if(distance < tmp)
					{
						distance = tmp;
						runX = i; runY = j;
					}
					else if(distance == tmp && (myStep[i][j] > myStep[runX][runY]))
					{
						runX = i; runY = j;
					}
				}

		/* �s����܂ł̓��̂��push���� */
		while(runX != VISIBLE || runY != VISIBLE) // run�̓S�[���n�_�Ȃ̂ŁA�t�����Ă��ǂ�
		{
			if(myStep[runX-1][runY] == myStep[runX][runY]-1) // �����������O
			{
				push(st, E);	// ��������push����
				runX -= 1;		// �S�[�������̏ꏊ��
			}
			else if(myStep[runX+1][runY] == myStep[runX][runY]-1)
			{
				push(st, W);
				runX += 1;
			}
			else if(myStep[runX][runY-1] == myStep[runX][runY]-1)
			{
				push(st, S);
				runY -= 1;
			}
			else if(myStep[runX][runY+1] == myStep[runX][runY]-1)
			{
				push(st, N);
				runY += 1;
			}
			else
			{
				st->count = 0;
				return STOP;
			}
		}
		Action ret = pop(st);
		int nextVx=0, nextVy=0;
		if(ret == N)
			nextVy--;
		else if(ret == S)
			nextVy++;
		else if(ret == E)
			nextVx++;
		else if(ret == W)
			nextVx--;
		for(int i=0; i<5; i++)
			for(int j=0; j<5; j++)
			{
				bfview[i][j] = myStep[VISIBLE-2+i+nextVx][VISIBLE-2+j+nextVy];
				if(bfview[i][j] != -1)
					bfview[i][j] = 0;
			}
		bfview[2][2] = 1;
		return ret;
	}
	else // �߂��ɋS�����Ȃ�
	{
		return (Action)GetRand(3);
	}
	return STOP;
}