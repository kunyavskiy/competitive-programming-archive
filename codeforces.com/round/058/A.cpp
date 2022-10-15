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

bool check(int g,int b){
	if (b < g-1)
		return false;
	if (g < (b-1)/2 )
		return false;
	return true;
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int a,b,c,d;
	cin>>a>>b>>c>>d;
	if (check(a,d) || check(b,c))
		cout<<"YES\n"<<endl;
	else
		cout<<"NO\n"<<endl;
    return 0;
}