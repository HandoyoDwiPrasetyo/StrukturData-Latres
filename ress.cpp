#include <iostream>
#include <string.h>
#include <malloc.h>
using namespace std;

struct logistik {
	char nama[30], kategori[30];
	int berat, harga, pk, jenis;
};
typedef struct typequeue *typeptr;
struct typequeue {
	logistik data;
	typeptr next;
};
typeptr qDepan, qBelakang;

void buatQueue();
int queueKosong();
void enqueue(logistik newData);
void inputData();
void dequeue();
void cetakQueue();
int getOption();

int main() {
	buatQueue();
	char is_continue;
	enum option {CREATE = 1, READ, DELETE, FINISH};
	
	int pilihan = getOption();
	
	while(pilihan != FINISH) {
		switch(pilihan) {
			case CREATE:
				cout << "Input Data" << endl;
				cout << "==========" << endl;
				inputData();
				break;
			case READ:
				cout << "Daftar Data" << endl;
				cout << "===========" << endl;
				cetakQueue();
				break;
			case DELETE:
				cout << "Pengiriman" << endl;
				cout << "==========" << endl;
				dequeue();
				break;
			default:
				cout << "Pilihan tidak ditemukan!" << endl;
				break;
		}
		
		label_continue:
		
		cout << "\nLanjutkan ke menu?(y/n) : "; cin >> is_continue;
		if((is_continue == 'y') | (is_continue == 'Y')) {
			pilihan = getOption();
		} else if ((is_continue == 'n') | (is_continue == 'N')) {
			break;
		} else {
			goto label_continue;
		}
	}
	
	cout << "\nAkhir dari program" << endl;
	
	return 0;
}

int getOption() {
	int pilih;
	system("cls");
	cout << "Menu" << endl;
	cout << "===============" << endl;
	cout << "1. Input Data" << endl;
	cout << "2. Daftar Data" << endl;
	cout << "3. Pengiriman" << endl;
	cout << "4. Exit" << endl;
	cout << "===============" << endl;
	cout << "Pilih [1-4]? : "; cin >> pilih;
	
	return pilih;
}

void buatQueue() {
	qDepan = (typequeue *) malloc(sizeof(typequeue));
	qDepan = NULL;
	qBelakang = qDepan;
}

int queueKosong() {
	if(qDepan == NULL)
		return true;
	else
		return false;
}
void enqueue(logistik newData) {
	typeptr NB;
	NB = (typequeue *)malloc(sizeof(typequeue));
	NB->data = newData;
	if (NB->data.jenis > 1){
		if(queueKosong()) {
			qDepan = NB;
			qBelakang = qDepan;
		} else if (NB->data.jenis < qDepan->data.jenis) {
			NB->next = qDepan->next;
			qDepan->next = NB;
		} else {
			NB->next = qDepan;
			qDepan = NB;
		}
	} else { 
		if(queueKosong()) {
			qDepan = NB;
			qBelakang = qDepan;
		} else {
			qBelakang->next = NB;
			qBelakang = NB;
			qBelakang->next = NULL;
		}
	}
	
	/*
	typeptr NB;
	NB = (typequeue *)malloc(sizeof(typequeue));
	NB->data = newData;
	if (NB->data.jenis > 1){
		if (NB->data.harga > qDepan->data.harga && qDepan != NULL) {
			NB->next = qDepan;
			qDepan = NB;
		} else {
			if(queueKosong()) {
				qDepan = NB;
				qBelakang = qDepan;
			} else if (NB->data.jenis < qDepan->data.jenis) {
				NB->next = qDepan->next;
				qDepan->next = NB;
			} else {
				NB->next = qDepan;
				qDepan = NB;
			}
		}
		
	} else { 
		if(queueKosong()) {
			qDepan = NB;
			qBelakang = qDepan;
		} else {
			qBelakang->next = NB;
			qBelakang = NB;
			qBelakang->next = NULL;
		}
	}
	 */
}

void inputData() {
	char is_continue;
	logistik inputData;
	inputData.pk = 1;
	int pilihKategori;
	do {
		cout << "Data ke-" << inputData.pk << endl;
		cout << "Nama : "; cin >> inputData.nama;
		cout << "Kategori" << endl;
		cout << "1. Lambat +Rp 0" << endl;
		cout << "2. Biasa +Rp 10.000" << endl;
		cout << "3. Cepat +Rp 30.000" << endl;
		cout << "Pilih Kategori [1-3] : "; cin >> pilihKategori;
		cout << "Berat : "; cin >> inputData.berat;
		if (inputData.berat < 1) {
			inputData.harga = 20000;
		} else if (inputData.berat >= 1 && inputData.berat <= 10) {
			inputData.harga = 100000;
		} else if (inputData.berat > 10) {
			inputData.harga = 100000 + ((inputData.berat - 10) * 10000);
		}
		
		if (pilihKategori == 1) {
			strcpy(inputData.kategori, "Lambat");
			inputData.harga += 0;
			inputData.jenis = 1;
		} else if (pilihKategori == 2) {
			strcpy(inputData.kategori, "Biasa");
			inputData.harga += 10000;
			inputData.jenis = 2;
		} else if (pilihKategori == 3) {
			strcpy(inputData.kategori, "Cepat");
			inputData.harga += 30000;
			inputData.jenis = 3;
		}
		enqueue(inputData);
		inputData.pk++;
		
		cout << "\nInput data lagi?(y/n) : "; cin >> is_continue;
	} while((is_continue == 'y') | (is_continue == 'Y'));
}

void dequeue() {
	typeptr hapus;
	if(queueKosong()) { 
		cout << "Data masih kosong !";
	} else {
		hapus = qDepan;
		qDepan = hapus->next;
		free(hapus);
	}
}

void cetakQueue() {
	typeptr bantu;
	bantu = qDepan;
	do {
		cout << "Data ke-" << bantu->data.pk << endl;
		cout << "Nama : " << bantu->data.nama << endl;
		cout << "Kategori : " << bantu->data.kategori << endl;
		cout << "Berat : " << bantu->data.berat << endl;
		cout << "Harga : " << bantu->data.harga << endl;
		bantu = bantu->next;
	} while(bantu != NULL);
}

