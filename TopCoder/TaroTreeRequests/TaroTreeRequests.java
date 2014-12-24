import java.io.*;
import java.util.*;

public class TaroTreeRequests {
	public long getNumber(int n, int m, int startValue, int maxValue, int maxHeight) {
		curValue = startValue;
		value = new int[n];
		parent = new int[n];
		for (int i = 1; i < n; ++ i) {
			value[i] = genNextRandom() % maxValue;
			parent[i] = Math.max(0,i-1-(genNextRandom()%maxHeight));
		}

		nill = new LinkCutTree(0);
		nill.ch[0] = nill.ch[1] = nill.fa = nill;

		dot = new LinkCutTree[n];
		for (int i = 0; i < n; ++ i) {
			dot[i] = new LinkCutTree(value[i]);
		}
		for (int i = 1; i < n; ++ i) {
			dot[i].fa = dot[parent[i]];
		}

		long ret = 0;
		for (int qcase = 0; qcase < m; ++ qcase) {
			int u = genNextRandom() % n;
			int v = genNextRandom() % n;
			if (u > v) {
				int t = u; u = v; v = t;
			}
			if (u == v) {
				ret --;
			} else {
				dot[v].access();
				dot[u].splay();
				if (dot[u].fa == nill) {
					dot[u].access();
					dot[v].splay();
					ret += dot[v].mx;
				} else {
					dot[parent[u]].access();
					dot[u].splay();
					dot[u].fa = dot[v];
					parent[u] = v;
				}
			}
		}

		return ret;
	}

	int genNextRandom() {
		curValue = (curValue * 1999 + 17) % 1000003;
		return (int)curValue;
	}

	int[] value;
	int[] parent;
	long curValue;
	static LinkCutTree nill;
	LinkCutTree[] dot;

	class LinkCutTree {
		LinkCutTree[] ch;
		LinkCutTree fa;
		int val,mx;

		LinkCutTree(int v) {
			ch = new LinkCutTree[2];
			ch[0] = ch[1] = fa = nill;
			val = mx = v;
		}

		void up() {
			if (this == nill) return ;
			mx = Math.max(Math.max(ch[0].mx,ch[1].mx),val);
		}

		void setc(LinkCutTree p,int c) {
			ch[c] = p;
			p.fa = this;
			up();
		}
		boolean isroot() {
			return fa == nill || fa.ch[0] != this && fa.ch[1] != this;
		}
		int d() {
			return fa.ch[1] == this ? 1 : 0;
		}
		void rot() {
			int c = d(),cc = fa.d();
			LinkCutTree ff = fa.fa;
			fa.setc(ch[c^1],c);
			this.setc(fa,c^1);
			if (ff.ch[cc] == fa) 
				ff.setc(this,cc);
			else
				this.fa = ff;
		}
		LinkCutTree splay() {
			for ( ; !isroot(); rot()) {
				if (!fa.isroot()) {
					if (d() == fa.d())
						fa.rot();
					else
						rot();
				}
			}
			return this;
		}
		LinkCutTree access() {
			LinkCutTree p = this,q = nill;
			while (p != nill) {
				p.splay().setc(q,1);
				q = p;
				p = p.fa;
			}
			return splay();
		}
	}

	void debug(Object... o) {
		System.err.println(Arrays.deepToString(o));
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("TaroTreeRequests (1000 Points)");
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

            int N = Integer.parseInt(Reader.nextLine());
            int M = Integer.parseInt(Reader.nextLine());
            int startValue = Integer.parseInt(Reader.nextLine());
            int maxValue = Integer.parseInt(Reader.nextLine());
            int maxHeight = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            long __answer = Long.parseLong(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(N, M, startValue, maxValue, maxHeight, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1419389186;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int N, int M, int startValue, int maxValue, int maxHeight, long __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		TaroTreeRequests instance = new TaroTreeRequests();
		long __result = 0;
		try {
			__result = instance.getNumber(N, M, startValue, maxValue, maxHeight);
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
        private static final String dataFileName = "TaroTreeRequests.sample";
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
