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

const string TASKNAME = "C";
const string TASKMOD = "large";
const string INFILE = TASKNAME+"-"+TASKMOD+".in";
const string OUTFILE = TASKNAME+"-"+TASKMOD+".out";


const int MAXN = 2111111;

int p[MAXN];
vector<int> pr;


void PreCalc(){
    for (int i=2;i<MAXN;i++){
        if (p[i] == 0){
            p[i] = i;
            pr.pb(i);
        }
        for (int j=0;j<pr.size() && pr[j] <= p[i] && i*1LL*pr[j] <= MAXN;j++)
            p[i*pr[j]] = pr[j];
    }
}

void solve(){
    int64 n;
    cin >> n;
    int64 ans = 0;
    for (int i=0;i<pr.size();i++){
        int64 tmp = pr[i];
        for (;tmp <= n / pr[i];tmp*=pr[i])
            ans++;
    }
    cout << ans +(n!=1)<< endl;
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