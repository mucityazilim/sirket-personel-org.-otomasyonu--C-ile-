#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// ÞÝRKET PERSONEL ORG. OTOMASYONU 
// MUCÝT YAZILIM- Sadýk ÞAHÝN

typedef struct Bolum {
	int bolumID; 
	char bolumAd[20]; 
	int personelSayisi; 
} bolum ;

typedef struct Kisisel {
	char dogumTarih[20]; 
	char dogumYeri[20]; 
	char cinsiyet; 
	char medeniHali; 
	
} kisisel ;

typedef struct Iletisim {
	char sehir[20]; 
	char ilce[20]; 
	char adres[30]; 
	char tel[20]; 
	char eposta[30]; 	
}iletisim ;

typedef struct Personel {
	char TC[20]; 
	int bolumID; 
	char adSoyad[30]; 
	char baslamaTarihi[20]; 
	float maas; 
	kisisel k1; 
	iletisim i1; 	
}personel ;


void bolumEkle() 
{
	system("cls") ; 
	printf("Bolum ekleme  \n\n") ; 
	bolum b1; 
	int numara=0; 

	FILE * numPtr = fopen("bolumNumaralar.dat", "a+b") ; 
	while( fread (&numara, sizeof(int), 1, numPtr )  != NULL  )
	{		
	}
	numara++;
 	fwrite  (&numara, sizeof(int), 1, numPtr ); 
	fclose(numPtr) ; 

	 	
	b1.bolumID= numara; 	
	printf("Bolum Adi : ") ; scanf(" %[^\n]s", b1.bolumAd ); 
	b1.personelSayisi= 0; 	
	
	FILE * ptr = fopen("bolumler.dat", "a+b") ; 
	fwrite  (&b1, sizeof(bolum ), 1, ptr ); 
	fclose(ptr); 
	printf("Bolum kaydi tamam \n") ; 
	
}
void bolumListele () 
{
	system("cls") ; 
	printf("Bolum listesi... \n\n") ; 
	bolum b1; 	
	
	printf("%-20s%-20s%-20s\n", "BOLUM-ID", "BOLUM-AD", "PERS.SAYISI" )  ; 
	FILE * ptr = fopen("bolumler.dat", "r+b") ;
	while( fread  (&b1, sizeof(bolum ), 1, ptr ) !=NULL  ) 
	{
		printf("%-20d%-20s%-20d\n", b1.bolumID, b1.bolumAd, b1.personelSayisi); 	
	}
	fclose(ptr); 	
}

void bolumDuzenle() 
{
	system("cls") ; 
	printf("Bolum duzenleme... \n\n") ; 
	bolum b1; 	
	int numara, sayac=0, sonuc=0; 
	bolumListele() ; 
	printf("Bolum No : ") ; scanf("%d", &numara ) ; 
	
	
	FILE * ptr = fopen("bolumler.dat", "r+b") ;
	
	while( fread  (&b1, sizeof(bolum ), 1, ptr ) !=NULL  ) 
	{
		if( numara== b1.bolumID  ) 
		{
			printf("%-20s%-20s%-20s\n", "BOLUM-ID", "BOLUM-AD", "PERS.SAYISI" )  ; 
			printf("%-20d%-20s%-20d\n", b1.bolumID, b1.bolumAd, b1.personelSayisi); 
			sonuc=1; 
			break; 			
		}				
		sayac++; 
	}
	if( sonuc==0  )
	printf("%d numarali bolum bulunamadi ! \n", numara ); 
	else
	{
		rewind(ptr); 
		printf("Bolumun Yeni Adi : ") ; scanf(" %[^\n]s", b1.bolumAd ) ; 		
		fseek( ptr, (sayac) * sizeof(bolum), 0 ) ; 
		fwrite  (&b1, sizeof(bolum ), 1, ptr ) ; 
		printf("Bolum Adi Degistirildi. \n") ; 		
	}	
	fclose(ptr); 		
	
}
void bolumSil () 
{
	system("cls") ; 
	printf("Bolum silme... \n\n") ; 
	bolum b1; 	
	bolumListele() ; 
	int numara, sonuc=0; 
	
	printf("Bolum No : "); scanf("%d", &numara  ) ; 
	
	
	printf("%-20s%-20s%-20s\n", "BOLUM-ID", "BOLUM-AD", "PERS.SAYISI" )  ; 
	FILE * ptr = fopen("bolumler.dat", "r+b") ;
	while( fread  (&b1, sizeof(bolum ), 1, ptr ) !=NULL  ) 
	{
		if(  numara== b1.bolumID   ) 
		{
			sonuc=1; 
			break; 
		}
	}	
	if( sonuc==0)
	{
		fclose(ptr); 
		printf("%d numarali bolum bulunamadi ! \n", numara ); 			
	}
	else if( b1.personelSayisi !=0 )
	{
		fclose(ptr); 
		printf("%d numarali bolumu silemezsiniz ! bu bolumda kayitli personel var ! \n", numara ); 			
		
	}
	

	else
	{
		rewind(ptr); 
		FILE * yptr = fopen("yedek.dat", "w+b") ;
		while( fread  (&b1, sizeof(bolum ), 1, ptr ) !=NULL  ) 
		{
			if(  numara != b1.bolumID ) 
			{
				fwrite  (&b1, sizeof(bolum ), 1, yptr ) ; 			 				 
			}
		} 
		fclose(ptr)	; 
		fclose(yptr); 
		
		remove("bolumler.dat"); 
		rename("yedek.dat", "bolumler.dat") ; 
		printf("Bolum kaydi silindi \n") ; 		
	}
	
}





