#include<stdio.h>
#define MAX 15
void drawBoard(int matris[][MAX], int N);
void readFromFile(int matris[][MAX], char *fileName);
int main(){
            int skor[MAX]={0};
            int i,j=0,tus=1,N,k,l,m,y,t,z,p,s,r,x1,y1,back=0,x2,y2,c,toplamskor;
            char fileName[20];
            printf("kac adet kullanici oyunu oynayacak?\n");
            scanf("%d",&p);
            char user[p][MAX];
            printf("oyunu oynayacak kullanicilarin adlari nedir?\n");

           for(i=0;i<p;i++){
            scanf("%s",&user[i]);
                }
         while(back==0)  // oyundan cik tusuna basana kadar oyunda kalmak icin dongu
            { 

    int gecersizhamle=0,undo[MAX][MAX]={0},undosayac=0,sayac=0,exit=0,adim=1,puan=0;
    int matris[MAX][MAX]={{0}};
    printf("ANA MENU\n");
    printf("1. rastgele matris olustur\n");
    printf("2. dosyadan matris olustur\n");
    printf("3. kullanici skorlarini goster\n");
    printf("4. cikis\n");
    scanf("%d",&k);

    if(k==1)        // rastgele matris modu kodlari
    {
        printf("kacinci kullanici oyunu oynayacak?\n");
        scanf("%d",&r);
      if(r>p || r<=0)
      {
          printf("gecersiz bir sayi girdiniz\n");     // kullanici sayisindan fazla bir deger veya 0 ve kucuk deger girince hata vermesini sagladim
      }
      else{
        printf("1. manuel modda oyna\n");
        printf("2. ana menuye don\n");
        scanf("%d",&l);
        if(l==1)
        {
            printf("matrisin boyutlarini giriniz\n");
            scanf("%d",&N);
            for(i=0;i<N;i++)
            {
                for(j=0;j<N;j++){
                    matris[i][j]=0;       
                }
            }

            srand(time(NULL));
            for(i=2;i<=N*2+1;i++)       // rastgele matris modunda oyun tahtasini rastgele olusturmak icin
               {

               z= i / 2;
               y=rand() %N;
               t=rand() %N;
               if(matris[y][t]==0)      {

                matris[y][t]=z;         }
                else                    {

                 c=0,j=0;
                 while(matris[c][j]!=0) {
                    j++;

                }
                 matris[c][j]=z;
                }
                }
                drawBoard(matris,N);
               while(exit!=1)          // oyun sonlanana kadar bu dongude kalinacak
               {

               printf("baslangic noktasini giriniz,onceki hamlenize donmek icin -1,-1 giriniz.\n");     // matrisin undo olmasi
               scanf("%d,%d",&x1,&y1);
               if(x1==-1 && y1==-1)
               {
                   for(i=0;i<N;i++){
                for(j=0;j<N;j++){

                    matris[i][j]=undo[i][j];   // bir onceki hamleye donebilmek icin onceki durumu bir matriste sakladim
                    }}
                    undosayac++;    // yapilan undo hamle sayisini tuttum cunku puanlama icin gerekli

               }
               else{
               printf("bitis noktasini giriniz\n");
               scanf("%d,%d",&x2,&y2);
               printf("bu yol hangi sayinin yolu olsun\n");
               scanf("%d",&m);
               printf("%d . adim =(%d,%d) ---> (%d,%d)\n",adim,x1,y1,x2,y2);   // burada yapilan hamleyi ve hamlenin kacinci adim oldugunu yazdirdim
               adim++;
               if(x1>=N || x2>=N  || y1>=N || y2>=N || m>N)
               {
                   printf("gecersiz hamle girdiniz.\n");    // oyun tahtasi boyutundan buyuk bir sayi girilirse gecersiz olmasini sagladim
                   gecersizhamle++;    // gecersiz hamle sayaci tuttum bu da puanlama icin gerekli
               }
else {
               for(i=0;i<N;i++){
                for(j=0;j<N;j++){

                    undo[i][j]=matris[i][j];
                    }}

               for(i=0;i<N;i++){
                for(j=0;j<N;j++){

                    undo[i][j]=matris[i][j];
                    }}
               if(x1==x2 && y1<y2)                 // buralarda girilen hamlenin yeni halini matrise yerlestirdim
               {
                 for(i=y1;i<=y2;i++)
                 {
                    matris[x1][i]=m;
                 }
                 }
                 else if(x1==x2 && y1>y2)
                 {
                     for(i=y1;i>=y2;i--)
                 {
                    matris[x1][i]=m;
                 }
                 }
                 else if(x1<x2 && y1==y2)
                 {
                     for(i=x1;i<=x2;i++)
                 {
                    matris[i][y1]=m;
                 }
                 }
                 else if (x1>x2 && y1==y2)
                 {
                     for(i=x1;i>=x2;i--)
                 {
                    matris[i][y1]=m ;
                 }
                 }
               }
               }
                 drawBoard(matris,N);     // yapilan hamleden sonra oyun tahtasini bastirdim
                 for(i=0;i<N;i++)
            {
                for(j=0;j<N;j++){
                    if(matris[i][j]==0)
                    {
                        sayac++;     // tahtada bosluk kalmayinca sayaci arttirdim bu sayede while dongusunden cikacak ve oyun sonlanacak
                    }
                }
            }
            if(sayac==0)
            {
                exit=1;
            }
            else{
                sayac=0;
            }
               }
                 exit=0;
                 puan-=undosayac*10;  // yapylan undo sayisina gore puanlama
                 puan+=N*10;    // matrisin boyutuna gore puanlama
                 puan+=20; // rastgele matris modunda oynadigi icin
                 puan-=gecersizhamle*5;      // gecersiz hamle sayisina gore puanlama
                 skor[r-1]+=puan;     // oyunu oynayan kullanicinin toplam skorunu bir dizide sakladim
                 toplamskor=skor[r-1];   

                 printf("tebrikler kazandiniz\n");
                 printf("bu oyundaki puaniniz:%d\n",puan);
                 printf("%s isimli kullanicinin toplam skoru:%d\n",user[r-1],toplamskor);
                 puan=0;    // oyun bittigi icin bu oyunda gecerli puaný sýfýrladim ki bidahaki oyunda 0dan baslasin
        }
                 if(l==2)
                 {
                     back=0;   // kullanici ana menuye donu secerse ana menuye donmesi icin
                 }
    }
    }

                 if(k==2)          // dosyadan matris modu
                 {
                 	printf("kacinci kullanici oyunu oynayacak?\n");
                     scanf("%d",&r);
                     if(r>p || r<=0)
      {
                 printf("gecersiz bir sayi girdiniz\n");  } // kullanici sayisindan fazla bir deger veya 0 ve kucuk deger girince hata vermesini sagladim
      else{
                     printf("1. manuel modda oyna\n");
                     printf("2. ana menuye don\n");
                     scanf("%d",&l);
                 if(l==1){
                     printf("matrisin boyutlarini giriniz\n");
                     scanf("%d",&N);
                     printf("Dosya Adini Giriniz");
  	                 scanf("%s",fileName);
                     readFromFile(matris,fileName);
                     drawBoard(matris,N);

                     while(exit!=1)   // oyun sonlanana kadar bu dongude kalinacak
               {

               printf("baslangic noktasini giriniz,onceki hamlenize donmek icin -1,-1 giriniz.\n");  // matrisin undo olmasi
               scanf("%d,%d",&x1,&y1); 
               if(x1==-1 && y1==-1)
               {
                   for(i=0;i<N;i++){
                for(j=0;j<N;j++){

                    matris[i][j]=undo[i][j];    // bir onceki hamleye donebilmek icin onceki durumu bir matriste sakladim
                    }}
                undosayac++;  // undo sayaci tuttum cunku puanlamada gerekli
               }

else {
               printf("bitis noktasini giriniz\n");
               scanf("%d,%d",&x2,&y2);
               printf("bu yol hangi sayinin yolu olsun\n");
               scanf("%d",&m);
               printf("%d . adim =(%d,%d) ---> (%d,%d)\n",adim,x1,y1,x2,y2);   // yapilan hamleler ve adim sayisi ekrana bastiriliyor
               adim++;
               if(x1>=N || x2>=N  || y1>=N || y2>=N || m>N+1)
               {
                   printf("gecersiz hamle girdiniz.\n");    // oyun tahtasindan buyuk deger girilirse gecersiz hamle uyarisi
                   gecersizhamle++;  // gecersiz hamle sayaci puanlamada gerekli
               } 
else {

               for(i=0;i<N;i++){
                for(j=0;j<N;j++){

                    undo[i][j]=matris[i][j];
                }
                }

               if(x1==x2 && y1<y2)   // yapilan hamleye gore matrisin yeni halini ayarlama
               {
                 for(i=y1;i<=y2;i++)
                 {
                    matris[x1][i]=m;
                 }
                 }
                 else if(x1==x2 && y1>y2)
                 {
                     for(i=y1;i>=y2;i--)
                 {
                    matris[x1][i]=m;
                 }
                 }
                 else if(x1<x2 && y1==y2)
                 {
                     for(i=x1;i<=x2;i++)
                 {
                    matris[i][y1]=m;
                 }
                 }
                 else if (x1>x2 && y1==y2)
                 {
                     for(i=x1;i>=x2;i--)
                 {
                    matris[i][y1]=m ;
                 }
                 }
               }
               }
                 drawBoard(matris,N);

                    for(i=0;i<N;i++)
            {
                for(j=0;j<N;j++){
                    if(matris[i][j]==0)
                    {
                        sayac++;   // oyun bitince donguden cikmak icin
                    }
                }
            }
            if(sayac==0)
            {
                exit=1;    
            }
            else{
                sayac=0;
            }
                 }

                 exit=0;
                 puan-=undosayac*10;  // yapilan undo sayisina gore puanlama
                 puan+=N*10;    // matrisin boyutuna gore puanlama
                 puan+=10; // dosyadan matris modunda oynadigi icin
                 puan-=gecersizhamle*5;
                 skor[r-1]+=puan;
                 toplamskor=skor[r-1];
                 printf("tebrikler kazandiniz\n");
                 printf("bu oyundaki puaniniz:%d\n",puan);
                 printf("%s isimli kullanicinin toplam skoru:%d\n",user[r-1],toplamskor);
                 puan=0;

                 }
                 if(l==2)
                 {
                     back=0;  // ana menuye donme tusu
                 }

                 }
                 }
                 if(k==3)        // ana menude kullanici skorlarini goster kismi
                 {
              for(i=0;i<p;i++)
              {
                  printf("%s isimli kullanicinin toplam skoru:%d\n",user[i],skor[i]);
              }
                 }
                 if(k==4)      // cikis bolumu
                 {
                     return 0;
                 }
            }

  return 0;
}
void readFromFile(int matris[][MAX], char *fileName){
	int i,j, temp;
	FILE *data = fopen(fileName,"r");
	if(!data){
        printf("Dosya Acilamadi!");
		return;
    }
    while(!feof(data)){
        fscanf(data,"%d %d %d\n",&i,&j,&temp);
		matris[i][j]=temp;
    }
  	fclose(data);
}

void drawBoard(int matris[][MAX], int N){
    int i,j,k;
    for(i=0;i<N;i++){
        printf("\n");
        for (k=0;k<N;k++)
            printf("-------");
        printf("\n");
        for(j=0;j<N;j++)
            if (matris[i][j]!=0)
                printf("  %d   |",matris[i][j]);
            else
                 printf("      |",matris[i][j]);
    }
}
