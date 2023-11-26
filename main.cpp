#include <iostream>

using namespace std;

const int LENGTH = 7;

void fillarray(int arr1[], int length) {
    for (int i = 0; i < length; i++) {
        arr1[i] = rand() % 10;
    }
}

void printarray(int arr[], int length) {
    /*
    Число в массиве записано задом наперед
    */
    for (int i = length - 1 ; i >= 0; i--) {
        cout << arr[i] << "";
    }

    cout << endl;
}

int get_number_length(int arr[], int arr_len) {
    for (int i = arr_len-1; i >= 0; i--) {
        if (arr[i]) {
            return i+1;
        }
    }

    return 1;
}

void normalize(int arr[], int len) {
    for (int i = 0; i < len - 1; ++i) {
        if (arr[i] >= 10) { 
            int transfer = arr[i] / 10;
            arr[i + 1] += transfer;
            arr[i] -= transfer * 10;
        }
        else if (arr[i] < 0) { 
            arr[i] += 10;
            arr[i + 1] -= 1;
        }
    }
}

void sum(int arr1[], int arr2[], int res[], int length) {
    for (int i = 0; i < length; i++) {
        res[i] = (arr1[i] + arr2[i]);
    }

    normalize(res, length+1);
}

void minusA(int arr1[], int arr2[], int res[], int len) {

    for (int i = 0; i < len; i++) {
        res[i] = arr1[i] - arr2[i];
    }

    normalize(res, len);
}

void karatsubaMultiply(int num1[], int num2[], int result[], int len) {
    if (len == 1) {


        for (int i = 0; i < get_number_length(num1, len); i++) {
            for (int j = 0; j < get_number_length(num2, len); j++) {
                result[i + j] += num1[i] * num2[j];
            }
        }

        normalize(result, LENGTH*2);
        return;
    }

    int a[LENGTH] = { 0 };
    int b[LENGTH] = { 0 };
    int c[LENGTH] = { 0 };
    int d[LENGTH] = { 0 };

    for (int i = 0; i < len / 2; i++) {
        b[i] = num1[i];
        d[i] = num2[i];
    }

    for (int i = len /2; i < len; i++) {
        a[i - (len /2)] = num1[i];
        c[i - (len /2)] = num2[i];
    }

    int ac[LENGTH * 2] = {0};
    int bd[LENGTH * 2] = {0};
    int ApB[LENGTH * 2] = {0};
    int CpD[LENGTH * 2] = {0};
    int ApBCpD[LENGTH * 2] = {0};
    int ApBCpDminACminBD[LENGTH * 2] = {0};
    int temp[LENGTH * 2] = {0};

    karatsubaMultiply(a, c, ac, max(get_number_length(a, LENGTH), get_number_length(c, LENGTH)));

    karatsubaMultiply(b, d, bd, len/2);

    sum(a, b, ApB, len);
    sum(c, d, CpD, len);

    karatsubaMultiply(ApB, CpD, ApBCpD, max(get_number_length(ApB, (len-len/2)+1), get_number_length(CpD, (len-len/2)+1)));
    
    minusA(ApBCpD, ac, temp, len*2);

    minusA(temp, bd, ApBCpDminACminBD, len*2);

    for (int i = 0; i < get_number_length(bd, (len/2)*2+1); i++) {
        result[i] += bd[i];
    }

    for (int i = 0; i <get_number_length(ApBCpDminACminBD, LENGTH * 2); i++) {
        result[i + len/2] += ApBCpDminACminBD[i];
    }

    for (int i = 0; i < get_number_length(ac, LENGTH*2); i++) {
        result[i + (len/2)*2] += ac[i];
    }

    normalize(result, LENGTH * 2);
}


int main() {
    srand(time(NULL));

    int length = LENGTH;

    int res[LENGTH * 2] = {0};


    int arr1[LENGTH] = {0};
    int arr2[LENGTH] = {0};

    fillarray(arr1, length);
    fillarray(arr2, length);

    cout << "First array: " << endl;
    printarray(arr1, length);
    cout << endl;

    cout << "second array: " << endl;
    printarray(arr2, length);
    cout << endl;

    karatsubaMultiply(arr1, arr2, res, LENGTH);

    cout << "Karatsuba result: " << endl;
    printarray(res, LENGTH*2);

}
