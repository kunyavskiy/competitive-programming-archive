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

int n;
pair<int,int> s[110000];

int a[110000];
int b[110000];

void setval(int pos,int aval,int bval){
	if (aval == -1) aval = s[pos].first - bval;
	if (bval == -1) bval = s[pos].first - aval;
	//assert(aval + bval == s[pos].first);
	a[s[pos].second] = aval;
	b[s[pos].second] = bval;
}

int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  	scanf("%d",&n);
  	for (int i = 0; i < n; i++)
  		scanf("%d",&s[i].first),s[i].second = i;

  	sort(s,s+n);       

  	int maxA,maxB;
  	int diffA,diffB;

  	maxA = s[0].first;
  	maxB = 0;
  	diffA = diffB = 1;
  	setval(0,maxA,maxB);

  	for (int i = 1; i < n; i++){
  		int df = s[i].first - s[i-1].first;
  		if (df > 1 || (i >= n-2)){
  			maxA += 1;
  			maxB += df - 1;
  			diffA++,diffB++;
  			setval(i,maxA,maxB);
  			continue;
  		}
  		df = s[i+1].first - s[i].first;
  		if (df > 1){
  			if (diffA < diffB)
  				diffA++,maxA++;
  			else
  				diffB++,maxB++;
  			setval(i,maxA,maxB);
  			continue;
  		}
  		df = s[i+2].first - s[i+1].first;
  		setval(i,maxA+1,-1);
  		setval(i+1,-1,maxB+2);
	    setval(i+2,-1,maxB+1);
	    maxB += max(a[s[i].second],maxB+2);
	    maxA += a[s[i+2].second];
	    i += 2;
	    diffA += 2;
	    diffB += 2;
  	}

  	puts("YES");
  	for (int i = 0; i < n; i++)
  		printf("%d%c",a[i]," \n"[i==n-1]);
  	for (int i = 0; i < n; i++)
  		printf("%d%c",b[i]," \n"[i==n-1]);

      
    TIMESTAMP(end);
    return 0;
}