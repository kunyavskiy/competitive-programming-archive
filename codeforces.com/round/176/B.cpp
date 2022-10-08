//#include <iostream>
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
#include <sstream>
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

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "B"

typedef long long ll;
typedef long double ld;


const int MAXN = 1000010;

int n;
int a[2*MAXN];

int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    //freopen(TASKNAME".out","w",stdout);
  #endif

    scanf("%d",&n);
    int shift = 1;
    for (int i = 0; i < n; i++)
    	a[i + shift] = i;

    for (int i = 2; i <= n; i++){
    	for (int j = 0; j < n; j += i)
    		swap(a[shift + min(j,n-1)], a[shift-1]);
        swap(a[shift-1], a[shift + n]);	

    	shift++;         
     	//for (int j = 0; j < n; j++)
    	//	eprintf("%d%c",a[shift+j]+1," \n"[j==n-1]);

    }
    

    for (int i = 0; i < n; i++)
    	printf("%d%c",a[shift+i]+1," \n"[i==n-1]);
      
    TIMESTAMP(end);
    return 0;
}