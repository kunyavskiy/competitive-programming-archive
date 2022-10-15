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
	node *l,*r;
	int64 kol;
	int64 sum;
	int64 x;
	int64 mykol;
	int y;
	node(){
		l=r=0;
		mykol=kol=1;
		sum=x=0;
		y=rand();
	}
	node (int64 X,int64 Kol){
		l=r=0;
		mykol=kol=Kol;
		x=X;
		sum=X*kol;
		y=rand();
	}
};

void update(node* v){
	if (!v)
		return;
	v->kol=v->mykol;
	v->sum=v->kol*v->x;
	if (v->l){
		v->kol+=v->l->kol;
		v->sum+=v->l->sum;
	}
	if (v->r){
		v->kol+=v->r->kol;
		v->sum+=v->r->sum;	
	}
}

node* merge(node* l,node* r){
	if (!l)
		return r;
	if (!r)
		return l;
	if (l->y > r->y){
		l->r=merge(l->r,r);
		update(l);
		return l;
	}
	r->l=merge(l,r->l);
	update(r);
	return r;
}


void split(node* v,int x,node* &l,node* &r){
	if (!v){
		l=r=0;
		return;
	}
	if (v->x <=x){
		l=v;
		split(v->r,x,v->r,r);
		update(l);
		return;
	}
	r=v;
	split(v->l,x,l,v->l);
	update(r);
	return;
}

node* root;

void add(int64 x,int64 kol){
	node *l,*r,*m;
	m=new node(x,kol);
	split(root,x,l,r);
	l=merge(l,m);
	root=merge(l,r);
}

void delete_und(node* &v){
	if (!v)
		return;
	delete_und(v->l);
	delete_und(v->r);
	delete v;
	v=0;
}

bool buy(node* &v,int64 kol,int64 sum){
	if (!v)
		return false;
	if (v->kol < kol)
		return false;
	if (v->l){
		if (v->l->kol >= kol)
		{
			bool q=buy(v->l,kol,sum);
			update(v);
			return q;
		}
		if (v->l->sum > sum)
			return false;
		sum-=v->l->sum;
		kol-=v->l->kol;
	}
	if (v->mykol >=kol){
		if (v->x * kol > sum)
			return false;
		v->mykol-=kol;
		delete_und(v->l);
		if (v->mykol==0)
		{
			node* tmp=v;
			v=v->r;
			delete tmp;
		}
		update(v);
		return true;
	}
	
	if (v->x * v->mykol >sum)
		return false;
	kol-=v->mykol;
	sum-=v->x * v->mykol;
	if (buy(v->r,kol,sum)){
		delete_und(v->l);
		node* tmp=v;
		v=v->r;
		delete tmp;
		return true;
	}
	return false;
}


int64 par1,par2;
string s;


int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  root=0;
  for (;;){
  if (!(cin>>s))
		break;
	if (s=="ARRIVE")
	{
			cin>>par1>>par2;
  		add(par2,par1);
	}
 	if (s=="BUY")
  		{
			cin>>par1>>par2;
  			if (buy(root,par1,par2))
  				printf("HAPPY\n");
  			else
  				printf("UNHAPPY\n");
  		}
  }
  
  return 0;
}