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
#include <iterator>
#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <stack>
#define mp make_pair
#define pb push_back   
#define setval(a,v) memset(a,v,sizeof(a))
using namespace std;

typedef long long int64;
typedef long double ld;

const string TASKNAME = "B";
const string TASKMOD = "large";
const string INFILE = TASKNAME+"-"+TASKMOD+".in";
const string OUTFILE = TASKNAME+"-"+TASKMOD+".out";



void PreCalc(){
}

const int MAXN = 510;

int sum[MAXN][MAXN];
int wxsum[MAXN][MAXN];
int wysum[MAXN][MAXN];
int c[MAXN][MAXN];
int n,m;

void precalc(){
    for (int i=0;i<n;i++)
        for (int j=0;j<m;j++){
            sum[i][j] = c[i][j];wxsum[i][j]=(i+1)*c[i][j];wysum[i][j]=(j+1)*c[i][j];
            if (i) sum[i][j] += sum[i-1][j],wxsum[i][j] +=wxsum[i-1][j],wysum[i][j]+=wysum[i-1][j];
            if (j) sum[i][j] += sum[i][j-1],wxsum[i][j] +=wxsum[i][j-1],wysum[i][j]+=wysum[i][j-1];
            if (i && j) sum[i][j] -= sum[i-1][j-1],wxsum[i][j] -= wxsum[i-1][j-1],wysum[i][j]-=wysum[i-1][j-1];
        }
}

inline int get(int lx,int ly,int rx,int ry,int from[][MAXN]){
    int ans = 0;
    ans += from[rx][ry];
    if (lx) ans -= from[lx-1][ry];
    if (ly) ans -= from[rx][ly-1];
    if (lx && ly) ans += from[lx-1][ly-1];
    return ans;        
}



void solve(){
    int ans = 2;
    int d;
    scanf("%d %d %d",&n,&m,&d);
    for (int i=0;i<n;i++)
        for (int j=0;j<m;j++){
            char C;
            scanf(" %c ",&C);
            c[i][j] = C-'0';
        }
    precalc();
    for (int i=0;i<n;i++)
        for (int j=0;j<m;j++)
            for (int cur = ans+1 + (ans%2 == 1);;cur+=2){
                int cur2 = cur/2;
                if (i - cur2 < 0 || j-cur2 < 0 || i+cur2 >=n || j+cur2 >= m)
                    break;

                int left = (j+1)*get(i-cur2,j-cur2,i+cur2,j,sum);
                left -= get(i-cur2,j-cur2,i+cur2,j,wysum);
                left -= c[i-cur2][j-cur2]*cur2;
                left -= c[i+cur2][j-cur2]*cur2;

                int right = - (j+1)*get(i-cur2,j,i+cur2,j+cur2,sum) + get(i-cur2,j,i+cur2,j+cur2,wysum);
                right -= c[i-cur2][j+cur2]*cur2;
                right -= c[i+cur2][j+cur2]*cur2;

                if (left != right)
                    continue;


                int up = (i+1)*get(i-cur2,j-cur2,i,j+cur2,sum) - get(i-cur2,j-cur2,i,j+cur2,wxsum);
                up -= c[i-cur2][j-cur2]*cur2;
                up -= c[i-cur2][j+cur2]*cur2;

                int down = - (i+1)*get(i,j-cur2,i+cur2,j+cur2,sum) + get(i,j-cur2,i+cur2,j+cur2,wxsum);
                down -= c[i+cur2][j-cur2]*cur2;
                down -= c[i+cur2][j+cur2]*cur2;

                if (down != up)
                    continue;
                ans = cur;
            }

    for (int i=0;i<n;i++)
        for (int j=0;j<m;j++)
            for (int cur = ans+1 + (ans%2 == 0);;cur+=2){
                int cur2 = cur/2;
                if (i - cur2+1 < 0 || j-cur2+1 < 0 || i+cur2 >=n || j+cur2 >= m)
                    break;

                int left = (2LL*j+3)*get(i-cur2+1,j-cur2+1,i+cur2,j,sum);
                left -= 2LL*get(i-cur2+1,j-cur2+1,i+cur2,j,wysum);
                left -= c[i-cur2+1][j-cur2+1]*(2LL*cur2-1);
                left -= c[i+cur2][j-cur2+1]*(2LL*cur2-1);

                int right = - (2LL*j+3)*get(i-cur2+1,j+1,i+cur2,j+cur2,sum) + 2LL*get(i-cur2+1,j+1,i+cur2,j+cur2,wysum);
                right -= c[i-cur2+1][j+cur2]*(2LL*cur2-1);
                right -= c[i+cur2][j+cur2]*(2LL*cur2-1);

                if (left != right)
                    continue;


                int up = (2LL*i+3)*get(i-cur2+1,j-cur2+1,i,j+cur2,sum) - 2LL*get(i-cur2+1,j-cur2+1,i,j+cur2,wxsum);
                up -= c[i-cur2+1][j-cur2+1]*(2LL*cur2-1);
                up -= c[i-cur2+1][j+cur2]*(2LL*cur2-1);

                int down = - (2LL*i+3)*get(i+1,j-cur2+1,i+cur2,j+cur2,sum) + 2LL*get(i+1,j-cur2+1,i+cur2,j+cur2,wxsum);
                down -= c[i+cur2][j-cur2+1]*(2LL*cur2-1);
                down -= c[i+cur2][j+cur2]*(2LL*cur2-1);

                if (down != up)
                    continue;
                ans = cur;
       }
   





   if (ans == 2)
      cout << "IMPOSSIBLE\n";
   else
      cout << ans << endl;

                          
}

int main(){
    freopen(INFILE.data(),"r",stdin);
    freopen(OUTFILE.data(),"w",stdout);
    PreCalc();
    int t;
    cin>>t;
    for (int i=1;i<=t;i++)
        {
            printf("Case #%d: ",i);
            solve();
            if (i>t-20 || i%10==0)
                cerr<<"SOLVED:"<<i<<endl;
        }


  return 0;
}