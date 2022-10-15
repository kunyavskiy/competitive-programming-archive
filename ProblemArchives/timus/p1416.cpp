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

const int MAXN = 501;
int p[MAXN];

int get(int v){
    if (p[v] == v) return v;
    return p[v] = get(p[v]);
}

void join(int a,int b){
    p[get(a)] = get(b);
}

pair<int,pair<int,int> > e[MAXN*MAXN];

vector<int> v;

int n,m;

int solve(int x){
    for (int i = 0; i < n; i++)
        p[i] = i;

    int ans, cnt;
    ans = cnt = 0;

    for (int i = 0; i < m; i++)
        if (i != x && get(e[i].second.first) != get(e[i].second.second)){
            join(e[i].second.first, e[i].second.second);
            v.pb(i);
            ans += e[i].first;
            cnt++;
            if (cnt == n-1)
                return ans;
        }
    return (1<<30);
}



int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif                                                                                                            
    scanf("%d %d",&n,&m);
    for (int i = 0; i < m; i++){
        scanf("%d %d %d",&e[i].second.first,&e[i].second.second,&e[i].first);
        --e[i].second.first;
        --e[i].second.second;
    }

    sort(e,e+m);

    int val = solve(-1);

    if (val == (1<<30)){
        printf("Cost: -1\n");
        printf("Cost: -1\n");
        return 0;
    }

    printf("Cost: %d\n",val);

    val = (1<<30);
                                                                                                        
    for (int i = 0; i < n-1; i++)
        val = min(val,solve(v[i]));

    
    if (val == (1<<30)){
        printf("Cost: -1\n");
        return 0;
    }

    printf("Cost: %d\n",val);

    return 0;
}