/*
    POSTTEST 5
    Nama    : Aziizah Oki Shofrina
    NIM     : 2109106004
    Kelas   : Informatika A'21
*/

// include library
#include <iostream>
#include <string>
#include <windows.h>    // system()
#include <iomanip>      // setw()
#include <conio.h>      // getch()

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
void swap(Song *elemen1, Song *elemen2);
void bubbleSortJudul(Song array[], const char* mode);
void insertionSortArtis(Song array[], const char* mode);
int partitionAlbum(Song arr[], int low, int high, const char* mode);
void quickSortAlbum(Song arr[], int low, int high, const char *mode);
void selectionSortTahun(Song array[], const char *mode);

// tampilan program
void tampilanAwal();
void tampilkanPilihanDaftar(Song arrayLagu[]);
void tampilkanDaftarLagu(Song arrayLagu[], int indexAwal, const char* indikator, const char* mode="ASC", const char* warning="");
void tampilkanLagu(Song arrayLagu[], Song lagu, const char* indikator, int warningColor=14);
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
        
        char opsi = getch();    // opsi yg dipilih user

        // pilihan menu
        switch (opsi) {

        // keluar dari program
        case 's':
            pintuKeluar();
            running = false;
            break;

        // tampilkan playlist
        case 'd':
            tampilkanPilihanDaftar(songs);
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

        warning = "";   // reset warning

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
    for (int i=0; i<STORAGE; i++){
        if (arrayLagu[i].title == ""){
            return i;
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


/*--------------------------------  SORTING  -------------------------------- */
// tukar data
void swap(Song *elemen1, Song *elemen2) {
    Song temp = *elemen1;
    *elemen1 = *elemen2;
    *elemen2 = temp;
}

// sorting berdasarkan judul
void bubbleSortJudul(Song array[], const char* mode){
    Song temp;
    int length = panjangArray(array);
    for (int i=0; i<length-1; i++){
        for (int j=0; j<length-1; j++){
            // ascending
            if(
                array[j].title.compare(array[j+1].title) > 0
                && mode == "ASC"
            ){
                temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }

            // descending
            if (
                array[j].title.compare(array[j+1].title) < 0
                && mode == "DESC"
            ){
                temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            } // end if
        } // end for
    } // end for 
} // end function

// sorting berdasarkan artis
void insertionSortArtis(Song array[], const char *mode){
    Song key;
    int i, j,
        length = panjangArray(array);

    for (i = 1; i < length; i++) {

        key = array[i];
        j = i-1;

        // ascending
        if (mode == "ASC") {
            while (j >= 0 && array[j].artist > key.artist){
                array[j+1] = array[j];
                j = j-1;
            }

        // descending
        } else {
            while (j >= 0 && array[j].artist < key.artist){
                array[j+1] = array[j];
                j = j-1;
            }
        }

        array[j+1] = key;
    }
}

// sorting berdasarkan album
int partitionAlbum(Song arr[], int low, int high, const char *mode) {
    string pivot = arr[high].album;
    int i = (low - 1);
    for (int j = low; j <= high- 1; j++) {

        // ascending
        if (
            arr[j].album.compare(pivot) <= 0
            && mode == "ASC"
        ) {
            i++;
            swap(&arr[i], &arr[j]);
        }

        // descending
        if (
            arr[j].album.compare(pivot) >= 0
            && mode == "DESC"
        ) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
void quickSortAlbum(Song arr[], int low, int high, const char *mode) {
    if (low < high) {
        int pi = partitionAlbum(arr, low, high, mode);
        quickSortAlbum(arr, low, pi - 1, mode);
        quickSortAlbum(arr, pi + 1, high, mode);
    }
}

// sorting berdasarkan tahun
void selectionSortTahun(Song array[], const char *mode) {
    bubbleSortJudul(array, mode);
    int indexMin,
        length = panjangArray(array);

    for (int i = 0; i < length-1; i++) {
        indexMin = i;

        for (int j = i+1; j < length; j++){
            
            // ascending
            if (
                array[j].year <= array[indexMin].year
                && mode == "ASC"
            ){
                indexMin = j;
                swap(&array[indexMin], &array[i]);
            }

            // descending
            if (
                array[j].year >= array[indexMin].year
                && mode == "DESC"
            ){
                indexMin = i;
                swap(&array[indexMin], &array[j]);
            }
        }
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

// menu pilihan sorting
void tampilkanPilihanDaftar(Song arrayLagu[]){
    const char *warning = "";

    refresh :
    bool run = true;
    while(run){
        system("cls");
        cout << endl << endl;

        // peringatan
        warnaText(12); 
        cout << "\t" << warning << "\n" << endl; 
        warnaText(7);

        // tampilan menu
        cout << "\tDaftar lagu berdasarkan :\n\n"
            << "\t[1] Judul \t [3] Album\n\n"
            << "\t[2] Artis \t [4] Tahun\n\n";

        cout << "\n\t<= Kembali ";
        warnaText(8);
        cout << "[a]" << endl;
        warnaText(7);

        // input menu yg diinginkan
        char opsi = getch();

        // menu yg tersedia
        switch (opsi) {

            // berdasarkan judul
            case '1':
                tampilkanDaftarLagu(arrayLagu, 0, "Judul");
                break;

            // berdasarkan artis
            case '2':
                tampilkanDaftarLagu(arrayLagu, 0, "Artis");
                break;

            // berdasarkan album
            case '3':
                tampilkanDaftarLagu(arrayLagu, 0, "Album");
                break;

            case '4':
                tampilkanDaftarLagu(arrayLagu, 0, "Tahun");
                break;

            // kembali ke menu sebelumnya
            case 'a':
                run = false;
                break;

            // opsi tidak ada
            default:
                warning = "Opsi tidak tersedia!";
                goto refresh;
                break;
        } // end switch

        warning = "";

    }   

}

// sorting berdasarkan judul, artis, album, tahun
void tampilkanDaftarLagu(Song arrayLagu[], int indexAwal, const char* indikator, const char* mode, const char* warning) {
    system("cls");
    cout << endl << endl;

    // peringatan
    warnaText(12); 
    cout << "\t" << warning << "\n" << endl; 
    warnaText(7);

    // mode pengurutan asc/desc
    warnaText(5);
    cout << "\t" << mode << " ";
    warnaText(8);
    cout << "('SPACE' untuk mengganti mode)" << endl;
    warnaText(7);

    int page = int(indexAwal/10 + 1);
    cout << "\tDaftar lagu tersimpan :";
    warnaText(14);
    cout << "\t\t\tPage "<< page << endl;
    warnaText(7);

    int indexMax = panjangArray(arrayLagu)-1;

    // indikator pengurutan
    // berdasarkan judul
    if (indikator == "Judul"){
        bubbleSortJudul(arrayLagu, mode);
       
        // tampilan daftar lagu
        for (int i=indexAwal; i<indexAwal+10; i++){
            cout << "\t(" << i+1 << "). " 
                << arrayLagu[i].title << endl;
        }

    // berdasarkan artis
    } else if (indikator == "Artis"){
        insertionSortArtis(arrayLagu, mode);

        // tampilan daftar lagu
        for (int i=indexAwal; i<indexAwal+10; i++){
            cout << "\t(" << i+1 << "). ";
            
            if (arrayLagu[i].title == ""){
                cout << endl;
            } else {
                cout << arrayLagu[i].artist << " - " << arrayLagu[i].title << endl;
            }

        }

    // berdasarkkan album
    } else if (indikator == "Album"){
        quickSortAlbum(arrayLagu, 0, indexMax, mode);

        // tampilkan daftar lagu
        for (int i=indexAwal; i<indexAwal+10; i++){
            cout << "\t(" << i+1 << "). ";

            if (arrayLagu[i].title == ""){
                cout << endl;
            } else {
                cout << arrayLagu[i].album << " - " << arrayLagu[i].title << endl;
            }

        }
    
    // berdasarkan tahun
    } else if (indikator == "Tahun"){
        selectionSortTahun(arrayLagu, mode);

        // tampilkan daftar lagu
        for (int i=indexAwal; i<indexAwal+10; i++){
            cout << "\t(" << i+1 << "). ";

            if (arrayLagu[i].title == ""){
                cout << endl;
            } else {
                cout << arrayLagu[i].year << " - " << arrayLagu[i].title << endl;
            }

        }
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
    
    // menu yg tersedia
    switch (opsi) {

        // kembali ke menu awal
        case 's': ;
            break;

        // pilih lagu
        case 'w':
            int nomor;
            
            cout << "\n\tNomor lagu\t: "; cin >> nomor;

            cin.clear();
            cin.ignore();
            fflush(stdin);

            if (
                nomor > STORAGE-1
                || nomor <= 0 
                || arrayLagu[nomor-1].title == "" 
            ){
                tampilkanDaftarLagu(
                    arrayLagu, 
                    indexAwal,
                    indikator,
                    mode, 
                    "Nomor tidak valid!"
                );
            } else {
                tampilkanLagu(
                    arrayLagu, 
                    arrayLagu[nomor-1],
                    indikator
                );
            }
            break;

        // ke page sebelumnya
        case 'a':
            if (page > 1) {
                tampilkanDaftarLagu(
                    arrayLagu, 
                    indexAwal-10,
                    indikator,
                    mode
                );
            } else {
                tampilkanDaftarLagu(
                    arrayLagu, 
                    indexAwal, 
                    indikator,
                    mode, 
                    "Ini adalah awal halaman!"
                );
            }
            break;

        // ke page selanjutnya
        case 'd':
            if (page < STORAGE/10) {
                tampilkanDaftarLagu(
                    arrayLagu, 
                    indexAwal+10,
                    indikator,
                    mode
                );

            } else {
                tampilkanDaftarLagu(
                    arrayLagu, 
                    indexAwal, 
                    indikator,
                    mode, 
                    "Ini adalah akhir halaman!"
                );
            }
            break;

        // ganti mode sorting
        case ' ':
            if (mode == "ASC"){
                mode = "DESC";
            } else {
                mode = "ASC";
            }
            tampilkanDaftarLagu(
                arrayLagu, 
                indexAwal, 
                indikator,
                mode
            );
            break;

        // opsi tidak ada
        default:
            tampilkanDaftarLagu(
                arrayLagu, 
                indexAwal, 
                indikator,
                mode, 
                "Opsi tidak tersedia!"
            );
            break;
    }
}

// rincian lagu tertentu
void tampilkanLagu(Song arrayLagu[], Song lagu, const char* indikator, int warningColor){
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
            tampilkanDaftarLagu(arrayLagu, 0, indikator);
            break;

        // hapus lagu
        case '\b':
            arrayLagu = hapusLagu(arrayLagu, index);
            tampilkanDaftarLagu(arrayLagu, 0, indikator);
            break;

        // kembali ke menu
        case 'a':
            tampilkanDaftarLagu(arrayLagu, 0, indikator);
            break;
        
        // opsi tidak ada
        default:
            tampilkanLagu(arrayLagu, lagu, indikator, 12);
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

    // tanda sudah berhasil
    warnaText(10);
    cout << "\n\tLagu baru berhasil ditambahkan!" << endl;
    warnaText(7);

    getch();

    return laguBaru;

}













