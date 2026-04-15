#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;


struct kereta {
    string noKereta;
    string namaKereta;
    string asal;
    string tujuan;
    int hargaTiket;
};

struct transaksi {
    string namaPenumpang;
    string noKereta;
    string namaKereta;
    string asal;
    string tujuan;
    int harga;
};

struct NodeQueue {
    transaksi data;
    NodeQueue* next;
};

struct NodeStack {
    transaksi data;
    NodeStack* next;
};

NodeQueue* head_queue = nullptr;
NodeQueue* tail_queue = nullptr;

NodeStack* head_stack = nullptr;

kereta daftarKereta[100];
int jumlahKereta = 7;

void enqueue(transaksi t);
void dequeue(kereta* keretaArr, int keretaCount);
void pushToStack(transaksi t); 
void pop();
void peekQueue();
void peekStack();
void tampilAntrian();
void tampilRiwayat();

void init_data_awal() {
    daftarKereta[0] = {"KA001", "kereta", "mugirejo", "surabaya", 350000};
    daftarKereta[1] = {"KA089", "whoosh", "jakarta", "malang", 280000};
    daftarKereta[2] = {"KA201", "Mutiara Selatan", "bandung", "surabaya", 250000};
    daftarKereta[3] = {"KA098", "Bima", "jakarta", "surabaya", 220000};
    daftarKereta[4] = {"KA101", "Taksaka", "jakarta", "yogyakarta", 180000};
    daftarKereta[5] = {"KA301", "Senja Utama", "bandung", "yogyakarta", 200000};
    daftarKereta[6] = {"KA002", "Argo Lawu", "solo", "jakarta", 320000};
}

void lihatJadwal(kereta* arr, int n) {
    cout << "\n--- Jadwal semua kereta ---\n";
    cout << left
         << setw(10) << "no"
         << setw(20) << "nama"
         << setw(15) << "asal"
         << setw(15) << "tujuan"
         << setw(12) << "harga" << endl;
    for (int i = 0; i < n; i++) {
        cout << left
             << setw(10) << (arr + i)->noKereta
             << setw(20) << (arr + i)->namaKereta
             << setw(15) << (arr + i)->asal
             << setw(15) << (arr + i)->tujuan
             << setw(12) << (arr + i)->hargaTiket << endl;
    }
}

void tambahData(kereta*& arr, int& n) {
    if(n >= 100) {
        cout << "kapasitas penuh\n";
        return;
    }
    kereta k;
    cin.ignore();
    cout << "masukkan no kereta: ";
    getline(cin, k.noKereta);
    cout << "masukkan nama kereta: ";
    getline(cin, k.namaKereta);
    cout << "masukkan asal: ";
    getline(cin, k.asal);
    cout << "masukkan tujuan: ";
    getline(cin, k.tujuan);
    cout << "masukkan harga tiket: ";
    cin >> k.hargaTiket;
    *(arr + n) = k;
    n++;
    cout << "Data berhasil ditambahkan.\n";
}

int linearSearchRute(kereta* arr, int n, const string& asal, const string& tujuan) {
    for(int i = 0; i < n; i++) {
        if((arr + i)->asal == asal && (arr + i)->tujuan == tujuan) {
            return i;
        }
    }
    return -1;
}

int jumpSearchByNo(kereta* arr, int n, const string& no) {
    int step = static_cast<int>(sqrt(n));
    int prev = 0;
    while (prev < n && (arr + min(step, n) - 1)->noKereta < no) {
        prev = step;
        step += static_cast<int>(sqrt(n));
        if (prev >= n)
            return -1;
    }
    int batas = step;
    if (batas > n) batas = n;
    while (prev < batas && (arr + prev)->noKereta < no) {
        prev++;
    }
    if (prev < n && (arr + prev)->noKereta == no)
        return prev;
    return -1;
}

void swapkereta(kereta* b, kereta* a) {
    kereta temp = *a;
    *a = *b;
    *b = temp;
}

void merge(kereta* arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    kereta L[n1], R[n2];
    for (int i = 0; i < n1; i++)
        L[i] = *(arr + l + i);
    for (int j = 0; j < n2; j++)
        R[j] = *(arr + m + 1 + j);
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].namaKereta <= R[j].namaKereta) {
            *(arr + k) = L[i];
            i++;
        } else {
            *(arr + k) = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        *(arr + k) = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        *(arr + k) = R[j];
        j++;
        k++;
    }
}

void mergeSortNama(kereta* arr, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSortNama(arr, l, m);
    mergeSortNama(arr, m + 1, r);
    merge(arr, l, m, r);
}

