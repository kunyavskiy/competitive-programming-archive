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
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "A"

typedef long long ll;
typedef long double ld;

const int SHIFT = 100;

int val[SHIFT*2][SHIFT*2];


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
  	int n;
  	scanf("%d",&n);   
  	val[SHIFT][SHIFT] = n;
  	int iter = 0;
  	while (true){
  		bool any = false;

  		for (int i = 1; i < 2*SHIFT-1; i++){
  			int* v1 = val[i-1]+1;
  			int* v2 = val[i+1]+1;
  			int* v3 = val[i];
  			int* v4 = val[i]+2;
  			int* v5 = val[i]+1;
  			int* end = val[i] + 2*SHIFT - 1;
  			for (; v5 != end; v5++){
  				if (*v5 >= 4){
  					 (*v1)++;
  					 (*v2)++;
  					 (*v3)++;
  					 (*v4)++;
  					 *v5 -= 4;
  					 any = true;
	  			}
	  			v1++;v2++;v3++;v4++;
	  		}
	  	}
		if (!any)
			break;
	  	iter++;
  	}
  	eprintf("iter = %d\n",iter);
  	int t;
  	scanf("%d",&t);
  	for (int i = 0; i < t; i++){
  		int x,y;
  		scanf("%d %d",&x,&y);
  		if (abs(x) > SHIFT || abs(y) > SHIFT)
  			printf("0\n");
  		else
  			printf("%d\n",val[x+SHIFT][y+SHIFT]);
  	}
    TIMESTAMP(end);
    return 0;
}