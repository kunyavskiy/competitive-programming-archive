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

#define taskname "boattrip"

using namespace std;

typedef long long ll;
typedef long double ld;

const int MAXN = 1000;
vector<int> g[MAXN];

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif

    ll ans = 0;
    int n;
    scanf("%d",&n);

    for (int i = 0; i < n-1; i++){
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        --a,--b;
        g[a].pb(c);
        g[b].pb(c);
        ans += 2*c;
    }

    int mv = 0;

    for (int i = 0; i < n; i++)
        if (g[i].size() == 1)
            mv = max(mv,g[i][0]);

    ans -= 2*mv;

    cout << ans << endl;
	return 0;
} 