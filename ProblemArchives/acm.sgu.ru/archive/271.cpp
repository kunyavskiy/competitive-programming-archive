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
#define setval(a,v) memset(a,v,sizeof(a))
using namespace std;

struct node{
	node* l;
	node* r;
	bool rev;
	int y;
	string val;
	int kol;
	node(){
		l=r=0;
		rev=false;
		y=rand();
		val="";
		kol=1;
	}
	node(string v){
		l=r=0;
		rev=false;
		y=rand();
		val=v;
		kol=1;
	}
};

node* root;

void update(node* v){
	if (!v)
		return;
	v->kol=1;
	if (v->l)
		v->kol += v->l->kol;
	if (v->r)
		v->kol += v->r->kol;
	return;		
}

void push(node* v){
	if (!v)
		return;
	if (!v->rev)
		return;
	swap(v->l,v->r);
	if (v->l)
		v->l->rev^=1;
	if (v->r)
		v->r->rev^=1;
	v->rev=0;
}

node* merge(node* l,node* r){
	if (!l)
		return r;
	if (!r)
		return l;
	push(l);
	push(r);
	if (l->y > r->y)
		{
			l->r=merge(l->r,r);
			update(l);
			return l;
		}
	r->l = merge(l,r->l);
	update(r);
	return r;
}

void split(node* v,int kol,node* &l,node* &r){
	//cerr<<v->val<<" "<<v->kol<<endl;
	if (kol==0){
		l=0;
		r=v;
		return;
	}
	if (!v)
	{
		l=r=0;
		return;
	}
	push(v);
	if (v->l){
		if (v->l->kol >= kol)
			{
				r=v;
				split(v->l,kol,l,v->l);
				update(r);
				return;
			}
		kol-= v->l->kol;
	}
	
	l=v;
	--kol;
	
	split(v->r,kol,v->r,r);
	update(l);
}

void rev(int K){
	if (!root)
		return;
	node *l,*r;
	split(root,max(0,(root->kol)-K),l,r);
	if (r)
		r->rev^=1;
	root=merge(l,r);
}

void print(node* v){
	if (!v)
		return;
	push(v);
	print(v->l);
	printf("%s\n",v->val.data());
	print(v->r);
}

char S[1000];

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  
  int n,m,k;
  scanf("%d %d %d\n",&n,&m,&k);
  root=0;
  
  for (int i=0;i<n;i++){
  	string s;
		gets(S);
		s=S;
  	node* tmp=new node(s);
  	root=merge(tmp,root);
  }
  
  for (int i=0;i<m;i++){
		gets(S);
		string s;
		s=S;
  	if (s=="ROTATE")
  		rev(k);
  	else
  	{
  		s.erase(s.begin(),s.begin()+4);
  		s.erase(--s.end());
  		node* tmp=new node(s);
  		root=merge(root,tmp);
  	}
  }  	  
  if (root)
  	root->rev^=1;
  print(root);
  return 0;
}