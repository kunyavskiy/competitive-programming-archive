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

#ifndef M_PI
	#define M_PI 3.1415926535897932384626433832795
#endif


#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

string s1,s2;

vector<int> p;



int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	cin >> s1;
  	cin >> s1 >> s2;

  	string s = s1 + ' ' + s2 + s2;
  	p.resize(s.size());

  	for (int i = 1; i < s.size(); i++){
  		int j = p[i-1];
  		for (; j && s[j] != s[i]; j = p[j-1]);
  		if (s[j] == s[i])
  			j++;
  		p[i] = j;
  		if (i > s1.size() && p[i] == s1.size()){
  			cout << i - (int)s1.size() - (int)s2.size()<< endl;
  			return 0;
  		}
  	}

  	cout << -1 << endl;
  return 0;
}