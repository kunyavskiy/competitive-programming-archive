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

#define TASKNAME "FN"

#ifdef LOCAL
static struct __timestamper {
	~__timestamper(){
        TIMESTAMP(end);
	}
} __TIMESTAMPER;
#endif

typedef long long ll;
typedef long double ld;

ll pow(ll a,ll b,ll p){
	if (!b) return 1;
	if (b & 1) return (pow(a, b-1, p) * a) % p;
	return pow((a*a) % p, b/2, p) % p;
}

ll inv(ll a,ll p){
	return pow(a, p-2, p);
}

ll getPrimeRoot(int p){
	vector<int> divs;
	int tmp = p - 1;
	for (int i = 2; i * i <= tmp; i++){
		if (tmp % i == 0){
			divs.pb((p - 1) / i);
			while (tmp % i == 0)
				tmp /= i;
		}
	}
	if (tmp != 1)
		divs.pb((p - 1) / tmp);
	while (true){
		int r = rand() % p;
		if (!r) continue;
		bool ok = true;
		for (int i = 0; ok && i < (int)divs.size(); i++)
			if (pow(r, divs[i], p) == 1)
				ok = false;
		if (ok) {
			return r;
		}
	}
	assert(false);
}

vector<int> getLog(ll a, ll b, ll p){
	int sqp = (int)sqrt(p)+1;
	if (sqp % 2 == 1) sqp++;
	vector< pair<int,int> > small, big;
	for (int i = 0; i < sqp; i++)
		small.pb(mp(pow(a, i, p),i));
//	eprintf("\n\n");
	int inva = inv(a,p);
	for (int i = 0; i < sqp; i++) {
//		eprintf("%d -> "LLD"\n", i * sqp, (b * pow(inva, i*sqp, p)) % p);
		big.pb(mp((b * pow(inva, i*sqp, p)) % p,i*sqp));
	}

	sort(small.begin(), small.end());
	sort(big.begin(), big.end());

	vector<int> ans;

	for (int i = 0; i < (int)small.size(); i++){
		int id = lower_bound(big.begin(), big.end(), mp(small[i].first, -1)) - big.begin();
		if (id != (int)big.size() && big[id].first == small[i].first){
			int x = small[i].second + big[id].second;
//			eprintf("a = "LLD", inva = %d, x = %d, p = "LLD", b = "LLD"\n", a, inva,x, p, b);
//			eprintf("%d %d %d %d\n", big[id].first, small[i].first, small[i].second, big[id].second);
		    assert(pow(a, x, p) == b);
		    if (x < p-1)
			    ans.pb(x);
		}
	}
	return ans;
}

ll getSqrt(ll a,ll p){
	if (a == 0) return 0;
//	eprintf("a = "LLD", p = "LLD"\n", a, p);
	ll root = getPrimeRoot(p);
	vector<int> _b = getLog(root, a, p);
	assert((int)_b.size() == 1);
	ll b = _b[0];
	if (b % 2 != 0)	return -1;
	ll res = pow(root, b/2, p);
	assert((res * res) % p == a);
	return res;
}

ll getAns(ll a, ll c, ll p, int ty){
	ll rt = getSqrt((c * c + 4 * (ty ? -1 : 1) + p) % p, p);
	if (rt == -1) return -1;
	ll ax1 = ((c + rt + 2*p) * inv(2, p)) % p;
	ll ax2 = ((c - rt + 2*p) * inv(2, p)) % p;
	eprintf("Solutions ("LLD", " LLD", "LLD", %d)are "LLD" and "LLD"\n",a,c,p,ty, ax1, ax2);
	assert(((pow(ax1, 2, p) - c * pow(ax1, 1, p) + (ty ? 1 : -1)) % p) == 0);
	assert(((pow(ax2, 2, p) - c * pow(ax2, 1, p) + (ty ? 1 : -1)) % p) == 0);
	vector<int> res1 = getLog(a, ax1, p);
	vector<int> res2 = getLog(a, ax2, p);
	vector<int> res = res1;
	res.insert(res.end(), res2.begin(), res2.end());
	int ans = -1;
	for (int i = 0; i < (int)res.size(); i++){
		if (res[i] % 2 == ty){
		    eprintf(LLD" %d " LLD" " LLD" %d\n", a, res[i], pow(a, res[i],p), c, ty);
		    assert(pow(a, res[i],p) == ax1 || pow(a, res[i],p) == ax2);
			assert(((pow(a, res[i],p) - pow(inv(p-a,p), res[i], p) + p) % p == c));
			assert(((pow(a, res[i]*2LL, p) - c * pow(a, res[i], p) + (ty ? 1 : -1)) % p) == 0);
			if (ans == -1)
				ans = res[i];
			ans = min(ans, res[i]);
		}			
	}
	return ans;
}

void solve(){
	ll c,p;
	scanf(LLD" "LLD,&c,&p);
	ll sq5 = getSqrt(5, p);
	eprintf("sq5 = "LLD"\n", sq5);
	assert(sq5 != -1);
	ll a = ((1 + sq5) * inv(2,p)) % p;    
	c = (c * sq5) % p;

	eprintf("a = "LLD", b = "LLD", inv5 = "LLD",\n", a, inv(p-a,p), inv(sq5, p));
	                       

	eprintf(LLD"\n", c);

	ll oans = getAns(a, c, p, 1);
	ll eans = getAns(a, c, p, 0);

	if (oans == -1)	
		printf(LLD"\n", eans);
	else if (eans == -1)
		printf(LLD"\n", oans);
	else
		printf(LLD"\n", min(eans,oans));
}



int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
    srand(1234253);
  	
  	int t;
  	scanf("%d",&t);

  	while (t-->0)
  		solve();

      
  return 0;
}