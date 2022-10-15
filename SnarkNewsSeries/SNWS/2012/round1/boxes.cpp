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

#define taskname "boxes"

#define norm(x,y) (((y) >= n)?(x):(y))

using namespace std;

typedef long long int64;
typedef long double ld;

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif

    int n,x,y;
    cin >> n >> x >> y;
    --x,--y;
    
    for (int i = 1;; i++){
        int x1 = x-!!(x&((1<<i)-1))*(1<<(i-1));
        int y1 = y-!!(y&((1<<i)-1))*(1<<(i-1));
        if (x1 == y1){
            printf("%d %d\n",x1+1,y+1);
            break;
        }
        printf("%d %d %d %d\n",x1+1,min(n,norm(x1,x1+(1<<(i-1))+1)),y1+1,norm(y1,y1+(1<<(i-1)))+1);
        x = x1;
        y = y1;
    }
	return 0;
} 