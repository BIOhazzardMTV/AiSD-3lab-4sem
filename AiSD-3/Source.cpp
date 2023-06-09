#include<iostream>
#include<vector>
#include<algorithm>
#include<limits>
#include<conio.h>
template<typename V, typename D>
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

template<typename V, typename D>
struct vertex {
    std::vector<edge<V, D>> edges;
    V src;
    vertex() : src(NULL) {}
    vertex(V n) : src(n) {}
};

template<typename V, typename D = double>
class Graph {
private:
    std::vector<vertex<V, D>> graph;

    int indexByName(V name) {
        for (int i = 0; i < graph.size(); i++) {
            if (graph[i].src == name) return i;
        }
        return -1;
    }

    void walkHelp(V src, std::vector<V>& path, std::vector<bool>& visited) {
        visited[indexByName(src)] = true;
        path.push_back(src);
        std::vector<edge<V, D>> adj;
        for (int i = 0; i < graph[indexByName(src)].edges.size(); i++) {
            adj.push_back(graph[indexByName(src)].edges[i]);
        }
        for (int j = 0; j < adj.size(); j++) {
            if (!visited[indexByName(adj[j].dest)]) walkHelp(adj[j].dest, path, visited);
        }
    }

    D shortestPathHelp(V src, V dest, std::vector<V>& res) {
        std::vector<D> dis(graph.size(), INT_MAX);
        std::vector<int> as(graph.size(), -1);
        dis[indexByName(src)] = 0;
        for (int i = 0; i < graph.size(); i++) {
            bool flag = true;
            for (int j = 0; j < graph.size(); j++) {
                if (dis[j] != INT_MAX) {
                    for (int k = 0; k < graph[j].edges.size(); k++) {
                        if (dis[j] + graph[j].edges[k].dist < dis[indexByName(graph[j].edges[k].dest)]) {
                            dis[indexByName(graph[j].edges[k].dest)] = dis[j] + graph[j].edges[k].dist;
                            flag = false;
                            as[k] = j;
                        }
                    }
                }
                for (int k = 0; k < dis.size(); k++) {
                    std::cout << dis[k] << "  ";
                }
                std::cout << "\n";
            }
            if (i == graph.size() - 1 && !flag) throw "Negative cycle";
            if (flag) break;
        }
        for (V i = dest; i != src; i = graph[as[indexByName(i)]].src) {
            res.push_back(i);
        }
        res.push_back(dest);
        return dis[indexByName(dest)];
    }

public:
    bool hasVertex(const V& v) {
        for (int i = 0; i < graph.size(); i++) {
            if (graph[i].src == v) return true;
        }
        return false;
    }

    bool addVertex(const V& v) {
        if (!hasVertex(v)) {
            graph.push_back(vertex<V, D>(v));
            return true;
        }
        return false;
    }

