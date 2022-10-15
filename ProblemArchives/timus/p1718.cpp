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

set<string> minv,maxv;

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif            
	int n;
	cin >> n;
	for (int i = 0; i < n; i++){
		string res,name;
		cin >> name;
		cin >> res;
		if (res == "AC"){
			maxv.insert(name);
			continue;
		}
		if (res == "CE")
			continue;
		int tid;
		cin >> tid;
        if (tid < 6)
        	continue;
        if (tid == 6)
        	maxv.insert(name);
        else if (tid > 6)
        	minv.insert(name),maxv.insert(name);
	}
	cout << minv.size() <<" "<<maxv.size() << endl;
  return 0;
}