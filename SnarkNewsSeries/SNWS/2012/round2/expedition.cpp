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

#define taskname "expedition"

using namespace std;

typedef long long int64;
typedef long double ld;

int a[1100];

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif

    int n,m;
    scanf("%d %d",&n,&m);

    for (int i = 0; i < m; i++)
        scanf("%d",&a[i]);

    sort(a,a+m);

    if (m < n){
        printf("0\n");
        return 0;
    }

    int one = m/(n+1);
    int ans = 0;

    for (int j = m-one; j < m; j++){
        ans += a[j];
    }

    printf("%d\n",ans);

	return 0;
} 