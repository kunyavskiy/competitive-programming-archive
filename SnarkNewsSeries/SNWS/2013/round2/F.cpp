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

int a[(1<<20)+100];

int main(){
    #ifdef LOCAL
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif

    a[0] = 1;

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++){
    	for (int j = 0; j < (1<<(i-1)); j++){
    		a[j] *= 2;
    		a[j]--;
    	}
    	for (int j = (1<<(i-1)); j < (1<<i); j++){
    		a[j] = a[j - (1<<(i-1))] + 1;
    	}
    }

    for (int i = 0; i < (1<<n); i++)
    	printf("%d%c",a[i]," \n"[i==(1<<n)-1]);


    return 0;
} 