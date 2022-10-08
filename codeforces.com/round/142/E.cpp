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

const int MAXN = 1100;

ld lnf[MAXN];

ld lnc(int n,int k){
    return lnf[n] - lnf[k] - lnf[n-k];
}

vector<int> v[1100];

vector<int> all;

int n,m;

ld get[1100];
ld unget[1100];


ld dp1[1100];
ld dp2[1100];

int dcf[1100];
bool dcfu[1100];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  for (int i = 1; i < MAXN; i++)
    lnf[i] = log(i) + lnf[i-1];

  scanf("%d %d",&n,&m);

  for (int i = 0; i < m; i++){
    int k;
    scanf("%d",&k);
    for (int j = 0; j < k; j++){
        int x;
        scanf("%d",&x);
        v[i].pb(x);
        all.pb(x);
    }
    sort(v[i].begin(),v[i].end());
  }

  sort(all.begin(),all.end());

  int minv = all[all.size() - n];

  int can = n - (all.end() - upper_bound(all.begin(),all.end(),minv));

  for (int i = 0; i < m; i++){
    int id = lower_bound(v[i].begin(),v[i].end(),minv) - v[i].begin();
    if (id == (int)v[i].size() || v[i][id] != minv){
       unget[i] = exp(-lnc(v[i].size(),id));
       get[i] = 0; 
       dcfu[i] = 0;
    }
    else {
       unget[i] = exp(-lnc(v[i].size(),id+1));
       get[i] = exp(-lnc(v[i].size(),id)); 
       dcfu[i] = 1;
    }
  }    

  dcf[m-1] = dcfu[m-1];
  for (int i = m-2; i >= 0; i--)
    dcf[i] = dcf[i+1] + dcfu[i];

  for (int i = 0; i <= can; i++)
    dp1[i] = dp2[i] = 0;

  dp1[0] = 1;

  for (int i = 0; i < m; i++){
     for (int j = 0; j <= can; j++){
        if (dcfu[i] && can-j <= dcf[i]){
            dp2[j+1] += dp1[j] * ((can - j) / dcf[i]) * get[i];
            dp2[j] += dp1[j] * (1.0 - (can-j)/dcf[i]) * unget[i];
        }
        else {                                                   
            dp2[j] += dp1[j] * unget[i];
        }
     }
     for (int j = 0; j <= can; j++){
        dp1[j] = dp2[j];
        dp2[j] = 0;
     }
  }

  cout.precision(15);
  cout << fixed << dp1[can] << endl;


      
  return 0;
}