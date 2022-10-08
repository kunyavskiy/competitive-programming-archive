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
#define y1 botva
using namespace std;

ld t1,t2;
ld d1,d2,d3;
int x1,x2,x3,y1,y2,y3;

const ld eps=1E-09;

bool intersec(ld r,ld a,ld b,ld c,ld &r1x,ld &r1y,ld &r2x,ld& r2y){
  ld d=(a*a+b*b)*r*r-c*c;
  if (d<-eps)
  	return false;
  if (d>eps)
    {
      d=sqrtl(d);
			r1x=(-a*c+b*d)/(a*a+b*b);r1y=(-b*c-a*d)/(a*a+b*b);
      r2x=(-a*c-b*d)/(a*a+b*b);r2y=(-b*c+a*d)/(a*a+b*b);
      return true;
    }
  if (fabsl(d)<eps)
    {
      r1x=r2x=-a*c/(a*a+b*b);
      r1y=r2y=-b*c/(a*a+b*b);
      return true;
    }
  return false;   

}

bool intersec(int x1,int y1,ld r1,int x2,int y2,ld r2,ld &r1x,ld &r1y,ld &r2x,ld& r2y){
	x2-=x1;
	y2-=y1;
	ld a=-2*x2;
	ld b=-2*y2;
	ld c=x2*x2+y2*y2+r1*r1-r2*r2;
	bool q=intersec(r1,a,b,c,r1x,r1y,r2x,r2y);
	if (q){
		r1x+=x1;
		r2x+=x1;
		r1y+=y1;
		r2y+=y1;
		return true;
	}
	return false;
}


bool check(int x1,int y1,ld r1,int x2,int y2,ld r2,int x3,int y3,ld r3){
	ld px1,px2,py1,py2;
	if (!intersec(x1,y1,r1,x2,y2,r2,px1,py1,px2,py2))
		return false;
//	cerr<<t<<" "<<px1<<" "<<py1<<" "<<px2<<" "<<py2<<endl;
	if (((x3-px1)*(x3-px1)+(y3-py1)*(y3-py1))<(r3*r3)+eps)
		return true;
	if (((x3-px2)*(x3-px2)+(y3-py2)*(y3-py2))<(r3*r3)+eps)
		return true;
	return false;	
}

bool check(ld t){
	ld r1=t;
	ld r3=d1+t1-t;
	ld r2=d2+t2-t;
	if (r1<-eps || r2<-eps || r3<-eps)
		return false;
	if (check(x1,y1,r1,x2,y2,r2,x3,y3,r3))
		return true;
	if (check(x1,y1,r1,x3,y3,r3,x2,y2,r2))
		return true;
	if (check(x3,y3,r3,x2,y2,r2,x1,y1,r1))
		return true;
	return false;
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  cin>>t1>>t2;
  cin>>x1>>y1>>x2>>y2>>x3>>y3;
  d1=sqrt((x3-x1)*1.0*(x3-x1)+(y3-y1)*(y3-y1));
  d2=sqrt((x2-x1)*1.0*(x2-x1)+(y2-y1)*(y2-y1));
  d3=sqrt((x3-x2)*1.0*(x3-x2)+(y3-y2)*(y3-y2));
  if (d2+t2>d1+d3-eps){
  	cout.precision(15);
  	cout<<fixed;
  	cout<<(d1+d3+min(t1,t2))<<endl;
  	return 0;
  }
  ld l=0;
  ld r=1E+05;
 //	cerr<<d1<<" "<<d2<<endl;
  for (;r-l>1E-06;){
  //	cerr<<l<<" "<<r<<endl;
  	ld m=(l+r)/2;
  	if (check(m))
  		l=m;
  	else
  		r=m;
  }
  cout.precision(15);
  cout<<((l+r)/2)<<endl;
  return 0;
}