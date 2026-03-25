#include <iostream>
#include <string>
#include <algorithm> 
#include <cmath>  
#include <iomanip>
using namespace std;

struct Kereta {
    string noKereta;
    string namaKereta;
    string asal;
    string tujuan;
    int hargaTiket;
};

Kereta daftarKereta[100];
int jumlahKereta = 7; 

void init_data_awal() {
    daftarKereta[0] = {"KA001", "kereta", "mugirejo", "surabaya", 350000};
    daftarKereta[1] = {"KA089", "whoosh", "jakarta", "malang", 280000};
    daftarKereta[2] = {"KA201", "Mutiara Selatan", "bandung", "surabaya", 250000};
    daftarKereta[3] = {"KA098", "Bima", "jakarta", "surabaya", 220000};
    daftarKereta[4] = {"KA101", "Taksaka", "jakarta", "yogyakarta", 180000};
    daftarKereta[5] = {"KA301", "Senja Utama", "bandung", "yogyakarta", 200000};
    daftarKereta[6] = {"KA002", "Argo Lawu", "solo", "jakarta", 320000};
}

void lihatJadwal(Kereta* arr, int n) {
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

void tambahData(Kereta*& arr, int& n) { 
    if(n >= 100) {
        cout << "kapasitas penuh\n";
        return;
    }

    Kereta k;
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

int linearSearchRute(Kereta* arr, int n, const string& asal, const string& tujuan) {
    for(int i = 0; i < n; i++) { //perulangan untuk membaca semua array of struct daftarkereta
        if((arr + i)->asal == asal && (arr + i)->tujuan == tujuan) { // cek apakah data di daftar kereta sama dengan dicari user
            return i;  // jika benar, hasil ditampilkan ke user
        }
    }
    return -1; 
}

int jumpSearchByNo(Kereta* arr, int n, const string& no) {
    int step = static_cast<int>(sqrt(n)); //variable ukuran lompatan
    int prev = 0; 

    while ((arr + min(step, n) - 1)->noKereta < no) {
        prev = step;
        step += static_cast<int>(sqrt(n));
        if (prev >= n)
            return -1;
    }

    int batas = step;
    if (batas > n) batas = n; 

    while (prev < batas) {
        if ((arr + prev)->noKereta == no)
        return prev;
        prev++;
    }
    return -1;
    }

void swapKereta(Kereta* a, Kereta* b) {
    Kereta temp = *a;
    *a = *b;
    *b = temp;
}

void merge(Kereta* arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    Kereta L[n1], R[n2];

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

void mergeSortNama(Kereta* arr, int l, int r) {
    if (l >= r) return;

    int m = l + (r - l) / 2;
    mergeSortNama(arr, l, m);
    mergeSortNama(arr, m + 1, r);
    merge(arr, l, m, r);
}

void selectionSortHarga(Kereta* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if ((arr + j)->hargaTiket < (arr + min_idx)->hargaTiket) {
                min_idx = j;
            }
        }
        if(min_idx != i) {
            swapKereta((arr + i), (arr + min_idx)); 
        }
    }
}

int main() {
    init_data_awal();

    Kereta* ptrKereta = daftarKereta;

    int pilihan;
    do {
        cout << "\n--- Sistem informasi kereta api ---\n";
        cout << "1. tampilkan jadwal semua kereta\n";
        cout << "2. tambah data kereta baru\n";
        cout << "3. cari rute (linear search)\n";
        cout << "4. cari nomor kereta (jump search)\n";
        cout << "5. urutkan berdasarkan nama(A ke Z - Merge Sort)\n";
        cout << "6. urutkan berdasarkan harga (Termurah ke termahal - Selection Sort)\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch(pilihan) {
            case 1:
                lihatJadwal(ptrKereta, jumlahKereta);
                break;
            case 2:
                tambahData(ptrKereta, jumlahKereta); 
                break;
            case 3: {
                string asal, tujuan;
                cin.ignore();
                cout << "masukkan asal: ";
                getline(cin, asal);
                cout << "masukkan tujuan: ";
                getline(cin, tujuan);
                int idx = linearSearchRute(ptrKereta, jumlahKereta, asal, tujuan);
                if(idx != -1) {
                    cout << "ditemukan:\n";
                    cout << (ptrKereta + idx)->noKereta << " | "
                         << (ptrKereta + idx)->namaKereta << " | "
                         << (ptrKereta + idx)->asal << " -> " << (ptrKereta + idx)->tujuan << endl;
                } else {
                    cout << "tidak ketemu.\n";
                }
                break;
            }
            case 4: {
                string no;
                cout << "masukkan nomor kereta";
                cin >> no;
                int idx = jumpSearchByNo(ptrKereta, jumlahKereta, no);
                if(idx != -1) {
                    cout << "ditemukan:\n";
                    cout << (ptrKereta + idx)->noKereta << " | "
                         << (ptrKereta + idx)->namaKereta << " | "
                         << (ptrKereta + idx)->hargaTiket << endl;
                } else {
                    cout << "tidak ketemu.\n";
                }
                break;
            }
            case 5:
                mergeSortNama(ptrKereta, 0, jumlahKereta - 1);
                cout << "data berhasil diurutkan berdasarkan nama kereta (A ke Z).\n";
                break;
            case 6:
                selectionSortHarga(ptrKereta, jumlahKereta);
                cout << "Data berhasil diurutkan berdasarkan harga tiket (termurah ke termahal).\n";
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