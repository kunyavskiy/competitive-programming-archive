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
    #define M_PI 3.1415926535897932384626433832795
    #define prev prev_dsfdfgfhgfh
    #define next next_mkdlsmfdgkl
    #define hash hash_mdfdsgdhgfm
    #undef assert
    #define assert(x) if (!(x)) throw 1
    #define sqrt(x) sqrt((double)(x))
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

const string _spec[35] = {"and", "array", "begin", "case", "class", "const", "div", "do", "else", "end", "for", "function",
                        "if", "implementation", "interface", "mod", "not", "of", "or", "procedure", "program", "record", 
                        "repeat", "shl", "shr", "string", "then", "to", "type", "unit", "until", "uses", "var", "with",
                         "while"};
 
set<string> spec;

string downit(string s){
    for (int i = 0; i < (int)s.size(); i++)
        if ('A' <= s[i] && s[i] <= 'Z')
            s[i] -= 'A'-'a';
    return s;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    spec = set<string>(_spec,_spec+35);

    char c = getc(stdin);

    while (true){
        if (c == 0 || c == EOF)
            break;
        if (c == '\''){
            printf("<span class=string>");
            putc(c,stdout);
            do {
               c = getc(stdin);
               putc(c,stdout);
            } while (c != '\'');
            printf("</span>");
            c = getc(stdin);
            continue;
        }
        if (c == '{'){
            printf("<span class=comment>");
            putc(c,stdout);
            do {
               c = getc(stdin);
               putc(c,stdout);
            } while (c != '}');
            printf("</span>");
            c = getc(stdin);
            continue;
        }
        if (c == '/'){
            char c1 = getc(stdin);
            if (c1 != '/'){
               putc(c,stdout);
               c = c1;
               continue;
            }
            printf("<span class=comment>");
            putc('/',stdout);
            do {
               putc(c,stdout);
               c = getc(stdin);
            } while (c != 10 && c != 13);
            printf("</span>");
            continue;
        }
        if ('0' <= c && c <= '9'){  
            printf("<span class=number>");

            bool waspoint = false;
            do {
               putc(c,stdout);
               c = getc(stdin);
               if (c == '.'){
                 if (waspoint) 
                    break;
                 waspoint = true;
                 char c1 = getc(stdin);
                 if ('0' <= c1 && c1 <= '9'){
                    putc('.',stdout);
                    c = c1;
                 }
                 else {
                    ungetc(c1,stdin);
                    break;
                 }
               } 
            } while (('0' <= c && c <= '9') || c == '.');
            printf("</span>");
            continue; 
        }  
        if (c == '#'){
            char c1 = getc(stdin);
            if (!('0' <= c1 && c1 <= '9')){
                putc('#',stdout);
                c = c1;
                continue;              
            }  
            printf("<span class=string>");
            putc('#',stdout);
            c = c1;
            do {
               putc(c,stdout);
               c = getc(stdin); 
            } while ('0' <= c && c <= '9');
            printf("</span>");
            continue;
        }
        if (isalpha(c)){
            string s;
            do {
               s += c;
               c = getc(stdin);
            } while (isalpha(c) || isdigit(c));
            if (spec.find(downit(s)) != spec.end()){
                printf("<span class=keyword>%s</span>",s.data());
            }
            else {
                printf("%s",s.data());
            }
            continue;                
        }
        putc(c,stdout);
        c = getc(stdin);
    }

    return 0;
}