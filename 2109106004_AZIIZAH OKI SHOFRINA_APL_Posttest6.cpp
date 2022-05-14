/*
    POSTTEST 6
    Nama    : Aziizah Oki Shofrina
    NIM     : 2109106004
    Kelas   : Informatika A'21
*/

// include library
#include <iostream>
#include <string>
#include <windows.h>    // system()
#include <iomanip>      // setw()
#include <conio.h>      // HANDLE

using namespace std;

// key pada keyboard
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

// menu yang dipilih
#define SELECT 9
#define UNSELECT 0
#define ENTER 13
#define RESET 7
#define MARKED 8

// penyimpanan yg disediakan
#define STORAGE 70

// struct Song
struct Song{
    string title;
    string artist;
    string album;
    float duration;             // menit
    string genre[3];
    unsigned int year;  
};

/*--------------------------------  PROTOTYPE  -------------------------------- */

// tampilan program
void tampilanAwal();                    
void tampilkanDaftarLagu();
void hasilPencarian(string cari, string atribut, Song arrayDitemukan[]);
void tampilkanLagu(Song arrayLagu[], Song lagu);
void pintuKeluar();

// ubah data lagu
Song *editLagu(Song arrayLagu[], int index);
Song *hapusLagu(Song arrayLagu[], int index);
Song tambahLagu(Song arrayLagu[], int index);

// sorting
void swap(Song *elemen1, Song *elemen2);
void sortJudul(string mode);
void sortArtis(string mode);
int partition(int low, int high, string mode);
void sortAlbum(int low, int high, string mode);
void sortTahun(string mode);

// searching
int searchJudul(int awal, string cari);
int searchArtis(int awal, string cari);
int searchAlbum(int awal, string cari);
int searchTahun(int awal, int cari);
bool dataDitemukan(int array[], int length, int cari);

// fungsi yg digunakan
void color(unsigned short kodeWarna);
int panjangArray(Song arrayLagu[]);
int indexLagu(Song lagu);
void gotoxy(int x, int y);
void clearCin();
void hapusTulisan();
bool isSpace(string str);
void listLagu(Song arrayLagu[], int awal, int akhir, string atribut, string mode="ASC");
void karakter(int ascii, int jumlah, int warna=7);
void notifHapus(int ya, int tidak);
bool formTerisi(Song lagu);
string lower(string str);

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


/*--------------------------------  PROGRAM UTAMA  -------------------------------- */

int main(){

    // tampilan awal program
    tampilanAwal();

    // var default
    bool running = true;
    short int opsi0 = UNSELECT,
              opsi1 = SELECT,
              opsi2 = UNSELECT; 

    while (running){
    		
        system("cls"); 
        cout << endl << endl << endl;

        // judul halaman
        cout << "\t"; karakter(178, 12, 5); 
        cout << "   Menu PLaylist   ";  karakter(178, 13, 5);
        cout << endl << endl;

        // keterangan
        int length = panjangArray(songs);    
        cout << "\t\t\b\bTerdapat " << length << " lagu yang tersimpan\n"
             << "\t\t\b\b        pada playlist.                     \n\n"; color(13);
        cout << "\t\t\b\b             ---                           \n\n"; 

        // tampilan menu
        cout << "\t      "; color(opsi1); cout << char(16); color(7); cout << " Daftar lagu   ";  // opsi 1   
        cout << "\t"      ; color(opsi2); cout << char(16); color(7); cout << " Tambah lagu\n\n"; // opsi 2
        cout << "\t      "; color(opsi0); cout << char(16); color(7); cout << " Keluar     \n\n"; // opsi 0
        
        char opsi, key;
        opsi = getch();    // opsi yg dipilih user

        // pilihan menu
        switch (opsi) {

            case ENTER:
                // keluar dari program
                if (opsi0 == SELECT) {
                    pintuKeluar();
                    running = false;
                    break;
                
                // tampilkan playlist
                } else if (opsi1 == SELECT) {
                    tampilkanDaftarLagu();

                // tambah lagu baru
                } else if (opsi2 == SELECT) {
                    songs[length] = tambahLagu(songs, length);
                }

                break;

            case -32:
                key = getch();

                // pilih opsi 0 - keluar
                if (
                    opsi1 == SELECT && key == DOWN ||
                    opsi2 == SELECT && key == DOWN
                ) {
                    opsi0 = SELECT;
                    opsi1 = UNSELECT;
                    opsi2 = UNSELECT;

                // pilih opsi 1 - tampilkan daftar
                } else if (
                    opsi2 == SELECT && key == LEFT ||
                    opsi0 == SELECT && key == UP   
                ) {
                    opsi0 = UNSELECT;
                    opsi1 = SELECT;
                    opsi2 = UNSELECT;
                
                // pilih opsi 2 - tambah lagu
                } else if (
                    opsi1 == SELECT && key == RIGHT ||
                    opsi0 == SELECT && key == RIGHT 
                ) {
                    opsi0 = UNSELECT;
                    opsi1 = UNSELECT;
                    opsi2 = SELECT;
                }

        } // end switch

    } // end while

    return 0;
}


/*--------------------------------  TAMPILAN  -------------------------------- */

