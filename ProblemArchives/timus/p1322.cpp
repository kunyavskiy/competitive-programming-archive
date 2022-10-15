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


pair<char,int> s[110000];
int pos;
char buf[110000];
int id[110000];



int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    gets(buf);
    sscanf(buf,"%d",&pos);
    --pos;
    gets(buf);

    int n = strlen(buf);


    for (int i = 0; i < n; i++)
        s[i] = mp(buf[i],i);

    sort(s,s+n);
    for (int i = 0; i < n; i++)
        id[s[i].second] = i;

    string s = "";

    for (int i = 0; i < n; i++){
        s += buf[pos];
        pos = id[pos];
    }

    reverse(s.begin(),s.end());
    printf("%s\n",s.data());
    return 0;
}