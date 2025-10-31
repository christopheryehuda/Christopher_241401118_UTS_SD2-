#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Pesanan {
    string namaHewan;
    string menuPesanan;
    int statusVIP;   // 1 = biasa, 2 = VIP
    int waktuDatang; 
};

// Implementasi queue manual pakai dynamic array (vector)
struct Queue {
    vector<Pesanan> data;

    // enqueue
    void enqueue(Pesanan p) {
        data.push_back(p);
    }

    // dequeue
    Pesanan dequeue() {
        if (data.empty()) {
            cout << "Antrian kosong!\n";
            Pesanan kosong;
            return kosong;
        }
        Pesanan front = data[0];
        // geser semua elemen ke depan (simulasi dequeue manual)
        for (int i = 1; i < data.size(); i++) {
            data[i - 1] = data[i];
        }
        data.pop_back();
        return front;
    }

    bool isEmpty() {
        return data.empty();
    }
};

int main() {
    int n;
    cout << "Masukkan jumlah pesanan: ";
    cin >> n;
    cin.ignore();

    Queue vipQueue;
    Queue biasaQueue;

    // Input data
    for (int i = 0; i < n; i++) {
        Pesanan p;
        cout << "\nPesanan " << i + 1 << ":\n";
        cout << "Nama hewan: ";
        getline(cin, p.namaHewan);
        cout << "Menu pesanan: ";
        getline(cin, p.menuPesanan);
        cout << "Status VIP (1=biasa, 2=VIP): ";
        cin >> p.statusVIP;
        cin.ignore();
        p.waktuDatang = i;

        if (p.statusVIP == 2)
            vipQueue.enqueue(p);
        else
            biasaQueue.enqueue(p);
    }

    cout << "\n=== Urutan Pelayanan ===\n";
    int nomor = 1;

    while (!vipQueue.isEmpty()) {
        Pesanan p = vipQueue.dequeue();
        cout << nomor++ << ". " << p.namaHewan << " - " << p.menuPesanan << "  [VIP]\n";
    }

    while (!biasaQueue.isEmpty()) {
        Pesanan p = biasaQueue.dequeue();
        cout << nomor++ << ". " << p.namaHewan << " - " << p.menuPesanan << endl;
    }

    return 0;
}
