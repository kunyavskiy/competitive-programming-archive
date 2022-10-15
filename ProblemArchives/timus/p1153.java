import java.io.*;
import java.lang.*;
import java.util.*;
import java.math.*;

public class p1153
{
    BigInteger sqrt(BigInteger x){
        BigInteger l = BigInteger.ONE;
        BigInteger r = BigInteger.valueOf(2).pow(x.bitLength()/2+3);
        while (r.subtract(l).compareTo(BigInteger.ONE) != 0){
            BigInteger mid = l.add(r).divide(BigInteger.valueOf(2));
            if (mid.multiply(mid).compareTo(x) <= 0)
                l = mid;
            else
                r = mid;
        }
        return l;
    }

    void solve() throws IOException{
        BigInteger x = new BigInteger(nextToken());
        x = x.multiply(BigInteger.valueOf(8)).add(BigInteger.ONE);
        x = sqrt(x).subtract(BigInteger.ONE).divide(BigInteger.valueOf(2));
        out.println(x);        
    }

    public static void main(String[] args) throws IOException{
        new p1153().run();
    }

    BufferedReader in;
    StringTokenizer tokenizer;
    PrintWriter out;

    public void run() throws IOException
    {
        try {                               
            boolean oj = System.getProperty("ONLINE_JUDGE") != null;
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
