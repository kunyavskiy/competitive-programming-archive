#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <cstdlib>
#include <cstdio>
#include <stack>
#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <functional>
#include <bitset>
#include <ctime>
#include <cassert>
#define pb push_back
#define mp make_pair      
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
 
typedef long long ll;
typedef long double ld;


const int MAXN = 5100000;

class SumAndProductPuzzle {

int p[MAXN];
vector<int> primes;
int res[MAXN];

public:
    ll getSum(int a, int b) {
        memset(p, 0, sizeof(p));
        p[0] = 0;
        p[1] = 1;

        for (int i = 2; i < MAXN; i++) {
        	if (!p[i]){
        		p[i] = i;
        		primes.pb(i);
        	}
        	assert(i % p[i] == 0);
        	for (int j = 0; j < (int)primes.size() && primes[j] <= p[i] && i * primes[j] < MAXN; j++)
        		p[i * primes[j]] = primes[j];        		
        }

        memset(res, 1, sizeof(res));

        for (int i = 2; i < MAXN; i++)
        	if (p[i] != i)
	        	for (int j = 2; j * (i+1) - j * j < MAXN && j * (i+1) - j * j > 0; j++) {
        		     res[j * (i+1) - j * j] = false;
    	    	}

        ll ans = 0;
        int cnt = 0;
        for (int i = a; i <= b; i++) {
        	if (res[i] && p[i-1] != i-1) {
	        	cnt++;
        		ans += i;
        		eprintf("%d\n", i);
        	}
        }
        printf("%d\n", cnt);
        return ans;
    }
};



class SumAndProductPuzzle2 {

bool good[MAXN];
int ans[MAXN];

bool check(int x) {
   int ans = 0;
   for (int i = 1; i * i <= x; i++){
       if (x % i == 0) {
          int temp = i + x / i - 1;
          if (!good[temp]) {
          	if (ans++ == 2) return false;
          }
       }
   }
   return ans == 1;
}


public:
    ll getSum(int a, int b) {
        memset(good, 1, sizeof(good));
        good[0] = 0;
        for (int i = 2; i * i <= MAXN; i++)
        	if (good[i]){
        	   for (int j = i * i; j < MAXN; j+=i)
        	   	  good[j] = false;
        	}
        ll ans = 0;
        for (int i = a; i <= b; i++) {
        	if (i % 100000 == 0) printf("%d\n", i);
        	if (!good[i-1] && check(i-1)) {
        		eprintf("%d\n", i);
        		ans += i;
        	}
        }
        return ans;
    }
};


int main() {
	int res = SumAndProductPuzzle().getSum(1, 20);
	eprintf("\n");
	 res = SumAndProductPuzzle2().getSum(1, 20);
	printf("%d\n", res);
}
// END KAWIGIEDIT TESTING
