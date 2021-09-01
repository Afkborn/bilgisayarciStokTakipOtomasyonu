// Furkan Cagri Erkoca
// 2012721007
// Bilgisayar stok takip otomasyon
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <dirent.h>

#define FILENAME "stock.txt"
#define FATURAKLASOR "fatura\\"
#define MAX_COUNT_URUN 256
#define MAX_COUNT_FATURA 256
#define hTag "########################################"
#define tire "------------------------------"
#define yazdirMenu "|ID\tFIYAT\tSTOK DURUMU\tBARKOD\tKDV%\tAGIRLIK\tISIM"
#define yazdirUrun "|"<<urun[i].id << "\t" << urun[i].price << "TL\t" << urun[i].stockCount << "\t\t" << urun[i].barcode << "\t"<< urun[i].rateVAT <<"\t" << urun[i].weight << "g\t" <<urun[i].name
#define secenekMenu "1)Stok Giris\t\t2)Satis\n3)Urun listele\t\t4)Urun sil\n5)Fiyat guncelle\t6)Stok guncelle\n7)Barkod guncelle\t8)KDV guncelle\n9)Agirlik guncelle\t10)Butun urunleri sil\n11)Faturalari gor\t12)Cikis\n13)Hakkinda\n>>> "
#define selectErrorMessage "Yanlis giris, tekrar kontrol edin!"
#define noProductErrorMessage "Once urun girmeyi dene!"

DIR *dir;
struct dirent *ent;

using namespace std;
struct urunler{
    int id;
    string name;
    int stockCount;
    int price;
    int barcode;
    int rateVAT;
    int weight;
};


void txtFileUpdate(struct urunler urun[], int urunSayi){
    remove(FILENAME);
    ofstream dosyaYaz(FILENAME,std::ios_base::app);
    for(int i=0;i<urunSayi;i++){
        if (urun[i].id ==0 && urun[i].name == "null" && urun[i].stockCount ==0 && urun[i].price ==0){
            continue;
        }
        else{
            dosyaYaz << urun[i].id << " " << urun[i].name << " " << urun[i].stockCount << " " << urun[i].price << " "<< urun[i].barcode << " " << urun[i].rateVAT<< endl;
        }

    }
    dosyaYaz.close();
}

void hepsiniYazdir(struct urunler urun[], int urunSayi){
    int bulunanSayi=0;
    cout << yazdirMenu << endl;
    for (int i=0;i<urunSayi;i++){
        if (urun[i].id ==0 && urun[i].name == "null" && urun[i].stockCount ==0 && urun[i].price ==0)
            {
                continue;
            }
        else{
            bulunanSayi++;
            cout << yazdirUrun<<endl;
            }
    }
    if(bulunanSayi==0){
        cout << "Veri bulunamadi! Veri girmeyi deneyin."<<endl;
    }
    cout << endl << endl;
}

void idIleYazdir(struct urunler urun[], int urunSayi, int ID){
    cout << yazdirMenu << endl;
    int sayac2=0;
    for (int i=0;i<urunSayi;i++){
            if (urun[i].id == ID){
                cout << yazdirUrun<<endl;
                sayac2++;
            }
    }
    if (sayac2==0){
        cout << "Bulunamadi"<<endl;
    }
    cout << endl << endl;
}

bool idControl(struct urunler urun[], int urunSayi, int ID){
    bool control = false;
    for (int i=0;i<urunSayi;i++){
            if (urun[i].id == ID){
                control =true;
            }
    }
    return control;
}

void isimIleYazdir(struct urunler urun[],int urunSayi, string name){
    int uzunluk = name.length();
    char kucukHal[uzunluk+1];
    char buyukHal[uzunluk+1];
    string ilkHarf = name;
    ilkHarf[0] = toupper(name[0]);
    for (int i=0; i<uzunluk; i++){
        kucukHal[i] = tolower(name[i]);
        buyukHal[i] = toupper(name[i]);
    }

    kucukHal[uzunluk] = '\0';
    buyukHal[uzunluk] = '\0';

    cout << yazdirMenu << endl;
    int sayac2=0;
    for (int i=0;i<urunSayi;i++){
            if (urun[i].name == name){
                cout << yazdirUrun<<endl;
                sayac2++;
            }
            else if (urun[i].name == kucukHal){
                cout << yazdirUrun<<endl;
                sayac2++;
            }
            else if (urun[i].name == buyukHal){
                cout << yazdirUrun<<endl;
                sayac2++;
            }
            else if (urun[i].name == ilkHarf){
                cout << yazdirUrun<<endl;
                sayac2++;
            }
    }
    if (sayac2==0){
        cout << "Bulunamadi"<<endl;
    }
    cout << endl << endl;
}

