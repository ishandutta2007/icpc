import java.io.*;
import java.util.*;

public class GCDLCM {
	public String possible(int n, String type, int[] A, int[] B, int[] C) {
		int m = A.length;
		int[] useful = new int[m*9];
		char[] str = type.toCharArray();
		{
			int tot = 0;
			for (int i = 0; i < m; ++ i) {
				int x = C[i];
				for (int j = 2; j*j <= x; ++ j) {
					if (x%j == 0) {
						useful[tot++] = j;
						while (x%j == 0) x /= j;
					}
				}
				if (x != 1)
					useful[tot++] = x;
			}
			Arrays.sort(useful,0,tot);
			int p = 1;
			for (int i = 1; i < tot; ++ i) {
				if (useful[i] != useful[p-1])
					useful[p++] = useful[i];
			}
			useful = Arrays.copyOf(useful,p);
		}
		for (int base : useful) {
			int[] count = new int[m];
			for (int i = 0; i < m; ++ i) {
				int x = C[i];
				while (x%base == 0) {
					count[i] ++;
					x /= base;
				}
			}
			TwoSat sat = new TwoSat(m<<1);
			for (int i = 0; i < m; ++ i) {
				for (int j = i+1; j < m; ++ j) {
					if (A[i] == A[j])
						sat.perform(i<<1,j<<1,str[i],str[j],count[i],count[j]);
					if (A[i] == B[j])
						sat.perform(i<<1,j<<1|1,str[i],str[j],count[i],count[j]);
					if (B[i] == A[j])
						sat.perform(i<<1|1,j<<1,str[i],str[j],count[i],count[j]);
					if (B[i] == B[j])
						sat.perform(i<<1|1,j<<1|1,str[i],str[j],count[i],count[j]);
				}
			}
			if (!sat.run()) return "Solution does not exist";
		}
		return "Solution exists";
	}

	class TwoSat {
		ArrayList<Integer>[] edges;
		boolean[] mark;
		int[] stack;
		int top;
		int n;
		TwoSat(int _n) {
			n = _n;
			edges = new ArrayList[n];
			for (int i = 0; i < n; ++ i)
				edges[i] = new ArrayList<Integer>();
			mark = new boolean[n];
			stack = new int[n];
		}
		void perform(int u,int v,char ch_u,char ch_v,int count_u,int count_v) {
			if (ch_u == 'G' && ch_v == 'G') {
				if (count_u != count_v)
					hasContradiction(u,v);
				if (count_u > count_v)
					hasContradiction(u^1,v);
				if (count_u < count_v)
					hasContradiction(u,v^1);
			}
			if (ch_u == 'L' && ch_v == 'L') {
				if (count_u != count_v)
					hasContradiction(u,v);
				if (count_u > count_v) 
					hasContradiction(u,v^1);
				if (count_u < count_v)
					hasContradiction(u^1,v);
			}
			if (ch_u == 'L' && ch_v == 'G') {
				int t;
				t = u; u = v; v = t;
				t = count_u; count_u = count_v; count_v = t;
				char c;
				c = ch_u; ch_u = ch_v; ch_v = c;
			}
			if (ch_u == 'G' && ch_v == 'L') {
				if (count_u != count_v)
					hasContradiction(u,v);
				if (count_u > count_v)
					hasContradiction(u,v^1);
				if (count_u > count_v)
					hasContradiction(u^1,v);
				if (count_u > count_v)
					hasContradiction(u^1,v^1);
			}
		}
		void hasContradiction(int u,int v) {
			edges[u].add(v^1);
			edges[v].add(u^1);
		}
		boolean run() {
			for (int i = 0; i < n; i += 2) {
				if (!mark[i] && !mark[i^1]) {
					top = 0;
					if (!dfs(i)) {
						while (top > 0) mark[stack[--top]] = false;
						if (!dfs(i^1)) return false;
					}
				}
			}
			return true;
		}
		boolean dfs(int u) {
			if (mark[u]) return true;
			if (mark[u^1]) return false;
			stack[top++] = u;
			mark[u] = true;
			for (int v : edges[u]) {
				if (!dfs(v)) return false;
			}
			return true;
		}
	}

	// CUT begin
	public static void main(String[] args){
		System.err.println("GCDLCM (1000 Points)");
		System.err.println();
		HashSet<Integer> cases = new HashSet<Integer>();
		for (int i = 0; i < args.length; ++i) cases.add(Integer.parseInt(args[i]));
		runTest(cases);
	}

	static void runTest(HashSet<Integer> caseSet) {
		int cases = 0, passed = 0;
		while (true) {
			String label = Reader.nextLine();
			if (label == null || !label.startsWith("--"))
				break;

			int n = Integer.parseInt(Reader.nextLine());
			String type = Reader.nextLine();
			int[] A = new int[Integer.parseInt(Reader.nextLine())];
			for (int i = 0; i < A.length; ++i)
				A[i] = Integer.parseInt(Reader.nextLine());
			int[] B = new int[Integer.parseInt(Reader.nextLine())];
			for (int i = 0; i < B.length; ++i)
				B[i] = Integer.parseInt(Reader.nextLine());
			int[] C = new int[Integer.parseInt(Reader.nextLine())];
			for (int i = 0; i < C.length; ++i)
				C[i] = Integer.parseInt(Reader.nextLine());
			Reader.nextLine();
			String __answer = Reader.nextLine();

			cases++;
			if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
				continue;
			System.err.print(String.format("  Testcase #%d ... ", cases - 1));

			if (doTest(n, type, A, B, C, __answer))
				passed++;
		}
		if (caseSet.size() > 0) cases = caseSet.size();
		System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

		int T = (int)(System.currentTimeMillis() / 1000) - 1417530901;
		double PT = T / 60.0, TT = 75.0;
		System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int n, String type, int[] A, int[] B, int[] C, String __expected) {
		type = new String(type);
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		GCDLCM instance = new GCDLCM();
		String __result = "";
		try {
			__result = instance.possible(n, type, A, B, C);
		}
		catch (Throwable e) { exception = e; }
		double elapsed = (System.currentTimeMillis() - startTime) / 1000.0;

		if (exception != null) {
			System.err.println("RUNTIME ERROR!");
			exception.printStackTrace();
			return false;
		}
		else if (__expected.equals(__result)) {
			System.err.println("PASSED! " + String.format("(%.2f seconds)", elapsed));
			return true;
		}
		else {
			System.err.println("FAILED! " + String.format("(%.2f seconds)", elapsed));
			System.err.println("           Expected: " + "\"" + __expected + "\"");
			System.err.println("           Received: " + "\"" + __result + "\"");
			return false;
		}
	}

	static class Reader {
		private static final String dataFileName = "GCDLCM.sample";
		private static BufferedReader reader;

		public static String nextLine() {
			try {
				if (reader == null) {
					reader = new BufferedReader(new InputStreamReader(new FileInputStream(dataFileName)));
				}
				return reader.readLine();
			}
			catch (IOException e) {
				System.err.println("FATAL!! IOException");
				e.printStackTrace();
				System.exit(1);
			}
			return "";
		}
	}
	// CUT end
}
