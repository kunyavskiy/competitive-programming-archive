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
            

int n,s,t;

bool dp[11000];
int a[210];

void recalc(int x){
    memset(dp,0,sizeof(dp));
    dp[0] = 1;

    for (int i = 0; i < n; i++)
        if (i != x){
            for (int j = 0; j+a[i] <= 10000; j++)
                dp[j+a[i]] |= dp[j];
        }
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    scanf("%d %d %d",&s,&t,&n);

    for (int i = 0; i < n; i++)
        scanf("%d",&a[i]);

    int ans = 0;

    for (int i = 0; i < n; i++){
        recalc(i);

        for (int j = 0; j < n; j++){
            if (i == j)
                continue;
            int ch = (s-t);
            int zn = (a[i]-a[j]);
            //cerr << ch <<" "<<zn << endl;
            if (ch*zn < 0)
                continue;
            /*if (zn == 0 && ch == 0){
                if (dp[s]){
                    ans++;
                }
                continue;
            }*/
            if (zn == 0)
                continue;
            if (abs(ch) % abs(zn) != 0)
                continue;

            int cnt = abs(ch)/abs(zn);
            //cerr << cnt << " "<<(s - a[i] * cnt)<<endl;
            if (s < a[i] * cnt)
                continue;
            if (dp[s - a[i]*cnt]){
                cerr <<i  << " "<<j<<endl;
                ans++;
            }
        }
    }

    cout << ans << endl;

  return 0;
}