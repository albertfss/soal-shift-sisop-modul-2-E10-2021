# **soal-shift-sisop-modul-2-E10-2021**
Kelompok E-10
- Stefanus Albert Kosim (05111940000096)
- Ahmad Luthfi Hanif (05111940000179)
- Albert Filip Silalahi (05111940000116)

# **Soal 1**
Stevany pacar Stevan akan berulang tahun, karena Steven bucin dia ingin memberikannya hadiah berupa folder yang berisi hal-hal yang disukai wanita malang itu.

## **1A**
Steven ingin membuat folder dimana nama folder-foldernya adalah Musyik untuk mp3, Fylm untuk mp4, dan Pyoto untuk jpg
```
 child_id = fork(); 
        if (child_id == 0)
        {
            char *argv[] = {"mkdir","Fylm","Musyik","Pyoto",NULL};
            execv("/bin/mkdir", argv); 
        }
```
Pertama dibuat fork untuk membuat proses yang baru, lalu argv menyimpan perintah membuat folder dan nama folder yang akan dibuat. Selanjutnya perintah dieksekusi dengan ```execv``` 


## **1B**
Steven harus mendownload musik, film, dan foto dari link yang sudah disediakan
```
 child_id2 = fork();
        if (child_id2 == 0)
        {
            char *dwnldmusik[] = { "wget", "-q","--no-check-certificate","https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "-O","Musik_for_Stevany.zip",NULL};
            execv("/bin/wget", dwnldmusik);
        }
 
        while ((wait(NULL)) > 0);
        child_id3 = fork();          
        if (child_id3 == 0)
        {
            char *dwnldfoto[]=  { "wget", "-q","--no-check-certificate","https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", "-O","Foto_for_Stevany.zip",NULL};
            execv("/bin/wget", dwnldfoto);   
        }
 ```
 Disini kita buat fork baru lagi untuk menjalankan proses selanjutnya. Fork pertama akan didownload zip yang berisi Musik dari link yang sudah ada. ```wget``` merupakan perintah nya. 
 ```  while ((wait(NULL)) > 0);```, bagian ini bertujuan untuk menunggu proses yang dilakukan sebleumnya, setelah selesai akan dilanjutkan ke proses selanjutnya yaitu mendownload zip Foto_for_stevany.

## **1C dan 1D**
Steven harus meng-extract isi zip dan memindahkannya ke folder yang tadi sudah dibuat sesuai dengan ketentuan
```
 while(wait(NULL) > 0);
        child_id5 = fork();
        if(child_id5==0)
        {
            char *unzipmusik[]={"unzip", "-j", "Musik_for_Stevany.zip", "-d", "./Musyik", NULL};
            execv("/bin/unzip", unzipmusik);
        }
 
        while ((wait(NULL)) > 0);
        child_id6 = fork();          
        if (child_id6 == 0)
        {
            char *unzipfoto[]={"unzip", "-j", "Foto_for_Stevany.zip", "-d", "./Pyoto", NULL};
            execv("/bin/unzip", unzipfoto);
        }
        child_id4 = fork();
        if(child_id4==0)
        {
            while ((wait(&status)) > 0);
            char *unzipfilm[]={"unzip", "-j", "Film_for_Stevany.zip", "-d", "./Fylm", NULL};
            execv("/bin/unzip", unzipfilm);
        }
```
Pertama dibuat fork dulu untuk proses baru. ``` char *unzipmusik[]={"unzip", "-j", "Musik_for_Stevany.zip", "-d", "./Musyik", NULL};``` Kita membuat array yang menyimpan perinitah untuk unzip/extract files. Tag ```-j``` digunakan agar tidak dibuat file baru. Disini yang di extract adalah **Musik_for_Stevany.zip** selanjutnya ada ``` "-d", "./Musyik"``` yang gunanya kita akan memindahkan hasil extract tersebut ke folder Musyik. Kemudian array tersebut dieksekusi dengan perintah ```execv```
Seetelah proses extract dan memindahkan musik, dibuat lagi fork baru untuk unzip dan memindahkan foto dan film

