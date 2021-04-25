# **soal-shift-sisop-modul-2-E10-2021**
Kelompok E-10
- Stefanus Albert Kosim (05111940000096)
- Ahmad Luthfi Hanif (05111940000179)
- Albert Filip Silalahi (05111940000116)

# **Soal 1**
Stevany pacar Stevan akan berulang tahun, karena Steven bucin dia ingin memberikannya hadiah berupa folder yang berisi hal-hal yang disukai wanita malang itu.

## **1A**
Steven ingin membuat folder dimana nama folder-foldernya adalah Musyik untuk mp3, Fylm untuk mp4, dan Pyoto untuk jpg

## **1B**
Steven harus mendownload musik, film, dan foto dari link yang sudah disediakan

## **1C dan 1D**
Steven harus meng-extract isi zip dan memindahkannya ke folder yang tadi sudah dibuat sesuai dengan ketentuan

## **1E**
Untuk memudahkan Steven, ia ingin semua hal di atas berjalan otomatis 6 jam sebelum waktu ulang tahun Stevany

## **1F**
Setelah itu pada waktu ulang tahunnya Stevany, semua folder akan di zip dengan nama Lopyu_Stevany.zip dan semua folder akan di delete(sehingga hanya menyisakan .zip).


# **Soal 2**
Loba bekerja di sebuah petshop terkenal, suatu saat dia mendapatkan zip yang berisi banyak sekali foto peliharaan dan Ia diperintahkan untuk mengkategorikan foto-foto peliharaan tersebut.
## **2A**

- **Soal**
  Pertama-tama program perlu mengextract zip yang diberikan ke dalam folder “/home/[user]/modul2/petshop”. program harus bisa membedakan file dan folder sehingga dapat memproses file yang seharusnya dikerjakan dan menghapus folder-folder yang tidak dibutuhkan.
- **Penyelsaian**


# **Soal 3**

## **3A**

- **Soal**
  
  Ranora harus membuat daemon dengan tujuan membuat folder sesuai dengan timestamp [YYYY-mm-dd_HH:ii:ss] setiap 40 detik
