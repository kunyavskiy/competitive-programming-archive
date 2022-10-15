import java.io.*;
import java.lang.*;
import java.util.*;
import java.math.*;

public class p1206
{

    BigInteger calc(int k){
    	if (k == 0)
    		return BigInteger.ZERO;
    	return BigInteger.valueOf(10+9+8+7+6+5+4+3+2+1).pow(k);
    }

	void solve() throws IOException{
		int k = nextInt();
		BigInteger res = calc(k);
		res = res.subtract(calc(k-1).multiply(BigInteger.valueOf(19)));
		out.println(res);
	}   






	public static void main(String[] args) throws IOException{
		new p1206().run();
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
