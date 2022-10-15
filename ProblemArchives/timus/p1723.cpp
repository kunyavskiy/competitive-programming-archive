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

map<string,int> v;

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	string s;
	cin >> s;

	for (int i = 0; i < s.size(); i++)
		for (int j = i+1; j <= s.size(); j++)
			v[string(s.begin()+i,s.begin()+j)]++;

	vector<pair<int,string> > val;
	vector<pair<string,int> > val2(v.begin(),v.end());

	for (int i = 0; i < val2.size(); i++)
		val.pb(mp(val2[i].second,val2[i].first));
	cout << max_element(val.begin(),val.end())->second << endl;

  return 0;
}