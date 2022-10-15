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

void solve(){
	int n;
	string s;
	cin>>n>>s;
	for (int i=0;i<4*n;i+=4){
		int tmp=(s[i]-'0')*10+(s[i+1]-'0')*10+(s[i+2]-'0')+(s[i+3]-'0');
		printf("%c",char(tmp));
	}
	printf("\n");
}

int main()
{
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int t;
	cin>>t;
	for (;t;--t)
		solve();
    return 0; 
}