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

#define TASKNAME "C"

typedef long long ll;
typedef long double ld;

const int MAXN = 1100000;

stack<int> st;
int a[MAXN];
int n;


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

    scanf("%d",&n);
  	for (int i = 0; i < n; i++){
  		scanf("%d",&a[n-i-1]);
  	}
  	int t;
  	scanf("%d",&t);
  	for (int i = 0; i < t; i++){
  		int x;
  		scanf("%d",&x);
  		a[n-x] = -a[n-x];
  	}

  	for (int i = 0; i < n; i++){
  		if (a[i] < 0)
  			st.push(-a[i]);
  		else {
  			if (!st.empty() && st.top() == a[i])
  				st.pop();
  			else
  				a[i] *= -1, st.push(-a[i]);
  		}
  	}

  	if (!st.empty())
  		printf("NO\n");
  	else {
  		printf("YES\n");
  		for (int i = 0; i < n; i++)
  			printf("%d%c",a[n-i-1]," \n"[i==n-1]);
  	}

      
  TIMESTAMP(end);
  return 0;
}