#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

const long long kMax = 1LL << 60;

struct Edge {
    int u, v;
    long long c, f;

    Edge (int u, int v, int c = 0, int f = 0): 
        u(u), v(v), c(c), f(f) {}
};

int reverse_e (int i) {
    return i ^ 1;
}

bool BFS (const vector<vector<int>> &e_index, const vector<Edge> &e, int S, int T,
          vector<vector<int>> *layered_network) {
    vector<int>  dist(e_index.size());
    vector<bool> used(e_index.size());
    dist[S] = 0;
    used[S] = true;
    queue<int> q;
    q.push(S);
    while (!q.empty()) {
        int ver = q.front();
        q.pop();
        for (auto i : e_index[ver]) {
            if (e[i].c - e[i].f > 0 && (!used[e[i].v] || dist[e[i].v] > dist[ver] + 1)) {
                dist[e[i].v] = dist[ver] + 1;
                used[e[i].v] = true;
                q.push(e[i].v);
            }
        }
    }
    layered_network->resize(e_index.size());
    for (int i = 0; i < e.size(); ++i) {
        auto edge = e[i];
        if (dist[edge.u] + 1 == dist[edge.v]) {
            (*layered_network)[edge.u].push_back(i);
        }
    }
    return used[T];
}

long long DFS (const vector<vector<int>> &layered_nework,
               vector<Edge> *e, vector<int> *first_to_use,
               int S, int T,
               int ver, long long min_cap = kMax) {
    if (ver == T) {
        return min_cap;
    }
    for (int &i = (*first_to_use)[ver]; i < layered_nework[ver].size(); ++i) {
        auto& edge = (*e)[layered_nework[ver][i]];
        if (edge.c - edge.f == 0) {
            continue;
        }
        long long flow = DFS(layered_nework,
                             e, first_to_use,
                             S, T, 
                             edge.v, std::min(min_cap, edge.c - edge.f));
        if (flow > 0) {
            edge.f += flow;
            (*e)[reverse_e(layered_nework[ver][i])].f -= flow;
            return flow;
        }
    }
    return 0;
}


long long Dinic (const vector<vector<int>> &e_index, vector<Edge> *e,
                 int S, int T) {
    long long flow = 0;
    vector<vector<int>> layered_nework;
    while (BFS(e_index, *e, S, T, &layered_nework)) {
        vector<int> first_to_use(e_index.size());
        long long delta;
        do {
            delta = DFS(layered_nework, e, &first_to_use, S, T, S);
            flow += delta;
        } while (delta);
        layered_nework.clear();
    }
    return flow;
}

void ReadGraph (vector<vector<int>> &e_index, vector<Edge> &e) {
    int n, m;
    scanf("%d%d", &n, &m);
    e_index.resize(n);
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        --u, --v;
        e.push_back(Edge(u, v, c));
        e.push_back(Edge(v, u));
        e_index[u].push_back(2 * i);
        e_index[v].push_back(2 * i + 1);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    vector<vector<int>> e_index;
    vector<Edge> e;
    ReadGraph(e_index, e);
    std::cout << Dinic(e_index, &e, 0, e_index.size() - 1);
}


