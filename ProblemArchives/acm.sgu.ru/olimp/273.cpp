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
using namespace std;

typedef long double ld;
typedef long long int64;

const ld eps=1e-09;

ld asinmy(ld tmp){
	assert(tmp<1+eps);
	ld l=0;
	ld r=M_PI/2;
	for (int i=0;i<500;i++){
		ld m=(l+r)/2;
		if (sin(m)<tmp)
			l=m;
		else
			r=m;
	}
	return (l+r)/2;
}


ld acosmy(ld tmp){
	assert(tmp<1+eps);
	ld l=0;
	ld r=M_PI/2;
	for (int i=0;i<500;i++){
		ld m=(l+r)/2;
		if (cos(m)>tmp)
			l=m;
		else
			r=m;
	}
//	cerr<<"acos("<<tmp<<")="<<(l+r)/2<<endl;
	return (l+r)/2;
}                                                                                                                                                                 


ld sqrtmy(ld tmp){
	assert(tmp>-eps);
	if (tmp<eps)
		return 0;
	ld l=0;
	ld r=tmp+10;
	for (int i=0;i<500;i++){
		ld m=(l+r)/2;
		if (m*m<tmp)
			l=m;
		else
			r=m;
	}
	return (l+r)/2;
}

ld h,l,m;

                                                                                                                                           

bool check(ld y1,ld x2,ld x3){
	ld mlen=sqrtmy(y1*y1+(x2+x3)*(x2+x3)/4);
	if (abs(mlen-m)>eps)
		return false;
	ld nc1=sqrtmy(y1*y1+x2*x2);
	ld nc2=sqrtmy(y1*y1+x3*x3);
	ld y=y1/nc1+y1/nc2;
	ld x=x2/nc1+x3/nc2;
	ld coef=y1/y;
	y*=coef;
	x*=coef;
	if (abs(sqrtmy(x*x+y*y)-l)>eps)
		return false;
	if (abs(x2-x3)<eps)
		return false;
	if (abs(y1)<eps)
		return false;
	return true;	
}

void solve(ld h,ld m,ld g){
//	cerr<<h<<" !!!!!! "<<m<<" "<<g<<endl;
	ld r=2*m/h;
	ld alp,bet;
                   
	if (abs(g)<eps)
		alp=bet=M_PI/4;
	else {
		r=r/sin(2*g);
		if (abs(r)<eps)
			return;
		r=1/r;
		r=2*r-cos(2*g);
		if (abs(r)>1+eps)
			return;
		ld tmp=acos(r);
		alp=tmp/2-g;
		bet=alp+2*g;
		
	}
//	cerr<<"!!!"<<alp<<" "<<bet<<endl;
	if (abs(alp+bet)>M_PI-eps)
		return;
	if (-alp>g-eps)
		return;
	if (bet < g+eps)	
		return;
	if (abs((-alp)-bet)<eps)
		return;
	if (!check(h,-tan(alp)*h,tan(bet)*h))
		return;
	printf("YES\n");
	cout.precision(15);
	cout<<fixed<<0<<" "<<h<<endl;
	cout<<fixed<<-tan(alp)*h<<" "<<0<<endl;
	cout<<fixed<<tan(bet)*h<<" "<<0<<endl;
	exit(0);
}

int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	cin>>h>>l>>m;
//	cerr<<h<<" "<<l<<" "<<m<<endl;
	if (h>l+eps || h>m+eps){
		printf("NO\n");
		return 0;
	}
	if (abs(h-l)<eps && abs(h-m)>eps){
		printf("NO\n");
		return 0;
	}
	if (abs(m-l)<eps && abs(h-m)>eps){
		printf("NO\n");
		return 0;
	}
	if (abs(h-m)<eps && abs(h-l)>eps){
		printf("NO\n");
		return 0;
	}	
	if (abs(h)<eps){
		printf("NO\n");
		return 0;
	}
	ld g=acosmy(h/l);
//	cerr<<g<<endl;
	solve(h,sqrtmy(m*m-h*h),g);
	solve(h,-sqrtmy(m*m-h*h),g);
	printf("NO\n");
    return 0;
}