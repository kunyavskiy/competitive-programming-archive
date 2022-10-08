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

#define TASKNAME "C"
#define TASKMOD "large"

typedef long long ll;
typedef long double ld;

void PreCalc(){
}

const int inf = 1e9;

struct Solver {
	struct Edge {
		int from, to, c;
		int next;
		Edge(int from, int to, int c, int next):from(from), to(to), c(c), next(next){}
	};

	vector<int> first;
	vector<Edge> es;
	int cur;
	vector<int> used;
	int usedver;

	Solver(int n):first(n, -1), cur(0), used(n){
	}
	void adde(int a, int b, int c){
//	    eprintf("%d %d\n", a, b);
		assert(0 <= a && a < (int)first.size());
		assert(0 <= b && b < (int)first.size());
		es.pb(Edge(a, b, c, first[a]));
		first[a] = (int)es.size() - 1;
		es.pb(Edge(b, a, 0, first[b]));
		first[b] = (int)es.size() - 1;
	}



	int dfs(int v, int to){
		if (v == to) return 1;
		if (used[v] == usedver) return 0;
		used[v] = usedver;
		for (int it = first[v]; it != -1; it = es[it].next) {
			if (es[it].c && dfs(es[it].to, to)) {
				es[it].c--;
				es[it^1].c++;
				return true;
			}
		}
		return false;
	}

	int solve(int from, int to){
		usedver++;
		while (dfs(from, to)) {
			cur++;
			usedver++;
		}
		return cur;
	}

};


void solve(){
    int n;
    scanf("%d",&n);
    vector<int> ids(n);
    vector<int> ty(n);
    for (int i = 0; i < n; i++) {
        char c;
        scanf(" %c %d",&c,&ids[i]);
        ty[i] = c == 'E';
    }

    Solver s(n+5);
    s.adde(n+2, n+1, inf);

    int cnt = 0;


    for (int i = 0; i < n; i++){
    	vector<bool> have(2010);
		if (ty[i] == 1) {
		    cnt++;
			s.adde(n+1, n+4, 1);
			s.adde(n+3, i, 1);
			for (int j = i+1; j < n; j++) {
				if (ty[j] == 0 && (ids[j] == ids[i] || ids[i] == 0 || ids[j] == 0) && !have[ids[i] | ids[j]]) 
					s.adde(i, j, 1);
				if (ids[j]) have[ids[j]] = 1;
			}				
			if (!have[ids[i]])
				s.adde(i, n, 1);
		} else {
			for (int j = i-1; j >= 0; j--) {
				if (ids[j]) have[ids[j]] = 1;
			}				
			if (!have[ids[i]])
				s.adde(i, n+2, 1);
			else {
				s.adde(i, n+4, 1);
				s.adde(n+3, n+2, 1);
    		    cnt++;
			}     
		}
    }
    pair<int, int> res;

    for (int i = 0; i <= cnt; i++){
    	if (s.solve(n+3, n+4) == cnt) {
    		printf("%d\n", i);
    		return;
    	}
    	s.adde(n, n+2, 1);
   	}
    puts("CRIME TIME");
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