- **Penyelesaian**
  
  Untuk menjalankan program setiap 40 detik, digunakan daemon yang ada pada modul namun fungsi sleep diganti parameternya menjadi `sleep(40)`. Untuk membuat penamaan folder sesuai dengan timestamp, digunakan header time.h.
  ```
    time_t rawtime;
    struct tm *info;
    char buffer[80];
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d_%X", info);
    ```
    Dimana variabel `rawtime` untuk menyimpan timestamp dalam format **Unix epoch**, variabel `info` untuk timestamp yang sudah terstruktur sesuai dengan localtime, dan variabel `buffer` untuk menyimpan string hasil format variabel info. `strftime` kemudian akan menyimpan timestamp [YYYY-mm-dd_HH:ii:ss] ke dalam buffer.

    Setelah nama folder sudah diproses, kemudian process akan di `fork` dan child process melaksanakan `execv(/bin/mkdir/)` dengan argumen yang akan dilaksanakan adalah `mkdir $buffer`
    ```
    pid_t child_id;
    child_id = fork();

    if(child_id == 0) {
        char* arg[] = {"mkdir", "-p", buffer, NULL};
        execv("/bin/mkdir", arg);
    }
    ```
    Folder akan memiliki penamaan dan range waktu berikut
    
    ![mkdir](https://i.ibb.co/Z8mjqRH/Screenshot-160.png)
## **3B**

- **Soal**

    Ranora harus mengunduh 10 gambar dari https://picsum.photos/ dimana tiap gambar akan didownload setiap 5 detik. Gambar-gambar tersebut akan dinamai sesuai dengan timestamp [YYYY-mm-dd_HH:ii:ss] (waktu ketika gambar tersebut diunduh) serta ukuran gambarnya adalah persegi (n%1000) + 50 pixel dimana n adalah detik Epoch Unix.

- **Penyelesaian**

    Setelah folder dibuat, dilakukan loop sebanyak 10x, dimana di tiap loop process akan di `fork` untuk mengunduh dari https://picsum.photos/. Agar ukuran foto yang diunduh sesuai dengan yang diinginkan, ditambahkan ukuran di akhir link menjadi https://picsum/photos/ukuran. Ukurannya dihitung dengan `rawtime%1000 + 50`. dan kemudian link tersebut disimpan ke dalam variabel link bertipe string (char[80]).
    
    Untuk penamaan file, digunakan cara yang sama dengan **3A**. Untuk mengunduh, digunakan `exec(/bin/wget/)` dengan argumen 
    ```
    "wget", "-q", "-O", path, link, NULL
    ```
    dimana path adalah `namaFolder/namaFile`. Di akhir loop (sebelum masuk ke iterasi selanjutnya), dipanggil fungsi `sleep(5)` agar foto didownload setiap 5 detik. 
    
    ![downloaded_photo](https://i.ibb.co/2jmg5LT/Screenshot-162.png")
    
## **3C**

- **Soal**

    Ranora membuat file status.txt dengan isi "Download Success" yang dienkripsi dengan *Caesar Cipher* shift 5 jika foto telah selesai diunduh. Selanjutnya Ranora ingin direktori tersebut di-*zip* dan direktorinya akan dihapus setelah di-*zip* sehingga hanya ada file *zip*

- **Penyelesaian**

    Agar file `status.txt` dibuat tepat setelah proses unduh kesepuluh fotonya selesai, maka dilakukan fork sebelum dilakukan looping di soal **3B**, sehingga loop dan pembuatan file `status.txt` berada pada satu child yang sama.

    Tepat setelah unduhan selesai, maka proses akan di fork dan membuat sebuah file `status.txt` yang berisi "Download Success" dengan enkripsi *Caesar Cipher* shift 5. Enkripsi ini menggunakan cara sebagai berikut :
    
    - Tambahkan ASCII setiap huruf dengan 5.
    - Karena ASCII 'Z' lebih kecil dari 'a', maka diberikan batas.
    - Dilakukan pengecekan apakah ASCII nya melebihi 'z' atau (lebih besar dari 'Z' dan lebih kecil dari 'a').
    - Jika ASCII nya melebihi batas tersebut, maka ASCII nya dikurangi dengan 26 karena jumlah alphabet ada 26.

    Setelah isinya dienkripsi, program akan menjakankan `execv` dengan perintah `zip`. Program akan menunggu proses zip selesai dengan menggunakan 
    ```
    while(wait(NULL) != child_id);
    ```
    Setelah proses zip selesai, selanjutnya program akan menjalankan `execv` dengan perintah `rm`.
    
    ![zip and remove folder](https://i.ibb.co/8BGv5Vw/Screenshot-164.png)
    
## **3D**

- **Soal**

    Ranora ingin mempermudah pengendalian program dengan meng-generate program killer yang berfungsi untuk menterminasi semua proses program yang sedang berjalan dan kemudian program tersebut akan menghapus dirinya sendiri. Program ini merupakan program **bash**

- **Penyelesaian**

    Untuk membuat program bash yang akan menterminasi semua proses yang sedang berjalan, digunakan **killall** dan **sigkill** dengan target program yang sedang berjalan yaitu program **soal3**. Setelah program mengeksekusi signal sigkill, maka program killer.sh akan dihapus dengan command `rm $0` dimana $0 adalah nama filenya yaitu `killer.sh`. Program killer ini ditulis sebagai berikut :
    ```
    char *code = ""
    "#!/bin/bash\n"
    "killall -9 ./soal3\n"
    "rm $0\n";
    fprintf(src, code, NULL);
    ```
    dimana src adalah pointer yang menunjuk ke file killer.sh. 
    ![make killer.sh](https://i.ibb.co/3YGy5by/Screenshot-161.png)
    
## **3E**

- **Soal**

    Ranora membuat 2 mode masing masing menggunakan argumen `-x` untuk menghentikan program utama namun tetap menjalankan proses direktorinya berjalan (sisa unduhan, zip dan menghapus folder yang telah di zip) dan `-z` untuk menghentikan program dengan menggunakan **Soal 3D**

    Untuk menangkap argumen saat ingin menjalankan program, maka digunakan parameter string pada main
    ```
    int main(int argc, char** argv)
    ```
    - argc adalah banyaknya argumen yang dimasukkan
    - argv adalah char berdimensi 2 yang berisi argumen yang dimasukkan

    Karena kita membutuhkan **tepat dua** argumen, yaitu `./soal3 -mode`, maka dibuat control flow dimana jika argumen yang diterima jumlahnya tidak sesuai maka program tidak dijalankan, begitu pula dengan modenya. 

    Jika input sudah sesuai, maka dibuat flag untuk menandai mode yang dimasuki, `1` untuk `-z` dan `2` untuk `-x`. Kemudian dibuat fungsi untuk membuat program killer.sh yang parameter yang menerima flag tersebut. 
    - Jika flag yang adalah 1, maka program akan menulis code di **soal 3D**
    
    ![command -z](https://i.ibb.co/QFGVpx8/Screenshot-165.png)
    
    - Jika flag yang adalah 2, maka program akan menulis code sebagai berikut :
    ```
    char *code = ""
    "#!/bin/bash\n"
    "kill %d\n"
    "rm $0\n";
    fprintf(src, code, getpid());
    ```
    dimana kill getpid() akan menterminasi Process ID yang dimiliki program utama.
    
    ![command -x](https://i.ibb.co/n8GbZ7n/Screenshot-166.png)
    
## **Kesulitan**

Terdapat bug jika proses remove foldernya digabung dengan zip menggunakan command `zip zipname -r -m path`
