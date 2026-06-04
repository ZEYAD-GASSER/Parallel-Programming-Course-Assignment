#include <omp.h>
#include <iostream>

using namespace std ;
const int MAX = 10;

int big(int j) {
    return j * 2;
}

int main() {
    int A[MAX];

    #pragma omp parallel for
    for (int i = 0; i < MAX; i++) {
        int j = 5 + 2 * (i + 1);
        A[i] = big(j);
    }

    for (int i = 0; i < MAX; i++) {
        cout << "A[" << i << "] = " << A[i] << "\n";
    }

    return 0;
}
