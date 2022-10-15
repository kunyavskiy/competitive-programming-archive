import java.io.*;
import java.lang.*;
import java.util.*;

public class p1642
{


	void solve() throws IOException{
		int n = nextInt();
		int x = nextInt();
		int a[] = new int[n];
		for (int i = 0; i < n; i++)
			a[i] = nextInt();
		Arrays.sort(a);
		int left = -1111, right = 1111;
		for (int i: a)
			if (i < 0)
				left = i;  
			else {
				right = i;
				break;
			}
		if (left <= x && x <= right){
			if (x < 0)
				out.println((2*right-x)+" "+(-x));
			else
				out.println(x+" "+(-2*left+x));
		}
		else 
			out.println("Impossible\n");
	}






	public static void main(String[] args) throws IOException{
		new p1642().run();
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
