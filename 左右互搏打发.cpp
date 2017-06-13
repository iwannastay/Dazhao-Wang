﻿#include <iostream>
#include <vector>

#define GOUBI 50

using namespace std;



class Ellipse
{
public:
	int r;
	int x;
	int y;
	int z;
	//Ellipse* last;
	//Ellipse* next;
	Ellipse(){}
	Ellipse(int _x, int _y, int _z, int _r) :x(_x), y(_y), z(_z), r(_r)
	{
	}
};

vector<Ellipse> *plist;
vector<Ellipse> mlist(30);
vector<Ellipse> blist;
int blocks[3][2];

bool Inside(Ellipse e)
{
	if (abs(e.x) + e.r > GOUBI)
		return false;
	if (abs(e.y) + e.r > GOUBI)
		return false;
	if (abs(e.z) + e.r > GOUBI)
		return false;
	return true;
}

bool Overlapped(Ellipse e, int no)
{
	int dx, dy, dz, ds;
	for (int i = 0; i < no; i++)
	{
		dx = (plist->at(i).x - e.x)*(plist->at(i).x - e.x);
		dy = (plist->at(i).y - e.y)*(plist->at(i).y - e.y);
		dz = (plist->at(i).z - e.z)*(plist->at(i).z - e.z);
		ds = (plist->at(i).r + e.r)*(plist->at(i).r + e.r);
		if (dx + dy + dz < ds)
			return false;
	}

	for (int i = 0; i < blist.size(); i++)
	{
		dx = (blist.at(i).x - e.x)*(blist.at(i).x - e.x);
		dy = (blist.at(i).y - e.y)*(blist.at(i).y - e.y);
		dz = (blist.at(i).z - e.z)*(blist.at(i).z - e.z);
		ds = (blist.at(i).r + e.r)*(blist.at(i).r + e.r);
		if (dx + dy +dz < ds)
			return false;
	}
	return true;
}

void Find(Ellipse &balloon, int no)
{


	int tmp_x1 = 0, tmp_y1 = 0, tmp_z1 = 0;//最终结果
	int max_r1 = 0;
	for (int x = -GOUBI; x < GOUBI; x++)
	{
		balloon.x = x;
		int tmp_x2 = 0, tmp_y2 = 0, tmp_z2 = 0;//当前面最佳
		int max_r2 = 0; int offset = sqrt(GOUBI*GOUBI - x*x);
		for (int y = -GOUBI; y < GOUBI;)
		{
			balloon.y = y;
			int tmp_x3 = 0, tmp_y3 = 0, tmp_z3 = 0;//当前列最佳
			int max_r3 = 0; int offset = sqrt(GOUBI*GOUBI - y*y);
			for (int z = -GOUBI; z < GOUBI;)
			{
				balloon.z = z;
				balloon.r = 0;
				while (Inside(balloon) && Overlapped(balloon, no))
				{
					balloon.r++;
				}
				balloon.r--;
				if (balloon.r >= max_r3)
				{
					max_r3 = balloon.r;
					tmp_x3 = balloon.x;
					tmp_y3 = balloon.y;
					tmp_z3 = balloon.z;
				}
				/*if (abs(z) == offset&&no > 0)
					z += 2 * offset + 1;
				else */z++;
			}
			if (max_r3 >= max_r2)
			{
				max_r2 = max_r3;
				tmp_x2 = tmp_x3;
				tmp_y2 = tmp_y3;
				tmp_z2 = tmp_z3;
			}
			/*if (abs(y) == offset&&no > 0)
				y += 2 * offset + 1;
			else */y++;
		}
		if (max_r2 >= max_r1)
		{
			max_r1 = max_r2;
			tmp_x1 = tmp_x2;
			tmp_y1 = tmp_y2;
			tmp_z1 = tmp_z2;
		}
	}
	balloon.x = tmp_x1;
	balloon.y = tmp_y1;
	balloon.z = tmp_z1;
	balloon.r = max_r1;
}

void Draw(int m)
{
	Ellipse asd(0, 0, 0, 0);
	vector<Ellipse> list(m);
	list.reserve(10);
	plist = &list;
	for (int i = 0; i < m; i++)
		Find(list.at(i), i);
	mlist.swap(list);
}