// tampilan awal program
void tampilanAwal(){
    while (true) {
        system("cls");
        cout << endl << endl << endl;

        // bingkai
        color(13);
        cout << setw(15); karakter(176, 31, 13); cout << endl;
        cout << setw(15); karakter(176, 1, 13);  cout << setw(30); karakter(176, 1, 13); cout << endl;      
        cout << setw(15); karakter(176, 1, 13);  cout << setw(30); karakter(176, 1, 13); cout << endl;      
        cout << setw(15); karakter(176, 1, 13);  cout << setw(30); karakter(176, 1, 5); cout << endl;      
        cout << setw(15); karakter(176, 1, 13);  cout << setw(30); karakter(176, 1, 5); cout << endl;      
        cout << setw(15); karakter(176, 1, 13);  cout << setw(30); karakter(176, 1, 5); cout << endl;      
        cout << setw(15); karakter(176, 1, 5);  cout << setw(30); karakter(176, 1, 5); cout << endl;      
        cout << setw(15); karakter(176, 1, 5);  cout << setw(30); karakter(176, 1, 5); cout << endl;      
        cout << setw(15); karakter(176, 31, 5); cout << endl;
        
        // isi bingkai
        gotoxy(23, 5); color(5); cout << "SONG PLAYLIST";
        gotoxy(28, 7); color(9); cout << "***"; 
        gotoxy(17, 9); color(13); cout << "Tekan SPACE untuk memulai"; 

        cout << endl << endl << endl;
            
        char respon = getch();

        color(RESET);

        // jika tekan SPACE
        if (respon == 32){
            break;
        }

    }
}

// sorting berdasarkan judul, artis, album, tahun
void tampilkanDaftarLagu() {

    // var default
    bool openPage  = true;
    string warning = "",
           mode    = "ASC",
           atribut = "judul";
    short int indexAwal = 0,
              page,
              judul = SELECT,
              artis = UNSELECT,
              album = UNSELECT,
              tahun = UNSELECT,
              cari  = UNSELECT,
              nav   = UNSELECT;

    while (openPage) {
        system("cls"); 
        cout << endl << endl << endl; color(RESET);
        
        // sorting list berdasarkan atribut
        cout << "\tSorting berdasarkan :  "; color(5);
        cout << char(22) << " " << char(22) << " " << char(22) << " " << char(22) << " " << char(22) << " " << char(22) << " "; 
        cout << char(22) << " " << char(22) << " " << char(22) << " " << char(22) << " " << char(22) << " " << char(22); cout << endl;
        cout << "\t"  ; color(7); cout << "Judul "; color(judul); cout << char(31);
        cout << "    "; color(7); cout << "Artis "; color(artis); cout << char(31);
        cout << "    "; color(7); cout << "Album "; color(album); cout << char(31);
        cout << "    "; color(7); cout << "Tahun "; color(tahun); cout << char(31);

        // peringatan/notif
        color(12); cout << "\n\t" << warning  << endl;               

        // mode pengurutan asc/desc
        color(13); cout << "\t" << mode << " ";
        color(8);  cout << "[Tekan SPACE untuk mengganti]" << endl; 

        // halaman
        page = indexAwal/10 + 1;
        color(7);  cout << "\tDaftar lagu tersimpan :";
        color(14); cout << "\t\t\tPage "<< page << endl; color(7);

        // tampilkan list lagu
        listLagu(songs, indexAwal, indexAwal+10, atribut, mode);

        // opsi cari lagu
        cout << "\n\t"; color(cari); cout << char(254); color(7); 
        cout << " Cari " << atribut << "  :";
        
        // cari ditunjuk
        if (cari == SELECT) {           
            color(MARKED); cout << " [Tekan ENTER untuk mengisi]"; 

        // cari dipilih
        } else if (cari == MARKED) {    
            gotoxy(24, 19); hapusTulisan();
            gotoxy(24, 19); color(SELECT);

            // inisialisasi var
            int index = 0,
                indexAwal = 0,
				length = panjangArray(songs),
                indexAtribut;
            Song laguDitemukan[length];

            // cari berdasarkan tahun - integer
            if (atribut == "tahun") {
                // masukkan angka
                int cariInt;
                    cin >> cariInt; 
                    clearCin(); color(RESET);

                // cari lagu yg ditemukan
                while (true) {
	
                    indexAtribut = searchTahun(indexAwal, cariInt);
                    if (indexAtribut == -1) { break; }

                    laguDitemukan[index] = songs[indexAtribut];

                    indexAwal = indexAtribut+1;
                    index++;
                    
                    if (indexAwal > length-1) { break; }
                    
                }
                cari = SELECT;
                
                // jika tidak ditemukan
                if (index == 0) {
                    warning = "Lagu tidak ditemukan!";
                    continue;
                }

                // buka hasil pencarian
                hasilPencarian(to_string(cariInt), atribut, laguDitemukan);
                continue;

            // cari berdasarkan judul, artis, album - string
            } else {

                // masukkan string
                string cariStr;
                getline(cin, cariStr); fflush(stdin); color(RESET);

                // cari lagu yg ditemukan
                while (true) {

                    // berdasarkan atribut
                    if      (atribut == "judul") { indexAtribut = searchJudul(indexAwal, cariStr); }
                    else if (atribut == "artis") { indexAtribut = searchArtis(indexAwal, cariStr); }
                    else if (atribut == "album") { indexAtribut = searchAlbum(indexAwal, cariStr); }


                    if (indexAtribut == -1) { break; } 

                    laguDitemukan[index] = songs[indexAtribut];

                    indexAwal = indexAtribut+1;
                    index++;

                } 

                cari = SELECT;

                //jika tidak ditemukan
                if (index == 0) {
                    warning = "Lagu tidak ditemukan!";
                    continue;

                } 

                // buka hasil pertemuan
                hasilPencarian(cariStr, atribut, laguDitemukan);
                continue;

            } // end if - atribut

        }

        cout << endl << endl << endl; color(RESET);

        // tombol navigasi per halaman
        color(7)  ; cout << "\tKembali\t\t"; color(7)  ; cout << "\t\t    Berikutnya\n";
        color(nav); cout << "\t  <=   \t\t"; color(nav); cout << "\t\t        =>    \n"; 

        cout << endl << endl; color(RESET);

        char opsi, key;
        opsi = getch();
        
        // menu yg tersedia
        switch (opsi) {

            // tekan enter
            case ENTER:
                if (cari == SELECT) { cari = MARKED; }
                break;

            // tekan tombol panah
            case -32:
                key = getch();

                // pilih judul
                if (        
                    artis == SELECT && key == LEFT ||
                    cari  == SELECT && key == UP && judul == MARKED
                ) {
                    judul = SELECT; 
                    artis = UNSELECT;
                    cari  = UNSELECT;
                    atribut = "judul";

                // pilih artis
                } else if ( 
                    judul == SELECT && key == RIGHT ||
                    album == SELECT && key == LEFT  ||
                    cari  == SELECT && key == UP && artis == MARKED
                ) {
                    artis = SELECT;
                    judul = UNSELECT;
                    album = UNSELECT;
                    cari  = UNSELECT;
                    atribut = "artis";
                
                // pilih album
                } else if ( 
                    artis == SELECT && key == RIGHT ||
                    tahun == SELECT && key == LEFT  ||
                    cari  == SELECT && key == UP && album == MARKED
                ) {
                    album = SELECT;
                    artis = UNSELECT;
                    tahun = UNSELECT;
                    cari  = UNSELECT;
                    atribut = "album";

                // pilih tahun
                } else if(  
                    album == SELECT && key == RIGHT ||
                    cari  == SELECT && key == UP && tahun == MARKED
                ) {
                    tahun = SELECT;
                    album = UNSELECT;
                    cari  = UNSELECT;
                    atribut = "tahun";
                
                // pilih cari lagu
                } else if ( 
                    (judul == SELECT || artis == SELECT || album == SELECT || tahun == SELECT) && key == DOWN ||
                    nav == SELECT && key == UP
                ) {
                    if (judul == SELECT) { judul = MARKED; }
                    if (artis == SELECT) { artis = MARKED; }
                    if (album == SELECT) { album = MARKED; }
                    if (tahun == SELECT) { tahun = MARKED; }
                    
                    cari  = SELECT;
                    nav = UNSELECT;

                // pilih navigasi
                } else if (cari == SELECT && key == DOWN) {    
                    nav  = SELECT;
                    cari = UNSELECT;
                
                // ke halaman selanjutnya
                } else if (nav == SELECT && key == RIGHT) {     
                    indexAwal += 10;

                    if (indexAwal > STORAGE-1) {
                        warning = "Ini adalah akhir halaman!";
                        indexAwal -= 10;
                        continue;
                    }

                // ke halaman sebelumnya
                } else if (nav == SELECT && key == LEFT) {      
                    indexAwal -= 10;

                    if (indexAwal < 0) {
                        openPage = false;
                        break;
                    }
                    
                }

                break;

            // tekan spasi
            case ' ':
                if (mode == "ASC"){
                    mode = "DESC";
                } else {
                    mode = "ASC";
                }
                break;

        }

        warning = ""; // reset warning
    }
    
}

