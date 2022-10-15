#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <sstream>
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

struct obset{
    vector<string> v;

    void load(string s){
        stringstream str(s);
        while (str >> s)
            v.pb(s);
        sort(v.begin(),v.end());
    }

    void print(){
        if (v.empty())
            printf("No solution.\n");
        for (int i = 0; i < (int)v.size(); i++)
            printf("%s%c",v[i].data()," \n"[i==(int)v.size()-1]);
    }
};

void intersec(const obset& a, const obset& b,obset& res){
    res.v.resize(min(a.v.size(),b.v.size()));
    res.v.resize(set_intersection(a.v.begin(),a.v.end(),b.v.begin(),b.v.end(),res.v.begin()) - res.v.begin());
}

char buf[250];
char buf2[250];


map<string,obset> v;

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int n;
    scanf("%d",&n);

    for (int i = 0; i < n; i++){
        scanf(" %[^:] : %[^\r\n] ",buf,buf2);
        v[buf].load(buf2);
    }

    int m;
    scanf("%d",&m);
    for (int i = 0; i < m; i++){
        scanf(" %[^\r\n] ",buf2);
        obset lst;
        lst.load(buf2);

        obset res;

        for (int i = 0; i < (int)lst.v.size(); i++){
             if (i == 0)
                res = v[lst.v[i]];
             else {
                obset nres;
                intersec(res, v[lst.v[i]], nres);
                res = nres;
             }
        } 

        res.print();
    }               
    return 0;
}