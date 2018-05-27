#include <ctime>
#include <iostream>
#include <vector>
#include <limits>
#include <limits.h>

using std::cout, std::endl;
using std::vector;
using std::rand, std::srand, std::time;

/******************************
 * Graph class that uses an adjacency 
 * matrix internally
 ******************************/
class Graph {

    private:
        float **adj_matrix;
        int vertices;
        int edges;
        int size;

		float min_dist(float *distances, bool s_set[])
		{
			float min = std::numeric_limits<float>::max(), min_index;
			for (int i = 0; i < this->size; i++) {
				if (distances[i] <= min && s_set[i] == false)
					min = distances[i], min_index = i;
			}

			return min_index;
		}

    public:
        // Class constructor
        Graph(int size)
        {
            this->size = size;
            adj_matrix = new float *[size];
            for (int i = 0; i < size; i++) {
                  adj_matrix[i] = new float[size];
                  for (int j = 0; j < size; j++)
                        adj_matrix[i][j] = 0;
            }

            vertices = size;
            edges = 0;
        }

        // Dijkstras algorithm
        int path(int x, int y)
        {
            // https://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/

            float *distances = new float[this->size];
            bool *s_set = new bool[this->size];

            for (int i = 0; i < this->size; i++) {
                distances[i] = std::numeric_limits<float>::max();
                s_set[i] = false;
            }

            distances[x] = 0;

     		for (int i = 0; i < this->size - 1; i++) {
				int u = this->min_dist(distances, s_set);
				s_set[u] = true;
				for (int v = 0; v < this->size; v++) {
				 if (!s_set[v] && adjacent(u, v) && distances[u] != INT_MAX && distances[u]+this->adj_matrix[u][v] < distances[v])
				    distances[v] = distances[u] + this->adj_matrix[u][v];
                }
		 	}

            distances[x] = 0;
            return distances[y];
        }

        int v()
        {
            return this->vertices;
        }

        int e()
        {
            return this->edges;
        }

        void add_edge(int x, int y)
        {
            if (x < this->size && y < this->size) {
                this->adj_matrix[x][y] = 1;
                this->adj_matrix[y][x] = 1;
                this->edges++;
            }
            return;
        }

        void delete_edge(int x, int y)
        {
            if (x < this->size && y < this->size) {
                this->adj_matrix[x][y] = 0;
                this->adj_matrix[y][x] = 0;
                this->edges--;
            }
            return;
        }

        bool adjacent(int n1, int n2)
        {
            if (n1 < this->size && n2 < this->size)
                return this->adj_matrix[n1][n2] != 0;
            else
                return false;
        }

        void neighbors(int x)
        {
            int res = 0;

            if (x < this->size) {
                for (int i = 0; i < this->size; i++) {
                    if (this->adj_matrix[x][i] != 0) {
                        cout << " " << i;
                        res++;
                    }
                }
                cout << endl;
            }
        }

        void display()
        {
            for (int i = 0; i < this->size; i++) {
                for (int j = 0; j < this->size; j++) {
                    cout << " " << this->adj_matrix[i][j];
                }
                cout << endl;
            }
        }

        int get_edge_value(int x, int y)
        {
            if (x < this->size && y < this->size) {
                return this->adj_matrix[x][y];
            }
        }

        void set_edge_value(int x, int y, float val)
        {
            if (x < this->size && y < this->size) {
                this->adj_matrix[x][y] = val;
            }
        }
};

void run_simulation(const float DENSITY, const float DIST_RANGE[2])
{
    const int NODES = 50;
    Graph graph(NODES);

    // Generate up to NODES edges
    for (int i = 0; i < NODES; i++) {

        for (int j = 0; j < NODES; j++) {
            float r = static_cast<float>(rand() / static_cast<float>(RAND_MAX));
            float d = static_cast<float>(rand() / static_cast<float>(RAND_MAX/10.0));
            if (r < DENSITY) {
                graph.add_edge(i, j);
                graph.set_edge_value(i, j, d);
            }
        }

    }

    int tot = 0, num = 0;
    for (int i = 0; i < NODES; i++) {
        int dist = graph.path(0, i);
        if (dist > 0) {
            tot += dist;
            num++;
        }
    }
    cout << "Average distance: "<< tot / num << endl;

    return;
}

int main(void)
{

    // Seed the programs rand() calls
    srand(time(nullptr));

    // Run the simulations
    const float DIST_RANGE[2]   = {1.0, 10.0};
    run_simulation(0.2, DIST_RANGE);
    run_simulation(0.4, DIST_RANGE);

    return 0;
}
