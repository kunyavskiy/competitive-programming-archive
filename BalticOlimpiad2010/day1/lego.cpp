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
#define filename "lego"
using namespace std;

char xc[6][6];
char yc[6][6];

char pole[6][6][6];

char havex[6][6];
char havey[6][6];
int h;

const char types[]=".WBG";


int64 perebor(int x,int y,int z){
	//cerr<<x<<" "<<y<<" "<<z<<endl;
	if (z==h){
		for (int i=0;i<6;i++)
			for (int j=0;j<h;j++)
				if (havex[i][j]!=xc[i][j] || havey[i][j]!=yc[i][j])
					return 0;
		return 1;
	}
	if (x==6)
		return perebor(0,y+1,z);
	if (y==6)
		return perebor(0,0,z+1);
	if (pole[z][x][y]!='.')
		{
			int hxc=havex[x][z];
			int hyc=havey[y][z];
			if (havex[x][z]=='.' && xc[x][z]!=pole[z][x][y])
				return 0;
			if (havey[y][z]=='.' && yc[y][z]!=pole[z][x][y])
				return 0;
			if (havex[x][z]=='.')
				havex[x][z]=pole[z][x][y];
			if (havey[y][z]=='.')
				havey[y][z]=pole[z][x][y];
			int tmp=perebor(x+1,y,z);
			havex[x][z]=hxc;
			havey[y][z]=hyc;
			return tmp;
		}
	int64 ans=0;
	if (x<5 && y<5 && havex[x][z]!='.' && havex[x+1][z]!='.' && havey[y][z]!='.' && havey[y+1][z]!='.')
		{
			if (z==0 || pole[z-1][x][y]!='.' || pole[z-1][x+1][y]!='.' || pole[z-1][x][y+1]!='.' || pole[z-1][x+1][y+1]!='.'){
				pole[z][x][y]=pole[z][x+1][y]=pole[z][x][y+1]=pole[z][x+1][y+1]='W';
				ans+=perebor(x+1,y,z)*3;
			}
			pole[z][x][y]=pole[z][x+1][y]=pole[z][x][y+1]=pole[z][x+1][y+1]='.';
			ans+=perebor(x+1,y,z);
			return ans;
		}
	for (int i=3;i>=0;i--)
		if (i==0 || x<5 && y<5 && pole[z][x+1][y]=='.' && pole[z][x][y+1]=='.' && pole[z][x+1][y+1]=='.')
			if (i==0 || z==0 || pole[z-1][x][y]!='.' || pole[z-1][x+1][y]!='.' || pole[z-1][x][y+1]!='.' || pole[z-1][x+1][y+1]!='.')
			{
				if (i!=0)
					pole[z][x][y]=pole[z][x+1][y]=pole[z][x][y+1]=pole[z][x+1][y+1]=types[i];
				ans+=perebor(x+(i==0),y,z);
				if (i!=0)
					pole[z][x][y]=pole[z][x+1][y]=pole[z][x][y+1]=pole[z][x+1][y+1]='.';
			}
	return ans;		
}

int main()
{
	//ld time=clock();
  freopen(filename".in","r",stdin);
  freopen(filename".out","w",stdout);
	cin>>h;
	for (int i=0;i<h;i++)
		for (int j=0;j<6;j++)
			cin>>xc[5-j][h-i-1];	
	for (int i=0;i<h;i++)
		for (int j=0;j<6;j++)
			cin>>yc[j][h-i-1];		
	for (int i=0;i<6;i++)
		for (int j=0;j<6;j++)
			havex[i][j]=havey[i][j]='.';
	for (int i=0;i<6;i++)
		for (int j=0;j<6;j++)
			for (int k=0;k<6;k++)
				pole[i][j][k]='.';
	cout<<perebor(0,0,0)<<endl;
//	cerr<<((clock()-time)/CLOCKS_PER_SEC)<<endl;
  return 0;
}