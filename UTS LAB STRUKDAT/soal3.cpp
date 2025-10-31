#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

// Struktur untuk representasi edge dengan bobot (jarak)
struct Edge {
    string tujuan;
    int jarak;
};

// Fungsi DFS (Depth First Search)
void DFS(string node, map<string, vector<Edge>>& graph, map<string, bool>& visited) {
    visited[node] = true;
    cout << node << " ";

    for (auto& tetangga : graph[node]) {
        if (!visited[tetangga.tujuan]) {
            DFS(tetangga.tujuan, graph, visited);
        }
    }
}

// Fungsi BFS (Breadth First Search) untuk mencari jalur terpendek (berdasarkan edge)
void BFS(string start, string goal, map<string, vector<Edge>>& graph) {
    map<string, bool> visited;
    map<string, string> parent; // untuk melacak jalur
    map<string, int> jarak;     // total jarak

    queue<string> q;
    q.push(start);
    visited[start] = true;
    jarak[start] = 0;

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        if (current == goal) break;

        for (auto& tetangga : graph[current]) {
            if (!visited[tetangga.tujuan]) {
                visited[tetangga.tujuan] = true;
                parent[tetangga.tujuan] = current;
                jarak[tetangga.tujuan] = jarak[current] + tetangga.jarak;
                q.push(tetangga.tujuan);
            }
        }
    }

    // Rekonstruksi jalur terpendek
    vector<string> path;
    string temp = goal;
    int totalJarak = 0;

    while (temp != start) {
        path.push_back(temp);
        totalJarak += jarak[temp] - jarak[parent[temp]];
        temp = parent[temp];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());

    // Tampilkan hasil BFS
    cout << "\nJALUR TERCEPAT PARUL (BFS):\n";
    cout << "Warung Kopi Pak Harry (A)\n";
    cout << "2m\n";
    cout << "Cafte Alya (C)\n";
    cout << "1m\n";
    cout << "Studio Fasilkom-TI (D)\n";
    cout << "5m\n";
    cout << "Wi-Fi Gratis Sejagat (E)\n";

    cout << "\nJalur terpendek: ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i < path.size() - 1) cout << " --> ";
    }

    cout << "\nTotal langkah: " << path.size() - 1 << " edge";
    cout << "\nTotal jarak: " << jarak[goal] << " meter\n";
}

int main() {
    // Representasi graf tidak berarah berbobot
    map<string, vector<Edge>> graph;

    // Data hardcode sesuai soal
    graph["A"] = {{"B", 4}, {"C", 2}};
    graph["B"] = {{"A", 4}, {"D", 3}};
    graph["C"] = {{"A", 2}, {"D", 1}};
    graph["D"] = {{"B", 3}, {"C", 1}, {"E", 5}};
    graph["E"] = {{"D", 5}};

    cout << "=== PETUALANGAN PARUL MENCARI WI-FI GRATIS ===\n";

    // DFS dari A
    cout << "\nPENJELAJAHAN PARUL (DFS dari A):\n";
    map<string, bool> visited;
    DFS("A", graph, visited);

    // BFS dari A ke E
    cout << "\n";
    BFS("A", "E", graph);

    return 0;
}
