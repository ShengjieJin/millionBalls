#include"BALL.h"
#include <graphics.h>
#include<time.h>
using namespace std;

#define N 1000			//������
#define a 10			//���γ�������
#define R 4			//�뾶



//����ȫ�ֱ���
int width = 1280;
int height = 800;
int blank = 100;
int v = 100;
//int realwidth = 8000;
//int realheight = 8000;
//vector<Ball>spriteList(N);
Ball* spriteList = new Ball[N];

void CreatBall(int x) {    //xΪ��������С�������

	for(int i = 0; i < N ; i++)
	{
		Ball* temp = new Ball();
		//���´���Ϊ��������ɴ��룬���������ڵķ�Χ���վ��ȷֲ��ĸ������������
		random_device rd;
		mt19937 mt(rd());
		uniform_int_distribution<> dis(0, 3);
		uniform_int_distribution<> dis1(R, width - blank - R);  //С�����ɷ�Χ
		uniform_int_distribution<> dis2(R, height - R);  //С�����ɷ�Χ
		uniform_int_distribution<> dis_real1(-v, v);  //С���ٶȷ�Χ
		uniform_int_distribution<> dis_real2(-v, 0);//С���ٶȷ�Χ
		uniform_int_distribution<> dis_real3(0, v);//С���ٶȷ�Χ
		switch (dis(mt))//���ɷ���
		{
		case 0: //��
			temp->setpos(dis(mt), 0);
			temp->setvelocity(Magnitude(dis_real1(mt), dis_real3(mt)));
			break;
		case 1: //��
			temp->setvelocity(Magnitude(dis_real1(mt), dis_real2(mt)));
			break;
		case 2: //��
			temp->setvelocity(Magnitude(dis_real3(mt), dis_real1(mt)));
			break;
		case 3: //��
			temp->setvelocity(Magnitude(dis_real2(mt), dis_real1(mt)));
			break;
		default:
			break;
		}
		temp->setpos(dis1(mt), dis2(mt));
		temp->setradius(R);
		//temp->setmaxspeed(100);
		//spriteList.push_back(*temp);
		spriteList[i] = *temp;
	};

}

int main()
{
	initgraph(width, height, INIT_RENDERMANUAL);
	setcaption("millionBalls");
	setbkcolor(WHITE);
	setfillcolor(BLACK);
	srand(time(NULL));						//���������
	CreatBall(N);
	int n = 0;
	int c = 0;
	double t = fclock();
	for (; is_run(); delay_fps(60)) {
		if (kbhit()) {
			if (getch() == 27)
				break;
		}
		if (fclock() - t > 0.2) {
			t = fclock();
			if (n < N && (n + a) <= N) n+=a;
		}
		for (int i = 0; i != n; ++i) {
			spriteList[i].action(t - fclock(), width - blank, height, spriteList, i, c);
			cleardevice();
		}
		
		for (int i = 0; i != n; ++i)
		{
			fillellipse(spriteList[i].pos.posx, spriteList[i].pos.posy, spriteList[i].r, spriteList[i].r);
			line(width - blank - R, 0, width - blank - R, height);
			xyprintf(width - blank, 0, "FPS:%.3f", getfps());
			xyprintf(width - blank, 20, "С������%d", n);
			xyprintf(width - blank, 40, "��ײ���Σ�");
			xyprintf(width - blank, 60, "%d", c);
		}
	}

	delete[] spriteList;
	closegraph();
	return 0;
}