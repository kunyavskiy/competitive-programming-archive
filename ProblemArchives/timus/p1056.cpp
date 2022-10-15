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
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

const int MAXN = 11000;

vector<int> g[MAXN];
int val[MAXN];
int d[MAXN];



int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int n;
    scanf("%d",&n);
    for (int i = 1; i < n; i++){
        int p;
        scanf("%d",&p);
        g[i].pb(p-1);
        g[p-1].pb(i);
    }

    int mv = 0;
    queue<int> q;

    for (int i = 0; i < n; i++){
        if (g[i].size() == 1)
            q.push(i), val[i] = 1;
        d[i] = g[i].size();
    }

    for (;!q.empty();){
        int v = q.front();
        q.pop();
        mv = max(mv,val[v]);

        for (int i = 0; i < g[v].size(); i++){
            int to = g[v][i];
            d[to]--;
            if (d[to] == 1){
                val[to] = val[v]+1;
                q.push(to);
            }
        }
    }


    for (int i = 0; i < n; i++)
        if (val[i] == mv)   
            printf("%d ",i+1);

    return 0;
}