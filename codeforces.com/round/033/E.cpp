#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <iterator>
#include <algorithm>
#include <queue>
#include <memory.h>
#include <stack>
#define mp make_pair
#define pb push_back                     

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

const int sut=60*24;
const int month=sut*31;

int t[month][100];
int fromx[month][100];
int fromy[month][100];


int readtime(){
    int h,m;
    scanf("%d:%d",&h,&m);
    return h*60+m;
}

void readinterval(int& a,int& b){
    a=readtime();
    scanf(" - ");
    b=readtime();
}

int readdate(){
    int d;
    scanf("%d",&d);
    return (d-1)*sut+readtime();
}

void printdate(int t){
    int d=t/sut+1;
    t%=sut;
    int h=t/60;
    t%=60; 
    printf("%d %02d:%02d ",d,h,t);
}

int eatstart[200];              
int eatend[200];
int eptr;
int end[200];
int ptre[200];
int cost[200];
int l[200];
pair<int,pair<int,string> > r[200];
int m,n,k;
int timer;
bool isnow;
string Num[200];

void next(int i){
    end[i]++;
    while (end[i]==eatstart[ptre[i]]){
        end[i]=eatend[ptre[i]]+1;
        ptre[i]++;
    }
}

void next(){       
    if (!isnow)
        for (int i=0;i<m;i++)        
           next(i);
    timer++;
    if (eatend[eptr]+1==timer){
        isnow=false;
        eptr++;
    }                
    if (eatstart[eptr]==timer)
        isnow=true;
}

map<string,int> num;

void setval(int i,int j,int i1,int j1,int val=-1){
    if (val==-1)
        val=t[i1][j1];
    if (t[i][j]>=val)
        return;
    t[i][j]=val;
    fromx[i][j]=i1;
    fromy[i][j]=j1;
}
      
int kol;


void gen(int i,int j){
    if (i==0 || j==0){
        printf("%d\n",kol);
        return;
    } 
  //  cerr<<i<<" "<<j<<endl;
    if (t[fromx[i][j]][fromy[i][j]]!=t[i][j]){
        kol++;
        gen(fromx[i][j],fromy[i][j]);
        printf("%d ",r[j-1].second.first);
        printdate(fromx[i][j]);
        printdate(i-1);
        printf("\n");
    }
    else
        gen(fromx[i][j],fromy[i][j]);
}

    
int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    scanf("%d %d %d\n",&m,&n,&k);
    for (int i=0;i<m;i++){
        string s;
        getline(cin,s);
        num[s]=i;
       // cerr<<s<<endl;
    }
    for (int i=0;i<m;i++)
        scanf("%d",&l[i]);
    for (int i=0;i<4;i++){
        readinterval(eatstart[i],eatend[i]);
    }
    for (int i=4;i<200;i++)
        {
            eatstart[i]=eatstart[i-4]+sut;
            eatend[i]=eatend[i-4]+sut;
        }                   
    for (int i=0,it=0;i<n;i++,it++){
        string s;
        cin>>s;
        r[i].first=readdate();
        r[i].second.first=it+1;
        r[i].second.second=s;
        scanf("%d",&cost[i]);
        if (num.find(s)==num.end()){
            --n,--i;
            continue;
        }
        end[i]=-1;
    }                                         
    if (n==0){
        printf("0\n0\n");
        return 0;
    }
    sort(r,r+n);
    for (int i=0;i<n;i++)
        for (int j=0;j<l[num[r[i].second.second]]-1;j++)
            next(i);
  //  cerr<<r[0].first<<" "<<r[1].first<<endl;
    timer=-1;
    for (int i=0;i<k*sut+100;i++){
        next();
//        cerr<<i<<" "<<isnow<<" "<<end[0]<<" "<<end[1]<<endl;                
        for (int j=0;j<=n;j++)
            {
                setval(i+1,j,i,j);
                if (j!=n)
                   setval(i,j+1,i,j);
                if (j!=n && end[j]<r[j].first && !isnow){
                    setval(end[j]+1,j+1,i,j,t[i][j]+cost[j]);
                }
            }
    }
    int ans=0;
    for (int i=0;i<k*sut+100;i++)
        ans=max(ans,t[i][n]);
    printf("%d\n",ans);
    if (ans!=0)
        for (int i=0;i<k*sut+100;i++)
            if (t[i][n]==ans){
                gen(i,n);
                return 0;
            }
    return 0;
}