int bolumMenu() 
{
	int secim; 
	printf("\n\tBolum Islemleri\n\n") ; 
	printf("\t1- Bolum Ekle  \n\n"); 
	printf("\t2- Bolum Duzenle \n\n"); 
	printf("\t3- Bolum Sil \n\n"); 
	printf("\t4- Bolum Listele \n\n"); 	
	printf("\t0- Cikis \n\n"); 
	printf("Seciminiz : "); scanf("%d", &secim) ; 
	system("cls") ; 
	return secim; 
	
}



void bolumIslemleri() 
{
	int secim= bolumMenu(); 
	
	while( secim != 0)
	{
		switch(secim )
		{
			case 1: bolumEkle(); break; 
			case 2: bolumDuzenle(); break; 
			case 3: bolumSil(); break; 
			case 4: bolumListele(); break; 			
			case 0: break; 
			default : printf("Hatali secim ! \n") ; 
		}
		secim= bolumMenu(); 		
		
	}
	
	printf("Cikis yaptiniz... ")  ; 
	
	
	
}

void bolumGuncelle(int numara, int sayi )
{
	FILE *ptr = fopen("bolumler.dat", "r+b" ) ; 
	bolum b1; 
	int sayac=0; 
	while( fread ( &b1, sizeof(bolum), 1, ptr ) != NULL  )
	{
		if( numara == b1.bolumID ) 
		{
			break; 
		}
		sayac++; 
	}
	rewind(ptr); 
	fseek ( ptr, (sayac) * sizeof(bolum), 0 ) ; 
	b1.personelSayisi += sayi; 
	fwrite ( &b1, sizeof(bolum), 1, ptr ) ; 
	fclose(ptr); 
	printf("\nbolum guncellendi \n") ; 
	
}


