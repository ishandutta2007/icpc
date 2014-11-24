import java.io.*;
import java.util.*;

public class Main {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		PrintWriter out = new PrintWriter(System.out);
		new Solver().solve(1,in,out);
		out.close();
	}
}

class Solver {
	void solve(int ca,Scanner in,PrintWriter out) {
		int n = in.nextInt();
		long cur = 0,cmax = 0,cmin = 0;
		for (int i = 0; i < n; ++ i) {
			int x = in.nextInt();
			if (i==0 || cur-x>cmin) cmin = cur-x;
			if (i==0 || cur+x>cmax) cmax = cur+x;
			if (cmin+x > cur) cur = cmin+x;
			if (cmax-x > cur) cur = cmax-x;
		}
		out.println(cur);
	}
}
