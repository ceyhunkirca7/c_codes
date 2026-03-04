# Sayı Birleştirme Oyunu (Numberlink) - Proje Rehberi

Bu proje, C programlama dili ile geliştirilmiş terminal tabanlı bir sayı birleştirme (Numberlink) zeka oyunudur. Oyuncudan NxN boyutundaki bir matriste aynı sayıları, yolların birbirini kesmemesi şartıyla birleştirmesi ve tüm matrisi boşluk kalmayacak şekilde doldurması beklenmektedir. Projede çoklu oyuncu desteği, rastgele matris üretimi, dosyadan matris okuma, puanlama sistemi ve hamle geri alma (undo) özellikleri bulunmaktadır.

## 🛠️ Kurulum ve Derleme İşlemleri

Eğer projeyi sıfırdan derlemek isterseniz, bilgisayarınızda bir C derleyicisi (örneğin MinGW) kurulu olmalıdır.

**Terminal üzerinden derlemek için:**
```bash
gcc 21011088.c -o oyun.exe
```

Dev-C++ IDE kullanıyorsanız, `21011088.dev` proje dosyasını açıp derleyebilirsiniz. Windows üzerinden doğrudan `.\21011088.exe` komutu ile mevcut derlenmiş uygulamayı direkt çalıştırabilirsiniz.

## 🚀 Projeyi Çalıştırma ve Adım Adım Oynanış

Terminali (Windows Command Prompt veya PowerShell) proje dizininde açın ve aşağıdaki komutu girerek oyunu başlatın:

```cmd
.\21011088.exe
```

Oyun çalıştırıldıktan sonra terminal (komut) arayüzündeki tüm etkileşimler adım adım aşağıda açıklanmıştır:

### 1. Sisteme Giriş ve Tanımlamalar

- **Soru:** `kac adet kullanici oyunu oynayacak?`
  - **Ne Girilecek:** Oyunu arka arkaya oynayacak (ya da sırası geldiğinde menüye dahil olacak) kullanıcı sayısıdır. **Örn: `1`** diyerek Enter'a basın.

- **Soru:** `oyunu oynayacak kullanicilarin adlari nedir?`
  - **Ne Girilecek:** Kayıt açılacak oyuncunun profil ismi. **Örn: `Ahmet`** diyerek Enter'a basın. Eğer 2 oyuncu girdiyseniz ilkini yazıp Enter yaptıktan sonra menüde ikincisini soracaktır.

### 2. Oyun Modu Menüsü

Isim girişinden hemen sonra ekrana aşağıdaki gibi ana menü yansır:

```text
ANA MENU
1. rastgele matris olustur
2. dosyadan matris olustur
3. kullanici skorlarini goster
4. cikis
```

*Fakat menüde ne seçeceğinizi belirtmeden hemen önce hangi oyuncunun hamlesi olacağını bildirmelisiniz:*

- **Soru:** `kacinci kullanici oyunu oynayacak?`
  - **Ne Girilecek:** İlk sırada girdiğiniz kullanıcının oynaması için numarası. **Örn: `1`** (Eğer çoklu girdiyseniz diğerinin numarası vs. girilebilir). Enter'a basın.

- **Menü Seçimi (Görünmez Soru):** Bu aşamada imleç bekleyecektir. **Örn: `2`** yazıp Enter'a basarak **Dosyadan matris oluşturma** seçeneğini seçin.

### 3. Tahtayı Seçme ve Çizdirme

Seçenek 2'yi seçmeniz halinde sistem sizden oynamak istediğiniz tahta dosyasını isteyecektir:

- **Soru / Bekleyiş:** `11x11.txt`, `5x5.txt`, veya `7x7.txt` gibi proje klasöründe bulunan dosyalardan bir tanesinin adını girin.
  - **Giriş:** **`5x5.txt`**

Dosya okunduğunda terminalde `- - -` çizgileri kullanılarak oyun matrisi (tahta) aşağıdaki gibi çizilecektir. Oyunun hedefi, 0 olan boşlukları bağlamak istediğiniz sayıyla doldurmaktır.

### 4. Oyun İçi Hamleler ve Koordinatlar

Tahta çizildikten sonra sizden birleştirme hamleleriniz için koordinatlar isteyecektir. Her hamlede sırasıyla başlangıç `x1,y1` sonrasında bitiş `x2,y2` istenecek şekilde tasarlandığı için format şöyledir:

- **Soru:** `baslangic noktasini giriniz,onceki hamlenize donmek icin -1,-1 giriniz.`
  - **Ne Girilecek:** Matrisin üstünde gördüğünüz sayıya karşılık gelen X ve Y koordinatlarıdır (satır, sütun). **Örn: `1,2`** (Dikkat: C dilinde matris indekslerinin 0'dan başladığını ve programınızdaki koordinatlama mantığına göre girilmesi gerektiğini unutmayın). Enter'a basın.
  *Not: Hamle geri almak istenirse, `-1,-1` yazılır.*

- **Soru:** (Sistem içindeki scanf bekleyişi, bazen soru yazısı atlanabilir)
  - **Ne Girilecek:** Bitiş noktasının koordinatları aynı şekilde. **Örn: `1,4`**

- **Soru:** `bu yol hangi sayinin yolu olsun`
  - **Ne Girilecek:** Başlangıç ile bitiş arasındaki kutucukların hangi rakamla (böylece hangi sayıyla birleştirileceğini) belirleyen değerdir. Örneğin 3 leri birleştiriyorsanız yolu da 3 karakterinden oluşturmak için **Örn: `3`** yazın.

Girdiğiniz noktalar arasındaki satır veya sütun 3'lerle doldurulur ve tahtanın güncel hali basılır.

### 5. Puanlama ve Oyun Bitişi

Tahtadaki 0'lar (boşluklar) tamamen birleştirilince sayı birleştirme tamamlanmış olur. Tamamlanma durumunda:
1. Oyun matris boyutuna göre bir temel puan ekler.
2. Sizin yaptığınız her `undo` (Geri alma) hamlesi başına *10 puan düşülür*.
3. Belirlenen sınırlardan fazla, geçersiz veya oyun dışı girilen her hatalı koordinatta *5 puan düşürülür*.
4. Toplam puanınız ekrana basılır ve `ANA MENU`'ye tekrar yönlendirilirsiniz.