## **1E**
Untuk memudahkan Steven, ia ingin semua hal di atas berjalan otomatis 6 jam sebelum waktu ulang tahun Stevany

## **1F**
Setelah itu pada waktu ulang tahunnya Stevany, semua folder akan di zip dengan nama Lopyu_Stevany.zip dan semua folder akan di delete(sehingga hanya menyisakan .zip).
```
if(info.tm_mday == 9 & info.tm_mon + 1 == 4 && 22 - info.tm_hour == 0 && 
        info.tm_min == 22 && executed == 1)
    {
        child_pid = fork();
        if (child_pid == 0)
        {
            char *ZIP[]= {"zip","-r","Lopyu_Stevany.zip","Fylm","Musyik","Pyoto",NULL};
            execv("/bin/zip", ZIP);
        }
        while ((wait(NULL)) > 0);
        child_pid = fork();
        if (child_pid == 0)
        {
            char *delete[]={"rm", "-r", "Fylm", "Musyik", "Pyoto", NULL};
            execv("/bin/rm", delete);
        }
    }
 ```
 Bagian ```if``` berfungsi untuk memberikan kondisi kode di bawah nya akan dijalankan, yaitu pada 9 April pukul 22.22 WIB.
 Selanjutnya dibuat fork untuk proses zip. ```char *ZIP[]= {"zip","-r","Lopyu_Stevany.zip","Fylm","Musyik","Pyoto",NULL}```. Array ini menyimpan perintah untuk membuat satu folder zip dengan nama **Lopyu_Stevany.zip** dimana zip tersebut berisi folder Fylm, Musyik, dan Pyoto. Selanjutnya dieksekusi dengan perintah ```exec```.
 Selanjutnya, ada folder yang harus dihapus. Dengan membuat ``` char *delete[]={"rm", "-r", "Fylm", "Musyik", "Pyoto", NULL};``` kita akan menghapus folder Fylm, Musyik, Pyoto dan mengeksekusinya dengan ```execv("/bin/rm", delete);```.
 

## **Screenshot**

