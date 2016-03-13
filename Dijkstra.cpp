#include "Heap.cpp"

namespace dijkstra {
    struct Edge {
        int to;
        int length;

        Edge () {}

        Edge (int to, int length): to(to), length(length) {}
    };

    void scan(Edge *edge) {
        scanf("%d%d", &edge->length, &edge->to);
    }

    void scan(vector<Edge> *edge_vector) {
        int n;
        scanf("%d", &n);
        edge_vector->resize(n);
        for (auto& edge : *edge_vector) {
            scan(&edge);
        }
    }

    void scan(vector<vector<Edge>> *adjacency_list) {
        int n;
        scanf("%d", &n);
        adjacency_list->resize(n);
        for (auto& v : *adjacency_list) {
            scan(&v);
        }
    }

    struct Pass {
        int dist, to;

        bool operator < (const Pass &other) const {
            if (dist == other.dist) return to < other.to;
            return dist < other.dist;
        }
    };

    void Dijkstra (int start, const vector<vector<Edge>> &edge, vector<int> *min_dist) {
        static const int unreachable = -1;
        int num_of_vertices = static_cast<int>(edge.size());
        auto& dist = *min_dist;

        dist.assign(num_of_vertices, unreachable);
        dist[start] = 0;

        heap::Heap<Pass> gray(num_of_vertices);
        gray.insert({0, start}, start);

        while (!gray.empty()) {
            Pass cur_min = gray.get_min();
            gray.extract_min();

            for (auto& e : edge[cur_min.to]) {
                if (dist[e.to] == unreachable) {
                    dist[e.to] = dist[cur_min.to] + e.length;
                    gray.insert({dist[e.to], e.to}, e.to);
                } else if (dist[e.to] > dist[cur_min.to] + e.length) {
                    dist[e.to] = dist[cur_min.to] + e.length;
                    gray.decrease(e.to, {dist[e.to], e.to});
                }
            }
        }
    }
}
