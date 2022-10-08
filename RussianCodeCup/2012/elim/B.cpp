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

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

vector<int> s;

vector<int> g[110000];
vector<int> l[110000];

int c1,c2;
int n;

bool go(int v,int p){
    if (v == c2){
        s.pb(c2);
        return true;
    }
    s.pb(v);
    for (int i = 0; i < (int)g[v].size(); i++)
        if (g[v][i] != p && go(g[v][i],v))
            return true;
    s.pop_back();
    return false;
}

int get(int a,int b){
    for (int i = 0;i < (int)g[a].size(); i++)
        if (g[a][i] == b)
            return l[a][i];
    assert(false);
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    scanf("%d",&n);
    scanf("%d %d",&c1,&c2);
    --c1,--c2;
    for (int i = 0; i < n-1; i++){
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        --a,--b;
        g[a].pb(b);
        g[b].pb(a);
        l[a].pb(c);
        l[b].pb(c);
    }
    go(c1,-1); 


    int a,b,c,d,e;

    a = get(c1,s[1]);
    c = get(c2,s[s.size()-2]);
    b = 1<<30;

    for (int i = 1; i < (int)s.size()-2; i++)
        b = min(b, get(s[i],s[i+1]));

    d = e = -(1<<30);

    for (int i = 0; i < (int)g[c1].size(); i++)
        if (g[c1][i] != s[1])
            d = max(d,l[c1][i]);

    for (int i = 0; i < (int)g[c2].size(); i++)
        if (g[c2][i] != s[s.size()-2])
            e = max(e,l[c2][i]);


    if (s.size() == 2){
        int ans = a;
        ans = max(ans, a + min(d,e));
        cout << ans << endl;
        return 0;
    } 

                                                                 
    int ans = min(a,min(b,c));
    ans = max(ans, min(a,min(b,c)) + min(d,e));
    ans = max(ans, min(min(a,b) + d,c));
    ans = max(ans, min(a,min(b,c)+e));
    ans = max(ans, min(a,c));

    cout << ans << endl;
    return 0;
}