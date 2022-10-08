def gcd(a,b):
    if b==0:
        return a
    elif a==0:
          return b
    else:
        return gcd(b,a%b)
        
line1=input()
t=line1.split()
for test in range(1,int(t[0])+1):
   x=[]
   line=input()
   x=line.split()
   y=[]
   for i in range(1,len(x)):
     y.append(int(x[i]))
   y.sort();
   g=y[1]-y[0]
   for i in range(2,len(y)):
       g=gcd(g,y[i]-y[0])
   tmp=y[0]//g
   if y[0]%g!=0:
       tmp+=1
   y=tmp*g-y[0];
   print("Case #",test,": ",y,sep="")
    