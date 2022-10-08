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
#define setval(a,v) memset(a,v,sizeof(a))

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

struct node{
	node *l,*r;
	int L,R;

	ll adda;
	ll addb;
	ll setto;

};

void setto(node* v,ll val){
	v->setto = val;
	v->adda = v->addb = 0;
}

void add(node* v,ll vala,ll valb){
	v->adda += vala;
	v->addb += valb;
}

void push(node* v){
	if (!v->l){
		v->l = new node();
		v->r = new node();
		v->l->L = v->L;
		v->l->R = (v->L+v->R)/2;
		v->r->L = v->l->R+1;
		v->r->R = v->R;
	}

	if (v->setto != -1){
		setto(v->l,v->setto);
		setto(v->r,v->setto);
		v->setto = -1;
	}

	add(v->l,v->adda,v->addb);
	add(v->r,v->adda,v->addb + v->adda * (v->l->R - v->l->L + 1));
	v->adda = v->addb = 0;
}


int add(node* v,int L,int R,ll val){

	if (v->R < L || R < v->L)
		return 0;
	if (L <= v->L && v->R <= R){

		add(v,-1,val);
		return v->R - v->L + 1;
	}
	push(v);
	int cnt = add(v->l,L,R,val);
	cnt += add(v->r,L,R,val-cnt);
	return cnt;
}

void setto(node* v,int L,int R,ll val){

	if (v->R < L || R < v->L)
		return ;
	if (L <= v->L && v->R <= R){
		setto(v,val);
		return ;
	}
	push(v);
	setto(v->l,L,R,val);
	setto(v->r,L,R,val);
}

node* root;

ll get(ll x){
	node* v = root;

	while (v->L != x || v->R != x){
		push(v);
		if (v->l->R >= x)
			v = v->l;
		else
			v = v->r;
	}

	return v->addb+v->setto;
}


int len[110000];
int n,g,r;


void setto(int l,int r,ll val){
	setto(root,l,r,val);		
}    

void makeadd(int l,int r,ll val){
	add(root,l,r,val);		
}    

        

void print(node* v,int deep){
	if (!v)
		return;

	print(v->l,deep+1);
	for (int i = 0; i < deep; i++)
		cerr <<"  ";
	cerr << v->L <<" "<<v->R <<" "<<v->adda <<" "<<v->addb << endl;
	print(v->r,deep+1);
}



int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  scanf("%d %d %d",&n,&g,&r);

  for (int i = 0; i <= n; i++)
  	scanf("%d",&len[i]);

  root = new node;

  root->adda = root->addb = 0;
  root->L = 0;
  root->R = r+g-1;
  root->l = root->r = 0;
  root->setto = -1;

  ll sdv = 0;

  root->addb = 0;


  for (int i = n; i > 0; i--){
  	add(root,0,len[i]);
  	sdv = (sdv + (len[i]%(r+g))) % (r+g);

  	setto((g+sdv)%(r+g),(sdv+r+g-1)%(r+g),get(sdv)+r+g);
  	makeadd((g+sdv)%(r+g),(sdv+r+g-1)%(r+g),r);

  }

  root->addb += len[0];

  sdv = (sdv + len[0])%(r+g);

                                     

  int q;
  scanf("%d",&q);



  for (int i = 0; i < q; i++){
  	int t;
  	scanf("%d",&t);

  	ll ans = t + get((t+sdv)%(r+g));



  	printf(LLD"\n",ans);
  }

  return 0;
}