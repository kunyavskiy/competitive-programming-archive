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
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "A"
#define TASKMOD "large"

typedef long long ll;
typedef long double ld;

const int MOD = 1000002013;

void PreCalc(){
}

enum EventTy {_in,_out};

bool outFirst;

struct Event{
	EventTy type;
	int st;
	int cnt;
	Event(EventTy type,int st,int cnt):type(type),st(st),cnt(cnt){};
	bool operator<(const Event& r) const{
		if (st != r.st)
			return st < r.st;
		return ((type < r.type) ^ outFirst) && type != r.type;
	}
};

int getsum(int len){
	return (len * 1LL * (len + 1)/2) % MOD;
}

void solve(){
	int n,m;
	scanf("%d %d",&n,&m);
	vector<Event> v;
	int ans = 0;
	for (int i = 0; i < m; i++){
		int a,b,c;
		scanf("%d %d %d",&a,&b,&c);
		v.pb(Event(_in,a,c));
  	    v.pb(Event(_out,b,c));
  	    ans = (ans + (MOD - getsum(abs(b - a))) * 1LL * c) % MOD;
	}

	stack<Event> st;

	for (int i = 0; i < (int)v.size(); i++){
		outFirst = !st.empty() && st.top().type == _out;
		sort(v.begin()+i,v.end());
	    while (!st.empty() && st.top().type != v[i].type && v[i].cnt > 0){
	    	int usedcnt = min(v[i].cnt, st.top().cnt);
	    	st.top().cnt -= usedcnt;
	    	v[i].cnt -= usedcnt;
	    	ans = (ans + getsum(abs(st.top().st - v[i].st)) * 1LL * usedcnt) % MOD;
	    	if (st.top().cnt == 0)
	    		st.pop();
	    }
	    if (v[i].cnt)
	    	st.push(v[i]);
	}
	printf("%d\n",ans);
}


int main(){
  freopen(TASKNAME"-"TASKMOD".in","r",stdin);
  freopen(TASKNAME"-"TASKMOD".out","w",stdout);
	
  PreCalc();	
  TIMESTAMP(PreCalc);

  char buf[1000];
  int testNum;
  gets(buf);
  sscanf(buf,"%d",&testNum);

  for (int testId = 1; testId <= testNum; testId++){
  	if (testId <= 20 || testId >= testNum - 20 || testId % 10 == 0)
	  	TIMESTAMPf("Test %d",testId);
  	printf("Case #%d: ",testId);
  	solve();                        
  }
      
  TIMESTAMP(end);
  return 0;
}