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

//MAIN PROGRAM	
int main(){
	//Inisialisasi File
	FILE* fp;
	fp = fopen("input2.txt", "r");
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
	printf("Teks yang terbaca: \n");
	printf("\n");
	for (int i=0; i<JumlahKey; i++){
		printf("%s ", key[i].StringKey);}
	printf("\n");
	printf("\n");
	
	//Input nilai N
	printf("Masukkan N: "); scanf("%d", &N);
	printf("\n");
	
	//InsertKey bertugas memasukkan key ke dalam linked list
	InsertKey(&nodal, key, JumlahKey, N-1);
	
	//Menghapus nodal pertama (inisialisasi)
	nodal = nodal->next;
	
	//InsertValue bertugas memasukkan value ke dalam linked list
	InsertValue(&nodal, key, JumlahKey, N-1);
	
	printf("KEY    dan     VALUE\n");
	PrintList(nodal);
	fclose(fp);
	return 0;
}

