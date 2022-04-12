/*
    POSTTEST 1
    Nama    : Aziizah Oki Shofrina
    NIM     : 2109106004
    Kelas   : Informatika A'21
*/

// library utk input output
#include <iostream>
// libary utk clear terminal --> system("cls")
#include <cstdlib>
// library utk string
#include <string>

// menggunakan namespace std
using namespace std;

// membuat fungsi faktorial yg mereturn nilai bertipe int
int faktorial(int nilai){
    // jika nilai yg dimasukkan pada parameter == 1 atau == 0
    if (nilai == 1 || nilai == 0){
        return 1;
    // jika nilai yg dimasukkan adalah angka lainnya
    } else {
        return nilai*faktorial(nilai-1);
    }
}

// fungsi kombinasi
int kombinasi(int n, int r){
    return faktorial(n)/(faktorial(r)*faktorial(n-r));
}

// fungsi permutasi
int permutasi(int n, int r){
    return faktorial(n)/faktorial(n-r);
}

// prosedure program yg dipilih (kombinasi/permutasi)
void programPilihan(string program){
    // bersihkan terminal
    system("cls");
    
    // judul program
    cout << "Menentukan Hasil " << program << endl;
    cout << ".........................." << endl;
    
    // deklarasi var n, r
    int n, r; // n = byk objek yg tersedia, r = byk objek yg ingin dicari

    // masukkan nilai var n, r
    cout << "\nNilai n : "; cin >> n;
    cout << "Nilai r : "; cin >> r;

    // syarat n dan r yang dimasukkan
    if (n >= 0 && r >= 0 && r <= n){

        // hasil yg ditampilkan
        if (program == "Kombinasi"){
            cout << "\nHasil " << program << " = " << kombinasi(n, r) << endl;
        } else {
            cout << "\nHasil " << program << " = " << permutasi(n, r) << endl;
        }

    } else {
        cout << "\nHasil " << program << " tidak dapat\nditentukan." << endl;
    }

    // lanjutkan program ke langkah selanjutnya
    cin.ignore(1, '\n'); 
    cout << "\n\t\t    Next => "; cin.get();
}

// program utama
int main(){
    // inisialisasi running
    bool running = true;

    // selama running bernilai true, program dijalankan
    while (running){
        // bersihkan terminal
        system("cls");

        // judul program
        cout << "  =======================" << endl;
        cout << "  Kombinasi dan Permutasi" << endl;
        cout << "  =======================\n" << endl;

        // deklarasi var opsi, ulang
        char opsi, ulang;

        // opsi yg diinginkan
        cout << "Apa yang ingin Anda lakukan?" << endl;
        cout << "[1] Kombinasi  [2] Permutasi" << endl;
        cout << "  (Ketik '0' untuk keluar)" << endl;
        cout << "\n>> "; cin >> opsi;

        // menu yg dipilih
        switch (opsi){
        case '1':
            programPilihan("Kombinasi");
            break;

        case '2':
            programPilihan("Permutasi");
            break;

        case '0':
            running = false;
            break;

        default:
            // cin.ignore(int, char)
            cin.ignore(1, '\n');

            cout << "\n    Opsi tidak tersedia" << endl;
            cout << "\n\t\t    Next => "; cin.get();
            break;
        }   
    }

    // pernyataan program berhenti
    cout << "\n    Program dihentikan.\n" << endl;

    return 0;
}
