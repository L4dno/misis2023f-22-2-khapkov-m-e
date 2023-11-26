#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>

std::vector<std::vector<std::pair<int,int>>> graph;
std::vector<long long> d;
std::vector<char> used;
std::vector<int> p;
const long long INF = 1e18;

void Dijkstra_slow() {
    int n = graph.size();
    for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int j = 0; j < n; ++j) {
            if (!used[j] && (v == -1 || d[j] < d[v])) {
                v = j;
            }
        }
        if (d[v] == INF)
            break;
        used[v] = true;

        for (int j = 0; j < graph[v].size(); ++j) {
            int to = graph[v][j].first,
                len = graph[v][j].second;
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
            }
        }
    }
}

std::set<std::pair<int, int>> q;
void Dijkstra_fast(int s) {
    q.insert(std::make_pair(d[s], s));
    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase(q.begin());

        for (int j = 0; j < graph[v].size(); ++j) {
            int to = graph[v][j].first,
                len = graph[v][j].second;
            if (d[v] + len < d[to]) {
                q.erase(std::make_pair(d[to], to));
                d[to] = d[v] + len;
                p[to] = v;
                q.insert(std::make_pair(d[to], to));
            }
        }
    }
}

void GetPath(std::vector<int>& path, const int s, const int t) {
    
    for (int v = t; v != s; v = p[v]) {
        path.push_back(v);
    }
    path.push_back(s);
    std::reverse(path.begin(), path.end());
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie();
    int n, m;
    std::cin >> n >> m;
    graph.resize(n);
    for (int i = 0; i < m; ++i) {
        int s, f, w;
        // edges numbered from 1
        std::cin >> s >> f >> w;
        --s, --f;
        graph[s].push_back(std::make_pair(f, w));
        graph[f].push_back(std::make_pair(s, w));
    }
    const int s = 0;
    d.resize(n);
    std::fill(d.begin(), d.end(), INF);
    d[0] = 0;
    used.resize(n);
    std::fill(used.begin(), used.end(), false);
    p.resize(n);
    Dijkstra_fast(s);
    if (d[n-1]!=INF) {
        std::vector<int> path;
        GetPath(path, s, n - 1);
        for (int i = 0; i < path.size(); ++i) {
            std::cout << path[i] + 1 << " ";
        }
    }
    else {
        std::cout << -1;
    }
    return 0;
}