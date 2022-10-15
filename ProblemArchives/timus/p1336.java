import java.io.*;
import java.lang.*;
import java.util.*;
import java.math.*;

public class p1336
{


	void solve() throws IOException{
		long n = nextLong();
		BigInteger a,b;
		a = b = BigInteger.ONE;
		for (long i = 2; i*i <= n; i++){
			while (n % (i*i) == 0){
				n /= (i*i);
				a = a.multiply(BigInteger.valueOf(i));
			}

			if (n % i == 0){
				a = a.multiply(BigInteger.valueOf(i*i));
				b = b.multiply(BigInteger.valueOf(i));
				n /= i;
			}
		}


		a = a.multiply(BigInteger.valueOf(n*n));
		b = b.multiply(BigInteger.valueOf(n));

		out.println(a+"\n"+b);
	}






	public static void main(String[] args) throws IOException{
		new p1336().run();
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
