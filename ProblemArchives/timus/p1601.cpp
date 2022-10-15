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
	string s,t;
	s = "";
	while (getline(cin,t))
		s += t + '\n';
	bool q = true;
	for (int i = 0; i < s.size(); i++){
		if (q && 'a' <= s[i] && s[i] <='z')
			s[i] = s[i]-'a'+'A';
		if (!q && 'A' <= s[i] && s[i] <='Z')
			s[i] = s[i]-'A'+'a';		
		if (('a' <= s[i] && s[i] <='z') ||('A' <= s[i] && s[i] <='Z'))
			q = false;
		
		if (s[i] == '.' || s[i] == '?' || s[i] == '!')
			q = true;
	}
	cout << s;
		
  return 0;
}