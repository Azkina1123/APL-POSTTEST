/*
    POSTTEST 3
    NAMA    : AZIIZAH OKI SHOFRINA
    NIM     : 2109106004
    KELAS   : INFORMATIKA A'21
*/


/* include library */
#include <iostream>
#include <iomanip>      // setw()
#include <windows.h>    // system("cls") dan HANDLE
#include <conio.h>      // getch()

using namespace std;    // std

/* prototype fungsi dan prosedur */
float tambah(float, float);                       // fungsi tambah
float tambah(float, float, float);

float kurang(float, float);                       // fungsi kurang
float kurang(float, float, float);

float kali(float, float);                         // fungsi kali
float kali(float, float, float);

float bagi(float, float);                         // fungsi bagi
float bagi(float, float, float);

int sisaBagi(int, int);                     // fungsi sisa bagi
int sisaBagi(int, int, int);

void warnaText(unsigned short);              // atur warna teks
char pilihOperator(int);                    // pilih operator
void halamanOperasi(int, string, char);     // halaman proses perhitungan
void duaAngka(char);                        // jika memilih 2 angka atau 2 parameter
void tigaAngka(char);                       // jika memilih 3 angka atau 3 parameter

/* program utama */
int main() {
    bool running = true;    
    int warning = 0;

    do {
        // pilih operator
        char opsi = pilihOperator(warning);

        switch (opsi) {
            
            // 1 = operator +
            case '1':
                halamanOperasi(0, "Penjumlahan", '+');
                break;
            
            // 2 = operator -
            case '2':
                halamanOperasi(0, "Pengurangan", '-');
                break;

            // 3 = operator *
            case '3':
                halamanOperasi(0, "Perkalian", '*');
                break;

            // 4 = operator /
            case '4':
                halamanOperasi(0, "Pembagian", '/');
                break;

            // 5 = operator /
            case '5':
                halamanOperasi(0, "Sisa pembagian", '%');
                break;

            // 0 = keluar dari program
            case '0':
                cout << endl;
                running = false;

            // opsi tidak tersedia
            default:
                warning = 1;
                break;
        }

    } while (running == true);

    // penutup
    warnaText(6); 
    cout << setw(50)
         << "Terima kasih telah menggunakan program." << endl
         << endl;
    warnaText(7);

    getch();

    return 0;
    
}


/* atur warna teks */
void warnaText(unsigned short color) {
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon, color);
}

/* fungsi tambah overloading */
float tambah(float bil1, float bil2) {
    return bil1 + bil2;
}
float tambah(float bil1, float bil2, float bil3) {
    return bil1 + bil2 + bil3;
}

/* fungsi kurang overloading */
float kurang(float bil1, float bil2) {
    return bil1 - bil2;
}
float kurang(float bil1, float bil2, float bil3) {
    return bil1 - bil2 - bil3;
}

/* fungsi kali overloading */
float kali(float bil1, float bil2) {
    return bil1 * bil2;
}
float kali(float bil1, float bil2, float bil3) {
    return bil1 * bil2 * bil3;
}

/* fungsi bagi overloading */
float bagi(float bil1, float bil2) {
    return bil1 / bil2;
}
float bagi(float bil1, float bil2, float bil3) {
    return bil1 / bil2 / bil3;
}

int sisaBagi(int bil1, int bil2) {
    return bil1 % bil2;
}
int sisaBagi(int bil1, int bil2, int bil3) {
    return bil1 % bil2 % bil3;
}


/* judul utama program */
void judulKalkulator() {
    cout << endl;

    warnaText(7);
    cout << setw(35) << "KALKULATOR\n" << endl;
}

/* kode warning untuk tiap halaman */
void cekWarning(int warning) {
    // kode warning == 1
    if (warning == 1){
        warnaText(4);
        cout << setw(40) << "Opsi tidak tersedia!\n" << endl;
        warnaText(7);

    // kode warning = 0
    } else {
        cout << setw(32) << "---\n" << endl;
    }
}

/* pilih operator */
char pilihOperator(int warning) {
    system("cls");

    // tampilkan judul
    judulKalkulator();

    // warning/pemberitahuan jika ada kesalahan
    cekWarning(warning);

    // petunjuk
    warnaText(6);
    cout << setw(46) << "Tekan angka opsi pilihan Anda!\n" << endl;
    warnaText(7);

    // pilihan/opsi
    cout << setw(51) << "Penjumlahan (+)   [1] [4]   (/) Pembagian \n"
         << setw(56) << "Pengurangan (-)   [2] [5]   (%) Sisa Pembagian \n"
         << setw(30) << "  Perkalian (*)   [3]\n" 
         << endl;

    // jika ingin keluar
    warnaText(8);
    cout << setw(42) << "(Tekan '0' untuk keluar)" << endl;
    warnaText(7);

    // kembalikan nilai opsi
    char opsi;
    opsi = getch();
    return opsi;
}

