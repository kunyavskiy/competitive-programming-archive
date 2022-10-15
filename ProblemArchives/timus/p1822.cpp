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

const int MAXN = 11000;

vector<int> g[MAXN];
int t[MAXN];
int n;


int get(int V,ld x){
    vector<int> v;
    for (int i = 0; i < (int)g[V].size(); i++)
        v.pb(get(g[V][i],x));
    v.pb(0);
    int id = (int)((g[V].size()*x)/100+0.9999999999);
    nth_element(v.begin(),v.begin()+id,v.end());
    return v[id] + t[V];
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    scanf("%d",&n);
    int nt;
    scanf("%d",&nt);
    for (int i = 0; i < n-1; i++){
        int p;
        scanf("%d %d",&p,&t[i+1]);
        g[p-1].pb(i+1);
    }

    ld l = 0;
    ld r = 100;

    for (int it = 0;it < 30;it++){
        if (get(0,(l+r)/2) > nt)
            r = (l+r)/2;
        else 
            l = (l+r)/2;
    }

    cout.precision(15);
    cout << fixed<<l << endl;

    return 0;
}