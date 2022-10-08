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
#define TASKMOD "large"

typedef long long ll;
typedef long double ld;

void PreCalc(){
}

const int MAXN = 110000;

double p[2][MAXN];

void solve(){
	ll n,x,y;
	scanf(LLD" "LLD" "LLD,&n,&x,&y);
	ll l = 0; 
	l = abs(x) + abs(y);
	assert(l % 2 == 0);
	l /= 2;                    
	for (int i = 0; i < l; i++)
		n -= 4*i+1;
	//eprintf(LLD" "LLD"\n",l,n);
	if (n <= 0){
		printf("0.0000000000\n");
		return;
	}
	if (n >= 4*l + 1){
		printf("1.0000000000\n");
		return;
	}  
                   
	assert(l < MAXN - 10);

	memset(p,0,sizeof(p));
	p[0][0] = 1;

	l = 2*l;


	for (int i = 0; i < n; i++){
		for (int j = 0; j <= l && j <= i; j++){
			if (j < l) 
				p[1][j+1] += p[0][j] / 2.0;
			else
				p[1][j] += p[0][j] / 2.0;
			if (i - j < l) 
				p[1][j] += p[0][j] / 2.0;
			else
				p[1][j+1] += p[0][j] / 2.0;
		}
		for (int j = 0; j <= l+1 && j <= i+1; j++)
			p[0][j] = p[1][j], p[1][j] = 0;
	}

	double ans = 0;
	for (int i = y + 1; i <= l; i++)
		ans += p[0][i];		
	printf("%.10lf\n",ans);
	eprintf("%.10lf "LLD" "LLD" "LLD"\n",ans,y,l,n);
}


int main(){
  freopen(TASKNAME"-"TASKMOD".in","r",stdin);
  freopen(TASKNAME"-"TASKMOD".out","w",stdout);
	
  PreCalc();	

  char buf[1000];
  int testNum;
  gets(buf);
  sscanf(buf,"%d",&testNum);

  for (int testId = 1; testId <= testNum; testId++){
  	if (testId <= 20 || testId >= testNum - 20 || testId % 10 == 0)
	  	eprintf("Test %d\n",testId);
  	printf("Case #%d: ",testId);
  	solve();                        
  }
      
  TIMESTAMP(end);
  return 0;
}