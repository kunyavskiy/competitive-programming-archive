#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
 
typedef char sint;
const sint inf=125;
 
int a[101];
 
sint t[2][1000001];
char s[101];
int tmp;
sint tmp2;
sint* swap_tmp;
sint *t1,*t2;
int sum,i,j;
 
int main(void)
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    int n;
    scanf("%s\n%d",s,&n);
    int st=1%n;        
    int cur=0;        
    int sz=strlen(s); 
    sint iswap;        
 
    for (i=0,j=sz-1;i<j;++i,--j){
        iswap=s[i];
        s[i]=s[j];
        s[j]=iswap;
    }
        
    for (i=0;i<sz;++i){
        if (s[i]=='0')
            a[i]=st;
        else{
            a[i]=n-st;      
            if (a[i]==n) a[i]=0;
            cur+=st;
        }
        if (cur>=n)  cur-=n;
        st=st*2;
        if (st>=n) st-=n;       
    }
    
	if (cur==0){
		printf("0\n");
		return 0;
	}
    
    std::sort(a,a+sz);

    for (i=0;i<sz;i++)
    	if ((a[i]+cur)%n==0){
    		printf("1\n");
    		return 0;
    	}
    	
    for (i=0;i<sz;i++)
    	for (j=i+1;j<sz;j++)
	    	if ((a[i]+a[j]+cur)%n==0){
    			printf("2\n");
    			return 0;
	    	}
	    	
	for (i=0;i<sz;i++)
    	for (j=i+1;j<sz;j++)
	    	for (int k=j+1;k<sz;k++)
	    	if ((a[i]+a[j]+a[k]+cur)%n==0){
    			printf("3\n");
    			return 0;
	    	}
    		       
        
    
    for (i=0;i<n;++i)
        t[1][i]=t[0][i]=inf;
    t[0][cur]=0;
    t1=t[0];
    t2=t[1];
    sum=cur+1;
    for ( i=0;i<sz;++i){
        tmp=a[i];
        if (tmp!=0){
                for (j=0;j<sum;++j){
                tmp2=*t1;
                if (t2[tmp]>tmp2+1)
                        t2[tmp]=tmp2+1;
                    if (t2[j]>tmp2)
                        t2[j]=tmp2;
                        *t1=inf;        
                        ++tmp;
                        ++t1;
                        if (tmp>=n) tmp-=n;
            }
            t1-=sum;
            swap_tmp=t1;
            t1=t2;
            t2=swap_tmp;
            sum+=a[i];
            if (sum>=n) sum=n;
        }
    }
    printf("%d\n",(int)t1[0]);              
    return 0;
}