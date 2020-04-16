#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <conio.h>

//DEKLARASI STRUCT DAN LINKED LIST

//struct Node ialah linked list yang menyimpan key dan value
struct Node{
	 char* key;
	 char* value;
	 struct Node* next;};


//struct MyData ialah bentukan yang menyimpan tiap kata dari file eksternal	 
struct MyData{
	char StringKey[50];};
	

//DEKLARASI FUNGSI DAN PROSEDUR

//fungsi PrintList berfungsi untuk mencetak pasangan key dan value
void PrintList(struct Node* X){
	while (X != NULL){
		printf("Key: %s ,", X->key);
		printf(" Value: %s \n", X->value);
		X = X->next; }}

//fungsi InsertKey digunakan untuk memasukkan key ke dalam linked list
//fungsi bekerja dengan membaca kata yang disimpan dalam array statis (bertipe MyData), melakukan konkatenasi berdasarkan N-grams
//lalu menyimpan key dalam linked list
void InsertKey (struct Node** head, struct MyData n[10000], int JumlahKey, int N){
	int i; int j;
	for (i=0; i<JumlahKey; i++)
	{
		struct Node* nodebaru = (struct Node*) malloc (sizeof(struct Node));
		struct Node* temp = *head;
		char *str =(char*) malloc (1000); //str bertugas menyimpan kata yang akan diconcat, lalu dimasukkan dalam node
		strcpy(str, n[i].StringKey); //menyalin kata ke i dalam array key menuju str
		
		//melakukan penyambungan kata per kata dan pemberian spasi untuk membentuk suatu key
		for (j=0; j<N; j++)
		{ 
			strcat(str, " ");
			if (i+j+1 >= JumlahKey)
			{
				strcat(str, n[i+j+1-JumlahKey].StringKey);
			}
			else
			{ 
				strcat(str, n[i+j+1].StringKey);
			}
		}
		nodebaru->key = str;
		nodebaru->next = NULL;
	//memasukkan node ke dalam linked list
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = nodebaru;
	}
} 
	
	
//Fungsi InsertValue berfungsi untuk memasukkan value ke dalam linked list
//Fungsi bekerja dengan menggeser kata-kata dalam array statis sejauh N
//Lalu memasukkan kata tersebut ke dalam linked list yang bersesuaian indeksnya
void InsertValue (struct Node** head, struct MyData key[10000], int JumlahKey, int N){
	struct Node* temp = *head;
	int i;
	for (i = 0; i<JumlahKey; i++)
	{
		char *str=(char*) malloc (1000);
		//Kalau indeks sudah lebih dari jumlah key, kembali ke key[0] (membuat pembacaan secara circular)
		if ((i+N+1) >= JumlahKey)
		{
			strcpy(str, key[i+N+1 - JumlahKey].StringKey);
		}
		else
		{
			strcpy(str, key[i+N+1].StringKey);
		}
		temp->value = str;
		temp=temp->next;
	}
}
		
//Fungsi isUnique berfungsi untuk menentukan apakah suatu key unik 
int isUnique(char input[50],struct Node*head)
{
    int unik = 0; // inisialisasi
    while ((head!=NULL) && (unik<2))
    {
        if (strcmp(head->key,input)==0)
        {
            unik = unik + 1; // Jika ketemu key yang sama, unik ++
        }
        head = head->next; // ke bagian selanjutnya
    }
//Jika Unik(1 key dalam daftar key-value), maka return 1
    if (unik == 1)
    {
        return 1;
    }
//Jika tidak, return 0
    else
    {
        return 0;
    }
}

//Fungsi randomizer berfungsi untuk mengacak value apabila ditemukan lebih dari 1
//Fungsi ini menyimpan value-value dari key yang sama dalam suatu array temp
//Lalu mencetak salah satunya saja secara acak
void randomizer(char str[50], struct Node* head, char* string){
	struct data
	{
	char value[50];
	};
	  
	int i=0;
	int j=0;
	int hasil_random;
	struct data temp[500];
	while (head!=NULL)
	{	
		if (strcmp(str,head->key)==0)
		{
			strcpy((temp[i].value),(head->value));
			i=i+1;
		}
		head=head->next;
		j=j+1;
	}
    hasil_random = (rand() % (i));
    strcpy(string, (temp[hasil_random].value));
return;
}

