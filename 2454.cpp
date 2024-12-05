#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int dfs(vector<vector<int>>& lake, int x, int y, vector<vector<bool>>& visited) {
    if (x < 0 || x >= lake.size() || y < 0 || y >= lake[0].size() || lake[x][y] == 0 || visited[x][y]) {
        return 0;
    }
    
    visited[x][y] = true;
    int fish = lake[x][y];
        // Move in all four possible directions
    fish += dfs(lake, x + 1, y, visited);
    fish += dfs(lake, x - 1, y, visited);
    fish += dfs(lake, x, y + 1, visited);
    fish += dfs(lake, x, y - 1, visited);
    
    return fish;
}

int maxFish(vector<vector<int>>& lake) {
    int m = lake.size();
    int n = lake[0].size();
    int maxFishCaught = 0;
    
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (lake[i][j] > 0 && !visited[i][j]) {
                maxFishCaught = max(maxFishCaught, dfs(lake, i, j, visited));
            }
        }
    }
    
    return maxFishCaught;
}

int main() {
    int m, n;
    cin >> m >> n;
    
    vector<vector<int>> lake(m, vector<int>(n));
    
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> lake[i][j];
        }
    }
    
    cout << maxFish(lake) << endl;
    
    return 0;
}