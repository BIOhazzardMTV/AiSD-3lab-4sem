#include<iostream>
#include<vector>
template<typename V, typename Distance = double>
class Graph {
public:
    struct vertex;
    struct edge {
        V dest;
        Distance dist;
        edge(V a, Distance d) : dest(a), dist(d) {}
    }; 

    struct vertex {
        std::vector<edge> edges;  // a.edges({ b,6 }, { c, -5 }, { d, 11 }, { e, -8 })
        V src;
        vertex(V n) : src(n) {}
    };

private:
    std::vector<vertex> graph;
public:
    //проверка-добавление-удаление вершин
    bool has_vertex(const V& v) const {
        for (int i = 0; i < graph.size(); i++) {
            if (graph[i].src == v) return true;
        }
        return false;
    }
    void add_vertex(const V& v) {
        if (!has_vertex(v)) graph.push_back(vertex(v));
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
        }
    }
    std::vector<V> vertices() const;
};

int main() {
    return 0;
}