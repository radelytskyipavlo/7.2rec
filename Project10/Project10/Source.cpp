#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

void CreateRow(int** a, const int rowNo, const int N, const int Low, const int High, int colNo) {
    a[rowNo][colNo] = Low + rand() % (High - Low + 1);
    if (colNo < N - 1)
        CreateRow(a, rowNo, N, Low, High, colNo + 1);
}

void CreateRows(int** a, const int N, const int Low, const int High, int rowNo) {
    CreateRow(a, rowNo, N, Low, High, 0);
    if (rowNo < N - 1)
        CreateRows(a, N, Low, High, rowNo + 1);
}

void PrintRow(int** a, const int rowNo, const int N, int colNo) {
    cout << setw(4) << a[rowNo][colNo];
    if (colNo < N - 1)
        PrintRow(a, rowNo, N, colNo + 1);
    else
        cout << endl;
}

void PrintRows(int** a, const int N, int rowNo) {
    PrintRow(a, rowNo, N, 0);
    if (rowNo < N - 1)
        PrintRows(a, N, rowNo + 1);
    else
        cout << endl;
}

void SearchFirstEven(int** a, const int N, int i, int& minEven, int& k) {
    if (a[i][i] % 2 == 0) {
        k = i;
        minEven = a[i][i];
        return;
    }
    if (i < N - 1)
        SearchFirstEven(a, N, i + 1, minEven, k);
}

void SearchMinEven(int** a, const int N, int i, int j, int& minEven, int& minRow, int& minCol) {
    if (a[i][j] % 2 == 0 && a[i][j] < minEven) {
        minEven = a[i][j];
        minRow = i;
        minCol = j;
    }
    if (i < N - 1 || j < N - 1) {
        if (j == N - 1) {
            SearchMinEven(a, N, i + 1, 0, minEven, minRow, minCol);
        }
        else {
            SearchMinEven(a, N, i, j + 1, minEven, minRow, minCol);
        }
    }
}

void SwapMinMaxInRows(int** a, const int N, int rowNo) {
    int maxElement = a[rowNo][0];
    int minElement = a[rowNo][0];
    int maxCol = 0, minCol = 0;

    for (int j = 1; j < N; ++j) {
        if (a[rowNo][j] > maxElement) {
            maxElement = a[rowNo][j];
            maxCol = j;
        }
        if (a[rowNo][j] < minElement) {
            minElement = a[rowNo][j];
            minCol = j;
        }
    }

    int temp = a[rowNo][maxCol];
    a[rowNo][maxCol] = a[rowNo][minCol];
    a[rowNo][minCol] = temp;

    if (rowNo < N - 1)
        SwapMinMaxInRows(a, N, rowNo + 1);
}

int main() {
    srand(static_cast<unsigned>(time(NULL)));

    int N;
    cout << "N: ";
    cin >> N;
    cout << endl;

    int** a = new int* [N];
    for (int i = 0; i < N; i++)
        a[i] = new int[N];

    int Low = -9, High = 9;
    CreateRows(a, N, Low, High, 0);

    cout << "Original:" << endl;
    PrintRows(a, N, 0);

    SwapMinMaxInRows(a, N, 0);

    cout << "Modified:" << endl;
    PrintRows(a, N, 0);

    for (int i = 0; i < N; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}
