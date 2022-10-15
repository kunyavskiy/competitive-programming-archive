#define NDEBUG
#define _SECURE_SCL 0
#undef _DEBUG
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
#include <list>
#include <deque>
#define mp make_pair
#define pb push_back
#define int64 long long
#define ld long double
#define fileinout
using namespace std;
                               
int sz[(1<<16)+100];

struct mnoj
{
  unsigned int mask[4];
  int num;
  int randel;

  inline int size()  {
    int res=0;
    unsigned int a;
    for (int i=0;i<4;i++) {
      a=mask[i];
      res+=sz[a&((1<<16)-1)];
      a>>=16;
      res+=sz[a];
    }
    return res;
  }

  inline mnoj(unsigned int _a=0,unsigned int _b=0,unsigned int _c=0,unsigned int _d=0)  {
    mask[0]=_a;
    mask[1]=_b;
    mask[2]=_c;
    mask[3]=_d;
    num=0;
  }

  inline mnoj(int a)  {
    if (a==0)             {
        mask[0]=0;
        mask[1]=0;
        mask[2]=0;
        mask[3]=0;
        return;
      }
    assert(false);
  }

  inline unsigned int& operator[](int a)  {return mask[a];}

  inline void print() {
    for (unsigned int i=99;i!=0;i--)
      if (mask[i/32]&(((unsigned int)1)<<(i%32)))      {
        printf("%u ",i);
      }
    if (mask[0]&1)
      printf("0 ");
  }
};

inline mnoj operator& (mnoj a,mnoj b){
  mnoj res;
  for (int i=0;i<4;i++)
    res[i]=a[i]&b[i];
  return res;
}

inline mnoj operator| (mnoj a,mnoj b){
  mnoj res;
  for (int i=0;i<4;i++)
    res[i]=a[i]|b[i];
  return res;
}

inline mnoj operator- (mnoj a,mnoj b){
  mnoj res;
  for (int i=0;i<4;i++)
    res[i]=a[i]&(~b[i]);
  return res;
}

inline mnoj operator| (mnoj a,unsigned int b){
  a.mask[b/32]=a.mask[b/32]|(((unsigned int)1)<<(b%32));
  return a;
}

inline bool operator== (mnoj a,mnoj b){
  for (int i=0;i<4;i++)
    if (a.mask[i]!=b.mask[i])
      return false;
  return true;
}

inline bool operator< (mnoj a,mnoj b){ return a.size()<b.size();}

inline bool in(mnoj a,mnoj b){  return ((a|b)==b);}

list<mnoj> ans; 
vector<int> poss; 
int szans; 
int eq[600];
mnoj m[600]; 
int n;
int ns;
list<mnoj> tec;
vector<int> tecpos;
int tecsize; 
                      
inline void reverse(){
  for (int i=0,j=n-1;i<j;i++,j--)
    swap(m[i],m[j]);
}

inline void mnoj_insert (int i){
    mnoj old,new1,new2;
    mnoj ins=m[i];
    for (list<mnoj>::iterator iter=tec.begin();iter!=tec.end();++iter)    
      if (!in(*iter,ins))  {
        old=(*iter);
        new1=old-ins;
        new2=old-new1;
        ins=ins-old;
        iter=tec.erase(iter);
        iter=tec.insert(iter,new1);
        iter=tec.insert(iter,new2);
        break;
      }
    else ins=ins-(*iter); 
    tec.push_front(ins);
    tecsize+=ins.size();
    tecpos[m[i].num]=tecsize-m[i].size();
}

inline int mnoj_insert_count(int i){
    mnoj old;
    mnoj ins=m[i];
    for (list<mnoj>::iterator iter=tec.begin();iter!=tec.end();++iter)    
      if (!in(*iter,ins))      {
        old=(*iter);    
        ins=ins-old;                 
        break;
      }
      else ins=ins-(*iter);      
    return m[i].size()-ins.size();         
}

inline void solve(){                       
  tec.clear();
  tecpos.assign(ns,0);    
  tecsize=0;
  for (int i=0;i<n;i++)    {                                 
    mnoj_insert(i);
    if (tecsize>szans)
      break;
  }
  for (int i=0;i<ns;i++)
    tecpos[i]=tecpos[eq[i]];
  if (tecsize<szans)  {
    szans=tecsize;
    ans.swap(tec);
    poss.swap(tecpos);
  }
}

inline void firster(int i,int j){
  int p1=mnoj_insert_count(i);
  int p2=mnoj_insert_count(j);
  if (p1>p2)
    return;
  if (p1<p2) {
    swap(m[i],m[j]);
    return;
  }
  if (m[i].size()>m[j].size()) {
      swap(m[i],m[j]);
      return;
    }
 return;
}
       
