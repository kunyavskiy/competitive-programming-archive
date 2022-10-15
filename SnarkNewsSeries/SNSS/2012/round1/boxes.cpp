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

#define taskname "BOXES"

using namespace std;

typedef long long ll;
typedef long double ld;

int a[110000];

int main(){
    #ifdef LOCAL
        #ifndef taskname
            #error taskname is not defined
        #else
            freopen(taskname".in","r",stdin);
            freopen(taskname".out","w",stdout);
        #endif
    #endif

    int t;
    scanf("%d",&t);

    for (;t-->0;){
        int n;
        scanf("%d",&n);
        for (int i = 0; i < n; i++)
            scanf("%d",&a[i]);
        ll res = 0;
        for (int i = 1; i < n; i++){
            res += max(0,a[i] - a[i-1] - 1);
            a[i] -= max(0,a[i] - a[i-1] - 1);
        }

        for (int i = n-1; i >= 0; i--){
            res += max(0,a[i] - a[i+1] - 1);
            a[i] -= max(0,a[i] - a[i+1] - 1);
        }

        cout << res << endl;
    }


    return 0;
} 