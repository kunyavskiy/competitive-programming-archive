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

const int INF = 1<<29;

pair<int,int> a[110000];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int n,m,k;
    cin >> n >> m >> k;

    for (int i = 1; i <= n; i++){
        a[i] = mp(-INF,INF);
        for (int j = 0; j <= k; j++)
            if (j > i)
                a[i] = max(a[i], mp(m,0));
            else
                a[i] = max(a[i], mp(-a[i-j].second + j, -a[i-j].first));
    } 

    cout << a[n].first <<" "<<-a[n].second << endl;

    return 0;
}