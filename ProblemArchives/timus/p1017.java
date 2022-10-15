import java.io.*;
import java.lang.*;
import java.util.*;
import java.math.*;

public class p1017
{


	void solve() throws IOException{
		int n;
		n = nextInt();
		BigInteger[][] dp = new BigInteger[n+1][n+1];
		for (int i = 0; i < n; i++)
			dp[0][i] = BigInteger.ONE;

		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < n; j++){
				if (j == 0) {
					dp[i][j] = BigInteger.ZERO;
					continue;
				}
				if (i < j)
					dp[i][j] = dp[i][j-1];
				else                    
					dp[i][j] = dp[i][j-1].add(dp[i-j][j-1]);
//				System.out.println(i+" "+j+" "+dp[i][j]);
		   }
		}
	    out.println(dp[n][n-1]);
	}






	public static void main(String[] args) throws IOException{
		new p1017().run();
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
