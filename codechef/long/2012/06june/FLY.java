import java.io.*;
import java.lang.*;
import java.util.*;
import java.math.*;

public class Main
{

    BigDecimal vof(double d){
        return BigDecimal.valueOf(d);
    }

    void solveone() throws IOException{
        int n = nextInt();
        BigDecimal c = new BigDecimal(nextToken());
        int m = nextInt();
        if (m == 0){
            if (c.compareTo(vof(2)) >= 0){
                out.printf(Locale.US,"%.9f\n",vof(n-1).multiply(c).add(vof(n-1).multiply(vof(n-2)).multiply(vof(2))).add(vof(n-1).multiply(vof(2))));
                // (n-1)*c+((n-1)*(n-2)*2)+((n-1)*2)
            }else{
                out.printf(Locale.US,"%.9f\n",vof(n).multiply(vof(n-1)).multiply(vof(1).add(c.divide(vof(2)))));
                // (n*(n-1)*(1+c/2))
            }
            return;
        }
        if (m == 1){
            int a=nextInt(),b=nextInt();
            if (c.compareTo(vof(2)) >= 0){
                out.printf(Locale.US,"%.9f\n",vof(n-1).multiply(c).add(vof(n-1).multiply(vof(n-2)).multiply(vof(2))).add(vof(n-1).multiply(vof(2))).subtract(c));
                //(n-1)*c+(n-1)*(n-2)*2+(n-1)*2-c
            }else{
                out.printf(Locale.US,"%.9f\n",vof(n).multiply(vof(n-1)).multiply(vof(1).add(c.divide(vof(2)))).subtract(c));
                // n*(n-1)*(1+c/2)-c
            }
            return;
        }
        if (m == 2){         
            int a=nextInt(),b=nextInt();
            int _c=nextInt(),d=nextInt();
            if (a == _c || b == d || a == d|| b == _c){
              if (c.compareTo(vof(2)) >= 0){
                 out.printf(Locale.US,"%.9f\n",vof(n-1).multiply(c).add(vof(n-1).multiply(vof(n-2)).multiply(vof(2))).add(vof(n-1).multiply(vof(2))).subtract(vof(2).multiply(c)));
                 // (n-1)*c+(n-1)*(n-2)*2+(n-1)*2 - 2c
              }else{
                 out.printf(Locale.US,"%.9f\n",vof(n).multiply(vof(n-1)).multiply(vof(1).add(c.divide(vof(2)))).subtract(vof(2).multiply(c)));
                 // n*(n-1)*(1+c/2)-2c
              }
            }
            else {
              if (c.compareTo(vof(2)) >= 0){
                 BigDecimal ans1 = vof(n).multiply(c).add(vof(n-1).multiply(vof(n-2)).multiply(vof(2))).add(vof(n-1).multiply(vof(2))).subtract(vof(2));
                 // n*c+(n-1)*(n-2)*2 +(n-1)*2 - 2
                 BigDecimal ans2 = vof(n-1).multiply(c).add(vof(n-2).multiply(vof(n-3)).multiply(vof(2))).add(vof(n-2).multiply(vof(2))).add(vof(6)).add(vof(n-3).multiply(vof(6)));
                 // (n-1)*c+(n-2)*(n-3)*2 + (n-2)*2 + 6 + (n-3)*6;
                 if (ans1.compareTo(ans2) < 0)
                    out.printf(Locale.US,"%.9f\n",ans1.subtract(vof(2).multiply(c)));
                 else
                    out.printf(Locale.US,"%.9f\n",ans2.subtract(vof(2).multiply(c)));
              }else{
                 out.printf(Locale.US,"%.9f\n",vof(n).multiply(vof(n-1)).multiply(vof(1).add(c.divide(vof(2)))).subtract(vof(2).multiply(c)));
              }
            }
            return;
        }
    }

    void solve() throws IOException{
        int t = nextInt();
        while (t > 0){
            solveone();
            t--;
        }
    }

    public static void main(String[] args) throws IOException{
        new Main().run();
    }

    BufferedReader in;
    StringTokenizer tokenizer;
    PrintWriter out;

    public void run() throws IOException
    {
        try {                               
            boolean oj = System.getProperty("LOCAL") == null;
            Reader reader = oj ? new InputStreamReader(System.in) : new FileReader("input.txt");
            Writer writer = oj ? new OutputStreamWriter(System.out) : new FileWriter("output.txt");
            in = new BufferedReader(reader);
            tokenizer = null;
            out = new PrintWriter(writer);
            solve();
            out.close();
        }catch (Exception e) {
            e.printStackTrace();
            System.exit(1);
        }       
    }

    int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }

    long nextLong() throws IOException {
        return Long.parseLong(nextToken());
    }

    double nextDouble() throws IOException {
        return Double.parseDouble(nextToken());
    }

    String nextToken() throws IOException {
        while (tokenizer == null || !tokenizer.hasMoreTokens()) {
            tokenizer = new StringTokenizer(in.readLine());
        }
        assert tokenizer != null;
        return tokenizer.nextToken();
    }

}                                    
