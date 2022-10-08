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

const string TASKNAME = "C";
const string TASKMOD = "large";
const string INFILE = TASKNAME+"-"+TASKMOD+".in";
const string OUTFILE = TASKNAME+"-"+TASKMOD+".out";



void PreCalc(){
}

string A,B;

int get(string s){
    int temp;
    sscanf(s.data(),"%d",&temp);
    return temp;
}

string get(int val){
    char s[20];
    sprintf(s,"%d",val);
    return s;
}

void solve(){
    cin >> A >> B;
    int a = get(A);
    int b = get(B);

    ll cnt = 0;

    for (int n = a; n <= b; n++){
        string temp = get(n);
        vector<int> v;
        for (int i = 0; i < (int)A.size(); i++){
            rotate(temp.begin(),temp.begin()+1,temp.end());
            int m = get(temp);
            if (n < m && m <= b){
//                cerr << n <<" "<<m<<endl;
                v.pb(m);
            }
        }
        sort(v.begin(),v.end());
        cnt += unique(v.begin(),v.end()) - v.begin();
    }  

    cout << cnt << endl;
    return;
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
            if (i>t-20 || i%1==0)
                cerr<<"SOLVED:"<<i<<endl;
        }


  return 0;
}