void personelEkle() 
{
	system("cls") ; 
	printf("Personel ekleme  \n\n") ; 
	personel p1; 
	
	
	printf("TC             : "); scanf(" %[^\n]s", p1.TC ) ; 
	printf("Ad Soyad       : "); scanf(" %[^\n]s", p1.adSoyad ) ; 	
	bolumListele() ; 
	printf("Bolum No       : "); scanf(" %d", &p1.bolumID ) ; 
	printf("Baslama Tarihi : "); scanf(" %[^\n]s", p1.baslamaTarihi ) ; 
	printf("Maas  (TL)     : "); scanf(" %f", &p1.maas ) ; 
	
	
	system("cls"); 
	printf("Kisisel bilgileri... : \n\n"); 
	
	printf("Dogum Tarihi   : "); scanf(" %[^\n]s", p1.k1.dogumTarih ) ; 
	printf("Dogum Yeri     : "); scanf(" %[^\n]s", p1.k1.dogumYeri ) ; 
	printf("Cinsiyet       : "); scanf(" %[^\n]s", &p1.k1.cinsiyet ) ; 
	printf("Medeni Hali    : "); scanf(" %[^\n]s", &p1.k1.medeniHali ) ; 
	
	
	system("cls"); 
	printf("Iletisim bilgileri... : \n\n"); 
	
	printf("Sehir          : "); scanf(" %[^\n]s", p1.i1.sehir ) ; 
	printf("Ilce           : "); scanf(" %[^\n]s", p1.i1.ilce ) ; 
	printf("Adres          : "); scanf(" %[^\n]s", p1.i1.adres ) ; 
	printf("Telefon        : "); scanf(" %[^\n]s", p1.i1.tel ) ; 
	printf("E-Posta        : "); scanf(" %[^\n]s", p1.i1.eposta ) ; 
	
	FILE *ptr= fopen("personel.dat", "a+b") ; 
	fwrite( &p1, sizeof(personel), 1, ptr  ) ; 
	fclose(ptr); 
	printf("Personel kaydi tamam \n") ; 
	bolumGuncelle(p1.bolumID, 1); 
	
}

void personelAra() 
{
	system("cls") ; 
	printf("Personel arama \n\n") ; 
	personel p1; 
	int sonuc=0; 	
	char tc[20]; 
	printf("TC             : "); scanf(" %[^\n]s", tc ) ; 
	
	
	
	FILE *ptr= fopen("personel.dat", "r+b") ; 
	while( fread ( &p1, sizeof(personel), 1, ptr  )  != NULL  )
	{
		if( strcmp( tc, p1.TC ) == 0  )
		{			
			sonuc=1; 
			break; 			
		}
	}		
	fclose(ptr); 
	if( sonuc==0 )
	printf("%s TC numarali personel kaydi bulunamadi ! \n", tc ); 
	else
	{
		system("cls"); 
		printf("%-20s%-20s%-30s%-20s%-20s\n", "TC", "BOLUM-ID", "AD-SOYAD", "BAS-TARIH", "MAAS (TL)" ) ; 
		printf("%-20s%-20d%-30s%-20s%.2f\n", p1.TC, p1.bolumID, p1.adSoyad, p1.baslamaTarihi, p1.maas ); 
		
		printf("\nKISISEL BILGILER : \n"); 
		printf("Dogum Tarih : %s \n", p1.k1.dogumTarih ) ; 
		printf("Dogum Yeri  : %s\n", p1.k1.dogumYeri ) ; 
		printf("Cinsiyet    : %c\n", p1.k1.cinsiyet ) ; 
		printf("Medeni Hali : %c\n", p1.k1.medeniHali ) ; 
		
		printf("\nILETISIM BILGILER : \n"); 
		printf("Sehir       : %s\n", p1.i1.sehir ) ; 
		printf("Ilce        : %s\n", p1.i1.ilce ) ; 
		printf("Adres       : %s\n", p1.i1.adres ) ; 
		printf("Telefon     : %s\n", p1.i1.tel ) ; 
		printf("E-Posta     : %s\n", p1.i1.eposta ) ; 
		
	}	
	
}

