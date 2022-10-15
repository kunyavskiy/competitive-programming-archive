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

using namespace std;

typedef long long ll;
typedef long double ld;

const int MAXN = 110000;

ll a[MAXN];
ll b[MAXN];
int n;

pair<ll,ll> c[MAXN];

bool check(int t){
	for (int i = 0; i < n; i++)
		c[i] = mp(a[i] + t * b[i], b[i]);
	sort(c,c+n);
	for (int i = 1; i < n; i++){
		if (c[i] == c[i-1])
			continue;
		if (c[i].first == c[i-1].first || c[i].second < c[i-1].second)
			return false;
	}
	return true;
}

int main(){
    #ifdef LOCAL
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif

    scanf("%d",&n);
    for (int i = 0; i < n; i++)
    	scanf(LLD" "LLD,&a[i],&b[i]);

    int l = -1;
    int r = (1<<30)-10;

    while (r - l > 1){
    	int m = (l+r)/2;
    	
    	if (check(m))
    		r = m;
    	else
    		l = m;
    }

    cout << r << endl;

    return 0;
} 