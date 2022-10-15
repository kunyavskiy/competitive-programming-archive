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

const int MAXN = 400000;


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

ll xmask[34][34][34];


void PreCalc(){
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int t = 0; t < 34; t++){
                int x = t % 6;
                ll& mask = xmask[i][j][t];
                mask ^= (1LL<<num(i,j));

                for (int k = 1; ; k++){
                    int ni = i + dx[d1[x]]*p1[x]*k;
                    int nj = j + dy[d1[x]]*p1[x]*k;
                    if (!good(ni,nj))
                        break;
                    mask ^= 1LL<<num(ni,nj);
                }
                for (int k = 1; ; k++){
                    int ni = i + dx[d2[x]]*p2[x]*k;
                    int nj = j + dy[d2[x]]*p2[x]*k;
                    if (!good(ni,nj))
                        break;
                    mask ^= 1LL<<num(ni,nj);
                }
            }
}


void recalc(ll& mask){
    int sumx[n],sumy[m];
    memset(sumx,0,sizeof(sumx));
    memset(sumy,0,sizeof(sumy));
    
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (mask & (1LL<<num(i,j))){
                sumx[i]++;
                sumy[j]++;
            }

    ll mask1 = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (mask & (1LL<<num(i,j)))
                mask1 ^= xmask[i][j][sumx[i] + sumy[j] - 1];
            
    mask = mask1;
}



int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
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

    PreCalc();

    int id = 0;

    while (true){
        assert(++id < MAXN);
        recalc(curm);

        if (have.find(curm) != have.end()){
            pper = have[curm];
            per = id - pper;
            break; 
        }
        cnt[id] = __builtin_popcountll(curm);
        have[curm] = id;
    }


    int sum = 0;
    for (int i = pper; i < id; i++)
        sum += cnt[i];



    for (int i = 0; i < q; i++){
        ll ans = 0;
        ll val;
        cin >> val;
        ++val;
        ll temp = max(0LL,val - pper)/per;
        ans += temp * sum;
        val -= temp * per;

        for (int j = 0; j < val; j++)
            ans += cnt[j];

        cout << ans << endl;
    }


    return 0;
}