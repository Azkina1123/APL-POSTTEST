/*
    POSTTEST 4
    Nama    : Aziizah Oki Shofrina
    NIM     : 2109106004
    Kelas   : Informatika A'21
*/

// include library
#include <iostream>
#include <string>
#include <windows.h>
#include <iomanip>
#include <conio.h>

using namespace std;

// penyimpanan yg disediakan
const int STORAGE = 70;

// struct Song
struct Song{
    string title;
    string artist;
    string album;
    float duration;             // menit
    string genre[3];
    unsigned int year;  
};

// fungsi yg digunakan
void warnaText(unsigned short kodeWarna);
int panjangArray(Song[]);
int indexElemen(Song arrayLagu[], Song lagu);
void swap(Song *lagu1, Song *lagu2);
int partition(Song arr[], int low, int high);
void quickSort(Song arr[], int low, int high);

// tampilan program
void tampilanAwal();
void tampilkanDaftarJudul(Song arrayLagu[], int indexAwal, string warning="");
void tampilkanLagu(Song arrayLagu[], Song lagu, int warningColor=14);
void pintuKeluar();

// ubah data lagu
Song *editLagu(Song arrayLagu[], int index);
Song *hapusLagu(Song arrayLagu[], int index);
Song tambahLagu(Song arrayLagu[], int index);


/*--------------------------------  PROGRAM UTAMA  -------------------------------- */
int main(){
    // data yg tersimpan
    Song songs[STORAGE] = {
        {"Dying Every Second", "YongYong", "Dying Every Second", 3.0f, {"Rap/Hip Hop", "K-Pop"}, 2022},
        {"Stand Out Fit In", "ONE OK ROCK", "Eye of the Storm", 3.58f, {"Rock"}, 2019},
        {"Bottom of the Ocean", "Golden Child", "Game Changer", 3.51f, {"Dance/Electronic", "K-Pop"}, 2021},
        {"Gyutto", "Mosawo", "Gyutto", 4.0f, {"J-Pop"}, 2020},
        {"Silent Scream", "Anna Blue", "IN2 MINDS", 3.67f, {"Pop"}, 2017},
        {"Hot Air Balloon", "Owl City", "Ocean Eyes", 3.58f, {"Dance/Electronic"}, 2009},
        {"Eternal Flame", "Pentagon", "Eternal Flame", 3.76f, {"Pop"}, 2020},
        {"One Day", "Produce 101 Japan Season 2", "FINAL", 4.43f, {"Dance"}, 2021},
        {"Forget Me Not", "Enhypen", "Border : Hakanai", 3.38f, {"Dance/Electronic"}, 2021},
        {"Memories", "High Tension", "Memories", 3.36f, {"Dance/Electronic"}, 2020},
        {"SOS", "End of the World", "Eye", 5.38f, {"J-Pop"}, 2019},
        {"For the Hopeless", "The Years Gone By", "Something You Know Nothing About", 2.93f, {"Rock"}, 2009},
        {"All Day", "Cody Simpson", "Coast to Coast", 3.15f, {"R&B/Soul, Pop, UK R&B"}, 2011},
        {"Force", "Tomorrow X Together", "Still Dreaming", 3.98f, {"Dance/Electronic"}, 2021},
        {"Into Bloom", "N.Flying", "TURBULENCE", 3.18f, {"K-pop"}, 2021},
        {"My Gravity", "Yezi", "My Gravity", 3.85f, {"Dance/Electronic", "Pop", "K-Pop"}, 2020}
    };

    // tampilan awal program
    tampilanAwal();

    // keterangan
    bool running = true;
    string warning = "";

    while (running){

        // refresh halaman
    	refresh:
    		
        system("cls"); 
        cout << endl << endl << endl;

        // jumlah data tersimpan
        int length = panjangArray(songs);

        // urutkan array berdasarkan judul
        quickSort(songs, 0, length-1);   
        cout << "\tTerdapat " << length << " lagu yang tersimpan pada playlist." << endl;

        // peringatan
        warnaText(12);
        cout << "\n\t\t   " << warning << "\n" << endl;
        warnaText(7);

        // tampilan menu
        cout << "\t<= Tambah lagu                 Daftar lagu =>" << "\n";
        warnaText(8);
        cout << "\t       [a]                         [d]       " << "\n"; warnaText(7);
        cout << "\t                    Keluar                  " << "\n";
        warnaText(8);
        cout << "\t                      [s]                   " << "\n"; warnaText(7);
        char opsi = getch();

        // pilihan menu
        switch (opsi) {

        // keluar dari program
        case 's':
            pintuKeluar();
            running = false;
            break;

        // tampilkan playlist
        case 'd':
            tampilkanDaftarJudul(songs, 0);
            break;

        // tambah lagu baru
        case 'a':
            songs[length] = tambahLagu(songs, length-1);
            break;

        // opsi tidak ada
        default:
            warning = "Opsi tidak tersedia!";
            goto refresh;
            break;

        } // end switch

        warning = "";

    } // end while

    return 0;
}


