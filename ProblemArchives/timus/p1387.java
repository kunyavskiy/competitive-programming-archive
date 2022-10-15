import java.io.*;
import java.lang.*;
import java.util.*;
import java.math.*;

public class p1387
{

    void solve() throws IOException{
        int n = nextInt();
        BigInteger dp[] = new BigInteger[n+1];
        dp[0] = BigInteger.ZERO;
        dp[1] = BigInteger.ONE;
        for (int i = 2; i <= n; i++){
           dp[i] = BigInteger.ZERO;
           for (int j = 1; j < i; j++){
            BigInteger temp = BigInteger.ZERO;
            for (int d = 1; d <= j; d++)
                if (j % d == 0)
                    temp = temp.add(dp[d].multiply(BigInteger.valueOf(d)));
            dp[i] = dp[i].add(temp.multiply(dp[i-j]));
           }
           assert(dp[i].mod(BigInteger.valueOf(i-1)).intValue() == 0);
           dp[i] = dp[i].divide(BigInteger.valueOf(i-1));
        }
        out.println(dp[n]);
    }

    public static void main(String[] args) throws IOException{
        new p1387().run();
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
