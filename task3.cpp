#include <iostream>
#include <vector>

int main()
{
    int n,m;
    int dinamic[1100][1100];
    std::cin >> n;
    std::vector<int> a(n+1);
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    std::cin >> m;
    std::vector<int> b(m+1);
    for (int i = 1; i <= m; i++) std::cin >> b[i];
    for (int i = 0; i <=n; i++)
        for(int j = 0; j <=m; j++) dinamic[i][j] = 0;
    int prev[1100];
    for (int i = 1; i <= n; i++){
        int ind, best;
        ind = best = 0;
        for (int j = 1; j <=m; j++){
            dinamic[i][j] = dinamic[i-1][j];
            if (a[i] == b[j] && dinamic[i-1][j] < best + 1){
                dinamic[i][j] = best + 1;
                prev[j] = ind;
            }
            if (a[i] > b[j] && dinamic[i-1][j] > best){
                best = dinamic[i-1][j];
                ind = j;
            }
        }
    }
    int max = 0;
    for (int j = 1; j <= m; j++)
        if (dinamic[n][j] > max) max = dinamic[n][j];
    
    std::cout << max;
    return 0;
}