#include "Data.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	ChangeWindowMode(TRUE);
	SetDrawScreen( DX_SCREEN_BACK);
	if(DxLib_Init()==-1)		// �c�w���C�u��������������
	{
		return -1 ;			// �G���[���N�����璼���ɏI��
	}

	Mode gamemode=OPENING;
	AI_T ai[AI_NUM];
	int death[AI_NUM]={0};
	Tagger tagger;
	int STAGE[WIDTH][HEIGHT]={0};
	int round=0;
	int step=0;

	while(ProcessMessage()==0){
		switch(gamemode){
		case OPENING:
			intro();
			gamemode=SETTING;
			break;
		case SETTING:
			
			make_Stage(STAGE);//�}�b�v�\��
			init_Tagger(&tagger,STAGE);//�S�̏�����
			for(int i=0;i<AI_NUM;i++){//AI�̏�����
				init_Ai(&ai[i],STAGE);
			}
			
			round++;
			gamemode=RUNNING;
			break;
		case RUNNING:
			/*
			if(tagger.step==20){
				tagger.act=next_Tagger(tagger);
				tagger.step=0;
			}

			for(int i=0;i<AI_NUM;i++){
				if(ai[i].step==20){
					setview_Ai(&ai[i]);
					ai[i].act=next_Ai(ai[i]);
					ai[i].step=0;
				}
			}

			update_Tagger(&tagger);
			for(int i=0;i<AI_NUM;i++){
				update_Ai(&ai[i]);
			}
			*/

			
			ClearDrawScreen();
			draw(STAGE,ai[],tagger);
			
			
			/*��sh�E�E�ߊl���肵�[��
			for(int i=0;AI_NUM;i++){
				if(Death_Ai(ai[i],tagger)){
					death[i]++;
					if(round>=ROUND_MAX){
						gamemode=ENDING;
					}
					else{
						gamemode=SETTING;
					}
					break;
				}
			}
			*/
			break;
		case ENDING:
			//result();
			break;
		default:
			break;
		}
		if(CheckHitKey(KEY_INPUT_ESCAPE))break;
		ScreenFlip();
	}

	DxLib_End() ;				// �c�w���C�u�����g�p�̏I������

	return 0 ;				// �\�t�g�̏I�� 
}