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

int k;
bool poly1[300][300];
int w1,h1;
bool poly2[300][300];
int w2,h2;
int64 ans;

bool check(int x,int y,int k1,int k2){
	for (int i=0;i<k1;i++)
		for (int j=0;j<k2;j++)
			if (x+i>=h2 || y+i>=w2 && poly2[x+i][y+j])
				return false;
	return true;				
}

void cnt (int x,int y){
	int wz1,hz1;
	wz1=max(k-w2+1,0);
	hz1=max(k-h2+1,0);
	if (poly1[x][y])
		ans+=wz1*hz1;
	int wz2,hz2;
	wz2=wz1;
	hz2=k-hz1;
	if (poly1[x][y])
		for (int j=0;j<hz2;j++){
			bool q=true;
			int sx=hz2-j;
			for (int nx=x+1;sx<h2;nx++)
			{
				sx+=k;
				q&=((nx<h1) && (poly1[nx][y]));
			}
			if (q)
				ans+=wz2;
		}
	int wz3=k-wz1;
	int hz3=hz1;
	if (poly1[x][y])
		for (int j=0;j<wz3;j++){
			bool q=true;
			int sx=wz3-j;
			for (int ny=y+1;sx<w2;ny++)
			{
				sx+=k;
				q&=((ny<w1) && (poly1[x][ny]));
			}
			if (q)
				ans+=hz3;
		}
	for (int i=hz1+1;i<k;i++)
		for (int j=wz1+1;j<k;j++)
		{
			if ((h2-(k-i))/k+x>=h1)
				continue;
			if ((w2-(k-j))/k+y>=w1)
				continue;
			if (!poly1[x][y] && !check(0,0,k-i,k-j))
				continue;
			int sx=k-i+1;
			bool q=true;
			for (int nx=x+1;sx<h2;nx++)
			{
				q&=poly1[nx][y] || check(sx,0,k,k-j);
				sx+=k;
			}
			if (!q)
				continue;
			int sy=k-j+1;
			for (int ny=y+1;sy<w2;ny++)
			{		
				q&=poly1[x][ny] || check(0,sy,k-i,k);
				sy+=k;
			}			
			if (!q)
				continue;
			sx=k-i+1;
			for (int nx=x+1;sx<h2;nx++){
				sy=k-j+1;
				for (int ny=y+1;sy<w2;ny++)
				{
					q&=poly1[nx][ny] || check(nx,ny,k,k);
					sy+=k;
				}
				sx+=k;
			}
			if (!q)
				continue;
			ans++;			
		}
	return ;
}


int main()
{
  freopen("poly.in","r",stdin);
  freopen("poly.out","w",stdout);
  scanf("%d",&k);
  scanf("%d %d",&h2,&w2);
  char c;
  for (int i=0;i<h2;i++)
  	for (int j=0;j<w2;j++)
  	{
  		scanf(" %c ",&c);
  		poly2[i][j]=(c=='X');
  	}
  scanf("%d %d",&h1,&w1);
  for (int i=0;i<h1;i++)
  	for (int j=0;j<w1;j++)
  	{
  		scanf(" %c ",&c);
  		poly1[i][j]=(c=='X');
  	}
  for (int i=0;i<h1;i++)
  	for (int j=0;j<w1;j++)
  		cnt(i,j);
  cout<<ans<<endl;
  return 0;
}