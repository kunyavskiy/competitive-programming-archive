import java.io.*;
import java.lang.*;
import java.util.*;
import java.math.*;

public class p1036
{


	void solve() throws IOException{
		int n = nextInt(), sum = nextInt();
		if (sum % 2 == 1){
			out.println(0);
			return;
		}
		sum /= 2;
		BigInteger[][] ans = new BigInteger[n+1][sum+1];
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= sum; j++)
				ans[i][j] = BigInteger.ZERO;
		ans[0][0] = BigInteger.ONE;         
		for (int i = 0; i < n; i++)
			for (int j = 0; j <= sum; j++)
				for (int k = 0; k < 10; k++)
					if (j+k <= sum)
						ans[i+1][j+k] = ans[i+1][j+k].add(ans[i][j]);
		out.println(ans[n][sum].multiply(ans[n][sum]));
		return;
	}

	public static void main(String[] args) throws IOException{
		new p1036().run();
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
