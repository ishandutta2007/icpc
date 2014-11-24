/* Created Time: Monday, November 25, 2013 PM02:24:40 CST */
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
string a,b,c;
bool right(string &x) {
    for (int i = 0; i < x.length(); i ++) {
        if (x[i]>='a' && x[i]<='z' || x[i]>='0' && x[i]<='9' || x[i]=='<' || x[i]=='>') continue;
        return false;
    }
    return true;
}
bool check() {
    if (a.length()>b.length()) return false;
    int j = 0; 
    for (int i = 0; i < a.length(); i ++) {
        while (j<b.length() && a[i]!=b[j]) j ++;
        if (j==b.length()) return false;
        j ++;
    }
    if (!right(a) || !right(b)) return false;
    return true;
}
int main() {
    int n;
    cin >> n;
    a = "<3";
    for (int i = 0; i < n; i ++) {
        cin >> c;
        a += c;
        a += "<3";
    }
    cin >> b;
    if (check()) cout << "yes" << endl;
    else cout << "no" <<endl;
    return 0;
}
