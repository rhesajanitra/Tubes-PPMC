#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <conio.h>

//DEKLARASI STRUCT DAN LINKED LIST
struct Node{
	 char* key;
	 char* value;
	 int jumlah;
	 struct Node* next;};
	 
struct Key{
	 char* data;
	 struct Key* next;};
	 
struct MyData{
	char StringKey[50];};
	

//DEKLARASI FUNGSI DAN PROSEDUR
void PrintList(struct Node* X){
	while (X != NULL){
		printf("Key: %s ,", X->key);
		printf(" Value: %s \n", X->value);
		X = X->next; }}

//Memasukkan key ke dalam linked list
void InsertKey (struct Node** head, struct MyData n[10000], int JumlahKey, int N){
	int i; int j;
	for (i=0; i<JumlahKey; i++){
		struct Node* nodebaru = (struct Node*) malloc (sizeof(struct Node));
		struct Node* temp = *head;
		//str bertugas menyimpan kata yang akan diconcat, lalu dimasukkan dalam node
		char *str =(char*) malloc (1000);
		strcpy(str, n[i].StringKey);
		for (j=0; j<N; j++){
			strcat(str, " ");
			if (i+j+1 >= JumlahKey){
				strcat(str, n[i+j+1-JumlahKey].StringKey);}
			else{ 
				strcat(str, n[i+j+1].StringKey);}}
		nodebaru->key = str;
		nodebaru->jumlah = 1;
		nodebaru->next = NULL;
	while (temp->next != NULL){
		temp = temp->next;}
	temp->next = nodebaru;}}
	
	
//Memasukkan value ke linked list
void InsertValue (struct Node** head, struct MyData key[10000], int JumlahKey, int N){
	struct Node* temp = *head;
	int i;
	for (i = 0; i<JumlahKey; i++){
		char *str=(char*) malloc (1000);
		//Kalau indeks sudah lebih dari jumlah key, kembali ke key[0]
		if ((i+N+1) >= JumlahKey){
			strcpy(str, key[i+N+1 - JumlahKey].StringKey);}
		else{
			strcpy(str, key[i+N+1].StringKey);}
		temp->value = str;
		temp=temp->next;}}
//Fungsi untuk menentukan apakah suatu key unik 
int isUnique(char input[50],struct Node*head)
{
    int unik=0; // inisialisasi
    while ((head!=NULL) && (unik<2))
    {
        if (strcmp(head->key,input)==0)
        {
            unik = unik + 1; // Jika ketemu yang sama, unik ++
        }
        head=head->next; // ke bagian selanjutnya
    }
//Jika Unik(1 key dalam daftar key-value), maka return 1
    if (unik==1)
    {
        return 1;
    }
//Jika tidak, return 0
    else
    {
        return 0;
    }
}
// Prosedur untuk merandom value yang dipilih apabila terdapat beberapa key yang sama
void randomizer(char str[50], struct Node* head){
  struct data
  {
    char value[20];
  };
  int i=0;
  int j=0;
  int hasil_random;
  struct data temp[500];
  while (head!=NULL)
  {
      if (strcmp(str,head->key)==0)
      {
          strcpy((temp[i].value),(head->value));//Memasukkan ke array berisi value
          i=i+1;
      }
      head=head->next;
      j=j+1;
  }
    hasil_random = (rand() % (i));// Memilih index random dari array value dari key yang sama
    printf(" %s",temp[hasil_random].value); // Menulis hasil random
    return;
}
//Prosedur menulis hasil akhir sesuai request user
void print_Hasil(int ngram, int jumlah_kata,char str[50],struct Node* head)
{
    struct Node* temp;
    int i=1;
    temp = head;
    int hasil;
    while (strcmp(str,temp->key)!=0) //mencari titik mulai penulisan 
    {
        temp = temp->next;
    }
    while (i<=jumlah_kata-ngram)
    {
        if (isUnique((temp->key),head)==1) // Jika Unik, tulis value
        {
            printf(" %s",temp->value);

        }
        else
        {
            randomizer(temp->key,head); // Jika tidak, value dirandom
        }
        i= i +1;
	//Jika sudah ujung, putar ke awal lagi
        if (temp->next==NULL)
        {
            temp=head;
        }
        else
        {
            temp=temp->next;
        }
    }
}


