#include <iostream>
#include <string.h>

using namespace std;
typedef struct{
	int jumlah=0;
	char kata;
}hitung;
hitung abjad[27];
void isikata();
int main()
{
	char nama[30];
	char ulang;
	isikata();
  do
    {
     cout<<"Input : ";
  cin.getline(nama,
  sizeof(nama));
   for (int i = 0; i <
       strlen(nama); i++)
    {
     if (nama[i] > 96)
      {
  nama[i] = nama[i] - 32;
      }
 for(int j=1;j<= 27; j++)
   {
if(nama[i]==abjad[j].kata)
    {
abjad[j].jumlah += 1 ;
    }
  }
}
for (int i = 0; i <= 27; i++)
  {
    if (i<27)
    {
  if(abjad[i].jumlah > 0)
    {
cout<<"     "<<abjad[i].kata<<" = " <<abjad[i].jumlah<<endl;
   }
}
   else
   {
if(abjad[i].jumlah > 0)
      {
cout<< "              = "<<abjad[i].jumlah<<endl;
       }
    }
}
   cout<<endl<<endl;
cout<<"Input lagi ? y/t"; cin>>ulang;
  cin.ignore();
 } while (ulang=='y');
}

void isikata(){
   char kata1;
   int i = 1;
   for (kata1 = 'A' ; kata1 <= 'Z' ; kata1++)
  {
   abjad[i].kata = kata1;
   abjad[i].jumlah = 0;
   i++;
  }
    abjad[27].kata = ' ';
    abjad[27].jumlah = 0;
  }
