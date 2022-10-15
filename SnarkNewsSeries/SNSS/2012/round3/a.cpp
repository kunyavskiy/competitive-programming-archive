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

#define taskname "a"

using namespace std;

typedef long long ll;
typedef long double ld;

int main(){
    #ifdef LOCAL
        freopen(taskname".in","r",stdin);
        freopen(taskname".out","w",stdout);
    #endif

    ll sum;

    while (scanf(LLD,&sum) == 1){
        if (sum == 0)
            break;

        ll a = (ll)sqrt(2*sum);

        while (a*(a+1)/2 <= sum)
            a++;
        while (a*(a-1)/2 > sum)
            a--;

        printf(LLD" "LLD"\n",a,a*(a+1)/2 - sum);
    }


    return 0;
} 