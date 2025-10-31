#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Struktur data node linked list
struct Barang {
    string nama;
    int harga;
    int jumlah;
    Barang* next;
};

// Fungsi menambah barang di depan list
void tambahDepan(Barang*& head, string nama, int harga, int jumlah) {
    Barang* baru = new Barang{nama, harga, jumlah, head};
    head = baru;
}

// Fungsi menambah barang di belakang list
void tambahBelakang(Barang*& head, string nama, int harga, int jumlah) {
    Barang* baru = new Barang{nama, harga, jumlah, NULL};
    if (head == NULL) {
        head = baru;
    } else {
        Barang* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = baru;
    }
}

// Fungsi menambah barang setelah nama tertentu
bool tambahSetelah(Barang*& head, string target, string nama, int harga, int jumlah) {
    Barang* temp = head;
    while (temp != NULL && temp->nama != target)
        temp = temp->next;

    if (temp == NULL)
        return false;

    Barang* baru = new Barang{nama, harga, jumlah, temp->next};
    temp->next = baru;
    return true;
}

// Fungsi menghapus barang berdasarkan nama
bool hapusBarang(Barang*& head, string namaHapus) {
    if (head == NULL)
        return false;

    Barang* temp = head;
    Barang* prev = NULL;

    if (temp->nama == namaHapus) {
        head = temp->next;
        delete temp;
        return true;
    }

    while (temp != NULL && temp->nama != namaHapus) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
        return false;

    prev->next = temp->next;
    delete temp;
    return true;
}

// Fungsi menampilkan seluruh isi keranjang
void tampilkanKeranjang(Barang* head) {
    if (head == NULL) {
        cout << "\nKeranjang masih kosong!\n";
        return;
    }

    cout << "\n=== Daftar Barang di Keranjang ===\n";
    cout << left << setw(25) << "Nama Barang"
         << setw(10) << "Harga"
         << setw(10) << "Jumlah"
         << setw(10) << "Subtotal" << endl;
    cout << string(55, '-') << endl;

    int totalBarang = 0;
    int totalHarga = 0;
    Barang* temp = head;

    while (temp != NULL) {
        cout << left << setw(25) << temp->nama
             << setw(10) << temp->harga
             << setw(10) << temp->jumlah
             << setw(10) << temp->harga * temp->jumlah << endl;
        totalBarang++;
        totalHarga += temp->harga * temp->jumlah;
        temp = temp->next;
    }

    cout << string(55, '-') << endl;
    cout << "Total Barang : " << totalBarang << endl;
    cout << "Total Harga  : " << totalHarga << endl;
}

int main() {
    Barang* head = NULL;
    int n;

    cout << "Masukkan jumlah barang awal: ";
    cin >> n;
    cin.ignore();

    // Input awal
    for (int i = 0; i < n; i++) {
        string nama;
        int harga, jumlah;
        cout << "\nBarang " << i + 1 << ":\n";
        cout << "Nama barang : ";
        getline(cin, nama);
        cout << "Harga barang: ";
        cin >> harga;
        cout << "Jumlah barang: ";
        cin >> jumlah;
        cin.ignore();
        tambahBelakang(head, nama, harga, jumlah);
    }

    char lanjut;
    do {
        cout << "\n=== Menu Keranjang Belanja ===\n";
        cout << "1. Tambah barang di depan\n";
        cout << "2. Tambah barang setelah nama tertentu\n";
        cout << "3. Tambah barang di belakang\n";
        cout << "4. Hapus barang berdasarkan nama\n";
        cout << "5. Tampilkan semua barang\n";
        cout << "6. Keluar\n";
        cout << "Pilih menu: ";

        int pilih;
        cin >> pilih;
        cin.ignore();

        if (pilih == 1) {
            string nama; int harga, jumlah;
            cout << "Nama barang : ";
            getline(cin, nama);
            cout << "Harga barang: ";
            cin >> harga;
            cout << "Jumlah barang: ";
            cin >> jumlah;
            cin.ignore();
            tambahDepan(head, nama, harga, jumlah);
        }
        else if (pilih == 2) {
            string target, nama; int harga, jumlah;
            cout << "Masukkan nama barang yang ingin disisip setelahnya: ";
            getline(cin, target);
            cout << "Nama barang baru : ";
            getline(cin, nama);
            cout << "Harga barang: ";
            cin >> harga;
            cout << "Jumlah barang: ";
            cin >> jumlah;
            cin.ignore();
            if (!tambahSetelah(head, target, nama, harga, jumlah))
                cout << "Barang dengan nama " << target << " tidak ditemukan!\n";
        }
        else if (pilih == 3) {
            string nama; int harga, jumlah;
            cout << "Nama barang : ";
            getline(cin, nama);
            cout << "Harga barang: ";
            cin >> harga;
            cout << "Jumlah barang: ";
            cin >> jumlah;
            cin.ignore();
            tambahBelakang(head, nama, harga, jumlah);
        }
        else if (pilih == 4) {
            string namaHapus;
            cout << "Masukkan nama barang yang akan dihapus: ";
            getline(cin, namaHapus);
            if (!hapusBarang(head, namaHapus))
                cout << "Barang tidak ditemukan!\n";
        }
        else if (pilih == 5) {
            tampilkanKeranjang(head);
        }
        else if (pilih == 6) {
            cout << "Program selesai.\n";
            break;
        }

        cout << "\nKembali ke menu? (y/n): ";
        cin >> lanjut;
        cin.ignore();
    } while (lanjut == 'y' || lanjut == 'Y');

    return 0;
}
