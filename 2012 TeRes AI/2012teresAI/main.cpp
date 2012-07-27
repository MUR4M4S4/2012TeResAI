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
	int end=0;

	while(ProcessMessage()!=-1){
		switch(gamemode){
		case OPENING:
			intro();
			gamemode=SETTING;
			break;
		case SETTING:
			make_Stage(STAGE);//�}�b�v�\��
			init_Tagger(&tagger,STAGE);//�S�̏�����

			//for(int i=0;i<AI_NUM;i++){//AI�̏����� //henteko : ai�����ׂ�init_Ai�ɓn��
			init_Ai(ai,STAGE);
			//}

			round++;
			gamemode=RUNNING;

			break;
		case RUNNING:
			
			if(tagger.step==0){
				tagger.act=next_Tagger(tagger,STAGE);
			}
			for(int i=0;i<AI_NUM;i++){
				if(ai[i].step==0){
					setview_Ai(&ai[i],STAGE);
					//ai[i].act=next_Ai(ai[i].view); //henteko : ����moveFunc()���g�����߃R�����g�A�E�g
					ai[i].act = ai[i].moveFunc(ai[i].view);
				}
			}

			update_Tagger(&tagger,STAGE);
			for(int i=0;i<AI_NUM;i++){
				update_Ai(&ai[i],STAGE);
			}
			update_stage(STAGE,ai,tagger);
			
			ClearDrawScreen();
			draw(STAGE,ai,tagger);
			
			if(tagger.step==0){
				for(int i=0;i<AI_NUM;i++){
					if(death_Ai(ai[i],tagger)==1){
						death[i]++;
						const char* str = strcat(ai[i].name , "�����܂�܂���"); //������A��
						DrawString(100,240,str,GetColor(255,0,0));
						WaitTimer(3000);
						if(round>=ROUND_MAX){
							gamemode=ENDING;
						}
						else{
							gamemode=SETTING;
						}
						break;
					}
				}
			}
			if(CheckHitKey(KEY_INPUT_R)==1){
				gamemode=SETTING;
			}
			break;
		case ENDING:
			result(ai,death);
			WaitKey();
			end=1;
			break;
		default:
			break;
		}
		if(end==1 || CheckHitKey(KEY_INPUT_ESCAPE))break;
		ScreenFlip();
	}

	DxLib_End() ;				// �c�w���C�u�����g�p�̏I������

	return 0 ;				// �\�t�g�̏I�� 
}