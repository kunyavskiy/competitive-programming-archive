//#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "D"

typedef long long ll;
typedef long double ld;


struct linear{
	ll a,b;

	ll at(ll x){
		return a * x + b;
	}
	
	linear(ll a,ll b):a(a),b(b){}
	linear(){}
	bool operator<(const linear& r) const{
		if (a != r.a) return a < r.a;
		return b < r.b;
	}
};

linear operator+(const linear& a,const linear& b){
	return linear(a.a + b.a, a.b + b.b);
}

vector< pair<int,linear> > v;



void addseg(ll l,ll r,ll t){
	assert(l < r);
	v.pb(mp(t - r, linear(1, -(t-r))));
	v.pb(mp(t - l, linear(-1, (t-l))));	
}

int n,q;


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

    vector< pair<int,int> > events;

    scanf("%d",&q);
    scanf("%d",&n);
    for (int i = 0; i < n; i++){
    	int l,r,t;
    	scanf("%d %d %d",&l,&r,&t);
    	events.pb(mp(l,t+1));
    	events.pb(mp(r,-t-1));
    }

    int last = 0;

    sort(events.begin(),events.end());
    multiset<int> s;

    for (int i = 0; i < (int)events.size(); ){
    	int j = i;
    	while (j < (int)events.size() && events[j].first == events[i].first) j++;
    	if (!s.empty())
    		addseg(last, events[i].first, *s.begin()-1);
		last = events[i].first;
    	for (;i < j; i++)
    		if (events[i].second > 0)
    			s.insert(events[i].second);
    		else
    			s.erase(s.find(-events[i].second));
    }

    v.pb(mp(0,linear(0,0)));
    sort(v.begin(),v.end());

    for (int i = 1; i < (int)v.size(); i++)
    	v[i].second = v[i-1].second + v[i].second;

    vector<pair<int,linear> > _v;

	for (int i = 0; i < (int)v.size(); i++)
		if (i == (int)v.size()-1 || v[i].first != v[i+1].first)
			_v.pb(v[i]);
	v = _v;
                   
	for (int i = 0; i < q; i++){
		int t;
		scanf("%d",&t);
		int id = upper_bound(v.begin(),v.end(), mp(t, linear(1LL<<60,1LL<<60)))-v.begin()-1;
		assert(0 <= id && id < (int)v.size());
		printf(LLD"\n", v[id].second.at(t));
	}

	
        
    TIMESTAMP(end);
    return 0;
}