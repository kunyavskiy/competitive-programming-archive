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
typedef pair<int,double> dist_t;

dist_t operator+(dist_t a,dist_t b){
    return dist_t(a.first+b.first,-a.second * b.second);
}

set<pair<dist_t,int> > s;

vector<int> g[110000];
vector<dist_t> l[110000];

dist_t d[110000];
int p[110000];

void print(int x){
    if (d[x].first == 1){
        printf("%d ",x+1);
        return;
    }
    print(p[x]);
    printf("%d ",x+1);
    return ;
}



int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int n,m;
    scanf("%d %d",&n,&m);
    int s,t;
    scanf("%d %d",&s,&t);
    --s,--t;
    for (int i = 0; i < m; i++){
        int x,y,p;
        scanf("%d %d %d",&x,&y,&p);
        --x,--y;
        g[x].pb(y),l[x].pb(dist_t(1,p*0.01-1));
        g[y].pb(x),l[y].pb(dist_t(1,p*0.01-1));
    } 

    for (int i = 0; i < n; i++)
        d[i] = dist_t(1<<30,1e100);

    d[s] = dist_t(1,-1);
    ::s.insert(mp(d[s],s));



    while (! ::s.empty()){
        int v = ::s.begin()->second;
        ::s.erase( ::s.begin());
        for (int i = 0; i < (int)g[v].size(); i++){
            int to = g[v][i];
            if (d[to] > d[v] + l[v][i]){
               ::s.erase(mp(d[to],to));
               d[to] = d[v] + l[v][i];
               p[to] = v;
               ::s.insert(mp(d[to],to));
            }
        }
    }

    cout << d[t].first <<" "<<fixed<<1+d[t].second << endl;
    print(t);    

    return 0;
}