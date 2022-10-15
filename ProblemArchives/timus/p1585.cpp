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

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	string s;
	getline(cin,s);
	map<string,int> m;
	int n;
	sscanf(s.data(),"%d",&n);
	m["Emperor Penguin"] = m["Macaroni Penguin"] = m["Little Penguin"] = 0;
	for (int i = 0; i < n; i++){
		getline(cin,s);
		m[s]++;
	}

	vector<pair<string,int> > v(m.begin(),m.end());
	vector<pair<int,string> > v2;
	v2.pb(mp(v[0].second,v[0].first));
	v2.pb(mp(v[1].second,v[1].first));
	v2.pb(mp(v[2].second,v[2].first));
    sort(v2.begin(),v2.end());
    cout << v2[2].second << endl;                                                   
    return 0;
}