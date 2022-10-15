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
#define abs(a) (((a)<0)?(-(a)):(a))
using namespace std;

const int base=1000;
const int baselen=3;

struct klong;

struct tlong{
	vector<int> c;
	int sign;
	tlong(string);
	tlong(const klong&);
	tlong(int);
	tlong (int sz,int){
		c.resize(sz,0);
		sign=1;
	}
	int& operator[](int a){
		return c[a];
	}	
	int operator[](int a) const{
		return c[a];
	}
	void norm();
	int size() const{
		return c.size();
	}
	void print();
	tlong(){
		c.pb(0);
	}
};

void tlong::print(){
	norm();
	if (sign==-1)
		printf("-");
	printf("%d",c.back());
	for (int i=(int)c.size()-2;i>=0;i--)
		printf("%03d",c[i]);
	printf("\n");
}

tlong::tlong(string s){
	sign=1;
	if (s[0]=='-'){
		sign=-1;
		s.erase(s.begin());
	}
	for (int i=s.size();i>=0;i-=baselen)
		c.pb(atoi(string(s.begin()+max(i-baselen,0),s.begin()+i).data()));
}

tlong::tlong(int a){
	sign=1;
	if (a<0){
		sign=-1;
		a*=-1;
	}		
	for (;a;a/=base)
		c.pb(a%base);
	if (c.size()==0) c.pb(0);
}

void tlong::norm(){
	for (;c.size()>1 && c.back()==0;c.pop_back());
	if (c.back()<0){
		sign*=-1;
		int csz=c.size();
		for (int i=0;i<csz;i++)
			c[i]*=-1;
		for (int i=0;i<csz;i++)
			if (c[i]<0){
				c[i]=c[i]+base;
				c[i+1]--;
			}
		for (;c.size()>1 && c.back()==0;c.pop_back());
	}
	if (c.size()==1 && c.back()==0)
		sign=0;
}

tlong operator+(const tlong& a,const tlong& b){
	int asz=a.size(),bsz=b.size();
	tlong res(max(asz,bsz)+10,0);
	int rsz=res.size();
	res.sign=1;
	for (int i=0;i<rsz-4;i++){
		if (i<asz) res[i]+=a[i]*a.sign;
		if (i<bsz) res[i]+=b[i]*b.sign;
		if (res[i]>=base){
			res[i]-=base;
			++res[i+1];
		}
		if (res[i]<0){
			res[i]+=base;
			--res[i+1];
		}
	}
	res.norm();
	return res;		
}

tlong operator-(const tlong& a,const tlong& b){
	int asz=a.size(),bsz=b.size();
	tlong res(max(asz,bsz)+10,0);
	int rsz=res.size();
	res.sign=1;
	for (int i=0;i<rsz-4;i++){
		if (i<asz) res[i]+=a[i]*a.sign;
		if (i<bsz) res[i]-=b[i]*b.sign;
		if (res[i]>=base){
			res[i]-=base;
			++res[i+1];
		}
		if (res[i]<0){
			res[i]+=base;
			--res[i+1];
		}
	}
	res.norm();
	return res;		
}

tlong operator*(const tlong& a,int b){
	tlong res(a.size()+5,0);
	int64 c=0;
	for (int i=0;i<res.size()-2;i++){
		if (i<a.size())		c+=a[i]*1LL*b;
		res[i]=c%base;
		c/=base;
	}
	res.norm();
	return res;		
}

int smod(int64 a,int b){
	if (a<0){
		a+=b*(abs(a)/b);
		a+=b*100;
	}
	return a%b;
}

int operator%(const tlong& a,int b){
	int asz=a.size();
	int res=0;
	for (int i=asz-1;i>=0;--i)
		res=smod(res*1LL*base+a[i]*a.sign,b);
	return res;
}

bool operator<(const tlong& a,const tlong& b){
	assert(a.sign>=0 && b.sign>=0);
	if (a.size()!=b.size())
		return a.size()<b.size();
	for (int i=(int)a.size()-1;i>=0;--i)
		if (a[i]!=b[i])
			return a[i]<b[i];
	return true;
}

istream& operator>>(istream& ist,tlong& t){
	string s;
	getline(ist,s);
	t=tlong(s);
	return ist;
}

int p[350];
int r[350][350];
const int pr_kol=170;

bool check(int a){
	for (int i=2;i*i<=a;i++)
		if (a%i==0)
			return 0;
	return 1;
}

