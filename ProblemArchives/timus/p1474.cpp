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


char s[1111];

vector<int> ans;
int n;

void gow(int cnt){
    for (int i = 2*n; i >= 0 && cnt > 0; i--){
        if (s[i] == 'W' && i < 2*n && s[i+1] == '_')
            swap(s[i],s[i+1]),ans.pb(i),cnt--;
        if (s[i] == 'W' && i < 2*n-1 && s[i+1] == 'B' && s[i+2] == '_')
            swap(s[i],s[i+2]),ans.pb(i),cnt--;       
    }
}


void gob(int cnt){
    for (int i = 0; i < 2*n+1 && cnt > 0; i++){
        if (s[i] == 'B' && i > 0 && s[i-1] == '_')
            swap(s[i],s[i-1]),ans.pb(i),cnt--;
        if (s[i] == 'B' && i > 1 && s[i-1] == 'W' && s[i-2] == '_')
            swap(s[i],s[i-2]),ans.pb(i),cnt--;       
    }
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
   
   scanf("%d",&n);

   for (int i = 0; i < n; i++)
      s[i] = 'W';
   for (int j = n+1; j < 2*n+1; j++)
      s[j] = 'B';
   s[n] = '_';


   for (int i = 1; i <= n; i++){
     if (i & 1)
        gow(i);
     else
        gob(i);
   }



   for (int i = n; i >= 0; i--)
      gow(n),gob(n);

   printf("%d\n",(int)ans.size());
   for (int i = 0; i < (int)ans.size(); i++)
     printf("%d ",ans[i]);   
   return 0;
}