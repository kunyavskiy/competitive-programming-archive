#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <sstream>
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

struct node{
    string name;
    map<string,node*> next;
    node(){
    }
    node(string s){
        name = s;
    }
};

node* root;

void add(string s){
    for (int i = 0; i < (int)s.size(); i++)
        if (s[i] == '\\')
            s[i] = ' ';
    stringstream str(s);

    node* t = root;
    for (;str >> s;){
        if (t->next.find(s) == t->next.end())
            t->next[s] = new node(s);
        t = t->next[s];
    }
}

void print(node* v,int deep){
    if (deep >= 0){
        for (int i = 0; i < deep; i++)
            printf(" ");
        printf("%s\n",v->name.data());
    }

    for (map<string,node*>::iterator iter = v->next.begin(); iter != v->next.end(); ++iter)
        print(iter->second,deep+1);
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    string s;
    getline(cin,s);
    int n;
    sscanf(s.data(),"%d",&n);
    root = new node();
    for (int i = 0; i < n; i++)
        getline(cin,s),add(s);


    print(root,-1);

    return 0;
}