#include <bits/stdc++.h>
using namespace std;

map<pair<string,string>,bool> mp;

bool equ(string a,string b) {
    if (mp.find(make_pair(a,b)) != mp.end())
        return mp[make_pair(a,b)];
    if (mp.find(make_pair(b,a)) != mp.end())
        return mp[make_pair(b,a)];
    if (a == b)
        return true;
    int n = a.length(),m = b.length();
    if (n == m && n == 1)
        return a == b;
    if (n != m || n % 2 != 0 || n % 2 != 0)
        return false;
    string a1 = a.substr(0,n / 2);
    string a2 = a.substr(n / 2);
    string b1 = b.substr(0,n / 2);
    string b2 = b.substr(n / 2);
    mp[make_pair(a,b)] = (equ(a1,b1) && equ(a2,b2)) || (equ(a1,b2) && equ(a2,b1));
    return mp[make_pair(a,b)];
}

int main() {
    freopen("B_hack.data","r",stdin);
    string s1,s2;
    cin >> s1 >> s2;
    if (equ(s1,s2))
        cout << "YES";
    else 
        cout <<"NO";
    printf("\n%.10f\n",clock() * 1. / CLOCKS_PER_SEC);
    return 0;
}
