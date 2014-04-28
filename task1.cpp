#include <vector>
#include <string>
#include <ctime>
#include <iostream>
#include <fstream>
class WagFish
{
public:
    int getanswer(const std::string& line1, const std::string& line2){
        std::vector<std::vector<int>> d( line1.length() + 1, std::vector<int> (line2.length(), 0));
        for(int i = 0; i <= line1.length();i++)
            for(int j = 0; j <= line2.length(); j++){
                if (i == 0 && j == 0) d[i][j] = 0;
                else if (i > 0 && j == 0) d[i][j] = i;
                else if (i == 0 && j > 0) d[i][j] = j;
                else if (line1[i - 1] == line2[j - 1]) d[i][j] = d[i - 1][j - 1];
                else d[i][j] = std::min(d[i - 1][j], std::min(d[i][j - 1], d[i - 1][j - 1])) + 1;
        }
        return d[line1.length()][line2.length()];
    }
    
    
    
};

class Hirshberg
{
    void getresult(const std::string& fline, const std::string& sline,
                    int flinefirst, int flinelast, int slinefirst, int slinelast,
                    std::vector<std::string>& list)
    {
        if (slinefirst == slinelast)
        {
            for (int i = flinelast - 1; i >= flinefirst; i--)
            {
                std::string notation = "insert ";
                notation.push_back(fline[i]);
                notation = notation + " to " + std::to_string((int) slinefirst) + " position";
                list.push_back(notation);
            }
        }
        else
            if (flinefirst == flinelast - 1)
            {
                bool flag = false;
                for (int i = slinelast - 1; i >= slinefirst; i--)
                    if (flag || sline[i] != fline[flinefirst])
                    {
                        list.push_back("delete " + std::to_string((int) i) + " symbol");
                    } else if (sline[i] == fline[flinefirst])
                        flag = true;
                
                if (!flag)
                {
                    list.pop_back();
                    list.push_back("change "+std::to_string((int) slinefirst) + " symbol to " + fline[flinefirst]);
                }
            } else
            {
                int slinelen = slinelast - slinefirst + 1;
                int flinelen = flinelast - flinefirst + 1;
                std::vector<int> dpleft(slinelen), dpright(slinelen),
                tmpdpleft(slinelen), tmpdpright(slinelen);
                
                for (int i = 0; i < slinelen; i++)
                    tmpdpleft[i] = dpleft[i] = i;
                
                int midfline = flinelen / 2;
                for (int i = 1; i <= midfline; i++)
                {
                    dpleft[0] = i;
                    for (int j = 1; j < slinelen; j++)
                    {
                        if (fline[flinefirst + i - 1] == sline[slinefirst + j - 1])
                            dpleft[j] = tmpdpleft[j - 1];
                        else dpleft[j] = 1 + std::min(std::min(tmpdpleft[j], tmpdpleft[j - 1]), dpleft[j - 1]);
                    }
                    if (i < midfline)
                        tmpdpleft.swap(dpleft);
                }
                
                for (int i = 0; i < slinelen; i++)
                    tmpdpright[i] = dpright[i] = slinelen - i - 1;
                
                for (int i = flinelen - 1; i > midfline; i--)
                {
                    dpright[slinelen - 1] = flinelen - i;
                    for (int j = slinelen - 2; j >= 0; j--)
                    {
                        if (fline[flinefirst + i - 1] == sline[slinefirst + j])
                            dpright[j] = tmpdpright[j + 1];
                        else dpright[j] = 1 + std::min(std::min(tmpdpright[j], tmpdpright[j + 1]), dpright[j + 1]);
                    }
                    if ( i > midfline+ 1)
                        tmpdpright.swap(dpright);
                }
                
                int min = slinelen + flinelen;
                int midsline = 0;
                for (int i = 0; i < slinelen; i++)
                    if (dpleft[i] + dpright[i] < min) 
                    {
                        min = dpleft[i] + dpright[i];
                        midsline = i;
                    }
                midsline += slinefirst;
                midfline += flinefirst;
                
                dpleft.clear(); dpright.clear();
                tmpdpleft.clear(); tmpdpright.clear();
                
                getresult(fline, sline, midfline, flinelast, midsline, slinelast, list);
                getresult(fline, sline, flinefirst, midfline, slinefirst, midsline, list);
            }
    }
    
public:
    int getanswer(const std::string& s, const std::string& t, std::vector<std::string>& result)
    {
        result.clear();
        getresult(s, t, 0, s.length(), 0, t.length(), result);
        return result.size();
    }

};

void TestHish_vs_VF()
{
    srand(time(0));
    
    int firstlen = rand() % 100;
    int secondlen = rand() % 100;
    std::string firstline, secondline;
    
    for(int i = 1; i <= firstlen; i++){
        firstline.push_back(rand() % 26 + 65);
    }
    for(int i = 1; i <= secondlen; i++){
        secondline.push_back(rand() % 26 + 65);
    }
    
    WagFish class1;
    Hirshberg class2;
    std::vector<std::string> empty;
    int answer1 = class1.getanswer(firstline, secondline);
    int answer2 = class2.getanswer(firstline, secondline, empty);
    
    if (answer1 != answer2)
        std::cout << "Wrond answer " << answer1 << " and " << answer2;
    else std::cout << "OK";
};

/*void maintest(){
    std::ifstream in1("first.txt");
    std::string firstinputstring;
    while (!in1.eof()) in1 >> firstinputstring;
    in1.close();
    std::ifstream in2("second.txt");
    std::string secondinputstring;
    while(!in2.eof()) in2 >> secondinputstring;
    in2.close();
    std::vector<std::string> result;
    Hirshberg work;
    work.getanswer(firstinputstring, secondinputstring, result);
    for (int i = 0; i < result.size(); i++)
        std::cout << result[i] << '\n';
}
*/

int main()
{
    TestHish_vs_VF();
    maintest();
    return 0;
}