int findIdWithName(struct urunler urun[], int urunSayi, string name){
    int uzunluk = name.length();
    char kucukHal[uzunluk+1];
    char buyukHal[uzunluk+1];
    string ilkHarf = name;
    ilkHarf[0] = toupper(name[0]);
    for (int i=0; i<uzunluk; i++){
        kucukHal[i] = tolower(name[i]);
        buyukHal[i] = toupper(name[i]);
    }

    kucukHal[uzunluk] = '\0';
    buyukHal[uzunluk] = '\0';





    for (int i=0;i<urunSayi;i++){
            if (urun[i].name == kucukHal){
                    return urun[i].id;
            }
            else if (urun[i].name == buyukHal){
                    return urun[i].id;
            }
            else if (urun[i].name == name){
                    return urun[i].id;
            }
            else if (urun[i].name == ilkHarf){
                    return urun[i].id;
            }

    }

    return 0;
}

void getTimeForFileName(char *buffer){
        time_t rawtime;
        struct tm * timeinfo;
        time (&rawtime);
        timeinfo = localtime (&rawtime);
        strftime (buffer,80,"%Y%m%d%H%M%S",timeinfo);
}

void getTime(char *buffer){
        time_t rawtime;
        struct tm * timeinfo;
        time (&rawtime);
        timeinfo = localtime (&rawtime);
        strftime (buffer,80,"%Y-%m-%d %H:%M:%S",timeinfo);
}

void kdvIleYazdir(struct urunler urun[],int urunSayi, int kdvOran){
    cout << yazdirMenu << endl;
    int sayac2=0;
    for (int i=0;i<urunSayi;i++){
            if (urun[i].rateVAT == kdvOran){
                cout << yazdirUrun<<endl;
                sayac2++;
            }
    }
    if (sayac2==0){
        cout << "Bulunamadi"<<endl;
    }
    cout << endl << endl;
}

void barkodIleYazdir(struct urunler urun[],int urunSayi, int barkod){
    cout << yazdirMenu << endl;
    int sayac2=0;
    for (int i=0;i<urunSayi;i++){
            if (urun[i].barcode == barkod){
                cout << yazdirUrun<<endl;
                sayac2++;
            }
    }
    if (sayac2==0){
        cout << "Bulunamadi"<<endl;
    }
    cout << endl << endl;
}

int findIdWithBarcode(struct urunler urun[], int urunSayi, int barkod){
    for (int i=0;i<urunSayi;i++){
            if (urun[i].barcode == barkod){
                    return urun[i].id;
            }
    }
    return 0;
}

int faturalariYazdir(string *faturaArray){
    int countFatura = 1;
    int countFaturaArray =0;
    if ((dir = opendir(FATURAKLASOR)) != NULL) {
            while ((ent = readdir(dir)) != NULL) {
                string isim = ent->d_name;
                if (isim == "." || isim==".."){
                    continue;
                }
                else{
                    cout << countFatura << ")" << isim << endl;
                    faturaArray[countFaturaArray] = isim;
                    countFatura++;
                    countFaturaArray++;
                }
            }
            closedir(dir);
    }
    return countFaturaArray;
}

bool sayiMi(string sayi){
    string rakamlar[] = {"0","1","2","3","4","5","6","7","8","9"};
    int uzunluk = sayi.length();
    int rakamSayisi =0;

    for (int i=0;i<uzunluk;i++)
        for(int j=0;j<10;j++)
            if (sayi[i] == rakamlar[j][0])
                rakamSayisi++;
    if (rakamSayisi == uzunluk){
        return true;
    }
    return false;
}


