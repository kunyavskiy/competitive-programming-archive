import java.io.*;
import java.lang.*;
import java.util.*;
import java.math.*;

public class p1012
{


    void solve() throws IOException{

      int n = nextInt(), k = nextInt();

      BigInteger[][] dp = new BigInteger[n+1][2];

      dp[0][0] = BigInteger.ONE;
      dp[0][1] = BigInteger.ZERO;

      for (int i = 1; i <= n; i++){
        dp[i][0] = dp[i-1][0].add(dp[i-1][1]).multiply(BigInteger.valueOf(k-1));
        dp[i][1] = dp[i-1][0];
      } 

      out.println(dp[n][0]);
    }






    public static void main(String[] args) throws IOException{
        new p1012().run();
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
