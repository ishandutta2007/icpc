import java.io.*;
import java.util.*;

public class ColourHolic {
	public int countSequences(int[] A) {
		prepare();
		Arrays.sort(A);
		int a = A[0],b = A[1],c = A[2],d = A[3];
		long answer = 0;
		if (a == 0 && b == 0) {
			if (c == d) return 2;
			if (c+1 == d || c == d+1) return 1;
			return 0;
		} else if (a == 0) {
			for (int i = 0; i <= b-1; ++ i) {
				for (int j = 0; j <= c-1 && i+j <= d; ++ j) {
					long t = 0;
					if (b-i == c-j) {
						t = 2;
					} else if (b-i+1 == c-j || b-i == c-j+1) {
						t = 1;
					}
					t = t * comb(b-1,i) % MOD * comb(c-1,j) % MOD;
					int x = b-i+c-j;
					int y = d-i-j;
					if (x < y-1) continue;
					t = t * comb(x-y+1+y,y) % MOD;
					answer += t;
					if (answer >= MOD) answer -= MOD;
				}
			}
			return (int)answer;
		} else {
			long[] small = new long[a+b-1];
			for (int i = 0; i <= a-1; ++ i) {
				for (int j = 0; j <= b-1; ++ j) {
					long t = 0;
					if (a-i == b-j) {
						t = 2;
					} else if (a-i+1 == b-j || a-i == b-j+1) {
						t = 1;
					}
					t = t * comb(a-1,i) % MOD * comb(b-1,j) % MOD;
					small[i+j] += t;
					if (small[i+j] >= MOD) small[i+j] -= MOD;
				}
			}
			long[] big = new long[c+d-1];
			for (int i = 0; i <= c-1; ++ i) {
				for (int j = c-i-1; j <= c-i+1; ++ j) {
					if (j <= 0) continue;
					if (j > d) continue;
					int k = d-j;
					long t = 0;
					if (c-i == j) {
						t = 2;
					} else {
						t = 1;
					}
					t = t * comb(c-1,i) % MOD * comb(d-1,k) % MOD;
					big[i+k] += t;
					if (big[i+k] >= MOD) big[i+k] -= MOD;
				}
			}
			return (int)answer;
		}
	}

	long comb(int a,int b) {
		if (a < b) return 0;
		return F[a] * Finv[b] % MOD * Finv[a-b] % MOD;
	}

	void prepare() {
		int n = 200000 + 5;
		F = new long[n];
		Finv = new long[n];
		Inv = new long[n];
		Finv[0] = F[0] = 1;
		Inv[1] = 1;
		for (int i = 2; i < n; ++ i) {
			Inv[i] = (MOD-MOD/i) * Inv[MOD%i] % MOD;
		}
		for (int i = 1; i < n; ++ i) {
			F[i] = F[i-1] * i % MOD;
			Finv[i] = Finv[i-1] * Inv[i] % MOD;
		}
	}

	long[] F,Finv,Inv;
	final int MOD = (int)1e9+9;

	void debug(Object... o) {
		System.err.println(Arrays.deepToString(o));
	}

	// CUT begin
	public static void main(String[] args){
		System.err.println("ColourHolic (1000 Points)");
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

			int[] n = new int[Integer.parseInt(Reader.nextLine())];
			for (int i = 0; i < n.length; ++i)
				n[i] = Integer.parseInt(Reader.nextLine());
			Reader.nextLine();
			int __answer = Integer.parseInt(Reader.nextLine());

			cases++;
			if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
				continue;
			System.err.print(String.format("  Testcase #%d ... ", cases - 1));

			if (doTest(n, __answer))
				passed++;
		}
		if (caseSet.size() > 0) cases = caseSet.size();
		System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

		int T = (int)(System.currentTimeMillis() / 1000) - 1417349601;
		double PT = T / 60.0, TT = 75.0;
		System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int[] n, int __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		ColourHolic instance = new ColourHolic();
		int __result = 0;
		try {
			__result = instance.countSequences(n);
		}
		catch (Throwable e) { exception = e; }
		double elapsed = (System.currentTimeMillis() - startTime) / 1000.0;

		if (exception != null) {
			System.err.println("RUNTIME ERROR!");
			exception.printStackTrace();
			return false;
		}
		else if (__result == __expected) {
			System.err.println("PASSED! " + String.format("(%.2f seconds)", elapsed));
			return true;
		}
		else {
			System.err.println("FAILED! " + String.format("(%.2f seconds)", elapsed));
			System.err.println("           Expected: " + __expected);
			System.err.println("           Received: " + __result);
			return false;
		}
	}

	static class Reader {
		private static final String dataFileName = "ColourHolic.sample";
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