void selectionSortHarga(kereta* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if ((arr + j)->hargaTiket < (arr + min_idx)->hargaTiket) {
                min_idx = j;
            }
        }
        if(min_idx != i) {
            swapkereta((arr + i), (arr + min_idx));
        }
    }
}

void enqueue(transaksi t) {
    NodeQueue* newNode = new NodeQueue;
    newNode->data = t;
    newNode->next = nullptr;
    if (tail_queue == nullptr) {
        head_queue = tail_queue = newNode;
    } else {
        // Tambahkan di akhir
        tail_queue->next = newNode;
        tail_queue = newNode;
    }
    cout << "Penumpang " << t.namaPenumpang << " dengan rute " << t.asal << " -> " << t.tujuan << " masuk antrian." << endl;
}

void dequeue(kereta* keretaArr, int keretaCount) {
    if (head_queue == nullptr) { 
        cout << "Antrian kosong! Tidak ada yang bisa diproses." << endl;
        return;
    }

    NodeQueue* temp = head_queue;
    transaksi t = temp->data; 

    int idx = -1;
    for (int i = 0; i < keretaCount; i++) {
        if ((keretaArr + i)->noKereta == t.noKereta) {
            idx = i;
            break;
        }
    }

    if (idx != -1) {
        t.namaKereta = (keretaArr + idx)->namaKereta;
        t.harga = (keretaArr + idx)->hargaTiket;

        pushToStack(t); 
        cout << "Proses pembelian tiket untuk " << t.namaPenumpang << " selesai." << endl;
        cout << "Detail: " << t.namaPenumpang << " memesan " << t.namaKereta << " (" << t.noKereta << ") dari " << t.asal << " ke " << t.tujuan << "." << endl;
    } else {
        cout << "Nomor kereta " << t.noKereta << " untuk penumpang " << t.namaPenumpang << " tidak ditemukan. transaksi dibatalkan." << endl;
    }

    head_queue = head_queue->next;
    if (head_queue == nullptr) {
        tail_queue = nullptr;
    }
    delete temp; 

    if (tail_queue == nullptr) { 
        head_queue = tail_queue = nullptr; 
    }
}


void pushToStack(transaksi t) {
    NodeStack* newNode = new NodeStack;
    newNode->data = t;
    newNode->next = head_stack;
    head_stack = newNode;
}


void pop() {
    if (head_stack == nullptr) { 
        cout << "Riwayat kosong! Tidak ada transaksi yang bisa dibatalkan." << endl;
        return;
    }
    NodeStack* temp = head_stack;
    cout << "transaksi terakhir untuk " << temp->data.namaPenumpang << " di kereta " << temp->data.namaKereta << " dibatalkan dan dihapus dari riwayat." << endl;
    head_stack = head_stack->next;
    delete temp;
}

void peekQueue() {
    if (head_queue == nullptr) { 
        cout << "Antrian kosong." << endl;
        return;
    }
    cout << "Penumpang terdepan di antrian: " << head_queue->data.namaPenumpang << ", Rute: " << head_queue->data.asal << " -> " << head_queue->data.tujuan << endl;
}

void peekStack() {
    if (head_stack == nullptr) { 
        cout << "Riwayat kosong." << endl;
        return;
    }
    cout << "transaksi terakhir: " << head_stack->data.namaPenumpang << ", kereta: " << head_stack->data.namaKereta << ", Rute: " << head_stack->data.asal << " -> " << head_stack->data.tujuan << endl;
}

void tampilAntrian() {
    if (head_queue == nullptr) { 
        cout << "Antrian kosong." << endl;
        return;
    }
    cout << "\n--- Daftar Antrian Pembelian Tiket ---\n";
    cout << left
         << setw(20) << "Nama Penumpang"
         << setw(15) << "No kereta"
         << setw(15) << "Asal"
         << setw(15) << "Tujuan" << endl;
    NodeQueue* current = head_queue;
    while (current != nullptr) {
        cout << left
             << setw(20) << current->data.namaPenumpang
             << setw(15) << current->data.noKereta
             << setw(15) << current->data.asal
             << setw(15) << current->data.tujuan << endl;
        current = current->next;
    }
}

void tampilRiwayat() {
    if (head_stack == nullptr) { 
        cout << "Riwayat transaksi kosong." << endl;
        return;
    }
    cout << "\n--- Riwayat transaksi Pembelian Tiket ---\n";
    cout << left
         << setw(20) << "Nama Penumpang"
         << setw(15) << "No kereta"
         << setw(20) << "Nama kereta"
         << setw(15) << "Asal"
         << setw(15) << "Tujuan"
         << setw(10) << "Harga" << endl;
    NodeStack* current = head_stack;
    while (current != nullptr) {
        cout << left
             << setw(20) << current->data.namaPenumpang
             << setw(15) << current->data.noKereta
             << setw(20) << current->data.namaKereta
             << setw(15) << current->data.asal
             << setw(15) << current->data.tujuan
             << setw(10) << current->data.harga << endl;
        current = current->next;
    }
}