int main()
{
	int m,n;
	printf("Please input the number of balloons: \n");
	scanf_s("%d", &m);
	printf("Please input the number of points: \n");
	scanf_s("%d", &n);
	printf("Well, some random blocks have been created!\nPlease wait...\n");
	for (int i = 0; i < n; i++)
	{
		int x = rand() % GOUBI * 2 - GOUBI;
		int y = rand() % GOUBI * 2 - GOUBI;
		int z = rand() % GOUBI * 2 - GOUBI;
		Ellipse qwe(x, y, z, 0);
		blist.push_back(qwe);
	}
	//vector<Ellipse>().swap(blist);

	Draw(m);
	for (int i = 0; i < blist.size(); i++)
		cout << "第" << i + 1 << "个障碍：(x,y,z)= (" << (float)blist.at(i).x / GOUBI << "," << (float)blist.at(i).y / GOUBI << "," << (float)blist.at(i).z / GOUBI << ")" << "  R=" << (float)blist.at(i).r / GOUBI << endl;

	for (int i = 0; i < m;i++)
		cout << "第" << i + 1 << "个点：(x,y,z)= (" << (float)mlist.at(i).x / GOUBI << "," << (float)mlist.at(i).y / GOUBI << "," << (float)mlist.at(i).z / GOUBI << ")" << "  R=" << (float)mlist.at(i).r / GOUBI << endl;
	return 0;
}


//#include<cstdlib>
//#include<cstdio>
//#include<cmath>
//using namespace std;
//
//typedef struct Ball
//{
//	double x;
//	double y;
//	double r;
//}ball;
//
//typedef struct ballList
//{
//	struct ballList * next;
//	Ball ball;
//}BallList;
//
//void insert(Ball ball);
//double distance(Ball b1, Ball b2);
//int judge(Ball b);
//void putBall();
//void putPoint(double x, double y);
//double abs_(double num);
//
//BallList *head = NULL;
//double step = 0.01;
//int num = 0;
//double sumr = 0;
//
//int main(){
//	//FILE *stream;
//	//freopen_s("test.txt", "w", stdout);
//	int n, pointNum, i;
//	printf_s("The number of balloon(s): ");
//	scanf_s("%d", &n);
//	printf_s("The number of point(s)");
//	scanf_s("%d", &pointNum);
//	for (i = 0; i < pointNum; i++){
//		printf_s("The %d th point's position(x y)：", i + 1);
//		double x, y;
//		scanf_s("%lf %lf", &x, &y);
//		putPoint(x, y);
//	}
//	printf_s("\nBalloon No\t x-coordinate\t y-coordinate\t radius\t r^2 sum\n");
//	for (i = 0; i < n; i++){
//		putBall();
//	}
//	printf_s("\nr^2sum:\t %lf\n", sumr);
//	return 0;
//}
//
//void putPoint(double x, double y){
//	Ball ball = { x, y, 0 };
//	insert(ball);
//}
//
//void insert(Ball ball){
//	ballList * newBall = (ballList *)malloc(sizeof(ballList));
//	newBall->ball = ball;
//	newBall->next = head;
//	head = newBall;
//}
//
//void putBall()
//{
//	Ball ball = { -1 + step, -1 + step, 0 };
//	Ball maxBall = ball;
//	int i, j;
//	for (i = 0; ball.x < 1; ++i){
//		ball.x += step;
//		ball.y = -1 + step;
//		for (j = 0; ball.y < 1; ++j){
//			ball.y += step;
//			ball.r = 0;
//			double rstep = 0.1;
//			while (rstep > 0.00001){
//				if (ball.r > maxBall.r){
//					maxBall = ball;
//				}
//				ball.r += rstep;
//				if (!judge(ball))
//				{
//					ball.r -= rstep;
//					rstep /= 10;
//				}
//			}
//		}
//	}
//	if (judge(maxBall)){
//		insert(maxBall);
//		num++;
//		sumr += maxBall.r * maxBall.r;
//		printf("%d\t %.3lf\t %.3lf\t %.3lf\t %lf \n", num, maxBall.x, maxBall.y, maxBall.r, sumr);
//	}
//}
//
//int judge(Ball b)
//{
//	if ((abs_(b.x) + b.r) > 1 || (abs_(b.y) + b.r) > 1)
//	{
//		return false;
//	}
//	ballList *tmp = head;
//	while (tmp)
//	{
//		Ball ball = tmp->ball;
//		if (distance(b, ball) < b.r + ball.r)
//		{
//			return false;
//		}
//		tmp = tmp->next;
//	}
//	return true;
//}
//
//double abs_(double num)
//{
//	if (num > 0)
//		return num;
//	return 0 - num;
//}
//
//double distance(Ball b1, Ball b2)
//{
//	double x1 = b1.x;
//	double y1 = b1.y;
//	double x2 = b2.x;
//	double y2 = b2.y;
//	return pow((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2), 0.5);
//}
//
