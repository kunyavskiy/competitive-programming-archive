#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>
#define mp make_pair
#define pb push_back

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "ROWCOLOP"

typedef long long ll;
typedef long double ld;

ll a[4000000];
ll b[4000000];

int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
    int n,q;
    scanf("%d %d",&n,&q);

    for (int i = 0; i < q; i++){
    	int c,x;
    	if (scanf(" RowAdd %d %d",&c,&x) == 2)
    		a[c-1] += x;
    	else {
    		scanf(" ColAdd %d %d",&c,&x);
    		b[c-1] += x;
    	}
    } 

    cout << *max_element(a,a+n) + *max_element(b,b+n) << endl;
      
  return 0;
}