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

char s[200][200];
ld wp[200],owp[200],oowp[200];
int win[200],cnt[200];
int n;

void solve(){
    scanf("%d",&n);
    for (int i=0;i<n;i++){
        wp[i] = owp[i] = oowp[i] = win[i] = cnt[i] = 0;
        for (int j=0;j<n;j++){
            scanf(" %c ",&s[i][j]);
            if (s[i][j] == '0')
                cnt[i] ++;
            else if (s[i][j] == '1')
                cnt[i] ++,win[i] ++;                
        }
        wp[i] = win[i] *1.0 / cnt[i];
    }
    
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++)
            if (s[i][j] != '.')
                owp[i] += (wp[j]*cnt[j] - (s[j][i] == '1'))/(cnt[j]-1);            
        owp[i] /= cnt[i];        
    }

    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++)
            if (s[i][j] != '.')
               oowp[i] += owp[j];/*cnt[j] - wp[i])/(cnt[j]-1);*/
        oowp[i] /= cnt[i];
    }

    for (int i=0;i<n;i++){
        cout.precision(15);
//        cerr<<wp[i]<<" "<<owp[i]<<" "<<oowp[i]<<endl;
        cout << fixed << 0.25*wp[i] + 0.5*owp[i] + 0.25 * oowp[i] << endl;
    }

  //  cerr<<endl;
        
}

int main(){
    freopen(INFILE.data(),"r",stdin);
    freopen(OUTFILE.data(),"w",stdout);
    PreCalc();
    int t;
    cin>>t;
    for (int i=1;i<=t;i++)
        {
            printf("Case #%d:\n",i);
            solve();
            if (i>t-20 || i%10==0)
                cerr<<"SOLVED:"<<i<<endl;
        }
  return 0;
}