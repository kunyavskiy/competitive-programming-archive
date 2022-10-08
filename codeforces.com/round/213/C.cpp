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
#include <numeric>
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

#define TASKNAME "C"

#ifdef LOCAL
static struct __timestamper {
	~__timestamper(){
        TIMESTAMP(end);
	}
} __TIMESTAMPER;
#endif

typedef long long ll;
typedef long double ld;


const int MAXN = 5e7;

int p[MAXN];
vector<int> primes;

vector<int> v;

int last = 1;

const int Primes[] = {2, 3, 5, 7, 11};

const int CNT = 5;

bool check(int x){
    for (int i = 0; i < CNT; i++)
    	while (x % Primes[i] == 0) x /= Primes[i];
	return x == 1;
}

int calcCnt(int a){
	int cnt = 0;
	for (int i = 0; i < CNT; i++)
		if (a % Primes[i] == 0)
			cnt++;
	return cnt;
}

bool cmp(int a, int b){
	return calcCnt(a) > calcCnt(b);
}

int checkSol(vector<int> v, int ptr){
	if ((int)v.size() < ptr) return false;

	sort(v.begin(), v.end(), cmp);
	vector<int> nv;
	vector<int> used(v.size());
	int cnt[CNT];
	memset(cnt, 0, sizeof(cnt));

	while ((int)nv.size() < ptr){
		int best = -1, bv = -1;
		for (int i = 0; i < (int)v.size(); i++)
			if (!used[i]){
			   int temp[CNT];
			   memcpy(temp, cnt, sizeof(cnt));
			   for (int j = 0; j < CNT; j++)
			   	  if (v[i] % Primes[j] == 0)
			   	  	temp[j]++;
			   int value = 0;
			   for (int j = 0; j < CNT; j++)
			   	 value += min(temp[j], (ptr + 1) / 2);
			   value += *min_element(temp, temp + CNT) * 2;
			                                                               
			   if (best == -1 || value > bv){
			      best = i;
			      bv = value;
			   }
			}
	     assert(best != -1);
	     used[best] = 1;
	     nv.pb(v[best]);
	   for (int j = 0; j < CNT; j++){
	   	  if (v[best] % Primes[j] == 0){
	   	  	cnt[j]++;
	   	  }
//	   	  	eprintf("%d ", cnt[j]);
	   }
//	   eprintf("\n");
	}

	v = nv;
		
/*    for (int i = 0; i < CNT; i++){
    	int cnt = 0;
    	for (int j = 0; j < (int)v.size(); j++)
    	    cnt += v[j] % Primes[i] == 0;
		if (cnt < (ptr + 1) / 2){
//		   eprintf("Failed %d\n", Primes[i]);
		   assert(false);
		}
    }*/
    for (int i = 0; i < (int)v.size(); i++)
    	printf("%d ", v[i]);
    return true;
}


bool solve(int ptr){
	while (last <= 2*ptr*ptr){
		if (check(last)) v.pb(last);
		last++;
	}
	return checkSol(v, ptr);
}


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

/*    for (int i = 10; i <= 5000; i++){
        if (solve(i)) eprintf("OK %d\n", i);
        else {
           eprintf("FUCK %d\n", i);
           assert(false);
        }
    }*/

    int n;
    scanf("%d",&n);
    solve(n);
       
      
  return 0;
}