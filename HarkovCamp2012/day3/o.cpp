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

#define taskname "o"

const int inf = 1000000000;
const ld eps = 1e-9;

const int base = 1000;
const int baselen = 3;

double tt=clock();


struct tlong{
	int sz, v[21000];
	
	void mult(int b){
		int c = 0;
		for (int i = 0; i < sz || c; i++){
			if (i == sz){
				sz++;
			}
			c = c + v[i] * b;
			v[i] = c % base;
			c /= base;
		}			
	}


	
	void lmult(ll b){
		ll c = 0;
		for (int i = 0; i < sz || c; i++){
			if (i == sz){
				sz++;
			}
			c = c + v[i] * b;
			v[i] = c % base;
			c /= base;
		}			
	}


	void divide(int b){
		int c = 0;
		for (int i = sz-1; i >= 0; i--){
			c = c + v[i];
			v[i] = c/b;
			c %= b;
			c *= base;
		}
		assert(c == 0);
		while (sz!=1 && v[sz-1] == 0)
			sz--;
	}

	void print(){
		printf("%d",v[sz-1]);

		for (int i = sz-2; i >= 0; i--)
			printf("%0*d",baselen,v[i]);
	}
};

tlong res;

int main(){
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);

  int n,k;
  scanf("%d %d",&n,&k);
  ll sum = 0;
  for (int i = 0; i < n; i++){
  	int a;
  	scanf("%d",&a);
  	sum += a;
  }

  //cerr<<(tt-clock())/CLOCKS_PER_SEC<<endl;
  res.v[0]=1, res.sz=1;

  for (int i = n; i < n+k;i++){
  	res.mult(i);
  	res.divide(i-n+1);
  }

  res.print();
  printf(" ");

  if (sum==0)
  {
    puts("0");
    return 0;
  }
  res.mult(k);
  res.divide(n);
  /*vector <int> V;
  for (int i=0; i<res.sz; i++)
    for (int j=0; j<3; j++)
      V.pb(res.v[i]%1000), res.v[i]/=1000;

  //res.mult(sum);
  //cerr<<(tt-clock())/CLOCKS_PER_SEC<<endl;

   ll b=sum;

		ll c = 0;
		int sz = V.size(); 
		for (int i = 0; i < sz || c; i++){
			if (i == sz){
				V.pb(0);
				sz++;
			}
			c = c + V[i] * b;
			V[i] = c % base;
			c /= base;
		}			
		while (V.size()!=1 && V.back() == 0)
			V.pop_back();
  printf("%d", V.back());
  for (int i=(int)V.size()-2; i>=0; i--)
    printf("%03d", V[i]);*/
  res.lmult(sum);
  res.print();
  printf("\n");
  //cerr<<(tt-clock())/CLOCKS_PER_SEC<<endl;
  return 0;
}

