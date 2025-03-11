
#include <iostream>
using namespace std;


class Node {
public:
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

class MyList {
public:
    Node* head;

    MyList() {
        head = nullptr;
    }

    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }


    void display() const {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
    }


    bool empty() const {
        return head == nullptr;
    }


    void pop_front() {
        if (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    int front() const {

        if (head) {
            return head->data;
        }
        else {
            return -1;
        }
    }
};


class MyQueue {
public:
    MyList list;

    void push(int value) {
        list.push_back(value);
    }

    void pop() {
        list.pop_front();
    }

    int front() const {
        return list.front();
    }

    bool empty() const {
        return list.empty();
    }
};


class MyStack {
public:
    MyList list;

    void push(int value) {
        Node* newNode = new Node(value);
        newNode->next = list.head;
        list.head = newNode;
    }

    void pop() {
        if (!list.empty()) {
            Node* temp = list.head;
            list.head = list.head->next;
            delete temp;
        }
    }

    int top() const {
        return list.front();
    }

    bool empty() const {
        return list.empty();
    }
};


class Graph {
public:
    int vertices;
    MyList* adjList;
    const int INF = 1000000;

    Graph(int v) {
        vertices = v;
        adjList = new MyList[v];
    }

    ~Graph() {
        delete[] adjList;
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void displayGraph() {
        cout << "\n--- Social Network Representation (Adjacency List) ---\n";
        for (int i = 0; i < vertices; i++) {
            cout << "User " << i << " is connected to: ";
            adjList[i].display();
            cout << endl;
        }
    }

    void BFS(int start) {
        bool* visited = new bool[vertices]();
        MyQueue q;
        q.push(start);
        visited[start] = true;

        cout << "\n--- Shortest Path Using BFS ---\n";
        cout << "Starting from user " << start << ": ";
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            Node* temp = adjList[node].head;
            while (temp) {
                int neighbor = temp->data;
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
                temp = temp->next;
            }
        }
        cout << endl;
        delete[] visited;
    }

    void DFS(int start) {
        bool* visited = new bool[vertices]();
        MyStack s;
        s.push(start);
        visited[start] = true;

        cout << "\n--- Exploring All Nodes Using DFS ---\n";
        cout << "Starting from user " << start << ": ";
        while (!s.empty()) {
            int node = s.top();
            s.pop();
            cout << node << " ";

            Node* temp = adjList[node].head;
            while (temp) {
                int neighbor = temp->data;
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    s.push(neighbor);
                }
                temp = temp->next;
            }
        }
        cout << endl;
        delete[] visited;
    }

    double closenessCentrality(int node) {
        int* distances = new int[vertices];
        for (int i = 0; i < vertices; i++) {
            distances[i] = INF;
        }
        distances[node] = 0;

        MyQueue q;
        q.push(node);

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            Node* temp = adjList[current].head;
            while (temp) {
                int neighbor = temp->data;
                if (distances[neighbor] == INF) {
                    distances[neighbor] = distances[current] + 1;
                    q.push(neighbor);
                }
                temp = temp->next;
            }
        }

        double totalDistance = 0;
        int reachableNodes = 0;
        for (int i = 0; i < vertices; i++) {
            if (distances[i] != INF) {
                totalDistance += distances[i];
                reachableNodes++;
            }
        }

        if (reachableNodes <= 1) {
            delete[] distances;
            return 0;
        }


        double centrality = (reachableNodes - 1) / totalDistance;
        delete[] distances;
        return centrality;
    }

    void calculateCentrality() {
        cout << "\n--- Closeness Centrality of All Users ---\n";
        for (int i = 0; i < vertices; i++) {
            double centrality = closenessCentrality(i);
            cout << "User " << i << " has a closeness centrality of: " << centrality << endl;
        }
    }

    void efficientCentrality() {
        double centrality = closenessCentrality(0);
        int user = 0;
        for (int i = 1; i < vertices; i++) {
            double currentCentrality = closenessCentrality(i);
            if (centrality < currentCentrality) {
                centrality = currentCentrality;
                user = i;
            }
        }
        cout << "User " << user << " is in the best position to spread information, with a centrality of " << centrality << endl;
    }


};

int main() {
    cout << "\t-----------Welcome to the Social Network Analysis Tool -----------\n\n";

    cout << "Danish" << "Ali" << endl;
    cout<<"_____________________________" << endl;
    cout << "Reg_N0" << ":" << "L1F22BSCS0244" << endl;
    cout << "_____________________________" << endl;
    cout << "Section" << ":" << "D_2" << endl;
    cout << "_____________________________" << endl;

    Graph g(6);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    g.addEdge(4, 5);



    g.displayGraph();

    int choice;
    do {
        cout << "\n\t---------------------- Menu ----------------------\n";
        cout << "1. Find the shortest path to spread information (BFS)\n";
        cout << "2. Explore all nodes (DFS)\n";
        cout << "3. Find the best position to spread information (Closeness Centrality)\n";
        cout << "4. View closeness centrality of each user\n";

        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Enter the user ID to start the BFS: ";
            int start;
            cin >> start;
            g.BFS(start);
            break;
        }
        case 2: {
            cout << "Enter the user ID to start the DFS: ";
            int start;
            cin >> start;
            g.DFS(start);
            break;
        }
        case 3:
            g.efficientCentrality();
            break;
        case 4:
            g.calculateCentrality();
            break;

        case 0:
            cout << "Thank you for using the Social Network Analysis Tool. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
