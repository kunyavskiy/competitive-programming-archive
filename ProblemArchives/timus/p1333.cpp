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

#ifndef M_PI
	#define M_PI 3.1415926535897932384626433832795
#endif


#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef double ld;

ld x[10],y[10],r[10];
int n;


bool check(ld x0,ld y0){
	for (int i = 0; i < n; i++)
		if ((x[i] - x0)*(x[i]-x0)+(y[i]-y0)*(y[i]-y0) < r[i]*r[i])
			return 1;
	return 0;    
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  scanf("%d",&n);
  for (int i = 0;i < n; i++)
  	scanf("%lf %lf %lf",&x[i],&y[i],&r[i]);


  int cnt = 0;
                           
  for (int i = 0; i < 1000000; i++)
  	cnt += check(rand()*1.0/RAND_MAX,rand()*1.0/RAND_MAX);

  cout.precision(15);
  cout << fixed << cnt/10000.0 << endl;


	
  return 0;
}