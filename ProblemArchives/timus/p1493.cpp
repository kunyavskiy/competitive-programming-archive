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

bool check(int x){
	int sum1,sum2;
	sum1 = sum2 = 0;
	sum1 += x%10; x/= 10;
	sum1 += x%10; x/= 10;
	sum1 += x%10; x/= 10;
	sum2 += x%10; x/= 10;
	sum2 += x%10; x/= 10;
	sum2 += x%10; x/= 10;
	return sum1 == sum2;
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int a;
	cin >> a;
	if (check(a-1) || check(a+1))
		cout <<"Yes"<<endl;
	else
		cout <<"No"<<endl;
  return 0;
}