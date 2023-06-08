#include<iostream>
#include<vector>
#include<algorithm>
#include<limits>
#include<conio.h>
template<typename V, typename D = double>
struct edge
{
    V dest;
    D dist;
    edge(V a, D d) : dest(a), dist(d) {}
    bool operator==(edge e)
    {
        if ((this->dest == e.dest) && (this->dist == e.dist))
        {
            return true;
        }
        return false;
    }
};

template<typename V, typename D = double>
struct vertex
{
    std::vector<edge<V, D>> edges;
    V src;
    vertex(V n) : src(n) {}
};

template<typename V, typename D = double>
class Graph
{
private:
    std::vector<vertex<V, D>> graph;

    int index_by_name(V name) {
        for (int i = 0; i < graph.size(); i++)
        {
            if (graph[i].src == name) return i;
        }
        return -1;
    }

public:
    bool has_vertex(const V& v) {
        for (int i = 0; i < graph.size(); i++)
        {
            if (graph[i].src == v) return true;
        }
        return false;
    }

    bool add_vertex(const V& v) {
        if (!has_vertex(v))
        {
            graph.push_back(vertex<V, D>(v));
            return true;
        }
        return false;
    }

    bool remove_vertex(const V& v)
    {
        if (has_vertex(v))
        {
            for (int i = 0; i < graph.size(); i++)
            {
                if (graph[i].src == v) graph.erase(graph.begin() + i);
                else
                {
                    for (int j = 0; j < graph[i].edges.size(); j++)
                    {
                        if (graph[i].edges[j].dest == v) graph[i].edges.erase(graph[i].edges.begin() + j);
                    }
                }
            }
            return true;
        }
        return false;
    }

    std::vector<V> vertices() {
        std::vector<V> res;
        for (int i = 0; i < graph.size(); i++)
        {
            res.push_back(graph[i].src);
        }
        return res;
    }

    bool has_edge(const V src, const V dest) {
        if (has_vertex(src) && has_vertex(dest))
        {
            for (int i = 0; i < graph[index_by_name(src)].edges.size(); i++)
            {
                if (graph[index_by_name(src)].edges[i].dest == dest) return true;
            }
        }
        return false;
    }

    bool has_edge(const V src, const edge<V, D> e) { //c учетом расстояния в edge
        if (has_vertex(src) && has_vertex(e.dest))
        {
            for (int i = 0; i < graph[index_by_name(src)].edges.size(); i++)
            {
                if (graph[index_by_name(src)].edges[i] == e) return true;
            }
        }
        return false;
    }

    bool add_edge(const V v, const V dest, const D& dist)
    {
        if (!has_edge(v, dest))
        {
            graph[index_by_name(v)].edges.push_back(edge<V, D>(dest, dist));
            return true;
        }
        return false;
    }

    bool remove_edge(const V src, const V dest)
    {
        if (has_edge(src, dest)) {
            for (int i = 0; i < graph[index_by_name(src)].edges.size(); i++)
            {
                if (graph[index_by_name(src)].edges[i].dest == dest) graph[index_by_name(src)].edges.erase(graph[index_by_name(src)].edges.begin() + i);
                return true;
            }
        }
        return false;
    }

    bool remove_edge(const V src, const edge<V, D> e) //c учетом расстояния
    {
        if (has_edge(src, e))
        {
            for (int i = 0; i < graph[index_by_name(src)].edges.size(); i++)
            {
                if (graph[index_by_name(src)].edges[i] == e) graph[index_by_name(src)].edges.erase(graph[index_by_name(src)].edges.begin() + i);
                return true;
            }
        }
        return false;
    }

    std::vector<edge<V, D>> edges(const V src)
    {
        std::vector<edge<V, D>> res;
        if (has_vertex(src)){
            for (int i = 0; i < graph[index_by_name(src)].edges.size(); i++) {
                res.push_back(graph[index_by_name(src)].edges[i]);
            }
        }
        return res;
    }

    size_t order() const
    {
        return graph.size();
    }

