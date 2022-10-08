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

const string TASKNAME = "A";
const string TASKMOD = "large";
const string INFILE = TASKNAME+"-"+TASKMOD+".in";
const string OUTFILE = TASKNAME+"-"+TASKMOD+".out";



void PreCalc(){
}

void solve(){
    int s,r,x,n;
    ld t;
    cin>>x>>s>>r>>t>>n;
    vector<pair<int,int> > res;
    r -= s;
    for (int i=0;i<n;i++){
        int a,b,c;
        cin>>a>>b>>c;        
        res.pb(mp(c+s,abs(b-a)));
        x -= abs(b-a);
    }
    res.pb(mp(s,x));
    sort(res.begin(),res.end());

    ld ans = 0;
    for (int i=0;i<res.size();i++){
        ld need = res[i].second /(ld) (res[i].first + r);
        ld slow = res[i].second - min(need,t)*(res[i].first + r);
        ld fast = min(need,t)*(res[i].first + r);
        t -= fast / (res[i].first + r);
        ans += fast / (res[i].first + r);
        ans += slow / res[i].first;
    }   

    cout.precision(15);
    cout << fixed << ans << endl;
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