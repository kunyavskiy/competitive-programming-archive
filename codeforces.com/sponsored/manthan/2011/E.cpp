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
#define setval(a,v) memset(a,v,sizeof(a))

#if ( _WIN32 || __WIN32__ )
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

int64 l,r;

const ld eps = 1e-9;


int x[2000];
int y[2000];
int n;

int cmp(int x1,int y1,int x2,int y2,int x0,int y0){
	ld ang1=atan2(y1-y0,x1-x0);
	ld ang2=atan2(y2-y0,x2-x0);
	if (ang1 < -eps)
		ang1+= 2*M_PI;
	if (ang2 < -eps)
		ang2+= 2*M_PI;
	cerr<<ang1<<" "<<ang2<<endl;		
	//cerr<<x1-x0<<" "<<y1-y0<<" "<<x2-x0<<" "<<y2-y0<<" "<<x0<<" "<<y0<<" "<<ang1<<" "<<ang2<<endl;
	if (abs(ang2 - ang1) > eps)
		return (ang1 < ang2)*2 - 1;		
	int64 tmp=(x1-x0)*1LL*(y2-y0)-(x2-x0)*1LL*(y1-y0);
	if (tmp > 0)
		return 1;
	if (tmp < 0)
		return -1;
	return 0;
}

int checkpoint(int x0,int y0){
	bool q=false;
	for (int it=0;it<n;it++){
		rotate(x,x+1,x+n);		
		rotate(y,y+1,y+n);		
		bool ls,mr;
		ls=mr=false;
		for (int i=0;i<n;i++){
			if (x[i] == x0 && y[i]==y0) continue;
			if (x[i+1] == x0 && y[i+1]==y0) continue;
			int tmp=cmp(x[i],y[i],x[i+1],y[i+1],x0,y0);	
			if (tmp < 0)
				ls=true;
			if (tmp > 0)
				mr=true;
		}
		if ((!ls) || (!mr))
			q=true;
		cerr<<endl;
	}
	cerr<<endl;
	return q;
}

void error(){
	printf("0\n");
	exit(0);
}

int64 down(int64 b,int64 a){
	if (b==0)
		return 0;
	if (a<0){
		a=-a;
		b=-b;
	}		
	int64 x=b/a;
	while (x*a > b)
		--x;
	while ((x+1)*a <= b)
		++x;
	return x;
}

int64 up(int64 b,int64 a){
	if (b == 0)
		return 0;
	int64 x=down(a,b);
	if (x*a != b)
		x++;		
	return x;
}

void update(int64 a,int64 b){
	if (a == 0){
		if (b>=0)
			return;
		error();
	}
	if (a > 0)
		l=max(l,up(b,a));		
	else 
		r=min(r,down(b,a));	
}




int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	int64 y0;
  	cin>>n;
	for (int i=0;i<n;i++)
		scanf("%d %d",&x[i],&y[i]);		
	l=x[0];
	r=x[1];
	y0=y[0];
	if (l > r){
		reverse(x,x+n);
		reverse(y,y+n);
		swap(l,r);
	}
	reverse(x+1,x+n);
	reverse(y+1,y+n);
	reverse(x,x+n);
	reverse(y,y+n);
	bool ls,mr;
	ls=mr=false;
	for (int i=0;i<n;i++)
		if (y[i] < y0)
			ls=true;
		else if (y[i] > y0)
			mr=true;
	if (ls && mr){
	
	//	for (int i=0;i<n;i++)
	//		cerr<<x[i]<<" "<<y[i]<<endl;
	
		cout<<checkpoint(l,y0)+checkpoint(r,y0)<<endl;
		return 0;
	}
	
	if (ls){
		y0*=-1;
		for (int i=0;i<n;i++)
			y[i]*=-1;
	}			
/*
	for (int i=0;i<n;i++)
		y[i]-=y0;		
	y0=0;
	
	for (int i=0;i<n;i++)
	
	
	x[n]=x[0];
	y[n]=y[0];
	++l,--r;
	
	for (int i=0;i<n;i++)
		update(y[i]-y[i+1],x[i+1]*1LL*y[i]-x[i]*1LL*y[i+1]);			
		
		
	int64 ans=r-l+1;
	ans+=checkpoint(x[0],0);
	ans+=checkpoint(x[n-1],0);
	cout<< ans << endl;*/
	int cnt=0;
	for (int i=l;i<=r;i++)
		if (checkpoint(i,y0))
			cnt++;
	cout<<cnt<<endl;
	return 0;
}