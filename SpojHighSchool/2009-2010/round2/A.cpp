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
//#define fileinout
using namespace std;



void sort_3(int &a,int &b,int &c)
{
  if (a<b)
    swap(a,b);
  if (a<c)
    swap(a,c);
  if (b<c)
    swap(b,c);
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("A.in","r",stdin);
    freopen("A.out","w",stdout);
  #endif
//  return 0;
  int test;
  scanf("%d",&test);
  int n,x1,y1,z1,x2,y2,z2,x,y,z;

 // return 0;
  const ld EPS=1E-20;
  for (;test;--test)
  {
     scanf("%d",&n);
     scanf("%d %d %d",&x1,&y1,&z1);
     scanf("%d %d %d",&x2,&y2,&z2);
     x=abs(x1-x2);
     y=abs(y1-y2);
     z=abs(z1-z2);
        
     if (n<x+y+z)
     {
        printf("0.0000000000\n");
        continue;
     }
    
     if ((n-x-y-z)%2!=0)
     {
        printf("0.0000000000\n");
        continue;
     }
     ld p=0;
     sort_3(x,y,z);
     int c=n-x-y;
     int c1=(c+z)/2;
     int c2=(c-z)/2;
     int a1=x;
     int a2=0;
     int b1=y;
     int b2=0;
     ld pa=1;
     for (int i=1;i<=n;i++)
        {
          pa*=i;
          pa/=6;
          if (i<=x)
            pa/=i;
          if (i<=y)
            pa/=i;
          if (i<=c1)
            pa/=i;
          if (i<=c2)
            pa/=i;
        }         
     for (int a=x;c>=z;a+=2,c-=2)
     {
        int cc=c;
        int cc1=c1;
        int cc2=c2;
        ld pb=pa;
        b1=y;
        b2=0;   
        for (int b=y;cc>=z;b+=2,cc-=2)
           {
             p=p+pb;                            
             ++b1;
             ++b2;
             if (b1)
              pb/=b1;
             if (b2)
               pb/=b2;
             if (cc1)
               pb*=cc1;
             if (cc2)
               pb*=cc2;
             cc1--;
             cc2--;
           }
        ++a1;
        ++a2;
        if (a1)
          pa/=a1;
        if (a2)
          pa/=a2;
        if (c1)
          pa*=c1;
        if (c2)
          pa*=c2;
        --c1;
        --c2;
     }       
     printf("%.10llf\n",p);     
  }          
  return 0;
}