void personelSil () 
{
	system("cls") ; 
	printf("Personel silme \n\n") ; 
	personel p1; 
	int sonuc=0; 	
	char tc[20]; 
	printf("TC             : "); scanf(" %[^\n]s", tc ) ; 
	
	
	FILE *ptr= fopen("personel.dat", "r+b") ; 
	while( fread ( &p1, sizeof(personel), 1, ptr  )  != NULL  )
	{
		if( strcmp( tc, p1.TC ) == 0  )
		{			
			sonuc=1; 
			break; 			
		}
	}		
	
	if( sonuc==0 )
	{
		fclose(ptr); 
		printf("%s TC numarali personel kaydi bulunamadi ! \n", tc ); 
			
	}

	else
	{
		rewind(ptr) ; 		
		
		system("cls"); 
		printf("%-20s%-20s%-30s%-20s%-20s\n", "TC", "BOLUM-ID", "AD-SOYAD", "BAS-TARIH", "MAAS (TL)" ) ; 
		printf("%-20s%-20d%-30s%-20s%.2f\n", p1.TC, p1.bolumID, p1.adSoyad, p1.baslamaTarihi, p1.maas ); 
		
		char tercih; 
		printf("%s personelini silmek istediginize emin misiniz ? [e] : ", p1.adSoyad ); scanf(" %c", &tercih ); 
		
		
		FILE *yPtr= fopen("yedek.dat", "w+b") ; 
		
		if( tercih=='e' || tercih =='E') 
		{
			while( fread ( &p1, sizeof(personel), 1, ptr  )  != NULL  )
			{
				if( strcmp( tc, p1.TC ) != 0  )
				{			
					 fwrite( &p1, sizeof(personel), 1, yPtr ) ; 					 	
				}
			}
			
			fclose(ptr); 
			fclose(yPtr) ; 
			
			remove("personel.dat") ; 
			rename("yedek.dat", "personel.dat") ; 
			printf("Silme islemi tamam \n")	 ; 
			bolumGuncelle(p1.bolumID, -1) ; 
		}
		else
		printf("Silme islemi iptal edildi \n") ; 	
		
	}	
	
	fclose(ptr); 
	
}

void personelListele() 
{
	system("cls") ; 
	printf("Personel listeleme \n\n") ; 
	personel p1; 
	int numara ; 	
	bolumListele() ; 	
	
	printf("Bolum No  : "); scanf(" %d", &numara  ) ; 
	
	
	FILE *ptr= fopen("personel.dat", "r+b") ; 
	
	printf("%-20s%-20s%-30s%-20s%-20s\n", "TC", "BOLUM-ID", "AD-SOYAD", "BAS-TARIH", "MAAS (TL)" ) ; 	
	while( fread ( &p1, sizeof(personel), 1, ptr  )  != NULL  )
	{
		if(  numara == p1.bolumID   )
		{			
			 
		 printf("%-20s%-20d%-30s%-20s%.2f\n", p1.TC, p1.bolumID, p1.adSoyad, p1.baslamaTarihi, p1.maas ); 
			 	
		}
		
	}		
	fclose(ptr);  
	 	
}

void personelMaasGuncelle() 
{
	 system("cls") ; 
	printf("Personel maas guncelle \n\n") ; 
	personel p1; 
	int sonuc=0, sayac=0; 
	char tc[20]; 
	
	printf("TC    : "); scanf(" %[^\n]s", tc  ) ; 
	
	
	FILE *ptr= fopen("personel.dat", "r+b") ; 
	
	while( fread ( &p1, sizeof(personel), 1, ptr  )  != NULL  )
	{
		if(  strcmp( tc, p1.TC ) ==0  )
		{			
		 sonuc= 1; 
		 break; 			 	
		}
		sayac++; 
	}		
	
	if( sonuc==0)
	{
		printf("%s numarali personel kaydi bulunamadi \n", tc ) ; 		
	}
	else
	{ 
		rewind(ptr) ; 
		printf("%-20s%-20s%-30s%-20s%-20s\n", "TC", "BOLUM-ID", "AD-SOYAD", "BAS-TARIH", "MAAS (TL)" ) ; 							 
		 printf("%-20s%-20d%-30s%-20s%.2f\n", p1.TC, p1.bolumID, p1.adSoyad, p1.baslamaTarihi, p1.maas ); 
		 
		 printf("Yeni Maas  (TL)  : ") ; scanf("%f", &p1.maas ); 
		 
		 fseek( ptr, (sayac) *sizeof(personel), 0 ) ; 
		 fwrite ( &p1, sizeof(personel), 1, ptr  )  ; 
		 printf("Maas guncellendi \n") ; 	 
		
	}	
	fclose(ptr);  	
	
}

