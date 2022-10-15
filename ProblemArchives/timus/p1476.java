import java.io.*;
import java.lang.*;
import java.util.*;
import java.math.*;

public class p1476
{

    void solve() throws IOException{
       int m = nextInt();
       int n = nextInt();
       int k = nextInt();
       BigInteger[][] dp = new BigInteger[n+1][m+1];

       BigInteger[][] c = new BigInteger[m+1][m+1];

       for (int i = 0; i <= m; i++)
           for (int j = 0; j <= m; j++){
               if (i == 0 && j == 0){
                  c[i][j] = BigInteger.ONE;
                  continue;
               }
               c[i][j] = BigInteger.ZERO;
               if (i != 0) c[i][j] = c[i][j].add(c[i-1][j]);
               if (i != 0 && j != 0) c[i][j] = c[i][j].add(c[i-1][j-1]);
           }


       for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            dp[i][j] = BigInteger.ZERO;

       dp[0][m] = BigInteger.ONE;

       for (int i = 0; i < n; i++)
          for (int j = 0; j <= m; j++){              
            if (dp[i][j].equals(BigInteger.ZERO))
                continue;
            for (int a = 0; a <= m-j && a <= k; a++)
                for (int b = 0; b <= j; b++)
                    dp[i+1][a+b] = dp[i+1][a+b].add(dp[i][j].multiply(c[m-j][a]).multiply(c[j][b]));
          }
       

       BigInteger ans = BigInteger.ZERO;
       for (int i = 0; i <= m; i++){
         ans = ans.add(dp[n][i]);
       }
       out.println(ans);       
    }

    public static void main(String[] args) throws IOException{
        new p1476().run();
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
            while (true);
//            System.exit(1);
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
