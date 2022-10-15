import java.io.*;
import java.lang.*;
import java.util.*;

public class p1021
{
	public static void main(String[] args) throws IOException
	{                                     
		boolean oj = System.getProperty("ONLINE_JUDGE") != null;
		Reader reader = oj ? new InputStreamReader(System.in) : new FileReader("input.txt");
		Writer writer = oj ? new OutputStreamWriter(System.out) : new FileWriter("output.txt");
		Scanner in = new Scanner(new BufferedReader(reader));
		PrintWriter out = new PrintWriter(writer);

		int n = in.nextInt();
		int[] a = new int[n];
		for (int i = 0; i < n; i++)
			a[i] = in.nextInt();		
		int m = in.nextInt();
		int[] b = new int[m];
		for (int i = 0; i < m; i++)
			b[i] = in.nextInt();
		int ptr1 = 0,ptr2 = 0;
		while (true){
			if (ptr1 == n || ptr2 == m)
				break;
			if (a[ptr1] + b[ptr2] == 10000){
				out.println("YES");
				out.flush();
				return;
			}
			if (a[ptr1] + b[ptr2] > 10000)
				ptr2++;
			else
				ptr1++;	
		}
		out.println("NO");
		out.flush();
		return;  
	}
}