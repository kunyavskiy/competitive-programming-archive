#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

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

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
    #define M_PI 3.1415926535897932384626433832795
    #define prev prev_dsfdfgfhgfh
    #define next next_mkdlsmfdgkl
    #define hash hash_mdfdsgdhgfm
    #undef assert
    #define assert(x) if (!(x)) throw 1
    #define sqrt(x) sqrt((double)(x))
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

set<pair<int,int> > s;

pair<int,int> v[110000];
int n,m;

vector<pair<int,int> > ans;

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    scanf("%d",&m);

    while (true){
        scanf("%d %d",&v[n].first,&v[n].second);
        if (v[n].first == 0 && v[n].second == 0)
            break;
        n++;
    }

    sort(v,v+n);

    int ptr = 0;
    int cov = 0;

    while (true){      
        if (cov >= m)
            break;
        while (ptr < n && v[ptr].first <= cov){
            s.insert(mp(v[ptr].second,v[ptr].first));
            ptr++;
        } 
        if (s.empty() || (--s.end())->first <= cov){
            printf("No solution\n");
            return 0;
        }
        cov = (--s.end())->first;
        ans.pb(mp((--s.end())->second,(--s.end())->first));
    }

    printf("%d\n",ans.size());
    for (int i = 0; i < (int)ans.size(); i++)
        printf("%d %d\n",ans[i].first,ans[i].second);


    return 0;
}