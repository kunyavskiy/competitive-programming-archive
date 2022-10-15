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
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

const int MAXN = 110000;

vector<pair<int,int> > gl[MAXN],gc[MAXN],gp[MAXN];

ll d[MAXN][2];

int n,m;

set<pair<ll,pair<int,int> > > s;


void update(int v,vector<pair<int,int> >& g,int ver,ll d0){
   for (int i = 0; i < g.size(); i++){
       int to = g[i].first;
       int len = g[i].second;
       if (d[to][ver] > d0 + len){
           s.erase(mp(d[to][ver],mp(to,ver)));
           d[to][ver] = d0 + len;
           s.insert(mp(d[to][ver],mp(to,ver)));
       }
   }
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    cin >> n >> m;

    for (int i = 0; i < m; i++){
       int a,b,c; string s;
       cin >> a >> b >> c >> s;
       --a,--b;
       if (s[0] == 'L')
          gl[a].pb(mp(b,c));
       else if (s[0] == 'C')
          gc[a].pb(mp(b,c)); 
       else {
          assert(s[0] == 'P');
          gp[a].pb(mp(b,c));
       }
    }

    memset(d,63,sizeof(d));
    d[0][1] = 0;
    s.insert(mp(0,mp(0,1)));


    for (;!s.empty();){
        int v = s.begin()->second.first;
        int ver = s.begin()->second.second;
        s.erase(s.begin());


        if (v == n-1){
            printf("Online\n");
            cout<<d[v][ver]<<endl;
            return 0;
        }

        if (ver){
            update(v,gl[v],ver,d[v][ver]);
        }

        update(v,gc[v],ver,d[v][ver]);
        update(v,gp[v],0,d[v][ver]);
    }

    printf("Offline\n");
    return 0;
}