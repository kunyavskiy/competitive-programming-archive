import java.io.*;
import java.lang.*;
import java.util.*;
import java.math.*;

public class p1222
{

	BigInteger max(BigInteger a,BigInteger b){
		if (a.compareTo(b) >= 0)	
			return a;
		return b;
	}

	void solve() throws IOException{
		int n = nextInt();
		BigInteger[] dp = new BigInteger[n+1];
		dp[0] = BigInteger.ONE;
		for (int i = 1; i <= n; i++){
			dp[i] = BigInteger.ZERO;
			if (i <= 100){
				for (int j = 1; j <= i; j++)
					dp[i] = max(dp[i],dp[i-j].multiply(BigInteger.valueOf(j)));
			}
			else {
				for (int j = 1; j*j <= i; j++)
					dp[i] = max(dp[i],dp[i-j].multiply(BigInteger.valueOf(j)));			
			}
		}
		out.println(dp[n]);
		return;
	}






	public static void main(String[] args) throws IOException{
		new p1222().run();
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
