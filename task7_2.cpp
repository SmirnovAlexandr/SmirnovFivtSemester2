#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cstdlib>
#include <cstdio>

class Graph{
    std::vector<std::vector<int> > matrix;
    std::vector<int> visited, tin, fup;
    int time;
    std::set<int> Set;
    
    void dfs(int vertex, int parent = -1){
        visited[vertex] = 1;
        int child = 0;
        tin[vertex] = fup[vertex] = time++;
        for (int i = 0; i < matrix[vertex].size(); i++){
            int to = matrix[vertex][i];
            if (to != parent){
                if (visited[to]) fup[vertex] = std::min(fup[vertex], tin[to]);
                else {
                    dfs(to, vertex);
                    fup[vertex] = std::min(fup[vertex], fup[to]);
                    if (fup[to] >= tin[vertex] && parent != -1)
                        Set.insert(vertex);
                    child++;
                }
            }
        }
        if (parent == -1 && child > 1) Set.insert(vertex);
    }
    
public:
    Graph(int numbersofvertexes):
    matrix(numbersofvertexes, std::vector<int> (0)),
    visited(numbersofvertexes, 0),
    tin(numbersofvertexes, 0),
    fup(numbersofvertexes, 0),
    time(0)
    {}
    
    void readgraph(int m){
        for (int i = 0; i < m; i++){
            int start, finish;
            std::cin >> start >> finish;
            matrix[start].push_back(finish);
            matrix[finish].push_back(start);
        }
    }

    void solve(){
        for (int i = 1; i < matrix.size(); i++)
            if (!visited[i]) dfs(i);
        std::cout << Set.size() << '\n';
        for(int i = 1; i < matrix.size(); i++)
            if (Set.count(i)) std::cout << i << '\n';
    }
};
int main(int argc, const char * argv[])
{
    freopen("points.in", "r", stdin);
    freopen("points.out", "w", stdout);
    int n,m;
    std::cin >> n >> m;
    Graph graph(n + 1);
    graph.readgraph(m);
    graph.solve();
    
    return 0;
}

