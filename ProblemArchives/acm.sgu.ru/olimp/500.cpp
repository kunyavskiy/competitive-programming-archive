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

struct filename{
	vector<string> p;
	filename(){};
	filename(string s);
	filename(const filename& f,string s);
};

filename::filename(const filename& f,string s){
	p=f.p;
	assert(p.size()>1);
	p.pop_back();
	string s1="";
	int sz=s.size();
	for (int i=0;i<=sz;i++){
		if (i==sz || s[i]=='\\'){
			if (s1=="..")
			{
				assert(p.size()>1);
				p.pop_back();
			}
			else
				p.pb(s1);
			s1="";
		}
		else
			s1+=s[i];
	}
	for (int i=0;i<p.size();i++)
		for (int j=0;j<p[i].size();j++)
			if (p[i][j]<='Z' && p[i][j]>='A')
				p[i][j]=p[i][j]-'A'+'a';
}

filename::filename(string s){
	int sz=s.size();
	int i;
	for (i=0;i<=sz;i++){
		assert(i<sz);
		if (s[i]==':')
			break;
	}
	p.pb(string(s.begin(),s.begin()+i));
	assert(s[i+1]=='\\');
	i+=2;
	string s1="";
	for (;i<=sz;i++){
		if (i==sz ||s[i]=='\\'){
			if (s1=="..")
			{
				assert(p.size()>1);
				p.pop_back();
			}
			else
				p.pb(s1);
			s1="";
		}
		else
			s1+=s[i];
	}
	for (int i=0;i<p.size();i++)
		for (int j=0;j<p[i].size();j++)
			if (p[i][j]<='Z' && p[i][j]>='A')
				p[i][j]=p[i][j]-'A'+'a';
};

bool operator<(const filename& a,const filename& b){
	return a.p<b.p;
}

struct file{
	filename name;
	vector<string> v;
	int ended;
	string res;
	file(){};
	bool read();	
	string calc();
};

bool file::read(){
	string s;
	if (!getline(cin,s))
		return false;
	name=filename(s);
	for (;;){
		getline(cin,s);
		if (s=="^Z") break;
		v.pb(s);		
	}
	ended=0;
	res="";
	return true;
}

map<filename,file*> fs;

typedef map<filename,file*>::iterator itertype;

file* read(){
	file* first=new file;
	first->read();
	fs[first->name]=first;
	while (true){
		file* tmp=new file;
		if (!tmp->read())
			break;
		fs[tmp->name]=tmp;
	}
	return first;
}

char stmp1[10000];
char stmp2[10000];

bool isinclude(string s,string& name){
	stmp1[0]=stmp2[0]=0;
	s=s+char(1);
	int a=sscanf(s.data()," # include < %[a-zA-Z0-9.\\:] > %s",stmp1,stmp2);
	if (a==0){
		//cerr<<s<<" : bad begin"<<endl;
		return false;
	}
	if (a==1){
		//cerr<<s<<" : bad end"<<endl;
		return false;
	}
	if (stmp2[1]!=0 || stmp2[0]!=1){
		//cerr<<s<<" : "<<stmp2<<" at the end"<<endl;
		return false;
	}
	name=stmp1;
	//cerr<<s<<" : "<<"OK with name "<<name<<endl;
	return true;
}

bool isabsolute(const string& s){
	for (int i=0;i<s.size();i++)
		if (s[i]==':')
			return true;
	return false;
}

void toolong(){
	printf("Too long file\n");
	exit(0);
}

string file::calc(){
	if (ended==2)
		return res;
	if (ended==1)
		toolong();
	ended=1;
	string iname;
	//cerr<<"CALCING "<<name.p.back()<<endl;
	//cerr<<v.size()<<" LINES"<<endl;
	for (int i=0;i<v.size();i++){
		if (isinclude(v[i],iname)){
			itertype iter;
			if (isabsolute(iname))
				iter=fs.find(filename(iname));
			else
				iter=fs.find(filename(name,iname));
			if (iter==fs.end())
				continue;			
			res+=iter->second->calc();
		}
		else
			res+=v[i]+'\n';
	}
	ended=2;
	return res;
}

int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
	printf("%s",read()->calc().data());
  return 0;
}