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

using namespace std;

char s[1100];

inline bool checknext(char* s,const string& t){
	for (int i=0;i<t.size();i++)
		if (s[i]!=t[i])
			return false;
	return true;
}

inline bool checkhttp(char* s){
	return checknext(s,"http://");
}

inline void skiphttp(char* &s){
	if (checkhttp(s)){
		s+=7;
		return;
	}
}

inline bool iswordchar(char c){
	if ('a'<=c && c<='z')
		return true;
	if ('A'<=c && c<='Z')
		return true;
	if ('0'<=c && c<='9')
		return true;
	return c=='_';
}


inline void skipword(char* &s){
	for (;iswordchar(*s);++s);	
}


inline void skipfile(char* &s){
	if (!iswordchar(*s))
		return;	
	skipword(s);
	while (*s=='.'){
		++s;
		if (!iswordchar(*s)){
			--s;
			return;	
		}
		skipword(s);
	}
}

bool checkpath(char *s){
	if (*s!='/')
		return false;
	++s;
	if (!iswordchar(*s))
		return false;
	skipword(s);
	return *s==0 || *s=='/';
}

inline void skiponepath(char* &s){
	++s;
	skipword(s);
}

inline void skippath(char* &s){
	while (checkpath(s))
		skiponepath(s);
}

bool checkint(char* s,char end,int maxv){
	int x=-1;
	for (;isdigit(*s);s++){
		if (x==-1){
			x=*s-'0';
			continue;
		}
		if (x==0)
			return false;
		x=x*10+*s-'0';
		if (x > maxv)
			return false;		
	}
	if (x==-1)
		return false;	
	if (*s!=end)
		return false;
	return true;	
}

void skipint(char* &s){
	for (;isdigit(*s);s++);
	if (*s=='.')
		s++;
}

bool checkip(char *s){
	if (!checkint(s,'.',255))
		return false;
	skipint(s);
	if (!checkint(s,'.',255))
		return false;
	skipint(s);
	if (!checkint(s,'.',255))
		return false;
	skipint(s);
	if (!checkint(s,'/',255) && !checkint(s,':',255) && !checkint(s,0,255))
		return false;
	return true;
}

inline void skipip(char* &s){	
	skipint(s);
	skipint(s);
	skipint(s);
	skipint(s);
}

inline bool checkname(char *s){
	if (!iswordchar(*s))
		return false;
	skipword(s);
	return (*s=='/' || *s==':' || *s==0);
}

inline void skipname(char* &s){
	skipword(s);
}

inline string getword(char* &s){
	string t="";
	for (;iswordchar(*s);++s)	
		t+=*s;
	return t;	
}

inline bool islatin(char c){
	if ('a'<=c && c<='z')
		return true;
	if ('A'<=c && c<='Z')
		return true;
	return false;
}

bool checkprefdom(char *s){
	string dom="";
	if (!iswordchar(*s))
		return false;
	for (bool q=false;!q || *s=='.';q=true){
		if (q)
			s++;
		dom=getword(s);
		if (dom.size()==0)
			return false;
	}
	if (*s!='/' && *s!=':' && *s!=0)
		return false;
	if (dom.size()!=2 && dom.size()!=3)
		return false;	
	for (int i=0;i<dom.size();i++)
		if (!islatin(dom[i]))
			return false;		
	return true;			
}

void skipprefdom(char* &s){
	for (;*s!='/' && *s!=':' && *s!=0;){
		skipword(s);
		if (*s=='.')
			++s;
	}
}


bool skiphost(char* &s){
	if (checkip(s)){
		skipip(s);
		return true;
	}
	if (checkprefdom(s)){
		skipprefdom(s);
		return true;
	}
	if (checkname(s)){
		skipname(s);
		return true;
	}
	return false;
}


bool skipport(char* &s){
	++s;
	if (checkint(s,'/',65535) || checkint(s,0,65535)){
		skipint(s);
		return true;
	}
	return false;
}

bool solve(){
	char* s=::s;
	skiphttp(s);
	if (!skiphost(s))
		return false;
	if (*s==0)
		return true;
	if (*s==':')
		if (!skipport(s))
			return false;
	if (*s==0)
		return true;
	
	if (*s!='/')
		return false;
	skippath(s);
	if (*s==0)
		return true;
	if (*s!='/')
		return false;
	s++;
	skipfile(s);
	return *s==0;
}

int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  for (;;){
  	memset(s,0,sizeof(s));
  	s[0]=0;
  	if (!gets(s))
  		break;
  	bool q=solve();
  	if (q)
  		printf("YES\n");
  	else 
  		printf("NO\n");
  }
  return 0;
}