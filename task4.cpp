#include <string>
#include <iostream>

std::string dinamic[100][100];

std::string rec(int left, int right, std::string & string){
    if (left < 0 || left >= string.length() || right < 0 || right >= string.length() || left > right) return "";
    if (dinamic[left][right] == ""){
        if (left == right) {
            dinamic[left][right] = string[left];
        }
        else{
            std::string line1 = rec(left, right - 1, string);
            std::string line2 = rec(left + 1, right, string);
            std::string line3 = "";
            if (string[left] == string[right]) line3 = string[left] +rec(left + 1, right - 1, string) + string[right];
            
            if (line1.length() >= line2.length() && line1.length() >= line3.length()) dinamic[left][right] = line1;
            else if (line2.length() >= line1.length() && line2.length() >= line3.length()) dinamic[left][right] = line2;
            else dinamic[left][right] = line3;
        }
    }
    return dinamic[left][right];
}

int main()
{
    std::string string;
    std::cin >> string;
    for (int i = 0; i < string.length(); i++)
        for (int j = 0; j< string.length(); j++)
            dinamic[i][j] = "";
    std::string answer = rec(0, string.length() - 1, string);
    std::cout << answer.length() << '\n';
    std::cout << answer;
    return 0;
}

