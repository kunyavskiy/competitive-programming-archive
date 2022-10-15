#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <memory.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iterator>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

#define taskname "bonus"

using namespace std;

typedef long long int64;
typedef long double ld;

int pow(int a,int b,int mod){
    if (b == 0)
        return 1%mod;
    if (b & 1)
        return (pow(a,b-1,mod)*1LL*a)%mod;
    return pow((a*1LL*a)%mod,b/2,mod);
}

int sum(int a,int b,int mod){
    if (b == 0)
        return 1%mod;
    if ((b & 1) == 0)
        return (sum(a,b-1,mod) + pow(a,b,mod))%mod;
    int temp = sum((a*1LL*a)%mod,b/2,mod);
    return (temp * 1LL* (1 + a)) % mod;
}

int main(){
    #ifdef LOCAL
        #ifndef taskname
            #error taskname is not defined
        #else
            freopen(taskname".in","r",stdin);
            freopen(taskname".out","w",stdout);
        #endif
    #endif

    int a,b,c;
    cin >> a >> b >> c;

    cout << sum(a, b-1, c) << endl;   
    return 0;
} 