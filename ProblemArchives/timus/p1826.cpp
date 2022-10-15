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
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

int n;
vector <int> a;
 
int main()
{

  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
   cin >> n;
   for (int i = 0; i < n; i++)
   {
       int temp;
       cin >> temp;
       a.pb(temp);
   }
 
   int res = 0;


   sort(a.begin(),a.end()); 
 
   while (!a.empty()){

   		if (a.size() <= 2){
   			res += a[a.size()-1];
   			a.clear();
   		}
   		else if (a.size() == 3){
		   for (int i = 0; i < (int)a.size(); i++)
  		   	  res += a[i];
           a.clear();
        } else {
           if (2*a[1] + a[0] + a[a.size()-1] < 2*a[0] + a[a.size()-1] + a[a.size()-2]){
              res += 2*a[1] + a[0] + a[a.size()-1];
              a.pop_back();a.pop_back();
           }
           else {
              res += 2*a[0] + a[a.size()-1] + a[a.size()-2];
              a.pop_back();a.pop_back();
           }
       }
  }
 
  cout << res << endl;
 
  return 0;
}