    bool removeVertex(const V& v)
    {
        if (hasVertex(v)) {
            for (int i = 0; i < graph.size(); i++) {
                if (graph[i].src == v) graph.erase(graph.begin() + i);
                else {
                    for (int j = 0; j < graph[i].edges.size(); j++) {
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
        for (int i = 0; i < graph.size(); i++) {
            res.push_back(graph[i].src);
        }
        return res;
    }

    int allEdges() {
        int count = 0;
        for (int i = 0; i < graph.size(); i++) {
            for (int j = 0; j < graph.size(); j++) {
                if(hasEdge(graph[i].src, graph[j].src)) count++;
            }
        }
        return count;
    }

    bool hasEdge(const V src, const V dest) {
        if (hasVertex(src) && hasVertex(dest)) {
            for (int i = 0; i < graph[indexByName(src)].edges.size(); i++) {
                if (graph[indexByName(src)].edges[i].dest == dest) return true;
            }
        }
        return false;
    }

    bool hasEdge(const V src, const edge<V, D> e) { //c учетом расстояния в edge
        if (hasVertex(src) && hasVertex(e.dest)) {
            for (int i = 0; i < graph[indexByName(src)].edges.size(); i++) {
                if (graph[indexByName(src)].edges[i] == e) return true;
            }
        }
        return false;
    }

    bool addEdge(const V v, const V dest, const D& dist) {
        if (!hasEdge(v, dest)) {
            graph[indexByName(v)].edges.push_back(edge<V, D>(dest, dist));
            return true;
        }
        return false;
    }

    bool removeEdge(const V src, const V dest) {
        if (hasEdge(src, dest)) {
            for (int i = 0; i < graph[indexByName(src)].edges.size(); i++) {
                if (graph[indexByName(src)].edges[i].dest == dest) graph[indexByName(src)].edges.erase(graph[indexByName(src)].edges.begin() + i);
                return true;
            }
        }
        return false;
    }

    bool removeEdge(const V src, const edge<V, D> e) //c учетом расстояния
    {
        if (hasEdge(src, e)) {
            for (int i = 0; i < graph[indexByName(src)].edges.size(); i++) {
                if (graph[indexByName(src)].edges[i] == e) graph[indexByName(src)].edges.erase(graph[indexByName(src)].edges.begin() + i);
                return true;
            }
        }
        return false;
    }

    std::vector<edge<V, D>> edges(const V src) {
        std::vector<edge<V, D>> res;
        if (hasVertex(src)) {
            for (int i = 0; i < graph[indexByName(src)].edges.size(); i++) {
                res.push_back(graph[indexByName(src)].edges[i]);
            }
        }
        return res;
    }

    size_t order() const {
        return graph.size();
    }

    size_t degree() {
        std::vector<int> count(graph.size(), 0);
        for (int i = 0; i < graph.size(); i++) {
            for (int j = 0; j < graph[i].edges.size(); j++) {
                count[i]++;
                count[indexByName(graph[i].edges[j].dest)]++;
            }
        }
        int max = count[0];
        for (int i = 1; i < count.size(); i++) {
            if (max < count[i]) max = count[i];
        }

        return max;
    }

    void print() const {
        for (int i = 0; i < graph.size(); i++) {
            std::cout << "[" << graph[i].src << "]";
            for (int j = 0; j < graph[i].edges.size(); j++) {
                std::cout << "->[" << graph[i].edges[j].dest << "]";
            }
            std::cout << "\n";
        }
    }

    std::pair<std::vector<V>,D> shortestPath(const V src, const V dest) {
        std::vector<V> res;
        D dist = shortestPathHelp(src, dest, res);
        return std::pair<std::vector<V>,D>(res, dist);
    }

    std::vector<V> walk(V src) {
        std::vector<bool> visited;
        for (int i = 0; i < graph.size(); i++) {
            visited.push_back(false);
        }
        std::vector<V> path;
        walkHelp(src, path, visited);
        return path;
    }

};

void IgnoreLine() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template<typename T>
T GetT() {
    while (true) {
        T x{};
        std::cin >> x;
        if (std::cin.fail()) {
            std::cin.clear();
            IgnoreLine();
            system("cls");
            std::cout << "Oops, that input is invalid.  Please try again.\n" << std::endl;
        }
        else {
            IgnoreLine();
            return x;
        }
    }
}

template<typename V,typename D>
void AddVertex(Graph<V,D>& g) {
    std::cout << "Enter the name of vertex: ";
    V name = GetT<V>();
    while (g.hasVertex(name)) {
        std::cout << "\n";
        std::cout << "Oops, that input is invalid.  Please try again: " << std::endl;
        name = GetT<V>();
    }
    g.addVertex(name);
}

template<typename V, typename D>
void DeleteVertex(Graph<V, D>& g) {
    if (g.vertices().size() == 0) {
        std::cout << "Available vertices:" << std::endl;
        for (int i = 0; i < g.vertices().size(); i++) {
            std::cout << g.vertices()[i] << "  ";
        }
        std::cout << "\nEnter the name of vertex: ";
        V name = GetT<V>();
        while (!g.hasVertex(name)) {
            std::cout << "\n";
            std::cout << "Oops, that input is invalid.  Please try again: " << std::endl;
            name = GetT<V>();
        }
        g.removeVertex(name);
    }
}

template<typename V, typename D>
void AddEdge(Graph<V, D>& g) {
    if (g.vertices().size() > 1) {
        std::cout << "Enter the start vertex: ";
        V name1 = GetT<V>();
        while (!g.hasVertex(name1)) {
            std::cout << "\n";
            std::cout << "Oops, that input is invalid.  Please try again: ";
            name1 = GetT<V>();
        }
        std::cout << "Enter the end vertex: ";
        V name2 = GetT<V>();
        while (!g.hasVertex(name2)) {
            std::cout << "\n";
            std::cout << "Oops, that input is invalid.  Please try again: ";
            name2 = GetT<V>();
        }
        std::cout << "Enter the weight of the edge: ";
        D dist = GetT<D>();
        while (dist == 0) {
            std::cout << "\n";
            std::cout << "Oops, that input is invalid.  Please try again: ";
            dist = GetT<D>();
            std::cout << "\n";
        }
        g.addEdge(name1, name2, dist);
    }
    else std::cout << "Your graph is empty." << std::endl;
}

int main() { 
    Graph<char*, int> g;
    while (true) {
        system("cls");
        std::cout << "1 - Add vertex" << std::endl;
        std::cout << "2 - Remove vertex" << std::endl;
        std::cout << "3 - Add edge" << std::endl;
        std::cout << "4 - Remove edge" << std::endl;
        std::cout << "5 - Check for vertex" << std::endl;
        std::cout << "6 - Check for edge" << std::endl;
        std::cout << "7 - Get vertices" << std::endl;
        std::cout << "8 - Get order" << std::endl;
        std::cout << "9 - Get degree" << std::endl;
        std::cout << "10 - Find shortest path between 2 vertices" << std::endl;
        std::cout << "11 - Walk through graph" << std::endl;
        std::cout << "12 - Task" << std::endl;
        std::cout << "0 - Exit the program" << std::endl;
        int ans = GetT<int>();
        system("cls");
        switch (ans) {
        case 1:
            AddVertex(g);
            break;
        case 2:
            DeleteVertex(g);
            break;
        case 3:
            AddEdge(g);
            std::cout << "\nPress any key to continue..." << std::endl;
            if (_getch());
        case 4:
            std::cout << "\nPress any key to continue..." << std::endl;
            if (_getch());
            break;
        case 5:
            std::cout << "\nPress any key to continue..." << std::endl;
            if (_getch());
            break;
        case 6:
            std::cout << "\nPress any key to continue..." << std::endl;
            if (_getch());
            break;
        case 7:
            std::cout << "\nPress any key to continue..." << std::endl;
            if (_getch());
            break;
        case 8:
            std::cout << "\nPress any key to continue..." << std::endl;
            if (_getch());
            break;
        case 9:

            break;
        case 10:

            break;
        case 11:

            break;
        case 12:

            break;
        case 0:
            std::cout << "See you soon :)" << std::endl;
            return 0;
            break;
        default:
            break;
        }
    }
}