//MAIN PROGRAM	
int main(){
	//Inisialisasi File
	FILE* fp;

    int pilihan;
    printf("\n-----------------------------------------------------------------------------\n");
    printf("Selamat datang di N-Gram Word Prediction based on NLP Program by Kelompok C2 \n");
    printf("-----------------------------------------------------------------------------\n");
    printf("\n------------------------------------------Program Description--------------------------------------------\n");
    printf("Program ini mampu mengolah data string dari file external dengan ekstensi .txt sebanyak maksimal 10000 kata.\n");
    printf("Setiap string tersebut akan diproses sesuai dengan N-Gram yang dipilih oleh user ke dalam bentuk key and value.\n");
    printf("User mencetak kata - kata random sejumlah kata yang diinginkan dan dimulai dari kata sesuai dengan input user.\n");
    pilihan = 0;
    
    while(pilihan !=2){
        printf("\n\n----------Main Menu------------\n");
        printf("Silahkan pilih menu berikut.\n");
        printf("1. Input file .txt dan mulai program\n");
        printf("2. Keluar Program\n");
        
        printf("Pilihan Menu (angka 1 atau 2) : ");
        scanf("%d", &pilihan);

        if (pilihan == 1)
        {
            char file[30], sampah[20];
            gets(sampah);
            printf("Anda memilih untuk input file, silahkan masukkan nama file : ");
            gets(&file);
            fp = fopen(file, "r");

            int N;
        
            //Inisialisasi elemen pertama dari linked list
            struct Node* nodal = (struct Node*) malloc (sizeof(struct Node));
            nodal->key = "Inisialisasi";
            nodal->value = "Inisialisasi";
            nodal->jumlah = 1;
            nodal->next = NULL;
        
            //key[1000] berfungsi untuk menyimpan kata per kata yang dibaca dari file
            struct MyData key[10000];
        
            //char dataku berfungsi untuk menyimpan tiap kata yang terbaca (menyimpan 1 kata saja secara temporary).
            char dataku[50];
        
            //Membaca data dan memasukkan ke dalam array key[1000]
            int JumlahKey = 0;
            while (fscanf(fp, "%s", dataku)==1){
            strcpy(key[JumlahKey].StringKey, dataku);
            JumlahKey++;}
                       
            //Input nilai N
            printf("Masukkan N (berapa N-gram) : "); scanf("%d", &N);
            
            //InsertKey bertugas memasukkan key ke dalam linked list
            InsertKey(&nodal, key, JumlahKey, N-1);
            
            //Menghapus nodal pertama (inisialisasi)
            nodal = nodal->next;
            
            //InsertValue bertugas memasukkan value ke dalam linked list
            InsertValue(&nodal, key, JumlahKey, N-1);
            
            int pilihmenu;
            while(pilihmenu!=4){
            printf("\n--Menu Program--\n");
            printf("1. Tampilkan Teks yang terbaca \n");
            printf("2. Tampilkan Tabel Daftar Key dan Value \n");
            printf("3. Mulai proses cetak random word. (dapat diulangi) \n");
            printf("4. Keluar sekuens dan kembali ke main menu. \n");
            printf("Pilihan Menu (angka) : ");
            scanf("%d", &pilihmenu); 
            
            if (pilihmenu == 1)
            {
                printf("Teks yang terbaca: \n");
                printf("\n");
                
                for (int i=0; i<JumlahKey; i++){
                    printf("%s ", key[i].StringKey);}
                    printf("\n");
                }
            else if (pilihmenu == 2)
                {
                        printf("KEY    dan     VALUE\n");
                        PrintList(nodal);
                }

            else if (pilihmenu == 3)
                {
                        //Proses mencetak huruf - huruf random
                        int numinput; char userinput[30];
                        printf("\nMasukkan Jumlah Random Words yang ingin di cetak : ");
                        scanf("%d", &numinput);
                        gets(sampah);
		   	int pilihrandom = (rand () % (JumlahKey));
                        struct Node* awal;
                        awal = nodal;
                        for (int i = 0; i<pilihrandom; i++){
				awal = awal->next;}
			strcpy (userinput, awal->key);
                        printf("\n-----Hasil processing-----\n");

                        printf("\n... %s",userinput);
                        print_Hasil(N,numinput, userinput, nodal);
                        printf(" ...\n");
                }
            else 
                { printf("Anda keluar dari sekuens ini. Silahkan kembali ke main menu.\n");}}
        }

        else
        {
            printf("Anda berhasil keluar program, selamat jalan dan terimakasih!\n");
        }

	fclose(fp);}
	return 0;
}

