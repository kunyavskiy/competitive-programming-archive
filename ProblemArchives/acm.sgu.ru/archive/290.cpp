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

struct point{
	int x,y,z;
	string name;
	point(){};
	point(int X,int Y,int Z,string S="")
	{
		x=X;
		y=Y;
		z=Z;
		name=S;
	}
};

istream& operator>>(istream& ifs,point& p){
	string s;
	getline(ifs,s);
	for (;s[s.size()-1]==' ';)
		s.erase(--s.end());
	//cerr<<"GET "<<s<<endl;
	p=point();
	s+=char(1);
	int a,b,c;
	char ec;
	for (;!(sscanf(s.data(),"%d %d %d %c",&a,&b,&c,&ec)==4 && ec==1);)
	{
		p.name+=s[0];
		s.erase(s.begin());
	}
	sscanf(s.data(),"%d %d %d",&p.x,&p.y,&p.z);
	//cerr<<p.name<<" "<<p.x<<" "<<p.y<<" "<<p.z<<endl;
	return ifs;
}

point operator-(const point& a,const point& b)
{
	return point(a.x-b.x,a.y-b.y,a.z-b.z);
}

bool used[100];
point pts[100];

struct plane{
	int64 a,b,c,d;
	plane(){}
	inline bool gen(const point& p1,const point& p2,const point& p3)
	{
		point v1=p2-p1;
		point v2=p3-p1;
		a=v1.y*v2.z-v2.y*v1.z;
		b=-(v1.x*v2.z-v2.x*v1.z);
		c=v1.x*v2.y-v1.y*v2.x;
		d=-a*p1.x-b*p1.y-c*p1.z;
		if (a==0 && b==0 && c==0)
			return false;
		return true;
	}
};

inline int operator* (plane a,point b)
{
	int64 tmp=a.a*b.x+a.b*b.y+a.c*b.z+a.d;
	if (tmp>0)
		return 1;
	if (tmp==0)
		return 0;
	return -1;
}

int n;
bool smth;
bool nu[100];
int kol[3];
		
inline void check(const point& A,const point& B,const point& C)
{
	plane a;
	if (!a.gen(A,B,C))
		return;
	smth=true;
	setval(kol,0);
	for (int i=0;i<n;i++)
	{
		int tmp=a*pts[i];
		kol[tmp+1]++;
		nu[i]=tmp==0;			
		if (kol[0] && kol[2])
			return;
	}
	for (int i=0;i<n;i++)
			used[i]|=nu[i];
}


int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  cin>>n;
  string TMP;
  getline(cin,TMP);
  for (int i=0;i<n;i++)
  	cin>>pts[i];
  for (int i=0;i<n;i++)
  	for (int j=i+1;j<n;j++)
  		for (int k=j+1;k<n;k++)
  			if (!used[k] || !used[i] || !used[j])
  				check(pts[i],pts[j],pts[k]);
  if (!smth)
  {
  	for (int i=0;i<n;i++)
  		used[i]=true;
  }
  vector<string> res;
  for (int i=0;i<n;i++)
  	if (used[i])
  		res.pb(pts[i].name);
 	printf("%d\n",res.size());
 	sort(res.begin(),res.end());
 	for (int i=0;i<res.size();i++)
 		printf("%s\n",res[i].data());
  return 0;
}