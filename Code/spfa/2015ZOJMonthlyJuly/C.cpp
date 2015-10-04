#include <bits/stdc++.h>

std::map<std::string,std::string> map[2];

void init() {
    map[0]["0E"] = "`";
    map[1]["0E"] = "~";
    map[0]["16"] = "1";
    map[1]["16"] = "!";
    map[0]["1E"] = "2";
    map[1]["1E"] = "@";
    map[0]["26"] = "3";
    map[1]["26"] = "#";
    map[0]["23"] = "4";
    map[1]["23"] = "$";
    map[0]["2E"] = "5";
    map[1]["2E"] = "%";
    map[0]["36"] = "6";
    map[1]["36"] = "^";
    map[0]["3D"] = "7";
    map[1]["3D"] = "&";
    map[0]["3E"] = "8";
    map[1]["3E"] = "*";
    map[0]["46"] = "9";
    map[1]["46"] = "(";
    map[0]["22"] = "0";
    map[1]["22"] = ")";
    map[0]["4E"] = "-";
    map[1]["4E"] = "_";
    map[0]["55"] = "=";
    map[1]["55"] = "+";
    map[0]["15"] = "q";
    map[1]["15"] = "Q";
    map[0]["1D"] = "w";
    map[1]["1D"] = "W";
    map[0]["24"] = "e";
    map[1]["24"] = "E";
    map[0]["2C"] = "r";
    map[1]["2C"] = "R";
    map[0]["2D"] = "t";
    map[1]["2D"] = "T";
    map[0]["35"] = "y";
    map[1]["35"] = "Y";
    map[0]["3C"] = "u";
    map[1]["3C"] = "U";
    map[0]["43"] = "i";
    map[1]["43"] = "I";
    map[0]["44"] = "o";
    map[1]["44"] = "O";
    map[0]["4D"] = "p";
    map[1]["4D"] = "P";
    map[0]["54"] = "[";
    map[1]["54"] = "{";
    map[0]["5B"] = "]";
    map[1]["5B"] = "}";
    map[0]["5D"] = "\\";
    map[1]["5D"] = "|";
    map[0]["1C"] = "a";
    map[1]["1C"] = "A";
    map[0]["1B"] = "s";
    map[1]["1B"] = "S";
    map[0]["25"] = "d";
    map[1]["25"] = "D";
    map[0]["2B"] = "f";
    map[1]["2B"] = "F";
    map[0]["33"] = "g";
    map[1]["33"] = "G";
    map[0]["34"] = "h";
    map[1]["34"] = "H";
    map[0]["3B"] = "j";
    map[1]["3B"] = "J";
    map[0]["42"] = "k";
    map[1]["42"] = "K";
    map[0]["4B"] = "l";
    map[1]["4B"] = "L";
    map[0]["4C"] = ";";
    map[1]["4C"] = ":";
    map[0]["52"] = "'";
    map[1]["52"] = "\"";
    map[0]["1A"] = "z";
    map[1]["1A"] = "Z";
    map[0]["45"] = "x";
    map[1]["45"] = "X";
    map[0]["29"] = "c";
    map[1]["29"] = "C";
    map[0]["2A"] = "v";
    map[1]["2A"] = "V";
    map[0]["32"] = "b";
    map[1]["32"] = "B";
    map[0]["31"] = "n";
    map[1]["31"] = "N";
    map[0]["3A"] = "m";
    map[1]["3A"] = "M";
    map[0]["41"] = ",";
    map[1]["41"] = "<";
    map[0]["49"] = ".";
    map[1]["49"] = ">";
    map[0]["4A"] = "/";
    map[1]["4A"] = "?";

}

char str[1000000 + 5];
int n;

bool caps_lock,caps_lock_pressing;
bool l_shift;
bool r_shift;

std::string answer;

void work() {
    n = strlen(str);
    answer.clear();
    caps_lock_pressing = caps_lock = l_shift = r_shift = false;


    for (int i = 0; i < n; i += 2) {
        std::string code(str + i,str + i + 2);
        if (code == "21") {
            answer.push_back(' ');
        } else if (code == "66") {
            if (!answer.empty()) {
                answer.pop_back();
            }
        } else if (code == "0D") {
            answer.push_back('\t');
        } else if (code == "12") {
            l_shift = true;
        } else if (code == "59") {
            r_shift = true;
        } else if (code == "5A") {
            answer.push_back('\n');
        } else if (code == "58") {
            if (caps_lock_pressing == false) {
                caps_lock ^= 1;
                caps_lock_pressing = true;
            }
        } else if (code == "F0") {
            std::string code2(str + i + 2,str + i + 4);
            if (code2 == "12") {
                l_shift = false;
            } else if (code2 == "59") {
                r_shift = false;
            } else if (code2 == "58") {
                caps_lock_pressing = false;
            }
            i += 2;
        } else {
            char c = map[0][code][0];
            if (c >= 'a' && c <= 'z') {
                answer += map[caps_lock ^ (l_shift | r_shift)][code];
            } else {
                answer += map[l_shift | r_shift][code];
            }
        }
    }
    puts(answer.c_str());
}


int main() {
    init();
    /*
    freopen("C.txt","r",stdin);
    freopen("C.key","w",stdout);
    char A[2],B[2],C[3];
    while (scanf("%s%s%s",A,B,C) == 3) {
        printf("map[0][\"%s\"] = \"%s\";\n",C,B);
        printf("map[1][\"%s\"] = \"%s\";\n",C,A);
    }
    return 0;
    */


    while (scanf("%s",str) == 1) {
        work();
    }
}
