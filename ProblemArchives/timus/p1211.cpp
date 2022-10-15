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
    #undef assert
    #define assert(x) if (!(x)) throw 1
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

int next[26000];
int used[26000];
int n;

void solve(){
    scanf("%d",&n);
    memset(used,0,sizeof(used));

    for (int i = 0; i < n; i++)
        scanf("%d",&next[i]), --next[i];

    bool f0 = false;

    for (int i = 0; i < n; i++){
        if (next[i] == -1){
            if (f0){
                cout <<"NO" << endl;
                return;
            }
            f0 = true;
            used[i] = i+1;
            continue;
        }

        used[i] = i+1;
        int j;
        for (j = next[i]; j != -1 && !used[j]; j = next[j]){
            used[j] = i+1;
        }

        if (j != -1 && used[j] == i+1){
            printf("NO\n");
            return;
        }            
    }

    printf("YES\n");
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int t;
    scanf("%d",&t);

    for (int i = 0; i < t; i++)
        solve();

    return 0;
}