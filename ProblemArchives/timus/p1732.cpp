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

string s;

bool used[2100000];

int p[2100000];



int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    getline(cin,s);
    int ptr = 0;

    string t;


    while (cin >> t){
        p[0] = 0;        
        for (int i = 1; i < t.size(); i++){
            int j = p[i-1];
            for (;j && t[j] != t[i]; j = p[j-1]);
            if (t[j] == t[i]) j++;
            p[i] = j;
        }
    

        bool q = false;
        int curp = 0;

        for (;ptr < s.size() && !q; ptr++){
            for (;curp && t[curp] != s[ptr]; curp = p[curp-1]);
            if (t[curp] == s[ptr]) curp++;
            if (curp == t.size()){
                q = true;
            }
        }

        if (!q){
            printf("I HAVE FAILED!!!\n");
            return 0;
        }           

        for (int j = ptr - (int)t.size(); j < ptr; j++)
            used[j] = true;
        ptr ++;    
    }

    for (int i = 0; i < s.size(); i++)
        if (!used[i] && s[i] != ' ')
            s[i] = '_';
    cout << s << endl;
    
    return 0;
}