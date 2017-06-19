#include <iostream>
#include <vector>
#include <windows.h>

#define GOUBI 50

using namespace std;

HANDLE thread[2] = { NULL };
CRITICAL_SECTION cs;

DWORD threadID1, threadID2;

class myEllipse
{
public:
	int r;
	int x;
	int y;
	int z;
	//myEllipse* last;
	//myEllipse* next;
	myEllipse(){}
	myEllipse(int _x, int _y, int _z, int _r) :x(_x), y(_y), z(_z), r(_r)
	{
	}
};

vector<myEllipse> *plist;
vector<myEllipse> mlist(30);
vector<myEllipse> blist;
int blocks[3][2];

bool Inside(myEllipse e)
{
	if (abs(e.x) + e.r > GOUBI)
		return false;
	if (abs(e.y) + e.r > GOUBI)
		return false;
	if (abs(e.z) + e.r > GOUBI)
		return false;
	return true;
}

bool Overlapped(myEllipse e, int no)
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

void Find1(myEllipse &balloon, int no)
{
	myEllipse temp;
	int tmp_x1 = 0, tmp_y1 = 0, tmp_z1 = 0;//最终结果
	int max_r1 = 0;
	for (int x = -GOUBI; x <= 0; x++)
	{
		temp.x = x;
		int tmp_x2 = 0, tmp_y2 = 0, tmp_z2 = 0;//当前面最佳
		int max_r2 = 0; int offset = sqrt(GOUBI*GOUBI - x*x);
		for (int y = -GOUBI; y < GOUBI;)
		{
			temp.y = y;
			int tmp_x3 = 0, tmp_y3 = 0, tmp_z3 = 0;//当前列最佳
			int max_r3 = 0; int offset = sqrt(GOUBI*GOUBI - y*y);
			for (int z = -GOUBI; z < GOUBI;)
			{
				temp.z = z;
				temp.r = 0;
				while (Inside(temp) && Overlapped(temp, no))
				{
					temp.r++;
				}
				temp.r--;
				if (temp.r >= max_r3)
				{
					max_r3 = temp.r;
					tmp_x3 = temp.x;
					tmp_y3 = temp.y;
					tmp_z3 = temp.z;
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

	EnterCriticalSection(&cs);
	if (max_r1 > balloon.r)
	{
		balloon.x = tmp_x1;
		balloon.y = tmp_y1;
		balloon.z = tmp_z1;
		balloon.r = max_r1;
	}
	LeaveCriticalSection(&cs);

}

void Find2(myEllipse &balloon, int no)
{

	myEllipse temp;
	int tmp_x1 = 0, tmp_y1 = 0, tmp_z1 = 0;//最终结果
	int max_r1 = 0;
	for (int x = 1; x < GOUBI; x++)
	{
		temp.x = x;
		int tmp_x2 = 0, tmp_y2 = 0, tmp_z2 = 0;//当前面最佳
		int max_r2 = 0; int offset = sqrt(GOUBI*GOUBI - x*x);
		for (int y = -GOUBI; y < GOUBI;)
		{
			temp.y = y;
			int tmp_x3 = 0, tmp_y3 = 0, tmp_z3 = 0;//当前列最佳
			int max_r3 = 0; int offset = sqrt(GOUBI*GOUBI - y*y);
			for (int z = -GOUBI; z < GOUBI;)
			{
				temp.z = z;
				temp.r = 0;
				while (Inside(temp) && Overlapped(temp, no))
				{
					temp.r++;
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
	EnterCriticalSection(&cs);
	if (max_r1 > balloon.r)
	{
		balloon.x = tmp_x1;
		balloon.y = tmp_y1;
		balloon.z = tmp_z1;
		balloon.r = max_r1;
	}
	LeaveCriticalSection(&cs);
}

typedef void(*T) (myEllipse &balloon, int no);
DWORD WINAPI ThreadFunc(LPVOID n)
{
	T a[2] = { Find1, Find2 };
	int i = *(int*)n;
	Find1(plist->at(i),i);
	return 0;
}


void Draw(int m)
{
	vector<myEllipse> list(m);
	list.resize(10);
	plist = &list;
	for (int i = 0; i < m; i++)
	{
		thread[0] = CreateThread(NULL, 0, ThreadFunc, (LPVOID)&i, 0, &threadID1);
		thread[1]= CreateThread(NULL, 0, ThreadFunc, (LPVOID)&i, 0, &threadID2);
		WaitForMultipleObjects(2, thread, TRUE, INFINITE);
	}
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
		int x = rand() % GOUBI * 2 - GOUBI;
		int y = rand() % GOUBI * 2 - GOUBI;
		int z = rand() % GOUBI * 2 - GOUBI;
		myEllipse qwe(x, y, z, 0);
		blist.push_back(qwe);
	}
	for (int i = 0; i < blist.size(); i++)
		cout << "第" << i + 1 << "个障碍：(x,y,z)= (" << (float)blist.at(i).x / GOUBI << "," << (float)blist.at(i).y / GOUBI << "," << (float)blist.at(i).z / GOUBI << ")" << "  R=" << (float)blist.at(i).r / GOUBI << endl;
	
	printf("Please wait...\n");
	InitializeCriticalSection(&cs);
	Draw(m);
	DeleteCriticalSection(&cs);
	

	for (int i = 0; i < m;i++)
		cout << "第" << i + 1 << "个点：(x,y,z)= (" << (float)mlist.at(i).x / GOUBI << "," << (float)mlist.at(i).y / GOUBI << "," << (float)mlist.at(i).z / GOUBI << ")" << "  R=" << (float)mlist.at(i).r / GOUBI << endl;
	return 0;
}