/*--------------------------------  FUNGSI  -------------------------------- */

// atur warna teks
void warnaText(unsigned short kodeWarna) {
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon, kodeWarna);
}

// jumlah data tersimpan
int panjangArray(Song arrayLagu[]){
    int length;
    for (int i=0; i<STORAGE; i++){
        if (arrayLagu[i].title == ""){
            length = i;
            return length;
        }
    }

    return STORAGE;
}

// cari index elemen tertentu
int indexElemen(Song arrayLagu[], Song lagu){
    for (int i=0; i<STORAGE; i++){
        if (arrayLagu[i].title == lagu.title){
            return i;
        }
    }
    return -1;
}

// menukar data
void swap(Song *lagu1, Song *lagu2){
    Song t = *lagu1;
    *lagu1 = *lagu2;
    *lagu2 = t;
}

int partition (Song arr[], int low, int high) {
    string pivot = arr[high].title;
    int i = (low - 1);
    for (int j = low; j <= high- 1; j++) {
        if (arr[j].title <= pivot) {
        i++;
        swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(Song arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

/*--------------------------------  TAMPILAN  -------------------------------- */

// tampilan awal program
void tampilanAwal(){
    ulang:
    system("cls");

    cout << endl << endl << endl;

    cout << setw(47) << "=-----------------------------=" << "\n"
         << setw(47) << ":                             :" << "\n"
         << setw(47) << ":        SONG PLAYLIST        :" << "\n"
         << setw(47) << ":                             :" << "\n"
         << setw(47) << ":             ***             :" << "\n"
         << setw(47) << ":                             :" << "\n"
         << setw(19) << ":  ";
         
    warnaText(14);
	cout << "Tekan SPACE untuk memulai";
	warnaText(7);
	
	cout << "  :" << "\n"
         << setw(47) << ":                             :" << "\n"
         << setw(47) << "=-----------------------------=" << "\n";
        
    char respon = getch();

    // selama tidak tekan SPACE
    if (respon != ' '){
        goto ulang;
    }
}

// list lagu tersimpan
void tampilkanDaftarJudul(Song arrayLagu[], int indexAwal, string warning) {
    system("cls");
    cout << endl << endl;

    // peringatan
    warnaText(12); 
    cout << "\t" << warning << "\n" << endl; 
    warnaText(7);

    int page = int(indexAwal/10 + 1);
    cout << "\tDaftar lagu tersimpan :";
    warnaText(14);
    cout << "\t\t\tPage "<< page << endl;
    warnaText(7);

    // tampilan daftar lagu
    for (int i=indexAwal; i<indexAwal+10; i++){
        cout << "\t(" << i+1 << "). " 
            << arrayLagu[i].title << endl;
    }

    // tampilan menu
    cout << "\n\t\t\tPilih lagu ";
    warnaText(8);
    cout << "\n\t\t\t    [w] ";
    warnaText(7);

    cout << "\n\t<= Prev page\t\t\t Next page =>";
    warnaText(8);
    cout << "\n\t      [a]   \t\t\t    [d]";
	warnaText(7);

	cout << "\n\t\t\t  Kembali" ;
	warnaText(8);
	cout << "\n\t\t\t    [s]     " << endl;
	warnaText(7);

    char opsi = getch();
    int index = panjangArray(arrayLagu)-1;

    // menu yg tersedia
    switch (opsi) {

        // kembali ke menu awal
        case 's': 
            break;

        // pilih lagu
        case 'w':
            int nomor;
            cout << "\n\tNomor lagu\t: "; cin >> nomor;

            if (
                nomor > STORAGE-1
                || nomor <= 0 
                || arrayLagu[nomor-1].title == "" 
            ){
                tampilkanDaftarJudul(
                    arrayLagu, 
                    indexAwal, 
                    "Nomor tidak valid!"
                );
            } else {
                tampilkanLagu(
                    arrayLagu, 
                    arrayLagu[nomor-1]
                );
            }
            break;

        // ke page sebelumnya
        case 'a':
            if (page > 1) {
                tampilkanDaftarJudul(
                    arrayLagu, 
                    indexAwal-10
                );
            } else {
                tampilkanDaftarJudul(
                    arrayLagu, 
                    indexAwal, 
                    "Ini adalah awal halaman!"
                );
            }
            break;

        // ke page selanjutnya
        case 'd':
            if (page < STORAGE/10) {
                tampilkanDaftarJudul(
                    arrayLagu, 
                    indexAwal+10
                );

            } else {
                tampilkanDaftarJudul(
                    arrayLagu, 
                    indexAwal, 
                    "Ini adalah akhir halaman!"
                );
            }
            break;

        // opsi tidak ada
        default:
            tampilkanDaftarJudul(
                arrayLagu, 
                indexAwal, 
                "Opsi tidak tersedia!"
            );
            break;
    }

}

// rincian lagu tertentu
void tampilkanLagu(Song arrayLagu[], Song lagu, int warningColor) {
    system("cls");
    cout << endl << endl;

    // menu kembali
    cout << "\t<= BACK";
    warnaText(8);
    cout << " [a]  \n\n" << endl;
    warnaText(7);

    // rincian lagu
    cout << "\tJudul\t: " << lagu.title << "\n\n"
         << "\tArtis\t: " << lagu.artist << "\n\n"
         << "\tAlbum\t: " << lagu.album << "\n\n"
         << "\tDurasi\t: " << lagu.duration << " menit\n\n"
         << "\tGenre\t: ";

    for (int i=0; i<3; i++){
        cout << lagu.genre[i] << " ";
    }
    
    cout << "\n\n\tTahun\t: " << lagu.year << "\n\n" 
         << endl;

    // tanda peringatan
    warnaText(warningColor);
    cout << "\t#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#\n" << endl;
    warnaText(7);

    // tampilan menu
    cout << "\t  Edit rincian lagu \t Hapus rincian lagu  " << endl;
    warnaText(8);
    cout << "\t        [tab]       \t   [backspace] " << endl;
    warnaText(7);

    char opsi = getch(); 
    int index = indexElemen(arrayLagu, lagu);

    // menu yg tersedia
    switch(opsi){
        
        // edit lagu
        case '\t':
            arrayLagu = editLagu(arrayLagu, index);
            tampilkanDaftarJudul(arrayLagu, 0, "");
            break;

        // hapus lagu
        case '\b':
            arrayLagu = hapusLagu(arrayLagu, index);
            tampilkanDaftarJudul(arrayLagu, 0, "");
            break;

        // kembali ke menu
        case 'a':
            tampilkanDaftarJudul(arrayLagu, 0, "");
            break;
        
        // opsi tidak ada
        default:
            tampilkanLagu(arrayLagu, lagu, 12);
            break;
    } // end switch
    
}

// penutup program
void pintuKeluar() {
    system("cls");
    cout << endl << endl << endl << endl;

    // pemberitahuan berhasil
    warnaText(14);
    cout << "\t Terima kasih telah menggunakan program.\n";
    warnaText(7);

    getch();
}

// edit rincian lagu
Song *editLagu(Song arrayLagu[], int index) {
    int warningColor = 7;

    refresh :
    system("cls");
    cout << endl << endl; 
    fflush(stdin);

    // judul halaman
    cout << "\t\tEdit Rincian Lagu\n"
         << "\t\t-----------------\n"
         << endl;

    // judul lagu
    warnaText(warningColor);
    cout << "\tJudul lagu\t-> " << arrayLagu[index].title << endl;
    warnaText(11);
    cout << "\t          \t-> ";
    getline(cin, arrayLagu[index].title); fflush(stdin);
    warnaText(7);

    // judul lagu tidak boleh kosong
    if (arrayLagu[index].title == ""){
        warningColor = 12;
        goto refresh;
    }

    // artis
    cout << "\n\tArtis\t\t-> " << arrayLagu[index].artist << endl;
    warnaText(11);
    cout << "\t     \t\t-> ";
    getline(cin, arrayLagu[index].artist); fflush(stdin);
    warnaText(7);
    
    // album
    cout << "\n\tAlbum\t\t-> " << arrayLagu[index].album << endl;
    warnaText(11);
    cout << "\t     \t\t-> ";
    getline(cin, arrayLagu[index].album); fflush(stdin);
    warnaText(7);
    
    // durasi
    cout << "\n\tDurasi\t\t-> " << arrayLagu[index].duration << endl;
    
    // genre
    warnaText(8);
    cout << "\n\t(Max 3 genre)" << endl;
    warnaText(7);

    cout << "\tGenre\t\t-> " 
         << arrayLagu[index].genre[0] << " " 
         << arrayLagu[index].genre[1] << " "
         << arrayLagu[index].genre[2] << " " 
         << endl;
    warnaText(11);
    for (int i=0; i<3; i++){
        cout << "\t\t\t-> ";
        getline(cin, arrayLagu[index].genre[i]); fflush(stdin);
    }    
    warnaText(7);
    
    // tahun
    cout << "\n\tTahun\t\t-> " << arrayLagu[index].year << endl;
    warnaText(11);
    cout << "\t     \t\t-> ";
    cin >> arrayLagu[index].year; fflush(stdin);
    warnaText(7);

    // urutkan ulang berdasarkan judul
    quickSort(arrayLagu, 0, panjangArray(arrayLagu)-1);
    
    // tanda sudah berhasil
    warnaText(10);
    cout << "\n\tRincian lagu telah berhasil diperbarui!" << endl;
    warnaText(7);

    getch();
    
    return arrayLagu;
}

// hapus lagu
Song *hapusLagu(Song arrayLagu[], int index) {
    for (int i=index; i<STORAGE; i++){
        if (i == STORAGE-1){
            arrayLagu[i] = {"", "", "", 0, {""}, 0};
        } 
        if (arrayLagu[i].title != ""){
            swap(arrayLagu[i], arrayLagu[i+1]); 
        } 
    }

    // urutkan ulang berdasarkan judul
    quickSort(arrayLagu, 0, panjangArray(arrayLagu)-1);

    // tanda sudah berhasil
    warnaText(10);
    cout << "\n\tLagu telah berhasil dihapus!" << endl;
    warnaText(7);

    getch();

    return arrayLagu;
}

// tambah lagu baru
Song tambahLagu(Song arrayLagu[], int index) {
    int warningColor = 7;       // warna peringatan 
    
    refresh:                    // refresh halaman

    system("cls");
    cout << endl << endl; 
    fflush(stdin);

    // judul halaman
    cout << "\t\tTambah Lagu Baru\n"
         << "\t\t----------------\n"
         << endl;

    Song laguBaru = arrayLagu[index];

    // judul lagu
    warnaText(warningColor);
    cout << "\tJudul lagu\t";
    warnaText(11);
    cout << "-> ";
    getline(cin, laguBaru.title); fflush(stdin);
    warnaText(7);

    // judul lagu tidak boleh kosong
    if (laguBaru.title == ""){
        warningColor = 12;
        goto refresh;
    }
    
    // artis
    cout << "\n\tArtis\t\t";
    warnaText(11);
    cout << "-> ";
    getline(cin, laguBaru.artist); fflush(stdin);
    warnaText(7);

    // album
    cout << "\n\tAlbum\t\t";
    warnaText(11);
    cout << "-> ";
    getline(cin, laguBaru.album); fflush(stdin);
    warnaText(7);

    // durasi
    cout << "\n\tDurasi\t\t";
    warnaText(11);
    cout << "-> ";
    cin >> laguBaru.duration; fflush(stdin);
    warnaText(7);

    // genre
    warnaText(8);
    cout << "\n\t(Max 3 genre)" << endl;
    warnaText(7);
    
    cout << "\tGenre\t\t: \n";
    warnaText(11);
    for (int i=0; i<3; i++){
        cout << "\t\t\t-> ";
        getline(cin, laguBaru.genre[i]); fflush(stdin);
    }  
    warnaText(7);
    
    // tahun
    cout << "\n\tTahun\t\t";
    warnaText(11);
    cout << "-> ";
    cin >> laguBaru.year; fflush(stdin);
    warnaText(7);

    // urutkan ulang berdasarkan judul
    quickSort(arrayLagu, 0, panjangArray(arrayLagu)-1);

    // tanda sudah berhasil
    warnaText(10);
    cout << "\n\tLagu baru berhasil ditambahkan!" << endl;
    warnaText(7);

    getch();

    return laguBaru;

}













