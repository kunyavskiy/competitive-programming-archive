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


vector<int> v[110000];

int val[110000];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    memset(val,128,sizeof(val));

    int n,R;
    scanf("%d %d",&n,&R);

    int cnt = 0;

    set<pair<int,int> > s;

    for (int i = 0; i < n; i++){
        int x;
        scanf("%d",&x);
        int id;
        if (s.empty() || s.begin()->first >= x-R)
            id = cnt++;
        else 
            id = s.begin()->second;
        s.erase(mp(val[id],id));
        val[id] = x;
        s.insert(mp(val[id],id));
        v[id].pb(i);        
    }

    printf("%d\n",cnt);

    for (int i = 0; i < cnt; i++){         
        printf("%d",v[i].size());
        for (int j = 0; j < (int)v[i].size(); j++)
            printf(" %d",v[i][j]+1);
        printf("\n");
    }                       

    return 0;
}