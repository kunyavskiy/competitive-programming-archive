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

#ifndef M_PI
	#define M_PI 3.1415926535897932384626433832795
#endif


#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

vector<int> res[1100];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    int n;
    cin >> n;
    for (int ans = 2*n; ans >= 0; --ans){
        if (ans * (ans-1) <= 2*n){
            int cnt = 1;
            for (int i = 0; i < ans; i++)
                for (int j = i+1; j < ans; j++)
                   res[i].pb(cnt),res[j].pb(cnt),cnt++;
            printf("%d",ans);
            for (int i = 0; i < ans; i++){
                printf("\n%d",ans-1);
                for (int j = 0; j < ans-1; j++)
                    printf(" %d",res[i][j]);
            }
            return 0;
        }
    }
    assert(false);
  return 0;
}