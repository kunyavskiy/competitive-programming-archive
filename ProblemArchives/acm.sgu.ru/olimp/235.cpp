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

#define taskname "D"

#ifdef LOCAL 
  #define LLD "%I64d"
#else
  #define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

struct node{
  node* par;
  node* next[2];
  int l,r;
  bool good;
  int kol;
  node(){
    good=false;
    l=r=kol=0;
    next[0]=next[1]=par=0;
  }
};

struct pos{
  node* to;
  int before;
};

int s[4010];
int s1[4010];
int n,n1;

node* split(pos p){
  if (p.before==0)
    return p.to;

  if (p.before== p.to->r - p.to->l)
    return p.to->par;

  node* tmp=new node;
  
  tmp->l=p.to->l;
  tmp->r=p.to->r - p.before;
  p.to->l=tmp->r;
  tmp->par=p.to->par;
  p.to->par=tmp;

  tmp->par->next[s[tmp->l]]=tmp;
  tmp->next[s[tmp->r]]=p.to;

  return tmp;
}


bool go(pos& p,int c){


 // cerr<<p.to<<endl;
 // cerr<<p.before<<endl;
  if (p.before == 0)
    {                    
      if (!p.to->next[c])
        return false;
      p.to=p.to->next[c];

      p.before=(p.to->r) - (p.to->l);

  //    cerr<<"!!!"<<p.to<<" "<<p.before<<endl;
    }

                       

  if (s[p.to->r - p.before] ==c)
  {
    p.before--;
    return true;
  }

//  cerr<<"!!!"<<endl;

  node* tmp=split(p);
  p.to=tmp;
  p.before=0;
  return false;
}

node* root;


void add1(int suf){
  pos p;
  p.to=root;
  p.before=0;    
  for (int i=suf;i<n;i++)
    if (!go(p,s[i]))
      {
        node* tmp=new node;
        tmp->l=i;
        tmp->r=n;    
        assert(p.before==0);
        assert(p.to->next[s[i]]==0);
        p.to->next[s[i]]=tmp;
        tmp->par=p.to;
        return;          
      }           
}

void add2(int suf){
  pos p;
  p.to=root;
  p.before=0;
  for (int i=suf;i<n1;i++){
    if (p.before==0)
      p.to->good=true;
   // cerr<<"!"<<i<<endl;    
    if (!go(p,s1[i]))
      {
     //   cerr<<"CAN NOT GO:"<<s1[i]<<endl;
        p.to->good=true;
        return;
      }
  }     
  node* tmp=split(p);
  tmp->good=true;
}

void deletebad(node* &v){
  if (!v)
    return;
  if (!v->good){
    v=0;
    return;
  }
  deletebad(v->next[0]);
  deletebad(v->next[1]);
}

int calc(node* v){

//  cerr<<v<<endl;

  if (!v)
    return 0;
  v->kol=0;
  v->kol+=calc(v->next[0]);
  v->kol+=calc(v->next[1]);               
  v->kol+=v->r - v->l;  

  //cerr<<"OUT"<<v<<endl;
  return v->kol;
}

void gen(node *v,int k){
  for (;k;){

    //cerr<<v<<" "<<k<<endl;

    if (v->next[0]){

      //cerr<<"!!!"<<v->next[0]<<" "<<v->next[0]->kol<<endl;
                                  
      if (v->next[0]->kol >= k){
        for (int i= v->next[0]->l; i< v->next[0]->r && k; i++){
          printf("%d",s[i]);
          k--;
        }
        v=v->next[0];
        continue;
      }
      k-=v->next[0]->kol;
    }

    for (int i= v->next[1]->l; i< v->next[1]->r && k; i++){
      printf("%d",s[i]);
      k--;
    }
    v=v->next[1];

  }
}

void printtree(node* v){
  cerr<<v<<" "<<v->next[0]<<" "<<v->next[1]<<" "<<v->l<<" "<<v->r<<endl;
  if (v->next[0])
    printtree(v->next[0]);
  if (v->next[1])
    printtree(v->next[1]);
}

int main(){
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  string str;
  cin>>str;
  n=str.size();
  for (int i=0;i<n;i++)
    s[i]=str[i]-'0';
  cin>>str;
  n1=str.size();
  for (int i=0;i<n1;i++)
    s1[i]=str[i]-'0';
  root=new node;
  for (int i=0;i<n;i++)
    add1(i);


;
//  cerr<<endl;

  for (int i=0;i<n1;i++){
    add2(i);
   // cerr<<i<<endl;
   // printtree(root);
   // cerr<<endl<<endl;
  }




  deletebad(root);
//
//  printtree(root);

  int k;
  cin>>k;
  calc(root);
                   
  gen(root,k);
  return 0;
}