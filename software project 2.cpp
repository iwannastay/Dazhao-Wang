#include <iostream>
#include <vector>

#define GOUBI 100

using namespace std;



class Ellipse
{
public:
	int r;
	int x;
	int y;
	//Ellipse* last;
	//Ellipse* next;
	Ellipse(){}
	Ellipse(int _x, int _y, int _r) :x(_x), y(_y), r(_r)
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
	return true;
}

bool Overlapped(Ellipse e, int no)
{
	int dx, dy, ds;
	for (int i = 0; i < no; i++)
	{
		dx = (plist->at(i).x - e.x)*(plist->at(i).x - e.x);
		dy = (plist->at(i).y - e.y)*(plist->at(i).y - e.y);
		ds = (plist->at(i).r + e.r)*(plist->at(i).r + e.r);
		if (dx + dy < ds)
			return false;
	}

	for (int i = 0; i < blist.size(); i++)
	{
		dx = (blist.at(i).x - e.x)*(blist.at(i).x - e.x);
		dy = (blist.at(i).y - e.y)*(blist.at(i).y - e.y);
		ds = (blist.at(i).r + e.r)*(blist.at(i).r + e.r);
		if (dx + dy < ds)
			return false;
	}
	return true;
}

void Find(Ellipse &balloon, int no)
{


	int tmp_x1 = 0, tmp_y1 = 0;
	int max_r1 = 0;
	for (int x = -GOUBI; x < GOUBI; x++)
	{
		balloon.x = x;
		int tmp_x2 = 0, tmp_y2 = 0;
		int max_r2 = 0; int offset = sqrt(GOUBI*GOUBI - x*x);
		for (int y = -GOUBI; y < GOUBI;)
		{
			balloon.y = y;
			balloon.r = 0;
			while (Inside(balloon) && Overlapped(balloon, no))
			{
				balloon.r++;
			}
			balloon.r--;
			if (balloon.r >= max_r2)
			{
				max_r2 = balloon.r;
				tmp_y2 = balloon.y;
				tmp_x2 = balloon.x;
			}
			/*if (abs(y) == offset&&no > 0)
				y += 2 * offset + 1;
			else */y++;
		}
		if (max_r2 > max_r1)
		{
			max_r1 = max_r2;
			tmp_x1 = tmp_x2;
			tmp_y1 = tmp_y2;
		}
	}
	balloon.x = tmp_x1;
	balloon.y = tmp_y1;
	balloon.r = max_r1;
}

void Draw(int m)
{
	Ellipse asd(0,0,0);
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
	printf("Well, some random blocks have been created!\n");
	for (int i = 0; i < n; i++)
	{
		int x = 0;
		int y =	0;
		Ellipse qwe(x, y, 0);
		blist.push_back(qwe);
	}
	//vector<Ellipse>().swap(blist);

	Draw(m);
	for (int i = 0; i < blist.size(); i++)
		cout << "第" << i + 1 << "个点：(x,y)= (" << (float)blist.at(i).x / GOUBI << "," << (float)blist.at(i).y / GOUBI << ")" << "  R=" << (float)blist.at(i).r / GOUBI << endl;

	for (int i = 0; i < m;i++)
		cout << "第" << i + 1 << "个点：(x,y)= (" << (float)mlist.at(i).x / GOUBI << "," << (float)mlist.at(i).y / GOUBI << ")" << "  R=" << (float)mlist.at(i).r / GOUBI << endl;
	return 0;
}
