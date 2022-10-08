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

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

int cnt[10];

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int n,k;
  string s;
  cin >> n >> k >> s;
  for (int i = 0; i < n; i++)
  	cnt[s[i]-'0']++;

  int ans = 1<<30;
  int ansid = 0;

  for (int i = 0; i < 10; i++){
  	int sum = 0,h = 0;
  	for (int j = 0; j < 10; j++){
  		if (i + j < 10){
  			sum += min(k-h,cnt[i+j])*j;
  			h += min(k-h,cnt[i+j]);
  		}
  		if (j && i-j >= 0){
  			sum += min(k-h,cnt[i-j])*j;
  			h += min(k-h,cnt[i-j]);
  		}
  	}

  	if (ans > sum) {
  		ans = sum;
  		ansid = i;
  	}
  }

  int h = k;

  for (int j = 0; j < 10 && h; j++){
  	for (int i = 0; i < n && h; i++)
  		if (s[i]-'0' == ansid+j){
  			s[i] = ansid+'0';
  			h--;
  		}
  	if (j){
  	  	for (int i = 0; i < n && h; i++)
  			if (s[i]-'0' == ansid-j){
  				s[i] = ansid+'0';
  				h--;
  			}
  	}
  }

  cout << ans << endl << s << endl;
  		
  

  return 0;
}