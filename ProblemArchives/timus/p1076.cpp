#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <queue>
#include <memory.h>
#include <stack>
#define mp make_pair
#define pb push_back                     
#define setval(a,v) memset(a,v,sizeof(a))



#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
	#define M_PI 3.1415926535897932384626433832795
    #define prev prev_dsfdfgfhgfh
    #define next next_mkdlsmfdgkl
    #undef assert
    #define assert(x) if (!(x)) throw 1
#endif

using namespace std;

typedef long long ll;
typedef long double ld;
int a[250][250];
int fl[250],fr[250];
int p[250],d[250];
int mt[250];
bool used[250];
int n;

void iterate(int nv){
	memset(d,100,sizeof(d));
	memset(used,0,sizeof(used));

	d[n] = 0;
	int l = n;
	mt[n] = nv;

	while (mt[l] != -1){
		int k = mt[l];
		int nl = -1;
		used[l] = true;
		for (int i = 0; i < n; i++)
			if (!used[i]){
				if (d[i] > d[l] + a[k][i] + fl[k] + fr[i])	
					d[i] = d[l] + a[k][i] + fl[k] + fr[i], p[i] = l;
				if (nl == -1 || d[nl] > d[i])
					nl = i;
			}

		int add = d[nl];

		for (int i = 0; i <= n; i++)
			if (used[i])
				fr[i] += add, fl[mt[i]] -= add;
			else
				d[i] -= add;
	    l = nl;
	}

	while (l != n){
		mt[l] = mt[p[l]];		
		l = p[l];
	}
}




int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  scanf("%d",&n);
  int sum = 0;
  for (int i = 0; i < n; i++)
  	for (int j = 0; j < n; j++)
  		scanf("%d",&a[j][i]),a[j][i] *= -1,sum -= a[j][i];

  memset(mt,-1,sizeof(mt));

  for (int i = 0; i < n; i++)
  	iterate(i);

  for (int i = 0; i < n; i++)
  	sum += a[mt[i]][i]; 

  cout << sum << endl;
  return 0;
}