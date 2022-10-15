#pragma optimize("time",on)

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



#define lf(x) ((x)<<1)
#define rg(x) (((x)<<1)|1)
#define par(x) ((x)>>1)


#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;




typedef long long int64;
typedef float ld;

template<typename T>
inline T sqr(T a){
	return a*a;
}

const int MAXSQRT=8*1000*1000;
ld sqrts[MAXSQRT+100];

void initsqrt(){
	for (int i=0;i<=MAXSQRT+50;i++)
		sqrts[i]=sqrt(i);
}

inline ld mysqrt(int x){
	return sqrts[x];
}

struct heap{
		int *h,*b,*num;
		int sz,szmem;
		void up(int pos);
		void down(int pos);
		inline void norm(int pos){
			up(pos);
			down(pos);
		}
		void resize(int);
		heap(){
			h=b=num=0;
			sz=0;
		}
		void setval(int a,int b);
		int getmin();
		int getval(int);	
};

void heap::resize(int n){
	if (n>szmem){
		szmem=max(n,40);		
		if (h) delete[] h;
		if (b) delete[] b;
		if (num) delete[] num;
		h=new int[szmem];		
		b=new int[szmem];
		num=new int[szmem];
		--h,--b,--num;
	}
	sz=n;
	for (int i=1;i<=n;i++){
		h[i]=0;
		b[i]=num[i]=i;
	}
	sz=n;
}

void heap::up(int pos){
	int x=h[pos];
	int back=b[pos];
	int nm=num[pos];
	int tmp;
	for (;pos!=1;){	
		tmp=par(pos);
		if (h[tmp]<=x)	break;
		h[pos]=h[tmp];
		b[num[tmp]]=pos;
		num[pos]=num[tmp];
		pos=tmp;
	}
	h[pos]=x;
	b[nm]=pos;
	num[pos]=nm;
	
}

void heap::down(int pos){
	int l,r;
	int x=h[pos];
	int nm=num[pos];
	for (;;){
		l=lf(pos);
		r=rg(pos);
		if (l>sz) break;
		if (r<=sz){
			if (h[l]>h[r])
				swap(l,r);				
		}
		if (h[l]>=x) break;
		h[pos]=h[l];
		b[num[l]]=pos;
		num[pos]=num[l];
		pos=l;
	}
	h[pos]=x;
	b[nm]=pos;
	num[pos]=nm;
}

inline void heap::setval(int pos,int v){
	++pos;
	int& tmp=h[b[pos]];
	if (tmp==v) return;
	tmp=v;
	up(b[pos]);
	down(b[pos]);
}

inline int heap::getmin(){
	return h[1];
}

inline int heap::getval(int pos){
	return h[b[pos+1]];
}

const ld Tmax=10;
const ld Tmin=0.1;
const ld DT=Tmin/Tmax;
const ld eps=1e-09;
int betw;
int clusters;

ld TL,start;
ld T;

inline ld gettime(){
    return (clock()-start)/CLOCKS_PER_SEC;
}

int w[2000];
int x[2000];
int y[2000];

int bestdx[10000];
int bestdy[10000];
ld bestf;

pair<ld,ld> f;
int dx[10000];
int dy[10000];

heap curf[2000];

int n,k;

inline int dist(int i,int j){
    return sqr(x[i]-dx[j])+sqr(y[i]-dy[j]);
}

inline int random(int l,int r){
    return l+rand()%(r-l+1);
}

inline ld rand01(){
    return ((ld)rand())/RAND_MAX;
}

inline bool checktime(){
    ld tmp=gettime();
    T=Tmax*pow(DT,tmp/TL);
    if (tmp>TL) return false;
    
    #ifdef FDEBUG
        
        static int timer;
        ++timer;
        if (timer==1){
        	cerr.precision(15);
            cerr<<fixed<<"TIME: "<<tmp<<endl;
            cerr<<"TEMPERATURE: "<<T<<endl;
            cerr<<"BESTF: "<<bestf<<endl;
            cerr<<"CURF: ("<<f.first<<" "<<f.second<<")"<<endl;
            cerr<<"CURDx: ";
            copy(dx,dx+k+1,ostream_iterator<int>(cerr," "));
            cerr<<"\n";
            cerr<<"CURDy: ";
            copy(dy,dy+k+1,ostream_iterator<int>(cerr," "));
            cerr<<"\n";
            for (int i=0;i<n;i++){            	
	            copy(curf[i].h+1,curf[i].h+k+2,ostream_iterator<int>(cerr," "));
	            cerr<<"\n";
	        }
            cerr<<endl;
            cerr<<endl;
            timer=0;
        }
    #endif
    
    #ifdef HDEBUG
    
    for (int i=0;i<n;i++)
    	for (int j=1;j<=k+1;j++){
    		cerr<<i<<" "<<j<<endl;
    		assert(lf(j)>curf[i].sz || curf[i].h[lf(j)]>=curf[i].h[j]);
    		assert(rg(j)>curf[i].sz || curf[i].h[rg(j)]>=curf[i].h[j]);
    		assert(curf[i].num[curf[i].b[j]]==j);
    		assert(curf[i].h[curf[i].b[j]]==dist(i,j-1));
    	}
    	
    #endif
    
    return true;
}

