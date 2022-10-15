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

#define taskname "c6"

const int inf = 1000000000;
const ld eps = 1e-9;

ll X,A,B;
int T;

ll dp[100];

void Precalc(){
	dp[0] = 1;
	for (int i = 0; i < 62; i++){
		for (int j = 0; j < 2; j++)	
			for (int k = 0; k < 2; k++){
     			if (((1LL<<i) & (((ll)j<<i) ^ X ^ ((ll)k<<i))))
     				continue;
				if ((A & (1LL<<i)) && !j)
					continue;
				if ((B & (1LL<<i)) && !k)
					continue;
				bool ca,cb;
				ca = cb = false;
				if ((A & (1LL<<i)) || !j)
					ca = true;
				if ((B & (1LL<<i)) || !k)
					cb = true;

				if (!ca && !cb)
					dp[i+1] += (1LL<<i) - 0;
				else if (ca && !cb)
					dp[i+1] += (1LL<<i) - (A & ((1LL<<i)-1));
				else if (!ca && cb)
					dp[i+1] += (1LL<<i) - (B & ((1LL<<i)-1));
				else
					dp[i+1] += dp[i];			
			}
	}
}

void gen(int id,ll num,ll& cura,ll& curb){
	if (id == -1){
		return;
	}
 	for (int j = 0; j < 2; j++)	
 		for (int k = 0; k < 2; k++){
 			
 			if (((1LL<<id) & (((ll)j<<id) ^ X ^ ((ll)k<<id))))
 				continue;
 			//cerr<<"!!!!"<<endl;
 			if ((A & ~((1LL<<(id))-1)) > (cura | (ll(j)<<id)))
 				continue;
 			if ((B & ~((1LL<<(id))-1)) > (curb | (ll(k)<<id)))
 				continue;



 			bool ca,cb;

 			ca = ((A & ~((1LL<<(id))-1)) == (cura | (ll(j)<<id)));
 			cb = ((B & ~((1LL<<(id))-1)) == (curb | (ll(k)<<id)));

 			ll cnt = 0;

 			if (!ca && !cb)
 				cnt = (1LL<<id) - 0;
 			else if (ca && !cb)
 				cnt = (1LL<<id) - (A & ((1LL<<id)-1));
 			else if (!ca && cb)
 				cnt = (1LL<<id) - (B & ((1LL<<id)-1));
 			else
 				cnt = dp[id];			

 			//cerr << id <<" "<<id<<" "<<j<<" "<<cura <<" "<<curb <<" "<<cnt << endl;

 			if (num > cnt)
 				num -= cnt;
 			else {
				cura|=(ll(j)<<id);
				curb|=(ll(k)<<id);

 				gen(id-1,num,cura,curb);
 				return;
 			}
 		}
 	assert(false);
}


int main(){
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);

  scanf(LLD" "LLD" "LLD,&X,&A,&B);
  scanf("%d",&T);
  Precalc();

  //for (int i = 0; i < 62; i++)
 // 	cerr << dp[i] << endl;

  for (int i = 0; i < T; i++){
  	ll n;
  	scanf(LLD,&n);
  	ll ra,rb;
  	ra = rb = 0;
  	gen(61,n,ra,rb);
  	assert((ra ^ rb) == X);
  	printf(LLD" "LLD"\n",ra,rb);
  }

  return 0;
}

