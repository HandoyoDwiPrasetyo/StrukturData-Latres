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
	char  nama[30], penyakit[20];
	int umur;
};
struct simpan{
	char  nama[30], penyakit[20];
	int umur;
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
void enqueue(char nama2[], char penyakit2[], int umur2);
void dequeue();
void cetakQueue();
int Antrian = 0, antrianRiwayat = 0;
char namaHapus[30];

int main(){
	int pilih, umur2, antrian;
	char kembali, nama2[30], penyakit2[20];
	
	do{
		antrian = 1;
		system("cls");
		if(!queueKosong()){
			cetakQueue();
		}
		cout<<"======RS NAKULA======"<<endl;
		cout<<" Menu : "<<endl;
		cout<<" 1. Tambah Pasien"<<endl;
		cout<<" 2. Daftar Antrian Pasien"<<endl;
		cout<<" 3. Panggil Pasien"<<endl;
		cout<<" 4. Exit"<<endl;
		cout<<" Pilih menu : ";cin>>pilih;
		switch(pilih){
			case 1 :
			{
				if(queueKosong()){
					createQueue();
				}
				while(antrian == 1){
					if(!queueKosong()){
						cetakQueue();
					}
				Antrian++;
				cout<<endl<<"Input Pasien"<<endl;
				cout<<"Nama : ";cin.ignore();cin.getline(nama2,sizeof(nama2));
				cout<<"Penyakit : ";cin.getline(penyakit2,sizeof(penyakit2));
				cout<<"Umur Pasien : ";cin>>umur2;
				enqueue(nama2,penyakit2,umur2);
				cout<<endl<<"1 Untuk Menambah Pasien/0 untuk ke Menu ";
				cin>>antrian; 
				system("cls");
				}
			}
			break;
			case 2 :
			{
				if(!queueKosong()){
					cetakQueue();
				}else
					cout<<"Pasien Tidak Ada, Silahkan Masukkan Daftar Pasien"<<endl;
			}
			break;
			case 3 : 
			{
				cout<<endl<<"Memanggil Pasien";
				if(!queueKosong()){
					dequeue();
				}else
					cout<<"Pasien Tidak Ada, Silahkan Masukkan Daftar Pasien"<<endl;
			}
			break;
			case 4 : 
				exit(0);
			break;
			default : 
				cout<<endl<<"Input Salah"<<endl;
			break;
		}
		cout<<"Kembali ke menu?(y/n)";cin>>kembali;
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

void enqueue(char nama2[], char penyakit2[], int umur2){
    typeptr NB;
    NB = (typequeue *) malloc(sizeof(typequeue));
    strcpy(NB->info.penyakit,penyakit2);
    strcpy(NB->info.nama,nama2);
    NB->info.umur = umur2;
   if (NB->info.umur > 60){
        if(queueKosong()){
            Qdepan=NB;
            Qbelakang=Qdepan;
        }
        else{
            NB->next=Qdepan;
            Qdepan=NB;
        }
    }
    else { 
		if(queueKosong()){
			Qdepan = NB;
			Qbelakang=Qdepan;
		}
		else{
        Qbelakang->next = NB;
		Qbelakang = NB;
		Qbelakang->next = NULL;
		}
	}
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
		strcpy(NB->info2.penyakit, hapus->info.penyakit);
		NB->info2.umur = hapus->info.umur;
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
		cout<<"\nMemanggil Pasien Atas Nama "<<Qbelakang1->info2.nama<<endl;
		cout<<"\nPasien Selanjutnya Harap Bersiap"<<endl;	
	}
}

void cetakQueue(){
	typeptr bantu;
	int i = 0;
	bantu = Qdepan;
	cout<<"======Daftar Pasien======"<<endl;
	do{
		i++;
		cout<<"NO 		: "<< i <<endl<<"Nama 		: "<< bantu->info.nama <<endl<<"Penyakit 	: " << bantu->info.penyakit <<endl<<"Umur 		: "<< bantu->info.umur <<endl;
		cout<<"\n";
		bantu = bantu->next;
	}while(bantu!=NULL && i!= Antrian);
	cout<<endl<<"Jumlah Antrian : "<<Antrian;
	cout<<endl<<endl;
}

