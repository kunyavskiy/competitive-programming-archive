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

char s[10000010];
int dp[10010];

const int CNT = 1000;

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int n;
  gets(s);
  sscanf(s,"%d",&n);
  int id = 1;
  for (int it = 1; it <= n; it++){
  	gets(s);
  	dp[0] = ++id;


  //	cerr << s << endl;	
  	for (int i = 0,j = 0;; i++,j++){
  		if (j == CNT){
  			++id;
  			dp[0] = dp[CNT+0]+1;
  			dp[1] = dp[CNT+1]+1;
  			dp[2] = dp[CNT+2]+1;
  			dp[3] = dp[CNT+3]+1;
  			dp[4] = dp[CNT+4]+1;
  			dp[5] = dp[CNT+5]+1;
  			dp[6] = dp[CNT+6]+1;
  			dp[7] = dp[CNT+7]+1;
  			dp[8] = dp[CNT+8]+1;
  			j = 0;
  		}
  		if (!s[i]){
  			printf((dp[j] == id)?"YES\n":"NO\n");
  			break;
  		}
  		if (dp[j] != id)
  			continue;
//  		cerr << string(s,s+i) << endl;
  		if (s[i] == 'o'&& s[i+1] == 'u' && s[i+2] == 't'){
  			dp[j+3] = id;
  			if (s[i+3] == 'p' && s[i+4] == 'u' && s[i+5] == 't')
  				dp[j+6] = id;
  		}
  		if (s[i] == 'i'&& s[i+1] == 'n'){
  			dp[j+2] = id;
  			if (s[i+2] == 'p' && s[i+3] == 'u' && s[i+4] == 't')
  				dp[j+5] = id;
  		}
  		if (s[i] == 'o' && s[i+1] == 'n' && s[i+2] =='e')
  			dp[j+3] = id;                                       
  		if (s[i] == 'p'&& s[i+1] == 'u')
 			if (s[i+2] == 't' && s[i+3] == 'o' && s[i+4] == 'n')
  				dp[j+5] = id;	
  	}

  	//cerr <<"END"<<endl;

  }

  return 0;
}