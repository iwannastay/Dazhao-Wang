#include <iostream>
#include <vector>

#define GOUBI 100

using namespace std;



struct Ellipse
{
	int r;
	int x;
	int y;
	//Ellipse* last;
	//Ellipse* next;
};

vector<Ellipse> *plist;
vector<Ellipse> mlist(30);

bool Inside(Ellipse e)
{
	if (abs(e.x) + e.r > GOUBI)
		return false;
	if (abs(e.y) + e.r > GOUBI)
		return false;
	return true;
}

bool UnOverlapped(Ellipse e, int no)
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
			while (Inside(balloon) && UnOverlapped(balloon, no))
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
		if (max_r2 >= max_r1)
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
	Ellipse asd;
	asd.x=0;
	asd.y=0;
	asd.r=0;
	vector<Ellipse> list(m,asd);
	list.reserve(10);
	plist = &list;
	for (int i = 0; i < m; i++)
		Find(list.at(i), i);
	mlist.swap(list);
}



int main()
{
	int m;
	printf("Please input the number of balloons: \n");
	scanf_s("%d", &m);
	Draw(m);
	for (int i = 0; i < m;i++)
		cout << "µÚ"<<i+1<<"¸öµã£º(x,y)= (" << mlist.at(i).x << "," << mlist.at(i).y << ")" << "  R=" << mlist.at(i).r << endl;
	return 0;
}

