#include <iostream>
#include <stack>
#include <string>
#define INF 10000000
#define MAX_NODES 100
using namespace std;
class Node 
{
public:
    string airport, airplane;
    int distance, price, halts;
    Node* next;
    Node(string v, string n, int d, int p, int h) : airport(v), airplane(n), distance(d), price(p), halts(h), next(NULL) {}
};
class Graph 
{
    string nodeNames[MAX_NODES];
    int nodeIndices[MAX_NODES], reverseNodeIndices[MAX_NODES], numNodes;
    Node* adjacencyList[MAX_NODES];
public:
    Graph(int n) : numNodes(n) 
    {
        // Initialize adjacency list
        for (int i = 0; i < numNodes; i++)
            adjacencyList[i] = NULL;
    }
    int getOrAddIndex(string node) 
    {
        for (int i = 0; i < numNodes; i++) 
        {
            if (nodeNames[i] == node)
                return i;
        }
        for (int i = 0; i < numNodes; i++)
        {
            if (nodeNames[i].empty()) 
            {
                nodeNames[i] = node;
                nodeIndices[i] = i;
                reverseNodeIndices[i] = i;
                return i;
            }
        }
        return -1; // No space left for new node
    }
    void addEdge(string u, string n, int d, int p, int h, string v) 
    {
        int indexU = getOrAddIndex(u), indexV = getOrAddIndex(v);
        // Add edge (u, v) with distance d
        Node* newNode = new Node(v, n, d, p, h);
        newNode->next = adjacencyList[indexU];
        adjacencyList[indexU] = newNode;
        // For undirected graph, add edge (v, u) with the same details
        newNode = new Node(u, n, d, p, h);
        newNode->next = adjacencyList[indexV];
        adjacencyList[indexV] = newNode;
    }
    void path(string start, string end) 
    {
        int dist[MAX_NODES], prev[MAX_NODES], visited[MAX_NODES], startIndex = getOrAddIndex(start), endIndex = getOrAddIndex(end);
        // Initialize distances, previous nodes, and visited array
        for (int i = 0; i < numNodes; i++) 
        {
            dist[i] = INF;
            prev[i] = -1; // Indicates no previous node
            visited[i] = false;
        }
        dist[startIndex] = 0;
        for (int i = 0; i < numNodes - 1; i++)
        {
            int minDist = INF, minIndex = -1;
            // Find the airport with the minimum distance
            for (int j = 0; j < numNodes; j++) 
            {
                if (!visited[j] && dist[j] < minDist) 
                {
                    minDist = dist[j];
                    minIndex = j;
                }
            }
            // Mark the selected airport as visited
            visited[minIndex] = true;
            // Update distance value of the adjacent vertices
            Node* current = adjacencyList[minIndex];
            while (current != nullptr) 
            {
                int v = getOrAddIndex(current->airport), w = current->distance;
                if (!visited[v] && dist[minIndex] != INF && dist[minIndex] + w < dist[v]) 
                {
                    dist[v] = dist[minIndex] + w;
                    prev[v] = minIndex; // Update previous node
                }
                current = current->next;
            }
        }
        // Print the shortest distance and path from start to end
        cout << "\nSHORTEST DISTANCE FROM " << start << " TO " << end << "     : ";
        if (dist[endIndex] == INF)
            cout << "\nSORRY, NOT FOUND!!!\n" << endl;
        else
            printPathDetails(prev, startIndex, endIndex);
    }
    void price(string start, string end) 
    {
        int dist[MAX_NODES], prev[MAX_NODES], visited[MAX_NODES], startIndex = getOrAddIndex(start), endIndex = getOrAddIndex(end);
        // Initialize distances, previous nodes, and visited array
        for (int i = 0; i < numNodes; i++) 
        {
            dist[i] = INF;
            prev[i] = -1; // Indicates no previous node
            visited[i] = false;
        }
        dist[startIndex] = 0;
        for (int i = 0; i < numNodes - 1; i++)
        {
            int minDist = INF, minIndex = -1;
            // Find the airport with the minimum distance
            for (int j = 0; j < numNodes; j++) 
            {
                if (!visited[j] && dist[j] < minDist) 
                {
                    minDist = dist[j];
                    minIndex = j;
                }
            }
            // Mark the selected airport as visited
            visited[minIndex] = true;
            // Update distance value of the adjacent vertices
            Node* current = adjacencyList[minIndex];
            while (current != nullptr) 
            {
                int v = getOrAddIndex(current->airport), w = current->price;
                if (!visited[v] && dist[minIndex] != INF && dist[minIndex] + w < dist[v]) 
                {
                    dist[v] = dist[minIndex] + w;
                    prev[v] = minIndex; // Update previous node
                }
                current = current->next;
            }
        }
        // Print the shortest distance and path from start to end
        cout << "\nLOWEST PRICE FROM " << start << " TO " << end << "          : ";
        if (dist[endIndex] == INF)
            cout << "\nSORRY, NOT FOUND!!!\n" << endl;
        else
            printPathDetails(prev, startIndex, endIndex);
    }
    void halts(string start, string end) 
    {
        int dist[MAX_NODES], prev[MAX_NODES], visited[MAX_NODES], startIndex = getOrAddIndex(start), endIndex = getOrAddIndex(end);
        // Initialize distances, previous nodes, and visited array
        for (int i = 0; i < numNodes; i++) 
        {
            dist[i] = INF;
            prev[i] = -1; // Indicates no previous node
            visited[i] = false;
        }
        dist[startIndex] = 0;
        for (int i = 0; i < numNodes - 1; i++)
        {
            int minDist = INF, minIndex = -1;
            // Find the airport with the minimum distance
            for (int j = 0; j < numNodes; j++) 
            {
                if (!visited[j] && dist[j] < minDist) 
                {
                    minDist = dist[j];
                    minIndex = j;
                }
            }
            // Mark the selected airport as visited
            visited[minIndex] = true;
            // Update distance value of the adjacent vertices
            Node* current = adjacencyList[minIndex];
            while (current != nullptr) 
            {
                int v = getOrAddIndex(current->airport), w = current->halts;
                if (!visited[v] && dist[minIndex] != INF && dist[minIndex] + w < dist[v]) 
                {
                    dist[v] = dist[minIndex] + w;
                    prev[v] = minIndex; // Update previous node
                }
                current = current->next;
            }
        }
        // Print the shortest distance and path from start to end
        cout << "\nLESS NUMBER OF HAULTS FROM " << start << " TO " << end << " : ";
        if (dist[endIndex] == INF)
            cout << "\nSORRY, NOT FOUND!!!\n" << endl;
        else
            printPathDetails(prev, startIndex, endIndex);
    }
    void printPathDetails(int prev[], int start, int end) 
    {
        stack<int> path;
        int current = end;
        while (current != start) 
        {
            path.push(current);
            current = prev[current];
        }
        path.push(start);
        int prevNode = -1;
        while (!path.empty()) 
        {
            int currentNode = path.top();
            path.pop();
            if (prevNode != -1) 
            {
                Node* edge = findEdge(prevNode, currentNode);
                cout << " -> (" << edge->airplane << "," << edge->distance << " km, $" << edge->price << ", " << edge->halts << " halts) -> " ;
            }
            cout << nodeNames[currentNode];
            prevNode = currentNode;
        }
        cout << endl;
    }
    Node* findEdge(int u, int v) 
    {
        Node* current = adjacencyList[u];
        while (current != nullptr)
        {
            if (nodeIndices[getOrAddIndex(current->airport)] == v)
                return current;
            current = current->next;
        }
        return nullptr; // Edge not found
    }
};
int main() 
{
    system("CLS");
    int numNodes, numEdges, d, p, h;
    cout << "\nENTER NUMBER OF AIRPORTS    : ";
    cin >> numNodes;
    cout << "ENTER NUMBER OF CONNECTIONS : ";
    cin >> numEdges;
    Graph graph(numNodes);
    cout << "\nENTER THE DETAILS : " << endl;
    for (int i = 0; i < numEdges; i++)
    {
        string u, v, n;
        cout << "\n------------------------------------------------" << endl;
        cout << "ENTER BOARDING AIRPORT    : ";
        cin >> u;
        cout << "ENTER AIRPLANE NAME       : ";
        cin >> n;
        cout << "ENTER DISTANCE (in kms)   : ";
        cin >> d;
        cout << "ENTER PRICE (in $)        : ";
        cin >> p;
        cout << "ENTER NUMBER OF HALTS     : ";
        cin >> h;
        cout << "ENTER DESTINATION AIRPORT : ";
        cin >> v;
        cout << "------------------------------------------------" << endl;
        graph.addEdge(u, n, d, p, h, v);
    }
    string start, end;
    cout << "\nENTER BOARDING AIRPORT    : ";
    cin >> start;
    cout << "ENTER DESTINATION AIRPORT : "; 
    cin >> end;
    graph.path(start, end);
    graph.price(start,end);
    graph.halts(start,end);
    cout << endl;
    return 0;
}