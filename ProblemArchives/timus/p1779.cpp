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

vector<pair<int,int> > ans;


void gen(int n){
	if (n == 3){
		ans.pb(mp(0,2));
		ans.pb(mp(1,2));
		return;
	}
	if (n == 2){
		ans.pb(mp(0,1));
		return;
	}
	if (n == 1)
		return;
	for (int i = 0; i < n-2; i++){
		ans.pb(mp(i,n-1));
		ans.pb(mp(i,n-2));
	}
	ans.pb(mp(n-1,n-2));
	gen(n-3);
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    int n;
    cin >> n;
    gen(n);
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++)
    	cout << ans[i].first+1 <<" "<<ans[i].second+1 << endl;
  return 0;
}