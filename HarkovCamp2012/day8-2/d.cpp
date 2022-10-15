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

#define taskname "d"

const int inf = 1000000000;
const ld eps = 1e-9;


int pow(int a,int b,int mod){
	if (!b)
		return (int(a!=0))%mod;
	if (b & 1)
		return (pow(a,b-1,mod)*1LL*a)%mod;
	int temp = pow(a,b>>1,mod);
	return (temp*1LL*temp)%mod;
}

int main(){
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);

  int cnt1,cnt2;
  cnt1 = cnt2 = 0;
  int n;
  int p;
  scanf("%d",&p);
  scanf("%d",&n);
  if (p == 2){
  	cout << 0 << endl;
  	return 0;
  }

  for (int i = 0; i < n; i++){
  	int a;
  	scanf("%d",&a);
  	a = pow(a,(p-1)/2,p);
  	if (a == 1)
  		cnt1++;
  	else if (a == p-1)
  		cnt2++;
  }

  cout << cnt1*1LL*cnt2<<endl;

  return 0;
}

