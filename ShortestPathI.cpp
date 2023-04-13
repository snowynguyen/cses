// include the necessary libraries
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// define a structure to store an edge
struct Edge {
  int v; // destination node
  int w; // weight of the edge
  Edge(int v, int w) {
    this->v = v;
    this->w = w;
  }
};

// define a structure to store a node in the priority queue
struct Node {
  int u; // current node
  long long d; // distance from the source node
  Node(int u, long long d) {
    this->u = u;
    this->d = d;
  }
};

// define a comparator for the priority queue
struct Compare {
  bool operator()(const Node& a, const Node& b) {
    return a.d > b.d; // compare by distance
  }
};

// define a constant for infinity
const long long INF = 1e18;

// function to read the graph and store it in an adjacency list
vector<vector<Edge>> readGraph(int n, int m) {
  // create an empty adjacency list of size n + 1
  vector<vector<Edge>> adj(n + 1);

  // loop through the edges
  for (int i = 0; i < m; i++) {
    // read the edge information
    int u, v, w;
    cin >> u >> v >> w;

    // add the edge to the adjacency list
    adj[u].push_back(Edge(v, w));
    //adj[v].push_back(Edge(u, w)); // assuming undirected graph
  }

  // return the adjacency list
  return adj;
}

// function to implement Dijkstra algorithm and print the shortest path from node 1 to node n
void dijkstra(vector<vector<Edge>>& adj, int n) {
  // create a priority queue to store the nodes
  priority_queue<Node, vector<Node>, Compare> pq;

  // create a vector to store the distances from node 1
  vector<long long> dist(n + 1, INF);

  // create a vector to store the previous nodes in the shortest path
  vector<int> prev(n + 1, -1);

  // initialize the distance of node 1 to be zero and push it to the queue
  dist[1] = 0;
  pq.push(Node(1, 0LL));

  // loop until the queue is empty or node n is reached
  while (!pq.empty()) {
    // get the node with the minimum distance from the queue
    Node node = pq.top();
    pq.pop();

    // get the current node and distance
    int u = node.u;
    int d = node.d;

    // if the current distance is larger than the stored distance, skip this node
    if (d > dist[u]) continue;

    // loop through the adjacent edges of the current node
    for (Edge edge : adj[u]) {
      // get the destination node and weight of the edge
      int v = edge.v;
      int w = edge.w;

      // relax the edge if possible
      if (dist[v] > dist[u] + w) {
        // update the distance and previous node of v
        dist[v] = dist[u] + w;
        prev[v] = u;

        // push v to the queue with the updated distance
        pq.push(Node(v, dist[v]));
      }
    }
  }

  // check if there is a path from node 1 to node n
  if (dist[n] == INF) {
    // print -1 if no path exists
    cout << -1 << endl;
  } else {
    // create a vector to store the path nodes in reverse order
    vector<int> path;

    // start from node n and trace back using prev vector until node -1 is reached
    int curr = n;
    while (curr != -1) {
      // add curr to the path vector
      path.push_back(curr);

      // move to the previous node in the path
      curr = prev[curr];
    }

    // print the path nodes in reverse order by looping from back to front of the path vector
    for (int i = 1; i <= n; ++i) {
      cout << dist[i] << " ";
    }
    cout << endl;
  }
}

// main function
int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n, m; cin >> n >> m;
  auto graph = readGraph(n, m);
  dijkstra(graph, n);
}