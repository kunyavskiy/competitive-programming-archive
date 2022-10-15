// WHAT'S WRONG WITH YOU GUYS??? WTF IS PENTIUM 3??? PLEASE UPGRADE SERVERS! IT'S RIDICULOUS TO TEST SOLUTIONS ON 9-YEAR OLD SYSTEM!"
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

typedef long long ll;
typedef long double ld;

time_t START = clock();

const double MINT = 1;
const double MAXT = 10;
const double DT = MINT/MAXT;
const double TL1 = 0.3;
const double TL2 = 1.6;
const double TL3 = 1.9;

double T;

int a[310][310];
int n,m;

ll f;
int x[310],xptr;
int y[310],yptr;
int usedx[310],usedy[310];

ll bf;
int bx[310],bxptr;
int by[310],byptr;

bool checkTime(double TL){
    double curTime = (clock() - START)*1.0/CLOCKS_PER_SEC/TL;
    if (curTime > 1)
        return false;

    T = MAXT * pow(DT,curTime);
    #ifdef DEBUG
       fprintf(stderr,"Time = %lf\n",curTime * TL);
       fprintf(stderr,"Temperature = %lf\n",T);    
       fprintf(stderr,"Best = "LLD"\n",bf);        
       fprintf(stderr,"Cur = "LLD"\n\n\n",f);
    #endif
    return true;
}


inline void update(){
   if (f > bf){
      bf = f;
      bxptr = xptr;
      memcpy(bx,x,xptr*sizeof(int));
      byptr = yptr;
      memcpy(by,y,yptr*sizeof(int));
   }
}         

void revert(){
   f = bf;
   xptr = bxptr;
   memcpy(x,bx,xptr*sizeof(int));
   yptr = byptr;
   memcpy(y,by,yptr*sizeof(int));
   memset(usedx,-1,sizeof(usedx));
   memset(usedy,-1,sizeof(usedy));

   for (int i = 0; i < xptr; i++)
      usedx[x[i]] = i;
   for (int i = 0; i < yptr; i++)
      usedy[y[i]] = i;
}

int random(int l,int r){
    return (l + rand()%(r-l));
}

double drandom(){
    return (rand() * 1.0 / RAND_MAX);
}


void checkAll(){
    for (int i = 0; i < n; i++)
        if (usedx[i] != -1){
            assert(0 <= usedx[i] && usedx[i] < xptr);
            assert(x[usedx[i]] == i);
        }
    for (int i = 0; i < m; i++)
        if (usedy[i] != -1){
            assert(0 <= usedy[i] && usedy[i] < yptr);
            assert(y[usedy[i]] == i);
        }
    for (int i = 0; i < xptr; i++)
        assert(usedx[x[i]] == i);
    for (int i = 0; i < yptr; i++)
        assert(usedy[y[i]] == i);

    ll sum = 0;
    for (int i = 0; i < xptr; i++)
        for (int j = 0; j < yptr; j++)
            sum += a[x[i]][y[j]];
    assert(sum == f);        
}

inline void revx(int id){
   if (usedx[id] != -1){
       swap(x[usedx[id]],x[xptr-1]);
       --xptr;
       usedx[x[usedx[id]]] = usedx[id];
       usedx[id] = -1;
   }
   else {
       x[xptr] = id;
       usedx[id] = xptr++;
   }        
}

inline void revy(int id){
   if (usedy[id] != -1){
       swap(y[usedy[id]],y[yptr-1]);
       --yptr;
       usedy[y[usedy[id]]] = usedy[id];
       usedy[id] = -1;
   }
   else {
       y[yptr] = id;
       usedy[id] = yptr++;
   }   
}

void iterate(){
    if (random(0,2) == 0){
        int id = random(0,n);
        ll dsum = 0;
        for (int i = 0; i < yptr; i++)
            dsum += a[id][y[i]];

        

        if (usedx[id] != -1)
            dsum *= -1;

        if (drandom() < exp((dsum / T) / f)){
            f += dsum;
            revx(id);    
        }              
    }
    else {
        int id = random(0,m);
        ll dsum = 0;
        for (int i = 0; i < xptr; i++)
            dsum += a[x[i]][id];

        if (usedy[id] != -1)
            dsum *= -1;

        if (drandom() < exp((dsum / T) / f)){
            f += dsum;
            revy(id);         
        }  
    }
    update();
    #ifdef DEBUG
        checkAll();
    #endif
}


