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

typedef long long int64;
typedef long double ld;

int n,k;

int pl[15];
int mn[15];
int per[15];

void genpl(){
	int64 tmp = 1;
	for (int i=1;i<10;i++)
		tmp=tmp*10;
	int ptr = 9;
	for (;ptr>=0;){
		pl[ptr]=n/(k*tmp);
		n%=(k*tmp);
		--ptr;
		tmp/=10;
	}
}

void genmn(){
	if (n==0)
		return;
	if (k==2 || k==4 || k==8 || k==5){
		for (int i=0;n;i++){
			n=n*10;
			mn[i]=n/k;
			n%=k;
		}
		return;
	}
	int ptr=1;
	if (k==6){
		per[ptr]=-1;
		n=n*10;
		mn[ptr++]=n/k;
		n=n%k;
	}	
	else
		mn[1]=-1;
	if (k%3==0){
		n=n*10;
		per[ptr]=n/k;
		return;
	}
	for (int i=1;i<=6;i++){
		n=n*10;
		per[i]=n/k;
		n=n%k;
	}
}

string get(){
	string s="";
	for (int i=9;i>=0;--i){
		s+=char('0'+(pl[i]>0));
		pl[i]-=(pl[i]>0);		
	}
	s=s+'.';
	if (k==2 || k==4 || k==8 || k==5){
		for (int i=0;i<10;i++){
			s+='0'+(mn[i]>0);
			mn[i]-=(mn[i]>0);
		}
		return s;		
	}
	int ptr=1;
	if (k==6){
		s+='0'+(mn[1]>0);
		mn[1]-=(mn[1]>0);
		ptr++;
	}
	s+='(';
	if (k%3==0){	
		s+='0'+(per[ptr]>0);
		per[ptr]-=(per[ptr]>0);		
	}
	else {	
		for (int i=1;i<=6;i++){
			s+='0'+(per[ptr]>0);
			per[ptr]-=(per[ptr]>0);
			++ptr;
		}		
	}
	s+=')';
	return s;	
}

string gen(string intp,string drob){
	if (!drob.size())
		return intp;
	if (!intp.size())
		return "0."+drob;
	return intp+'.'+drob;
}

string norm(string s){
	string intp(s.begin(),s.begin()+s.find('.'));
	while (intp.size() && intp[0] == '0')
		intp.erase(intp.begin(),intp.begin()+1);
	if (s.find('(') == string::npos){
		string drob(s.begin()+s.find('.')+1,s.end());
		while (drob.size() && drob[drob.size()-1]=='0')
			drob.erase(drob.end()-1);
		return gen(intp,drob);		
	}
	string pper(s.begin()+s.find('.')+1,s.begin()+s.find('('));
	string per(s.begin()+s.find('(')+1,s.begin()+s.find(')'));
	if (per.find('1') == string::npos){
		string drob=pper;
		while (drob.size() && drob[drob.size()-1]=='0')
			drob.erase(drob.end()-1);
		return gen(intp,drob);
	}
	for (;pper.size() && pper[pper.size()-1] == per[per.size()-1];){
		pper.erase(pper.end()-1);
		rotate(per.begin(),per.end()-1,per.end());
	}
	
	if (per.size()>1){
		bool q = true;
		for (int i=0;i<2;i++)
			if (per[i] != per[i+2] || per[i] != per[i+4])
				q=false;
		if (q)
			per = string(per.begin(),per.begin()+2-(per[0]==per[1]));						
		else {
			bool q = true;
			for (int i=0;i<3;i++)	
				if (per[i] != per[i+3])
					q=false;
			if (q)
				per = string(per.begin(),per.begin()+3);
		}
		
				
	}
	
	string drob = pper+'('+per+')';
	return gen(intp,drob);
}

void convert(string& s){
	for (int i=0;i<s.size();i++)
		if (s[i]=='1')
			s[i]='0'+k;		
}

void solve(){
	printf("%d=",n);
	genpl();
	genmn();
	bool q=false;
	while (true){
		string s=get();
		s=norm(s);
		convert(s);
		if (s=="")
			break;
		if (q)
			printf("+");
		else
			q=true;
		printf("%s",s.data());
	}
	printf("\n");
}



int main()
{
	freopen("numbers.in","r",stdin);
	freopen("numbers.out","w",stdout);
	cin>>n>>k;
 	solve();
	return 0;
}