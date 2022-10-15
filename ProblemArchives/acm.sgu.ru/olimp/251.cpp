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
#define ld double  
#define setval(a,v) memset(a,v,sizeof(a))
using namespace std;

const ld eps=1e-09;

struct plane;

struct point{
	ld x,y,z;
	point(){};
	point(ld X,ld Y,ld Z)
	{
		x=X;
		y=Y;
		z=Z;
	}
	bool gen(const plane& a,const point&p1,const point &p2);
};

istream& operator>>(istream& ifs,point& p){
	ifs>>p.x>>p.y>>p.z;
	return ifs;
}

point operator-(const point& a,const point& b)
{
	return point(a.x-b.x,a.y-b.y,a.z-b.z);
}


point operator+(const point& a,const point& b)
{
	return point(a.x+b.x,a.y+b.y,a.z+b.z);
}

typedef vector<point> polygon;

struct plane{
	ld a,b,c,d;
	plane(){}
	inline bool gen(const point& p1,const point& p2,const point& p3)
	{
		point v1=p2-p1;
		point v2=p3-p1;
		a=v1.y*v2.z-v2.y*v1.z;
		b=-(v1.x*v2.z-v2.x*v1.z);
		c=v1.x*v2.y-v1.y*v2.x;
		d=-a*p1.x-b*p1.y-c*p1.z;
		if (abs(a)<eps && abs(b)<eps && abs(c)<eps)
			return false;
		return true;
	}
	plane(const point& p1,const point &p2)
	{
		a=p2.x-p1.x;
		b=p2.y-p1.y;
		c=p2.z-p1.z;
		ld x=(p1.x+p2.x)/2;
		ld y=(p1.y+p2.y)/2;
		ld z=(p1.z+p2.z)/2;
		d=-a*x-b*y-c*z;
	}
};


ostream& operator<<(ostream& ofs,const point& a){
	ofs<<a.x<<" "<<a.y<<" "<<a.z<<endl;
	return ofs;
}

ostream& operator<<(ostream& ofs,const plane& a){
	ofs<<a.a<<" "<<a.b<<" "<<a.c<<" "<<a.d<<endl;
	return ofs;
}

ostream& operator<<(ostream& ofs,const polygon& a){
	for (int i=0;i<a.size();i++)
		ofs<<a[i];
	ofs<<endl;
	return ofs;
}


inline int operator* (plane a,point b)
{
	ld tmp=a.a*b.x+a.b*b.y+a.c*b.z+a.d;
	if (tmp>eps)
		return 1;
	if (tmp<-eps)
		return -1;
	return 0;
}

bool point::gen(const plane& a,const point& p1,const point& p2){
	//cerr<<"TRY GEN FROM"<<a<<p1<<p2<<endl;
	if ((a*p1)*(a*p2)!=-1)
		return false;
	ld vx=p2.x-p1.x;
	ld vy=p2.y-p1.y;
	ld vz=p2.z-p1.z;
	ld t=-(a.a*p1.x+a.b*p1.y+a.c*p1.z+a.d)/(a.a*vx+a.b*vy+a.c*vz);
	x=p1.x+t*vx;
	y=p1.y+t*vy;
	z=p1.z+t*vz;
	return true;
}


int n;
bool smth;
bool nu[100];
bool used[100];
int kol[3];
		
inline bool check(const point& A,const point& B,const point& C,const polygon &f)
{
	plane a;
	if (!a.gen(A,B,C))
		return false;
	smth=true;
	setval(kol,0);
	n=f.size();
	for (int i=0;i<n;i++)
	{
		int tmp=a*f[i];
		kol[tmp+1]++;
		nu[i]=tmp==0;			
		if (kol[0] && kol[2])
			return false;
	}
	for (int i=0;i<n;i++)
			used[i]|=nu[i];
	return true;
}

inline void norm(polygon &f)
{
	setval(used,false);
	int n=f.size();	
  for (int i=0;i<n;i++)
  	for (int j=i+1;j<n;j++)
  		for (int k=j+1;k<n;k++)
  			if (!used[k] || !used[i] || !used[j])
  				check(f[i],f[j],f[k],f);
  for (int i=0;i<n;i++)
  	if (!used[i])
  	{
  		swap(used[i],used[n-1]);
  		swap(f[i],f[n-1]);
  		f.pop_back();
  		--n;
  		--i;
  	}
}

bool operator< (point a,point b)
{
	if (abs(a.x-b.x)>eps)
		return a.x<b.x;
	if (abs(a.y-b.y)>eps)
		return a.y<b.y;
	return a.z<b.z;
}

bool operator== (point a,point b)
{
	return abs(a.x-b.x)<eps && abs(a.y-b.y)<eps && abs(a.z-b.z)<eps;
}

point srt;

point operator*(point v1,point v2)
{
	point res;
	res.x=v1.y*v2.z-v2.y*v1.z;
	res.y=-(v1.x*v2.z-v2.x*v1.z);
	res.z=v1.x*v2.y-v1.y*v2.x;
	return res;
}

