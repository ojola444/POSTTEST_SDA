#include <iostream>
using namespace std;

int FindMin(int A[], int n){
 int min = A[0];
 for(int i = 1; i <= n-1; i++){
    if (A[i] < min){
        cout << "indeks : "<< A[i] << endl;
        cout << "nilai min : "<< min << endl;
        min = A[i];
    }
 }
 return min;
}

int main(){
    int A[] = {1, 1, 2, 3, 5, 8, 13, 21} ;
    int n = sizeof(A) / sizeof(A[0]);
    int indexmin;

    cout << "nilai minimum : " << FindMin(A, n) << endl;
    cout << "indeks minimum : " << indexmin << endl;

    return 0;
}

/*

| Pseudocode        | Cost | Tmin  | Tmax   |
| :---------------- | :--- | :---- | :----- |
| procedure findMin | c1   | 1     | 1      |
| min <- A[0]       | c2   | 1     | 1      |
| for i <- 1 to n-1 | c3   | n     | n      |
| if A[i] < min     | c4   | n-1   | n-1    |
| min <- A[i]       | c5   | 0     | n-1    |
| end if            | c6   | n-1   | n-1    |
| end for           | c7   | n     | n      |
| return min        | c8   | 1     | 1      |
| end procedure     | c9   | 1     | 1      |
| Total Waktu              | O(n)  | O(n)

best case  = c1 + c2 + c3n + c4n-c4 + 0 + c6n-c6 + c7n + c8 + c9
           = (c3+c4+c6+c7)n + (c1+c2+c8+c9-c4-c6)
           = (1+1+1+1)n + (1+1+1+1-1-1)
           = 4n + 2

worst case = c1 + c2 + c3n + c4n-c4 + c5n-c5 + c6n-c6 + c7n + c8 + c9
           = (c3+c4+c5+c6+c7)n + (c1+c2+c8+c9-c4-c5-c6)
           = (1+1+1+1+1)n + (1+1+1+1-1-1-1)
           = 5n+1

dalam notasi Big-O, keudanya O(n)

*/