inline void solve_jadn() {
  tec.clear();
  tecpos.assign(ns,0);    
  tecsize=0;
  for (int i=0;i<n;i++) {
    for (int j=i+1;j<n;j++)                    
      firster(i,j);
    mnoj_insert(i);
    if (tecsize>szans)
      break;
  }
  for (int i=0;i<ns;i++)
    tecpos[i]=tecpos[eq[i]];
  if (tecsize<szans) {
    szans=tecsize;
    ans.swap(tec);
    poss.swap(tecpos);
  }

} 

void firster(mnoj &a,mnoj &b,const mnoj pr)
{
  if ((in(b,pr)) && (!in(a,pr)))       {
      swap(a,b);
      return;
    }
  if (in(a,pr) && (!in(b,pr)))
      return;
  if (a.size()>b.size())
    swap(a,b);
  return;
}   
      
int main()
{
  #ifndef ONLINE_JUDGE 
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif  
  mnoj m1[600];
  mnoj m2[600];
  mnoj m3[600];
  int randseed=21*n;
  scanf("%d",&n);
  ns=n;           
  for (int i=0;i<n;i++)  {
    int sz;
    scanf("%d",&sz);
    randseed+=sz*(i%21+1);
    unsigned int a;
    for (int j=0;j<sz;j++)    {
      scanf("%d",&a);
      m[i]=m[i]|a;
    }
    m[i].num=i;
  }               
  for (int i=0;i<n;i++)     {
      eq[m[i].num]=m[i].num;
      for (int j=i+1;j<n;j++)
        if (m[i]==m[j])           {
          eq[m[j].num]=m[i].num;
          swap(m[j],m[n-1]);          
          --n;
        }
  }   
  for (int i=0;i<n;i++)
    m3[i]=m[i];
  srand(randseed);
  sort(&m[0],&m[n]);
  for (int i=0;i<n;i++)
    m1[i]=m[i];     
  int tl=20001;
  szans=1000000000;
  sz[0]=0;
  for (int i=1;i<=(1<<16);i++)
    sz[i]=sz[i&(i-1)]+1;  
  sort(&m[0],&m[n]),solve();
  reverse(), solve();
  for (int i=1;i<n;i++)  {
    int upsz=(m[i-1]&m[i]).size();
    for (int j=i+1;j<n;j++)
        if ((m[i-1]&m[j]).size()>upsz)  {
          upsz=(m[i-1]&m[j]).size();
          swap(m[i],m[j]);
        }
  }
  solve();
  reverse(),solve();
  for (int i=1;i<n;i++)          
    for (int j=i+1;j<n;j++)
       firster(m[i],m[j],m[i-1]);
  solve();         
  vector<mnoj> mt;
  vector<mnoj> mtt;
  int it1=0;
  for (;it1<n;)
  {
    for (int j=it1+1;j<n;j++)
       firster(m[it1],m[j],mnoj(0));
    mt.push_back(m[it1]);
    it1++;       
    for (;it1<n;it1++){                
      for (int j=it1+1;j<n;j++)
        firster(m[it1],m[j],mt[it1-1]);
      if (in(m[it1],mt[it1-1]))
        mt.pb(m[it1]);
      else
        break;
    }
  reverse(mt.begin(),mt.end());
    for (;it1<n;it1++) {                 
      for (int j=it1+1;j<n;j++)
        firster(m[it1],m[j],mt[0]);
      if (in(m[it1],mt[0]))
        mt.pb(m[it1]);
      else
        break;
    }
  for (int i=0;i<mt.size();i++)
    mtt.push_back(mt[i]);
  mt.clear();
 }
  while (mtt.size()!=n);
  for (int i=0;i<n;i++)
    m[i]=mtt[i];
  solve();
  reverse(),solve();
  solve_jadn();
  for (int i=0;i<ns;i++)
    m[i]=m3[i];
  solve();
  reverse(),solve();  
  for (int i=0;i<n;i++)
    m[i]=m1[i];                                                                             
  solve();                                                                                  
  reverse();                                                                                
  tl--;                                                                                     
for (;tl;tl--)                                                                              
{
  solve();
  random_shuffle(&m[0],&m[n]);  
}
  printf("%d ",szans);
  for (list<mnoj>::reverse_iterator iter=ans.rbegin();iter!=ans.rend();++iter)
    (*iter).print();
  printf("\n");
  for (int i=0;i<ns;i++)
  printf("%d ",poss[i]);
  printf("\n");
  return 0; 
}         