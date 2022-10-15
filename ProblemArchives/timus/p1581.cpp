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

int a[1100];

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    int n;
    cin >> n;
    for (int i = 0; i <n ; i++)
    	cin >> a[i];
    for (int i = 0; i < n;){
    	int j = i;
    	for (;j<n && a[i] == a[j]; j++);
    	cout << j-i <<" "<<a[i] <<" \n"[j == n];
    	i = j;
    }
  return 0;
}