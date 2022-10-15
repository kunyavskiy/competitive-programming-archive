import java.io.*;
import java.lang.*;
import java.util.*;
import java.math.*;

public class p1402
{

	BigInteger f(int n){
		BigInteger a = BigInteger.ONE;
		for (int i = 1; i <= n; i++)
			a = a.multiply(BigInteger.valueOf(i));
		return a;
	}

	BigInteger c(int n,int k){
		return f(n).divide(f(k).multiply(f(n-k)));
	}


	void solve() throws IOException{
	     int n = nextInt();
	     BigInteger ans = BigInteger.ZERO;
	     for (int i = 2; i <= n; i++)
			ans = ans.add(c(n,i).multiply(f(i)));
		out.println(ans);	
	}






	public static void main(String[] args) throws IOException{
		new p1402().run();
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
