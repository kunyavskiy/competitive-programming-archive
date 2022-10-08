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

typedef long long ll;
typedef long double ld;

const string TASKNAME = "A";
const string TASKMOD = "small";
const string INFILE = TASKNAME+"-"+TASKMOD+".in";
const string OUTFILE = TASKNAME+"-"+TASKMOD+".out"; 

void PreCalc(){
}

void solve(){
    vector<int> d,l,dp;
    int n;
    scanf("%d",&n);
    d.resize(n+1);
    l.resize(n+1);
    dp.resize(n+1);
    for (int i = 0; i < n; i++){
       scanf("%d %d",&d[i],&l[i]);
       dp[i] = -1;
    }
    scanf("%d",&d[n]);
    l[n] = 0;
    dp[n] = -1;
    dp[0] = d[0];

    for (int i = 0; i < n; i++){
        if (dp[i] == -1)
            continue;
        //cerr << i <<" "<<dp[i] << endl;   
        for (int j = i+1; j <= n && d[i] + dp[i] >= d[j]; j++)
            dp[j] = max(dp[j],min(d[j] - d[i],l[j])); 
    }

    if (dp[n] != -1)
        printf("YES\n");
    else
        printf("NO\n");
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