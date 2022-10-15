#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

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

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

char s[300000];
char s1[300000];

#undef assert
#define assert(x) if (!(x)) throw 1




int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.cpp","w",stdout);
  #endif

  int ptr = 0;

  for (; (s[ptr++] = getc(stdin)) != EOF;);
  --ptr;

  for (int i = 0; i < ptr; i++)
  	if (s[i] == 10)
  		s[i] = char(215);
  	else if (s[i] == 13)
  		s[i] = char(216);
  	else if (s[i] == '"')
  		s[i] = char(217);
  	else if (s[i] == '?')
  		s[i] = char(218);
  	else {
  		assert(s[i] != char(215));
  		assert(s[i] != char(216));
		assert(s[i] != char(219));
		assert(s[i] != char(217));
		assert(s[i] != char(218));
  	}

  int ptr1 = 0;

  for (int i = 0; i < ptr; i++)
  	if (s[i] == 't' && s[i+1] == 'h')
  		s1[ptr1++] = char(219),i++;
  	else	
  		s1[ptr1++] = s[i];

  printf("//CPP\n");
  printf("#include <iostream>\n");
  printf("using namespace std;\n");
  printf("const string _s[1] = {\n");
  for (int i = 0; i < 1; i++)
  	printf("\"%s\"%c\n",string(s1+i*(ptr1/1+1),s1+min((i+1)*(ptr1/1+1),ptr1)).data(),",}"[i==0]);
  printf(";\n");
  printf("int main(){\n");
  printf("string s = \"\";");
  printf("for (int i = 0; i < 1; i++) s += _s[i];\n");
  printf("for (int i = 0; i < s.size(); i++)\n");
  printf("if (s[i] == char(215)) putc(10,stdout);\n");
  printf("else if (s[i] == char(216)) putc(13,stdout);\n");
  printf("else if (s[i] == char(219)) putc('t',stdout),putc('h',stdout);\n");
  printf("else if (s[i] == (char)217) putc('\"',stdout);\n");
  printf("else if (s[i] == (char)218) putc('?',stdout);\n");
  printf("else putc(s[i],stdout);\n");
  printf("}\n");
  return 0;
}