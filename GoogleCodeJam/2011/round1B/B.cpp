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

const int MAXN = 500;

pair<int64,int64> pos[MAXN];
int64 d;
int64 n;

bool check(int64 x){
    int64 start = -(1LL<<60LL);
    for (int i=0;i<n;i++){
        start = max(start,pos[i].first - x);
        start += d*(pos[i].second-1);
        if (start > pos[i].first + x)
            return false;
        start += d;
    }
    return true;    
}

void solve(){
    //scanf("%d %d",&n,&d);
    cin>>n>>d;
    for (int i=0;i<n;i++){
//        scanf("%I64d %I64d",&pos[i].first,&pos[i].second);
        cin>>pos[i].first >> pos[i].second;
        pos[i].first *= 2;
    }
    d*=2;
    sort(pos,pos+n);
    int64 l = -1;
    int64 r = 1LL<<58LL;
    for (;r-l>1;){
        int64 mid = (l+r)/2;
        if (check(mid))
            r = mid;
        else
            l = mid;
    }
    assert(check(r));
    cout << r/2 << (r%2?".5":".0") <<endl;
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