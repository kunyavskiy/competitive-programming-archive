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
           
ld a,b,c,d;
ld f(ld h)
{
  ld w=d+h;
  ld l=(a-c)*h/(b-d);
  l=a-l;
  return w*l;
}
ld max(ld a,ld b,ld c)
{
  return max(a,max(b,c));
}
int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  const ld eps=1E-6;
  while (true)
  {                                          
    cin>>a>>b>>c>>d;
    //cerr<<a<<" "<<b<< " "<<c<<" "<<d<<endl;
    assert(a==(int)a);
    assert(b==(int)b);
    assert(c==(int)c);
    assert(d==(int)d);
    if ((a==0) && (b==0) && (c==0) && (d==0))
       break;                              
    if (a==c)
      {
       if (b==d)
          {
            printf("0.0000000\n");
            continue;
          }
        assert(false);
      }
    assert(b!=d); 
   // cerr<<"!"<<endl;
    ld lf=0;
    ld rg=b-d;                                         
   //   cerr<<lf<<" " <<rg<<" "<<f(lf)<<" "<<f(rg)<<endl;
    while (abs(f(rg)-f(lf))>eps)
    {
      ld l1=lf+(rg-lf)/3;
      ld r1=rg-(rg-lf)/3;
      ld x1=f(l1);
      ld x2=f(r1);
      if (x1>x2)
        rg=r1;
      else
        lf=l1;
  //    cerr<<lf<<" " <<rg<<" "<<f(lf)<<" "<<f(rg)<<endl;                                              
    }      
    ld s=a*b-(a-c)*(b-d)/2; 
    printf("%.7llf\n",s-max(f(lf),f(rg),f((lf+rg)/2)));
  }
  return 0;
}                        