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
//#define fileinout
using namespace std;

ld eps=1E-07;

int x,y,vx,vy;

ld f(ld t)
{
  ld x1=x-vx*1.0*t;
  ld y1=y+vy*1.0*t;
  return x1*x1+y1*y1;
}

ld f1()
{
    ld ch=vx*1.0*x-vy*1.0*y;
    ld zn=vx*1.0*vx+vy*1.0*vy;
    if (ch<0)
      return 0;
    return ch/zn;

}

       
int main()
{
  #ifdef fileinout
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif         
  for (;true;)
  {
    scanf("%d %d %d %d",&vx,&x,&vy,&y);
    if ((x==0) && (vx==0) && (y==0) && (vy==0))
      break;            
    printf("%.6f\n",sqrt(min(f(0),f(f1()))));
  }
  return 0;
}