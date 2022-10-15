#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <memory.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iterator>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

#define taskname "ufo"

using namespace std;

typedef long long int64;
typedef double ld;

double eps;

ld x,y,r,r2;

template<typename T>
inline T Min(T a,T b){
	if (a<=b)
		return a;
	return b;
}

template<typename T>
inline T Max(T a,T b){
	if (a<=b)
		return b;
	return a;
}

inline bool checkin(ld x1,ld y1){
	return (x1-x)*(x1-x)+(y1-y)*(y1-y) <= r2;
}

inline bool checkin(ld lx,ld rx,ld ly,ld ry){
	return checkin(lx,ly) && checkin(lx,ry) && checkin(rx,ly) && checkin(rx,ry);
}

inline ld destx(ld x1,ld ly,ld ry){
	if (ly<= y && y<=ry)
		return (x1-x)*(x1-x);
	return (x1-x)*(x1-x)+Min((y-ly)*(y-ly),(y-ry)*(y-ry));
}

inline ld desty(ld y1,ld lx,ld rx){
	if (lx<= x && x<=rx)
		return (y1-y)*(y1-y);
	return (y1-y)*(y1-y)+Min((x-lx)*(x-lx),(x-rx)*(x-rx));
}

inline bool checkout(ld lx,ld rx,ld ly,ld ry){
	if (lx<=x && x<=rx && ly<=y && y<=ry)
		return false;
	if (destx(lx,ly,ry) < r2)
		return false;
	if (destx(rx,ly,ry) < r2)
		return false;
	if (desty(ly,lx,rx) < r2)
		return false;
	if (desty(ry,lx,rx) < r2)
		return false;
	return true;
}

ld ans;

ld Lx[1000000],Ly[1000000],Rx[1000000],Ry[1000000];
int ptr;

inline void push(ld lx,ld ly,ld rx,ld ry){
	Lx[ptr]=lx;
	Rx[ptr]=rx;
	Ly[ptr]=ly;
	Ry[ptr]=ry;
	++ptr;	
}

inline void pop(ld& lx,ld& ly,ld& rx,ld& ry){
	--ptr;
	lx=Lx[ptr];
	rx=Rx[ptr];
	ly=Ly[ptr];
	ry=Ry[ptr];
}


void calc(ld lx,ld rx,ld ly,ld ry){
	push(lx,rx,ly,ry);
	ld mx,my;
	for (;ptr;){
		pop(lx,rx,ly,ry);
		if (checkin(lx,rx,ly,ry))
			ans+=((rx-lx)*(ry-ly));			
		else if (checkout(lx,rx,ly,ry));
		else if (rx-lx < eps){
			ans+=((rx-lx)*(ry-ly))/2;				
		}
		else {
			mx=(lx+rx)/2;
			my=(ly+ry)/2;
			push(lx,mx,ly,my);
			push(lx,mx,my,ry);
			push(mx,rx,ly,my);
			push(mx,rx,my,ry);		
		}
	}
}



int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif
	cin>>x>>y>>r;
	r/=2;
	r2=r*r;
	ld x1,x2,y1,y2;
	cin>>x1>>x2>>y1>>y2;
	eps=1.1*(1e-5);
	x1=max(x1,x-r);
	y1=max(y1,y-r);
	x2=min(x2,x+r);
	y2=min(y2,y+r);	
	if (x1 < x2 && y1 < y2)
		calc(x1,x2,y1,y2);
	cout.precision(9);
	cout<<fixed<<ans<<endl;
	return 0;
} 