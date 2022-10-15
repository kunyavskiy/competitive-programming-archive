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

const int MATRSIZE=32;
int modul;

struct matrix{
  vector<vector<int64> > m;
  inline matrix()
  {
    m.assign(MATRSIZE,vector<int64> (MATRSIZE,0));
  }
  inline matrix(int a)
  {
    m.assign(MATRSIZE,vector<int64> (MATRSIZE,0));
    if (a==1)
    {
      for (int i=0;i<MATRSIZE;i++)
        m[i][i]=1;
    }                              
  }
  inline vector<int64>& operator[](int a)
  {
    return m[a];
  }                              
};
                                  
                                  
matrix operator*( matrix a, matrix b)
{
  matrix res;
  for (int i=0;i<MATRSIZE;i++)
    for (int j=0;j<MATRSIZE;j++)
      for (int k=0;k<MATRSIZE;k++)
      {
        res[i][j]+=a[i][k]*b[k][j];    
        res[i][j]%=modul;
      }
  return res;
}

matrix operator^( matrix a,int b)
{
  if (b==1)
    return a;
  if (b==0)
    return matrix(1);
  if (b%2==0)
  {
    matrix tmp=a^(b/2);
    return tmp*tmp;
  }
  return ((a^(b-1)))*a; 
}

ostream& operator<< (ostream& ofs,matrix& a)
{
  for (int i=0;i<MATRSIZE;i++)
  {
    for (int j=0;j<MATRSIZE;j++)
      ofs<<a[i][j]<<" ";
    ofs<<endl;
  }
  return ofs;
}

istream& operator>> (istream& ifs,matrix& a)
{
  for (int i=0;i<MATRSIZE;i++)
    for (int j=0;j<MATRSIZE;j++)
      ifs>>a[i][j];
  return ifs;
}




int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int n;                          
  matrix a(1);
  matrix first;     
  matrix second;
  matrix last;
  matrix prelast;
  matrix middle;
  for (int i=1;i<32;i++)
    for (int j=0;j<32;j++)              
    {
      int mb=i/2;
      int ma=j;            
      if (mb&(~ma))
      {                                   
        middle[i][j]=0;
        continue;
      }
      int ism=ma&(~mb);                 
      if ((ism==1) || (ism==2) || (ism==4) || (ism==8) || (ism==16))
        middle[i][j]=1;
      else
        middle[i][j]=0;
    }
  cerr<<middle<<endl;                           
  first=middle;
  for (int i=0;i<32;i++)
    for (int j=0;j<32;j++)
      if (i%4!=0 || j%2!=0)
        first[i][j]=0;
  second=middle;
  for (int i=0;i<32;i++)
    for (int j=0;j<32;j++)
      if (i%2!=0)
        second[i][j]=0;
  prelast=middle;
  for (int i=0;i<32;i++)
    for (int j=0;j<32;j++)
      if (j>=16)
        prelast[i][j]=0;
  last=middle;
  for (int i=0;i<32;i++)
    for (int j=0;j<32;j++)
      if (i>=16 || j>=8)
        last[i][j]=0;      
  scanf("%d %d",&n,&modul);
  if (n==4)
    {
      printf("%d\n",14%modul);
      return 0;
    }
  a=first;          
  a=a*second;        
  a=a*(middle^(n-5));
  a=a*prelast;    
  a=a*last;
  long long res=0;
  for (int i=0;i<32;i++)
    for (int j=0;j<32;j++)
      res=(res+a[i][j])%modul;
  cout<<res<<endl;
  return 0;
}