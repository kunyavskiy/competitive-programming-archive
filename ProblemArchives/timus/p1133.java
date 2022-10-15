import java.io.*;
import java.lang.*;
import java.util.*;
import java.math.*;

public class p1133
{


	void solve() throws IOException{
		int i = nextInt(),fi = nextInt(),j = nextInt(),fj = nextInt(),n = nextInt();
		if (i > j){
			int t = i;
			i = j;
			j = t;
			t = fi;
			fi = fj;
			fj = t;
		}

		BigInteger[] f = new BigInteger[2020];

		f[0] = BigInteger.ZERO;
		f[1] = BigInteger.ONE;

		for (int I = 2; I <= 2010; I++)
			f[I] = f[I-1].add(f[I-2]);


		int fi1 = (BigInteger.valueOf(fj).subtract(f[j-i-1].multiply(BigInteger.valueOf(fi))).divide(f[j-i])).intValue();

		assert BigInteger.valueOf(fj).subtract(f[j-i-1].multiply(BigInteger.valueOf(fi))).mod(f[j-i]).equals(BigInteger.ZERO);

		if (n >= i+1){
			for (int k = i+1; k < n; k++){
				int t = fi;
				fi = fi1;
				fi1 = t+fi1;
		    }
			out.println(fi1);
			return;
		}

		if (n == i){
			out.println(fi);
			return;
		}

		for (int k = i; k >= n; k--){
			int t = fi1;
			fi1 = fi;
			fi = t - fi;
	    }
		out.println(fi1);
		return;		
	}






	public static void main(String[] args) throws IOException{
		new p1133().run();
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
