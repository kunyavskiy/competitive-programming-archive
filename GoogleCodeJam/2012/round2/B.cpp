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

#define dbg(x) cerr.precision(5),copy(x.begin(),x.end(),ostream_iterator<ld>(cerr," ")),cerr<<endl
using namespace std;

typedef long long ll;
typedef long double ld;

const string TASKNAME = "B";
const string TASKMOD = "small";
const string INFILE = TASKNAME+"-"+TASKMOD+".in";
const string OUTFILE = TASKNAME+"-"+TASKMOD+".out";



void PreCalc(){
}

int W,L;

ld x[1100];
ld y[1100];

pair<int,int> r[1100];
int n;


void print(){
    for (int i = 0; i < n; i++)
        printf("%.3lf %.3lf ",(double)x[i],(double)y[i]);
    printf("\n");
}

bool tryit(){
    vector<ld> gr;
    vector<ld> val;
    gr.pb(0.0);
    val.pb(0.0);
    gr.pb(W);
    for (int i = 0; i < n; i++){
        int id = -1;
        for (int j = 0; j < (int)gr.size() - 1; j++)
            if (gr[j+1] - gr[j] >= (2-(j==0)-(j==(int)gr.size()-2))*r[i].first && val[j] + (2-(val[j] < (1e-9)))*r[i].first <= L + r[i].first){
                id = j;
                break;
            }  


        //cerr << gr[1] - gr[0] <<" "<<r[i].first <<" "<<L - val[0] << endl;

        if (id == -1)
            return false;

        ld temp = val[id];
                                            
        val[id] += (2 - (val[id] == 0))*r[i].first;
        x[r[i].second] = gr[id] + (1 - (id == 0))*r[i].first;
        y[r[i].second] = val[id] - r[i].first;
        gr.insert(gr.begin()+id+1,x[r[i].second] + r[i].first);
        val.insert(val.begin()+id+1,temp);

        //dbg(val);
        //dbg(gr);
        //cerr << endl;

        //cerr << gr[0] <<" "<<gr[1] <<" "<<gr[2] << endl;
        //cerr << val[0] <<" "<<val[2] << endl;

                                             
        //cerr <<"!!!!!"<<endl;
    }
    return true;
}

void solve(){
   scanf("%d",&n);
   scanf("%d %d",&W,&L);
   for (int i = 0; i < n; i++){
    scanf("%d",&r[i].first);
    r[i].second = i;
   }                    
   sort(r,r+n);
   reverse(r,r+n);
   if (tryit()){
    print();
    return;
   }
   assert(false);
   /*reverse(r,r+n);
   if (tryit()){
    print();
    return;
   }
   while (true){
    random_shuffle(r,r+n);
    if (tryit()){
        print();
        return;
    }
   }*/
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
            if (i>t-50 || i%10==0)
                cerr<<"SOLVED:"<<i<<endl;
        }

  return 0;
}