// hasil pencarian lagu
void hasilPencarian(string cari, string atribut, Song arrayDitemukan[]) {
    // var default
    bool openPage  = true;
    string warning = "";
    short int indexAwal = 0,
              indexAkhir,
              length = panjangArray(arrayDitemukan),
              pilih = SELECT,
              nav   = UNSELECT;

    while (openPage) {
        system("cls");
        cout << endl << endl << endl << endl; color(RESET);

        // keterangan
        cout << "\tHasil pencarian "; color(14); cout << cari; color(7); cout << "."; 
        color(12); cout << "\n\t" << warning << endl; color(7);
        cout << "\tLagu ditemukan : " << endl;

        // pengaturan page
        if (length > 10) { indexAkhir = indexAwal+10; } 
        else             { indexAkhir = length; }

        // tampilkan lagu yg ditemukan
        listLagu(arrayDitemukan, indexAwal, indexAkhir, atribut);

        // pilih lagu berdasarkan nomor urut
        gotoxy(0, 19); cout << "\t"; 
        color(pilih); cout << char(254); color(7); cout << " Pilih nomor :";

        // jika menunjuk pilih lagu
        if (pilih == SELECT) { 
            color(MARKED); cout << "  [Tekan ENTER untuk mengisi]";

        // jika menekan pilih lagu
        } else if (pilih == MARKED) {

            gotoxy(25, 19); hapusTulisan();
            gotoxy(25, 19); color(SELECT); 

            // masukkan nomor - integer
            int nomor;    
            cin >> nomor; 
            clearCin();

            pilih = SELECT;

            // jika nomor salah
            if ( nomor < 1 || nomor > length ) {
                warning = "Nomor tidak ditemukan!";
                continue;
            }
            
            // tampilkan rincian lagu
            tampilkanLagu(songs, arrayDitemukan[nomor-1]);
            openPage = false; break;
        }
        
        cout << endl << endl << endl; color(RESET);

        // tombol navigasi per halaman
        color(7)  ; cout << "\tKembali\t\t"; color(7)  ; cout << "\t\t    Berikutnya\n";
        color(nav); cout << "\t  <=   \t\t"; color(nav); cout << "\t\t        =>    \n"; 

        cout << endl << endl; color(RESET);

        // respon user
        char opsi, key;
        opsi = getch();

        switch (opsi) {
            
            // tekan enter
            case ENTER:
                if (pilih == SELECT) { pilih = MARKED; }

                break;

            // tekan tombol panah
            case -32:
                key = getch();

                // tunjuk pilih lagu
                if (nav == SELECT && key == UP) {
                    pilih = SELECT;
                    nav = UNSELECT;

                // tunjuk navigasi
                } else if (pilih == SELECT && key == DOWN) {
                    nav = SELECT;
                    pilih = UNSELECT;

                // ke halaman sebelumnya
                } else if (nav == SELECT && key == LEFT) {
                    indexAwal -= 10;

                    if (indexAwal < 0) {
                        openPage = false;
                        break;
                    }

                // ke halaman berikutnya
                } else if (nav == SELECT && key == RIGHT) {
                    indexAwal += 10;

                    if (indexAwal > length-1) {
                        warning = "Ini adalah akhir halaman!";
                        indexAwal -= 10;
                        continue;
                    }
                }

                break;

        }

        warning = ""; // reset warning
    }

}

