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
#define ld float
#define fileinout
using namespace std;

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  ld v=1450;                  
  cout<<fixed;
  cout.precision(30);         
  ld v1,t,f1,f2;
  for (;;)
  { 
    scanf("%f %f %f %f",&t,&v1,&f1,&f2);
    if (abs(t)<0.01)
      break;                            
    printf("%lf\n",t*v/2);  
  }
  return 0;
}