int main() {
    init_data_awal();
    kereta* ptrkereta = daftarKereta;
    int pilihan;
    do {
        cout << "\n--- Sistem Informasi & Pemesanan Tiket kereta Api ---\n";
        cout << "1. Tampilkan jadwal semua kereta\n";
        cout << "2. Tambah data kereta baru\n";
        cout << "3. Cari rute (linear search)\n";
        cout << "4. Cari nomor kereta (jump search)\n";
        cout << "5. Urutkan berdasarkan nama(A ke Z - Merge Sort)\n";
        cout << "6. Urutkan berdasarkan harga (Termurah ke termahal - Selection Sort)\n";
        cout << "--- Menu Pemesanan & Riwayat ---\n";
        cout << "7. Tambah ke Antrian (Enqueue)\n";
        cout << "8. Proses Antrian (Dequeue)\n";
        cout << "9. Tampilkan Antrian\n";
        cout << "10. Tampilkan Riwayat\n";
        cout << "11. Batal transaksi Terakhir (Pop)\n";
        cout << "12. Peek Antrian & Riwayat\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch(pilihan) {
            case 1:
                lihatJadwal(ptrkereta, jumlahKereta);
                break;
            case 2:
                tambahData(ptrkereta, jumlahKereta);
                break;
            case 3: {
                string asal, tujuan;
                cin.ignore();
                cout << "masukkan asal: ";
                getline(cin, asal);
                cout << "masukkan tujuan: ";
                getline(cin, tujuan);
                int idx = linearSearchRute(ptrkereta, jumlahKereta, asal, tujuan);
                if(idx != -1) {
                    cout << "ditemukan:\n";
                    cout << (ptrkereta + idx)->noKereta << " | "
                         << (ptrkereta + idx)->namaKereta << " | "
                         << (ptrkereta + idx)->asal << " -> " << (ptrkereta + idx)->tujuan << endl;
                } else {
                    cout << "tidak ketemu.\n";
                }
                break;
            }
            case 4: {
                string no;
                cout << "masukkan nomor kereta: ";
                cin >> no;
                int idx = jumpSearchByNo(ptrkereta, jumlahKereta, no);
                if(idx != -1) {
                    cout << "ditemukan:\n";
                    cout << (ptrkereta + idx)->noKereta << " | "
                         << (ptrkereta + idx)->namaKereta << " | "
                         << (ptrkereta + idx)->hargaTiket << endl;
                } else {
                    cout << "tidak ketemu.\n";
                }
                break;
            }
            case 5:
                mergeSortNama(ptrkereta, 0, jumlahKereta - 1);
                cout << "data berhasil diurutkan berdasarkan nama kereta (A ke Z).\n";
                break;
            case 6:
                selectionSortHarga(ptrkereta, jumlahKereta);
                cout << "Data berhasil diurutkan berdasarkan harga tiket (termurah ke termahal).\n";
                break;
            case 7: { // Enqueue
                if (jumlahKereta == 0) {
                    cout << "Belum ada data kereta. Silakan tambahkan data kereta terlebih dahulu." << endl;
                    break;
                }
                transaksi t;
                string asal, tujuan;
                cin.ignore();
                cout << "Masukkan nama penumpang: ";
                getline(cin, t.namaPenumpang);
                cout << "Masukkan asal: ";
                getline(cin, asal);
                cout << "Masukkan tujuan: ";
                getline(cin, tujuan);
                int idx = linearSearchRute(ptrkereta, jumlahKereta, asal, tujuan);
                if (idx != -1) {
                    t.asal = asal;
                    t.tujuan = tujuan;
                    t.noKereta = (ptrkereta + idx)->noKereta;
                    enqueue(t);
                } else {
                    cout << "Rute " << asal << " -> " << tujuan << " tidak ditemukan." << endl;
                }
                break;
            }
            case 8:
                dequeue(ptrkereta, jumlahKereta);
                break;
            case 9:
                tampilAntrian();
                break;
            case 10:
                tampilRiwayat();
                break;
            case 11:
                pop();
                break;
            case 12:
                peekQueue();
                peekStack();
                break;
            case 0:
                cout << "thank you thank you thank you.\n";
                break;
            default:
                cout << "pilihan tidak valid.\n";
        }
    } while(pilihan != 0);
    return 0;
}