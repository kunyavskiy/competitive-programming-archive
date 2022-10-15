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

typedef multiset<pair<pair<int,int>,int> > line;
typedef line::iterator liter; 

line l;

int64 ans[2];


void calc(int coef){
	if (coef == 0)
		return;
	vector<pair<int64,int> > evs;
	for (liter iter = l.begin();iter != l.end();++iter){
//		cerr <<"???"<<endl;
		evs.pb(mp(iter->first.first,iter->second));
		evs.pb(mp(iter->first.second,-iter->second));
	}
	sort(evs.begin(),evs.end());
	int bal = 0;
	for (int i=0;i<evs.size();i++){
//		cerr << "!"<<i << endl;
		bal += evs[i].second;
		if (bal > 0)
			ans[1] += (evs[i+1].first - evs[i].first)*1LL*coef;
		if (bal < 0)
			ans[0] += (evs[i+1].first - evs[i].first)*1LL*coef;
	}	
}

struct event{
	int l,r,x;
	int c;
	bool add;
	event(){
	}
	event(int l,int r,int x,int c,bool add):l(l),r(r),x(x),c(c),add(add){
	}
	bool operator<(const event& r) const{
		if (x != r.x)
			return x < r.x;
		return add > r.add;
	}
};

vector<event> ev;


void solve(){
	l.clear();
	sort(ev.begin(),ev.end());
	for (int i=0;i+1<ev.size();i++){
	//	cerr << i << endl;
		if (ev[i].add)
			l.insert(mp(mp(ev[i].l,ev[i].r),ev[i].c*2-1));
		else{
			assert(l.find(mp(mp(ev[i].l,ev[i].r),ev[i].c*2-1)) != l.end());
			l.erase(l.find(mp(mp(ev[i].l,ev[i].r),ev[i].c*2-1)));
		}
	//	cerr <<"!!!"<<i<<endl;
		calc(ev[i+1].x - ev[i].x);
	}
}


int x[5000];
int y[5000];
int r[5000];
int color[5000];
int n;


int down(int x,int to){
	return x - ((abs(x)^to)&1);
}

int up(int x,int to){
	return x + ((abs(x)^to)&1);
}


int div2(int x){
	if (x%2)
		return (x-1)/2;
	return x/2;
}



void pushnech(int x,int y,int r,int c){
	ev.pb(event(div2(up(x-y-r,1)),div2(down(x-y+r,1))+1,div2(up(x+y-r,1)),c,1));
	ev.pb(event(div2(up(x-y-r,1)),div2(down(x-y+r,1))+1,div2(down(x+y+r,1))+1,c,0));
}

void pushch(int x,int y,int r,int c){
	ev.pb(event(div2(up(x-y-r,0)),div2(down(x-y+r,0))+1,div2(up(x+y-r,0)),c,1));
	ev.pb(event(div2(up(x-y-r,0)),div2(down(x-y+r,0))+1,div2(down(x+y+r,0))+1,c,0));
}



void gennech(){
	ev.clear();
	for (int i=0;i<n;i++)
		pushnech(x[i],y[i],r[i],color[i]);	
}

void gench(){
	ev.clear();
	for (int i=0;i<n;i++)
		pushch(x[i],y[i],r[i],color[i]);	
}






int main(){
  #ifdef LOCAL
    freopen("dominace.in","r",stdin);
    freopen("dominace.out","w",stdout);
  #endif
  	scanf("%d %d",&n,&n);
	scanf("%d",&n);
	for (int i=0;i<n;i++){
		char c;
		scanf(" %c %d %d %d",&c,&x[i],&y[i],&r[i]);
		color[i] = (c == 'B');
	}
	gennech();
	solve();
	gench();
	solve();
	cout << ans[0] <<" "<<ans[1] << endl;
	
	return 0;

}