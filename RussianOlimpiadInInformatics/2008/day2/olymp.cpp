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

typedef pair<int,int> pii;


ld tect;
const ld eps=1e-09;
const ld inf=1e+100;
pii v[60];
pii p[60];
int tec[60];

struct ev{
	ld time;int fi;int ob;
};

bool operator<(const ev& a,const ev &b){
	return (a.time-b.time<-eps);
}


ev events[200000];
int pt;
int n,m;

void add (ld t,int o,int f){
	if (tec[f]==o)
		return;
	events[pt].time=t;
	events[pt].fi=p[f].second;
	events[pt].ob=v[o].second;
	tec[f]=o;
	pt++;
}

struct object{
	vector<int> obs;
	ld h;
	int v;
	int kol;
	int kolf;
	object(){
		obs.clear();
		h=0;
		v=0;
		kol=kolf=0;
	}
	object(int i){
		obs.pb(i);
		h=::v[i].first;
		v=::p[i].first;
		kolf=(i<m);
		kol=1;
	}
	void merge(object a){
		assert(abs(h-a.h)<eps);
		v=v+a.v;
		obs.insert(obs.end(),a.obs.begin(),a.obs.end());
		kol=kol+a.kol;
		kolf=kolf+a.kolf;
	}
	ld realv() const{
		return v*1.0/kol;
	}
	void down(ld t){
		h-=t*realv();
		for (int i=0;i<kol;i++)
			for (int j=0;j<kolf;j++)
				add(tect+t*i/kol,obs[(i+j)%kol],obs[j]);
	}
};

object now[50];

ld rovn(const object &a,const object &b){
	if (a.h<b.h)
		return rovn(b,a);
	if (a.kolf==0)
		return inf;
	if (b.kolf==0)
		return (a.h-b.h)/(a.realv());
	if (a.realv()-b.realv()<eps)
		return inf;
	return (a.h-b.h)/(a.realv()-b.realv());
}

ld rovn(const object &a){
	if (a.realv()<eps)
		return inf;
	return a.h/(a.realv());
}

void downall(ld t){
	for (int i=0;i<n;i++)
			now[i].down(t);
	tect+=t;
}

ld rovn(){
	ld ans=inf;
	for (int i=0;i<n;i++)
		ans=min(ans,rovn(now[i]));
	for (int i=0;i<n;i++)
		for (int j=i+1;j<n;j++)
			ans=min(ans,rovn(now[i],now[j]));
	return ans;
}

void merge_all(){
	for (int i=0;i<n-1;i++){
		if (abs(now[i].h-now[i+1].h)<eps)
		{
			now[i].merge(now[i+1]);
			for (int j=i+1;j<n;j++)
				swap(now[j],now[j+1]);
			n--;
			i--;
		}
	}
	for (;n>0;)
		if (now[n-1].h<eps)
			n--;	
		else
			break;
}

bool iterate(){
	ld itt=rovn();
	downall(itt);
	merge_all();
	return n!=0;
}




int main()
{
  freopen("olymp.in","r",stdin);
  freopen("olymp.out","w",stdout);
  scanf("%d",&n);
  for (int i=0;i<n;i++)
  {
  	scanf("%d",&v[i].first);
  	v[i].second=i+1;
  }
  scanf("%d",&m);
  for (int i=0;i<m;i++){
  	scanf("%d",&p[i].first);
  	p[i].second=i+1;
  }
  sort(p,p+m);
  reverse(p,p+m);
  sort(v,v+n);
  reverse(v,v+n);
  for (int i=m;i<n;i++)
	  p[i].first=0;
  for (int i=0;i<n;i++)
		now[i]=object(i);
  pt=0;
  merge_all();
  setval(tec,-1);
  for (;iterate(););
  cout.precision(9);
  cout<<fixed;
  cout<<tect<<endl;
  sort(events,events+pt);
  for (int i=0;i<pt;i++)
	  cout<<events[i].time<<" "<<events[i].ob<<" "<<events[i].fi<<endl;
  return 0;
}