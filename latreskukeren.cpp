#include <iostream>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <iomanip>

#define True 1
#define False 2

using namespace std;

typedef char typeinfo;
typedef struct typequeue *typeptr;
struct data{
	char  nama[30], alamat[50], namaObat[20];
	int hargaObat;
};
struct simpan{
	char  nama[30], alamat[50], namaObat[20];
	int hargaObat;
};
struct typequeue{
	typeptr prev;
	typeptr next;
	data info;
	simpan info2;
};


typeptr Qdepan, Qbelakang, Qdepan1, Qbelakang1;
void createQueue();
int queueKosong();
void enqueue(char nama2[], char alamat2[], char namaObat2[], int hargaObat2);
void dequeue();
void cetakQueue();
void cetakQueueRiwayat();
void cancel();
int Antrian = 0, antrianRiwayat = 0;
char namaHapus[30];

int main(){
	int pilih, hargaObat2, antrian;
	char kembali, nama2[30], alamat2[50], namaObat2[20];
	
	do{
		menuutama:
		antrian = 1;
		system("cls");
		if(!queueKosong()){
			cetakQueue();
		}
		cout<<"------------------------------"<<endl;
		cout<<"=== PROGRAM APOTEK ABADI ==="<<endl;
		cout<<"------------------------------"<<endl;
		cout<<" Menu : "<<endl;
		cout<<" 1. Beli Obat"<<endl;
		cout<<" 2. Lihat Daftar Pembeli"<<endl;
		cout<<" 3. Layani Pembeli"<<endl;
		cout<<" 4. Riwayat Pembelian"<<endl;
		cout<<" 5. Pembatalan Pembelian"<<endl;
		cout<<" 6. Exit"<<endl;
		cout<<" Pilih menu : ";cin>>pilih;
		switch(pilih){
			case 1 :
			{
				cout<<endl<<"== Menu Input Pembeli Obat-obatan";
				cout<<endl<<"---------------------------------------";
				if(queueKosong()){
					createQueue();
				}
				while(antrian == 1){
					if(!queueKosong()){
						cetakQueue();
					}
				Antrian++;
				cout<<endl<<"== Input Pembeli"<<endl;
				cout<<" Masukkan Nama : ";cin.ignore();cin.getline(nama2,sizeof(nama2));
				cout<<" Masukkan Alamat : ";cin.getline(alamat2,sizeof(alamat2));
				cout<<" Masukkan Nama Obat Yang dibeli : ";cin.getline(namaObat2,sizeof(namaObat2));
				cout<<" Masukkan Harga Obat : ";cin>>hargaObat2;
				enqueue(nama2,alamat2,namaObat2,hargaObat2);
				cout<<endl<<" Tekan 1 Untuk Menambah Pembelian || Tekan 0 untuk Kembali ke Menu ";
				cin>>antrian; 
				system("cls");
				}
			}
			break;
			case 2 :
			{
				cout<<endl<<"== Menu Daftar Pembeli";
				cout<<endl<<"---------------------------------------";
				if(!queueKosong()){
					cetakQueue();
				}else
					cout<<"== Tidak Ada Pembeli !!"<<endl;
			}
			break;
			case 3 : 
			{
				cout<<endl<<"== Menu Layani Pembeli";
				cout<<endl<<"---------------------------------------"<<endl;
				if(!queueKosong()){
					dequeue();
				}else
					cout<<"== Tidak Ada Pembeli !!"<<endl;
			}
			break;
			case 4 :
			{
				cout<<endl<<"== Menu Riwayat Pembelian";
				cout<<endl<<"---------------------------------------"<<endl;
				if(antrianRiwayat != 0){
					cetakQueueRiwayat();
				}else
					cout<<"== Belum Ada Pembeli !!"<<endl;
			}
			break;
			case 5 :
			{
				cout<<endl<<"== Menu Pembatalan Pembelian";
				cout<<endl<<"---------------------------------------"<<endl;
				if(!queueKosong()){
					cancel();
					cout<<"== Tidak Jadi Membeli !!"<<endl;
				}else
					cout<<"== Belum Ada Pembeli !!"<<endl;
			}
			break;
			case 6 :
			{ 
				exit(0);
			break;
			default : 
				cout<<endl<<"Input Yang Anda Masukan SALAH ! "<<endl;
			}
			break;
		}
		cout<<"Kembali ke menu ?[ y/n ] : ";cin>>kembali;
	}while(kembali == 'y' || kembali == 'Y');
}

