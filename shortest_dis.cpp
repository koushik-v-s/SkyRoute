#include <iostream>
#include <stack>
#include <string>
#include <limits>
#define INF 10000000
#define MAX_NODES 100
using namespace std;

class Node {
public:
    string airport, airplane;
    int distance, price, halts;
    Node* next;
    Node(string v, string n, int d, int p, int h)
        : airport(v), airplane(n), distance(d), price(p), halts(h), next(nullptr) {}
};

class Graph {
    string nodeNames[MAX_NODES];
    int numNodes;
    Node* adjacencyList[MAX_NODES];

public:
    Graph(int n) : numNodes(n) {
        for (int i = 0; i < numNodes; i++)
            adjacencyList[i] = nullptr;
    }

    int getOrAddIndex(string node) {
        for (int i = 0; i < numNodes; i++)
            if (nodeNames[i] == node)
                return i;

        for (int i = 0; i < numNodes; i++) {
            if (nodeNames[i].empty()) {
                nodeNames[i] = node;
                return i;
            }
        }
        return -1;
    }

    void addEdge(string u, string n, int d, int p, int h, string v) {
        int indexU = getOrAddIndex(u), indexV = getOrAddIndex(v);

        Node* newNode = new Node(v, n, d, p, h);
        newNode->next = adjacencyList[indexU];
        adjacencyList[indexU] = newNode;

        newNode = new Node(u, n, d, p, h);
        newNode->next = adjacencyList[indexV];
        adjacencyList[indexV] = newNode;
    }

    void shortestPath(string start, string end, int weightSelector) {
        int dist[MAX_NODES], prev[MAX_NODES];
        bool visited[MAX_NODES];
        int startIndex = getOrAddIndex(start);
        int endIndex = getOrAddIndex(end);

        for (int i = 0; i < numNodes; i++) {
            dist[i] = INF;
            prev[i] = -1;
            visited[i] = false;
        }
        dist[startIndex] = 0;

        for (int i = 0; i < numNodes - 1; i++) {
            int minDist = INF, minIndex = -1;
            for (int j = 0; j < numNodes; j++) {
                if (!visited[j] && dist[j] < minDist) {
                    minDist = dist[j];
                    minIndex = j;
                }
            }
            if (minIndex == -1) break; 
            visited[minIndex] = true;

            Node* current = adjacencyList[minIndex];
            while (current != nullptr) {
                int v = getOrAddIndex(current->airport);
                int w;
                if (weightSelector == 1) w = current->distance;
                else if (weightSelector == 2) w = current->price;
                else w = current->halts;

                if (!visited[v] && dist[minIndex] != INF && dist[minIndex] + w < dist[v]) {
                    dist[v] = dist[minIndex] + w;
                    prev[v] = minIndex;
                }
                current = current->next;
            }
        }

        if (dist[endIndex] == INF) {
            if (weightSelector == 1) cout << "\nSORRY, DISTANCE NOT FOUND!\n";
            else if (weightSelector == 2) cout << "\nSORRY, PRICE NOT FOUND!\n";
            else cout << "\nSORRY, HALTS NOT FOUND!\n";
        } else {
            if (weightSelector == 1) cout << "\nSHORTEST DISTANCE FROM " << start << " TO " << end << " : ";
            else if (weightSelector == 2) cout << "\nLOWEST PRICE FROM " << start << " TO " << end << " : ";
            else cout << "\nLEAST NUMBER OF HALTS FROM " << start << " TO " << end << " : ";
            printPath(prev, startIndex, endIndex);
        }
    }

    void printPath(int prev[], int start, int end) {
        stack<int> path;
        int current = end;
        while (current != start) {
            path.push(current);
            current = prev[current];
        }
        path.push(start);

        int prevNode = -1;
        while (!path.empty()) {
            int currentNode = path.top();
            path.pop();
            if (prevNode != -1) {
                Node* edge = findEdge(prevNode, currentNode);
                if (edge != nullptr)
                    cout << " -> (" << edge->airplane << "," << edge->distance << " km,$" << edge->price << "," << edge->halts << " halts) -> ";
                else
                    cout << " -> ??? -> ";
            }
            cout << nodeNames[currentNode];
            prevNode = currentNode;
        }
        cout << endl;
    }

    Node* findEdge(int u, int v) {
        Node* current = adjacencyList[u];
        while (current != nullptr) {
            if (getOrAddIndex(current->airport) == v)
                return current;
            current = current->next;
        }
        return nullptr;
    }
};

int main() {
    system("CLS");
    int numNodes, numEdges, d, p, h;
    cout << "\nENTER NUMBER OF AIRPORTS    : ";
    cin >> numNodes;
    cout << "ENTER NUMBER OF CONNECTIONS : ";
    cin >> numEdges;

    Graph graph(numNodes);

    cout << "\nENTER THE DETAILS : " << endl;
    for (int i = 0; i < numEdges; i++) {
        string u, v, n;
        cout << "\n------------------------------------------------" << endl;
        cout << "ENTER BOARDING AIRPORT    : "; cin >> u;
        cout << "ENTER AIRPLANE NAME       : "; cin >> n;
        cout << "ENTER DISTANCE (in kms)   : "; cin >> d;
        cout << "ENTER PRICE (in $)        : "; cin >> p;
        cout << "ENTER NUMBER OF HALTS     : "; cin >> h;
        cout << "ENTER DESTINATION AIRPORT : "; cin >> v;
        cout << "------------------------------------------------" << endl;
        graph.addEdge(u, n, d, p, h, v);
    }

    string start, end;
    cout << "\nENTER BOARDING AIRPORT    : "; cin >> start;
    cout << "ENTER DESTINATION AIRPORT : "; cin >> end;

    graph.shortestPath(start, end, 1); 
    graph.shortestPath(start, end, 2); 
    graph.shortestPath(start, end, 3); 

    cout << endl;
    return 0;
}
