#include "Data.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	ChangeWindowMode(TRUE);
	SetDrawScreen( DX_SCREEN_BACK);
	if(DxLib_Init()==-1)		// �c�w���C�u��������������
	{
		return -1 ;			// �G���[���N�����璼���ɏI��
	}

	//�f�o�b�N�p�ɃR���\�[�����o��������
	AllocConsole();
	freopen("CONOUT$","w",stdout);
	freopen("CONIN$","r",stdin);
	

	Mode gamemode=OPENING;
	AI_T ai[AI_NUM];
	int death[AI_NUM]={0};
	Tagger tagger[TAGGER_NUM];
	int tagger_num = 0;
	int STAGE[WIDTH][HEIGHT]={0};
	int round=0;
	int end=0;
	int StartTime,TimeLimit;

	while(ProcessMessage()!=-1){
		switch(gamemode){
		case OPENING:
			intro();
			gamemode=SETTING;
			break;
		case SETTING:
			make_Stage(STAGE);//�}�b�v�\��
			tagger_num = init_Tagger(tagger,STAGE);//�S�̏����� //tagger_num�͋S�̗v�f�ԍ�

			//for(int i=0;i<AI_NUM;i++){//AI�̏����� //henteko : ai�����ׂ�init_Ai�ɓn��
			init_Ai(ai,STAGE);
			//}

			round++;
			StartTime=GetNowCount();//�Q�[���J�n���̎����ɍ��킹��
			gamemode=RUNNING;

			break;
		case RUNNING:
			TimeLimit=TIME_LIMIT*1000-(GetNowCount()-StartTime);
			if(TimeLimit<0)TimeLimit=0;
			if(tagger[tagger_num].step==0){
				//tagger[tagger_num].act=next_Tagger(tagger[tagger_num],STAGE,ai);
				tagger[tagger_num].act=tagger[tagger_num].moveFunc(tagger[tagger_num].x,tagger[tagger_num].y,STAGE,ai); //AI�ƈꏏ�ŁAmoveFunc�g��
			}
			for(int i=0;i<AI_NUM;i++){
				if(ai[i].step==0){
					setview_Ai(&ai[i],STAGE);
					//ai[i].act=next_Ai(ai[i].view); //henteko : ����moveFunc()���g�����߃R�����g�A�E�g
					ai[i].act = ai[i].moveFunc(ai[i].view);
				}
			}

			update_Tagger(&tagger[tagger_num],STAGE);
			for(int i=0;i<AI_NUM;i++){
				update_Ai(&ai[i],STAGE);
			}
			update_stage(STAGE,ai,tagger[tagger_num]);
			
			ClearDrawScreen();
			draw(STAGE,ai,tagger[tagger_num]);
			DrawFormatString(30,30,GetColor(0,255,255),"ROUND%d",round);
			
			DrawFormatString(500,15,GetColor(0,255,0),"TIME %d",TimeLimit);
			
			if(tagger[tagger_num].step==0){
				for(int i=0;i<AI_NUM;i++){
					if(death_Ai(ai[i],tagger[tagger_num])==1){
						death[i]++;
						DrawBox(0,230,640,260,GetColor(0,0,0),1);
						DrawBox(-1,230,642,260,GetColor(255,0,0),0);
						DrawFormatString(100,240,GetColor(255,0,0),"%s�����܂�܂���",ai[i].name);// 8/3 zero�ǋL:AI�ߊl�̐錾���܂Ƃ߂��B
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
			if(TimeLimit<=0){// 8/3 zero�ǋL:�^�C���A�b�v��ݒ�
				round--;
				DrawString(100,240,"���Ԑ؂�ł�",GetColor(255,0,0));
				WaitTimer(3000);
				if(round>=ROUND_MAX){
					gamemode=ENDING;
				}
				else{
					gamemode=SETTING;
				}
				break;
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