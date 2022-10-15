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



set<string> vals;


void add(string s){
    vals.insert(s);
}

char buf[25];

                   
void find(string s){
    set<string>::iterator iter = vals.lower_bound(s);

    puts(s.data());

    int l = s.size();

    for (int i = 0; i < 20; i++){
        if (iter == vals.end())
            break;
        if ((int)iter->size() < l || s != string(iter->begin(),iter->begin()+l))
            break;
        puts(("  "+*iter).data());
        ++iter;
    
    } 
}
    

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  //cerr << sizeof(node) << endl;

  add("sun");

  while (true){
    if (scanf(" ? %s",buf) == 1){
        //cerr <<"find: "<<buf << endl;
        find(buf);
    }else if (scanf(" + %s",buf) == 1){
        //cerr <<"add: "<<buf << endl;
        add(buf);
    }else
        break;        
  }

  return 0;
}