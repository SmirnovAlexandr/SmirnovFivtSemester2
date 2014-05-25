#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

double len(double x1, double y1, double x2, double y2){
    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}
class DSU
{
    std::vector<int> parent;
    std::vector<int> rank;
    
public:
    DSU(int LEN):rank(LEN, 1)
    {
        parent.resize(LEN);
        for (int i = 0; i < LEN; i++)
            parent[i] = i;
    }
    int Find_set(int node){
        if (parent[node] == node) return node;
        else return parent[node] = Find_set(parent[node]);
    }
    void Union(int a, int b){
        a = Find_set(a);
        b = Find_set(b);
        if (a != b)
        {
            if (rank[a] < rank[b]) std::swap (a,b);
            parent[b] = a;
            if (rank[a] == rank[b]) rank[a]++;
        }
    }
};

class BM{
    const int SIGMA1 = 100;
    const int SIGMA2 = 10;
    const int CENTRES = 100;
    const int CITIES = 100;
    std::pair<double, double> randomtown (int sigma)
    {
        std::pair<double, double>  randomtown;
        double x, y, distance;
        do{
            x = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
            y = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
            distance = x * x + y * y;
        } while (distance > 1.0 || distance == 0);
        
        double tmp = std::sqrt(((-2) * std::log(distance)) / distance);
        randomtown.first = x * tmp * sigma;
        randomtown.second = y * tmp * sigma;
        return randomtown;
    }
public:
    double tester(std::vector<std::pair<double, double> > & vertexes){
        double dist = 0;
        for (int i = 0; i < CENTRES; ++i){
            std::pair<double, double>  new_centre = randomtown(SIGMA1);
            for (size_t j = 0; j < CITIES; ++j){
                std::pair<double, double> new_city = randomtown(SIGMA2);
                new_city.first += new_centre.first;
                new_city.second += new_centre.second;
                vertexes.push_back(new_city);
            }
        }
        for (int i = 1; i < vertexes.size() - 1; i++)
            dist += sqrt((vertexes[i].first - vertexes[i - 1].first) * (vertexes[i].first - vertexes[i - 1].first)
                            + (vertexes[i].second - vertexes[i - 1].second) * (vertexes[i].second - vertexes[i - 1].second));
        dist += sqrt((vertexes[vertexes.size() - 1].first - vertexes[0].first) * (vertexes[vertexes.size() - 1].first - vertexes[0].first)
                     + (vertexes[vertexes.size()].second - vertexes[0].second) * (vertexes[vertexes.size()].second - vertexes[0].second));
        return dist;
    }

    
};

class salesman{
    struct edge{
        int index1, index2;
        double len;
        bool operator<(const edge &b) const{
            return (len < b.len);
        }
    };
    std::vector<edge> edges, answeredges;
    std::vector<std::pair<double, double> > vertexes;
    std::vector<std::vector<int> > graph;
    std::vector<int> answervertexes;
    std::vector<bool> visited;
    DSU dsu;
    int n;
    
    void makeedges(){
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (i != j){
                    edge temp;
                    temp.index1 = i;
                    temp.index2 = j;
                    temp.len = sqrt((vertexes[j].first - vertexes[i].first) * (vertexes[j].first - vertexes[i].first)
                                    + (vertexes[j].second - vertexes[i].second) * (vertexes[j].second - vertexes[i].second));
                    edges.push_back(temp);
                }
    }
    void makegraph(){
        for (int i = 0; i < answeredges.size(); i++){
            graph[answeredges[i].index1].push_back(answeredges[i].index2);
            graph[answeredges[i].index2].push_back(answeredges[i].index1);
        }
    }
    void dfs(int v){
        if (!visited[v]){
            visited[v] = true;
            answervertexes.push_back(v);
            for (int i = 0; i < graph[v].size(); i++)
                dfs(graph[v][i]);
        }
    }
public:
    salesman(int n):
    dsu(n),
    n(n),
    graph(n, std::vector<int> (0)),
    visited(n, false)
    {}
    void readgraph(){
        for (int i = 0; i < n; i++){
            int x, y;
            std::cin >> x >> y;
            vertexes.push_back(std::make_pair(x, y));
        }
    }
    void solve(){
        BM bm;
        double stupid_answer = bm.tester(vertexes);
        makeedges();
        std::sort(edges.begin(),edges.end());
        for (int i = 0; i < edges.size(); i++)
            if (dsu.Find_set(edges[i].index1) != dsu.Find_set(edges[i].index2))
            {
                dsu.Union(edges[i].index1, edges[i].index2);
                answeredges.push_back(edges[i]);
            }
        makegraph();
        dfs(edges[0].index1);
        double ham_path = getanswer();
        std::cout << "Simple path: " << stupid_answer << "\n";
        std::cout << "Hamiltonian path: " << ham_path << "\n";
        if (stupid_answer >= ham_path) std::cout << "It is OK =) \nTest passed\n";
        else std::cout << "So sad =( \nTest didnot pass\n";
        writeanswer();
        
    }
    void writeanswer(){
        for (int i = 0; i < answervertexes.size(); i++)
            std::cout << answervertexes[i] + 1 << ' ';
    }
    double getanswer(){
        double ans = 0;
        for (int i = 1; i < answervertexes.size() - 1; i++)
            ans += len(vertexes[answervertexes[i]].first, vertexes[answervertexes[i]].second, vertexes[answervertexes[i - 1]].first, vertexes[answervertexes[i - 1]].second);
        ans += len(vertexes[answervertexes[answervertexes.size() - 1]].first, vertexes[answervertexes[answervertexes.size() - 1]].second, vertexes[answervertexes[0]].first, vertexes[answervertexes[0]].second);
        return ans;
    }
};

int main()
{
    salesman work(10000);
    work.solve();
    return 0;
}

