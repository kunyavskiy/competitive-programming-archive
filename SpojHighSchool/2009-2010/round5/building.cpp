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

int sum;

struct node{
	node* l,*r;
	int x,y;
	int64 sum;
	int kol;
	node(){
		l=r=NULL;
		x=0;
		y=rand();
		sum=0;
		kol=1;
	}
	node(int X){
		l=r=NULL;
		x=X;
		y=rand();
		sum=X;
		kol=1;
	}	
};



void update(node* x){
	if (!x)
		return;
	x->sum=x->x;
	if (x->l)
		x->sum+=x->l->sum;
	if (x->r)
		x->sum+=x->r->sum;
	x->kol=1;
	if (x->l)
		x->kol+=x->l->kol;
	if (x->r)
		x->kol+=x->r->kol;	
	return;
}

node* merge(node* a,node* b){
	if (a==NULL)
		return b;
	if (b==NULL)
		return a;
	if (a->y > b->y)
	{
		a->r=merge(a->r,b);
		update(a);
		return a;
	}
	b->l=merge(a,b->l);
	update(b);
	return b;	
}

void split(node* a,int x,node* &l,node* &r){
	if (a==NULL){
		l=r=NULL;
		return;
	}
	if (a->x<=x){
		l=a;
		split(a->r,x,a->r,r);
		update(a);
		return;
	}
	r=a;
	split(a->l,x,l,a->l);
	update(a);
	return;	
}

void add(node* &t,node* m){
	node* l=NULL;
	node* r=NULL;
	split(t,m->x,l,r);
	l=merge(l,m);
	t=merge(l,r);	
	update(t);
}

node* del(node* &t,int x){
	node *l=NULL,*m=NULL,*r=NULL;
	split(t,x,l,r);
	split(l,x-1,l,m);
	node *m1=m->l;
	node *m2=m->r;
	m->l=m->r=NULL;
	l=merge(l,m1);
	r=merge(m2,r);
	t=merge(l,r);		
	update(t);
	return m;
}

void k_split(node* t,int k,node* &l,node* &m,node* &r){
	if (t==NULL)	
		{
			l=m=r=NULL;
			return;
		}
	if (t->l && t->l->kol<k)
		k-=t->l->kol;
	else if (t->l)
		{
			r=t;
			k_split(t->l,k,l,m,t->l);
			update(t);
			return;
		}
	if (k!=1)
		k--;
	else
		{
			m=t;
			l=t->l;
			r=t->r;
			t->l=t->r=NULL;
			update(l);
			update(r);
			update(m);
			return;
		}
	l=t;
	k_split(t->r,k,t->r,m,r);
	update(t);
	return;		
}

int64 findsum(node* &t){
	node* l=NULL,*r=NULL,*m=NULL;
	k_split(t,t->kol/2+1,l,m,r);
	int64 sum=0;
	if (l)
		sum+=((l->kol)*1ll*(m->x))-(l->sum);
	if (r)
		sum+=(r->sum)-(r->kol)*1ll*(m->x);
	l=merge(l,m);
	t=merge(l,r);
	return sum;
}

int a[1000000];

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int n,k;
  scanf("%d %d",&n,&k);
  for (int i=0;i<n;i++)
  	scanf("%d",&a[i]);
  node* t=new node(a[0]);
  for (int i=1;i<k;i++)
  {
		node* tmp=new node(a[i]);
		add(t,tmp);		
	}
	int64 ans=findsum(t);
	int pans=0;
	for (int i=k;i<n;i++)
	{
		node* tmp=del(t,a[i-k]);
		(*tmp)=node(a[i]);
		add(t,tmp);
		int64 ts=findsum(t);
		if (ts<ans)
			{
				ans=ts;
				pans=i-k+1;
			}
	}
	cout<<ans<<" "<<pans<<endl;
  return 0;
}