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

#define taskname "experiment"

using namespace std;

typedef long long int64;
typedef long double ld;

const int MAXN = 11000;

int a[MAXN];
int ptr[MAXN];

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif

    int n;
    scanf("%d",&n);
    for (int i = 0; i < n; i++){
        scanf("%d",&a[i]);
        ptr[i] = n-1;
    }

    sort(a,a+n);

    for (int it = 0; it < n; it++){
        int pos = 0;
        for (int j = 1; j < n; j++)
            if (((a[pos] + a[ptr[pos]]+1) >> 1) < ((a[j]+a[ptr[j]]+1)>>1))
                pos = j;
        printf("%d ",(a[pos]+a[ptr[pos]]+1)>>1);
        ptr[pos]--;
    }
	return 0;
} 