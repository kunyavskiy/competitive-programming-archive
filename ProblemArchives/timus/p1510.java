import java.io.*;
import java.lang.*;
import java.util.*;

public class p1510
{


	void solve() throws IOException{
		int n = nextInt();
		int[] x = new int[n];

		for (int i = 0;i < n; i++)
			x[i] = nextInt();

		Arrays.sort(x);

		int st = 0;
		for (int i = 0; i <= n; i++){	
//			System.out.println(i+" "+st);
			if ((i - st)*2 >= n){				
				out.println(x[st]);
				return;
			}
			if (i != n)
				if (x[i] != x[st])
					st = i;				
		}
		assert false;
	}






	public static void main(String[] args) throws IOException{
		new p1510().run();
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
