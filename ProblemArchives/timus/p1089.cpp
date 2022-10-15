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



string s[110];
int n;

bool check(string s,string t){
	if (s.size() != t.size())
		return false;
	int diff = 0;
	for (int i = 0; i < s.size(); i++)
		if (s[i] != t[i])
			diff++;
	return diff <= 1;
}

string norm(string t){
	for (int i = 0; i < n; i++)
		if (check(s[i],t))
			return s[i];
	return t;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  while (getline(cin,s[n]))
  	if (s[n] == "#")
  		break;
  	else
  		n++;

  string cur = "";

  char c;

  int cnt = 0;

  while ((c = getc(stdin)) != EOF){
  	if (('a' <= c && c <= 'z'))
  		cur+=c;
  	else {
  		if (cur != norm(cur))
  			cnt++;
  		cout << norm(cur), cur = "";
  		cout << c;
  	}              	
  }

  printf("%d\n",cnt);
  return 0;
}