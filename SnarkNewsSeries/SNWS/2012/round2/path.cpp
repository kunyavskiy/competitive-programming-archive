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

#define taskname "path"

using namespace std;

typedef long long ll;
typedef long double ld;

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif

    int n;
    int l,r;
    ll vl,vr;

    vl = vr = 0;
    l = r = 1;

    scanf("%d",&n);

    for (int i = 0; i < n; i++){
        int l1,r1;
        scanf("%d %d",&l1,&r1);
        int vl1 = min(vl + abs(l - r1) + abs(r1 - l1), vr + abs(r - r1) + abs(r1 - l1));
        int vr1 = min(vl + abs(l - l1) + abs(r1 - l1), vr + abs(r - l1) + abs(r1 - l1));
        l = l1, r = r1;
        vl = vl1, vr = vr1;
    }

    cout << min(vl+abs(l-n),vr+abs(r-n)) + (n-1) << endl;
	return 0;
} 