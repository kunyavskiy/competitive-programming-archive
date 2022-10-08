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
const string TASKMOD = "large";
const string INFILE = TASKNAME+"-"+TASKMOD+".in";
const string OUTFILE = TASKNAME+"-"+TASKMOD+".out";



void PreCalc(){
}

int L[1100];
int P[1100];
int ord[1100];
int n;

bool cmp(int i,int j){
    return L[i] * P[j] < L[j] * P[i];
}

void solve(){
    scanf("%d",&n);
    for (int i = 0; i < n; i++)
        scanf("%d",&L[i]);
    for (int i = 0; i < n; i++)
        scanf("%d",&P[i]);
    for (int i = 0; i < n; i++)
        ord[i] = i;
    stable_sort(ord,ord+n,cmp);
    for (int i = 0; i < n; i++)
        printf("%d%c",ord[i]," \n"[i==n-1]);
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