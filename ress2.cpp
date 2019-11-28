#include <iostream>
#include <malloc.h>
#include <string.h>
using namespace std;

struct pasien {
	char nama[30], penyakit[30];
	int umur;
};
typedef struct typequeue *typeptr;
struct typequeue {
	pasien data;
	typeptr next;
};
typeptr qDepan, qBelakang;

int getOption();
void buatQueue();
int queueKosong();
void enqueue(pasien newData);
void inputData();
void dequeue();
void cetakQueue();

int main() {
	char is_continue;
	enum option {CREATE = 1, READ, DELETE, FINISH};
	
	int pilihan = getOption();
	
	while(pilihan != FINISH) {
			switch(pilihan) {
				case CREATE:
					cout << "Pendaftaran Pasien" << endl;
					cout << "==================" << endl;
					inputData();
					break;
				case READ:
					cout << "Daftar Pasien" << endl;
					cout << "=============" << endl;
					cetakQueue();
					break;
				case DELETE:
					cout << "Panggilan Pasien" << endl;
					cout << "================" << endl;
					cetakQueue();
					dequeue();
					break;
				default:
					cout << "Pilihan tidak ditemukan" << endl;
					break;
					
			}
			
			label_continue:
			
			cout << "\nLanjutkan ke menu?(y/n) : "; cin >> is_continue;
			if((is_continue == 'y') | (is_continue =='Y')) {
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
	cout << "=====================" << endl;
	cout << "1. Pendaftaran Pasien" << endl;
	cout << "2. Daftar Pasien" << endl;
	cout << "3. Panggilan Pasien" << endl;
	cout << "4. Exit" << endl;
	cout << "=====================" << endl;
	cout << "Pilih [1-4]? : "; cin >> pilih;
	
	return pilih;
}

void buatQueue() {
	qDepan = (typequeue *)malloc(sizeof(typequeue));
	qDepan = NULL;
	qBelakang = qDepan;
}

int queueKosong() {
	if(qDepan == NULL) {
		return true;
	} else {
		return false;
	}
}

void enqueue(pasien newData) {
	typeptr NB;
	NB = (typequeue *)malloc(sizeof(typequeue));
	NB->data = newData;
	if (NB->data.umur > 60){
		if(queueKosong()) {
			qDepan = NB;
			qBelakang = qDepan;
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
}

void inputData() {
	char is_continue;
	pasien inputData;
	int i = 1;
	do {
		cout << "Nama : "; cin >> inputData.nama;
		cout << "Penyakit : "; cin >> inputData.penyakit;
		cout << "Umur : "; cin >> inputData.umur;
		enqueue(inputData);
		if(i == 150) {
			cout << "\nPendaftaran Penuh" << endl;
			break;
		}
		i++;
		cout << "\nInput Pendaftar Lagi?(y/n) : "; cin >> is_continue;
	} while((is_continue == 'y') | (is_continue == 'Y'));
}

/*void dequeue() {
	typeptr hapus, bantu;
	pasien inputData;
	bantu = (typequeue *)malloc(sizeof(typequeue));
	bantu = qDepan;
	hapus = qDepan;
	cout << "\nMasukan nama pendaftar tertua : "; cin >> inputData.nama;
	if(queueKosong()) {
		cout << "Pendaftaran masih kosong!" << endl;	
	} else if (strcmp(bantu->data.nama, inputData.nama) == 0){
		hapus = qDepan;
		qDepan = hapus->next;
		cout << "Untuk pendaftar atas nama " << bantu->data.nama << " sudah terpanggil" << endl;
		free(hapus);
	} else {
		while((bantu->next->next != NULL) && (strcmp(bantu->next->data.nama, inputData.nama) != 0))
			bantu = bantu->next;
		if((strcmp(bantu->next->data.nama, inputData.nama) == 0)) {
			hapus = bantu->next;
			if(hapus == qBelakang) {
				qBelakang = bantu;
				qBelakang->next = NULL;
			} else
				bantu->next = hapus->next;
			cout << "Untuk pendaftar atas nama " << bantu->next->data.nama << " sudah terpanggil" << endl;
			free(hapus);
		} else
			cout << "Pendaftar tidak ditemukan!" << endl;
	}
}*/

void dequeue() {
	typeptr hapus;
	if (queueKosong()) { 
		cout << "Queue masih kosong !";
	}
	else {
		hapus = qDepan;
		qDepan = hapus->next;
		cout << "Untuk pendaftar atas nama " << hapus->data.nama << " sudah terpanggil" << endl;
		free(hapus);
	}
}

void cetakQueue() {
	typeptr bantu;
	bantu = qDepan;
	int i = 1;
	do {
		cout << "Data ke-" << i << endl;
		cout << "Nama : " << bantu->data.nama << endl;
		cout << "Penyakit : " << bantu->data.penyakit << endl;
		cout << "Umur : " << bantu->data.umur << endl << endl;
		bantu = bantu->next;
		i++;
	} while(bantu != NULL);
}