    size_t degree() {
        std::vector<int> count(graph.size(), 0);
        for (int i = 0; i < graph.size(); i++) {
            for (int j = 0; j < graph[i].edges.size(); j++) {
                count[i]++;
                count[index_by_name(graph[i].edges[j].dest)]++;
            }
        }
        int max = count[0];
        for (int i = 1; i < count.size(); i++) {
            if (max < count[i]) max = count[i];
        }

        return max;
    }

    void print() const
    {
        for (int i = 0; i < graph.size(); i++)
        {
            std::cout << "[" << graph[i].src << "]";
            for (int j = 0; j < graph[i].edges.size(); j++)
            {
                std::cout << "->[" << graph[i].edges[j].dest << "]";
            }
            std::cout << "\n";
        }
    }

    std::vector<V>  walk_2(const V& p, std::vector<bool>& labels) const
    {
        std::vector<V> path;
        vertex<V, D> tmp = find_by_name(p);
        path.push_back(p);
        labels[index_by_name(p)] = true;
        for (int i = 0; i < tmp.edges.size(); i++)
        {
            if (!labels[index_by_name(tmp.edges[i].dest)])
            {
                std::vector<V> path_2 = walk_2(tmp.edges[i].dest, labels);
                for (int j = 0; j < path_2.size(); j++)
                {
                    path.push_back(path_2[j]);
                }
            }
        }
        return path;
    }
    std::vector<V>  walk1(const V& start_vertex) const
    {
        if (!has_vertex(start_vertex)) throw "Error";
        std::vector<V> path;
        std::vector<bool> labels(graph.size(), false);
        V p = start_vertex;
        while (true)
        {
            std::vector<V> path_2 = walk_2(p, labels);
            for (int j = 0; j < path_2.size(); j++)
            {
                path.push_back(path_2[j]);
            }
            bool f = true;
            for (int i = 0; i < graph.size(); i++)
            {
                if (labels[i] == false)
                {
                    p = graph[i].src;
                    f = false;
                    break;
                }
            }
            if (f) break;
        }
        return path;
    }
};

template<typename V, typename D>
Graph<V, D> WorkWithGraph() {
    Graph<V, D> g;
    g.add_vertex(1);
    g.add_vertex(2);
    g.add_edge(1,2,5);
    g.print();
    if (_getch());
    return g;
}

int main() { 
    Graph<int, int> g;
    for (int i = 0; i < 7; i++) {
        g.add_vertex(i);
    }
    for (int i = 0; i < 6; i++) {
        g.add_edge(i, i + 1, i);
    }
    g.print();
    std::cout << std::endl;
    std::cout << g.degree() << "  " << g.order();
    g.edges(1);
    g.remove_edge(1, g.edges(1)[0]);
    g.remove_vertex(6);
    g.print();
    std::cout << std::endl;
    std::vector<int> kk = g.vertices();
    for (int i = 0; i < kk.size(); i++) {
        std::cout << kk[i] << " ";
    }
    /*Graph<int, int> g;
    while (true) {
        system("cls");
        std::cout << "1 - Work with graph" << std::endl;
        std::cout << "2 - " << std::endl;
        std::cout << "3 - " << std::endl;
        std::cout << "4 - " << std::endl;
        std::cout << "5 - " << std::endl;
        std::cout << "6 - " << std::endl;
        std::cout << "7 - " << std::endl;
        std::cout << "8 - " << std::endl;
        std::cout << "0 - Exit the program" << std::endl;
        int ans = _getch();
        system("cls");
        switch (ans) {
        case '1':
            g = WorkWithGraph<int, int>();
            break;
        case '2':
            break;
        case '3':
            std::cout << "\nPress any key to continue..." << std::endl;
            if (_getch());
        case '4':
            std::cout << "\nPress any key to continue..." << std::endl;
            if (_getch());
            break;
        case '5':
            std::cout << "\nPress any key to continue..." << std::endl;
            if (_getch());
            break;
        case '6':
            std::cout << "\nPress any key to continue..." << std::endl;
            if (_getch());
            break;
        case '7':
            std::cout << "\nPress any key to continue..." << std::endl;
            if (_getch());
            break;
        case '8':
            std::cout << "\nPress any key to continue..." << std::endl;
            if (_getch());
            break;
        case '0':
            std::cout << "See you soon :)" << std::endl;
            return 0;
            break;
        default:
            break;
        }
    }*/
}