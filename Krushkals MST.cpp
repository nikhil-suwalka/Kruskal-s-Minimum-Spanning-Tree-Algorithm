//
// Created by Nikhil on 29-01-21.
//

#include <iostream>
#include <vector>

using namespace std;

class Edge {

public:
    int weight, source, destination;

};

void sort(vector<Edge> &edges, int n) {

    Edge temp;
    for (int i = n - 1; i > 0; i--) {
        for (int j = 0; j < i; ++j) {

            if (edges[j].weight > edges[j + 1].weight) {
                temp = edges[j + 1];
                edges[j + 1] = edges[j];
                edges[j] = temp;
            }
        }
    }
}

bool is_cycle(vector<vector<int>> &graphs, int a, int b) {
    int count;
    int a_exists = -1, b_exists = -1;
    for (int i = 0; i < graphs.size(); ++i) {
        count = 0;
        for (int j = 0; j < graphs[i].size(); ++j) {
            if (graphs[i][j] == a) {
                a_exists = i;
                count++;
            } else if (graphs[i][j] == b) {
                b_exists = i;
                count++;
            }

//          Cycle exists (Both exists in same graph)
            if (count == 2)
                return false;
        }
    }

//    None of the element exists
    if (a_exists == -1 and b_exists == -1) {
        vector<int> temp;
        temp.push_back(a);
        temp.push_back(b);
        graphs.push_back(temp);
    } else {
//        Only first exists
        if (a_exists == -1)
            graphs[b_exists].push_back(a);

//        Only second exists
        else if (b_exists == -1)
            graphs[a_exists].push_back(b);

//        Both exists (in different graphs)
        else {
            for (int i = 0; i < graphs[b_exists].size(); ++i) {
                graphs[a_exists].push_back(graphs[b_exists][i]);
            }
            graphs.erase(graphs.begin() + b_exists);
        }
    }
    return true;
}

void print_graphs(const vector<vector<int>> &graphs) {
    for (int i = 0; i < graphs.size(); ++i) {
        for (int j = 0; j < graphs[i].size(); ++j) {
            cout << graphs[i][j] << " ";
        }
        cout << endl;
    }
}

void krushkals(int nodes, int no_edges, vector<Edge> edges) {
    sort(edges, no_edges);
    cout << "Sorted by weights\n";
    cout << "Weight\tSource\tDestination\n";
    for (int i = 0; i < no_edges; ++i) {
        cout << edges[i].weight << "\t\t" << edges[i].source << "\t\t" << edges[i].destination << endl;
    }
    cout << endl;

    vector<vector<int>> graphs;
    int edges_req = nodes - 1, current = 0, total_weight = 0;

    for (int i = 0; current < edges_req; ++i) {
//        print_graphs(graphs);
        if (is_cycle(graphs, edges[i].source, edges[i].destination)) {
            cout << "Edge: " << current + 1 << " added (" << edges[i].source << " <--> " << edges[i].destination << ")"
                 << endl;
            total_weight += edges[i].weight;
            current++;
        } else
            cout << "Edge: " << current + 1 << " skipped (" << edges[i].source << " <--> " << edges[i].destination
                 << ")" << endl;
    }

    cout << "Total weight of Minimum Spanning Tree: " << total_weight;

}


int main() {

    int nodes, no_edges;
    cout << "Enter the number of nodes in the graph" << endl;
    cin >> nodes;
    cout << "Enter the number of edges in the graph" << endl;
    cin >> no_edges;

    vector<Edge> edges;

    for (int i = 0; i < no_edges; i++) {
        cout << "Edge " << i + 1 << ":\nEnter Source and Destination" << endl;
        Edge edge;
        cin >> edge.source >> edge.destination;
        cout << "Enter the weight" << endl;
        cin >> edge.weight;
        edges.push_back(edge);
    }

    krushkals(nodes, no_edges, edges);

}