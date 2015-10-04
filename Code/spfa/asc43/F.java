import java.math.*;
import java.io.*;
import java.util.*;

public class F {
    public static void main(String[] args) {
        new F().run();
    }

    void run() {
        try {
            Scanner in = new Scanner(new File("frequent.in"));
            PrintWriter out = new PrintWriter(new File("frequent.out"));

            prepare();

            while (in.hasNext()) {
                int n = in.nextInt();
                int t = in.nextInt();
                if (n == 0 && t == 0) break;

                BigInteger b = pow(n,2 * t);
                BigInteger a = answer[n - 1][t];
                BigInteger gcd = a.gcd(b);
                a = a.divide(gcd);
                b = b.divide(gcd);
                for (int i = 0; i < n; ++ i) {
                    if (i > 0) out.print(' ');
                    out.print(i + 1);
                }
                out.println('\n' + a.toString() + '/' + b.toString());
                out.flush();
            }
            in.close();
            out.close();
        } catch(Exception e) {

        }
    }

    void prepare() {
        answer = new BigInteger[14][301];
        for (int i = 1; i <= 14; ++ i) {
            solve(i,300);
        }
    }

    BigInteger answer[][];

    BigInteger pow(int a,int b) {
        BigInteger ret = BigInteger.ONE;
        for (int i = 0; i < b; ++ i) {
            ret = ret.multiply(BigInteger.valueOf(a));
        }
        return ret;
    }

    void solve(int n,int t) {
        Status s = new Status(n);
        BigInteger dp[][] = new BigInteger[2][s.tot];
        int tr[][] = new int[s.tot][s.tot];
        {
            for (int j = 0; j < s.tot; ++ j) {
                ArrayList<Integer> cs = s.status[j];
                for (int k = 0; k < cs.size(); ++ k) {
                    for (int r = 0; r < cs.size(); ++ r) {
                        if (k == r) continue;
                        ArrayList<Integer> ns = new ArrayList<Integer>();
                        for (int q = 0; q < cs.size(); ++ q) {
                            if (q != k && q != r) {
                                ns.add((int)cs.get(q));
                            }
                        }
                        ns.add((int)cs.get(k) + (int)cs.get(r));
                        Collections.sort(ns);
                        tr[j][s.get_id(ns)] += (int)cs.get(k) * (int)cs.get(r);
                    }
                }
                tr[j][j] += n;
                for (int k = 0; k < cs.size(); ++ k) {
                    int x = (int)cs.get(k);
                    for (int r = 1; r < x; ++ r) {
                        ArrayList<Integer> ns = new ArrayList<Integer>();
                        for (int q = 0; q < cs.size(); ++ q) {
                            if (q != k) {
                                ns.add((int)cs.get(q));
                            }
                        }
                        ns.add(r);
                        ns.add(x - r);
                        Collections.sort(ns);
                        tr[j][s.get_id(ns)] += x;
                    }
                }
            }
        }
        for (int i = 0; i < 2; ++ i) {
            for (int j = 0; j < s.tot; ++ j) {
                dp[i][j] = BigInteger.ZERO;
            }
        }
        dp[0][0] = BigInteger.ONE;
        for (int i = 0; i < t; ++ i) {
            int cur = i & 1;
            int nex = cur ^ 1;
            answer[n - 1][i] = dp[cur][0];
            for (int j = 0; j < s.tot; ++ j) {
                if (dp[cur][j].equals(BigInteger.ZERO)) continue;
                for (int k = 0; k < s.tot; ++ k) {
                    if (tr[j][k] == 0) continue;
                    dp[nex][k] = dp[nex][k].add(dp[cur][j].multiply(BigInteger.valueOf(tr[j][k])));
                }
                dp[cur][j] = BigInteger.ZERO;
            }
        }
        answer[n - 1][t] = dp[t & 1][0];
    }

    class Status {
        ArrayList[] status;
        int tot;
        HashMap<ArrayList<Integer>,Integer> map;

        Status(int n) {
            tot = 0;
            status = new ArrayList[135];
            int A[] = new int[14];
            int cnt = 0;
            dfs(A,cnt,n,1);
            map = new HashMap<ArrayList<Integer>,Integer>();
            for (int i = 0; i < tot; ++ i) {
                map.put(status[i],i);
            }
        }

        int get_id(ArrayList<Integer> list) {
            return (int)map.get(list);
        }

        void dfs(int A[],int cnt,int left,int now) {
            if (left == 0) {
                ArrayList list = new ArrayList<Integer>();
                for (int i = 0; i < cnt; ++ i) {
                    list.add(A[i]);
                }
                status[tot++] = list;
                return ;
            }
            if (now > left) return ;
            A[cnt++] = now;
            dfs(A,cnt,left - now,now);
            cnt --;
            dfs(A,cnt,left,now + 1);
        }
    }
}

