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


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    
    int n;
    vector<string> s;
    cin >> n;
    s.resize(n);
    for (int i = 0; i < n; i++)
        cin >> s[i];

    sort(s.begin(),s.end());
            
    if (s[0] == s.back() && s.size() <= 2){
        printf("0\n");
        return 0;
    }
    if (unique(s.begin(),s.end()) != s.end()){
        printf("Impossible\n");
        return 0;
    }
    if (s.size() == 2){
        cout << 1 << endl;
        cout << s[0]<<"-"<<s[1] <<endl;
        return 0;
    }

    string trash;

    for (;binary_search(s.begin(),s.end(),trash) || trash == "";){
        if (trash.size() == 10)
            trash = "";
        trash = trash + char('a' + rand()%26);
    }

    cout << s.size() << endl;
    for (int i = 0; i < n; i++)
        cout << s[i] <<"-"<<trash<<endl;

    return 0;
}