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

struct _node;
typedef _node* node;

struct _node{
	node next[26],lnk,p;
	char c;
	int64 cost;
	int64 t[110];
	_node(){
		memset(next,0,sizeof(next));
		memset(t,-1,sizeof(t));
		lnk=p=0;
		cost=0;
	}	
	int64 calc(int len){
		if (t[len]!=-1)
			return t[len];
		if (len == 0)
			return t[len]=cost;
		t[len]=0;
		for (int i=0;i<26;i++)
			t[len]=max(t[len],next[i]->calc(len-1));
		t[len]+=cost;
		return t[len];
	}
	void gen(int len){
		if (len == 0)
			return;
		for (int i=0;i<26;i++)
			if (t[len] == next[i]->t[len-1]+cost){
				printf("%c",char('a'+i));
				next[i]->gen(len-1);
				return;
			}
	}
};

node root;

void add(){
	string s;int cost;
	cin>>s>>cost;
	node t = root;
	for (int i=0;i<s.size();i++){
		if (t->next[s[i]-'a'] == 0){
			node tmp = new _node;
			tmp->p = t;
			t->next[s[i]-'a']=tmp;
			tmp->c = s[i];
		//	cerr<<t<<" -"<<s[i]<<"> "<<tmp<<endl;
		}
		t=t->next[s[i]-'a'];
	}
	t->cost += cost;
}

void doauto(){
	queue<node> q;
	q.push(root);
	for (;!q.empty();){
		node v = q.front();q.pop();
		if (v == root){
			v->lnk = v;
			for (int i=0;i<26;i++)
				if (!v->next[i])
					v->next[i]=v;
				else
					q.push(v->next[i]);
		}
		else {
			if (v->p == root)
				v->lnk = v->p;
			else
				v->lnk = v->p->lnk->next[v->c-'a'];
			for (int i=0;i<26;i++)
				if (v->next[i])
					q.push(v->next[i]);
				else
					v->next[i] = v->lnk->next[i];
			v->cost+=v->lnk->cost;					
		}
	}

}




int main()
{                        
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int k;
	cin>>k;
	root = new _node;
	for (int i=0;i<k;i++)
		add();
	doauto();
	int n;
	cin>>n;
	cout<<root->calc(n)<<endl;
	root->gen(n);
	return 0;
}