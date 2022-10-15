// WHAT'S WRONG WITH YOU GUYS??? WTF IS PENTIUM 3??? PLEASE UPGRADE SERVERS! IT'S RIDICULOUS TO TEST SOLUTIONS ON 9-YEAR OLD SYSTEM!"
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

#undef assert
#define assert(x) if (!(x)) throw 1;

using namespace std;

typedef long long ll;
typedef long double ld;

const int dx[4] = {0,-1,0,1};
const int dy[4] = {-1,0,1,0};
                              
const int d1[6] = {1,0,1,2,3,0};
const int d2[6] = {3,2,2,3,0,1};
int p1[6],p2[6];

const int MAXN = 100000;


int n,m;
int q;

int cnt[MAXN];
int per;
int pper;

map<ll,int> have;

inline int num(int a,int b){
   return a*m+b; 
}

bool good(int x,int y){
    return 0 <= x && x < n && 0 <= y && y < m;
}


void recalc(ll& mask){
    int val[n][m];
    int sumx[n],sumy[m];
    memset(sumx,0,sizeof(sumx));
    memset(sumy,0,sizeof(sumy));
    
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++){
            val[i][j] = !!(mask & (1LL<<num(i,j)));
            sumx[i] += val[i][j];
            sumy[j] += val[i][j];
        }

    mask = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (val[i][j]){
                int x = (sumx[i] + sumy[j] - val[i][j]) % 6;
                mask ^= (1LL<<num(i,j));

                for (int k = 1; ; k++){
                    int ni = i + dx[d1[x]]*p1[x]*k;
                    int nj = j + dy[d1[x]]*p2[x]*k;
                    if (!good(ni,nj))
                        break;
                    mask ^= 1LL<<num(ni,nj);
                }
                for (int k = 1; ; k++){
                    int ni = i + dx[d2[x]]*p1[x]*k;
                    int nj = j + dy[d2[x]]*p2[x]*k;
                    if (!good(ni,nj))
                        break;
                    mask ^= 1LL<<num(ni,nj);
                }

            }

}



int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output2.txt","w",stdout);
  #endif
    scanf("%d %d %d",&n,&m,&q);
    int sx,sy;
    scanf("%d %d",&sx,&sy);
    --sx,--sy;
    ll curm = (1LL<<num(sx,sy));

    have[curm] = 0;
    cnt[0] = 1;

    for (int i = 0; i < 6; i++){
        scanf("%d %d",&p1[i],&p2[i]);
    }

    int id = 0;

    while (id < MAXN-10){
        id++;
        recalc(curm);
        cnt[id] = __builtin_popcountll(curm);
    }


    for (int i = 0; i < q; i++){
        ll ans = 0;
        ll val;
        cin >> val;
        ++val;

        for (int j = 0; j < val; j++)
            ans += cnt[j];

        cout << ans << endl;
    }

    return 0;
}