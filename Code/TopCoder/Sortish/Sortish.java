import java.io.*;
import java.util.*;

public class Sortish {
	public long ways(int sortedness, int[] seq) {
		int n = seq.length;
		for (int i = 0; i < n; ++ i) {
			if (seq[i] == 0) continue;
			for (int j = i+1; j < n; ++ j) {
				if (seq[i] == 0) continue;
				if (seq[i] < seq[j])
					sortedness --;
			}
		}
		if (sortedness < 0) return 0;
		
		int[] exist = new int[n+1];
		for (int x : seq)
			exist[x] ++;
		int m = 0;
		int[] miss = new int[exist[0]];
		for (int i = 1; i <= n; ++ i) {
			if (exist[i] == 0) {
				miss[m++] = i;
			}
		}
		int[][] weight = new int[m][m];
		for (int i = 0; i < m; ++ i) {
			for (int j = 0,cnt = 0; j < n; ++ j) {
				if (seq[j] != 0) continue;
				for (int k = 0; k < j; ++ k) {
					if (seq[k]!=0 && seq[k]<miss[i])
						weight[i][cnt] ++;
				}
				for (int k = j+1; k < n; ++ k) {
					if (seq[k]!=0 && miss[i]<seq[k])
						weight[i][cnt] ++;
				}
				cnt ++;
			}
		}

		int[] F = new int[8];
		F[0] = 1;
		for (int i = 1; i < 8; ++ i)
			F[i] = F[i-1]*i;
		int h = m>>1;
		int g = m-h;
		int[] big = new int[F[h]];
		int[] small = new int[F[g]];
		int count_big = 0;
		int count_small = 0;
		long answer = 0;
		int[] permutation_big = new int[F[h]];
		{
			int[] A = new int[h];
			for (int i = 0; i < h; ++ i)
				A[i] = i;
			int tot = 0;
			do {
				int cost = 0;
				for (int i = 0; i < h; ++ i) 
					for (int j = i+1; j < h; ++ j)
						if (A[i] < A[j])
							cost ++;
				permutation_big[tot++] = cost;
			} while (next_permutation(A));
		}
		int[] permutation_small = new int[F[g]];
		{
			int[] A = new int[g];
			for (int i = 0; i < g; ++ i)
				A[i] = i;
			int tot = 0;
			do {
				int cost = 0;
				for (int i = 0; i < g; ++ i)
					for (int j = i+1; j < g; ++ j)
						if (A[i] < A[j])
							cost ++;
				permutation_small[tot++] = cost;
			} while (next_permutation(A));
		}

		for (int s = 0; s < 1<<m; ++ s) {
			if (Integer.bitCount(s) != h) continue;
			int need = sortedness;
			for (int i = 0; i < m; ++ i) {
				if ((s>>i&1) == 0) {
					for (int j = i+1; j < m; ++ j) {
						if ((s>>j&1) == 1) {
							need --;
						}
					}
				}
			}
			if (need < 0) continue;
			count_big = count_small = 0;
			{
				int[] order = new int[h];
				int[] A = new int[h];
				int t = 0;
				for (int i = 0; i < m; ++ i) {
					if ((s>>i&1) == 1)
						order[t++] = i;
				}
				for (int i = 0; i < h; ++ i)
					A[i] = i;
				int tot = 0;
				do {
					int total = 0;
					for (int i = 0; i < h; ++ i) {
						total += weight[i+g][order[A[i]]];
					}
					total += permutation_big[tot++];
					if (total <= need)
						big[count_big++] = total;
				} while (next_permutation(A));
			}
			{
				int[] order = new int[g];
				int[] A = new int[g];
				int t = 0;
				for (int i = 0; i < m; ++ i) {
					if ((s>>i&1) == 0)
						order[t++] = i;
				}
				for (int i = 0; i < g; ++ i)
					A[i] = i;
				int tot = 0;
				do {
					int total = 0;
					for (int i = 0; i < g; ++ i) {
						total += weight[i][order[A[i]]];
					}
					total += permutation_small[tot++];
					if (total <= need)
						small[count_small++] = total;
				} while (next_permutation(A));
			}
			Arrays.sort(big,0,count_big);
			Arrays.sort(small,0,count_small);
			for (int i = 0,j = count_big-1; i<count_small && j>=0; ) {
				int k = i;
				while (k<count_small && small[i]==small[k]) k ++;
				while (j>=0 && big[j]+small[i]>need) j --;
				if (j>=0 && big[j]+small[i]==need) {
					int r = j;
					while (r>=0 && big[j]==big[r]) r --;
					answer += (long)(k-i)*(j-r);
					j = r;
				}
				i = k;
			}
		}
		return answer;
	}

	boolean next_permutation(int[] A) {
		if (A.length == 0) return false;
		int i,j;
		for (i = A.length-2; i>=0 && A[i]>A[i+1]; -- i);
		if (i == -1) return false;
		for (j = i+1; j<A.length && A[i]<A[j]; ++ j);
		int tmp;
		tmp	= A[i];
		A[i] = A[j-1];
		A[j-1] = tmp;
		for (++ i,j = A.length-1; i < j; ++ i, -- j) {
			tmp = A[i];
			A[i] = A[j];
			A[j] = tmp;
		}
		return true;
	}

	void debug(Object... o) {
		System.out.println(Arrays.deepToString(o));
	}

	// CUT begin
	public static void main(String[] args){
		System.err.println("Sortish (1000 Points)");
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

			int sortedness = Integer.parseInt(Reader.nextLine());
			int[] seq = new int[Integer.parseInt(Reader.nextLine())];
			for (int i = 0; i < seq.length; ++i)
				seq[i] = Integer.parseInt(Reader.nextLine());
			Reader.nextLine();
			long __answer = Long.parseLong(Reader.nextLine());

			cases++;
			if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
				continue;
			System.err.print(String.format("  Testcase #%d ... ", cases - 1));

			if (doTest(sortedness, seq, __answer))
				passed++;
		}
		if (caseSet.size() > 0) cases = caseSet.size();
		System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

		int T = (int)(System.currentTimeMillis() / 1000) - 1416983385;
		double PT = T / 60.0, TT = 75.0;
		System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int sortedness, int[] seq, long __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		Sortish instance = new Sortish();
		long __result = 0;
		try {
			__result = instance.ways(sortedness, seq);
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
		private static final String dataFileName = "Sortish.sample";
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
