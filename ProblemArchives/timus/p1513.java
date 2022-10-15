import java.io.*;
import java.lang.*;
import java.util.*;
import java.math.*;

public class p1513
{

    void solve() throws IOException{
        int n = nextInt(),k = nextInt()+2;
        BigInteger[] x = new BigInteger[n+2];
        BigInteger[] sum = new BigInteger[n+2];


        x[0] = sum[0] =  BigInteger.ONE;
        for (int i = 1; i <= n+1; i++){
            x[i] = sum[i-1];
            if (i >= k)
                x[i] = x[i].subtract(sum[i-k]);
            sum[i] = sum[i-1].add(x[i]);
            //System.err.println(x[i]);
        }

        out.println(x[n+1]);
    }

    public static void main(String[] args) throws IOException{
        new p1513().run();
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
