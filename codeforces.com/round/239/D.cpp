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

#if ( ( _WIN32 || __WIN32__ ) && __cplusplus < 201103L)
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "D"

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




struct MinStack {
	int v[410];
    int a[410];
    int ptr;

    MinStack(){a[0] = 1e9; ptr = 0;}

    void push(int x){
        v[ptr]=x;
        a[ptr+1] = min(a[ptr],x);
        ptr++;
    }

    int pop(){
    	ptr--;
    	return v[ptr];
    }

    bool empty() {return ptr==0;}    
    int get() {return a[ptr];}
    int size() {return ptr;}
    void clear(){
    	ptr=0;
    }
};

struct MinQueue {
    MinStack a, b;
    
    void pop(){
        if (b.empty()){
            while (!a.empty())
            b.push(a.pop());
        }
        assert(b.size());
        b.pop();
    }
    void push(int x){a.push(x);}
    int get(){return min(a.get(), b.get());}
    int size(){return a.size() + b.size();}
    void clear() {a.clear(); b.clear();}
};

const int MAXC = 160010;
const int MAXN = 400;

set<int> used[MAXC];
int a[MAXN][MAXN];

int bad[MAXN];
int n,m;
MinQueue q;

int findmax(){
    int ans = 0;
    q.clear();
    for (int r = 0; r < m; r++){
        q.push(bad[r]);
        while (q.get() <= r && q.size()) q.pop();
        ans = max(ans, q.size());
    }
    return ans;
}

int any[MAXC];

int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

    while (scanf("%d%d",&m,&n) == 2){
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++){
                scanf("%d",&a[j][i]);
//                a[i][j] = (rand()<<2) ^ rand();
            }

        int ans = 0;
        for (int up = 0; up < n && (n - up) * m > ans; up++){
        	int anyptr = 0;
            for (int i = 0; i < m; i++)
                bad[i] = m;
            int cur = m;
            for (int down = up; down < n && (n - up) * cur > ans; ++down){
                for (int i = 0; i < m; i++) if (bad[i] != i){
                    int val = a[down][i];
                    set<int>::iterator iter = used[val].lower_bound(i);
                    if (iter != used[val].end())
                        bad[i] = min(bad[i], *iter);
                    if (iter != used[val].begin()){
                        --iter;
                        bad[*iter] = min(bad[*iter], i);
                    }
                    if (used[val].empty())
                    	any[anyptr++] = val;
                    used[val].insert(iter,i);
                }
                cur = findmax();
                ans = max(ans, (down - up + 1) * cur);
            }
            for (int i = 0; i < anyptr; i++)
                used[any[i]].clear();
        }
        printf("%d\n", ans);
    }      
    return 0;
}