void recalc(int j,int nx,int ny){
    if (nx==dx[j] && ny==dy[j])
        return;
    if (nx>1000 || ny>1000)
        return;
    if (nx<-1000 || ny<-1000)
        return;

    for (int i=0;i<n;i++)
        f.second-=w[i]*mysqrt(dist(i,j));
    dx[j]=nx;
    dy[j]=ny;
    f.first=0;
    for (int i=0;i<n;i++){
        curf[i].setval(j,dist(i,j));
        f.first+=w[i]*mysqrt(curf[i].getmin());
        f.second+=w[i]*mysqrt(curf[i].getval(j));
    }
}

int iter;

bool iterate(){
    ++iter;
    if (iter==betw){
        if (!checktime()) return false;
        iter=0;
    }

    int tmp=random(1,k);

    int odx=dx[tmp];
    int ody=dy[tmp];
    pair<ld,ld> of=f;

    recalc(tmp,odx+random(-10,10),ody+random(-10,10));

    ld prob=exp((of.first-f.first)/T);       

    if (abs(of.first-f.first)<eps)
       prob=exp((of.second-f.second)/T);   

    if (f.first<=bestf-eps){
        bestf=f.first;
        memcpy(bestdx,dx,(k+1)*sizeof(int));
        memcpy(bestdy,dy,(k+1)*sizeof(int));
    }

    if (rand01()>prob)
        recalc(tmp,odx,ody);

    return true;
}

inline int myround(ld x){
    return int(x+0.5);
}

int dest[2500];


void init(){
    scanf("%d %d",&n,&k);
    if (k==6)
    	TL=0.35;
   	if (k==14){
   		TL=0.3;
   		betw=100;
   	}
	for (int i=0;i<n;i++){
		scanf("%d %d %d",&x[i],&y[i],&w[i]);
		dest[i]=1<<30;
	}
	dx[0]=dy[0]=0;
	for (int i=0;i<k;i++){
		for (int j=0;j<n;j++)
			dest[j]=min(dest[j],dist(j,i)*w[j]*w[j]);	
		int best=0;
		for (int j=0;j<n;j++)
			if (dest[j]>dest[best])
				best=j;
		dx[i+1]=x[best];
		dy[i+1]=y[best];			
	}
}    

void solve(){
    start=clock();
    init(); 
    
    for (int i=0;i<n;i++){    	
    	curf[i].resize(k+1);
        for(int j=0;j<=k;j++){
            curf[i].setval(j,dist(i,j));
            f.second+=w[i]*mysqrt(curf[i].getval(j));
        }
        f.first+=w[i]*mysqrt(curf[i].getmin());
    }

 
    bestf=f.first;
    memcpy(bestdx,dx,(k+1)*sizeof(int));
    memcpy(bestdy,dy,(k+1)*sizeof(int));
    checktime();
    for (iter=0;iterate(););
  //  cerr<<k<<endl;
    for (int i=1;i<=k;i++)
        printf("%d %d\n",bestdx[i],bestdy[i]);
//    cerr<<bestf<<endl;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	ld start=clock();
  	initsqrt();
    int t;
    scanf("%d",&t);
    if (t!=1)
        betw=400;
    else
        betw=200;              
    
/*  #ifdef LOCAL
    TL=1.0/t;
    betw=100;
  #else*/
    TL=(4.6-(clock()-start)/CLOCKS_PER_SEC)/t;  
//  #endif
    for (int it=0;it<t;++it){
        printf("CASE %d Y\n",it+1);
        solve();
    }      
    return 0;
}