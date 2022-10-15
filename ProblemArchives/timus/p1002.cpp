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


bool ok(char c,char a){
	switch (c){
		case '0': return a == 'o' || a == 'q' || a == 'z';
		case '1': return a == 'i' || a == 'j';
		case '2': return a == 'a' || a == 'b' || a == 'c';
		case '3': return a == 'd' || a == 'e' || a == 'f';
		case '4': return a == 'g' || a == 'h';
		case '5': return a == 'k' || a == 'l';
		case '6': return a == 'm' || a == 'n';
		case '7': return a == 'p' || a == 'r' || a == 's';
		case '8': return a == 't' || a == 'u' || a == 'v';
		case '9': return a == 'w' || a == 'x' || a == 'y';
	}
	assert(false);
}

string s;
string st[51000];
int n;
char buf[110];
bool dp[110];
string ans[110];


bool solve(){
	gets(buf);s = buf;
	if (s == "-1")
		return false;
	gets(buf);
	sscanf(buf,"%d",&n);
	for (int i = 0; i < n; i++)
		gets(buf),st[i] = buf;   		
	memset(dp,0,sizeof(dp));
	int len = s.size();
	ans[len] = "No solution.";
	dp[0] = 1;ans[0] = "";

	for (int i = 0; i < len; i++){
		if (!dp[i])
			continue;
		for (int j = 0; j < n; j++){
			if (i + st[j].size() > len || dp[i + st[j].size()])
				continue;
			bool q = true;
			for (int k = 0; k < st[j].size() && q; k++)
				if (!ok(s[i+k],st[j][k]))
					q = false;
			if (q){
				dp[i + st[j].size()] = true;
				ans[i + st[j].size()] = ans[i] + (i?" ":"")+st[j];
			}
		}
	}
    puts(ans[len].data());
    return true;             
}




int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	while(solve());
  return 0;
}