// rincian lagu tertentu
void tampilkanLagu(Song arrayLagu[], Song lagu){
    // var default
    bool openPage = true;           
    short int back    = SELECT,
              edit    = UNSELECT,
              hapus   = UNSELECT;

    while (openPage) {

        system("cls");
        cout << endl << endl << endl; color(RESET);

        // judul halaman
        cout << "\t"; karakter(178, 13, 5); 
        cout << "   Rincian Lagu   "; karakter(178, 14, 5);
        cout << endl << endl;

        // tampilkan rincian lagu
        cout << "\tJudul\t: "  << lagu.title    << "\n\n"
             << "\tArtis\t: "  << lagu.artist   << "\n\n"
             << "\tAlbum\t: "  << lagu.album    << "\n\n"
             << "\tDurasi\t: " << lagu.duration << " menit\n\n"
             << "\tGenre\t: ";
        for (int i=0; i<3; i++){ cout << lagu.genre[i] << " "; }
        cout << "\n\n\tTahun\t: "     << lagu.year     << "\n\n\n";

        color(13); cout << "\t#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#\n" << endl;

        // tampilan menu
        cout << "\t    "; color(edit);  cout << char(16); color(7); cout << " Edit rincian lagu";
        cout << "\t    "; color(hapus); cout << char(16); color(7); cout << " Hapus lagu   \n\n";

        // menu kembali
        color(7)   ; cout << "\tKembali\n";
        color(back); cout << "\t  <= \n\n"; color(7);

        int index = indexLagu(lagu);
        
        // edit lagu
        if (edit == MARKED ) { 
            arrayLagu = editLagu(arrayLagu, index);
            lagu = arrayLagu[index];  
            edit = SELECT;
            continue;  

        // hapus lagu
        } else if (hapus == MARKED) {
            int length, newLength;
            length = panjangArray(arrayLagu);

            arrayLagu = hapusLagu(arrayLagu, index);
            newLength = panjangArray(arrayLagu);

            hapus = SELECT;

            // jika berhasil hapus lagu
            if (length > newLength) {
                openPage = false;
                break;
            }
            continue;
         }

        // respon user
        char opsi, key;
        opsi = getch();

        switch(opsi){

            // tekan enter
            case ENTER:

                if (edit == SELECT) {
                    edit = MARKED;
                } else if (hapus == SELECT) {
                    hapus = MARKED;
                }
                break;

            // tekan tombol panah
            case -32:
                key = getch();

                // tunjuk kembali
                if (
                    edit  == SELECT && key == DOWN ||
                    hapus == SELECT && key == DOWN
                ) {
                    back = SELECT; edit = UNSELECT; hapus = UNSELECT;

                // tunjuk edit
                } else if (
                    back == SELECT && key == UP ||
                    hapus == SELECT && key == LEFT
                ) {
                    edit = SELECT; back = UNSELECT; hapus = UNSELECT;


                // tunjuk hapus
                } else if (
                    edit == SELECT && key == RIGHT ||
                    back == SELECT && key == RIGHT
                ) {
                    hapus = SELECT; edit = UNSELECT; back = UNSELECT; 
    
                // berhenti buka halaman
                } else if (back == SELECT && key == LEFT) {
                    openPage = false;
                    break;
                }

                break;
                
        } // end switch

    }
    
}

// penutup program
void pintuKeluar() {
    system("cls");
    cout << endl << endl << endl << endl << endl << endl;

    // pemberitahuan berhasil
    color(13);
    cout << "\t Terima kasih telah menggunakan program.\n";
    color(7);

    getch();
}

