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
using namespace std;

const int base=10000;
const int baselen=4;
const string baseformat="%04d";

struct tlong{
	vector<int> c;
	int& operator[](int a){
		return c[a];
	}
	int operator[](int a)const{
		return c[a];
	}
	unsigned int size() const{
		return c.size();
	}
	int& back(){
		return c.back();
	}
	int back() const {
		return c.back();
	}
	
	void resize(unsigned int size){
		c.resize(size);		
	}
	
	void pb(int a){	
		c.pb(a);
	}
	
	void pop_back(){
		c.pop_back();
	}
	
	inline void norm(){
		for (;size()>1 && back()==0;pop_back());
	}	
	tlong (int a){
		for (;a;a/=base)
			pb(a%base);
		if (size()==0)
			pb(0);
	}
	tlong(){
		resize(1);
		(*this)[0]=0;
	}
};


void print(const tlong& a,FILE* f=stdout){
	fprintf(f,"%d",a[a.size()-1]);
	for (int i=(int)a.size()-2;i>=0;--i)
		fprintf(f,baseformat.data(),a[i]);
}


tlong operator+(const tlong& a,const tlong& b){
	tlong res;
	res.resize(max(a.size(),b.size())+1);
	int asz=a.size();
	int bsz=b.size();
	int rsz=res.size();
	int c=0;
	for (int i=0;i<rsz;i++){
		if (i<asz) c+=a[i];
		if (i<bsz) c+=b[i];
		res[i]=c%base;
		c/=base;
	}
	assert(c==0);
	res.norm();
	return res;
}

tlong operator*(const tlong& a,const tlong& b){
	tlong res;
	res.resize(a.size()+b.size()+10);
	int asz=a.size();
	int bsz=b.size();
	for (int i=0;i<asz;i++)
		for (int j=0;j<bsz;j++){
			res[i+j]+=a[i]*b[j];
			for (int k=0;res[i+j+k]>=base;k++){
				res[i+j+k+1]+=res[i+j+k]/base;
				res[i+j+k]%=base;
			}
		}
	res.norm();
	return res;
}

tlong operator/(const tlong& a,const int& b){
	tlong res;
	res.resize(a.size());
	int c=0;
	for (int i=int(a.size())-1;i>=0;--i){
		c+=a[i];
		res[i]=c/b;
		c%=b;
		c*=base;		
	}
	res.norm();
	return res;
}

bool operator<(const tlong& a,const tlong& b){
	if (a.size()!=b.size())
		return a.size()<b.size();
	for (int i=(int)a.size()-1;i>=0;--i)
		if (a[i]!=b[i])
			return a[i]<b[i];
	return false;
}

bool operator==(const tlong& a,const tlong& b){
	if (a.size()!=b.size())
		return false;
	for (int i=(int)a.size()-1;i>=0;--i)
		if (a[i]!=b[i])
			return false;
	return true;
}

inline bool operator<=(const tlong& a,const tlong & b){
	return a<b || a==b;
}

inline bool operator>(const tlong& a,const tlong & b){
	return b<a;
}

inline bool operator>=(const tlong& a,const tlong& b){
	return b<=a;
}

inline bool operator!=(const tlong& a,const tlong& b){
	return !(a==b);
}

tlong operator/(const tlong& a,const tlong& b){
	tlong l=0;
	tlong r=a+1;
	tlong mid;
	for (;l+1<r;){
		mid=(l+r)/2;
		if (mid*b <= a)
			l=mid;
		else
			r=mid;		
	}
	return l;
}

struct fraction{
	tlong ch,zn;
	fraction(const tlong& a,const tlong& b){
		ch=a;
		zn=b;
	}	
	fraction(const tlong& a){
		ch=a;
		zn=1;
	}
	fraction(){
		ch=zn=0;
	}
	tlong value() const {
		assert(zn!=0);
		return ch/zn;
	}
	bool undef() const {
		return ch==0 && zn==0;
	}
};

fraction operator*(const fraction& a,const fraction& b){
	return fraction(a.ch*b.ch,a.zn*b.zn);
}

fraction operator/(const fraction& a,const fraction& b){
	return fraction(a.ch*b.zn,a.zn*b.ch);
}

bool operator<(const fraction& a,const fraction& b){
	return a.ch*b.zn < a.zn*b.ch;
}

bool operator<=(const fraction& a,const fraction& b){
	return a.ch*b.zn <= a.zn*b.ch;
}

bool operator>(const fraction& a,const fraction& b){
	return a.ch*b.zn > a.zn*b.ch;
}

bool operator>=(const fraction& a,const fraction& b){
	return a.ch*b.zn >= a.zn*b.ch;
}

bool operator==(const fraction& a,const fraction& b){
	return a.ch*b.zn == a.zn*b.ch;
}

bool operator!=(const fraction& a,const fraction& b){
	return a.ch*b.zn != a.zn*b.ch;
}

void print(const fraction& a){
	if (a.undef()) 
		cout<<"IDLE\n";
	else{
		print(a.value());
		cout<<endl;
	}
}

void eprint(const fraction& a){
/*	if (a.undef())
		cerr<<"UNDEF\n";
	else {*/
		print(a.ch,stderr);
		cerr<<"/";
		print(a.zn,stderr);
		cerr<<endl;
//	}
}



bool g[110][110];
fraction speed[110];
int x[110];
int y[110];
int r[110];
int n,m;

bool setval(int j,const fraction& a){
	if (speed[j].undef()){
		//eprint(a);
		speed[j]=a;
		return true;
	}
	if (a!=speed[j]){
		cout<<"DO NOT TURN IT ON!\n";
		exit(0);
	}	
	return false;
}

void dfs(int v){
//	cerr<<v<<endl;
	for (int i=0;i<n;i++){
		if (i==v) continue;
		if (x[i]==x[v] && y[i]==y[v]){
			if (setval(i,speed[v]))
				dfs(i);
		}
		else {
			if (!g[v][i]) continue;
			if (setval(i,speed[v]*fraction(r[v],r[i])))
				dfs(i);
		}		
	}	
}

int main()
{                        
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int start;
	scanf("%d %d %d",&n,&m,&start);
	--start;
	for (int i=0;i<n;i++)
		scanf("%d %d %d",&x[i],&y[i],&r[i]);
	for (int i=0;i<m;i++){
		int a,b;
		scanf("%d %d",&a,&b);
		--a,--b;
		g[a][b]=g[b][a]=1;
	}	
	speed[start]=tlong(60000);
//	eprint(speed[0]);
	dfs(start);		
	for (int i=0;i<n;i++)
		print(speed[i]);
	return 0;
}