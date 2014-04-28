#include <iostream>
#include <vector>
#include <set>

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
int main()
{
    int LEN, roads;
    std::cout << "Write numbers of nodes and roads \n";
    
    std::cin >> LEN >> roads;
    std::cout << "Write roads \n";
    DSU dsu(LEN + 1);
    for(int i = 0; i < roads; i++){
        int start,finish;
        std::cin >> start >> finish;
        dsu.Union(start, finish);
    }
    std::cout<<"Write numbers of requests \n";
    int requests;
    std::cin >> requests;
    for (int i = 0; i < requests; i++){
        int start,finish;
        std::cin >> start >> finish;
        if (dsu.Find_set(start) == dsu.Find_set(finish)) std::cout << "Vertices belong to one set \n";
        else std::cout << "Vertices belong to different sets";
    }
    

    return 0;
}