// edit rincian lagu
Song *editLagu(Song arrayLagu[], int index) {

    // var default
    bool openPage = true,
         editing  = false;
    string notif = "";
    short int judul   = SELECT,
              artis   = UNSELECT,
              album   = UNSELECT,
              durasi  = UNSELECT,
              genre   = UNSELECT,
              tahun   = UNSELECT,
              nav     = UNSELECT;

    while (openPage) {
        system("cls");
        cout << endl << endl << endl; color(RESET);

        // judul halaman
        cout << "\t"; karakter(178, 10, 5); 
        cout << "   Edit Rincian Lagu   ";  karakter(178, 11, 5);

        // tampilkan formulir
        color(judul); cout << "\n\n\t"; cout << char(16); 
        color(7);     cout << " Judul   : "  << arrayLagu[index].title ;

        color(artis); cout << "\n\n\t"; cout << char(16); 
        color(7);     cout << " Artis   : "  << arrayLagu[index].artist;

        color(album); cout << "\n\n\t"; cout << char(16); 
        color(7);     cout << " Album   : "  << arrayLagu[index].album;

        color(durasi);cout << "\n\n\t"; cout << char(16); 
        color(7);     cout << " Durasi  : "  << arrayLagu[index].duration;

        color(genre); cout << "\n\n\t"; cout << char(16); 
        color(7);     cout << " Genre   : ";
        
        for (int i=0; i<3; i++) { 
            gotoxy(20, 13+i); cout << "- " << arrayLagu[index].genre[i];
        }    
        
        color(tahun); cout << "\n\n\t"; cout << char(16); 
        color(7);     cout << " Tahun   : "  << arrayLagu[index].year; 

        // pengisian formulir
        string isiStr; int isiInt;

        // edit judul lagu
        if (judul  == SELECT || judul == MARKED)  { 
            
            if (!editing) {

                gotoxy(20, 5); color(MARKED); 
                cout << "[Tekan ENTER untuk mengedit]" << endl;

            } else {
                while (isSpace(isiStr)) {

                    gotoxy(20, 5); hapusTulisan();
                    gotoxy(20, 5); color(SELECT); 
                    getline(cin, isiStr); fflush(stdin);

                }

                arrayLagu[index].title = isiStr;
                judul = SELECT;
            }    
        
        // edit artis
        } else if (artis  == SELECT || artis == MARKED)  {
            if (!editing) {

                gotoxy(20, 7); color(MARKED); 
                cout << "[Tekan ENTER untuk mengedit]" << endl;

            } else {
                while (isSpace(isiStr)) {

                    gotoxy(20, 7); hapusTulisan();
                    gotoxy(20, 7); color(SELECT); 
                    getline(cin, isiStr); fflush(stdin);

                }

                arrayLagu[index].artist = isiStr;
                artis = SELECT;
            }    

        // edit album
        } else if (album  == SELECT || album == MARKED)  {
            if (!editing) {

                gotoxy(20, 9); color(MARKED); 
                cout << "[Tekan ENTER untuk mengedit]" << endl;

            } else {
                while (isSpace(isiStr)) {

                    gotoxy(20, 9); hapusTulisan();
                    gotoxy(20, 9); color(SELECT); 
                    getline(cin, isiStr); fflush(stdin);

                }

                arrayLagu[index].album = isiStr;
                album = SELECT;
            }

        // edit durasi -> tidak bisa
        } else if (durasi == SELECT) { 
            
            gotoxy(20, 11); 
            color(4); cout << "[Durasi tidak bisa diedit]  " << endl;    

        // edit genre
        } else if (genre  == SELECT || genre == MARKED)  {
            if (!editing) {

                gotoxy(22, 13); color(MARKED); 
                cout << "[Tekan ENTER untuk mengedit]" << endl;

            } else {

                for (int i=0; i<3; i++) {

                    while(isSpace(isiStr)) {
                        gotoxy(22, 13+i); hapusTulisan();
                        gotoxy(22, 13+i); color(SELECT);
                        getline(cin, isiStr); fflush(stdin);

                        if (
                            !isSpace(arrayLagu[index].genre[0]) && 
                            i > 0 && 
                            isSpace(isiStr)
                        ) { break; }

                    }

                    arrayLagu[index].genre[i] = isiStr; isiStr = "";
                }
                genre = SELECT;

            }    
        
        // edit tahun
        } else if (tahun  == SELECT || tahun == MARKED)  {
            if (!editing) {

                gotoxy(20, 17); color(MARKED); 
                cout << "[Tekan ENTER untuk mengedit]" << endl;

            } else {
                while (true) {

                    gotoxy(20, 17); hapusTulisan();
                    gotoxy(20, 17); color(SELECT); 
                    cin >> isiInt; if (!cin.fail()) { break; }
                    clearCin();

                }

                arrayLagu[index].year = isiInt;
                tahun = SELECT;
            }    
        }

        gotoxy(0, 19); color(RESET);

        // notifikasi
        if (editing) {
            notif = "Berhasil diperbarui!";
            editing = false;
        } else {
            notif = "";
        }

        color(10); cout << "\n\t\t\t\b\b\b\b" << notif << endl; color(7);

        // tombol kembali
        color(7)  ; cout << "\n\tKembali";
        color(nav); cout << "\n\t  <=   ";
        
        color(RESET); cout << endl << endl;

        // respon user
        char opsi, key;
        opsi = getch();

        switch (opsi) {
            // tekan enter
            case ENTER:
                if      (tahun == SELECT) { tahun = MARKED; editing = true;}
                else if (judul == SELECT) { judul = MARKED; editing = true;} 
                else if (artis == SELECT) { artis = MARKED; editing = true;} 
                else if (album == SELECT) { album = MARKED; editing = true;}
                else if (genre == SELECT) { genre = MARKED; editing = true;}

                break;

            // tekan tombol panah
            case -32:
                key = getch();

                // tunjuk judul
                if (artis == SELECT && key == UP) {
                    judul = SELECT; 
                    artis = UNSELECT;

                // tunjuk artis
                } else if (
                    judul == SELECT && key == DOWN ||
                    album == SELECT && key == UP
                ) { 
                    artis = SELECT; 
                    judul = UNSELECT; 
                    album = UNSELECT;

                // tunjuk album
                } else if (
                    artis == SELECT && key == DOWN ||
                    durasi == SELECT && key == UP  
                ) {
                    album = SELECT; 
                    artis = UNSELECT; 
                    durasi = UNSELECT;

                // tunjuk durasi
                } else if (
                    album == SELECT && key == DOWN ||
                    genre == SELECT && key == UP
                ) {
                    durasi = SELECT; 
                    album = UNSELECT; 
                    genre = UNSELECT;

                // tunjuk genre
                } else if (
                    durasi == SELECT && key == DOWN ||
                    tahun == SELECT && key == UP
                ) {
                    genre = SELECT; 
                    durasi = UNSELECT; 
                    tahun = UNSELECT;

                // tunjuk tahun
                } else if (
                    genre == SELECT && key == DOWN ||
                    nav   == SELECT && key == UP
                ) {
                    tahun = SELECT; 
                    genre = UNSELECT;
                    nav   = UNSELECT;

                // tunjuk kembali
                } else if (tahun == SELECT && key == DOWN) {
                    nav = SELECT; 
                    tahun = UNSELECT;
                
                // kembali
                } else if (nav == SELECT && key == LEFT) {

                    openPage = false;
                    break;
                }

                break;
        }

    }
    
    return arrayLagu;
}

// hapus lagu
Song *hapusLagu(Song arrayLagu[], int index) {

    // var default
    bool deleting = true;
    short int ya    = SELECT,
              tidak = UNSELECT;

    while (deleting) {

        // notifikasi penghapusan lagu
        notifHapus(ya, tidak);

        gotoxy(0, 22);
        color(RESET); cout << endl << endl;

        // respon user
        char opsi, key;
        opsi = getch();

        switch (opsi) {

            // tekan enter
            case ENTER:

                // batal hapus
                if (tidak == SELECT) {

                    deleting = false;
                    break;

                // benar hapus
                } else if (ya == SELECT) {

                    for (int i=index; i<panjangArray(songs); i++){

                        if (i == panjangArray(songs)-1) {
                            arrayLagu[i] = {"", "", "", 0, {""}, 0};
                        }

                        if (arrayLagu[i].title != "") {
                            swap(arrayLagu[i], arrayLagu[i+1]); 
                        } 
                    }

                    deleting = false;
                    break;
                }

                break;

            // tekan tombol panah
            case -32:
                key = getch();

                // tunjuk ya
                if (tidak == SELECT && key == LEFT) {
                    ya = SELECT; 
                    tidak = UNSELECT;

                // tunjuk tidak
                } else if (ya == SELECT && key == RIGHT) {
                    tidak = SELECT; 
                    ya = UNSELECT;
                }

                break;
                
        } // end swicth case

    }// end while

    return arrayLagu;
}

