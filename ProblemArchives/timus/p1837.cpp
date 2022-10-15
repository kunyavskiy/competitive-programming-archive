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

string s[110][3];

map<string,int> ans;

void print(){
	for (map<string,int>::iterator iter = ans.begin(); iter != ans.end(); ++iter)
		if (iter->second == 1000)
			cout << iter->first << " "<<"undefined" << endl;
		else
			cout << iter->first <<" "<<iter->second << endl;
    exit(0);
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int n;

  cin >> n;

  for (int i = 0; i < n; i++){
  	cin >> s[i][0] >> s[i][1] >> s[i][2];
  	ans[s[i][0]] = ans[s[i][1]] = ans[s[i][2]] = 1000;
  }

  if (ans.find("Isenbaev") == ans.end())
  	print();

  ans["Isenbaev"] = 0;

  for (;;){
  	bool q = false;

  	for (int i = 0; i < n; i++){
  		int val = 1000;
		val = min(val,ans[s[i][0]]);
  		val = min(val,ans[s[i][1]]);
  		val = min(val,ans[s[i][2]]);
  		if (val == 1000)
  			continue;
  		if (ans[s[i][0]] > val+1)
  			ans[s[i][0]] = val+1,q = true;
  		if (ans[s[i][1]] > val+1)
  			ans[s[i][1]] = val+1,q = true;
  		if (ans[s[i][2]] > val+1)
  			ans[s[i][2]] = val+1,q = true;

  	}


  	if (!q)
  		print();  		
  }

  return 0;
}