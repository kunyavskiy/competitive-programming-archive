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

multiset<int> s;

int main(){
    #ifdef LOCAL
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif

    int n;
    scanf("%d",&n);
    int maxc = 110000;

    for (int i = 0; i < n; i++){
    	int a;
    	scanf("%d",&a);
    	for (;a > 0 && maxc > 0;a--,maxc--){
    		s.insert(i+1);
    	}
    }

    int m;
    scanf("%d",&m);
    for (int i = 0; i < m; i++){
    	int a;
    	scanf("%d",&a);
    	if (a == 0){
    		printf("%d ",*s.begin());
    		s.erase(s.begin());
    	}
    	else
    		s.insert(a);
    }


    return 0;
} 