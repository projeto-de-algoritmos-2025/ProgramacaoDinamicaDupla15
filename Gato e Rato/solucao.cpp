class Solution {
public:
    int catMouseGame(vector<vector<int>>& graph) {
        int N = graph.size();

        vector<vector<vector<int>>> color(N, vector<vector<int>>(N, vector<int>(2, 0)));
        vector<vector<vector<int>>> degree(N, vector<vector<int>>(N, vector<int>(2, 0)));

        for (int m = 0; m < N; m++) {
            for (int c = 0; c < N; c++) {
                degree[m][c][0] = graph[m].size();  
                degree[m][c][1] = graph[c].size();  
                for (int x : graph[c]) {
                    if (x == 0) degree[m][c][1]--;
                }
            }
        }

        queue<array<int, 3>> q;

        for (int c = 0; c < N; c++) {
            for (int t = 0; t < 2; t++) {
                color[0][c][t] = 1;
                q.push({0, c, t});

                if (c != 0) {
                    color[c][c][t] = 2;
                    q.push({c, c, t});
                }
            }
        }

        auto parents = [&](int m, int c, int t) {
            vector<array<int,3>> res;
            if (t == 0) {
                for (int pc : graph[c]) {
                    if (pc == 0) continue;
                    res.push_back({m, pc, 1});
                }
            } else {
                for (int pm : graph[m]) {
                    res.push_back({pm, c, 0});
                }
            }
            return res;
        };

        while (!q.empty()) {
            auto [m, c, t] = q.front();
            q.pop();
            int stateColor = color[m][c][t];

            for (auto &p : parents(m, c, t)) {
                int pm = p[0], pc = p[1], pt = p[2];
                if (color[pm][pc][pt] != 0) continue;

                if ((stateColor == 1 && pt == 0) || (stateColor == 2 && pt == 1)) {
                    color[pm][pc][pt] = stateColor;
                    q.push({pm, pc, pt});
                } else {
                    if (--degree[pm][pc][pt] == 0) {
                        color[pm][pc][pt] = (pt == 0 ? 2 : 1);
                        q.push({pm, pc, pt});
                    }
                }
            }
        }

        return color[1][2][0];
    }
};