//Fungsi print_Hasil berfungsi melakukan pencetakan random words sebanyak jumlah_kata - N
void print_Hasil(int jumlah_kata, char str1[50],struct Node* head, int N)
{
    struct Node* temp;
    int i = 1;
    temp = head;
    char* str = str1;
    while (i<=jumlah_kata-N)
    {
		//Proses menemukan node dengan key yang sama dengan str
		while (strcmp(str,temp->key)!=0)
		{
        temp = temp->next;
        }
        char* string = (char*) malloc (50);
        //Apabila key tersebut unik, maka valuenya akan langsung disimpan dalam variabel "string"
        //Apabila key tersebut tidak unik, maka valuenya akan ditentukan dari randomizer, lalu disimpan dalam variabel "string"
		//"string" ini kemudian dicetak 
		if (isUnique((temp->key),head)==1)
		{
			strcpy(string, temp->value);
		}
		else
		{
			randomizer(temp->key, head, string);
		}
		printf(" %s", string);
		i= i + 1;
		
		//Untuk menentukan key selanjutnya yang akan dicari valuenya
		//Kata pertama dari key sebelumnya akan dihapus
		//Lalu ditambahkan/concatenate dengan spasi dan kata dari value dalam "string" yang tadinya telah dicetak
		char *newkey;
		for (newkey = str ; *newkey && *newkey != ' ' ; newkey++) ;
		if (*newkey) newkey++;
		strcpy(str, newkey);
		if (N != 1)
		{
			strcat(str, " ");
		}
		strcat(str, string);
		temp = head;
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
    
    while(pilihan != 2){
        printf("\n\n----------Main Menu------------\n");
        printf("Silahkan pilih menu berikut.\n");
        printf("1. Input file .txt dan mulai program\n");
        printf("2. Keluar Program\n");
        printf("Pilihan Menu (angka 1 atau 2) : ");
        scanf("%d", &pilihan);
        
        while (pilihan != 1 && pilihan != 2){
			printf("Maaf, input tidak valid. Silahkan ulangi kembali.\n");
			printf("Pilihan Menu (angka 1 atau 2) : ");
			scanf("%d", &pilihan);}

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
            nodal->next = NULL;
        
            //key[10000] berfungsi sebagai array statis untuk menyimpan kata per kata yang dibaca dari file
            struct MyData key[10000];
        
            //char dataku berfungsi untuk menyimpan tiap kata yang terbaca (menyimpan 1 kata saja secara temporary).
            char dataku[50];
        
            //Membaca data dan memasukkan kata per kata ke dalam array key[10000]
            int JumlahKey = 0;
            while (fscanf(fp, "%s", dataku)==1)
            {
				strcpy(key[JumlahKey].StringKey, dataku);
				JumlahKey++;
			}
                       
            //Input nilai N
            printf("Masukkan N (berapa N-gram) : "); scanf("%d", &N);
            
            //InsertKey bertugas memasukkan key ke dalam linked list
            InsertKey(&nodal, key, JumlahKey, N-1);
            
            //Menghapus nodal pertama (inisialisasi)
            nodal = nodal->next;
            
            //InsertValue bertugas memasukkan value ke dalam linked list
            InsertValue(&nodal, key, JumlahKey, N-1);
            
            int pilihmenu = 0;
            while(pilihmenu!=4){
            printf("\n--Menu Program--\n");
            printf("1. Tampilkan Teks yang terbaca \n");
            printf("2. Tampilkan Tabel Daftar Key dan Value \n");
            printf("3. Mulai proses cetak random word. (dapat diulangi) \n");
            printf("4. Keluar sekuens dan kembali ke main menu. \n");
            printf("Pilihan Menu (angka) : ");
            scanf("%d", &pilihmenu); 
            
            while(pilihmenu != 1 && pilihmenu != 2 && pilihmenu != 3 && pilihmenu != 4){
			printf("Maaf, input anda tidak valid. Silahkan ulangi kembali.\n");
			printf("Pilihan Menu (angka) : ");
            scanf("%d", &pilihmenu);}  
            
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
                        int numinput; char userinput[30]; struct Node* awal;
                        int pilihrandom = (rand () % (JumlahKey));
                        awal = nodal;
                        
                        //Meminta input jumlah kata random
                        printf("\nMasukkan Jumlah Random Words yang ingin di cetak : ");
                        scanf("%d", &numinput);
                        
                        gets(sampah);
                        for (int i = 0; i<pilihrandom; i++)
                        {
							awal = awal->next;
						}
						strcpy (userinput, awal->key);
						
						//Cetak kata
                        printf("\n-----Hasil processing-----\n");
                        printf("\n... %s",userinput);
                        print_Hasil(numinput, userinput, nodal, N);
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
