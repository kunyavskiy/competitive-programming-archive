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

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	string s;
	cin >> s;
	int n = s.size();
	string ans = "";

	for (int i = 0; i < n; i++){
		int j = 0;
		for (;i-j >= 0 && i+j < n && s[i-j] == s[i+j]; j++);
		--j;
		if (2*j +1 > (int)ans.size()) 
			ans = string(s.begin()+i-j,s.begin()+i+j+1);
		
	}



	for (int i = 0; i < n; i++){
		int j = 0;
		for (;i-j >= 0 && i+j+1 < n && s[i-j] == s[i+j+1]; j++);
		--j;
		if (2*j+2  > (int)ans.size())
			ans = string(s.begin()+i-j,s.begin()+i+j+2);
	}



	cout << ans << endl;
  return 0;
}