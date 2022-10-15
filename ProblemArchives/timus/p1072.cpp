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
typedef unsigned int uint;

const int MAXN = 100;

vector<uint> mask[MAXN];
vector<uint> ip[MAXN];

vector<int> g[MAXN];

int d[MAXN];      
int p[MAXN];
int s,t;

void print(int v){
    if (v == s){
        printf("%d",v+1);
        return;
    }
    print(p[v]);
    printf(" %d",v+1);
    return;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int n;
    scanf("%d",&n);
                           
    for (int i = 0; i < n; i++){
        int k;
        scanf("%d",&k);

        for (int j = 0; j < k; j++){
            int a,b,c,d;
            scanf("%d.%d.%d.%d",&a,&b,&c,&d);
            ip[i].pb((a<<24)|(b<<16)|(c<<8)|(d<<0));
            scanf("%d.%d.%d.%d",&a,&b,&c,&d);
            mask[i].pb((a<<24)|(b<<16)|(c<<8)|(d<<0));
        }               
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < (int)ip[i].size(); k++)
                for (int l = 0; l < (int)ip[j].size(); l++)
                    if ((ip[i][k] & mask[i][k]) == (ip[j][l] & mask[j][l]))
                        g[i].pb(j);

    for (int i = 0; i < n; i++)
        sort(g[i].begin(),g[i].end()),g[i].erase(unique(g[i].begin(),g[i].end()),g[i].end());

    scanf("%d %d",&s,&t);
    --s,--t;

    memset(d,63,sizeof(d));
    memset(p,-1,sizeof(p));

    d[s] = 0;

    queue<int> q;
    q.push(s);

    for (;!q.empty(); ){
        int v = q.front();
        q.pop();

        for (int j = 0; j < (int)g[v].size(); j++)
            if (d[g[v][j]] > d[v] + 1){
                d[g[v][j]] = d[v] + 1;
                p[g[v][j]] = v;
                q.push(g[v][j]);
            }                  
    }

    if (p[t] == -1){
        printf("No\n");
        return 0;
    }

    printf("Yes\n");
    print(t);      
    return 0;
}