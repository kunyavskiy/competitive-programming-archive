#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <queue>
#include <memory.h>
#include <stack>
#define mp make_pair
#define pb push_back                     
#define int64 long long
#define ld long double  
#define setval(a,v) memset(a,v,sizeof(a))
using namespace std;

typedef unsigned char uchar;

uchar from1[100][100][100];
uchar from2[100][100][100];
uchar from3[100][100][100];
int d[100][100][101];
bool a[100][100];
int n,m;
queue<int> q1,q2,q3;

int coordtoint(int a,int b)
{
	return a*m+b;
}

void inttocoord(int b,int &x,int &y)
{
	x=b/m;
	y=b%m;
} 

bool good(int x,int y)
{
	return ((x>=0) && (x<n) && (y>=0) && (y<m));
}


void go(int x,int y,int z){
	int x1,y1,x2,y2,x3,y3;
	inttocoord(x,x1,y1);
	inttocoord(y,x2,y2);
	inttocoord(z,x3,y3);
	for (int i=-1;i<2;i++)
		for (int j=-1;j<2;j++)
		if (abs(i)+abs(j)==1)
		{
			int tx1=x1+i;
  		int ty1=y1+j;
  		if (!good(tx1,ty1))
  			continue;
  		int tx2=x2;
  		int ty2=y2;
  		if ((tx1==tx2) && (ty1==ty2))
  		{
  			tx2+=i;
  			ty2+=j;
			}
			if (!good(tx2,ty2))
				continue;
			int tx3=x3;
			int ty3=y3;
  		if ((tx1==tx3) && (ty1==ty3))
  		{
  			tx3+=i;
  			ty3+=j;
			}
			if (!good(tx3,ty3))
				continue;
			if ((tx2==tx3) && (ty2==ty3))
				continue;
			if (!a[tx1][ty1] || !a[tx2][ty2] || !a[tx3][ty3])
				continue;
			int t1=coordtoint(tx1,ty1);
			int t2=coordtoint(tx2,ty2);
			int t3=coordtoint(tx3,ty3);
			if (d[t1][t2][t3]>d[x][y][z]+1)
			{
				d[t1][t2][t3]=d[x][y][z]+1;
				from1[t1][t2][t3]=x;
				from2[t1][t2][t3]=y;
				from3[t1][t2][t3]=z;
				q1.push(t1);
				q2.push(t2);
				q3.push(t3);
			}
		}
}

void go(int x,int y){
	int x1,y1,x2,y2;
	inttocoord(x,x1,y1);
	inttocoord(y,x2,y2);
	for (int i=-1;i<2;i++)
		for (int j=-1;j<2;j++)
		if (abs(i)+abs(j)==1)
		{
			int tx1=x1+i;
  		int ty1=y1+j;
  		if (!good(tx1,ty1))
  			continue;
  		int tx2=x2;
  		int ty2=y2;
  		if ((tx1==tx2) && (ty1==ty2))
  		{
  			tx2+=i;
  			ty2+=j;
			}
			if (!good(tx2,ty2))
				continue;
  		if (!a[tx1][ty1] || !a[tx2][ty2])
				continue;
			int t1=coordtoint(tx1,ty1);
			int t2=coordtoint(tx2,ty2);
			if (d[t1][t2][0]>d[x][y][0]+1)
			{
				d[t1][t2][0]=d[x][y][0]+1;
				from1[t1][t2][0]=x;
				from2[t1][t2][0]=y;
				q1.push(t1);
				q2.push(t2);
			}
		}
}

void print(int s1,int s2,int s3)
{
	if (from1[s1][s2][s3]==255)
		return;
	print(from1[s1][s2][s3],from2[s1][s2][s3],from3[s1][s2][s3]);
	if (s2==from2[s1][s2][s3] && s3==from3[s1][s2][s3])
		printf("MOVE ");
	else
		printf("PUSH ");
	if (from1[s1][s2][s3]-m==s1)
		printf("UP\n");
	if (from1[s1][s2][s3]+m==s1)
		printf("DOWN\n");
	if (from1[s1][s2][s3]-1==s1)
		printf("LEFT\n");
	if (from1[s1][s2][s3]+1==s1)
		printf("RIGHT\n");			
}

void print(int s1,int s2)
{
	if (from1[s1][s2][0]==255)
		return;
	print(from1[s1][s2][0],from2[s1][s2][0]);
	if (s2==from2[s1][s2][0])
		printf("MOVE ");
	else
		printf("PUSH ");
	if (from1[s1][s2][0]-m==s1)
		printf("UP\n");
	if (from1[s1][s2][0]+m==s1)
		printf("DOWN\n");
	if (from1[s1][s2][0]-1==s1)
		printf("LEFT\n");
	if (from1[s1][s2][0]+1==s1)
		printf("RIGHT\n");			
}


int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
	int s1,s2,s3,e2,e3;
	s2=s3=e2=e3=-1;
	scanf("%d %d",&n,&m);
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
			{
				char c;
				scanf(" %c ",&c);
				if (c=='#')
					a[i][j]=false;
				else
					a[i][j]=true;
				if (c=='M')
					s1=coordtoint(i,j);
				if (c=='B' && s2==-1)
					s2=coordtoint(i,j);
				else if (c=='B' && s2!=-1)
					s3=coordtoint(i,j);
				if (c=='X' && e2==-1)
					e2=coordtoint(i,j);
				else if (c=='X' && e2!=-1)
					e3=coordtoint(i,j);				
			}
	memset(d,1,sizeof(d));
	memset(from1,-1,sizeof(from1));
	const int inf=d[0][0][0];
	if (s3!=-1)
	{
		q1.push(s1);
		q2.push(s2);
		q3.push(s3);
		d[s1][s2][s3]=0;
		for (;!q1.empty();)
		{
			int t1,t2,t3;
			t1=q1.front();
			t2=q2.front();
			t3=q3.front();
			q1.pop();
			q2.pop();
			q3.pop();
			go(t1,t2,t3);
		}		
		int mind=inf;
		for (int i=0;i<n*m;i++)
			if (d[i][e2][e3]<mind)
				mind=d[i][e2][e3];
		for (int i=0;i<n*m;i++)
			if (d[i][e3][e2]<mind)
				mind=d[i][e3][e2];

		if (mind==inf)
			{
				printf("MISSION IMPOSSIBLE\n");
				return 0;
			};
		printf("%d\n",mind);
		for (int i=0;i<n*m;i++)
			if (d[i][e2][e3]==mind)
			{
				print(i,e2,e3);
				return 0;
			}		
		for (int i=0;i<n*m;i++)
			if (d[i][e3][e2]==mind)
			{
				print(i,e3,e2);
				return 0;
			}		
	}
	else
		{		
			q1.push(s1);
			q2.push(s2);
			d[s1][s2][0]=0;
			for (;!q1.empty();)
			{
				int t1,t2;
				t1=q1.front();
				t2=q2.front();
				q1.pop();
				q2.pop();
				go(t1,t2);
			}
			int mind=inf;
			for (int i=0;i<n*m;i++)
				if (d[i][e2][0]<mind)
					mind=d[i][e2][0];
			if (mind==inf)
				{	
					printf("MISSION IMPOSSIBLE\n");
					return 0;
				};
			printf("%d\n",mind);
			for (int i=0;i<n*m;i++)
				if (d[i][e2][0]==mind)
				{
					print(i,e2);
					return 0;
				}		
		}
  return 0;
}