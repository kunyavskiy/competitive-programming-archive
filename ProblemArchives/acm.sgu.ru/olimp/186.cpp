#include <iostream>
#include <iomanip>
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

#define sqr(x) ((x)*(x))

using namespace std;

                   
typedef long long int64;
typedef long double ld;

ld eps=1e-09;
const ld pi=M_PI;
const ld inf=1e+100;

ld P,Q1,Q2,Q3,L1,L2,S,R,r,R0;

bool ldless(ld a,ld b){
	return a < b - eps * (fabs(a) + fabs(b) + 1);
}

bool ldequal(ld a,ld b){
	return fabs(a - b) < eps * (fabs(a) + fabs(b) + 1);
}

bool ldmore(ld a,ld b){
	return ldless(b,a);
}

bool ldeqless(ld a,ld b){
  return !ldmore(a,b);
}

bool ldeqmore(ld a,ld b){
  return !ldless(a,b);
}

ld acosmy(ld a){
	ld l=0;
	ld r=pi;
	for (int i=0;i<100;i++)
		{
			ld m=(l+r)/2;
			if (cos(m)>a)
				l=m;
			else
				r=m;
		}
	return (l+r)/2;
}

ld asinmy(ld a){
	assert(ldeqmore(a,0));
	ld l=0;
	ld r=pi/2;
	for (int i=0;i<75;i++)
		{
			ld m=(l+r)/2;
			if (sin(m)>a)
				r=m;
			else
				l=m;
		}
	return (l+r)/2;
}

ld sqrts(ld a){
	assert(ldeqmore(a,0));
	if (ldequal(a,0))
		return 0;
	return sqrtl(a);
}

struct point{
	ld x,y,z;
	point(int h1,int m1,int s1,char p1,int h2,int m2,int s2,char p2,ld R){
		ld angle1=((h1*60.0+m1)*60.0+s1)/(60.0*60.0);
		angle1=angle1/180*pi;
		if (p1=='S')
			angle1*=-1;
		ld angle2=((h2*60.0+m2)*60.0+s2)/(60.0*60.0);
		angle2=angle2/180*pi;
		if (h1==90 && (m1>0 || s1>0)){
			angle1=pi-angle1;
			angle2+=pi;
		}
		if (p2=='E')
			angle2*=-1;
		z=R*sin(angle1);
		R=sqrts(R*R-z*z);
		x=R*cos(angle2);
		y=R*sin(angle2);		
		x/=::R;
		y/=::R;
		z/=::R;
	}
	point(ld a,ld b,ld c){
		x=a;
		y=b;
		z=c;		
	}
	point(){};
};

point operator+(point a,point b){
	return point(a.x+b.x,a.y+b.y,a.z+b.z);
}

point operator-(point a,point b){
	return point(a.x-b.x,a.y-b.y,a.z-b.z);
}

point operator*(point a,ld b){
	return point(a.x*b,a.y*b,a.z*b);
}

ld operator*(point a,point b){
	return sqrts(sqr(a.x-b.x)+sqr(a.y-b.y)+sqr(a.z-b.z));
}

enum rebtype {_under=0,_earth=1,_satelite=2};

struct reb{
	rebtype type;
	ld cost;
	ld len;
	int num1,num2;
	reb(rebtype t,ld c,ld l){
		type=t;
		len=l;
		cost=c;
	}
	reb(){}
};

bool operator<(reb a,reb b){
	if (!ldequal(a.cost,b.cost))
		return a.cost<b.cost;
	if (a.type!=b.type)
		return a.type<b.type;
	return ldless(a.len,b.len);
}

void minimize(reb& a,reb b){
	if (b<a)
		a=b;
}

bool good[210][210];

ld opr(ld a,ld b,ld c,ld d){
	return a*d-c*b;
}

ld ang(point a,point b){
	ld c=a.x*b.x+a.y*b.y+a.z*b.z;
	ld o1=opr(a.y,a.z,b.y,b.z);
	ld o2=opr(a.x,a.z,b.x,b.z);
	ld o3=opr(a.x,a.y,b.x,b.y);
	ld s=sqrts(o1*o1+o2*o2+o3*o3);
	return fabs(atan2(s,c));
}

ld len1(point a,point b){
	ld angle=ang(a,b);
	return R*angle;
}

