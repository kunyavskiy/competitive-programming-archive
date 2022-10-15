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
#define setval(a,v) memset(a,v,sizeof(a))
#define fileinout
using namespace std;

const int base = 10;
typedef vector<int> tlong;

void readlong(tlong& a)
{
	string s;
	cin>>s;             
	a.resize(0);
	for (int i=s.length()-1;i>=0;i--)          
	  a.pb(s[i]-'0');
	return;
}

tlong operator+(tlong a, tlong b)
{
	tlong res(max(a.size(),b.size())+10);
	int carry = 0;
	for (int i=0;i<max(a.size(),b.size()) || carry;++i) 
	{
		res[i]=carry+(i<b.size()?b[i]:0)+(i<a.size()?a[i]:0);
		carry=res[i]/base;
		res[i]%=base;
	}
	if (res[res.size()-1]==0)
		res.pop_back();
	return res;
}

tlong operator-(tlong a,tlong b)
{
	tlong res(a.size());
	int carry=0;
	for (int i=0;i<a.size();++i) 
	{
		res[i]=a[i]-carry-(i<b.size()?b[i]:0);
		carry=res[i]<0;
		if (carry)
		  res[i] += base;
	}
	while (res.size() > 1 && res.back() == 0)
		res.pop_back();	
	return res;
}

tlong operator*(tlong a,int b)
{
	vector<int> res(a.size()+10);
	int carry=0;
	for (int i=0;i<res.size();++i) 
	{                   
		long long cur = carry + ((i<a.size())?(a[i]):(0)) * 1ll * b;
		res[i] = int (cur % base);
		carry = int (cur / base);
	}
	while (res.size() > 1 && res.back() == 0)
		res.pop_back();
	return res;
}

tlong inttolong(int a)
{
	tlong res(0);    
	if (a==0)
		res.pb(0);
	for (;a;a/=base)
		res.pb(a%base);
	return res;
} 

bool operator<=(tlong& a,tlong& b)
{                   
	while (a.size() > 1 && a.back() == 0)
		a.pop_back();
	while (b.size() > 1 && b.back() == 0)
		b.pop_back();
	if (a.size()!=b.size())
		return a.size()<b.size();
	for (int i=a.size()-1;i>=0;i--)
		{
			if (a[i]<b[i])
				return true;
			if (a[i]>b[i])
				return false;
		}
	return true;
}

bool operator<(tlong& a,tlong& b)
{                   
	while (a.size() > 1 && a.back() == 0)
		a.pop_back();
	while (b.size() > 1 && b.back() == 0)
		b.pop_back();
	if (a.size()!=b.size())
		return a.size()<b.size();
	for (int i=a.size()-1;i>=0;i--)
		{
			if (a[i]<b[i])
				return true;
			if (a[i]>b[i])
				return false;
		}
	return false;
} 

tlong t[110][15];
bool cnted[110][15];
int L;
int SZ;

tlong cnt(int l,int kol)
{
	if (kol>10 || kol>SZ || l>L)
		return inttolong(0);
	if (cnted[l][kol])
		return t[l][kol];     
	cnted[l][kol]=true;    
	if (((l>0) && (kol==0)) || ((l==0) && (kol!=0)))
		return inttolong(0);
	if (l==L)
	{
		tlong ans=inttolong(1);
		for (int i=10-kol+1;i<=10;i++)
			ans=ans*i;          
		return t[l][kol]=ans;
	}                        
	return t[l][kol]=cnt(l+1,kol+1)*(SZ-kol)+cnt(l+1,kol)*kol;
}
         
bool used[255];
string s;      

void print_buk(int l,int kol,tlong& num){	
	if (l==L)
		return;
	for (int i='A';i<='A'+SZ-1;i++)
		if (used[i])
		{
			  if (t[l+1][kol]<=num)
			  	num=num-t[l+1][kol];
			  else
			  {
			  	s+=i;
			  	print_buk(l+1,kol,num);
			  	return;
			  }
		}
		else if (kol<10)
				 {
			      if (t[l+1][kol+1]<=num)
			      	num=num-t[l+1][kol+1];
			      else
			      	{
			      		s+=i;
			      		used[i]=true;
			      		print_buk(l+1,kol+1,num);
			      		return;
			      	}
         }
  assert(false);
}

tlong tc[110]; 

tlong cnt(int l)
{             
		if (l==L)
			return tc[l]=inttolong(1);
		if (used[s[l]])
			return tc[l]=cnt(l+1);
		used[s[l]]=true;
		bool cnted=false;
		tlong next;   		
		tc[l]=inttolong(0);
		for (int i='0';i<='9';i++)
		if (!used[i])
		{         
			if (!cnted)
			{
				used[i]=true;
				next=cnt(l+1);
				cnted=true;
				used[i]=false;
			}
			tc[l]=tc[l]+next;
		}     
		return tc[l];
}

char uc[255];       

void print_cif(int l,tlong& num)
{
   if (l==L)
   {
			assert(num==inttolong(0));  
   		reverse(&s[0],&s[L]);
   		return;
   }
   if (uc[s[l]]!=0)
   {
   		s+=uc[s[l]];
   	  print_cif(l+1,num);
   	  return;
   }
   for (int i='0';i<='9';i++)
   		if (!used[i])
   			if (tc[l+1]<=num)
   				num=num-tc[l+1];
   			else
   			{
   				s+=i;
   				used[i]=true;
   				uc[s[l]]=i;
   				print_cif(l+1,num);
   				return;
   			}	
	assert(false);
}


int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif               
  int tests;
  scanf("%d %d %d",&SZ,&L,&tests);
  setval(cnted,false);
	for (int i=0;i<101;i++)
		for (int j=0;j<11;j++)
			cnt(i,j);
	for (;tests;--tests)
  {
  	s="";
  	setval(uc,false);
  	setval(used,false);
  	tlong num;
  	readlong(num);               
  	print_buk(0,0,num);
  	reverse(s.begin(),s.end());
  	setval(used,false);
		cnt(0);                      
  	setval(used,false);
  	print_cif(0,num);
  	printf("%s\n",s.data());
  }                         
  return 0;
}