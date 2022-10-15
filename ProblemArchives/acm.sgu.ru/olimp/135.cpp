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
#include <memory.h>
#include <stack>
#define mp make_pair
#define pb push_back                     
#define int64 long long
#define ld long double
#define fileinout
using namespace std;

struct node;

struct node{
  node* lf;
  node* rg;
  char c;
  string name;
  bool havename;
  bool counted;
  node()
  {
    lf=rg=NULL;
    c=0;
    name="";
    havename=counted=false;
  }
  node(node* l,node* r,char _c)
  {
    lf=l;
    rg=r;
    c=_c;
    name="";
    havename=counted=false;
  }
  node(string s)
  {
     lf=rg=NULL;
     c=0;
     name=s;
     havename=true;
     counted=false;
  }
};

typedef pair<node*,node*> tnode;
typedef pair<tnode,char> onode;

map<onode,node*> counted;
map<string,node*> per;
set<string> names;
set<string> unames;

void addtotree(string s)
{
  char p1[40],p2[40],p3[40];
  char c;
  int kol;
  kol=sscanf(s.data(),"%[a-z0-9]=%[a-z0-9]%c%[a-z0-9]",&p1,&p2,&c,&p3);
  string lf(p1);
  string rg1(p2);
  string rg2(p3);
  assert(kol==2 || kol==4);
  if (kol==2)
  {
    if (unames.find(rg1)!=unames.end())
      {
        unames.insert(lf);
        per[lf]=per[rg1];
      }
    else
      {
        unames.insert(rg1);
        names.erase(rg1);
        node* tmp=new node;
        (*tmp)=node(rg1);
        per[rg1]=tmp;   
        unames.insert(lf);
        per[lf]=tmp;
      }
    return;
  }            
  if (unames.find(rg1)==unames.end())
  {
        unames.insert(rg1);
        names.erase(rg1);
        node* tmp=new node;
        (*tmp)=node(rg1);
        per[rg1]=tmp;   
  }
  if (unames.find(rg2)==unames.end())
  {
        unames.insert(rg2);
        names.erase(rg2);
        node* tmp=new node;
        (*tmp)=node(rg2);
        per[rg2]=tmp;   
  }
  onode tmp(tnode(per[rg1],per[rg2]),c);
  if (counted.find(tmp)!=counted.end())
    {
      node* r=counted[tmp];
      unames.insert(lf);
      per[lf]=r;  
      return;
    }
  node* r;
  r=new node;
  *r=node(per[rg1],per[rg2],c);  
  counted[onode(tnode(per[rg1],per[rg2]),c)]=r;
  unames.insert(lf);
  per[lf]=r;                                   
  return;
}


void gennames()
{
  for (char i='a';i<='z' && names.size()!=10001;i++)
    for (char i1='a';i1<='z' && names.size()!=10001;i1++)
      for (char i2='a';i2<='z' && names.size()!=10001;i2++)
        for (char i3='a';i3<='z' && names.size()!=10001;i3++)    
        {
          string s="";
          s+=i;
          s+=i1;
          s+=i2;
          s+=i3;
          names.insert(s);
        }            
}
                       
string ans;
int kol;

string print_tree(node* root,bool first=false)
{   
  if (!root)
    return "";
  if (root->counted)
    return root->name;
  string lf=print_tree(root->lf);
  string rg=print_tree(root->rg);
  string my;
  if (first)
  {
    my="res";
    if (root->havename )
      {
        if (root->name!="res")
        {                             
          kol++;
          ans=ans+my+"="+(root->name)+"\n";
        }
        return my;
      }
  }
  else if (root->havename)
      my=root->name;
  else {
      my=*names.begin();
      assert(!names.empty());
      names.erase(names.begin());
    }
  if ((rg!="") && (lf!=""))
  {
    assert(root->c);                       
    ans=ans+my+"="+lf+(root->c)+rg+"\n";
    kol++;
  }
  else 
    assert(lf=="" && rg=="");
  root->counted=true;
  root->name=my;
  return my;
}

int main()
{                            
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  gennames();
  ans="";
  kol=0;
  int n;
  scanf("%d\n",&n);
  for (int i=0;i<n;i++)
  {
    string s;
    getline(cin,s);
    addtotree(s);
  }
  if (per.find("res")==per.end())
    printf("0\n");
  else
    {
      print_tree(per["res"],true);
      printf("%d\n%s",kol,(kol!=0)?(ans.data()):(""));
    }                                     
  return 0;
}