// tambah lagu baru
Song tambahLagu(Song arrayLagu[], int index) {
    // var default
    bool openPage = true;
    short int judul  = SELECT,
              artis  = UNSELECT,
              album  = UNSELECT,
              durasi = UNSELECT,
              genre  = UNSELECT, 
              tahun  = UNSELECT,
              nav    = UNSELECT; 
    
    // lagu baru yg ditambahkan
    Song laguBaru = arrayLagu[index];

    while(openPage) {
        system("cls");
        cout << endl << endl << endl;
        
        // judul halaman
        cout << "\t"; karakter(178, 11, 5); 
        cout << "   Tambah Lagu Baru   ";  karakter(178, 11, 5);

        // tampilkan formulir
        color(judul); cout << "\n\n\t"; cout << char(16); 
        color(7);     cout << " Judul   : "  << laguBaru.title ;

        color(artis); cout << "\n\n\t"; cout << char(16); 
        color(7);     cout << " Artis   : "  << laguBaru.artist;

        color(album); cout << "\n\n\t"; cout << char(16); 
        color(7);     cout << " Album   : "  << laguBaru.album;

        color(durasi);cout << "\n\n\t"; cout << char(16); 
        color(7);     cout << " Durasi  : "  << laguBaru.duration;

        color(genre); cout << "\n\n\t"; cout << char(16); 
        color(7);     cout << " Genre   : ";
        
        for (int i=0; i<3; i++) { 
            gotoxy(20, 13+i); cout << "- " << laguBaru.genre[i];
        }    
        
        color(tahun); cout << "\n\n\t"; cout << char(16); 
        color(7);     cout << " Tahun   : "  << laguBaru.year;

        // pengisian formulir
        string isiStr; int isiInt; float isiFloat;
        
        // tunjuk judul
        if (judul  == SELECT)  { 
            
            if (!isSpace(laguBaru.title)) {

                gotoxy(20, 5); cout << laguBaru.title ;

            } else {
                while (isSpace(isiStr)) {

                    gotoxy(20, 5); hapusTulisan();
                    gotoxy(20, 5); color(SELECT); 
                    getline(cin, isiStr); fflush(stdin);

                }

                laguBaru.title = isiStr;
            }

            judul = UNSELECT; artis = SELECT; continue;
        
        // tunjuk artis
        } else if (artis  == SELECT)  {
            if (!isSpace(laguBaru.artist)) {

                gotoxy(20, 7); cout << laguBaru.artist ;

            } else {
                while (isSpace(isiStr)) {

                    gotoxy(20, 7); hapusTulisan();
                    gotoxy(20, 7); color(SELECT); 
                    getline(cin, isiStr); fflush(stdin);

                }

                laguBaru.artist = isiStr; 
            }
            artis = UNSELECT; album = SELECT; continue;

        // tunjuk album
        } else if (album  == SELECT)  {
            if (!isSpace(laguBaru.album)) {

                gotoxy(20, 9); cout << laguBaru.album ;

            } else {
                while (isSpace(isiStr)) {

                    gotoxy(20, 9); hapusTulisan();
                    gotoxy(20, 9); color(SELECT); 
                    getline(cin, isiStr); fflush(stdin);

                }

                laguBaru.album = isiStr;
            }
            album = UNSELECT; durasi = SELECT; continue;

        // tunjuk durasi
        } else if (durasi == SELECT)  {

            if (laguBaru.duration != 0) {
                gotoxy(20, 11); cout << laguBaru.duration ;

            } else {
                while (isSpace(isiStr)) {

                    gotoxy(20, 11); hapusTulisan();
                    gotoxy(20, 11); color(SELECT); 

                    cin >> isiFloat; 
                    if (!cin.fail() && isiFloat > 0) { break; }
                    clearCin();

                }

                clearCin();
                laguBaru.duration = isiFloat; 
            }

            durasi = UNSELECT; genre = SELECT; continue;

        // tunjuk genre
        } else if (genre  == SELECT)  {
            if (
                !isSpace(laguBaru.genre[0]) && 
                !isSpace(laguBaru.genre[1]) &&
                !isSpace(laguBaru.genre[2])
            ) {

                for (int i=0; i<3; i++) {
                    gotoxy(22, 13+i); cout << laguBaru.genre[i];

                }

            } else {

                for (int i=0; i<3; i++) {

                    while(isSpace(isiStr)) {
                        gotoxy(22, 13+i); hapusTulisan();
                        gotoxy(22, 13+i); color(SELECT);
                        getline(cin, isiStr); fflush(stdin);

                        if (
                            !isSpace(laguBaru.genre[0]) && 
                            i > 0 && 
                            isSpace(isiStr)
                        ) { break; }

                    }

                    laguBaru.genre[i] = isiStr; isiStr = "";

                }

            }
            genre = UNSELECT; tahun = SELECT; continue;   
        
        // tunjuk tahun
        } else if (tahun  == SELECT)  {
            if (laguBaru.year != 0) {

                gotoxy(20, 17); cout << laguBaru.year ;

            } else {
                while (true) {

                    gotoxy(20, 17); hapusTulisan();
                    gotoxy(20, 17); color(SELECT); 
                    cin >> isiInt; 
                    if (!cin.fail() && isiInt > 0) { break; }
                    clearCin();

                }
                clearCin();
                laguBaru.year = isiInt;
            }  
            tahun = UNSELECT; nav = SELECT; continue;
        }

        // jika berhasil mengisi seluruh formulir
        if (formTerisi(laguBaru)) {
            gotoxy(0, 19);
            color(10);  cout << "\t\t  Lagu berhasil ditambahkan!" << endl << endl;
            color(7)  ; cout << "\n\tKembali"; 
            color(nav); cout << "\n\t  <=   ";
        }

        gotoxy(0, 22);
        color(RESET); cout << endl << endl;

        // respon user
        char opsi, key;
        opsi = getch();

        switch(opsi) {
            // tekan tombol panah
            case -32:
                key = getch();

                // kembali
                if (nav == SELECT && key == LEFT) {
                    openPage = false;
                    break;

                } 

                break;
        }

    }                    

    return laguBaru;

}


