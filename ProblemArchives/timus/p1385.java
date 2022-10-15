import java.io.*;
import java.lang.*;
import java.util.*;
import java.math.*;

public class p1385
{


	void solve() throws IOException{
		int n = nextInt();
		BigInteger st10 = BigInteger.TEN.pow(n);
		BigInteger ans = BigInteger.ZERO;

		ans = st10.divide(BigInteger.valueOf(5)).subtract(st10.divide(BigInteger.valueOf(10)));
		ans = ans.add(st10.divide(BigInteger.valueOf(2)).subtract(st10.divide(BigInteger.valueOf(10))));
		ans = ans.add(st10.subtract(st10.divide(BigInteger.valueOf(10))));
		//ans = ans.subtract(BigInteger.valueOf(0));
		if (n > 1)
			ans = ans.add(st10.divide(BigInteger.valueOf(4)).subtract(st10.divide(BigInteger.valueOf(10))));			
		if (n > 2)
			ans = ans.add(st10.divide(BigInteger.valueOf(8)).subtract(st10.divide(BigInteger.valueOf(10))));			


		out.println(ans);
	}






	public static void main(String[] args) throws IOException{
		new p1385().run();
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
