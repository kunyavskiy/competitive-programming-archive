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



int dp[110][110];
int n,S,p;


void PreCalc(){
}

void solve(){
    memset(dp,0,sizeof(dp));    
    scanf("%d %d %d",&n,&S,&p);

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= S; j++)
            dp[i][j] = -(1<<20);

    dp[0][0] = 0;

    for (int i = 0; i < n; i++){
        int sum = 0;
        scanf("%d",&sum);

        for (int j = 0; j <= S; j++)
            for (int a = 0; a <= 10; a++)
                for (int b = max(0,a-2); b <= a; b++)
                    for (int c = b; c <= a; c++)
                        if (a+b+c == sum)
                            dp[i+1][j+(b == a-2 || c == a-2)] = max(dp[i+1][j+(b == a-2 || c == a-2)], dp[i][j]+(a >= p));
    }

    printf("%d\n",dp[n][S]);
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