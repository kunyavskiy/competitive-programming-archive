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


char curc(){
    char c;
    c = getc(stdin);
    ungetc(c,stdin);
    return c;
}

void skipBlanks(){
   while (curc() == ' ')
       getc(stdin);
}    



char __getc(FILE* a){
   char c = getc(a);
   return c;
}
#define getc __getc
 



struct mono{
    vector<pair<char,int> > v;
    int coef;

    void getone(){
        skipBlanks();
        char c = getc(stdin);
        assert(isalpha(c));
        skipBlanks();
        int step = 1;
        if (curc() == '^'){
            assert(getc(stdin) == '^');
            scanf("%d",&step);
        }
        skipBlanks();
        v.pb(mp(c,step));
    }

    void load(){
        skipBlanks();
        if (curc() == '+' || curc() == '-'){
            char c = getc(stdin);
            assert(c == '+' || c == '-');
            skipBlanks();
            if (isdigit(curc()))
               scanf("%d",&coef);
            else
               coef = 1;
            if (c == '-')
                coef *= -1;
            skipBlanks();                    
            if (curc() == '*')
                assert(getc(stdin) == '*');
        }
        else if (isdigit(curc())){
            skipBlanks();
            scanf("%d",&coef);
            if (curc() == '*')
                assert(getc(stdin) == '*');
        }else {
            coef = 1;
        }

        skipBlanks();
        if (isalpha(curc())){
            getone();
            skipBlanks();
        }
        while (curc() == '*'){
             assert(getc(stdin) == '*');
             //agetc(stdin);
             getone();
             skipBlanks();
        }
        norm();
    }

    void norm(){
        sort(v.begin(),v.end());
        for (int i = 1; i < (int)v.size(); i++)
            if (v[i].first == v[i-1].first){
                v[i-1].second += v[i].second;
                v.erase(v.begin()+i);
                --i;
            }
        for (int i = 0; i < (int)v.size(); i++){
            if (v[i].second == 0){
                v.erase(v.begin()+i);
                i--;
            }
        }
    }
     
    bool operator<(const mono& r) const{
        if (deg() != r.deg())
            return deg() > r.deg();
        for (int i = 0; i < (int)v.size(); i++){
            assert(i < (int)r.v.size());
            if (v[i] != r.v[i]){
                if (v[i].first != r.v[i].first)
                    return v[i].first < r.v[i].first;
                return v[i].second > r.v[i].second;
            }
        }
        return false;
    }

    bool operator==(const mono& r) const{
        return v == r.v;
    }

    int deg() const{
        int sum = 0;
        for (int i = 0; i < (int)v.size(); i++)
            sum += v[i].second;
        return sum;
    }

    void print(bool first) const{                                                                                      
        assert(coef);

        if (first){
            if (coef < 0)
                printf("-");
        }
        else {
            if (coef < 0)
                printf(" - ");
            else
                printf(" + ");
        }

        if (abs(coef) != 1 || !v.size()){
            printf("%d",abs(coef));
            if (v.size())
                printf("*");
        }

        for (int i = 0; i < (int)v.size(); i++){
            printf("%c",v[i].first);
            if (v[i].second != 1)
               printf("^%d",v[i].second);
            if (i+1 != (int)v.size())
                printf("*"); 
        }                                                
    }

};

mono mult(const mono& a,const mono& b){
    mono res = a;
    res.coef *= b.coef;
    for (int i = 0; i < (int)b.v.size(); i++)
        res.v.pb(b.v[i]);
    res.norm();
    return res;
}


struct poly{
    vector<mono> v;


    void norm(){
        sort(v.begin(),v.end());
        for (int i = 1; i < (int)v.size();i++)
            if (v[i] == v[i-1]){
                v[i-1].coef += v[i].coef;
                v.erase(v.begin()+i);
                --i;
            }
        for (int i = 0; i < (int)v.size(); i++)
            if (v[i].coef == 0){
                v.erase(v.begin()+i);
                i--;
            }
    }

    void print(){
        if (!v.size()){
            printf("0\n");
            return;
        }
        v[0].print(true);
        for (int i = 1; i < (int)v.size(); i++)
            v[i].print(false);
        printf("\n");
    }

    void load(){
        while (curc() != 10 && curc() != 13 && curc() != EOF){
            mono temp;
            temp.load();
            skipBlanks();
            v.pb(temp);
        }
        norm();
    }

};


poly mult(const poly& a,const poly& b){
    poly res;
    for (int i = 0; i < (int)a.v.size(); i++)
        for (int j = 0; j < (int)b.v.size(); j++)
            res.v.pb(mult(a.v[i],b.v[j]));

    res.norm();
    return res;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

     poly a,b;
     a.load();
     scanf(" ");
     b.load();
     //a.print();
     //b.print();
     mult(a,b).print();

    return 0;
}