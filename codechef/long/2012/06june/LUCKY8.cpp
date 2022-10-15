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

bool dp[21][21][21][2][2];

const int LEN = 19;

void solve(){
    string L,R;
    cin >> L >> R;
    while ((int)L.size() <= LEN)
        L = '0'+L;
    while ((int)R.size() <= LEN)
        R = '0'+R;


    memset(dp,0,sizeof(dp));
    dp[0][0][0][0][0] = 1;

    int ans = 0;

    for (int i = 0; i <= LEN; i++)
        for (int j = 0; j <= i; j++)
           for (int k = 0; j+k <= i; k++)
               for (int l = 0; l < 2; l++)
                  for (int r = 0; r < 2; r++){
                        if (!dp[i][j][k][l][r])
                            continue;

                        //cerr << i <<" "<<j<<" "<<k<<" "<<l<<" "<<r<<endl;
                           
                        for (int NV = (l?0:(L[i]-'0')); NV <= (r?9:(R[i]-'0')); NV++){
                            ans = max(ans,(j+(NV==4))*(k+(NV==7)));
                            dp[i+1][j+(NV==4)][k+(NV==7)][l|(NV != (L[i]-'0'))][r|(NV != (R[i]-'0'))] = true;
                        }
                            
                    }
    //cerr<<endl;
    printf("%d\n",ans);
    return ;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif  

  int t;
  scanf("%d",&t);

  while (t-->0)
    solve();

  return 0;
}