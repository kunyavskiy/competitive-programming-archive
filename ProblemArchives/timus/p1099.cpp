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

const int MAXN = 222;

vector<int> g[MAXN];
int mt[MAXN];
int n;

int p[MAXN];
bool used[MAXN];
int base[MAXN];
bool curused[MAXN];


int lca (int a, int b) {
    memset(curused,0,sizeof(curused));
    for (;;) {
        assert(a != -1);
        a = base[a];
        curused[a] = true;
        if (mt[a] == -1)  break; 
        a = p[mt[a]];
    }
    for (;;) {
        assert(b != -1);
        b = base[b];
        if (curused[b])  return b;
        b = p[mt[b]];
    }
}

void markpath(int v,int base,int b){
    while ( ::base[v] != base) {
        curused[ ::base[v]] = curused[ ::base[mt[v]]] = true;
        p[v] = b;
        b = mt[v];
        assert(b != -1);
        v = p[mt[v]];
        assert(v != -1);
    }

}

void recolor(int v){
    if (v == -1)
        return;
    assert(p[v] != -1);
    mt[v] = p[v];
    int temp = mt[p[v]];
    mt[p[v]] = v;
    recolor(temp);
}


int markcycle(int x,int y){
    int nb = lca(x,y);
    memset(curused,0,sizeof(curused));
    markpath(x,nb,y);
    markpath(y,nb,x); 
    return nb;
}


void find(int start){
    queue<int> q;
    q.push(start);

    for (int i = 0; i < n; i++)
        used[i] = 0, p[i] = -1, base[i] = i;

    while (!q.empty()){
        int v = q.front();
        q.pop();
        for (int i = 0; i < (int)g[v].size(); i++){
            int to = g[v][i];
            if (base[v] == base[to] || mt[v] == to)
                continue;
            if (to == start || (mt[to] != -1 && p[mt[to]] != -1)){
                int nb = markcycle(to,v);
                for (int i = 0; i < n; i++)
                    if (curused[base[i]]){
                        base[i] = nb;
                        if (!used[i]){
                            q.push(i);
                            used[i] = true;
                        }
                    }
                continue;
            }
            if (p[to] == -1){
                p[to] = v;
                if (mt[to] == -1){  
                    recolor(to);
                    return;
                }
                to = mt[to];
                used[to] = true;
                q.push(to);
            }
        }
    }
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    scanf("%d",&n);

    for (int a,b; scanf("%d %d",&a,&b) == 2;){
        --a,--b;
        g[a].pb(b);
        g[b].pb(a);
    }

    memset(mt,-1,sizeof(mt));        
    int ans = 0;
    for (int i = 0; i < n; i++)
        if (mt[i] == -1)
           find(i);

    for (int i = 0; i < n; i++)
        ans += (mt[i] != -1);

    printf("%d\n",ans);
    for (int i = 0; i < n; i++)
        if (mt[i] > i)
            printf("%d %d\n",i+1,mt[i]+1);       
    return 0;
}

/*
36
6 25
16 24
15 5
29 35
21 29
20 25
2 8
34 28
19 33
8 13
11 28
36 11
31 19
26 30
30 21
15 10
18 14
22 12
21 22
9 3
1 24
34 4
23 17
17 31
1 26
2 5
16 36
27 20
34 13
14 9
18 7
23 7
4 35
10 9
14 6
21 6
32 3
12 27
*/
