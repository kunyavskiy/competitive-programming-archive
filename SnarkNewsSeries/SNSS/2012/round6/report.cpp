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

int a[110];
int n;

int main(){
    #ifdef LOCAL
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif
    scanf("%d",&n);
    for (int i = 0; i < n; i++){
        scanf("%d",&a[i]);
    }

    sort(a,a+n);
    a[n-1] *= -1;

    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += a[i];

    if (sum > 0)
        printf("YES\n");
    else
        printf("NO\n");


    return 0;
} 