![hasil no1](https://i.ibb.co/7W48ytP/hasil-nomor1.png)

# **Soal 2**
Loba bekerja di sebuah petshop terkenal, suatu saat dia mendapatkan zip yang berisi banyak sekali foto peliharaan dan Ia diperintahkan untuk mengkategorikan foto-foto peliharaan tersebut.
## **2A**

- **Soal**
	Pertama-tama program perlu mengextract zip yang diberikan ke dalam folder “/home/[user]/modul2/petshop”. program harus bisa membedakan file dan folder sehingga dapat memproses file yang seharusnya dikerjakan dan menghapus folder-folder yang tidak dibutuhkan.
- **Penyelsaian**
```
int main() {
	pid_t child;
	int stat;
	
	child = fork();
	
	if(child < 0) {
		exit(EXIT_FAILURE);
	}
	
	if(child == 0) {
		char *argv[] = {"mkdir", "-p", "/home/ahmad/modul2/petshop", NULL};
        	execv("/bin/mkdir", argv);
	}
	else {
		while((wait(&stat)) > 0);
		extract();
		order();
	}
}

```
Dilakkan spawn proses dengan menggunakan fork untuk melakukan proses pembuatan direktori petshop dengan alamat direktori "/home/ahmad/modul2/petshop". Kemudian dengan menggunakan fungsi ```extract()``` untuk mengekstrak pets.zip
```
void extract() {
    	pid_t child;
	int status;

    	child = fork();

    	if (child == 0) {
        	char *argv[] = {"unzip", "/home/ahmad/Downloads/pets.zip",
                        	"-x",    "*/*",
                        	"-d",    "/home/ahmad/modul2/petshop",
                        	NULL};
        	execv("/usr/bin/unzip", argv);
        	exit(EXIT_SUCCESS);
 	}
    	while ((wait(&status)) > 0);
}
```
Pada fungsi ekstrak digunakan command ```-x */*``` agar folder beserta isi pada folder yang tidak diperlukan didalam zip tersebut ikut ter unzip.

## **2B**

- **Soal**

	Foto peliharaan perlu dikategorikan sesuai jenis peliharaan. program harus membuatkan folder-folder yang dibutuhkan sesuai dengan isi zip.
- **Penyelesaian**
```
void order(){
    int status;
    pid_t child;
    child=fork();

    if (child < 0){
        exit(EXIT_FAILURE); 
    }

    if (child == 0){
        DIR *directory;
        directory=opendir("/home/ahmad/modul2/petshop");
        if(directory != NULL){
            struct dirent *ep;
            while((ep = readdir(directory)) != NULL){
                if(ep->d_type == DT_REG){
                    char *temp1, *temp2, *temp3, *temp4;
                    char copy[99], copy2[99], copy3[99];
                    char base2[99], base3[99];
                    char hewan[25], name[25], umur[25];
                    int flag;
			
                    char *fileName = ep->d_name;
                    int length=strlen(fileName);
                    char newName[length];
                    sliceStr(fileName, newName, 0, length-5); 

                    temp1=strtok_r(newName, "_", &temp4);
                    for(;temp1!=NULL;temp1=strtok_r(NULL, "_", &temp4)){
                        flag= 0;
                        char base[99] = "/home/ahmad/modul2/petshop/";
                        strcpy(copy, ep->d_name);
                        strcpy(base2, base);
                        strcpy(base3, base);
                        strcpy(copy2, ep->d_name);
                        strcpy(copy3, ep->d_name);
                        temp3=strtok_r(temp1, ";", &temp2);
                        for (; temp3!=NULL; temp3=strtok_r(NULL, ";", &temp2)){
                            if (flag == 0) strcpy(hewan, temp3);
                            if (flag == 1) strcpy(name, temp3);
                            if (flag == 2) strcpy(umur, temp3);
                            flag=flag+1;
                        }
                    	
			//2b
                        strcat(base, hewan);
                        char *mkFolder[] = {"make-directory", "-p", base, NULL};
                        execute("/bin/mkdir", mkFolder);
```
Dengan menggunakan fungsi bawaan c dirent.h, kita dapat menggunakan DIR untuk membuka directory dan menggunakan struct dirent untuk membaca list folder yang ada di direktori yang dituju. Kemudian dengan menggunakan fungsi tersebut sebagai parameter pada fungsi, diambil string pertama sebelum tanda ";" dimana string tersebut merupakan jenis hewan dan digunakan untuk folder. Kemudian di akhir nanti menggunakan argumen dan fungsi ```execute()``` untuk membuat direktori sesuai dengan jenis nama hewan yang telah dibaca.

## **2C**

- **Soal**

	Setelah folder kategori berhasil dibuat, programm harus memindahkan foto ke folder dengan kategori yang sesuai dan di rename dengan nama peliharaan.
- **Penyelesaian**
```
			strcat(base2, copy2);
                        char *copytoFolder[] = {"cp", "-r", base2, base, NULL};
                        execute("/bin/cp", copytoFolder);

                        strcat(name, ".jpg");
                        strcpy(base3, base);
                        strcat(base3, "/");
                        strcat(base3, copy2);
                        strcat(base, "/");
                        strcat(base, name);
                        char *renameFile[] = {"mv", base3, base, NULL};
                        execute("/bin/mv", renameFile);
```
```
void sliceStr(const char *str, char *buffer, size_t start, size_t end){
    	size_t j = 0;
    	for(size_t i = start; i<=end; ++i) {
        	buffer[j++] = str[i];
    	}
    	buffer[j] = 0;
}
```
Disini gabungkan string yang diambil dengan jpg karena pada fungsi sebelumya terjadi pemotongan format file untuk scanning dan membuat base2 menjadi alamat tujuan. Setelah itu dengan menggunakan ```execute()``` untuk mengeksekusi, dipindahkan dengan menggunakan cp untuk mencopy. Lalu ubah namanya menjadi nama.jpg pada proses rename menggunakan fungsi mv. fungsi sliceStr tadi digunakan untuk memotong jpg untuk menscan list file yang ada di direktori.
## **2D**

- **Soal**

	Karena dalam satu foto bisa terdapat lebih dari satu peliharaan maka foto harus di pindah ke masing-masing kategori yang sesuai. 
- **Penyelesaian**
```
		if(ep->d_type == DT_REG){
                    char *temp1, *temp2, *temp3, *temp4;
                    char copy[99], copy2[99], copy3[99];
                    char base2[99], base3[99];
                    char hewan[25], name[25], umur[25];
                    int flag;
			
                    char *fileName = ep->d_name;
                    int length=strlen(fileName);
                    char newName[length];
                    sliceStr(fileName, newName, 0, length-5); 

                    temp1=strtok_r(newName, "_", &temp4);
                    for(;temp1!=NULL;temp1=strtok_r(NULL, "_", &temp4)){
                        flag= 0;
                        char base[99] = "/home/ahmad/modul2/petshop/";
                        strcpy(copy, ep->d_name);
                        strcpy(base2, base);
                        strcpy(base3, base);
                        strcpy(copy2, ep->d_name);
                        strcpy(copy3, ep->d_name);
                        temp3=strtok_r(temp1, ";", &temp2);
                        for (; temp3!=NULL; temp3=strtok_r(NULL, ";", &temp2)){
                            if (flag == 0) strcpy(hewan, temp3);
                            if (flag == 1) strcpy(name, temp3);
                            if (flag == 2) strcpy(umur, temp3);
                            flag=flag+1;
                        }
```
Loop pertama digunakan untuk memotong nama file string apabila bertemu dengan _ dan loop kedua digunakan untuk memotong nama file string apabila bertemu dengan ; dengan menggunakan fungsi strtok_r dari direktori awal, parameter, dan tempat alamat untuk menyimpan.

## **2E**

- **Soal**

	Di setiap folder buatlah sebuah file "keterangan.txt" yang berisi nama dan umur semua peliharaan dalam folder tersebut.
- **Penyelesaian**
```
                        //2e flag
                        char txtLoc[99], txtPath[99];
                        strcpy(txtLoc, base);
                        strcpy(txtPath, txtLoc);
```
```
                        //2e
                        strcat(txtPath, "/keterangan.txt");
                        strcpy(nama, "nama : ");
                        strcat(nama, namePerAnimal);
                        strcat(nama, "\n");
                        strcat(nama,"umur : ");
                        strcat(nama, umur);
                        strcat(nama," tahun\n\n");
 
                        FILE *fPtr = fopen(txtPath, "a");
                        fputs(nama, fPtr);
                        fclose(fPtr);
```
 
Kemudian, untuk memasukkan file txt sendiri dengan cara membuat path baru berisi "keterangan.txt", dan kemudian memasukkan nilai dalam variabel name, dan age pada file dengan format yang telah ditentukan. Setelah file selesai diappend, file akan ditutup kembali. Untuk memasukkan file juga masih di dalam looping pemisahan string yang awal.
```
 		if (ep->d_type == DT_REG){
                    char path[99] = "/home/ahmad/modul2/petshop/";
                    strcat(path, ep->d_name);
                    char *removeFile[] = {"remove file","-r", "-f", path, NULL};
                    execute("/bin/rm", removeFile);
```
Setelah serangkaian proses dijalankan hal yang terakhir dilakukan adalah menghapus file foto yang telah diproses.
## **Kesulitan**
Terdapat kendala pada compiler sehingga sempat bingung program tidak berjalan karena compiler atau error.Lalu, fungsi yang digunakan sebagian besar merupakan fungsi yang tidak ada dimodul/belum pernah dicoba sehingga kebingunan fungsi mana yang harus digunakan.

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