/* pilih banyak angka/parameter */
void halamanOperasi(int warning, string operasi, char simbol) {
    system("cls");

    // judul halaman
    judulKalkulator();
    cout << setw(33) << operasi << " ("<< simbol << ")\n" << endl;

    // warning/pemberitahuan
    cekWarning(warning);

    // pilihan banyak parameter
    warnaText(6); 
    cout << setw(51) << "Banyak angka yang ingin dioperasikan :\n" << endl; 
    warnaText(7);
    cout << setw(41) << "[ 2 ]    atau    [ 3 ]" << endl;

    // jika ingin keluar
    warnaText(8);
    cout << endl 
         << setw(42) << "(Tekan '0' untuk keluar)" << endl;
    warnaText(7);

    char opsi;
    opsi = getch();
    cout << endl;

    switch (opsi) {
    // 2 parameter
    case '2':
        duaAngka(simbol);
        break;
    
    // 3 parameter
    case '3':
        tigaAngka(simbol);
        break;

    // keluar
    case '0':
        break;
    
    // opsi tidak tersedia
    default:
        halamanOperasi(1, operasi, simbol);
        break;
    }
}

/* 2 angka atau 2 parameter */
void duaAngka(char simbol) {
    float bil1, bil2, hasil;     

    // formula operasi
    warnaText(1); 
    cout << setw(25) << "a";            // a
    warnaText(7);
    cout << " " << simbol << " ";       // operator
    warnaText(5); 
    cout << "b";                        // b
    warnaText(7);
    cout << " = ";                      // = 
    warnaText(2); 
    cout << "hasil\n" << endl;          // hasil
    warnaText(7);

    // masukkan parameter/angka yang dibutuhkan
    cout << setw(31) << "a = "; cin >> bil1;
    cout << setw(31) << "b = "; cin >> bil2;

    // operator yang sesuai
    if (simbol == '+'){
        hasil = tambah(bil1, bil2);
    
    } else if (simbol == '-'){
        hasil = kurang(bil1, bil2);
    
    } else if (simbol == '*'){
        hasil = kali(bil1, bil2);
    
    } else if (simbol == '%'){

        // jika pembagi tidak 0
        if (bil2 != 0){
            hasil = sisaBagi(bil1, bil2);
        }
    
    } else {
    
        // jika pembagi tidak 0
        if (bil2 !=0) {
            hasil = bagi(bil1, bil2);
        }
    }

    cout << endl;

    // tampilkan formula yang terbentuk
    warnaText(1);                           
    cout << setw(26) << bil1;               // bil1
    warnaText(7);
    cout << " " << simbol << " ";           // operator
    warnaText(5); 
    cout << bil2;                           // bil2
    warnaText(7);
    cout << " = ";                          // =

    // tampilkan hasil
    if (bil2 == 0 and simbol == '/' || bil2 == 0 and simbol == '%'){
        warnaText(2); 
        cout << "tak terdefinisi" << endl; 
        warnaText(7);
    } else {
        warnaText(2); 
        cout << hasil << endl; 
        warnaText(7);
    }

    // kembali ke menu utama
    warnaText(6);
    cout << endl
         << setw(46) << "Tekan ENTER untuk melanjutkan" << endl;
    getch();
    warnaText(7);
}

/* 3 angka atau 3 parameter */
void tigaAngka(char simbol) {
    float bil1, bil2, bil3, hasil;

    // formula operasi
    warnaText(1); 
    cout << setw(23) << "a";                // a
    warnaText(7);          
    cout << " " << simbol << " ";           // operator
    warnaText(5); 
    cout << "b";                            // b
    warnaText(7);            
    cout << " " << simbol << " ";           // operator           
    warnaText(3); 
    cout << "c";                            // c
    warnaText(7);
    cout << " = ";                          // =
    warnaText(2); 
    cout << "hasil\n" << endl;              // hasil
    warnaText(7);

    // masukkan parameter/angka
    cout << setw(31) << "a = "; cin >> bil1;
    cout << setw(31) << "b = "; cin >> bil2;
    cout << setw(31) << "c = "; cin >> bil3;
    
    // operator yang sesuai
    if (simbol == '+'){
        hasil = tambah(bil1, bil2, bil3);
    
    } else if (simbol == '-'){
        hasil = kurang(bil1, bil2, bil3);
    
    } else if (simbol == '*'){
        hasil = kali(bil1, bil2, bil3);
    
    } else if (simbol == '%'){

        if ((bil2 && bil3) != 0) {
            hasil = sisaBagi(bil1, bil2, bil3);
        }
    
    } else {
        
        if ((bil2 && bil3) != 0) {
            hasil = bagi(bil1, bil2, bil3);
        }
    }

    cout << endl;

    // tampilkan formula yang terbentuk
    warnaText(1);
    cout << setw(24) << bil1;               // bil1
    warnaText(7);
    cout << " " << simbol << " ";           // operator
    warnaText(5); 
    cout << bil2;                           // bil2
    warnaText(7);
    cout << " " << simbol << " ";           // operator
    warnaText(3); 
    cout << bil3;                           // bil3
    warnaText(7);
    cout << " = ";
    
    // tampilkan hasil                      // hasil
    if ((bil2 == 0 || bil3 == 0) && simbol == '/' \
    || (bil2 == 0 || bil3 == 0) && simbol == '%') {

        warnaText(2); 
        cout << "tak terdefinisi" << endl; 
        warnaText(7);

    } else {

        warnaText(2); 
        cout << hasil << endl; 
        warnaText(7);

    }

    warnaText(6);
    cout << endl
         << setw(46) << "Tekan ENTER untuk melanjutkan" << endl;
    getch();
    warnaText(7);
}



