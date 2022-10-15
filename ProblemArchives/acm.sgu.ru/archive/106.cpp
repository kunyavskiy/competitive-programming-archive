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

int64 gcdex(int64 a,int64 b,int64& x,int64& y){
	if (b==0)
	{
		x=1;
		y=0;
		return a;
	}
	int64 x1,y1,tmp;
	tmp=gcdex(b,a%b,x1,y1);
	x=y1;
	y=x1-(a/b)*y1;
	return tmp;
}


void cnt(int64 x,int64 delt,int64 lx,int64 rx,int64 &lk,int64& rk){
	int sgnd=delt/labs(delt);
	delt*=sgnd;
	if (x<lx){
		lk=(lx-x)/delt+(!!((lx-x)%delt));
		rk=(rx-x)/delt;
	}
	else if (x<rx){
		lk=-((x-lx)/delt);
		rk=(rx-x)/delt;
	}
	else{
		lk=-((x-lx)/delt);
		rk=-((x-rx)/delt+(!!((x-rx)%delt)));
	}
	if (sgnd==-1){
		lk=-lk;
		rk=-rk;
		swap(lk,rk);
	}
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
 	int a,b,c,x1,y1,x2,y2;
 	cin>>a>>b>>c>>x1>>x2>>y1>>y2;
 	c*=-1;
 	if (x1>x2 || y1>y2)
 		{
 			printf("0\n");
 			return 0;
 		}
 	if (a==0 && b==0){
 		if (c!=0)
 			{
 				printf("0\n");
 				return 0;
 			}
 		cout<<(x2-x1+1)*1ll*(y2-y1+1)<<endl;
 		return 0;
 	}
 	if (a==0){
 		int sgnb=b/abs(b);
		int sgnc=((c==0)?(0):((c)/abs(c)));
		b*=sgnb;c*=sgnc;
 		if (c%b!=0)
 		{
 			printf("0\n");
 			return 0;
 		}
		int tmp=c/b;
		tmp*=sgnb*sgnc;
		if (y1<=tmp && tmp<=y2)
			cout<<(x2-x1+1)<<endl;
		return 0;
 	}
 	if (b==0){
 		int sgna=a/abs(a);
		int sgnc=((c==0)?(0):((c)/abs(c)));
		a*=sgna;c*=sgnc;
 		if (c%a!=0)
 		{
 			printf("0\n");
 			return 0;
 		}
		int tmp=c/a;
		tmp*=sgna*sgnc;
		if (x1<=tmp && tmp<=x2)
			cout<<(y2-y1+1)<<endl;
		return 0; 	
 	}
 	
 	int64 x,y,tmp;
 	int sgna=a/abs(a);
 	int sgnb=b/abs(b);
 	int sgnc=((c==0)?(0):((c)/abs(c)));
 	a*=sgna;
 	b*=sgnb;
 	c*=sgnc;
 	tmp=gcdex(a,b,x,y);
 	if (c%tmp!=0){
 		printf("0\n");
 		return 0;
 	}
 	a/=tmp;b/=tmp;c/=tmp;
 	x*=sgna;a*=sgna;
 	y*=sgnb;b*=sgnb;
 	x*=c;y*=c;
 	x*=sgnc;y*=sgnc;c*=sgnc;
  	int64 lx,rx,ly,ry,lk,rk;
 	cnt(x,b,x1,x2,lx,rx);
 	cnt(y,-a,y1,y2,ly,ry);
 	lk=max(lx,ly);
 	rk=min(rx,ry);
 	if (lk>rk)
 		printf("0\n");
 	else
 		cout<<rk-lk+1<<endl; 		
  return 0;
}