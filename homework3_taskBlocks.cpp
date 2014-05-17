#include <iostream>
#include <vector>
#include <string>
#include <ctime>

class blocks{
    std::vector<std::vector<char> > info;
    std::vector<std::vector<int> > g;
    std::vector<bool> used;
    std::vector<int> mt;
    int n,k;
    
    bool try_kuhn (int v) {
        if (used[v])
            return false;
        used[v] = true;
        for (int i = 0; i < g[v].size(); i++){
            int to = g[v][i];
            if (mt[to] == -1 || try_kuhn (mt[to])) {
                mt[to] = v;
                return true;
            }
        }
        return false;
    }
    
public:
    std::vector<int> answer;
    bool flag;
    blocks(int k, std::string string):
    info(k, std::vector<char>(6)),
    g(k),
    used(k, false),
    mt(k, -1),
    k(k),
    n(string.length()),
    flag(true),
    answer(n, -1)
    {
        for (int i = 0; i < k; i ++)
            for(int j = 0; j < 6; j++){
                std::cin >> info[i][j];
                for (int z = 0; z < n; z++)
                    if (string[z] == info[i][j])
                        g[z].push_back(i);
            }
    }
    blocks(int k, std::string string, std::vector<std::vector<char> > &info):
    info(info),
    g(k),
    used(k, false),
    mt(k, -1),
    k(k),
    n(string.length()),
    flag(true),
    answer(n, -1)
    {
        for (int i = 0; i < k; i ++)
            for(int j = 0; j < 6; j++){
                for (int z = 0; z < n; z++)
                    if (string[z] == info[i][j])
                        g[z].push_back(i);
            }
    }

    void solve(){
        for (int v = 0; v < n; v++) {
            used.assign (n, false);
            try_kuhn (v);
        }
        for (int i = 0; i < k; i++)
            if (mt[i] >= 0) answer[mt[i]] = i;
        for (int i = 0; i < n; i++)
            if (answer[i] == -1) flag = false;
        if (flag) {
            std::cout << "YES\n";
            for (int i = 0; i < n; i++)
                std::cout << answer[i] + 1 << ' ';
        }
        else std::cout << "NO\n";
    }
    
};









class testblocks{
    int len, num;
    std::vector<bool> used;
    std::vector<std::vector<char> > info;
    std::string testline;
    bool f(int kol){
        bool result = false;
        if (kol > len) return true;
        else{
            for (int i = 0; i < num; i++)
                for(int j = 0; j < 6; j++)
                    if (testline[kol] == info[i][j] && !used[i]){
                        used[i] = true;
                        if (f(kol + 1)) result = true;
                        break;
                    }
            return result;
        }
    }
public:
    void test(){
        srand(time(0));
        len = rand() % (len - 1) + 1;
        num = rand() % num;
        info.assign(num, std::vector<char>(6));
        for (int i = 0; i < len; i++)
            testline.push_back((char) (rand() % 26 + 97));
        for (int i = 0; i < num; i ++)
            for (int j = 0; j < 6; j++)
                info[i][j] = (char) (rand() % 26 + 97);
        std::cout << "String: " << testline << "\n";
        std::cout << "Blocks: " << num << "\n";
        for (int i = 0; i < num; i++){
            for (int j = 0; j < 6; j++)
                std::cout << info[i][j] << ' ';
            std::cout << "\n";
        }
        bool test = true;
        blocks work(num, testline, info);
        std::cout << "Answer\n";
        work.solve();
        std::cout << "\n";
        if (work.flag){
            for (int i = 0; i < len && test; i++){
                test = false;
                for (int j = 0; j < 6 && !test; j++)
                    if (testline[i] == info[work.answer[i]][j]) test = true;
            }
            if (test) std::cout << "Test completed\n";
            else std::cout << "Test failed";
        }
        else{
            if (!f(0)) std::cout << "Test completed\n";
            else std::cout << "Test failed";
        }
    }
    
    
    testblocks(int len, int num):
    len(len),
    num(num),
    used(num, false)
    {}
            
    
};

int main()
{
    testblocks work(5, 10);
    work.test();
     
  /*  int k;
    std::string string;
    std::cin >> k;
    std::cin >> string;
    blocks work(k, string);
    work.solve();
   */
    return 0;
}