ld len2(point a,point b){
	ld angle=ang(a,b);
	ld angle2=acosmy(r/R);
	if (ldeqless(angle,2*angle2))
		return a*b;
	return 2*sqrts(R*R-r*r) + r * (angle - 2* angle2 ) ;
}

ld len3(point a,point b,point c){
	return a*c+b*c;
}

reb find1(point a,point b,int v1,int v2){
	reb res;
	res.type=_earth;
	res.len=len1(a,b);
	res.cost=res.len*P;
	res.num1=v1;
	res.num2=v2;
	return res;
}

reb find2(point a,point b,int v1,int v2){
	reb res;
	res.type=_under;
	res.len=len2(a,b);
	if (ldless(res.len,L1))
		res.cost=res.len*Q1;
	else if (ldeqless(res.len,L2))
		res.cost=res.len*Q2;
	else
		res.cost=res.len*Q3;
	res.num1=v1;
	res.num2=v2;
	return res;		
}

reb find3(point a,point b,point c,int v1,int v2){
	reb res;
	res.type=_satelite;
	res.len=len3(a,b,c);
	res.cost=S;
	res.num1=v1;
	res.num2=v2;
	return res;
} 

point p[210];
point s[210];
int n,m;

int rebptr;
int treeptr;
reb spis[210];
reb tree[210];

void readpoints(){
	cin>>n;
	cin>> R >> r >> P >> L1 >> Q1 >> L2 >> Q2 >> Q3 >> S;
	R*=1000;
	r*=1000;
	L1/=R;
	L2/=R;
	S/=R;
	for (int i=0;i<n;i++){
		int h1,m1,s1,h2,m2,s2;
		char c1,c2;
		cin>>h1>>m1>>s1>>c1>>h2>>m2>>s2>>c2;
		p[i]=point(h1,m1,s1,c1,h2,m2,s2,c2,R);
	}
}

void readsat(){
	cin>>m;
	for (int i=0;i<m;i++){
		int h1,m1,s1,h2,m2,s2,H;
		char c1,c2;
		cin>>h1>>m1>>s1>>c1>>h2>>m2>>s2>>c2>>H;
		s[i]=point(h1,m1,s1,c1,h2,m2,s2,c2,H+R);
	}
	r/=R;
	R0=R;
	R=1;
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++){
		
			ld d1=p[i]*s[j];
			ld d2=point(0,0,0)*s[j];
			ld d3=sqrts(d2*d2-R*R);
			if (ldmore(d1,d3))
				good[i][j]=false;
			else
				good[i][j]=true;
		}
}

void readdata(){
	readpoints();
	readsat();
}

reb rebinf;
bool used[210];

void gengraf(int i){
	if (i==0){
		for (int j=0;j<n;j++)
			spis[j]=rebinf;
	}
	spis[i]=rebinf;
	used[i]=true;
	for (int j=0;j<n;j++)
		if (!used[j]){
			minimize(spis[j],find1(p[i],p[j],i,j));
			minimize(spis[j],find2(p[i],p[j],i,j));
			for (int k=0;k<m;k++)
				if (good[i][k] && good[j][k])
					minimize(spis[j],find3(p[i],p[j],s[k],i,j));			
	}
}

ld dest[210];
ld ans;

void prima(){
	treeptr=n-1;
	gengraf(0);
	dest[0]=0;
	ans=0;
	for (int i=0;i<n-1;i++){
		reb minr=rebinf;
		for (int j=0;j<n;j++)
			minimize(minr,spis[j]);
		if (used[minr.num2])
			swap(minr.num1,minr.num2);
		assert(used[minr.num1] && !used[minr.num2]);
		tree[i]=minr;
		dest[minr.num2]=dest[minr.num1]+minr.len;
		ans+=minr.cost;
		gengraf(minr.num2);
	}

}

void printans(){
	cout.precision(10);
	cout<<fixed<<ans*R0<<endl;
	cout<<treeptr<<endl;
	for (int i=0;i<treeptr;i++)
		cout<<tree[i].num1+1<<" "<<tree[i].num2+1<<" "<<"uga"[tree[i].type]<<endl;
	cout.precision(10);
	for (int i=1;i<n;i++)
		cout<<fixed<<dest[i]*R0<<" \n"[i==n-1];
}

int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
	readdata();
	rebinf.cost=rebinf.len=inf;
	rebinf.type=_satelite;
	prima();
	printans();
  return 0;
}