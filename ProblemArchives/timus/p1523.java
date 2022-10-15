import java.io.*;
import java.lang.*;
import java.util.*;
import java.math.*;

public class p1523
{


	void solve() throws IOException{
        int n = nextInt(),k = nextInt();
        int[] a = new int[n];
        for (int i = 0; i < n; i++){
            a[i] = nextInt();            
            a[i] = n - a[i];
        }
        BigInteger[] dp = new BigInteger[n];
        for (int i = 0; i < n; i++)
            dp[i] = BigInteger.ONE;
        BigInteger[] fen = new BigInteger[n];

        for (int i = 0; i < k-1; i++){
            for (int j = 0; j < n; j++)
                fen[j] = BigInteger.ZERO;
            for (int j = 0; j < n; j++){
                for (int x = a[j]; x < n; x = (x | (x+1)))
                    fen[x] = fen[x].add(dp[j]);
                dp[j] = BigInteger.ZERO;
                for (int x = a[j]-1; x != -1 ; x = (x & (x+1))-1)
                    dp[j] = dp[j].add(fen[x]);
            }
        }

        BigInteger ans = BigInteger.ZERO;
        for (int i = 0; i < n; i++)
            ans = ans.add(dp[i]);
        out.println(ans.mod(BigInteger.valueOf(1000000000)));
	}

	public static void main(String[] args) throws IOException{
		new p1523().run();
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
