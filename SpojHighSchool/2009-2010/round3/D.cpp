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
#define ld double
#define fileinout
using namespace std;

const ld g=9.80665;
const ld coef=(sqrt(2.0)-1)/2;

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  ld a,s,m,c;    
  float aa,mm,ss,cc;
  for (;true;){       
    scanf("%f %f %f %f",&aa,&mm,&ss,&cc);
    a=aa;
    m=mm;
    s=ss;
    c=cc;
    if ((a<1E-09))
      break;
    ld a1=/*(int)*/ (s/a);
//    if (a*a1<s)
//      a1++;        
    a1=a*a1*coef;
    ld a2=s*c; 
    if (a1<a2)
      printf("1\n");
    else
      printf("2\n");
  }
  return 0;
}