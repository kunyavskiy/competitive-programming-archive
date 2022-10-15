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

#define TASKNAME "1253"

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


#ifndef LOCAL
#undef assert
#define assert(x) if (!(x)) { int t = 1/0; printf("%d\n", t);}
#endif

char buf[1024*1024];
int ptr = 0;

vector<string> v;


int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

    int n;        
    gets(buf);
    scanf("%d",&n);
    string cur;
    while (gets(buf)){
        cur += buf;
        if (cur[cur.size()-1] == '#') {
            cur.erase(cur.end()-1);
            v.pb(cur);
//            eprintf("|%s|\n", cur.data());
            cur = "";
        } else
            cur += "\n";
    }

    vector<pair<int, int> > st;
    st.pb(mp(0, 0));

    while (!st.empty() && ptr <= 1000000) {
        const string& s = v[st.back().first];
        int& pos = st.back().second;
        if (pos == (int)s.size()){
            st.pop_back();
            continue;
        }
        if (s[pos] != '*'){
            buf[ptr++] = s[pos++];
            continue;
        }
        pos++;
        int id = s[pos] - '0';
        pos++;
        assert(1 <= id && id <= (int)v.size());
        st.pb(mp(id-1, 0));
        if (st.size() >= 10)
        	ptr = 1000010;
    }

    if (ptr > 1000000)
        printf("#");
    else
        buf[ptr++] = 0, printf("%s", buf);
    return 0;
}