/*--------------------------------  SORTING  -------------------------------- */
// tukar data
void swap(Song *elemen1, Song *elemen2) {
    Song temp = *elemen1;
    *elemen1 = *elemen2;
    *elemen2 = temp;
}

// sorting berdasarkan judul
void sortJudul(string mode){        // bubble sort
    Song temp;
    int length = panjangArray(songs);
    for (int i=0; i<length-1; i++){
        for (int j=0; j<length-1; j++){
            // ascending
            if(
                songs[j].title.compare(songs[j+1].title) > 0
                && mode == "ASC"
            ){
                temp = songs[j];
                songs[j] = songs[j+1];
                songs[j+1] = temp;
            }

            // descending
            if (
                songs[j].title.compare(songs[j+1].title) < 0
                && mode == "DESC"
            ){
                temp = songs[j];
                songs[j] = songs[j+1];
                songs[j+1] = temp;
            } // end if
        } // end for
    } // end for 
} // end function

// sorting berdasarkan artis
void sortArtis(string mode){        // insertion sort
    Song key;
    int i, j,
        length = panjangArray(songs);

    for (i = 1; i < length; i++) {

        key = songs[i];
        j = i-1;

        // ascending
        if (mode == "ASC") {
            while (j >= 0 && songs[j].artist > key.artist){
                songs[j+1] = songs[j];
                j = j-1;
            }

        // descending
        } else {
            while (j >= 0 && songs[j].artist < key.artist){
                songs[j+1] = songs[j];
                j = j-1;
            }
        }

        songs[j+1] = key;
    }
}

// sorting berdasarkan album
int partition(int low, int high, string mode) {     
    string pivot = songs[high].album;
    int i = (low - 1);
    for (int j = low; j <= high- 1; j++) {

        // ascending
        if (
            songs[j].album.compare(pivot) <= 0
            && mode == "ASC"
        ) {
            i++;
            swap(&songs[i], &songs[j]);
        }

        // descending
        if (
            songs[j].album.compare(pivot) >= 0
            && mode == "DESC"
        ) {
            i++;
            swap(&songs[i], &songs[j]);
        }
    }
    swap(&songs[i + 1], &songs[high]);
    return (i + 1);
}

// sortting berdasarkan judul
void sortAlbum(int low, int high, string mode) {    // quick sort
    if (low < high) {
        int pi = partition(low, high, mode);
        sortAlbum(low, pi - 1, mode);
        sortAlbum(pi + 1, high, mode);
    }
}

// sorting berdasarkan tahun
void sortTahun(string mode) {  // selection sort
    sortJudul(mode);
    int indexMin,
        length = panjangArray(songs);

    for (int i=0; i<length-1; i++) {
        indexMin = i;

        for (int j= i+1; j<length; j++) {
            
            // ascending
            if (
                mode == "ASC" &&
                songs[j].year < songs[indexMin].year
            ) {
                indexMin = i;
                swap(&songs[j], &songs[indexMin]);
            }

            // descending
            if (
                mode == "DESC" &&
                songs[j].year > songs[indexMin].year
            ) {

                indexMin = i; 
                swap(&songs[indexMin], &songs[j]);
                
            } // end if
        } // end for - j
    } // end for - i
}

// sorting array int
void sortArray(int array[], int length) {       // insertion sort
    int key;
    int i, j;

    for (i = 1; i < length; i++) {

        key = array[i];
        j = i-1;

        while (j >= 0 && array[j] > key){
            array[j+1] = array[j];
            j = j-1;
        }

        array[j+1] = key;
    }
}

/*--------------------------------  SEARCHING  -------------------------------- */

// cari berdasarkan judul
int searchJudul(int awal, string cari) {    // sequential search

    for (int i=awal; i<panjangArray(songs); i++) {
        if (lower(songs[i].title) == lower(cari)) {
            return i;
        }
    }

    for (int i=awal; i<panjangArray(songs); i++) {
        if (lower(songs[i].title).find(lower(cari)) != -1) {
            return i;
        }
    }

    return -1;
}

// cari berdasarkan artis
int searchArtis(int awal, string cari) {    // binary search & sequential search
    sortArtis("ASC");

    int beg = awal, end = panjangArray(songs)-1, mid;
    while( beg <= end ){

        mid = (end + beg) / 2;

        if (lower(songs[mid].artist) == lower(cari)){ 
            return mid;

        } else {

            if(cari.compare(songs[mid].artist) > 0){ 
                beg = mid + 1;

            } else {
                end = mid - 1;
            
            } // end if

        } // end if

    } // end while   

    for (int i=awal; i<panjangArray(songs); i++) {
        if (lower(songs[i].artist).find(lower(cari)) != -1) {
            return i;
        }
    }

    return -1;
}

// cari berdasarkan album
int searchAlbum(int awal, string cari) {    // binary search & sequential search
    int beg = awal, end = panjangArray(songs)-1, mid;
    sortAlbum(beg, end, "ASC");

    while( beg <= end ){

        mid = (end + beg) / 2; 


        if (lower(songs[mid].album) == lower(cari)){ 
            return mid;

        } else {

            if(cari.compare(songs[mid].album) > 0){ 
                beg = mid + 1;

            } else {
                end = mid - 1;
            
            } // end if
        } // end if
    } // end while

    for (int i=awal; i<panjangArray(songs); i++) {
        if (lower(songs[i].album).find(lower(cari)) != -1) {
            return i;
        }
    }

    return -1;
}

