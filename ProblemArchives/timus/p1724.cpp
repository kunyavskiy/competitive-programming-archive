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
    #define next next_mkdlsmfdgkl
    #define hash hash_mdfdsgdhgfm
    #undef assert
    #define assert(x) if (!(x)) throw 1
    #define sqrt(x) sqrt((double)(x))
#endif

using namespace std;

typedef long long ll;
typedef long double ld;  

const int MAXN = 110000;
const int MAXLST = 1<<17;
const int MAXSZ = 2*MAXLST + 10;

struct item{
   int a,b;

   void merge(const item& l,const item& r){
      a = min(l.a,r.a);
      b = max(l.b,r.b);
   }
   item(){
      b = -(a = 1<<30);
   }
   void print(){
      cerr << "("<<a <<" "<<b<<")";
   }
};

char s[MAXN];

item tree[MAXSZ];
int lst;

void init(){
    int n = strlen(s);
    lst = 2;
    for (;lst < n; lst *= 2);

    stack<int> st;

    for (int i = 0; i < n; i++){
        if ('A' <= s[i] && s[i] <= 'Z')
            st.push(i);
        else {
            if (st.empty() || (s[st.top()] - 'A' + 'a' != s[i])){
                tree[i+lst].a = -(1<<30);
                while (!st.empty()){
                    tree[st.top()+lst].b = (1<<30);
                    st.pop();
                }
            }
            else {
                tree[st.top()+lst].b = i;
                tree[i+lst].a = st.top();
                st.pop();
            }
        }
    }


    while (!st.empty()){
        tree[st.top()+lst].b = (1<<30);
        st.pop();
    }


    for (int i = lst-1; i > 0; i--)
        tree[i].merge(tree[2*i],tree[2*i+1]); 

}

item get(int v,int l,int r,int L,int R){
    if (r < L || R < l)
        return item();
    if (L <= l && r <= R)
        return tree[v];
    item res;
    res.merge(get(2*v,l,(l+r)/2,L,R), get(2*v+1,(l+r)/2+1,r,L,R));
    return res;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    gets(s);
    init();

    int m;
    scanf("%d",&m);

    for (int i = 0; i < m; i++){
        int a,b;
        scanf("%d %d",&a,&b);
        --a,--b;
        item temp = get(1,0,lst-1,a,b);
        //temp.print();
        printf("%d",(int)(a <= temp.a && temp.b <= b));
    }

    return 0;
}