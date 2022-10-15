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

#define taskname "sequence"

using namespace std;

typedef long long ll;
typedef long double ld;

ll fib[100];
ll ans[100];
ll len[100];

ll n;
int cnt;


ll solve(ll n){
        if (n == 0)
            return 0;
        if (n == 1)
            return 1;
        if (n <= 3)
            return 2;
        fib[0] = 0;
        len[0] = 0;
        ans[0] = 0;
        fib[1] = 1;
        fib[1] = 1;
        ans[1] = 1;
        for (cnt=2;;cnt++){
            fib[cnt] = fib[cnt-1] + fib[cnt-2];
            ans[cnt] = ans[cnt-1] + fib[cnt-2] + ans[cnt-2];
            len[cnt] = len[cnt-1] + 2*fib[cnt-2] + len[cnt-2];
            if (len[cnt] > n)
                break;
        }
        cerr << len[cnt-1];
        ll l = (n - fib[cnt-1])/cnt;
        return ans[cnt-1] + l + solve(n - 2*l - 2*fib[cnt-2]-len[cnt-1]);
}

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif
        cin >> n;
        cout << solve(n) << endl;

 	    return 0;
} 