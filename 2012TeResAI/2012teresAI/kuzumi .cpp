/**********************************************************
	�v�Z��AI
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
#define KZ_TAGGER_STEP_GETA 5 // �]���̕␳
#define KZ_TAGGER_POINT_GETA 10 // �]���̕␳
int KZ_dequeue(stack *st);
Action kuzumi(int view[2*VISIBLE+1][2*VISIBLE+1])
{
	// ������悤�̕ϐ�
	static stack *st = (stack*)malloc(sizeof(stack));	// �����o�Hstack
	static int initFlag = TRUE;		// stack����j�����邩
	int aiX[AI_NUM], aiY[AI_NUM];	// ����ai�̍��W	
	int aiCount = 0;				// ����ai�̐�

	static int map[5][5] = {-1};			// �O�̍s�����̃}�b�v
	int myStep[2*VISIBLE+1][2*VISIBLE+1]; // �������S�̕����f�[�^
	int taggerStep[2*VISIBLE+1][2*VISIBLE+1]; // �I�j���S�̕����f�[�^

	static int crawlCount = 0; 
	/* view�̐��� */
	for(int i=0; i<2*VISIBLE+1; i++)
		for(int j=0; j<2*VISIBLE+1; j++)
			switch(view[i][j]) {
			case 1: // wall
				myStep[i][j] = taggerStep[i][j] = -1;
				break;
			case 2: // ai
				if(i != VISIBLE || j != VISIBLE) { // �����ȊO�Ȃ狏�ꏊ���L�^
					aiX[aiCount] = i;
					aiY[aiCount] = j;
					aiCount++;
				}
				// ���̂܂�0�̏������s��
			case 0: // way
				myStep[i][j] = taggerStep[i][j] = 0;
				break;
			case 3: // tagger
				myStep[i][j] = -1;		// �����͕ǈ�������
				taggerStep[i][j] = 1;	// �I�j�͎����̋��ꏊ
			}
	myStep[VISIBLE][VISIBLE] = 1;		// �����̋��ꏊ������

	/* �����ŁA�t�B�[���h�X�V�̔�����s�� */
	for(int i=1; i<5; i++)
		for(int j=0; j<5; j++)
			if(map[i][j] != myStep[VISIBLE-2+i][VISIBLE-2+j])
				initFlag = TRUE;

	/* Step�̃}�b�s���O */
	for(int i=1; i<KZ_STEPMAX; i++)
		for(int j=0; j<2*VISIBLE+1; j++)
			for(int k=0; k<2*VISIBLE+1; k++) {
				if(myStep[j][k] == i) {
					if(j != 0 && myStep[j-1][k] == 0)
						myStep[j-1][k] = i+1;
					if(j != VISIBLE*2 && myStep[j+1][k] == 0)
						myStep[j+1][k] = i+1;
					if(k != 0 && myStep[j][k-1] == 0)
						myStep[j][k-1] = i+1;
					if(k != VISIBLE*2 && myStep[j][k+1] == 0)
						myStep[j][k+1] = i+1;
				}
				if(taggerStep[j][k] == i) {
					if(j != 0 && taggerStep[j-1][k] == 0)
						taggerStep[j-1][k] = i+1;
					if(j != VISIBLE*2 && taggerStep[j+1][k] == 0)
						taggerStep[j+1][k] = i+1;
					if(k != 0 && taggerStep[j][k-1] == 0)
						taggerStep[j][k-1] = i+1;
					if(k != VISIBLE*2 && taggerStep[j][k+1] == 0)
						taggerStep[j][k+1] = i+1;
				}
			}
	// ���B�s�\�_��ǈ�������
	for(int i=1; i<2*VISIBLE+1; i++)
		for(int j=0; j<2*VISIBLE+1; j++) {
			if(myStep[i][j] == 0)
				myStep[i][j] = -1;
			if(taggerStep[i][j] == 0)
				taggerStep[i][j] = -1;
		}


	if(initFlag) {
		initFlag = FALSE;
		st->count = 0;
	}

	if(st->count > 0) // �X�^�b�N�ɐς܂�Ă����
		return pop(st);	// ���g��Ԃ�

	if(taggerStep[VISIBLE][VISIBLE] > 0) { // �I�j�������āA�������߂܂�ꏊ�ɂ���Ƃ�
		// �����|�C���g�̌���
		int escapeX, escapeY;
		int fastPoint = -30;
		for(int i=1; i<2*VISIBLE+1; i++)
			for(int j=0; j<2*VISIBLE+1; j++) {
				if(myStep[i][j]>0) { // �������s����ꏊ�ɂ���
					/* �]���|�C���g�P
						���̏ꏊ�ɂǂ��炪�������������邩
						�␳�P�A���R�x�|�C���g�i�������ɓ����邩�j�����Z����
						�␳�Q�A�I�j�̕��������ȏォ����ꏊ�͓_�������Z����
					*/
					int stepPoint = taggerStep[i][j] - myStep[i][j];
					int dirPoint = 0;
					if(i != 0 && myStep[i-1][j] == 0)			dirPoint++;
					if(i != VISIBLE*2 && myStep[i+1][j] == 0)	dirPoint++;
					if(j != 0 && myStep[i][j-1] == 0)			dirPoint++;
					if(j != VISIBLE*2 && myStep[i][j+1] == 0)	dirPoint++;
					if(dirPoint > 2)
						dirPoint *= 2;
					stepPoint += dirPoint;
					if(taggerStep[i][j] > KZ_TAGGER_STEP_GETA)
						stepPoint += KZ_TAGGER_POINT_GETA;

					if(stepPoint > fastPoint) {
						fastPoint = stepPoint;
						escapeX = i;
						escapeY = j;
					}
					/* �]���|�C���g�Q
					�]���|�C���g�P�����_�̏ꍇ
					�I�j�̕�������肩����ꏊ��I��
				*/
					if(stepPoint == fastPoint && taggerStep[i][j] > taggerStep[escapeX][escapeY]) {
						escapeX = i;
						escapeY = j;
					}
				}
			}

		// �����|�C���g�̋L��
		for(int i=myStep[escapeX][escapeY]; 1<i; i--) { // �����̋��ꏊ���S�[���ɂȂ�܂�
			if(myStep[escapeX-1][escapeY] == i-1) { // ���̏ꏊ�ɐ�����������Ȃ�
				push(st, E);	// ��������push����
				escapeX--;		// �����|�C���g���P���ɂ��炷
			} else if(myStep[escapeX+1][escapeY] == i-1) { // ���̏ꏊ�ɓ�����������Ȃ�
				push(st, W);	// ��������push����
				escapeX++;		// �����|�C���g���P���ɂ��炷
			} else if(myStep[escapeX][escapeY-1] == i-1) { // ���̏ꏊ�ɖk����������Ȃ�
				push(st, S);	// �������push����
				escapeY--;		// �����|�C���g���P�k�ɂ��炷
			}  else if(myStep[escapeX][escapeY+1] == i-1) { // ���̏ꏊ�ɓ쑤��������Ȃ�
				push(st, N);	// �k������push����
				escapeY++;		// �����|�C���g���P��ɂ��炷
			} else {	// �ςȏ�ԂɊׂ����Ƃ�
				st->count = 0;				// �X�^�b�N�����Z�b�g����
				return STOP;	// �Ƃ肠����������߂�Ƃ���
			}
		}
		Action ret = pop(st);
		int mapX = VISIBLE;
		int mapY = VISIBLE;
		switch(ret) {
		case N:
			mapY--;
			break;
		case S:
			mapY++;
			break;
		case W:
			mapX--;
			break;
		case E:
			mapX++;
		}
		for(int i=0; i<5; i++)
			for(int j=0; j<5; j++) {
				map[i][j] = myStep[mapX-2+i][mapY-2+j] == -1? -1: 0;
			}
		return ret;	// ���ʂ�pop���ĕԂ�
	}
	else { // �ЂƂ܂����S�ȂƂ�
		if(++crawlCount == 2) // 2�^�[���ɂP�}�X�������
		{
			crawlCount = 0;
			int targetX, targetY;
			int targetStep = KZ_STEPMAX;

			if(aiCount == 0) return STOP;
			for(int i=0; i<aiCount; i++)
				if(targetStep > myStep[aiX[i]][aiY[i]]) {
					targetX = aiX[i];
					targetY = aiY[i];
					targetStep = myStep[aiX[i]][aiY[i]];					
				}
			// �����������̌���
			for(int i=targetStep; 1<i; i--) { // �����̋��ꏊ���S�[���ɂȂ�܂�
				if(myStep[targetX-1][targetY] == i-1) { // ���̏ꏊ�ɐ�����������Ȃ�
					push(st, E);	// ��������push����
					targetX--;		// �����|�C���g���P���ɂ��炷
				} else if(myStep[targetX+1][targetY] == i-1) { // ���̏ꏊ�ɓ�����������Ȃ�
					push(st, W);	// ��������push����
					targetX++;		// �����|�C���g���P���ɂ��炷
				} else if(myStep[targetX][targetY-1] == i-1) { // ���̏ꏊ�ɖk����������Ȃ�
					push(st, S);	// �������push����
					targetY--;		// �����|�C���g���P�k�ɂ��炷
				}  else if(myStep[targetX][targetY+1] == i-1) { // ���̏ꏊ�ɓ쑤��������Ȃ�
					push(st, N);	// �k������push����
					targetY++;		// �����|�C���g���P��ɂ��炷
				} else {	// �ςȏ�ԂɊׂ����Ƃ�
					st->count = 0;				// �X�^�b�N�����Z�b�g����
					return STOP;	// �Ƃ肠����������߂�Ƃ���
				}
			}
			Action ret = pop(st);
			st->count = 0;	// ���g�͎̂Ă�
			int mapX = VISIBLE;
			int mapY = VISIBLE;
			switch(ret) {
			case N:
				mapY--;
				break;
			case S:
				mapY++;
				break;
			case W:
				mapX--;
				break;
			case E:
				mapX++;
			}
			for(int i=0; i<5; i++)	// map�͕ۑ�����
				for(int j=0; j<5; j++)
					map[i][j] = myStep[mapX-2+i][mapY-2+j] == -1? -1: 0;
			return ret;
		}
	}
	return STOP;
}