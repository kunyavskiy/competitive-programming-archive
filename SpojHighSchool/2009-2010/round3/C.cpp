#define NDEBUG  
#define _SECURE_SCL 0 
#undef _DEBUG   
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <memory.h>
#include <map>
#include <string>
#include <cmath>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <queue>
#include <stack>
#define mp make_pair
#define pb push_back
#define int64 long long
#define ld long double
#define cps CLOCKS_PER_SEC
#define fileinout
using namespace std;
 
const int solvemax=2500;
const int PERMAX=100;
//const int TL[PERMAX]={100,100,100,100,100,100,100,100,100,100,100,100,100};                                                             
int TL=175000000;
int permax;  
char a[solvemax+10][solvemax+10];
char b[solvemax+10];
int tmp[solvemax+10];
int anstmp;
int zav[PERMAX][solvemax+10];
char maxism[solvemax+10];
int n,m;
int nm;
const char mult[3][3]={{0,0,0},{0,1,2},{0,2,1}};
const char razn[3][3]={{0,2,1},{1,0,2},{2,1,0}};
const char sum[3][3]={{0,1,2},{1,2,0},{2,0,1}};
char ism[solvemax+10];
bool update;


inline long long time()
{                   
  long long res;
  asm volatile ("rdtsc" : "=A" (res));
  return res;
}

inline int number(int i,int j)
{
  return m*i+j;
}
                         
inline void swapr(int i,int j)
{
  for (int k=0;k<nm;k++)
    swap(a[i][k],a[j][k]);
  swap(b[i],b[j]);
}

inline int cnt(int num,int d)
{
  memset(ism,0,sizeof(ism));
  ism[num]=d;
  int res=0;                       
  for (int j=0;j<num;j++)
    ism[j]=razn[0][mult[ism[num]][a[j][num]]];
  for (int i=0;i<nm;i++)
    res=res+sum[b[i]][ism[i]]-b[i];
  return res;
}

inline void cnt_per(int num,int d)
{
  int* T=zav[num];
  num=tmp[num];             
  ism[num]=sum[ism[num]][d];
  int res=0;
  int tt;                      
  for (int j=1;j<=T[0];j++)
  {
    tt=T[j];
    ism[tt]=razn[ism[tt]][mult[d][a[tt][num]]];
  }
}

inline int cnt_val()
{
  int res=0; 
  for (int i=0;i<nm;i++)
    res=res+sum[b[i]][ism[i]]-b[i];
  return res;
}


inline void inc()
{
  update=true;                                                 
  for (int j=0;j<nm;j++)
    b[j]=sum[b[j]][ism[j]];
  return;
}

long long start;
bool end;
  
bool per(int num)
{
  if (num>tmp[0])
  {                                      
    int sum=0;
    sum=cnt_val();
    bool q=false;
    if (sum<anstmp)
    {
      anstmp=sum;
      for (int i=0;i<nm;i++)
        maxism[i]=ism[i];
      q=true;
    }           
    if (time()-start>TL)
      end=true; 
    return q;
  }  
  bool q=false;
  q|=per(num+1);     
  if (end)
    return q;
    cnt_per(num,1);
  q|=per(num+1);     
  if (end)
    return q;
    cnt_per(num,1);
  if (false);                     
    q|=per(num+1);
  if (end)
    return q;
    cnt_per(num,1);
  return q;
}


inline void perebor()
{                                         
  start=time();
  anstmp=0;
  memset(maxism,0,sizeof(maxism));
  memset(ism,0,sizeof(ism));
  end=false;
  per(1);
  for (int i=0;i<nm;i++)     
    ism[i]=maxism[i];
  if (cnt_val()<0);
    inc();             
  return;
}
           
