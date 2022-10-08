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
#include <iterator>
#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <stack>
#define mp make_pair
#define pb push_back   
#define setval(a,v) memset(a,v,sizeof(a))
using namespace std;

typedef long long int64;
typedef long double ld;

const string TASKNAME = "A";
const string TASKMOD = "small";
const string INFILE = TASKNAME+"-"+TASKMOD+".in";
const string OUTFILE = TASKNAME+"-"+TASKMOD+".out";



const string inp = "ejpmysljylckdkxveddknmcrejsicpdrysirbcpcypcrtcsradkhwyfrepkymveddknkmkrkcddekrkdeoyakwaejtysrreujdrlkgcjvzq";
const string oup = "ourlanguageisimpossibletounderstandtherearetwentysixfactorialpossibilitiessoitisokayifyouwanttojustgiveupqz";

char mt[256];

void PreCalc(){
    memset(mt,-1,sizeof(mt));
    for (int i = 0; i < (int)inp.size(); i++){
        assert(mt[(unsigned char)inp[i]] == -1 || mt[(unsigned char)inp[i]] == oup[i]);
        mt[(unsigned char)inp[i]] = oup[i];
    }
    mt[32] = ' ';
}

char s[1000];

void solve(){
    gets(s);
    for (int i = 0; s[i]; i++)
        printf("%c",mt[(unsigned char)s[i]]);
    printf("\n");
}

int main(){
    freopen(INFILE.data(),"r",stdin);
    freopen(OUTFILE.data(),"w",stdout);
    PreCalc();
    int t;
    gets(s);
    sscanf(s,"%d",&t);
    for (int i=1;i<=t;i++)
        {
            printf("Case #%d: ",i);
            solve();
            if (i>t-20 || i%10==0)
                cerr<<"SOLVED:"<<i<<endl;
        }
    return 0;
}