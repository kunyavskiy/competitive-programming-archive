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

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

int v[111000];

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	v[0] = 0;
  	v[1] = 1;
  	for (int i = 2; i < 100000; i++)
  		v[i] = v[i/2] + v[i/2+1]*(i%2);

  	for (int i = 1; i < 100000; i++)
  		v[i] = max(v[i],v[i-1]);

  	for (int n;cin>>n;){
  		if (n)
  			cout << v[n] << endl;
  	}

  return 0;
}