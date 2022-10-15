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

#ifndef LOCAL
#undef assert
#define assert(Expr) ;
#endif

#define vector botva475

using namespace std;

template<typename T>
struct vector{
	T* data;
	int csize;
	int rsize;
	int size()const{
		return csize;
	}		
	void push_back(const T& a){
		if (csize == rsize){			
			if (rsize==0){
				rsize=1;
				data = new T[1];
			}
			else {
				T* tmp=new T[rsize*2];
				memcpy(tmp,data,rsize*sizeof(T));
				rsize*=2;
				delete[] data;
				data=tmp;				
			}
		}
		data[csize++]=a;
	}
	vector(){
		data=0;
		csize=0;
		rsize=0;
	}
	T& operator[](int x){
		assert(x<csize);
		return data[x];
	}
	vector<T>(const vector<T>& a){
		csize=a.csize;
		rsize=a.rsize;
		if (data) delete[] data;
		data=new T[rsize];
		memcpy(a.data,data,csize*sizeof(T));
	}
	void clear(){
		if (data) delete[] data;
		data=0;
		csize=0;
		rsize=0;
	}
};



struct _tree;
typedef _tree* tree;
enum lexem {_open,_close,_add,_dec,_mult,_div,_var,_end,_begin};


inline bool isvarsimbol(char c){
	if ('a'<=c && c<='z')
		return true;
	if ('A'<=c && c<='Z')
		return true;
	return false;
}

struct _tree{
	vector<lexem> type;
	vector<tree> son;
	string name;		
	_tree(){
		type=vector<lexem>();
		son=vector<tree>();
		name="";
	}
};

char s[300];


_tree mem[1000];
int freetree;

inline tree gettree(){
	mem[freetree].type.clear();
	mem[freetree].son.clear();
	mem[freetree].name="";
	return &mem[freetree++];	
}



struct _current{
	int pos;
	lexem lex;
	string name;
	void next();
} current;

inline void _current::next(){
	if (s[pos]==0){
		lex=_end;
		return;		
	}
	if (isvarsimbol(s[pos])){
		lex=_var;
		name="";
		for (;s[pos] && isvarsimbol(s[pos]);++pos)
			name+=s[pos];		
		return;
	}
	char c=s[pos];
	if (c=='+')
		lex=_add;
	else if (c=='-')
		lex=_dec;
	else if (c=='*')
		lex=_mult;
	else if (c=='/')
		lex=_div;
	else if (c=='(')
		lex=_open;
	else if (c==')')
		lex=_close;		
	
	++pos;
}

tree expr();

tree mult(){
	if (current.lex == _var){
		tree res = gettree();
		res->name = current.name;
		current.next();
		return res;
	}
	if (current.lex == _open){	
		current.next();
		tree res=expr();
		assert(current.lex == _close);
		current.next();
		return res;
	}
	assert(false);
}

tree item(){
	tree res=mult();	
	if (current.lex == _mult || current.lex  == _div){
		tree tmp=gettree();
		tmp->son.pb(res);
		res=tmp;
		while (current.lex == _mult || current.lex  == _div){
			res->type.pb(current.lex);
			current.next();
			res->son.pb(mult());
		}
	}
	return res;
}

tree expr(){
	tree res=item();	
	if (current.lex == _add || current.lex  == _dec){
		tree tmp=gettree();
		tmp->son.pb(res);
		res=tmp;
		while (current.lex == _add || current.lex  == _dec){
			res->type.pb(current.lex);
			current.next();
			res->son.pb(item());
		}
	}
	return res;
}


char result[300];
char *res;

inline void printlex(lexem l){
	if (l == _add)	
		*res='+';
	if (l == _dec)
		*res='-';
	if (l == _mult)
		*res='*';
	if (l == _div)
		*res='/';
	res++;
}


void print(tree v,lexem prev,lexem next){
	if (v->type.size()==0){
		int sz=v->name.size();
		for (int i=0;i<sz;i++)
			*(res++)=v->name[i];
		return;
	}
	assert(v->type.size() == v->son.size()-1);
	bool q=false;
	if (prev == _dec){
		q |= (v->type[0] == _add) || (v->type[0] == _dec);
	}
	if (prev == _mult){
		q |= (v->type[0] == _add) || (v->type[0] == _dec);	
	}
	if (prev == _div){
		q |= true;
	}
	if (next == _mult){
		q |= (v->type[0] == _add) || (v->type[0] == _dec);	
	}
	if (next == _div){
		q |= (v->type[0] == _add) || (v->type[0] == _dec);	
	}

	
	if (q){
		*(res++)='(';
		prev=_begin;
		next=_end;
	}
	
	v->type.pb(next);
	print(v->son[0],prev,v->type[0]);
	int sz=v->son.size();
	for (int i=1;i<sz;i++){
		printlex(v->type[i-1]);
		print(v->son[i],v->type[i-1],v->type[i]);
	}
	
	if (q){
		*(res++)=')';
	}
	
}




int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int t;
    scanf("%d\n",&t);
	for (;t;--t){
		s[0]=0;
		gets(s);
		current.pos=0;
		current.next();
		freetree=0;
		memset(result,0,sizeof(result));
		res=result;
		print(expr(),_begin,_end);
		assert(current.lex == _end);
		puts(result);
	}
  return 0;
}