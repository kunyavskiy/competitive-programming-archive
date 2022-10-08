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
const string TASKMOD = "small";
const string INFILE = TASKNAME+"-"+TASKMOD+".in";
const string OUTFILE = TASKNAME+"-"+TASKMOD+".out";


struct polygon{
    vector<int> v;

    polygon split(int l,int r){
        if (l > r)
            swap(l,r);
        assert(in(l,r));
        int x = lower_bound(v.begin(),v.end(),l) - v.begin();
        int y = lower_bound(v.begin(),v.end(),r) - v.begin();
        polygon p;
        p.v = vector<int>(v.begin()+x,v.begin()+y+1);
        v.erase(v.begin()+x+1,v.begin()+y);
        return p;
    }
    bool in(int l,int r){
        return binary_search(v.begin(),v.end(),l) && binary_search(v.begin(),v.end(),r);
    }
    int& operator[](int a){
        assert(a < (int)v.size() && a>=0);
        return v[a];        
    }
    int operator[](int a)const{
        assert(a < (int)v.size() && a>=0);
        return v[a];        
    }
    int size()const{
        return (int)v.size();
    }
    polygon(){
    }
    void push_back(int x){
        v.pb(x);
    }
    void print(){
        cerr<<"POLY! ";
        copy(v.begin(),v.end(),ostream_iterator<int>(cerr," "));
        cerr<<endl;
    }
};

vector<polygon> p;



void PreCalc(){
}

const int MAXN = 2222;

int u[MAXN];
int v[MAXN];
bool dused[MAXN];
int n;

int col[MAXN];
bool used[MAXN];
int cnt;
int m;

bool check(){
//    copy(col,col+n,ostream_iterator<int>(cerr," "));
//    cerr<<endl;
    for (int i=0;i<(int)p.size();i++){
        for (int j=0;j<cnt;j++)
            used[j] = 0;
        for (int j=0;j<p[i].size();j++)
            used[col[p[i][j]]] = true;
        for (int j=0;j<cnt;j++)
            if (!used[j]){
                return false;
            }
    }
    return true;        
}



void splitpolygons(){
   for (int i=0;i<m;i++){
       --v[i],--u[i];
       for (int j=0;j<(int)p.size();j++)
         if (p[j].in(u[i],v[i])){    
            polygon tmp =p[j].split(u[i],v[i]);
            p.pb(tmp);
            break;
         }
   }                          
}

void gen1(polygon p){
    for (int i=0;i<cnt;i++)
        used[i] = 0;
    for (int i=0;i<p.size();i++)
        if (col[p[i]] != -1)
            used[col[p[i]]] = true;
    int pt=0;
    for (int i=0;i<p.size();i++){   
        if (col[p[i]] != -1)
            continue;
        while (pt != cnt-1 && used[pt])
            ++pt;
        col[p[i]] = pt;
        if (pt == cnt-1){
            pt = 0;
            memset(used,0,sizeof(used));
        }
        used[pt] = true;
    }
}

void changecolor(int a,int b,int c){
   // cerr<<"!!!!!!!!!"<<a<<" "<<b<<" "<<c<<endl;
    if (a > b)
        swap(a,b);
    int c1 = col[a];
    int c2 = col[b];
    if (a< c && c <b){  
        for (int i=0;i<=a;i++)
            if (col[i] == c1 || col[i] == c2)
                col[i] = col[i] ^ c1 ^ c2;
        for (int i=b;i<=n;i++)
            if (col[i] == c1 || col[i] == c2)
                col[i] = col[i] ^ c1 ^ c2;
        return;
    }
    for (int i=a;i<=b;i++)
       if (col[i] == c1 || col[i] == c2)
          col[i] = col[i] ^ c1 ^ c2;
}

void gen(polygon p){  
    //p.print();
    int best = -1;
    for (int i=0;i<m;i++)
        if (!dused[i] && p.in(u[i],v[i])){
            if (best == -1 || (v[best] - u[best] > v[i] - u[i]))
                best = i;
        }
    dused[best] = true;
    if (best == -1){
        gen1(p);
        return;
    }                  
    polygon p1 = p.split(u[best],v[best]);
    if (p.size() < p1.size()){
        swap(p,p1);
    }
    gen(p);
    if (col[u[best]] != col[v[best]] || (p1.size() -1 >= cnt)){   
        gen1(p1);
        return;
    }
    for (int i=0;i<m;i++)
        if ((u[i] == u[best] || v[i] == u[best]) && col[u[i]+v[i]-u[best]]!=-1){
            if (i == best)
                continue;
            if (col[v[i]] != col[u[i]]){
                changecolor(v[i],u[i],v[best]);
                gen1(p1);
                return;
            }
        }
    if (col[u[best]] == 0)
        col[u[best]] = 1;
    else
        col[u[best]] = 0;
    gen1(p1);        
}


void solve(){
    scanf("%d %d",&n,&m);
    polygon tmp;
    p.clear();
    p.pb(polygon());
    for (int i=0;i<n;i++){
        p[0].pb(i);
        col[i] = -1;
    }
    tmp = p[0];
    for (int i=0;i<m;i++)
        scanf("%d",&u[i]);    
    for (int i=0;i<m;i++){
        scanf("%d",&v[i]);
        dused[i] = false;
    }
    splitpolygons();
    cnt = 1<<30;
    for (int i=0;i<p.size();i++)
        cnt = min(cnt,p[i].size());

    gen(tmp);

    assert(check());
    cout << cnt << endl;
    for (int i=0;i<n;i++)
        cout << col[i]+1 << " \n"[i==n-1];
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
