#include <iostream>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#include <limits>
#include <list>
#include <fstream>
#include <limits.h>

using namespace std;

class Graph {

    private:
        int vertices;
        int edges;
        bool to_rm(const pair<int, float>&p, int rm) { return p.first == rm; }

    public:
        list<pair<int, float>> *adj_list;
        // Class constructor
        Graph(int size) {
            vertices = size;
            adj_list = new list<pair<int, float>>[size];

            edges = 0;
        }
        // From file constructor
        Graph(string const &str)
        {
            ifstream in_file(str);

            in_file >> vertices;
            adj_list = new list<pair<int, float>>[vertices];

            int x, y;
            float cost;
            while (in_file >> x >> y >> cost) {
                // cout << "x: " << x << " y: " << y << " cost: " << cost << endl;
                add_edge(x, y, cost);
            }

            edges = 0;
        }

        int v() const
        {
            return vertices;
        }

        int e()
        {
            return edges;
        }

        void add_edge(int x, int y, float distance)
        {
            adj_list[x].push_back(make_pair(y, distance));
            adj_list[y].push_back(make_pair(x, distance));
            edges++;
            return;
        }

        void delete_edge(int x, int y)
        {
            // TODO
            return;
        }

        bool adjacent(int x, int y)
        {
            list<pair<int, float>>::iterator it;
            for (it = adj_list[x].begin(); it != adj_list[x].end(); ++it) {
                if (it->first == y)
                    return true;
            }

            return false;
        }

        void neighbors(int x)
        {
            return;
        }

        int get_edge_value(int x, int y) const
        {
            list<pair<int, float>>::iterator it;
            for (it = adj_list[x].begin(); it != adj_list[x].end(); ++it) {
                if (it->first == y)
                    return it->second;
            }
        }

        void set_edge_value(int x, int y, float val)
        {
            return;
        }

        void disp()
        {
            for (int i = 0; i < edges; i++) {
                cout << "edge: " << i;
                list<pair<int, float>>::iterator it;
                for (it = adj_list[i].begin(); it != adj_list[i].end(); ++it) {
                    cout << " neighbor: " << it->first << " dist: " << it->second << endl;
                }
            }
        }
};

// MST Class
class MinSpanningTree {

    private:
        set<int> tree;
        const Graph &graph;

    public:
        MinSpanningTree(const Graph &g): graph(g) {}

        // Prims's algorithm
        void gen_tree()
        {
            // https://gigi.nullneuron.net/gigilabs/how-to-use-the-c-stl-priority-queue/
            // https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-using-stl-in-c/
            float tot_cost = 0;
            priority_queue< pair<int, float>, vector<pair<int, float>>, greater<pair<int, float>> > pq;
            int src = 0;
            vector<float> tree(graph.v(), numeric_limits<float>::infinity());
            vector<int> origins(graph.v(), -1);
            vector<bool> in_tree(graph.v(), false);
            pq.push(make_pair(0.0, src));
            tree[src] = 0;

            while (!pq.empty()) {
                int u = pq.top().second;
                pq.pop();
                in_tree[u] = true;

                for (auto it = graph.adj_list[u].begin(); it != graph.adj_list[u].end(); it++) {
                    int v = (*it).first;
                    float weight = (*it).second;
                    if (in_tree[v] == false && tree[v] > weight) {
                        tree[v] = weight;
                        pq.push(make_pair(tree[v], v));
                        origins[v] = u;
                    }
                }
            }

            cout << "************ EDGES ************" << endl;
            for (int i = 1; i < graph.v(); i++) {
				cout << origins[i] << " -> " << i << endl;
				tot_cost += graph.get_edge_value(origins[i], i);
            }
            cout << "MST COST: " << tot_cost << endl;
            return;
        }
};

int main(int argc, char **argv)
{
    // Command line arguments check
    if (argc != 2) {
        cout << "Useage: " << argv[0] << " <data file>" << endl;
        exit(-1);
    }

    // Open the specified data file and generate a graph
    Graph g(argv[1]);
    MinSpanningTree m(g);
    m.gen_tree();
    return 0;
}
