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

string s[110];

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> s[i];
  	for (int i = 0; i < n; i++){
  		bool q = false;
  		for (int j = 0; j < i; j++)
  			if (s[i] == s[j])
  				q = true;
  		if (q)
  			continue;
  		for (int j = i+1; j < n; j++)
  			if (s[i] == s[j])
  				q = true;
  		if (q)
  			cout << s[i] <<endl;
  		
  	}
    return 0;
}