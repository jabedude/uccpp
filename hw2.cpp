#include <iostream>
#include <vector>

using std::cout, std::endl;
using std::vector;

class Graph {

    private:
        int **adj_matrix;
        int vertices;
        int edges;
        int size;

    public:
        Graph(int size)
        {
            this->size = size;
            adj_matrix = new int *[size];
            for (int i = 0; i < size; i++) {
                  adj_matrix[i] = new int[size];
                  for (int j = 0; j < size; j++)
                        adj_matrix[i][j] = 0;
            }

            vertices = 0;
            edges = 0;
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

        void set_edge_value(int x, int y, int val)
        {
            if (x < this->size && y < this->size) {
                this->adj_matrix[x][y] = val;
            }
        }
};


int main(void)
{
    Graph g(10);

    g.add_edge(0, 1);
    g.add_edge(9, 1);

    g.display();

    g.neighbors(9);
    g.neighbors(1);

    return 0;
}
