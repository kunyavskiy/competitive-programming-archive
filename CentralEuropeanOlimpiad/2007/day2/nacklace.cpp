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
#define deque botva156

#if ( _WIN32 || __WIN32__ )
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;


template<int n,typename T>
class deque{
	public:
	T *l,*r;
	deque<n-1,pair<T*,T*> > *ind;
	int size;
	deque<n,T>(){
		l=r=0;
		ind = 0;
		size = 0;
	}
	deque<n,T>* copy(){
		deque<n,T>* res = new deque<n,T>;
		res->l = l;
		res->r = r;
		res->ind = ind;
		res->size = size;
		return res;
	}
	void push_front(T*);
	void push_back(T*);
	T* pop_front();
	T* pop_back();
	T* get_front();
	T* get_back();
};

template <typename T>
class deque<0,T>{
	public:
	T *l;
	int size;
	deque<0,T>(){
		l=0;
		size = 0;
	}
	deque<0,T>* copy(){
		deque<0,T>* res = new deque<0,T>;
		res->l = l;
		res->size = size;
		return res;
	}
	void push_front(T*);
	void push_back(T*);
	T* pop_front();	
	T* pop_back();
	T* get_front();
	T* get_back();
};


template<int n,typename T>
void deque<n,T>::push_front(T* val){
	++size;
	if (!l) l = val;
	else {
		pair<T*,T*> *nval = new pair<T*,T*>;
		*nval = mp(val,l);
		ind = ind->copy();
		ind->push_front(nval);
		l = 0;
	}		
}

template<int n,typename T>
void deque<n,T>::push_back(T* val){
	++size;
	if (!r) r = val;
	else {
		pair<T*,T*> *nval = new pair<T*,T*>;
		*nval = mp(r,val);
		ind = ind->copy();
		ind ->push_back(nval);
		r= 0;
	}		
}

template<int n,typename T>
T* deque<n,T>::pop_front(){
	--size;
	if (l){
		T* temp = l;
		l = 0;
		return temp;
	}
	else if (ind->size){
		ind = ind->copy();
		pair<T*,T*>* in = ind->pop_front();
		l = in->second;
		return in->first;
	}
	else {
		assert(r);
		T* temp = r;
		r = 0;
		return temp;
	}
}

template<int n,typename T>
T* deque<n,T>::pop_back(){
	assert(size);
	--size;
	if (r){
		T* temp = r;
		r = 0;
		return temp;
	}
	else if (ind->size){
		ind = ind->copy();
		pair<T*,T*>* in = ind->pop_back();
		r = in->first;
		return in->second;
	}
	else {
		assert(l);
		T* temp = l;
		l = 0;
		return temp;
	}
}

template<int n,typename T>
T* deque<n,T>::get_front(){
	assert(size);
	if (l)
		return l;
	else if (ind->size)
		return ind->get_front()->first;
	else {
		assert(r);
		return r;	
	}
}

template<int n,typename T>
T* deque<n,T>::get_back(){
	assert(size);
	if (r)
		return r;
	else if (ind->size)
		return ind->get_back()->second;	
	else {
		assert(l);
		return l;
	}
}

template<typename T>
void deque<0,T>::push_front(T* val){
	++size;
	if (!l) l = val;
	else assert(false);
}

template<typename T>
void deque<0,T>::push_back(T* val){
	++size;
    if (!l)	l = val;
	else assert(false);	
}

template<typename T>
T* deque<0,T>::pop_front(){
	--size;
	if (l){
		T* temp = l;
		l = 0;
		return temp;
	}
	else 	
		assert(false);
}

template<typename T>
T* deque<0,T>::pop_back(){
	--size;
	if (l){
		T* temp = l;
		l = 0;
		return temp;
	}
	else 
		assert(false);
}

template<typename T>
T* deque<0,T>::get_front(){
	if (l)
		return l;
	else 
		assert(false);
}

template<typename T>
T* deque<0,T>::get_back(){
	if (l)
		return l;
	else
		assert(false);
}
const int DEEP = 19;

deque<DEEP,int>* version[1100000];int ptr;


template <int n,typename T>
deque<n,T>* emptydeque(deque<n,T>*){
	deque<n,T>* temp = new deque<n,T>;
	temp->l = temp->r = 0;
	temp->ind = emptydeque(temp->ind);
	return temp;
}

template <typename T>
deque<0,T>* emptydeque(deque<0,T>*){
	deque<0,T>* temp = new deque<0,T>;
	temp->l = 0;
	return temp;
}

void init(){
	version[0] = emptydeque(version[0]);
	
	ptr = 1;
}

void create (int from, char op, int left, int param){
	deque<DEEP,int>* temp = version[from]->copy();
	int* p = new int;
	*p = param;
	if (op == 'R' && left)
		temp->pop_front();
	else if (op == 'R' && !left)
		temp->pop_back();
	else if (op == 'A' && left)
		temp->push_front(p);
	else if (op == 'A' && !left)
		temp->push_back(p);
	else
		assert(false);
	version[ptr++] = temp;
}

int pearl(int id,int left){
	assert(version[id]);
	if (left){
		int* res = version[id]->get_front();
		assert(res);
		return *res;
	}
	else {	
		int* res = version[id]->get_back();
		assert(res);
		return *res;
	}
}