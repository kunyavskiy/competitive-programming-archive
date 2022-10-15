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

bool t[41][361][321][10][2];
bool cnted[41][361][321][10][2];
//char cif[41][361][321][10][2];

int d;
int n;

bool cnt(int k,int s,int p,int q,bool up){
	if (s<0 || p<0)
		return false;
	if (cnted[k][s][p][q][up])
		return t[k][s][p][q][up];
	cnted[k][s][p][q][up]=true;
	bool& res=t[k][s][p][q][up];
	if (up){
		if (k==0)
			return res=(s==0 && p==0 && q==0);
		for (int i=(k==n);i<10;i++)
		{
			int tmp=i*d;
			int tmp1=tmp/10;
			int tmp2=tmp%10;
			if (tmp1>=q)
				{
					res=cnt(k-1,s-i,p-tmp1,9-tmp2,0);
					if (res)
						return true;
				}
			if (tmp1>=q-1){
					res=cnt(k-1,s-i,p-tmp1-1,10-tmp2,1);
					if (res)
						return true;
				}
		}
		return res=false;
	}
	if (k==0)
		return res=(s==0 && p==0);
	for (int i=(k==n);i<10;i++)
	{
		int tmp=i*d;
		int tmp1=tmp/10;
		int tmp2=tmp%10;
		if (tmp1<=q)
			{
				res=cnt(k-1,s-i,p-tmp1,9-tmp2,0);
				if (res)
				return true;
			}
		if (tmp1<=q-1){
				res=cnt(k-1,s-i,p-tmp1-1,10-tmp2,1);
				if (res)
					return true;
			}
	}
	return res=false;
}

void print(int k,int s,int p,int q,bool up){
	if (k==0)
		return;
	if (up){
		for (int i=(k==n);i<10;i++)
		{
			int tmp=i*d;
			int tmp1=tmp/10;
			int tmp2=tmp%10;
			if (tmp1>=q && cnt(k-1,s-i,p-tmp1,9-tmp2,0))
				{
					printf("%d",i);
					print(k-1,s-i,p-tmp1,9-tmp2,0);
					return;
				}
			if (tmp1>=q-1 && cnt(k-1,s-i,p-tmp1-1,10-tmp2,1)){
					printf("%d",i);
					print(k-1,s-i,p-tmp1-1,10-tmp2,1);
					return;
				}
		}
		assert(false);
	}
	for (int i=(k==n);i<10;i++)
	{
		int tmp=i*d;
		int tmp1=tmp/10;
		int tmp2=tmp%10;
		if (tmp1<=q && cnt(k-1,s-i,p-tmp1,9-tmp2,0))
			{
				printf("%d",i);
				print(k-1,s-i,p-tmp1,9-tmp2,0);
				return;
			}
		if (tmp1<=q-1 && cnt(k-1,s-i,p-tmp1-1,10-tmp2,1)){
				printf("%d",i);
				print(k-1,s-i,p-tmp1-1,10-tmp2,1);
				return;
			}
	}
	assert(false);
}




int main()
{
  freopen("digit.in","r",stdin);
  freopen("digit.out","w",stdout);
//  cerr<<(sizeof(t)+sizeof(cnted))/1024.0/1024<<endl;
  int s,p;
  scanf("%d %d %d %d",&n,&s,&p,&d);
  if (p%9 != (s*d) %9)
  	{
  		printf("-1\n");
  		return 0;
  	}
  if (d*s<p)
  	{
  		printf("-1\n");
  		return 0;
  	}
  p=(d*s-p)/9;
  for (int i=0;i<10;i++)
  	if (cnt(n,s,p,i,0))
  		{
  			//cerr<<n<<" "<<s<<" "<<p<<" "<<i<<endl;
  			print(n,s,p,i,0);
  			return 0;
  		}
  printf("-1\n");
  return 0;
}