inline bool solve()
{
  int coef,ttt;
  char* A;
  char *AA;
  const char* M;            
  for (int i=0;i<nm;i++)
    for (int j=0;j<nm;j++)
      a[i][j]=0;
  int num;
  for (int i=0;i<n;i++)
    for (int j=0;j<m;j++)
    {
      num=number(i,j);
      AA=a[num];
      AA[num]=1;
      if (i>0)
      AA[number(i-1,j)]=1;
      if (j>0)
        AA[number(i,j-1)]=1;
      if (i<n-1)
        AA[number(i+1,j)]=1;
      if (j<m-1)
        AA[number(i,j+1)]=1;
    };
  for (int i=0;i<nm;i++)
    swapr(i,rand()%(i+1));
  for (int i=0;i<nm;i++)
  {
    if (a[i][i]==0)
    {          
      for (int j=0;j<nm;j++)
      if (a[j][i]!=0 && ((j>i) || a[j][j]==0))
      {
        swapr(i,j);
        break;
      }
      if (a[i][i]==0)
        continue;
    }                
    tmp[0]=0;
    for (int j=i;j<nm;j++)
      if (a[i][j]!=0)
        tmp[++tmp[0]]=j;
    A=a[i];
    for (int j=0;j<nm;j++)
    if (j!=i)
    {
      coef=mult[a[j][i]][A[i]];
      AA=a[j];
      M=mult[coef];
      if (coef!=0)
      {            
        for (int k=1;k<=tmp[0];k++)
        {
          ttt=tmp[k];
          AA[ttt]=razn[AA[ttt]][M[A[ttt]]];
        }
        b[j]=razn[b[j]][M[b[i]]];
      }
    }
  }

  tmp[0]=0;
  for (int i=nm-1;i>=0;i--)
     if (a[i][i]==0)
     {
        tmp[++tmp[0]]=i;
        zav[tmp[0]][0]=0;
     }
  random_shuffle(&tmp[1],&tmp[tmp[0]+1]);
  for (int i=nm-1;i>=0;i--)
  {
    if (a[i][i]==0)
    {
      if (b[i]==0)                               
        continue;                                
      else
        return false;
    }
    AA=a[i];     
    b[i]=mult[b[i]][AA[i]];
    coef=AA[i];
    M=mult[coef];    
    for (int j=1;j<=tmp[0];j++)
    {
        ttt=tmp[j];
        char& abc=AA[ttt];
        abc=M[abc]; 
        if (abc!=0)
           zav[j][++zav[j][0]]=i;
    }
    a[i][i]=1;                               
  }                          
  update=true;             
  int t;     
  perebor();                             
  if ((end==true))
  {               ;
      for (int i=1;i<=tmp[0];i++)
      {        
        update=false;
        t=tmp[i]; 
        if (cnt(t,1)<0)
          inc(); 
        if (cnt(t,2)<0)
          inc();
        if (update)
          i=1;
      }
  }      
  return true;
}

char s[50];

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  srand(std::time(NULL));
  int t;
  permax=PERMAX-1;
  int kol,sum;
  char c;
  bool trans;
  scanf("%d",&t);     
  for (int test=1;test<=t;test++)
  {
    scanf("%d %d\n",&n,&m);
    nm=n*m;
    if (false)
    {
      trans=false;
      for (int i=0;i<n;i++)
      {         
        scanf(" %s ",&s);
        for (int j=0;j<m;j++)
        {
          c=s[j];
          if (c=='R')
            b[number(i,j)]=0;
          else if (c=='G')
            b[number(i,j)]=2;
          else if (c=='B')
            b[number(i,j)]=1;
        }                          
      }
    }
    else
    {
      trans=true;
      swap(n,m);
      for (int i=0;i<m;i++)
      {
        scanf(" %s ",&s); 
        for (int j=0;j<n;j++)
        {
          c=s[j];
          if (c=='R')
            b[number(j,i)]=0;
          else if (c=='G')
            b[number(j,i)]=2;
          else if (c=='B')
            b[number(j,i)]=1;
          else               
            assert(false);
        }
        scanf("\n");
      }
    }
    printf("Case %d: ",test);
    if (solve()==false)
      printf("N\n");
    else
    {
      printf("Y\n");
      kol=0,sum=0;
      for (int i=0;i<nm;i++)
        if (b[i]!=0)
        {
          kol++;
          sum+=b[i];
        }
      printf("%d %d\n",sum,kol);
      if (trans)
      {
        for (int i=0;i<nm;i++)
          if (b[i]!=0)
            printf("%d %d %d\n",i%m,i/m,b[i]);
      }
      else
      {
        for (int i=0;i<nm;i++)
          if (b[i]!=0)
            printf("%d %d %d\n",i/m,i%m,b[i]);
      }
    }
  }
  return 0;
} 