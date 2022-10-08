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
    if (b == 0)
        return 1;
    if (b & 1)
        return (pow(a,b-1)*1LL*a)%MOD;
    int temp = pow(a,b>>1);
    return (temp*1LL*temp)%MOD;      
}



int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    int k,w;

    cin >> k >> w;

    int ans = pow(k,w);
    int ans2 = 1;

    int temp = 1;

    for (int i = 1; i < k; i++){
        temp = (temp * 1LL* i) % MOD;
        ans2 = ans2 + temp;
        if (ans2 >=MOD)
            ans2 -= MOD;
    }
    
    ans = (ans * 1LL * ans2) % MOD;
    ans *= 2;
    ans %= MOD;



  return 0;
}