void personelBolumDegistir()  
{
	system("cls") ; 
	printf("Personel bolum degistirme \n\n") ; 
	personel p1; 
	int sonuc=0, sayac=0; 
	char tc[20]; 
	
	printf("TC    : "); scanf(" %[^\n]s", tc  ) ; 
	
	
	FILE *ptr= fopen("personel.dat", "r+b") ; 
	
	while( fread ( &p1, sizeof(personel), 1, ptr  )  != NULL  )
	{
		if(  strcmp( tc, p1.TC ) ==0  )
		{			
		 sonuc= 1; 
		 break; 			 	
		}
		sayac++; 
	}		
	
	if( sonuc==0)
	{
		printf("%s numarali personel kaydi bulunamadi \n", tc ) ; 		
	}
	else
	{ 
		rewind(ptr) ; 
		
		printf("%-20s%-20s%-30s%-20s%-20s\n", "TC", "BOLUM-ID", "AD-SOYAD", "BAS-TARIH", "MAAS (TL)" ) ; 							 
		 printf("%-20s%-20d%-30s%-20s%.2f\n", p1.TC, p1.bolumID, p1.adSoyad, p1.baslamaTarihi, p1.maas ); 
		 
		 int eskiBolumNo= p1.bolumID; 		 
		 bolumListele() ; 	
		 	 
		 printf("Yeni Bolum  No : ") ; scanf("%d", &p1.bolumID );  		 		 
		 fseek( ptr, (sayac) *sizeof(personel), 0 ) ; 
		 fwrite ( &p1, sizeof(personel), 1, ptr  )  ; 
		 printf("Bolum degistirildi  \n") ; 	 	
		 
		 bolumGuncelle( eskiBolumNo , -1)    ; 
		 bolumGuncelle( p1.bolumID, 1 )    ; 
		 
		 
		 
		 	
	}	
	fclose(ptr);  	
	
	
	
	
	
}



int personelMenu() 
{
	int secim; 
	printf("\n\tPersonel Islemleri\n\n") ; 
	printf("\t1- Personel Ekle  \n\n"); 
	printf("\t2- Personel Ara  \n\n"); 
	printf("\t3- Personel Sil  \n\n"); 
	printf("\t4- Personel Listele  \n\n"); 
	printf("\t5- Personel Maas Guncelle  \n\n"); 
	printf("\t6- Personel Bolumunu Degistir  \n\n"); 
	
	
	printf("\t0- Cikis \n\n"); 
	printf("Seciminiz : "); scanf("%d", &secim) ; 
	system("cls") ; 
	return secim; 
	
}





void personelIslemleri() 
{
	
	int secim= personelMenu(); 
	
	while( secim != 0)
	{
		switch(secim )
		{
			case 1: personelEkle(); break; 
			case 2: personelAra(); break; 
			case 3: personelSil(); break; 
			case 4: personelListele(); break; 
			case 5: personelMaasGuncelle(); break; 
			case 6: personelBolumDegistir(); break; 
			case 0: break; 
			default : printf("Hatali secim ! \n") ; 
		}
		secim= personelMenu(); 		
		
	}
	
	printf("Cikis yaptiniz... ")  ; 
	
	
	
	
	
}

int menu() 
{
	int secim; 
	printf("\n\tSIRKET PERSONEL ORGANIZASYON OTOMASYONU \n\n") ; 
	printf("\t1- BOLUM ISLEMLERI \n\n"); 
	printf("\t2- PERSONEL ISLEMLERI \n\n"); 
	printf("\t0- PROGRAMI KAPAT \n\n"); 
	printf("Seciminiz : "); scanf("%d", &secim) ; 
	system("cls") ; 
	return secim; 
	
}



int main() 
{
	int secim= menu(); 
	
	while( secim != 0)
	{
		switch(secim )
		{
			case 1: bolumIslemleri(); break; 
			case 2: personelIslemleri(); break; 
			case 0: break; 
			default : printf("Hatali secim ! \n") ; 
		}
		secim= menu(); 		
		
	}
	
	printf("Programi kapattiniz... ")  ; 
	
	
	return 0; 
}
