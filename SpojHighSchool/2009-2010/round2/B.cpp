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

int g[400][700];

int main()
{            
  #ifdef fileinout
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif     
  for (int i=0;i<700;i++)
  {
    g[0][i]=0;
    g[1][i]=1;
  }
  for (int i=0;i<300;i++)
    g[i][0]=0;
  vector<bool> used(400);
  for (int i=2;i<=300;i++)
    for (int j=1;j<=301;j++)
    {                                     
        used.assign(400,false);
        if (j<=i)
        {
        for (int k=1;k<=j && k<=i;k++)
          used[g[i-k][min(2*k,301)]]=true;
        for (int k=0;k<310;k++)
          if (!used[k])
            {
              g[i][j]=k;
              break;
            }    
//        cerr<<i<<" "<<j<<" "<<g[i][j]<<endl;  
        }
        else             
           g[i][j]=g[i][j-1];               
    }         
  int t;
  scanf("%d",&t);
  for (;t>0;t--)
  {
    int n;
    scanf("%d",&n);
    int gr=0;
    for (int i=0;i<n;i++)
    {
      int a;
      scanf("%d",&a);
      gr=gr^g[a][a-1];
    }      
    if (gr==0)
      printf("0\n");
     else
     printf("1\n");
   //  return 0;
  }
    

  return 0;
}