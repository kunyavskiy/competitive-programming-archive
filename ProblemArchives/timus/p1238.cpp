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
#include <sstream>
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
    #define M_PI 3.1415926535897932384626433832795
    #define prev prev_dsfdfgfhgfh
    #define next next_mkdlsmfdgkl
    #define hash hash_mdfdsgdhgfm
    #undef assert
    #define assert(x) if (!(x)) throw 1
    #define sqrt(x) sqrt((double)(x))
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

int dp[110][110];

string s;

int len(int x){
	int ans = 0;
	while (x) 
		ans++, x /= 10;
	return ans;
}

string vtos(int x){
	stringstream str;
	str << x;
	string s;
	str >> s;
	return s;
}

int get(int l,int r){
	int& ans = dp[l][r];
	if (ans != -1)
		return ans;
	if (l == r) return ans = 0;
	ans = r-l;
	for (int i = l+1; i < r; i++)
		ans = min(ans,get(l,i) + get(i,r));
	for (int i = 1; i < r-l; i++)
		if ((r-l) % i == 0)
			if (string(s.begin()+l,s.begin()+r-i) == string(s.begin()+l+i,s.begin()+r))
				ans = min(ans,get(l,l+i) + 2 + len((r-l)/i));
	return ans;
}

string gen(int l,int r){
	int ans = get(l,r);;
	assert(ans != -1);
	if (l == r) return "";
	for (int i = l+1; i < r; i++)
		if (ans == get(l,i) + get(i,r))
			return gen(l,i) + gen(i,r);
	for (int i = 1; i < r-l; i++)
		if ((r-l) % i == 0)
			if (string(s.begin()+l,s.begin()+r-i) == string(s.begin()+l+i,s.begin()+r))
				if (ans == get(l,l+i) + 2 + len((r-l)/i))
					return vtos((r-l)/i) + "(" + gen(l,l+i)+")";
	return string(s.begin()+l,s.begin()+r);
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	memset(dp,-1,sizeof(dp));
  	cin >> s;
  	cout << gen(0,s.size()) << endl;
    return 0;
}