int main()
{


    mkdir(FATURAKLASOR);
    system("color b");

    urunler urun[MAX_COUNT_URUN];

    ofstream dosyaYaz(FILENAME,std::ios_base::app);
    dosyaYaz.close();

    string faturaIsim[MAX_COUNT_FATURA];
    ifstream dosyaOku(FILENAME);
    int sayac =0;
    while (dosyaOku){
        dosyaOku>>urun[sayac].id>>urun[sayac].name>>urun[sayac].stockCount>>urun[sayac].price>>urun[sayac].barcode>>urun[sayac].rateVAT>>urun[sayac].weight;
        sayac++;
    }
    int valueCount = sayac-1;
    dosyaOku.close();

    bool urunSayiKontrol = false;
    if (valueCount >0){
        urunSayiKontrol = true;
    }
    int secim;
    bool control = true;
    cout << hTag << endl << "#  BILGISAYARCI STOK TAKIP OTOMASYONU  #" << endl << "#          FURKAN CAGRI ERKOCA         #" << endl << hTag << endl;
    while(control){
        cout << secenekMenu;
        cin >> secim;
        switch(secim){
            case 1://urungiris
                {
                        cout << "Urun Giris"<<endl;
                        int gID;
                        gID = valueCount;
                        urun[gID].id = gID+1;
                        cout <<"ID: "<< sayac << " icin isim girin: ";
                        cin >> urun[gID].name;
                        cout <<"ID: "<< sayac << " icin stok sayi girin: ";
                        cin >> urun[gID].stockCount;
                        cout <<"ID: "<< sayac << " icin fiyat girin: ";
                        cin >> urun[gID].price;
                        cout <<"ID: "<< sayac << " icin barkod numarasi girin: ";
                        cin >> urun[gID].barcode;
                        cout <<"ID: "<< sayac << " icin vergi orani girin: ";
                        cin >> urun[gID].rateVAT;
                        cout <<"ID: "<< sayac << " icin agirlik girin: ";
                        cin >> urun[gID].weight;
                        ofstream dosyaYaz(FILENAME,std::ios_base::app);
                        dosyaYaz << sayac << " " << urun[gID].name << " " << urun[gID].stockCount << " " << urun[gID].price << " "<< urun[gID].barcode<< " "<< urun[gID].rateVAT<< urun[gID].weight<<endl;
                        dosyaYaz.close();
                        valueCount++;
                        sayac++;
                        cout << "Stok basariyla kayit edildi." << endl;
                        break;
                }
            case 2://satis
                {
                    cout << "Satis"<<endl;
                    if (urunSayiKontrol){
                        int secim2;
                        cout << "1)Tek bir urun satin al\n2)Birden fazla urun satin al\n>>> ";
                        cin >> secim2;
                        switch(secim2){
                        case 1:
                        {
                            hepsiniYazdir(urun,valueCount);
                            int gID;
                            cout << "ID: ";
                            cin >> gID;
                            bool control = idControl(urun,valueCount,gID);
                            if (control){
                                gID--;
                                cout << "Urun Adi: " << urun[gID].name << endl << "Urun Stok: " << urun[gID].stockCount << endl << "Urun Fiyat: " << urun[gID].price << endl << endl;
                                int satisSayi;
                                cout << "Kac adet satmak istersiniz: ";
                                cin >> satisSayi;
                                if (satisSayi <= urun[gID].stockCount && satisSayi >0){
                                    int newStock = urun[gID].stockCount - satisSayi;
                                    int fiyat = satisSayi * urun[gID].price;
                                    cout << "KDV haric fiyat: " <<  fiyat << "TL."<<endl;
                                    char control4;
                                    cout << "KDV eklensin mi (e/E): ";
                                    cin >> control4;
                                    int kdvOran = urun[gID].rateVAT;
                                    if (control4 == 'E' ||control4 == 'e'){
                                        cout << "%" << kdvOran<<"kdv dahil fiyat: " << fiyat + (fiyat/100*kdvOran) << "TL." <<endl;
                                    }
                                    cout << endl << endl;
                                    urun[gID].stockCount = newStock;
                                    txtFileUpdate(urun,valueCount);

                                    char yesNo;
                                    cout << "Fatura olusturmak ister misiniz? (e/E)";
                                    cin >> yesNo;
                                    if (yesNo == 'E' || yesNo == 'e'){
                                        string isim;
                                        string soyisim;
                                        cout << "Isim: ";
                                        cin >> isim;
                                        cout << "Soyisim: ";
                                        cin >> soyisim;
                                        string telNo;
                                        cout << "Telefon numarasi(5xxxxxxxxx): ";
                                        cin >> telNo;
                                        bool telControl = sayiMi(telNo);
                                        bool telControl3=false;
                                        if(telNo.length()==10)
                                            telControl3=true;
                                        if (telControl && telControl3){
                                            string ePosta;
                                            cout << "E-posta: ";
                                            cin >> ePosta;
                                            char buffer[80];
                                            getTimeForFileName(buffer);
                                            string locBuf = FATURAKLASOR;
                                            locBuf += buffer;
                                            locBuf += ".txt";
                                            string buffer3 = buffer;
                                            buffer3+= ".txt";
                                            char buffer2[80];
                                            getTime(buffer2);
                                            ofstream dosyaYaz2(locBuf,std::ios_base::app);
                                            dosyaYaz2 << "Tarih: "<< buffer2 << endl;
                                            dosyaYaz2 << "Ad Soyad: "<< isim << " "<<soyisim << endl;
                                            dosyaYaz2 << "E-posta: "<< ePosta << endl;
                                            dosyaYaz2 << "Telefon Numarasi: "<< telNo << endl;
                                            dosyaYaz2 << tire << endl;
                                            dosyaYaz2 << "Urun adi: " << urun[gID].name << endl;
                                            dosyaYaz2 << "Urun Fiyati: " << urun[gID].price << endl;
                                            dosyaYaz2 << "Satis Adedi: " << satisSayi << endl;
                                            dosyaYaz2 << "KDV haric fiyat: " << fiyat << endl;
                                            dosyaYaz2 << "KDV orani: " << kdvOran << endl;
                                            dosyaYaz2 << "KDV dahil fiyat: " << fiyat  + (fiyat/100*kdvOran)<< endl;
                                            dosyaYaz2 << "Agirlik: " << urun[gID].weight << "g"<<endl;
                                            dosyaYaz2 << tire << endl;
                                            dosyaYaz2 << "Toplam KDV haric fiyati: " << fiyat << "TL."<<endl;
                                            dosyaYaz2 << "Toplam KDV dahil fiyati: " << fiyat  + (fiyat/100*kdvOran) << "TL."<<endl;
                                            cout <<"Toplam KDV haric fiyati: " << fiyat << "TL."<<endl;
                                            cout <<"Toplam KDV dahil fiyati: " << fiyat  + (fiyat/100*kdvOran) << "TL."<<endl;
                                            dosyaYaz2.close();
                                            cout << "Fatura basari ile olusturuldu. Dosya adi: " << buffer3 << endl<<endl;
                                        }
                                        else{
                                            cout << "Yanlis telefon numarasi!"<<endl;
                                        }

                                    }
                                }
                                else{
                                    cout << "Satis miktarini tekrar girin." << endl;
                                }
                            }
                            else{
                                cout << "Boyle bir ID bulunamadi." << endl;
                            }
                            break;
                        }
                        case 2:
                        {
                            hepsiniYazdir(urun,valueCount);
                            bool basketControl=true;
                            vector <int> basketID;
                            vector <int> basketCount;
                            while(basketControl){
                                int gID;
                                cout << "Almak istenilen urunun ID bilgisini yaziniz: ";
                                cin >> gID;
                                bool control = idControl(urun,valueCount,gID);

                                if (control){
                                    gID--;
                                    int gStock;
                                    cout << "Urun adi: " << urun[gID].name << endl;
                                    cout << "Kac adet almak istersiniz (Stok sayisi: " << urun[gID].stockCount << ") : ";
                                    cin >> gStock;
                                    if (gStock > 0 && urun[gID].stockCount >= gStock){
                                        basketID.push_back(gID);
                                        basketCount.push_back(gStock);
                                        cout << "Urun basarili bir sekilde sepete eklendi." << endl;
                                    }
                                    else{
                                        cout << "Urunden bu kadar yok." << endl;
                                    }
                                }
                                else{
                                    cout << "Boyle bir ID bulunamadi." << endl;
                                }


                                char control3;
                                cout << "Sepete yeni urun eklemek ister misiniz? (e/E): ";
                                cin >> control3;
                                if (control3 == 'E' || control3 == 'e'){
                                    basketControl = true;
                                }
                                else{
                                    bool kdvControl = false;
                                    char control4;
                                    cout << "KDV eklensin mi (e/E): ";
                                    cin >> control4;
                                    if (control4 == 'E' ||control4 == 'e'){
                                        kdvControl = true;
                                    }

                                    cout << "Sepette " << basketID.size() << " urun var." <<endl;
                                    int toplamFiyat =0;
                                    int kdvToplamFiyat =0;
                                    for (int i=0;i<basketID.size();i++){
                                        int urunID = basketID[i];
                                        int urunSayi = basketCount[i];
                                        int urunTaneFiyat = urun[urunID].price;
                                        int urunCokFiyat = urunSayi * urunTaneFiyat;
                                        int kdvOran = urun[urunID].rateVAT;
                                        int kdvDahilFiyat = urunCokFiyat + urunCokFiyat/100*kdvOran;
                                        cout << i+1 <<". urun adi: " << urun[urunID].name << ", Tane fiyati: "<< urunTaneFiyat << "TL, " << urunSayi << " tanesinin fiyati = " << urunCokFiyat << "TL, KDV Oran: "<< kdvOran << ", KDV'li fiyat: "<< kdvDahilFiyat << "."<<endl;
                                        if (kdvControl){
                                            kdvToplamFiyat +=  kdvDahilFiyat;
                                        }
                                        toplamFiyat+= urunCokFiyat;
                                        urun[urunID].stockCount -= urunSayi;
                                        txtFileUpdate(urun,valueCount);
                                    }
                                    cout << basketID.size() << " urunun KDV haric fiyati: " << toplamFiyat << "TL."<<endl;
                                    cout << basketID.size() << " urunun KDV dahil fiyati: " << kdvToplamFiyat << "TL."<<endl;
                                    cout << endl << endl;


                                    // FATURA OLUSTURUP OLUSTURMAMAYI SOR

                                    char yesNo;
                                    cout << "Fatura olusturmak ister misiniz? (e/E): ";
                                    cin >> yesNo;
                                    if (yesNo == 'E' || yesNo == 'e'){

                                        string telNo;
                                        cout << "Telefon numarasi(5xxxxxxxxx): ";
                                        cin >> telNo;
                                        bool telControl = sayiMi(telNo);
                                        bool telControl3=false;
                                        if(telNo.length()==10)
                                            telControl3=true;
                                        if (telControl && telControl3){
                                            string isim;
                                            string soyisim;
                                            cout << "Isim: ";
                                            cin >> isim;
                                            cout << "Soyisim: ";
                                            cin >> soyisim;
                                            string ePosta;
                                            cout << "E-posta: ";
                                            cin >> ePosta;
                                            char buffer[80];
                                            getTimeForFileName(buffer);

                                            string locBuf = FATURAKLASOR;
                                            locBuf += buffer;
                                            locBuf += ".txt";
                                            string buffer3 = buffer;
                                            buffer3+= ".txt";
                                            char buffer2[80];
                                            getTime(buffer2);
                                            ofstream dosyaYaz2(locBuf,std::ios_base::app);
                                            dosyaYaz2 << "Tarih: "<< buffer2 << endl;
                                            dosyaYaz2 << "Ad Soyad: "<< isim << " "<<soyisim << endl;
                                            dosyaYaz2 << "E-posta: "<< ePosta << endl;
                                            dosyaYaz2 << "Telefon Numarasi: "<< telNo << endl;
                                            int toplamFiyat2=0;
                                            int kdvToplamFiyat2=0;
                                            for (int i=0;i<basketID.size();i++){
                                                dosyaYaz2 << tire << endl;
                                                int urunID = basketID[i];
                                                int urunSayi = basketCount[i];
                                                int urunTaneFiyat = urun[urunID].price;
                                                int urunCokFiyat = urunSayi * urunTaneFiyat;
                                                int kdvOran = urun[urunID].rateVAT;
                                                int kdvDahilFiyat = urunCokFiyat + urunCokFiyat/100*kdvOran;
                                                int kdv = urunCokFiyat/100*kdvOran;
                                                dosyaYaz2 << "Urun adi: " << urun[urunID].name << endl;
                                                dosyaYaz2 << "Satis Adedi: " << urunSayi << endl;
                                                dosyaYaz2 << "Urun icin tane fiyat: " << urunTaneFiyat <<"TL"<< endl;
                                                dosyaYaz2 << "Urun icin toplam fiyat: " << urunCokFiyat <<"TL"<< endl;
                                                dosyaYaz2 << "Urun icin KDV orani: %" << kdvOran <<endl;
                                                dosyaYaz2 << "KDV bedeli: " << kdv <<"TL" <<endl;
                                                dosyaYaz2 << "Agirlik: " << urun[urunID].weight << "g" << endl;
                                                kdvToplamFiyat2+= kdvDahilFiyat;
                                                toplamFiyat2+= urunCokFiyat;
                                            }
                                            dosyaYaz2 << tire << endl;
                                            dosyaYaz2 << "KDV haric fiyat: " << toplamFiyat2 << "TL"<< endl;
                                            dosyaYaz2 << "KDV dahil fiyat: " << kdvToplamFiyat2  << "TL"<< endl;
                                            dosyaYaz2.close();
                                            cout << "Fatura basari ile olusturuldu. Dosya adi: " << buffer3 << endl<<endl;
                                        }
                                        else{
                                            cout << "Yanlis telefon numarasi!"<<endl;
                                        }
                                    }

                                    basketControl=false;
                                }
                            }
                            break;
                        }
                        default:
                            cout << selectErrorMessage <<endl;
                        }
                    }
                    else{
                        cout << noProductErrorMessage << endl;
                    }
                    break;
                }
            case 3://urunListele
                {
                    cout << "Urun Listele"<<endl;
                    if (urunSayiKontrol){
                        int secim4;
                        cout << "1)ID ile listele\n2)Isim ile listele\n3)Hepsini listele\n4)KDV orani ile listele\n5)Barkod numarasi ile listele\n>>> ";
                        cin >> secim4;
                        switch(secim4){
                        case 1:
                            {
                                int gID;
                                cout << "ID: ";
                                cin >> gID;
                                idIleYazdir(urun,valueCount,gID);
                                break;
                            }
                        case 3:
                            {
                                hepsiniYazdir(urun,valueCount);
                                break;
                            }
                        case 2:
                            {
                                string gName;
                                cout << "Isim: ";
                                cin >> gName;
                                isimIleYazdir(urun,valueCount,gName);
                                break;
                            }
                        case 4:
                            {
                                int kdvOran;
                                cout << "KDV Oran: ";
                                cin >> kdvOran;
                                kdvIleYazdir(urun,valueCount,kdvOran);
                                break;
                            }
                        case 5:
                            {
                                int barkod;
                                cout << "Barkod: ";
                                cin >> barkod;
                                barkodIleYazdir(urun,valueCount,barkod);
                                break;
                            }
                        default:
                            cout << selectErrorMessage <<endl;
                        }
                    }
                    else{
                        cout << noProductErrorMessage << endl;
                    }
                    break;
                }
            case 12://cikis
                {
                    control=false;
                    break;
                }
            case 4://urunSil
                {
                    cout << "Urun Sil"<<endl;
                    if (urunSayiKontrol){
                        int secim4;
                        cout << "1)ID ile sil\n2)Isim ile sil\n3)Barkod ile sil\n>>> ";
                        cin >> secim4;
                        bool control;
                        int gID;
                        switch (secim4){
                    case 1:
                        {
                            cout << "Silmek istediginiz urunun ID bilgisini giriniz: ";
                            cin >> gID;
                            control = idControl(urun,valueCount,gID);
                            if (control==false){
                                cout << "Bu ID ile bir urun bulunamadi." << endl<<endl;
                            }
                            break;
                        }
                    case 2:
                        {
                            string gName;
                            cout << "Silmek istediginiz urunun isim bilgisini giriniz: ";
                            cin >> gName;
                            gID = findIdWithName(urun,valueCount,gName);
                            if (gID !=0){
                                control = idControl(urun,valueCount,gID);
                            }
                            else{
                                cout << "Bu isimde bir urun bulunamadi."<<endl<<endl;
                                control = false;
                            }
                            break;
                        }
                    case 3:
                        {
                            int gBarcode;
                            cout <<"Silmek istediginiz urunun barkod bilgisini giriniz: ";
                            cin >> gBarcode;
                            gID = findIdWithBarcode(urun,valueCount,gBarcode);
                            if (gID !=0){
                                control = idControl(urun,valueCount,gID);
                            }
                            else{
                                cout << "Bu barkod nuamrasina sahip bir urun bulunamadi."<<endl<<endl;
                                control = false;
                            }
                            break;
                        }
                    default:
                        {
                           cout << selectErrorMessage <<endl<<endl;
                        }
                        }
                        if (control){
                            gID--;
                            cout << "Urun Adi: " << urun[gID].name << endl << "Urun Stok: " << urun[gID].stockCount << endl << "Urun Fiyat: " << urun[gID].price << endl;
                            char control2;
                            cout << "Silmek istediginizden emin misiniz?(e/E): ";
                            cin >> control2;
                            if (control2 == 'e' || control2 == 'E'){
                                urun[gID].id = 0;
                                urun[gID].name = "null";
                                urun[gID].price = 0;
                                urun[gID].stockCount =0;
                                cout <<"Silme islemi basarili."<<endl;
                                txtFileUpdate(urun,valueCount);
                            }
                            else{
                                cout << "Islem iptal edildi."<<endl;
                            }
                        }
                    }
                    else{
                        cout << noProductErrorMessage << endl;
                    }
                    break;
                }
            case 5://fiyatGuncelle
                {
                    cout << "Fiyat Guncelle"<<endl;
                    if (urunSayiKontrol){
                        int secim5;
                        cout << "1)ID ile fiyat guncelle\n2)Name ile fiyat guncelle\n3)Barkod ile fiyat guncelle\n>>> ";
                        cin >> secim5;
                        bool control;
                        int gID;
                        switch(secim5){
                        case 1:
                            {
                                // id ile fiyat guncelle
                                cout << "Fiyatini guncellemek istediginiz urunun ID numarasini giriniz: ";
                                cin >> gID;
                                control = idControl(urun,valueCount,gID);
                                if (control==false){
                                    cout << "Bu ID ile bir urun bulunamadi." << endl<<endl;
                                }
                                break;
                            }
                        case 2:
                            {
                                // name ile fiyat guncelle
                                string gName;
                                cout << "Fiyatini guncellemek istediginiz urunun isim bilgisini giriniz: ";
                                cin >> gName;
                                gID = findIdWithName(urun,valueCount,gName);
                                if (gID !=0){
                                    control = idControl(urun,valueCount,gID);
                                }
                                else{
                                    cout << "Bu isimde bir urun bulunamadi."<<endl<<endl;
                                    control = false;
                                }
                                break;
                            }
                        case 3:
                            {
                                int gBarcode;
                                cout << "Fiyatini guncellemek istedigininz urunun barkod bilgisini giriniz: ";
                                cin >> gBarcode;
                                gID = findIdWithBarcode(urun,valueCount,gBarcode);
                                if (gID !=0){
                                    control = idControl(urun,valueCount,gID);
                                }
                                else{
                                    cout << "Bu barkod numarasina sahip bir urun bulunamadi."<<endl<<endl;
                                    control = false;
                                }
                                break;
                            }
                        default:
                            {
                                cout << selectErrorMessage <<endl;
                            }
                        }
                        if (control){
                            gID--;
                            int newFiyat;
                            cout << urun[gID].name << "'nin suanki fiyati: " << urun[gID].price <<"TL." <<endl;
                            cout << urun[gID].name << " icin fiyat girin: ";
                            cin >> newFiyat;
                            if (newFiyat >0){
                                urun[gID].price= newFiyat;
                                txtFileUpdate(urun,valueCount);
                            }
                        }
                    }
                    else{
                        cout << noProductErrorMessage << endl;
                    }



                    break;
                }
            case 6://stokGuncelle
                {
                    cout << "Stok Guncelle"<<endl;
                    if (urunSayiKontrol){
                        int secim6;
                        int gID;
                        bool control;
                        cout << "1)ID ile stok guncelle\n2)Isim ile stok guncelle\n3)Barkod numarasi ile stok guncelle\n>>> ";
                        cin >> secim6;
                        switch(secim6){
                            case 1:
                                {
                                    cout << "Stogunu guncellemek istediginiz urunun ID numarasini giriniz: ";
                                    cin >> gID;
                                    control = idControl(urun,valueCount,gID);
                                    if (control==false){
                                        cout << "Bu ID ile bir urun bulunamadi." << endl<<endl;
                                    }
                                    break;
                                }
                            case 2:
                                {
                                    string gName;
                                    cout << "Sotgunu guncellemek istediginiz urunun isim bilgisini giriniz: ";
                                    cin >> gName;
                                    gID = findIdWithName(urun,valueCount,gName);
                                    if (gID !=0){
                                        control = idControl(urun,valueCount,gID);
                                    }
                                    else{
                                        cout << "Bu isimde bir urun bulunamadi."<<endl<<endl;
                                        control = false;
                                    }
                                    break;
                                }
                            case 3:
                            {
                                    int gBarcode;
                                    cout << "Stogunu guncellemek istedigininz urunun barkod bilgisini giriniz: ";
                                    cin >> gBarcode;
                                    gID = findIdWithBarcode(urun,valueCount,gBarcode);
                                    if (gID !=0){
                                        control = idControl(urun,valueCount,gID);
                                    }
                                    else{
                                        cout << "Bu barkod numarasina sahip bir urun bulunamadi."<<endl<<endl;
                                        control = false;
                                    }
                                    break;
                            }
                            default:
                                {
                                   cout << selectErrorMessage <<endl;
                                }
                        }
                        if (control){
                            gID--;
                            cout << "Urun Adi: " << urun[gID].name << endl << "Urun Stok: " << urun[gID].stockCount << endl << "Urun Fiyat: " << urun[gID].price << endl << endl;
                            int newStock;
                            cout << "Yeni stok sayisi: ";
                            cin >> newStock;
                            if (newStock >0){
                                urun[gID].stockCount = newStock;
                                cout << "Guncelleme basarili. Yeni stok :" << newStock << endl;
                                txtFileUpdate(urun,valueCount);
                                cout << endl << endl;
                            }
                        }
                    }
                    else{
                        cout << noProductErrorMessage << endl;
                    }
                    break;
                }
            case 13://hakkinda
                {
                    cout << hTag << endl << "#  BILGISAYARCI STOK TAKIP OTOMASYONU  #" << endl << "#          FURKAN CAGRI ERKOCA         #" << endl<<"#              2012721007              #" <<endl << hTag << endl;
                    break;
                }
            case 7://barkodGuncelle
                {
                    cout << "Barkod Guncelle"<<endl;
                    if (urunSayiKontrol){
                        int secim5;
                        cout << "1)ID ile barkod guncelle\n2)Name ile barkod guncelle\n3)Barkod ile barkod guncelle\n>>> ";
                        cin >> secim5;
                        bool control;
                        int gID;
                        switch(secim5){
                        case 1:
                            {
                                // id ile fiyat guncelle
                                cout << "Barkodunu guncellemek istediginiz urunun ID numarasini giriniz: ";
                                cin >> gID;
                                control = idControl(urun,valueCount,gID);
                                if (control==false){
                                    cout << "Bu ID ile bir urun bulunamadi." << endl<<endl;
                                }
                                break;
                            }
                        case 2:
                            {
                                // name ile fiyat guncelle
                                string gName;
                                cout << "Barkodunu guncellemek istediginiz urunun isim bilgisini giriniz: ";
                                cin >> gName;
                                gID = findIdWithName(urun,valueCount,gName);
                                if (gID !=0){
                                    control = idControl(urun,valueCount,gID);
                                }
                                else{
                                    cout << "Bu isimde bir urun bulunamadi."<<endl<<endl;
                                    control = false;
                                }
                                break;
                            }
                        case 3:
                            {
                                int gBarcode;
                                cout << "Barkodunu guncellemek istedigininz urunun suanki barkod bilgisini giriniz: ";
                                cin >> gBarcode;
                                gID = findIdWithBarcode(urun,valueCount,gBarcode);
                                if (gID !=0){
                                    control = idControl(urun,valueCount,gID);
                                }
                                else{
                                    cout << "Bu barkod numarasina sahip bir urun bulunamadi."<<endl<<endl;
                                    control = false;
                                }
                                break;
                            }
                        default:
                            {
                                cout << selectErrorMessage <<endl;
                            }
                        }
                        if (control){
                            gID--;
                            int barcode2;
                            cout << urun[gID].name << "'nin suanki barkodu : " << urun[gID].barcode <<"." <<endl;
                            cout << urun[gID].name << " icin yeni barkodu girin: ";
                            cin >> barcode2;
                            if (barcode2 >0){
                                urun[gID].barcode= barcode2;
                                txtFileUpdate(urun,valueCount);
                            }
                        }
                    }
                    else{
                        cout << noProductErrorMessage << endl;
                    }

                    break;
                }
            case 8://kdvGuncelle
                {
                    cout << "KDV Guncelle"<<endl;
                    if (urunSayiKontrol){
                        int secim5;
                        cout << "1)ID ile KDV guncelle\n2)Name ile KDV guncelle\n3)Barkod ile KDV guncelle\n>>> ";
                        cin >> secim5;
                        bool control;
                        int gID;
                        switch(secim5){
                        case 1:
                            {
                                // id ile fiyat guncelle
                                cout << "KDV oranini guncellemek istediginiz urunun ID numarasini giriniz: ";
                                cin >> gID;
                                control = idControl(urun,valueCount,gID);
                                if (control==false){
                                    cout << "Bu ID ile bir urun bulunamadi." << endl<<endl;
                                }
                                break;
                            }
                        case 2:
                            {
                                // name ile fiyat guncelle
                                string gName;
                                cout << "KDV oranini guncellemek istediginiz urunun isim bilgisini giriniz: ";
                                cin >> gName;
                                gID = findIdWithName(urun,valueCount,gName);
                                if (gID !=0){
                                    control = idControl(urun,valueCount,gID);
                                }
                                else{
                                    cout << "Bu isimde bir urun bulunamadi."<<endl<<endl;
                                    control = false;
                                }
                                break;
                            }
                        case 3:
                            {

                                int gBarcode;
                                cout << "KDV oranini guncellemek istedigininz urunun barkod bilgisini giriniz: ";
                                cin >> gBarcode;
                                gID = findIdWithBarcode(urun,valueCount,gBarcode);
                                if (gID !=0){
                                    control = idControl(urun,valueCount,gID);
                                }
                                else{
                                    cout << "Bu barkod numarasina sahip bir urun bulunamadi."<<endl<<endl;
                                    control = false;
                                }
                                break;
                            }
                        default:
                            {
                                cout << selectErrorMessage <<endl;
                            }
                        }
                        if (control){
                            gID--;
                            int kdvOran;
                            cout << urun[gID].name << "'nin suanki KDV orani : %" << urun[gID].rateVAT <<"." <<endl;
                            cout << urun[gID].name << " icin yeni KDV oranini girin: ";
                            cin >> kdvOran;
                            if (kdvOran >0){
                                urun[gID].rateVAT= kdvOran;
                                txtFileUpdate(urun,valueCount);
                            }
                        }

                    }
                    else{
                        cout << noProductErrorMessage << endl;
                    }

                    break;
                }
            case 9://agirlikGuncelle
                {
                    cout << "Agirlik Guncelle"<<endl;
                    if (urunSayiKontrol){
                        int secim5;
                        cout << "1)ID ile agirlik guncelle\n2)Name ile agirlik guncelle\n3)Barkod ile agirlik guncelle\n>>> ";
                        cin >> secim5;
                        bool control;
                        int gID;
                        switch(secim5){
                        case 1:
                            {
                                // id ile fiyat guncelle
                                cout << "Agirligini guncellemek istediginiz urunun ID numarasini giriniz: ";
                                cin >> gID;
                                control = idControl(urun,valueCount,gID);
                                if (control==false){
                                    cout << "Bu ID ile bir urun bulunamadi." << endl<<endl;
                                }
                                break;
                            }
                        case 2:
                            {
                                // name ile fiyat guncelle
                                string gName;
                                cout << "Agirligini guncellemek istediginiz urunun isim bilgisini giriniz: ";
                                cin >> gName;
                                gID = findIdWithName(urun,valueCount,gName);
                                if (gID !=0){
                                    control = idControl(urun,valueCount,gID);
                                }
                                else{
                                    cout << "Bu isimde bir urun bulunamadi."<<endl<<endl;
                                    control = false;
                                }
                                break;
                            }
                        case 3:
                            {

                                int gBarcode;
                                cout << "Agirligini guncellemek istedigininz urunun barkod bilgisini giriniz: ";
                                cin >> gBarcode;
                                gID = findIdWithBarcode(urun,valueCount,gBarcode);
                                if (gID !=0){
                                    control = idControl(urun,valueCount,gID);
                                }
                                else{
                                    cout << "Bu barkod numarasina sahip bir urun bulunamadi."<<endl<<endl;
                                    control = false;
                                }
                                break;
                            }
                        default:
                            {
                                cout << selectErrorMessage <<endl;
                            }
                        }
                        if (control){
                            gID--;
                            int gAgirlik;
                            cout << urun[gID].name << "'nin suanki agirligi : " << urun[gID].weight <<"." <<endl;
                            cout << urun[gID].name << " icin yeni agirligi girin: ";
                            cin >> gAgirlik;
                            if (gAgirlik >0){
                                urun[gID].weight= gAgirlik;
                                txtFileUpdate(urun,valueCount);
                            }
                        }
                    }
                    else{
                        cout << noProductErrorMessage << endl;
                    }

                    break;
                }
            case 10://butunUrunleriSil
                {
                    cout << "Butun Urunleri Sil"<<endl;
                    if (urunSayiKontrol){
                        char secim10;
                        cout << "Stokta bulunan butun urunleri siler. Bunu yapmak istediginden emin misin? (e/E): ";
                        cin >> secim10;
                        if (secim10 =='e'|| secim10=='E'){
                            remove(FILENAME);
                            for (int i=0;i<valueCount;i++){
                                urun[i].id = 0;
                                urun[i].name = "null";
                                urun[i].price = 0;
                                urun[i].stockCount =0;
                            }
                            cout << "Silme islemi basarili" << endl;
                        }
                    }
                    else{
                        cout << noProductErrorMessage << endl;
                    }
                    break;
                }
            case 11://faturalariGor
                {
                    cout << "Faturalari Gor"<<endl;
                    int result;
                    result = faturalariYazdir(faturaIsim);
                    if(result>0){
                        cout <<endl;
                        int secim11;
                        cout << "Hangi faturayi yazdirmak istersiniz: ";
                        cin >> secim11;
                        string faturaKonum = FATURAKLASOR;
                        faturaKonum += faturaIsim[secim11-1];
                        cout << endl << endl;
                        ifstream input(faturaKonum);
                        for(string line;getline(input,line);){
                            cout << line << endl;
                        }
                        cout << endl << endl;
                    }
                    else{
                        cout <<"Fatura bulunamadi."<<endl<<endl;
                    }

                    break;
                }
            default:
                cout << selectErrorMessage <<endl;
        }
    }
    return 0;
}
