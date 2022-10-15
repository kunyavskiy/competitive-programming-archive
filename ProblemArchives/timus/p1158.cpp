#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

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
#include <memory.h>
#include <stack>
#define mp make_pair
#define pb push_back                     
#define setval(a,v) memset(a,v,sizeof(a))



#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
	#define M_PI 3.1415926535897932384626433832795
    #define prev prev_dsfdfgfhgfh
    #undef assert
    #define assert(x) if (!(x)) throw 1
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

bool ok[256];


typedef vector<int> tlong;

void print(const tlong&);

void add(tlong& a,const tlong& b){
    /*print(a);
    cout <<" + ";
    print(b);
    cout <<" = \n";*/
    int c = 0;
    for (int i = 0; i < b.size() || c; i++){
        if (i == a.size())
            a.pb(0);
        c += a[i];
        if (i < b.size())
            c += b[i];
        a[i] = c % 10;
        c /= 10;
    }
   // print(a);
//    cout << endl << endl;
    
}


struct node{
    node* next[256];
    node* lnk;
    node* p;
    unsigned char c;
    tlong cnt[55];
    bool term;
    node(){
        memset(next,0,sizeof(next));
        lnk = p = 0;
        c = 0;
        for (int i = 0; i < 55; i++)
            cnt[i] = vector<int>(1,-1);           
        term = false;
    }
};

node* root;

void add(string s){
    node* t = root;
    for (int i = 0; i < (int)s.size(); i++){
        if (!t->next[(int)(unsigned char)s[i]]){
            node* temp = new node();
            temp->c = s[i];
            temp->p = t;
            t->next[(int)temp->c] = temp;
        }
        t = t->next[(int)(unsigned char)s[i]];            
    }
    t->term = true;    
}

int n,m,p;

node* getnext(node*,int);

node* getlnk(node* v){
    if (v->lnk)
        return v->lnk;
    if (v == root || v->p == root)
        v->lnk = root;
    else
        v->lnk = getnext(getlnk(v->p),v->c);
    v->term |= v->lnk->term;
    return v->lnk;       
}

node* getnext(node* v,int c){
    if (v->next[c])
        return v->next[c];
    if (v == root)
        return v->next[c] = v;
    return v->next[c] = getnext(getlnk(v),c);
}

vector<int> ZERO,ONE;

const tlong& calc(node* v,int len){
    if (!v->lnk)
        getlnk(v);
    if (v->term)
        return v->cnt[len] = ZERO;
    if (len == m)
        return v->cnt[len] = ONE;
    if (v->cnt[len].back() != -1)
        return v->cnt[len];    
    v->cnt[len] = ZERO;
    for (int i = 0; i < 256; i++)
        if (ok[i])
            add(v->cnt[len],calc(getnext(v,i),len+1));
    return v->cnt[len];
}

void print(const tlong& a){
    for (int i = a.size()-1; i >= 0; --i)
        printf("%d",a[i]);
    printf("\n");
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    string s;
    getline(cin,s);
    sscanf(s.data(),"%d %d %d",&n,&m,&p);
    root = new node();

    getline(cin,s);

    ZERO.pb(0);
    ONE.pb(1);


    for (int i = 0; i < n; i++)
        ok[(int)(unsigned char)(s[i])] = true;

    for (int i = 0; i < p; i++)
        getline(cin,s),add(s);


    print(calc(root,0));
    return 0;
}