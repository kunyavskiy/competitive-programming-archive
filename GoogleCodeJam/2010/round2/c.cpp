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

bool a[110][110];
bool a1[110][110];



void swap(){
	for (int i=0;i<100;i++)
		for (int j=0;j<100;j++)
			{
				a[i][j]=a1[i][j];
				a1[i][j]=0;
			}
}

bool check(){
	for (int i=0;i<100;i++)
		for (int j=0;j<100;j++)
			if (a[i][j])
				return true;
	return false;
}

void iterate(){
	for (int i=0;i<100;i++)
		for (int j=0;j<100;j++){
			if (!a[i][j])
				a1[i][j]=(i>0 && j>0 && a[i-1][j] && a[i][j-1]);
			else 
				a1[i][j]=((i>0 && a[i-1][j]) || (j>0 && a[i][j-1]));					
		}
	swap();		
}

void solve(){
	setval(a,0);
	int r;
	cin>>r;
	for (int i=0;i<r;i++){
		int x1,x2,y1,y2;
		cin>>x1>>y1>>x2>>y2;
		--x1;--x2;--y1;--y2;
		for (int i=x1;i<=x2;i++)
			for (int j=y1;j<=y2;j++)
				a[i][j]=1;
	}
	
	for (int i=0;;i++){
		if (!check())
			{
				printf("%d\n",i);
				return;
			}
		iterate();
	}
}


int main()
{
 
  int t;
  cin>>t;
  for (int i=1;i<=t;i++){
  	printf("Case #%d: ",i);
  	solve();
  }
  	
  
  return 0;
}