bool cmp(point a,point b)
{
	a=a-srt;
	b=b-srt;	
	point norm=a*b;
	if (abs(norm.x)>eps)
		return norm.x>0;
	if (abs(norm.y)>eps)
		return norm.y>0;
	if (abs(norm.z)>eps)
		return norm.z>0;
	return false;
}

ld opr(ld x00,ld x01,ld x10,ld x11){
	return x00*x11-x01*x10;
}

ld opr(ld x00,ld x01,ld x02,ld x10,ld x11,ld x12,ld x20,ld x21,ld x22){
	return x00*opr(x11,x12,x21,x22)-x01*opr(x10,x12,x20,x22)+x02*opr(x10,x11,x20,x21);
}

inline ld planevolume(polygon& f)
{
	srt=f[0];
	sort(++f.begin(),f.end(),cmp);
	int n=f.size();
	ld res=0;
	for (int i=1;i<n-1;i++)
		res+=abs((1/6.0)*opr(f[0].x,f[0].y,f[0].z,f[i].x,f[i].y,f[i].z,f[i+1].x,f[i+1].y,f[i+1].z));
//	cerr<<f;
//	cerr<<res<<endl<<endl;
	return res;
}

inline ld volume(polygon& f,const point& m)
{
	int n=f.size();
	sort(f.begin(),f.end());
	point sdv=m;
	for (int i=0;i<n;i++)
		f[i]=f[i]-sdv;
	vector<polygon> pls;
	polygon tmp;
  for (int i=0;i<n;i++)
  	for (int j=i+1;j<n;j++)
  		for (int k=j+1;k<n;k++)
  			if (check(f[i],f[j],f[k],f))
 				{
 					tmp.clear();
 					for (int i=0;i<n;i++)
 						if (nu[i])
	 						tmp.pb(f[i]);
	 				sort(tmp.begin(),tmp.end());
	 				pls.pb(tmp);	 				
				}
	sort(pls.begin(),pls.end());
	pls.erase(unique(pls.begin(),pls.end()),pls.end());
	ld res=0;
	int sz=pls.size();
	for (int i=0;i<sz;i++)
	{
		res+=planevolume(pls[i]);
	//	cerr<<pls[i];
	//	cerr<<res<<endl<<endl;
	}	
	for (int i=0;i<n;i++)
		f[i]=f[i]+sdv;
	return abs(res);
}


inline void rasres (polygon& f,plane a,const point& mu)
{
//	cerr<<"!"<<endl;
	if (a*mu==-1)
		{
			a.a=-a.a;
			a.b=-a.b;
			a.c=-a.c;
			a.d=-a.d;
		}
	int n=f.size();
	vector<polygon> pls;
	polygon tmp;
  for (int i=0;i<n;i++)
  	for (int j=i+1;j<n;j++)
  		for (int k=j+1;k<n;k++)
  			if (check(f[i],f[j],f[k],f))
 				{
 					tmp.clear();
 					for (int i=0;i<n;i++)
 						if (nu[i])
	 						tmp.pb(f[i]);
	 				sort(tmp.begin(),tmp.end());
	 				//cerr<<"FOUND"<<endl<<tmp;
	 				pls.pb(tmp);	 				
				}
	sort(pls.begin(),pls.end());
	pls.erase(unique(pls.begin(),pls.end()),pls.end());
	polygon res;
	for (int i=0;i<n;i++)
		if (a*f[i]>=0)
			res.pb(f[i]);
	for (int i=0;i<pls.size();i++)
	{
		srt=pls[i][0];
		sort(++pls[i].begin(),pls[i].end(),cmp);		
	}
	for (int i=0;i<pls.size();i++)
	{
		point tmp;
		int sz=pls[i].size();
		for (int j=0;j<sz;j++)
			if (tmp.gen(a,pls[i][j],pls[i][(j+1)%sz]))
				res.pb(tmp);
	}		
	sort(res.begin(),res.end());
	res.erase(unique(res.begin(),res.end()),res.end());
	f=res;
	return;
}

int main()
{
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  int n;
  cin>>n;
  vector<point> m(n);
  for (int i=0;i<n;i++)
  	cin>>m[i];
 	for (int i=0;i<n;i++)
 	{
 	//	cerr<<i<<endl;
 		polygon tec;
 		for (int x=0;x<201;x+=200)
	 		for (int y=0;y<201;y+=200)
 				for (int z=0;z<201;z+=200)
	 				tec.pb(point(x,y,z));
	 	for (int j=0;j<n;j++)
	 		if (i!=j)
	 			rasres(tec,plane(m[i],m[j]),m[i]);
	 	//cerr<<tec;
	 	cout<<fixed;
	 	cout.precision(5);
	 	cout<<volume(tec,m[i]);
	 	cout<<endl;
 	}
  return 0;
}