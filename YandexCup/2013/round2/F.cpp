#include <iostream>
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

#define TASKNAME "F"

typedef long long ll;
typedef long double ld;


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
  	
    int a,b,c;
    scanf("%d %d %d",&a,&b,&c);
    a -= max(a/2-1,0) * 2;
    b -= max(b/2-1,0) * 2;
    c -= max(c/2-1,0) * 2;

    string need;
    cin >> need;

    vector<pair<int,int> > v;
    for (int i = 0; i < a; i++) v.pb(mp(0,1));
    for (int i = 0; i < b; i++) v.pb(mp(0,2));
    for (int i = 0; i < c; i++) v.pb(mp(1,2));
    sort(v.begin(),v.end());

    do {
       string s = "RGB";
       for (int i = 0; i < (int)v.size(); i++)
         	swap(s[v[i].first],s[v[i].second]);
       if (s == need){
         	printf("Yes\n");
         	return 0;
       }
    } while (next_permutation(v.begin(),v.end()));
      
    printf("No\n");
    TIMESTAMP(end);
    return 0;
}