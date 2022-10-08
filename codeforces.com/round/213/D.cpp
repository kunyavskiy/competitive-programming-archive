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

#ifdef LOCAL
static struct __timestamper {
	~__timestamper(){
        TIMESTAMP(end);
	}
} __TIMESTAMPER;
#endif

typedef long long ll;
typedef long double ld;

map<ll,int> divisors;

ll a[1100000];

void addDivisors(ll x){
    for (ll i = 1; i * i <= x; i++){
        if (x % i == 0){
           divisors[i]++;
           if (i != x / i)
               divisors[x / i]++;
        }
    }
}

int cnt[100];

int getOrd(ll a, ll b){
   int cnt = 0;
   while (b % a == 0){
   	   cnt++;
   	   b /= a;
   }
   return cnt;
}

int n;

int getHalf(){
   int sum = 0;
   for (int i = 0;; i++){
       sum += cnt[i];
       if (sum >= (n + 1) / 2)
           return i;
   }
   assert(false);
}


bool cmp_second(const pair<ll,int>& a, const pair<ll,int> & b){
	if (a.second != b.second)
		return a.second > b.second;
	return a.first > b.first;
}

bool check(ll ans){
    int cnt = 0;
    for (int i = 0; i < 1000; i++){
        int id = rand() % n;
        if (a[id] % ans == 0)
        	cnt++;
    }
    if (cnt <= 300 && n >= 100) return false;
    cnt = 0;
    for (int i = 0; i < n; i++)
        cnt += (a[i] % ans == 0);
    return cnt >= (n + 1) / 2;
}

int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
    scanf("%d",&n);
    for (int i = 0; i < n; i++)
    	scanf(LLD,&a[i]);

    for (int i = 0; i < 20; i++){
     	int id = rand() % n;
      	addDivisors(a[id]);
    }

    vector<pair<ll,int> > v(divisors.begin(), divisors.end());

    sort(v.begin(), v.end(), cmp_second);

    ll ans = 1;

    for (int i = 0; i < (int)v.size(); i++){
        if (v[i].first >= ans && check(v[i].first))
           ans = max(ans, v[i].first);
    }

    printf(LLD"\n", ans);
    return 0;
}