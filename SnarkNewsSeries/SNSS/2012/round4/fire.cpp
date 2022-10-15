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

typedef long long int64;
typedef long double ld;


void solve(){
    int a,b;
    cin >> a >> b;

    int ha = 4*a;
    int hb = 27*b;

    int cnt1 = 0;
    int cnt2 = 0;

    while (ha > 0 && hb > 0){
        if (cnt1 * 41 < cnt2 * 107){
            cnt1++;
            hb -= min(ha, a);
        }
        else if (cnt1 * 41 > cnt2 * 107){
            cnt2++;
            ha -= (hb+26)/27;
        }
        else {
            cnt1++,cnt2++;
            int t = hb;
            hb -= min(ha, a);
            ha -= (t+26)/27;
        }
    }

    if (ha <= 0 && hb <= 0)
        puts("Elimination");
    else if (ha <= 0)
        puts("Newbie");
    else
        puts("Master");

}

int main(){
    #ifdef LOCAL
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif

    int t;
    scanf("%d",&t);

    while (t-->0)
        solve();


    return 0;
} 