#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

vector<int> antrian;
int front = -1;
int rear = -1;

vector<int> riwayat;
int top = -1;

bool cekIsi(){
    return front == -1 || front > rear;
}

void enqueue(int data){
    if(front == -1){
        front = 0;
    }
    rear++;
    antrian.push_back(data);
    cout << data << " masuk ke antrian" << endl;
}

int dequeueDanPush(){
    if (cekIsi()) {
        cout << "antrian kosong" << endl;
        return -1;
    }

    int data = antrian[front];
    front++;
    top++;
    riwayat.push_back(data);
    cout << data << " dimasukkan ke stack" << endl;

    if (cekIsi()) {
        front = rear = -1;
    }

    return data;

}

int peekQueue(){
    if (cekIsi()) {
        cout << "antrian kosong" << endl;
        return -1;
    }
    return antrian[front];
}

void displayQueue(){
    if (cekIsi()) {
        cout << "antrian kosong" << endl;
        return;
    }

    for(int i = 0; i <= rear; i++){
       cout << antrian[i] << " ";
    }
    cout << endl;
}

int peekStack(){
    if(top < 0){
        cout << "stack kosong" << endl;
        return -1;
    }else{
        return riwayat[top];
    }
}


int main(){

    for(int i = 0; i < 10; i++){
        enqueue(i);
    }

    cout << "data antrian(queue) terdepan : " << peekQueue() << endl;
    displayQueue();
    
    for(int j = 0; j <= rear; j++ ){
        dequeueDanPush();
    }
    
    cout << "data riwayat(stack) terdepan : " << peekStack();;
    

    return 0;
}