#include <iostream>
using namespace std;

struct mahasiswa 
{
 string nama;
 string NIM;
 float IPK;
};

int main(){

    struct mahasiswa data[5]{
        {"Febrianno", "038", 3.33},
        {"Ozora", "039", 3.30},
        {"Alinanto", "040", 3.44},
        {"Ali", "041", 3.67},
        {"Anto", "038", 3.89}
    };

    float ipkTertinggi = data[0].IPK;
    int mahasiswaPintar = 0;

    for (int i = 1; i < 5; i++){
        if (data[i].IPK > ipkTertinggi){
            ipkTertinggi = data[i].IPK;
            mahasiswaPintar = i;
        }
    }

    cout << "mahasiswa dengan ipk tertinggi adalah : " << data[mahasiswaPintar].nama << endl;
    cout << "ipk : " << ipkTertinggi << endl;
    return 0;
}