#include <iostream>
using namespace std;

void tukar(int *nilai1, int *nilai2){
  int temp = *nilai1;
  *nilai1 = *nilai2;
  *nilai2 = temp;
}

int main(){
    int input1, input2;

    cout << "masukkan input pertama : "; cin >> input1;
    cout << "masukkan input kedua : "; cin >> input2;
    cout << endl;
    cout << "input sebelum diubah : " << endl;
    cout << "input 1 : " << input1 << " alamatnya : " << &input1 << endl;
    cout << "input 2 : " << input2 << " alamatnya : " << &input2 << endl;
    
    tukar(&input1, &input2);
    
    cout << "input setelah diubah : " << endl;
    cout << "input 1 : " << input1 << " alamatnya : " << &input1 << endl;
    cout << "input 2 : " << input2 << " alamatnya : " << &input2 << endl;

}