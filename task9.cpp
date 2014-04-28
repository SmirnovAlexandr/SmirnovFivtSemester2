#include <iostream>
#include <vector>
#include <ctime>
class Graph{
    int n;
    std::vector<std::vector<int>> matrix;
    std::vector<int> answer;
    std::vector<int> deqin,deqout;
    bool flag = true;
    
    void FindEulerCycle(int v){
        while (matrix[v].size() > 0){
            int finish = matrix[v][matrix[v].size() - 1];
            matrix[v].pop_back();
            FindEulerCycle(finish);
            answer.push_back(v);
        }
    }
public:
    Graph (int numbersofelements):
    matrix(numbersofelements,std::vector<int>(0)),
    deqin(numbersofelements, 0),
    deqout(numbersofelements, 0),
    n(numbersofelements)
    {}
    void readgraph(int m){
        for(int i = 0; i < m; i++){
            int a,b;
            std::cin >> a >> b;
            matrix[a].push_back(b);
            deqin[b]++;
            deqout[a]++;
        }
    }
    void FindEulerPath(){
        for (int i = 1; i <= n && flag; i++)
            if (deqout[i] != deqin[i]) flag = false;
        if (flag){
            int i = 1;
            while (deqout[i] == 0 && i <= n)  i++;
            if (i <= n)
                FindEulerCycle(i);
            if (i > n) flag = false;
        }
    }
    void writeEulerCycle(){
        if (flag) {
            std::cout << "Yes\n";
            for (int i = 0; i < answer.size(); i++)
                std::cout << answer[i] << ' ';
        }
        else std::cout << "No";
    }
};

int main()
{
    int n,m;
    std::cin >> n >> m;
    Graph graph(n + 1);
    graph.readgraph(m);
    graph.FindEulerPath();
    graph.writeEulerCycle();
    return 0;
}

