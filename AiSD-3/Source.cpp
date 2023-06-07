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

    vertex find_by_name(const V name) {
        for (int i = 0; i < graph.size(); i++) {
            if (graph[i].src == name) return graph[i];
        }
        return NULL;
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
            graph.push_back(vertex(v));
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
        vertex a = find_by_name(src);
        if (a && has_vertex(dest)) {
            for (int i = 0; i < a.edges.size(); i++) {
                if (a.edges[i].dest == dest) return true;
            }
        }
        return false;
    }

    bool has_edge (const V src, const edge e) { //c учетом расстояния в edge
        vertex a = find_by_name(src);
        if (a && has_vertex(e.dest)) {
            for (int i = 0; i < a.edges.size(); i++) {
                if ((a.edges[i].dest == e.dest) && a.edges[i].dist == e.dist) return true;
            }
        }
        return false;
    }



};

int main() {
    return 0;
}