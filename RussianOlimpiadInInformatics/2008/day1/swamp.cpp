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

map<int,int> lf;
map<int,int> rg;
vector<pair<int,int> > tmpl;
vector<pair<int,int> > tmpr;
int y[100000];
int l[100000];
int r[100000];
int n;

void ras_up(int L,int R){
	for (int i=1;i<R;i++)
			r[i]=max(r[i],r[i-1]);
	for (int i=1;i<L;i++)
			l[i]=min(l[i],l[i-1]);
}

void ras_down(int L,int R){
	for (int i=n-2;i>=L;i--)
		l[i]=min(l[i],l[i+1]);
	for (int i=n-2;i>=R;i--)
		r[i]=max(r[i],r[i+1]);
}

int ansx[500000];
int ansy[500000];
int ansptr;

void add(int x,int y){
	ansx[ansptr]=x;
	ansy[ansptr]=y;
	ansptr++;
}

void gen_left(){
	add(l[n-1],y[n-1]);
	for (int i=n-2;i>=0;i--){
		if (l[i]!=l[i+1]){
			add(l[i+1],y[i]);
			add(l[i],y[i]);
		}
		else if (i==0 || l[i-1]!=l[i])
			add(l[i],y[i]);
	}
}

void gen_right(){
	add(r[0],y[0]);
	for (int i=1;i<n;i++){
		if (r[i]!=r[i-1]){
			add(r[i-1],y[i]);
			add(r[i],y[i]);
		}
		else if (i==n-1 || r[i+1]!=r[i])
			add(r[i],y[i]);
	}
}


int main()
{
  #ifndef ONLINE_JUDGE
    freopen("swamp.in","r",stdin);
    freopen("swamp.out","w",stdout);
  #endif
  scanf("%d",&n);
  for (int i=0;i<n;i++){
  	int a,b;
  	scanf("%d %d",&a,&b);
  	if (lf.count(b)==0)
  			lf[b]=rg[b]=a;
  	else
  		{
  			lf[b]=min(lf[b],a);
  			rg[b]=max(rg[b],a);  			
  		}
  }
  tmpl=vector<pair<int,int> > (lf.begin(),lf.end());
  tmpr=vector<pair<int,int> > (rg.begin(),rg.end());
  n=tmpl.size();
  for (int i=0;i<n;i++){
		y[i]=tmpl[i].first;
		l[i]=tmpl[i].second;
		r[i]=tmpr[i].second;
  }
  int minl=0,maxr=0;
  for (int i=0;i<n;i++){
  	if (l[i]<l[minl])
  		minl=i;
  	if (r[i]>r[maxr])
  		maxr=i;
  }
  ras_up(minl,maxr);
  ras_down(minl,maxr);
 	ansptr=0;
	gen_left();
	gen_right();
	printf("%d\n",ansptr);
	for (int i=0;i<ansptr;i++)
		printf("%d %d\n",ansx[i],ansy[i]);
  return 0;
}