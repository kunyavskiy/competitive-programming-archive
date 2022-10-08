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

#define TASKNAME "D"

typedef long long ll;
typedef long double ld;

const int gr[] = {0,1,2,1,4,3,2,1,5,6,2,1,8,7,5,9,8,7,3,4,7,4,2,1,10,9,3,6,11,12};

/*
map<int,int> gr;

int calcgr(int mask){
	if (!mask) return 0;
	if (gr.find(mask) != gr.end())
		return gr[mask];
	vector<int> used;
	for (int i = 1; i < 30; i++)
		if (mask & (1<<(i-1))){
			int mask1 = mask;
			for (int j = i; j <= 30; j += i)
				mask1 &= ~(1<<(j-1));
			assert(mask1 < mask);
			used.pb(calcgr(mask1));
		}
	sort(used.begin(),used.end());
	used.erase(unique(used.begin(),used.end()),used.end());
	used.pb(1000);
	int gr = 0;
	while (used[gr] == gr) gr++;
	return ::gr[mask] = gr;
}
*/

set<int> nums;



int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

/*  	for (int i = 0; i < 30; i++){
  		eprintf("%d\n",i);
  		printf("%d,",calcgr((1<<i)-1));
  	}*/


  	int n;
  	scanf("%d",&n);

  	nums.insert(1);
  	int g = 1;
  	for (int i = 2; i*i <= n; i++){
  		if (nums.find(i) != nums.end()) continue;
  		int p = 1;
  		ll cur = i;
  		nums.insert(cur);
  		while (cur * i <= n){
  			cur *= i;
  			p++;
  			nums.insert(cur);
  		}
  		g ^= gr[p];
  	} 

  	g ^= ((n - (int)nums.size()) % 2);

  	if (g)
  		printf("Vasya\n");
  	else
  		printf("Petya\n");
      
    TIMESTAMP(end);
    return 0;
}