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

int cnt[1000];

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int n;
  cin >> n;

  cnt[0] = 1;

  for (int i = 0; i < n/2; i++)
  	for (int j = 100; j >=0; j--)
  		for (int k = 1; k < 10; k++)
  			cnt[j+k] += cnt[j];



  int ans = 0;

  for (int i = 0; i < 100; i++){
//  	if (cnt[i])
//  		cout << i << " "<<cnt[i] << endl;
  	ans += cnt[i]*cnt[i];
  }

  cout << ans << endl;

  return 0;
}