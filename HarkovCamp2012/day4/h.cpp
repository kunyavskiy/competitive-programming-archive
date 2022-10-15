#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <list>
#include <queue>
#include <stack>
#include <deque>
#include <iterator>

#define mp make_pair
#define pb push_back
#define sqr(a) ((a) * (a))
#define zero(a) memset (a, 0, sizeof(a))
#define sz(a) (int)(a.size())

#ifdef LOCAL
	#define LLD "%I64d"
#else 
	#define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned int uint;

#define taskname "h"

const int inf = 1000000000;
const ld eps = 1e-9;


const int MAXN = 5000000;
vector<int> pr;
int p[MAXN+10];
int st[MAXN+10];
ll val[MAXN+10];

ll pow(ll a, int b){
	if (b == 0)
		return 1;
	if (b & 1)
		return (pow(a,b-1)*a);
    ll temp = pow(a,b>>1);
    return temp*temp;
}


void gen(){
	for (int i = 2; i <= MAXN; i++){
		if (p[i] == 0){
			p[i] = i;
			st[i] = 1;
			val[i] = i+1;
			pr.pb(i);
		}
		for (int j = 0; j < (int)pr.size() && i*1LL*pr[j] <=MAXN && pr[j] <= p[i]; j++){
			p[i*pr[j]] = pr[j];
			st[i*pr[j]] = 1 + st[i] * (pr[j] == p[i]);
			val[i*pr[j]] = val[i] * (pow((ll)pr[j],st[i*pr[j]]+1)-1) / (pow((ll)pr[j],st[i*pr[j]])-1);
		}
	}
}

int main(){
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);

  gen();
  val[1] = 1;

  for (int i = 1; i <= MAXN; i++)
  	val[i] += val[i-1];

  int l,r;
  while (scanf("%d %d",&l,&r) == 2){
  	printf(LLD"\n",val[r] - val[l-1]);
  }

  return 0;
}

