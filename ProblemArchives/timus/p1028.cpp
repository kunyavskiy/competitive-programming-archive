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

const int MAXC = 35000;

int f[MAXC];

void update(int a){
	for (;a < MAXC; a = a|(a+1))
		f[a]++;
}


int get(int a){
	int ans = 0;
	for (;a != -1; a = ((a&(a+1)) - 1))
		ans += f[a];
	return ans;
}

vector<pair<int,int> > v;

int cnt[MAXC];


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int n;
  cin >> n;
  v.resize(n);
  for (int i = 0; i < n; i++)
  	cin >> v[i].first >> v[i].second;
  sort(v.begin(),v.end());
  for (int i = 0; i < n; i++){
  	cnt[get(v[i].second)]++;
  	update(v[i].second);
  }

  for (int i = 0; i < n; i++)
  	printf("%d\n",cnt[i]);

  return 0;
}