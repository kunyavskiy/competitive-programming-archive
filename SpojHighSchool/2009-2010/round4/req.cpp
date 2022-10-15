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
#include <stack>
#define mp make_pair
#define pb push_back                     
#define int64 long long
#define ld long double
#define fileinout
using namespace std;

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  for (;true;)
  {
    int64 n,a;
    cin>>a>>n;
    if (a==0)
      break;
    cout<<max(n*n+(a-3)*n-(a-4),(int64)0)<<endl;;
  }         
  return 0;
}