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

bool a[100][100];
bool d[100][100];
int n;


bool check(int x,int y,int l){
	if (x+l>n || y+l>n)
		return false;
	bool q=true;
	for (int i=0;i<l;i++)
		{
			q&=d[x+l-1][y+i];
			q&=d[x+i][y+l-1];
		}
	return q;
}
int cnt(int x,int y){
	int res=1;
	for (;check(x,y,res);res++);
	res--;
	return res;
}

int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++){
		char c;
		scanf(" %c ",&c);
		a[i][j]=d[i][j]=(c=='~');
	}
	int res=0;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			if (d[i][j]){
				++res;
				int l=cnt(i,j);
				for (int dx=0;dx<l;dx++)
					for (int dy=0;dy<l;dy++)
						d[i+dx][j+dy]=false;
			}
	cout<<res<<endl;
  return 0;
}