void gcd (int a,int b,int& x,int& y)
{
	if (a==0)
	{
		x=0;y=1;
		return;
	}
	int x1,y1;
	gcd(b%a,a,x1,y1);
	x=y1-(b/a)*x1;
	y=x1;
	return;
}

void genprost(){
	int ptr=0;
	for (int i=1000000;ptr<pr_kol;i++)
		if (check(i))
			p[ptr++]=i;
	for (int i=0;i<pr_kol;i++)
		for (int j=0;j<pr_kol;j++)
			if (i!=j){			
				int a;
				gcd(p[i],p[j],r[i][j],a);
				r[i][j]=smod(r[i][j],p[j]);
				assert((p[i]*1LL*r[i][j])%p[j]==1);
			}
}

struct klong{
	vector<int> c;
	int& operator[](int a){
		return c[a];
	}
	int operator[](int a) const{
		return c[a];
	}
	klong(const tlong&);
	klong(){
		c.resize(pr_kol,0);
	}
};

klong::klong(const tlong& a){
	c.resize(pr_kol);
	for (int i=0;i<pr_kol;i++)
		c[i]=a%p[i];
}

klong operator+(const klong& a,const klong& b){
	klong res;
	for (int i=0;i<pr_kol;i++){
		res[i]=a[i]+b[i];
		if (res[i]>=p[i])
			res[i]-=p[i];
	}
	return res;
}

klong operator-(const klong& a,const klong& b){
	klong res;
	for (int i=0;i<pr_kol;i++){
		res[i]=a[i]-b[i];
		if (res[i]<0)
			res[i]+=p[i];
	}
	return res;
}

klong operator*(const klong& a,const klong& b){
	klong res;
	for (int i=0;i<pr_kol;i++)
		res[i]=(a[i]*1LL*b[i])%p[i];
	return res;
}

klong operator-(const klong& a){
	klong res;
	for (int i=0;i<pr_kol;i++){
		res[i]=p[i]-a[i];
		if (res[i]==p[i])
			res[i]=0;
	}
	return res;
}

istream& operator>>(istream &ist,klong& b){
	tlong t;
	ist>>t;
	b=klong(t);
	return ist;
}

tlong::tlong(const klong& a){
	tlong res(0),cur (1);
	c.pb(0);
	vector<int> x(pr_kol);
	for (int i=0; i<pr_kol; ++i) {
		x[i] = a[i];
		for (int j=0; j<i; ++j) 
			x[i] = smod(r[j][i] * 1LL *(x[i] - x[j]),p[i]);
		res=res+cur*x[i];
		cur=cur*p[i];
	}
	tlong st10=1;
	for (int i=0;i<1000;i+=5)
		st10=st10*100000;
	if (!(res<st10)){
		tlong pro=1;
		for (int i=0;i<pr_kol;i++)
			pro=pro*p[i];
		assert(res<pro);
		assert(!(pro<st10*2));
		res=res-pro;
	}
//	cerr<<a.c[0]<<" "<<p[0]<<endl;
	*this=res;
}

klong per[26];
char s[110000];
int ptr;

klong expr();
klong item();
klong mult();

klong mult(){
	if (s[ptr]=='['){
		++ptr;
		klong tmp=expr();
		tmp=tmp*tmp;
		assert(s[ptr]==']');
		++ptr;
		return tmp;
	}
	if (s[ptr]=='('){
		++ptr;
		klong tmp=expr();
		assert(s[ptr]==')');
		++ptr;
		return tmp;
	}
	if (s[ptr]=='-'){
		++ptr;
		return -mult();
	}
	if (s[ptr]=='+'){
		++ptr;
		return mult();
	}
	return per[s[ptr++]-'a'];
}

klong item(){
	klong a=mult();
	for (;;){
		if (s[ptr]=='*'){
				++ptr;
				a=a*mult();
				continue;
			}
		break;
	}
	return a;
}

klong expr(){
	klong a=item();
	for (;;){
		if (s[ptr]=='+'){
			++ptr;
			a=a+item();
			continue;
		}
		if (s[ptr]=='-'){
			++ptr;		
			a=a-item();
			continue;
		}
		break;
	}
	return a;
}


int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	genprost();
	int n;
	scanf("%d\n",&n);
	for (int i=0;i<n;i++)
		cin>>per[i];
	gets(s);
	ptr=0;
	tlong(expr()).print();	
    return 0;
}