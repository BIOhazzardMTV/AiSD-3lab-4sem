#include<iostream>
#include<vector>

template<typename V, typename D = double>
struct edge {
    V dest;
    D dist;
    edge(V a, D d) : dest(a), dist(d) {}
    bool operator==(edge e) {
        if ((this->dest == e.dest) && (this->dist == e.dist)) {
            return true;
        }
        return false;
    }
};

template<typename V, typename D = double>
struct vertex {
    std::vector<edge<V, D>> edges;  // a.edges({ b,6 }, { c, -5 }, { d, 11 }, { e, -8 })
    V src;
    vertex(V n) : src(n) {}
};

template<typename V, typename D = double>
class Graph {
private:
    std::vector<vertex<V, D>> graph;

    vertex<V, D> find_by_name(const V name) {
        for (int i = 0; i < graph.size(); i++) {
            if (graph[i].src == name) return graph[i];
        }
        return NULL;
    }

    int index_by_name(const V name) {
        for (int i = 0; i < graph.size(); i++) {
            if (graph[i].src == name) return i;
        }
        return -1;
    }

public:
    
    bool has_vertex(const V& v) const {
        for (int i = 0; i < graph.size(); i++) {
            if (graph[i].src == v) return true;
        }
        return false;
    }

    bool add_vertex(const V& v) {
        if (!has_vertex(v)) {
            graph.push_back(vertex<V, D>(v));
            return true;
        }
        return false;
    }

    bool remove_vertex(const V& v) {
        if (has_vertex(v)) {
            for (int i = 0; i < graph.size(); i++) {
                if (graph[i].src == v) graph.erase(i);
                else {
                    for (int j = 0; j < graph[i].edges.size(); j++) {
                        if (graph[i].edges[j].dest == v) graph[i].edges.erase(j);
                    }
                }
            }
            return true;
        }
        return false;
    }

    std::vector<V> vertices() const {
        std::vector<V> res;
        for (int i = 0; i < graph.size(); i++) {
            res.push_back(graph[i].src);
        }
        return res;
    }

    bool has_edge (const V src, const V dest) const {
        if (has_vertex(src) && has_vertex(dest)) {
            vertex<V, D> a = find_by_name(src);
            for (int i = 0; i < a.edges.size(); i++) {
                if (a.edges[i].dest == dest) return true;
            }
        }
        return false;
    }

    bool has_edge (const V src, const edge<V, D> e) { //c учетом расстояния в edge
        if (has_vertex(src) && has_vertex(e.dest)) {
            vertex<V, D> a = find_by_name(src);
            for (int i = 0; i < a.edges.size(); i++) {
                if (a.edges[i] == e) return true;
            }
        }
        return false;
    }

    bool add_edge(const V src, const V dest, const D& dist) {
        if (!has_edge(src, dest)) {
            graph[index_by_name(src)].edges.push_back(edge<V, D>(dest, dist));
            return true;
        }
        return false;
    }

    bool remove_edge(const V src, const V dest) {
        if (has_edge(src, dest)) {
            for (int i = 0; i < graph[index_by_name(src)].edges.size(); i++) {
                if (graph[index_by_name(src)].edges[i].dest == dest) graph[index_by_name(src)].edges.erase(i);
                return true;
            }
        }
        return false;
    }

    bool remove_edge(const V src, const edge<V, D> e) { //c учетом расстояния
        if (has_edge(src, e)) {
            for (int i = 0; i < graph[index_by_name(src)].edges.size(); i++) {
                if (graph[index_by_name(src)].edges[i] == e) graph[index_by_name(src)].edges.erase(i);
                return true;
            }
        }
        return false;
    }

    //получение всех ребер, выходящих из вершины
    std::vector<edge<V, D>> edges(const V src) {
        return find_by_name(src).edges;
    }

    size_t order() const { //порядок
        return graph.size();
    }
    size_t degree() const { //степень

    }
};

int main() {
    vertex<char> k('a');
    k.edges.push_back(edge<char, double>('b', 15));
    return 0;
}