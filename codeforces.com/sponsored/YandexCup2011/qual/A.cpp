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

typedef long long int64;
typedef long double ld;

const string names[5]={"Sheldon", "Leonard", "Penny", "Rajesh", "Howard"};

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int64 cnt = 5;
	int64 n;
	cin>>n;
	for (;cnt<n;){
		n-=cnt;
		cnt*=2;
	}
	cout<<names[(n-1)/(cnt/5)]<<endl;
	return 0;
}