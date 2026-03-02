#include <iostream>
using namespace std;

void reverseArray(int* arr, int size) {
    int* indeksAwal = arr;              
    int* indeksAkhir = arr + size - 1;  

    while (indeksAwal < indeksAkhir) {
        
        int temp = *indeksAwal;
        *indeksAwal = *indeksAkhir;
        *indeksAkhir = temp;

        cout << "alamat indeks (awal ke tengah) : " << indeksAwal << endl;
        cout << "alamat indeks (akhir ke tengah) : " << indeksAkhir << endl;
        cout << endl;

        indeksAwal++;
        indeksAkhir--;
    }
}

int main(){
    int arr[7] = {2, 3, 5, 7, 11, 13, 17};
    int n = sizeof(arr) / sizeof(arr[0]);
    reverseArray(arr, n);
    cout << "Setelah dibalik : ";
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    return 0;
}