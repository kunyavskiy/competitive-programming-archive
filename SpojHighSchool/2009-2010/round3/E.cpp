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

const int base = 1000;

int a[500];       
string s; 

inline int atoi(int l,int r)
{
  int res=0;
  for (int i=l;i<r;i++)
    res=res*10+s[i]-'0';
  return res;
}


inline void read()
{
  cin>>s;                                
  a[0]=0;
  for (int i=(int)s.length(); i>0; i-=3)
    if (i < 3)
      a[++a[0]]=atoi (0, i);
    else
      a[++a[0]]=atoi (i-3, i);
}                                     
inline long long ost(long long b)
{
  long long carry = 0;
  for (int i=a[0]; i>0;i--) 
  {  
      carry = a[i] + carry * base;
      carry%=b;
  }
  return carry;
}
                           
int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif      
  int n;   
  while (true)
  {           
    scanf("%d ",&n);
    if (n==0)
      break;               
    read();                         
    if (ost((n-1)*1ll*(n-1))==0)
      printf("Yes\n");
    else
      printf("No\n");
  }
  return 0;
}