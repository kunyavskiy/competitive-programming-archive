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

double p[110000];
int A,B;

void solve(){
    scanf("%d %d",&A,&B);
    for (int i = 1; i <= A; i++)
        scanf("%lf",&p[i]);
    p[0] = 1;
    for (int i = 1; i <= A; i++)
        p[i] *= p[i-1];

    ld ans = 1e9;

    for (int i = 0; i <= A; i++){
        ld cur;
        cur = 0;

        cur += (p[i] * (B-i + 1)) + (1-p[i])*(B-i+1 + B+1);
        if (i == 0) cur += min(A-i,1);
        else cur += A - i;            

//        cerr << i <<" "<<cur <<" "<<p[i]<< endl;

        ans = min(ans,cur);
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