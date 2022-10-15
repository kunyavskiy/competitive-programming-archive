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

using namespace std;

typedef long long ll;
typedef double ld;


const ld eps = 1e-8;

const int MAXN = 50010;

double x[MAXN];
double y[MAXN];
double z[MAXN];
int n;
              
double L,R;

bool cmp(const pair<ld,int>& a,const pair<ld,int>& b){
    if (abs(a.first - b.first) > eps)
        return a.first < b.first;
    return a.second > b.second;
}

bool check(ld H){
    vector<pair<ld,int> > ev;
    for (int i = 0; i < n; i++){
        if (y[i] > H){
          ev.pb(mp(min(R,max(x[i] - (y[i] - H) * z[i],L)), 1));
          ev.pb(mp(max(L,min(x[i] + (y[i] - H) * z[i],R)), -1));
        }
    }
    sort(ev.begin(),ev.end(),cmp);
                    
    if (!ev.size())
        return 0;
    if (abs(ev[0].first - L) > eps)
       return 0;


    int bal = 0;
    for (int i = 0; i < (int)ev.size(); i++){
        bal += ev[i].second;
        if (!bal && abs(ev[i].first - R) > eps)
            return 0;
    }
    return 1;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    scanf("%d",&n);
    scanf("%lf %lf",&L,&R);

    for (int i = 0; i < n; i++){
        scanf("%lf %lf %lf",&x[i],&y[i],&z[i]);
        z[i] = tan(z[i]/180 * M_PI);
    }

    ld l = 0;
    ld r = 1001;


    for (int i = 0; i < 70; i++){
        ld mid = (l+r)/2;
        if (check(mid))
           l = mid;
        else
           r = mid;
    }

    printf("%.12lf\n",(l+r)/2);
    return 0;
}