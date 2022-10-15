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

int a[110][110];

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int n;
	cin >> n;
	int cnt = 1;
	for (int dlt = n; dlt >= -n; --dlt)
		for (int i = 0; i < n; i++)
			if (i + dlt >= 0 && i +dlt < n)
				a[i][i+dlt] = cnt++;

    for (int i = 0; i < n; i++)
    	for (int j = 0; j < n; j++)
    		cout << a[i][j] <<" \n"[j == n-1];
  return 0;
}