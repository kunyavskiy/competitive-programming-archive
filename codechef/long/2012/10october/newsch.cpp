// WHAT'S WRONG WITH YOU GUYS??? WTF IS PENTIUM 3??? PLEASE UPGRADE SERVERS! IT'S RIDICULOUS TO TEST SOLUTIONS ON 9-YEAR OLD SYSTEM!"
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
                          

const int MOD = 1000000007;

int pow(int a,int b){
    if (!b) return 1;
    if (b&1) return (pow(a,b-1) * 1LL * a)%MOD;
    int temp = pow(a,b/2);
    return (temp * 1LL * temp) % MOD;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int t;
    scanf("%d",&t);

    while (t-->0){
        int n;
        scanf("%d",&n);
        int res = pow(3,n-1);
        if (n % 2)
            res = (res - 1 + MOD) % MOD;
        else
            res = (res + 1) % MOD;
        res = (res * 3LL) % MOD;
        cout << res << endl;
    }

  return 0;
}