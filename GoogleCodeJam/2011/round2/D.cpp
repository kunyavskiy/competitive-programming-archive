#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
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

const string TASKNAME = "D";
const string TASKMOD = "dbg";
const string INFILE = TASKNAME+"-"+TASKMOD+".in";
const string OUTFILE = TASKNAME+"-"+TASKMOD+".out";



void PreCalc(){
}


vector<int> g[500];
bitset<500> bt[500];
int n,m;

int dst[500];
int dp[500];



void bfs(){
    for (int i=0;i<n;i++)
        dst[i] = 1<<30;
    dst[1] = 0;
    queue<int> q;
    q.push(1);
    for (;!q.empty();){
        int v = q.front();q.pop();
        for (int i=0;i<g[v].size();i++){
            if (dst[g[v][i]] > dst[v] + 1){
                dst[g[v][i]] = dst[v] + 1;
                q.push(g[v][i]);
            }
        }
    }
}

bool used[500];

void solve(){                  
    scanf("%d %d",&n,&m);
    for (int i=0;i<n;i++){
        for (int j=0;j<500;j++)
            bt[i][j] = 0;
        g[i].clear();
    }
    for (int i=0;i<m;i++){
        int a,b;
        scanf("%d , %d",&a,&b);
        if (a != b){
            g[a].pb(b);             
            g[b].pb(a);
            bt[a].set(b);
            bt[b].set(a);
        }
    }
    bfs();
    queue<int> q;
    for (int i=0;i<n;i++)
        dp[i] = 0;
    dp[0] = bt[0].count();     
    q.push(0);             
    memset(used,0,sizeof(used));
    used[0] = 1;
    for (;!q.empty();){
        int v=q.front();q.pop();

        for (int i=0;i<g[v].size();i++){
            int to = g[v][i];
            if (dst[to] != dst[v] -1)
                continue;
            dp[to] = max(dp[to],dp[v] + ((to != 1)?(int(bt[to].count()) - int((bt[to]&bt[v]).count())-2):0));
            if (!used[to]){
                q.push(to);
                used[to] = true;
            }
        }                                                                                    
    }

    cout << dst[0] -1 <<" "<<dp[1]<<endl;

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