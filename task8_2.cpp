#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <set>

class Graph{
    int time, colors;
    bool flag = true;
    std::vector<int> color, timein, fup;
    std::vector<std::vector<int> > matrix;
    std::stack<int> Stack;
    
public:
    Graph(int numbersoftops, const std::vector<std::vector<int> > & mat):
    color(numbersoftops, 0),
    timein(numbersoftops),
    matrix(mat),
    time(0),
    colors(0),
    fup(numbersoftops)
    {}
    
    void dfs(int top)
    {
        if (timein[top] == 0){
            Stack.push(top);
            fup[top] = timein[top] = ++time;
            for (int j = 0; j < matrix[top].size(); j++)
                if (color[matrix[top][j]] == 0)
                {
                    if (timein[matrix[top][j]] == 0)
                        dfs(matrix[top][j]);
                    fup[top] = std::min(fup[top], fup[matrix[top][j]]);
                }
            if (fup[top] == timein[top])
            {
                int u;
                colors++;
                do {
                    u = Stack.top();
                    color[u] = colors;
                    Stack.pop();
                } while (u != top);
            }
        }
    }
public:
    void solve(){
        std::set<std::pair<int, int> > Set;
        for (int i = 1; i < matrix.size(); i++)
            if (color[i] == 0) dfs(i);
        for (int i = 1; i < matrix.size(); i++){
            for (int j = 0; j < matrix[i].size(); j++)
                if (color[i] != color[matrix[i][j]])
                    Set.insert(std::make_pair(color[i], color[matrix[i][j]]));
            
        }
        std::cout << Set.size();
        
    }
};
int main()
{
    int n,m;
    freopen("condense2.in", "r", stdin);
    freopen("condense2.out", "w", stdout);
    std::cin >> n >> m;
    std::vector<std::vector<int> > d (n + 1, std::vector<int> (0));
    for (int i = 0; i < m; i++){
        int start, finish;
        std::cin >> start >> finish;
        d[start].push_back(finish);
    }
    Graph graph(n + 1, d);
    graph.solve();
    
    
    
    return 0;
}