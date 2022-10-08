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

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "C"

typedef long long ll;
typedef long double ld;

ld ans = -1;

const int MAXN = 110;

int x[MAXN];
int y[MAXN];

vector<pair<int,int> > v;


ll dist(int i,int j){
	ll dx = x[j] - x[i];
	ll dy = y[j] - y[i];
	return dx * dx + dy * dy;
}

ld S(int i,int j,int k){
	ll x1 = x[k] - x[i];
	ll y1 = y[k] - y[i];
	ll x2 = x[j] - x[i];
	ll y2 = y[j] - y[i];
	return abs(x1*y2 - x2*y1)/2.0;
}

void check(ld x0,ld y0,ld d){
	for (int i = 0; i < n; i++)
		if (sqrt((x[i] - x0) * (x[i] - x0) + (y[i] - y0) * ( y[i] - y0)) > d + 1e-5)
			return;
	ans = min(ans,d);
}

void solve(int i,int j,int k){
	int a[3];
	a[0] = i;
	a[1] = j;
	a[2] = k;
	do {
		ll d1 = dist(a[0],a[1]);
		ll d2 = dist(a[0],a[2]);
		ll d3 = dist(a[1],a[2]);
		if (d1 <= d2 && d2 <= d3) break; 
		assert(next_permutation(a,a+3));
	} while (true);

	i = a[0];j = a[1]; k = a[2];
	ll I = dist(j,k);
	ll J = dist(i,k);
	ll K = dist(i,j);
	assert(I >= J && J >= K);


//	eprintf(LLD" "LLD" "LLD"\n",I,J,K);
//	eprintf("%d %d %d\n\n",i,j,k);

	if (I == J+K){
		if (binary_search(v.begin(),v.end(), mp (x[j] + x[k] - x[i], y[j] + y[k] - y[i])))
			check((x[j] + x[k])/2.0, (y[j] + y[k]) / 2.0, sqrt(I)/2);
	eprintf("%lf %d %d %d\n",(double)ans,i,j,k);
		return;
	}
	if (I > J+K)
		return;

	ld dI = sqrt(I);
	ld dJ = sqrt(J);
	ld dK = sqrt(K);         
	ld dS = S(i,j,k);
	ld dD = dI*dJ*dK/(4*dS);
	double x,y;
	getCenter(i,j,k,x,y);
	check(x,y,dD);
	eprintf("%lf %d %d %d\n",(double)ans,i,j,k);
}


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  	int n;
  	scanf("%d",&n);
  	for (int i = 0; i < n; i++){
  		scanf("%d %d",&x[i],&y[i]);
  		v.pb(mp(x[i],y[i]));
  	}

  	sort(v.begin(),v.end());

  	for (int i = 0; i < n; i++)
  		for (int j = i+1; j < n; j++)
  			for (int k = j+1; k < n; k++)
  				solve(i,j,k);


  	if (ans < 0)
  		printf("-1\n");
  	else
		printf("%.10lf\n",(double)ans);      
  return 0;
}