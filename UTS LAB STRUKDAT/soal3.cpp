#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

// Struktur edge
struct Edge {
    string tujuan;
    int jarak;
};

// DFS untuk menelusuri semua kafe
void DFS(string node, map<string, vector<Edge>>& graph, map<string, bool>& visited) {
    visited[node] = true;
    cout << node;

    // Cek apakah masih ada node yang belum dikunjungi untuk menambah tanda panah
    bool first = true;
    for (auto edge : graph[node]) {
        if (!visited[edge.tujuan]) {
            cout << " -> ";
            DFS(edge.tujuan, graph, visited);
            first = false;
        }
    }
}

// BFS untuk mencari jalur tercepat (berdasarkan jumlah edge)
void BFS(string start, string goal, map<string, vector<Edge>>& graph, map<string, string>& namaKafe) {
    queue<vector<string>> q;
    map<string, bool> visited;
    q.push({start});
    visited[start] = true;

    // Simpan jarak antar node
    map<pair<string, string>, int> jarakEdge;
    for (auto& g : graph) {
        for (auto& e : g.second) {
            jarakEdge[{g.first, e.tujuan}] = e.jarak;
            jarakEdge[{e.tujuan, g.first}] = e.jarak;
        }
    }

    while (!q.empty()) {
        vector<string> path = q.front();
        q.pop();
        string node = path.back();

        if (node == goal) {
            cout << "\n\nJALUR TERCEPAT PARUL (BFS):" << endl;
            int totalJarak = 0;

            // Tampilkan setiap langkah seperti di soal
            for (int i = 0; i < path.size(); i++) {
                cout << namaKafe[path[i]] << " (" << path[i] << ")" << endl;
                if (i < path.size() - 1) {
                    int jarak = jarakEdge[{path[i], path[i + 1]}];
                    cout << jarak << "m" << endl;
                    totalJarak += jarak;
                }
            }

            // Jalur ringkas di akhir
            cout << "\nJalur terpendek: ";
            for (int i = 0; i < path.size(); i++) {
                cout << path[i];
                if (i < path.size() - 1) cout << " -> ";
            }
            cout << endl;
            cout << "Total langkah: " << path.size() - 1 << " edge" << endl;
            cout << "Total jarak: " << totalJarak << " meter" << endl;
            return;
        }

        for (auto edge : graph[node]) {
            if (!visited[edge.tujuan]) {
                visited[edge.tujuan] = true;
                vector<string> newPath = path;
                newPath.push_back(edge.tujuan);
                q.push(newPath);
            }
        }
    }
}

int main() {
    // Deklarasi graph
    map<string, vector<Edge>> graph;
    graph["A"] = {{"C", 2}, {"B", 4}};
    graph["B"] = {{"A", 4}, {"D", 3}};
    graph["C"] = {{"A", 2}, {"D", 1}};
    graph["D"] = {{"C", 1}, {"E", 5}, {"B", 3}};
    graph["E"] = {{"D", 5}};

    // Nama kafe
    map<string, string> namaKafe = {
        {"A", "Warung Kopi Pak Harry"},
        {"B", "Kedai Coding IKLC"},
        {"C", "Cafe Alya"},
        {"D", "Studio Fasilkom-TI"},
        {"E", "Wi-Fi Gratis Sejagat"}
    };

    // Output DFS
    cout << "PENJELAJAHAN PARUL (DFS dari A):" << endl;
    map<string, bool> visited;
    for (auto& g : graph) visited[g.first] = false;
    DFS("A", graph, visited);

    // Output BFS
    BFS("A", "E", graph, namaKafe);

    return 0;
}