// cari berdasarkan tahun
int searchTahun(int awal, int cari) {        // sequential search
    for (int i=awal; i<panjangArray(songs); i++) {
        if (cari == songs[i].year){
            return i;
        }
    }
    return -1;
}

// cari int dalam array int
bool dataDitemukan(int array[], int length, int cari){       // interpolation search
    sortArray(array, length);

    int akhir = panjangArray(songs)-1,
        awal  = 0,
        posisi;
    bool berhenti = false;

    if (cari > array[akhir]) {
        return -1;
    }

    while (!berhenti) {
        posisi =  awal + (cari - array[awal])*(akhir-awal)
                         /(array[akhir] - array[awal]);

        cout << posisi << " "; getch();

        if (array[posisi] == cari) {
            return posisi;

        } else if (
            array[posisi] <= cari && 
            array[posisi] >= array[awal]
        ) {
            awal = posisi + 1;

        } else if (
            array[posisi] >= cari && 
            array[posisi] <= array[akhir]
        ) {
            akhir = posisi - 1;
        
        } else {
            berhenti = true;
        }

    }

    return -1;

}


/*--------------------------------  FUNGSI  -------------------------------- */

// atur warna teks
void color(unsigned short kodeWarna) {
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
int indexLagu(Song lagu){
    for (int i=0; i<STORAGE; i++){
        if (songs[i].title == lagu.title){
            return i;
        }
    }
    return -1;
}

// atur tempat tampilan
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// bersihkan cin
void clearCin() {
    cin.clear(); 
    cin.ignore(); 
    fflush(stdin);
}

// hapus tulisann tertentu
void hapusTulisan() {
    color(0);
    for (int i=0; i<30; i++) {
        cout << char(219);
    }
    cout << endl;
    color(RESET);
}

// cek spasi
bool isSpace(string str) {
    if (str == "\t" || str == "\n" || str == "") {
        return true;
    }

    int length = str.length(),
        isSpasi = 0;
    char strChar[length], 
         spasi = ' ';

    strcpy(strChar, str.c_str());

    for (int i=0; i<length; i++) {
        if (strChar[i] == spasi) {
            isSpasi++;
        }
    }

    if (length == isSpasi) {
        return true;
    }

    return false;
}

// tampilkan list lagu berdasarkan atribut
void listLagu(Song arrayLagu[], int awal, int akhir, string atribut, string mode) {

    if (atribut == "judul") {
        sortJudul(mode);
        
        // tampilan daftar lagu
        for (int i=awal; i<akhir; i++){
            cout << "\t(" << i+1 << "). " << arrayLagu[i].title << endl;
        }

    } else if (atribut == "artis") {
        sortArtis(mode);

        // tampilan daftar lagu
        for (int i=awal; i<akhir; i++){
            cout << "\t(" << i+1 << "). ";

            if (arrayLagu[i].title == ""){
                cout << endl;
            } else {
                cout << arrayLagu[i].artist << " - " << arrayLagu[i].title << endl;
            }
        }
    } else if (atribut == "album") {
        sortAlbum(0, panjangArray(arrayLagu)-1, mode);

        // tampilkan daftar lagu
        for (int i=awal; i<akhir; i++){
            cout << "\t(" << i+1 << "). ";

            if (arrayLagu[i].title == ""){
                cout << endl;
            } else {
                cout << arrayLagu[i].album << " - " << arrayLagu[i].title << endl;
            }

        }

    } else if (atribut == "tahun") {
        sortTahun(mode);

        // tampilkan daftar lagu
        for (int i=awal; i<akhir; i++){
            cout << "\t(" << i+1 << "). ";

            if (arrayLagu[i].title == ""){
                cout << endl;
            } else {
                cout << arrayLagu[i].year << " - " << arrayLagu[i].title << endl;
            }

        }
        
    }

}

// tampilkan char berdasarkan asciii
void karakter(int ascii, int jumlah, int warna) {
    color(warna);
    for (int i=0; i<jumlah; i++) {
        cout << char(ascii);
    }
    color(RESET);
}

// notifikasi untuk hapus lagu
void notifHapus(int ya, int tidak) {

    gotoxy(11, 11); 
    for (int i=0; i<26; i++) {
        if (i%2 == 0) {
            karakter(177, 2);
        } else {
            cout << " ";
        }
    }

    gotoxy(11, 18); 
    for (int i=0; i<26; i++) {
        if (i%2 == 0) {
            karakter(177, 2);
        } else {
            cout << " ";
        }
    }
    color(7);
    gotoxy(11, 10); cout << "---------------------------------------";
    gotoxy(11, 13); cout << "|  Apakah Anda yakin ingin menghapus  |";
    gotoxy(11, 14); cout << "|        lagu dari playlist?          |";
    gotoxy(11, 15); cout << "|                                     |";
    gotoxy(11, 16); cout << "|                                     |";
    gotoxy(19, 16); color(ya);    cout << char(16); color(7); cout << " Ya";
    gotoxy(34, 16); color(tidak); cout << char(16); color(7); cout << " Tidak";
    gotoxy(11, 19); cout << "---------------------------------------";
}

// cek formulir sudah diisi
bool formTerisi(Song lagu) {
    if (
        isSpace(lagu.title)  ||
        isSpace(lagu.artist) ||
        isSpace(lagu.album)  ||
        isSpace(lagu.genre[0]) ||
        lagu.duration == 0 ||
        lagu.year     == 0
    ) {
        return false;
    }
    return true;
}

// lowercase untuk string
string lower(string str) {
    for (int i=0; i<str.length(); i++) {
        str[i] = char(tolower(str[i]));
    }

    return str;
}





