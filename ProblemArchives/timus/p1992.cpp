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
#define eprintf(...) (void)0
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( ( _WIN32 || __WIN32__ ) && __cplusplus < 201103L)
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "1992"

#ifdef LOCAL
static struct __timestamper {
    string what;
    __timestamper(const char* what) : what(what){};
    __timestamper(const string& what) : what(what){};
	~__timestamper(){
        TIMESTAMPf("%s", what.data());
	}
} __TIMESTAMPER("end");
#else 
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;
                           

struct Stack {
	Stack* next;
	int val;
	Stack(Stack* next, int val):next(next), val(val){};
	int top() const { return val; };
	Stack* pop() const { return next; };
};

struct Clone {
	Stack *know, *was;

	Clone(){
		know = was = 0;
	}

	void learn(int x){
		know = new Stack(know, x);
	}
	void rollback(){
		assert(know);
		was = new Stack(was, know->top());
        know = know->pop();
	}
	void relearn(){
		assert(was);
		know = new Stack(know, was->top());
        was = was->pop();
	}
};

Clone cs[1100000];


int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

  	int n;
  	scanf("%d %*d", &n);
  	int ptr = 1;

  	for (int i = 0; i < n; i++){
  		int c, p;
  		char buf[10];
  		scanf("%s%d", buf,&c);
  		if (!strcmp(buf, "learn")) {
  			scanf("%d", &p);
  			cs[c].learn(p);
  		} else if (!strcmp(buf,"rollback"))
  			cs[c].rollback();
  		else if (!strcmp(buf,"relearn"))
  			cs[c].relearn();
  		else if (!strcmp(buf,"clone"))
  			cs[++ptr] = cs[c];
  		else if (!strcmp(buf,"check")){
  			if (cs[c].know)
  				printf("%d\n", cs[c].know->top());
  			else
  				printf("basic\n");
  		}
  	}
  return 0;
}