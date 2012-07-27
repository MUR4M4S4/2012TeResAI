#pragma once

#include "DxLib.h"
#include <string.h>
#include <iostream>
using namespace std;

#define AI_NUM 2
#define ROUND_MAX 100
//�X�e�[�W�̋K��
#define WIDTH 32
#define HEIGHT 24
//1�}�X�̑傫��
#define BOX (640/WIDTH)

//AI�̎��E
#define VISIBLE 3

typedef enum{
	OPENING,
	SETTING,
	RUNNING,
	ENDING,
} Mode;

typedef enum{
	N,
	E,
	S,
	W,
	STOP,
} Action;

typedef struct{
	char name[10];//���O
	int Graph;//AI�̉摜
	Action (*moveFunc)(int view[2*VISIBLE+1][2*VISIBLE+1]);		// �s����Ԃ��֐�
	int x;//���Wx
	int y;//���Wy
	int s_x;//�h�b�g���x���̍��W(���炩�ȓ����j
	int s_y;//�h�b�g���x���̍��W(���炩�ȓ����j
	int step;//�����ړ�������
	Action act;//AI�̍s��
	int life;//
	int view[2*VISIBLE+1][2*VISIBLE+1];//
} AI_T;

typedef struct{
	int Graph;
	int x;
	int y;
	int s_x;
	int s_y;
	int step;
	Action act;
} Tagger;


void intro();
void make_Stage(int Stage[WIDTH][HEIGHT]);
void init_Tagger(Tagger *tagger,int Stage[WIDTH][HEIGHT]);
void init_Ai(AI_T *ai,int Stage[WIDTH][HEIGHT]);
void draw(int stage[WIDTH][HEIGHT],AI_T ai[],Tagger tagger);
Action next_Ai(int view[2*VISIBLE+1][2*VISIBLE+1]);
Action next_Tagger(Tagger tagger,int Stage[WIDTH][HEIGHT]);
void update_Ai(AI_T *ai,int Stage[WIDTH][HEIGHT]);
void update_Tagger(Tagger *tagger,int Stage[WIDTH][HEIGHT]);
void setview_Ai(AI_T *ai,int Stage[WIDTH][HEIGHT]);
int death_Ai(AI_T ai,Tagger tagger);
void result(AI_T ai[],int death[]);
void update_stage(int Stage[WIDTH][HEIGHT],AI_T ai[],Tagger tagger);
void ranking(AI_T ai[],int deth[]);//7/23 tao31 �ǉ