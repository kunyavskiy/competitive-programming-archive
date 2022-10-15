#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <fstream>
#include <queue>
#include <memory.h>
#include <stack>
#include <deque>

#define mp make_pair
#define pb push_back

#define taskname "B"

#ifdef LOCAL 
  #define LLD "%I64d"
#else
  #define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

void impos(){
  printf("No solution.\n");
  exit(0);
}

int64 gcd(int64 a,int64 b){
  if (!b) return a;
  if (!a) return b;
  return gcd(b,a%b);
}

struct rac{
  int64 ch,zn;
  rac(){ch=zn=0;}
  rac(int a){
    ch=a;
    zn=1;
  }
  rac(int64 a,int64 b){
    ch=a;
    zn=b;
  }
  void norm(){
    if (zn==0)
      return;
    bool otr=(ch<0) ^ (zn<0);
    int tmp=gcd(abs(ch),abs(zn));
  //  cerr<<"GCD "<<ch<<" "<<zn<<" == " <<tmp<<endl;
    ch=abs(ch)/tmp;
    zn=abs(zn)/tmp;
    if (otr)
      ch*=-1;
  }
  void print(){
    norm();
    assert(zn!=0);
    printf(LLD,ch);
    if (zn!=1)
      printf("/"LLD,zn);
  }
  bool undef(){
    return zn==0;
  }
};

rac operator+(rac a,rac b){
  rac res;
  res.ch=a.ch*b.zn+a.zn*b.ch;
  res.zn=a.zn*b.zn;
  res.norm();
  return res;
}

rac operator-(rac a,rac b){
  rac res;
  res.ch=a.ch*b.zn-a.zn*b.ch;
  res.zn=a.zn*b.zn;
  res.norm();
  return res;
}

rac operator*(rac a,int64 b){
  a.ch*=b;
  a.norm();
  return a;
}   

rac operator/(rac a,int64 b){
  a.zn*=b;
  a.norm();
  return a;
}

bool operator==(rac& a,rac& b){
  a.norm();
  b.norm();
  return a.ch==b.ch && a.zn==b.zn;
}

rac a[100][100];
int kolx[100];
int koly[100];
bool usedx[100];
bool usedy[100];
int n,m;

void setval(int x,int y,rac val){

  //cerr<<"SET "<<x<<" "<<y<<" to "<<val.ch<<" "<<val.zn<<endl; 

  if (a[x][y].undef())
    {
      a[x][y]=val;
      ++kolx[x];
      ++koly[y];
      return;
    }
  if (a[x][y]==val)
    return;
  impos();
  assert(false);
}

void genx(int num){
  int f,s;
  rac fv,sv;
  f=s=-1;
  for (int i=0;i<m;i++)
    {
      if (a[num][i].undef())
        continue;
      if (f==-1){
        f=i;
        fv=a[num][i];
        continue;
      }
      s=i;
      sv=a[num][i];
      break;
    }           
  if (s==-1){
    assert(m==1);
    return;
  }
  rac d=(sv-fv)/(s-f);
  rac val=fv;
  for (int i=f-1;i>=0;i--){   
    val=val-d;
    setval(num,i,val);
  }
  val=fv;
  for (int i=f+1;i<m;i++){
    val=val+d;
    setval(num,i,val);
  }
}


void geny(int num){
  int f,s;
  rac fv,sv;
  f=s=-1;
  for (int i=0;i<n;i++)
    {
      if (a[i][num].undef())
        continue;
      if (f==-1){
        f=i;
        fv=a[i][num];
        continue;
      }
      s=i;
      sv=a[i][num];
      break;
    }
  if (s==-1){
    assert(n==1);
    return;
  }
  rac d=(sv-fv)/(s-f);
  rac val=fv;
  for (int i=f-1;i>=0;i--){   
    val=val-d;
    setval(i,num,val);
  }
  val=fv;
  for (int i=f+1;i<n;i++){
    val=val+d;
    setval(i,num,val);
  }
}


bool iterate(){
  bool q=false;
  for (int i=0;i<n;i++)
    if (!usedx[i]){
      q=true;
      if (kolx[i]>=2 || m==1){
        genx(i);
        usedx[i]=true;
        return true;
      }
    }
  for (int i=0;i<m;i++)
    if (!usedy[i]){
      q=true;
      if (koly[i]>=2 || n==1){
        geny(i);
        usedy[i]=true;
        return true;
      }
    }
  if (!q)
    return false;
  for (int i=0;i<n;i++)
    for (int j=0;j<m;j++)
      if (a[i][j].undef()){
        setval(i,j,rac(0,1));
        return true;
      }
  assert(false);
  return false;
}


int main(){
#ifdef LOCAL
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
#endif
  scanf("%d %d",&n,&m);

  /*if (n==3 && m==5){
    printf("1 2 3 4 5\n");
    printf("2 3 4 5 6\n");
    printf("3 4 5 6 7\n");
    return 0;
  }

  if (n==3 && m==3){
    printf("1 2 3\n");
    printf("1 2 3\n");
    printf("1 2 3\n");
    return 0;
  }

  if (n==1 && m==4){
    printf("No solution.\n");
    return 0;
  }

  if (n==1 && m==6){
    printf("4 8/3 4/3 0 -4/3 -8/3\n");
    return 0;
  }   */


  for (int i=0;i<n;i++)
    kolx[i]=usedx[i]=0;
  for (int j=0;j<m;j++)
    koly[j]=usedy[j]=0;

  for (int i=0;i<n;i++)
    for (int j=0;j<m;j++)
      {
        string s;
        cin>>s;
        if (s!="."){
          int tmp;
          sscanf(s.data(),"%d",&tmp);
         // cerr<<tmp<<endl;
          setval(i,j,rac(tmp,1));
        }
        else
          a[i][j]=rac(0,0);
      } 


  for (;iterate(););
  for (int i=0;i<n;i++){
    for (int j=0;j<m;j++){
      a[i][j].print();
      if (j!=m-1)
        printf(" ");
    }
    printf("\n");
  }  
  return 0;
}