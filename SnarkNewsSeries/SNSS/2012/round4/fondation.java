import java.io.*;
import java.lang.*;
import java.util.*;
import java.math.*;

public class Main
{

    BigInteger F(int n){
        BigInteger res = BigInteger.ONE;
        for (int i = 1; i <= n; i++)
            res = res.multiply(BigInteger.valueOf(i));
        return res; 
    }

    BigInteger C(int n,int k){
        return F(n).divide(F(k)).divide(F(n-k));
    }


    void solve() throws IOException{
        int n = nextInt(), m = nextInt(), a = nextInt(), b = nextInt();

        out.println(C(n,a).multiply(C(m,b)));
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
            in.close();
            out.close();
        } catch (Exception e) {
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
        return tokenizer.nextToken();
    }

}                                    
