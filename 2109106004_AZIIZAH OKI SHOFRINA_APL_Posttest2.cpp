/*
    POSTTEST 2
    Nama    : Aziizah Oki Shofrina
    NIM     : 2109106004
    Kelas   : Informatika A'21
*/

// include library
#include <iostream>
#include <cstdlib> // system("cls")
#include <cmath> // pow(bil, pangkat)
#include <iomanip> // setw(int) --> atur lebar sebanyak int

using namespace std;

int fungsi(int x, int y){
    /*
    variabel  = x, y
    koefisien = 1/2, -5
    konstanta = 0, 4
    */
    return x/2 - 5*y + 0 + 4;
}

int main(){
    // bersihkan terminal
    system("cls");

    // judul
    cout << setw(58);
    cout << "=========================================" << endl;
    cout << setw(58);
    cout << "Menampilkan Array 2 Dimensi dan Alamatnya" << endl;
    cout << setw(58);
    cout << "=========================================" << endl;

    cout << endl;

    // deklarasi array
    int aziizah_04[5][5];
    
    // subjudul 1
    cout << setw(52);
    cout << "Array Hasil Perhitungan Fungsi" << endl;
    cout << setw(50);
    cout << "f(x, y) = x/2 - 5*y + 0 + 4" << endl;

    cout << endl;

    // masukkan elemen
    for (int x=0; x<5; x++){                // dimensi 1
        for (int y=0; y<5; y++){            // dimensi 2
            aziizah_04[x][y] = fungsi(x, y);
        }
    }

    // deklarasi pointer
    int *ptr = &aziizah_04[0][0];

    // menampilkan elemen array
    for (int x=0; x<5; x++){
        cout << setw(26) << "[" << setw(4);
        for (int y=0; y<5; y++){
            cout << *ptr << setw(4);
            ptr++;
        }
        cout << "]" << endl;
    }

    cout << endl << endl;

    // subjudul 2
    cout << setw(50);
    cout << "Alamat dari Elemen Array" << endl;
 
    cout << endl;
    
    // menampilkan alamat elemen array
    for (int x=0; x<5; x++){
        cout << setw(4) << "[  ";
        for (int y=0; y<5; y++){
            cout << ptr << "  ";
            ptr++;
            
        }
        cout << "]" << endl;
    }

    cout << endl;

    return 0;
}
