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
#define filename ""
using namespace std;

const int maxm=600;

int a[600][maxm];
int sum[600][maxm];

int n,m;


bool trans;

	int A[600][600];
	int SUM[600][600];

void transponate(){
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++){
				A[j][i]=a[i][j];
				SUM[j][i]=sum[i][j];
			}
	swap(n,m);
	memset(a,0,sizeof(a));
	memset(sum,0,sizeof(sum));
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++){
				a[i][j]=A[i][j];
				sum[i][j]=SUM[i][j];
			}
	trans=true;
}



void printans(){
	if (trans)
		transponate();
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<m;j++)
			printf("%c",'X'*a[i][j]+'.'*(!a[i][j]));
		printf("\n");
	}
	exit(0);
}

bool good(int i,int j){
	return i>=0 && j>=0 && i<n && j<m;
}

int s[600];

bool checksum(int i,int j){
	int s=0;
	for (int di=-1;di<=1;di++)		
		for (int dj=-1;dj<=1;dj++)
			if (good(i+di,j+dj))
				s+=a[i][j];
	return s==sum[i][j];
}

bool try_line(int i){
	for (int j=1;j<m;j++)
		{
			a[i][j]=s[j-1]-a[i][j-1];
			if (j!=1)
				a[i][j]-=a[i][j-2];
			if (a[i][j]<0)
				return false;
			if (a[i][j]>1)
				return false;
		}
	return a[i][m-2]+a[i][m-1]==s[m-1];
}

void make_line(int i){
	for (int j=0;j<m;j++)
			{
				s[j]=sum[i+1][j];
				for (int di=0;di<=1;di++)
					for (int dj=-1;dj<=1;dj++)
						if (good(i+1+di,j+dj))
							s[j]-=a[i+di+1][j+dj];
			}
			
	a[i][0]=0;
	if (!try_line(i))
	{
		a[i][0]=1;
		try_line(i);
	}
	return;

}


void last_line(){
	int i=n-1;
	
	for (int j=0;j<m;j++)
	{
		s[j]=sum[i][j];
		s[j]-=a[i-1][j];
		if (j!=0)
			s[j]-=a[i-1][j-1];
		if (j!=m-1)
			s[j]-=a[i-1][j+1];
	}

	
	a[i][0]=0;
	if (!try_line(i))
	{
		a[i][0]=1;
		try_line(i);
	}
}

void pre_last_line(){
	int i=n-2;
	
	for (int j=0;j<m;j++)
	{
		s[j]=sum[i+1][j];
		s[j]-=a[i+1][j];
		if (j!=0)
			s[j]-=a[i+1][j-1];
		if (j!=m-1)
			s[j]-=a[i+1][j+1];
	}

	
	a[i][0]=0;
	if (!try_line(i))
	{
		a[i][0]=1;
		try_line(i);
	}
}

bool last_line_2(){
	assert(false);
	return false;
}

void solve(){
	for (int i=2;i<n;i+=3){
			for (int j=0;j<m;j++)
			{
				s[j]=sum[i-1][j]-sum[i-2][j];
				if (i!=2)
				{
					s[j]+=a[i-3][j];
					if (j!=0)
						s[j]+=a[i-3][j-1];
					if (j!=m-1)
						s[j]+=a[i-3][j+1];
				}
			}
			
			a[i][0]=0;
			if (!try_line(i)){
				a[i][0]=1;
				try_line(i);
			}	
	}
	int n1=n;
	if (n%3==0)
	{
		pre_last_line();
		n1-=2;
	}
	if (n%3==1)
	{
		last_line();
		n1-=2;
	}
	if (n%3==2)
	{
		last_line_2();
		n1-=3;
	}
	for (int i=n1-1;i>=0;i--)
		if (i%3!=2)
			make_line(i);
	printans();
}

int main()
{
	freopen("mines.in","r",stdin);
	freopen("mines.out","w",stdout);
	char c;
	cin>>n>>m;
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++){
			cin>>c;
			sum[i][j]=c-'0';
		}
	if (n%3==2)
	{
		transponate();
		cerr<<"TRANS"<<endl;
	}
	solve();
  return 0;
}