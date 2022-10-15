#include <cstdio>
#include <cmath>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

typedef long long ll;
typedef long double ld;

#define zero(a) memset (a, 0, sizeof(a))
#define pb push_back
#define mp make_pair
#define sz(a) ((int)(a.size()))
#define sqr(a) ((a) * (a))


#define lf(x) ((x)<<1)
#define rg(x) (((x)<<1)|1)


const int MAXN = 110000;
const int MAXLST = 1<<17;
const int MAXSZ = MAXLST*2 + 100;

struct item{
    ll sum,len,pref,suff,ans;

    item(ll sum,ll len,ll pref,ll suff,ll ans):sum(sum),len(len),pref(pref),suff(suff),ans(ans){
    }
    item(){
    }

    void print(){
        fprintf(stderr,"(%I64d %I64d %I64d %I64d %I64d)",sum,len,pref,suff,ans);
    }
};


ll coef[MAXSZ];   
item tree[MAXSZ];
ll upd[MAXSZ];
int n,m;
int lst,sz;
ll sumsq[MAXSZ];

//!!!!

item merge(const item& a,const item& b){
     item res;
     res.sum = a.sum + b.sum;
     res.len = a.len + b.len;
     res.pref = a.pref + b.pref + a.sum * b.len;
     res.suff = a.suff + b.suff + b.sum * a.len;
     res.ans = a.ans + b.ans + a.suff*b.len + b.pref*a.len;
     return res;
}

//\!!!!

void init(){
    lst = 2;
    for  (; lst < n; lst *= 2);
    sz = 2*lst - 1;
    for (int i = lst; i <= sz; i++)
        tree[i] = item(0,1,0,0,0);
    for (int i = lst -1 ; i > 0; --i)
        tree[i] = merge(tree[lf(i)],tree[rg(i)]);


    sumsq[0] = 0;

    //!!!!

    for (int i = 1; i <= lst; i++)
        sumsq[i] = sumsq[i-1] + i*1LL*(i-1);

    for (int i = 1; i <= lst; i++)
        coef[i] = i*1LL*i*1LL*(i+1)/2 - sumsq[i];

    /*for (int i = 1; i <= lst; i++)
        cerr << coef[i] <<" ";

    cerr << endl;*/


    //\!!!!
}


void add(int v,ll d){
    if (v > sz)
        return;
                                         

    upd[v] += d;
    item& ch = tree[v];


//cerr <<"!!!!!!!"<<v <<" "<<ch.len <<" "<<coef[ch.len]<<endl;

    //!!!!

    ch.sum += d*ch.len;
    ch.pref += ch.len*(ch.len+1)/2*d;
    ch.suff += ch.len*(ch.len+1)/2*d;
    ch.ans += coef[ch.len]*d;

    //\!!!!
}

void push(int v){
    if (upd[v] == 0)
        return;
    add(lf(v),upd[v]);
    add(rg(v),upd[v]);
    upd[v] = 0;
}



void update(int v, int l,int r,int L,int R,ll d){
    if (r < L || R < l)
        return;
    if (L <= l && r <= R){
        add(v,d);
        return;
    }
    push(v);
    update(lf(v),l,(l+r)/2,L,R,d);
    update(rg(v),(l+r)/2+1,r,L,R,d);
    tree[v] = merge(tree[lf(v)],tree[rg(v)]);
}

item get(int v, int l,int r,int L,int R){
    if (r < L || R < l)
        return item(0,0,0,0,0);
    if (L <= l && r <= R)
        return tree[v]; 
    push(v);
    return merge(get(lf(v),l,(l+r)/2,L,R), get(rg(v),(l+r)/2+1,r,L,R));
}


void printtree(){
    for (int i = 1; i <= sz; i++){
        tree[i].print();
        fprintf(stderr,"/%I64d ",upd[i]);
        if ((i&(i+1)) == 0)
            cerr << endl;
    }
    cerr << endl << endl;       
}

int main(void){
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  scanf("%d %d",&n,&m);
  init();
  for (int i = 0; i < m; i++){
        int a,b,c;
        if (scanf(" change %d %d %d",&a,&b,&c) == 3){
  //                cerr << "UPD " << a-1 << " "<<b-2 <<" "<<c << endl;
                update(1,0,lst-1,a - 1,b - 2,c);
        }
        else {
            scanf(" establish %d %d",&a,&b);
//              cerr << "GET " << a-1 << " "<<b-2  << endl;
            ll ans = get(1,0,lst-1,a-1,b-2).ans;
            ll len = b - a;
            len = len*(len+1)/2;
            cout.precision(15);
            cout << fixed << ans/double(len) << endl;
        }
    //  printtree();                                            
  }
  return 0;
}