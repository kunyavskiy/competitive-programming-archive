#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <list>
#include <queue>
#include <stack>
#include <deque>
#include <iterator>

#define mp make_pair
#define pb push_back
#define sqr(a) ((a) * (a))
#define zero(a) memset (a, 0, sizeof(a))
#define sz(a) (int)(a.size())

#ifdef LOCAL
	#define LLD "%I64d"
#else 
	#define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned int uint;

#define taskname "f"

const int inf = 1000000000;
const ld eps = 1e-9;

char a[2100];
char b[2100];

int cnt[26][2100];
int cnt2[26][2100];
int n,m;

int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}

int get(char a){
	if ('a' <= a && a <= 'z')
		return a -'a';
	return a - 'A';
}

int get(int sdv){
	int g = gcd(n,m);
	for (int i = 0; i < n; i++)
		cnt[get(a[i])][(i-sdv+g*2000)%g]++;
	for (int i = 0; i < m; i++)
		cnt2[get(b[i])][i%g]++;

	int ans = 0;
	for (int i = 0; i < g; i++)
		for (int j = 0; j < 26; j++)
			ans += cnt[j][i] * cnt2[j][i];


	for (int i = 0; i < n; i++)
		cnt[get(a[i])][(i-sdv+g*2000)%g]--;
	for (int i = 0; i < m; i++)
		cnt2[get(b[i])][i%g]--;

    return ans;
}

int main(){
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  gets(a);
  gets(b);

  n = strlen(a);
  m = strlen(b);
  int ans = 0;
  int val = 1;

  for (int i = 0; i < n; i++){
  	int temp =get(i);
//  	cerr << temp <<" "<<i<<endl;
  	if (temp > ans){
  		ans = temp;
  		val = i+1;
  	}
  }	

//  cerr << ans << endl;
  cout << val <<" "<<1 <<endl;

  return 0;
}

