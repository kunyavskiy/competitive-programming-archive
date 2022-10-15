#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

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

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

int sum(int a){
	int ans = 0;
	for (;a;a/=10)
		ans += a%10;
	return ans;
}

vector<pair<int,int> > v;
vector<int> ans;

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int n;
	scanf("%d",&n);
	for (int i = 1; i <= 100000; i++)
		v.pb(mp(-sum(i),i));
	sort(v.begin(),v.end());
	for (int i = 0; i < v.size() && n; i++)
		if (n + v[i].first >= 0)
			ans.pb(v[i].second),n += v[i].first;	

	cout << ans.size() << endl;

	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] << endl;
  return 0;
}