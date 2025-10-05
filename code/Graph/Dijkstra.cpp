template<class T>
class Dijkstra { // 0-base, O(mlogn)
    int n;
    vector<vector<pair<int, int>>> G;
    vector<T> weight;
public:
    vector<int> parent; // parent[source] = source
    vector<int> parent_edge; // parent_edge[source] = -1 
    vector<int> has_path;
    vector<T> dis;
    Dijkstra(int _n): n(_n), G(n), parent(n), parent_edge(n), has_path(n), dis(n) {}
    void add_edge(int u, int v, T w) {
        G[u].emplace_back(v, int(weight.size()));
        weight.push_back(w);
    }
    void solve(int source) {
        ranges::fill(dis, std::numeric_limits<T>::max());
        ranges::fill(has_path, 0);
        priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> pq;
        auto relax = [&](int u, T w, int f, int fedge) {
            if (dis[u] > w) {
                dis[u] = w;
                parent[u] = f;
                parent_edge[u] = fedge;
                pq.emplace(w, u);
            }
        };
        relax(source, 0, source, -1);
        while (!pq.empty()) {
            auto [w, u] = pq.top();
            pq.pop();
            if (dis[u] != w) continue;
            has_path[u] = true;
            for (auto [v, e] : G[u])
                relax(v, dis[u] + weight[e], u, e);
        }
    }
    vector<int> path(int target, bool vertex = true) {
        assert(has_path[target]);
        vector<int> res;
        if (vertex) res.push_back(target);
        for (int x = target; parent[x] != x; x = parent[x]) {
            if (vertex) res.push_back(parent[x]);
            else res.push_back(parent_edge[x]);
        }
        ranges::reverse(res);
        return res;
    }
};
