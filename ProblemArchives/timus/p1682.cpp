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


const int MAXN = 5100000;

int p[MAXN];
int n;

vector<int> g[110000];

int get(int v){
    if (p[v] == v)
        return v;
    return p[v] = get(p[v]);
}

void join(int a,int b){
//    cerr << a <<" "<<b <<" "<<(a+b*b)%n <<" "<<(b+a*a)%n << endl;
    p[get(a)] = get(b);
}

void addedge(int a,int b){
    g[a].pb(b);
    g[b].pb(a);
}



int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    scanf("%d",&n);

    for (int i = 0; i < n; i++){
        addedge(i,(n-(i*1LL*i)%n)%n);
    }

    for (int i = 0; i < n; i++){
        sort(g[i].begin(),g[i].end());
        g[i].erase(unique(g[i].begin(),g[i].end()),g[i].end());
    }

    for (int i = 1; i < MAXN; i++){
        p[i] = i;
        for (int j = 0; j*1LL*n < i; j++)
            for (int k = 0; k < (int)g[i%n].size(); k++){
                int to = j*n+g[i%n][k];
                if (to != 0 && to < i){
                    if (get(to) == get(i)){
                        printf("%d\n",i);
                        return 0;
                    }
                    join(to,i);
                }
            }
    }

    printf("-1\n");

    return 0;
}