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

vector<string> s[110000];


int cmpi(const string& a,const string& b,int ig){
    if (!isdigit(a[0]) && !isdigit(b[0]))
        return strcmp(a.data(),b.data());
    if (isdigit(a[0]) && !isdigit(b[0]))
        return -1;
    if (isdigit(b[0]) && !isdigit(a[0]))
        return 1;

    int ptr1 = 0;
    int ptr2 = 0;
    while (ptr1 < (int)a.size() && a[ptr1] == '0')
        ptr1++; 
    while (ptr2 < (int)b.size() && b[ptr2] == '0')
        ptr2++;

    if ((int)a.size() - ptr1 != (int)b.size() - ptr2)
        return 2*((int)a.size() - ptr1 > (int)b.size() - ptr2)-1;

    for (int j = 0; j+ptr1 < (int)a.size(); j++)
        if (a[j+ptr1] != b[j+ptr2])
            return 2*(a[j+ptr1] > b[j+ptr2])-1;

    if (ptr1 == ptr2)
        return 0;
    return (2*(ptr1 < ptr2) - 1)*ig;    
}


string join(const vector<string>&);

bool cmp(const vector<string>& a,const vector<string>& b){

    //cerr << a <<" "<<b<<endl;
    for (int i = 0; i < (int)a.size() && i < (int)b.size(); i++){
       int q = cmpi(a[i],b[i],0);
       //cerr << a[i] <<" "<<b[i] <<" "<<q<<endl;

       if (q == 1)
         return false;
       if (q == -1)
         return true;
    }
    if (a.size() != b.size())
        return a.size() < b.size();  
   // cerr <<"!!!"<<join(a)<<" "<<join(b)<<endl;
    for (int i = 0; i < (int)a.size() && i < (int)b.size(); i++){
       int q = cmpi(a[i],b[i],1);
     //  cerr << a[i] <<" "<<b[i] <<" "<<q<<endl;

       if (q == 1)
         return false;
       if (q == -1)
         return true;
    }

    return a.size() < b.size();
}

void split(const string& a,vector<string>& b){
    int l = 0;
    for (int j = 1; j <= (int)a.size(); j++)
        if (j == (int)a.size() || isdigit(a[j]) != isdigit(a[j-1])){
            b.pb(string(a.begin()+l,a.begin()+j));
            l = j;
     //       cerr << b.back() << " ";
        }
    //cerr<<endl;   
}

string join(const vector<string> & v){
    string s = "";
    for (int i = 0; i < (int)v.size(); i++)
        s += v[i];
    return s;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int n=0;
  string s;
  while (getline(cin,s)) 
    split(s, ::s[n++]);
    
  stable_sort( ::s, ::s+n,cmp);

  for (int i = 0; i < n; i++)
    puts(join( ::s[i]).data());

  return 0;
}