void createQueue(){
	Qdepan = (typequeue *) malloc(sizeof(typequeue));
	Qdepan = NULL;
	Qbelakang = Qdepan;
	
	//== > Riwayat < ==
	Qdepan1 = (typequeue *) malloc(sizeof(typequeue));
	Qdepan1 = NULL;
	Qbelakang1 = Qdepan;	
}

int queueKosong(){
	if(Qdepan == NULL){
		return(true);
	}else
		return(false);
}

void enqueue(char nama2[], char alamat2[], char namaObat2[], int hargaObat2){
	typeptr NB;
	NB = (typequeue *) malloc(sizeof(typequeue));
	strcpy(NB->info.nama,nama2);
	strcpy(NB->info.alamat,alamat2);
	strcpy(NB->info.namaObat,namaObat2);
	NB->info.hargaObat = hargaObat2;
	
	if(Qdepan == NULL){
		Qdepan = NB;
	}else
		Qbelakang->next = NB;
		
	Qbelakang = NB;
	Qbelakang->next = NULL;
}

void dequeue(){
	typeptr hapus;
	if(queueKosong()){
		cout<<" Queue masih kosong !!";
	}else{
		hapus = Qdepan;
		Qdepan = hapus->next;
	{
		typeptr NB;
		NB = (typequeue *) malloc(sizeof(typequeue));
		strcpy(NB->info2.nama, hapus->info.nama);
		strcpy(NB->info2.alamat, hapus->info.alamat);
		strcpy(NB->info2.namaObat, hapus->info.namaObat);
		NB->info2.hargaObat = hapus->info.hargaObat;
		if(Qdepan1 == NULL)
			Qdepan1 = NB;
		else
			Qbelakang1->next = NB;
		
		Qbelakang1 = NB;
		Qbelakang1->next = NULL;
		antrianRiwayat++;
	}
		free(hapus);
		Antrian--;
		cout<<"== Pelayanan "<<Qbelakang1->info2.nama<<" Selesai"<<endl;
	}
}

void cetakQueue(){
	typeptr bantu;
	int i = 0;
	bantu = Qdepan;
	cout<<endl<<"                                   == DAFTAR PEMBELI == ";
	cout<<endl<<"-----------------------------------------------------------------------------------------------"<<endl;
	cout<<setw(4)<<" No "<<setw(15)<<" Nama "<<setw(25)<<" Alamat "<<setw(25)<<" Obat "<<setw(35)<<" Harga "<<endl;
	do{
		i++;
		cout<<setw(4)<< i <<setw(15)<< bantu->info.nama <<setw(25)<< bantu->info.alamat <<setw(25)<< bantu->info.namaObat <<setw(35)<< bantu->info.hargaObat <<endl;
		bantu = bantu->next;
	}while(bantu!=NULL && i!= Antrian);
	cout<<endl<<"Jumlah Antrian : "<<Antrian;
	cout<<endl<<endl;
}

void cetakQueueRiwayat(){
	typeptr bantu;
	int i = 0;
	bantu = Qdepan1;
	cout<<endl<<" == RIWAYAT PEMBELIAN == ";
	cout<<endl<<"-----------------------------------"<<endl;
	cout<<setw(4)<<" No "<<setw(10)<<" Nama "<<setw(20)<<" Alamat "<<setw(20)<<" Obat "<<setw(30)<<" Harga "<<endl;
	do{
		i++;
		cout<<setw(4)<< i <<setw(10)<< bantu->info2.nama <<setw(20)<< bantu->info2.alamat <<setw(20)<< bantu->info2.namaObat <<setw(30)<< bantu->info2.hargaObat <<endl;
		bantu = bantu->next;
	}while(bantu != NULL && i != antrianRiwayat);
	cout<<endl<<"Jumlah Antrian : "<<Antrian;
	cout<<endl<<endl;
}

void cancel(){
	typeptr hapus;
	if(queueKosong()){
		cout<<" Queue Masih Kosong !";
	}else{
		hapus = Qbelakang;
		strcpy(namaHapus, hapus->info.nama);
		if(hapus == Qdepan){
			free(hapus);
			Qdepan = Qbelakang = NULL;
		}else{
			Qbelakang = hapus->prev;
			free(hapus);
			Qbelakang->next=NULL;
		}
		Antrian--;
		cout<<endl<<namaHapus<<" ";
	}
}