void gready(){
    static ll sum1[310];
    static ll sum2[319];
    static int lastid = -1, lasttp = -1;

    memset(sum1,0,sizeof(ll)*n);
    memset(sum2,0,sizeof(ll)*m);

    for (int i = 0; i < xptr; i++)
        for (int j = 0; j < m; j++)
            if (usedy[j] != -1)
                sum2[j] -= a[x[i]][j];
            else
                sum2[j] += a[x[i]][j];


    for (int i = 0; i < yptr; i++)
        for (int j = 0; j < n; j++)
            if (usedx[j] != -1)
                sum1[j] -= a[j][y[i]];
            else
                sum1[j] += a[j][y[i]];

    if (lasttp == 0) sum1[lastid] = -(1LL<<60);
    if (lasttp == 1) sum2[lastid] = -(1LL<<60);

    int id1 = max_element(sum1,sum1+n) - sum1;
    int id2 = max_element(sum2,sum2+m) - sum2;
    if (sum1[id1] > sum2[id2]){
        f += sum1[id1];
        revx(id1);          
        lastid = id1;
        lasttp = 0;
    }
    else {
        revy(id2);
        f += sum2[id2];          
        lastid = id2;
        lasttp = 1;
    }

    #ifdef DEBUG
        checkAll();
    #endif            
    
    update();
}

bool toogready(){
    static ll sum1[310];
    static ll sum2[319];

    memset(sum1,0,sizeof(ll)*n);
    memset(sum2,0,sizeof(ll)*m);

    for (int i = 0; i < xptr; i++)
        for (int j = 0; j < m; j++)
            if (usedy[j] != -1)
                sum2[j] -= a[x[i]][j];
            else
                sum2[j] += a[x[i]][j];


    for (int i = 0; i < yptr; i++)
        for (int j = 0; j < n; j++)
            if (usedx[j] != -1)
                sum1[j] -= a[j][y[i]];
            else
                sum1[j] += a[j][y[i]];


    ll s1,s2;
    s1 = s2 = 0;
    for (int i = 0; i < n; i++)
        if (sum1[i] > 0)
            s1 += sum1[i];
    for (int i = 0; i < m; i++)
        if (sum2[i] > 0)
            s2 += sum2[i];

    if (max(s1,s2) == 0) return false;

    if (s1 > s2){
        for (int i = 0; i < n; i++)
            if (sum1[i] > 0){
                revx(i);
                f += sum1[i];
            }
    }
    else {
        for (int i = 0; i < m; i++)
            if (sum2[i] > 0){
                revy(i);
                f += sum2[i];
            }
    }

    #ifdef LOCAL
        checkAll();
    #endif            
    
    update();
    return true;
}




int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    srand(time(NULL));

    scanf("%d %d",&n,&m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++){
            scanf("%d",&a[i][j]);
            f = max(f,(ll)a[i][j]);
        }

    xptr = 1;
    yptr = 1;
    for (int i = 0; i < n; i++)
        usedx[i] = -1;
    for (int i = 0; i < m; i++)
        usedy[i] = -1;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (a[i][j] == f)
                x[0] = i, y[0] = j;

    usedx[x[0]] = 0;
    usedy[y[0]] = 0;

    update();

    #ifdef DEBUG
    checkAll();
    #endif


    /*while (checkTime(TL1)){
        for (int i = 0; i < 500; i++)
            iterate();
    }*/

    //while (toogready());

    fprintf(stderr,"%18I64d\n",bf);

    while (checkTime(TL1))
         gready();
    fprintf(stderr,"%18I64d\n",bf);

    revert();

    T = 1e-9;
    for (int i = 0; i < 30000; i++)
        iterate();
    fprintf(stderr,"%18I64d\n",bf);

    while (checkTime(TL2)){
        if (random(1,10) == 3)
            T = 1e-9;
        for (int i = 0; i < 500; i++)
            iterate();
    }
    fprintf(stderr,"%18I64d\n",bf);

    while(checkTime(TL3) && toogready());

    T = 1e-9;
    while(checkTime(TL3))
        gready(); 

    revert();

    //assert(bf > 0);
    fprintf(stderr,"%lf\n",(clock()-START)*1.0/CLOCKS_PER_SEC);
    fprintf(stderr,"%18I64d\n",bf);

    sort(bx,bx+bxptr);
    sort(by,by+byptr);

    printf("%d %d\n",bxptr,byptr);
    for (int i = 0; i < bxptr; i++)
        printf("%d%c",bx[i]," \n"[i==bxptr-1]); 
    for (int i = 0; i < byptr; i++)
        printf("%d%c",by[i]," \n"[i==byptr-1]);          

  return 0;
}