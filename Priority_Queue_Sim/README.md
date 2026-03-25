# Max-Heap Tabanlı Çoklu Kuyruk (Priority Queue) Simülasyonu

> **Ders:** Veri Yapıları  
> **Öğrenci No:** 21011088  
> **Ödev:** HW3

---

## 📋 Proje Açıklaması

Bu proje, **N adet kuyruğun (queue) bir matris yapısı içinde temsil edildiği** ve her kuyruğun **Max-Heap** özelliği taşıdığı bir veri yapıları uygulamasıdır. Program, kullanıcıdan alınan boyutlara göre dinamik olarak bir matris oluşturur, bu matrisi benzersiz rastgele sayılarla doldurur, ardından heap yapısına dönüştürüp kuyrukları tek tek boşaltır.

### Temel Kavramlar

| Kavram | Açıklama |
|--------|----------|
| **Max-Heap** | Her düğümün, çocuklarından büyük veya eşit olduğu ağaç yapısı. Kök eleman her zaman en büyüktür. |
| **Priority Queue** | Elemanların öncelik sırasına göre çıkarıldığı kuyruk. Burada en büyük eleman en yüksek önceliğe sahiptir. |
| **Matris Temsili** | Her satır bir kuyruğu, sütunlar ise kuyruktaki elemanları temsil eder. |

---

## ⚙️ Programın Çalışma Mantığı

### 1. Kullanıcı Girişi
- Matris boyutları (`N × M`) kullanıcıdan alınır.
  - `N` → Kuyruk sayısı (satır)
  - `M` → Maksimum kuyruk kapasitesi (sütun)
- Her kuyruk için ayrı ayrı kapasite girilir (kapasite ≤ M).

### 2. Rastgele Matris Oluşturma (`randomMatrix`)
- `[1, N*M+5]` aralığında **benzersiz** rastgele tam sayılar üretilir.
- Her kuyruk, belirtilen kapasitesine göre bu sayılarla doldurulur.
- Boş kalan hücreler `-1` değeriyle işaretlenir.

### 3. Max-Heap Dönüşümü (`heapify`)
- Her satır (kuyruk) bağımsız olarak **Max-Heap** yapısına dönüştürülür.
- `heapifyRow` fonksiyonu, standart heap-down (sift-down) algoritmasını uygular.
- Dönüşüm sonrası her kuyruğun ilk elemanı (`matrix[i][0]`) o kuyruğun en büyük elemanıdır.

### 4. Dequeue İşlemi (`dequeue`)
Her adımda şunlar gerçekleşir:
1. Tüm kuyrukların kök elemanları (ilk elemanlar) okunur ve ekrana yazdırılır.
2. Bu kök elemanlar arasından **en büyüğü** bulunur.
3. En büyük eleman kuyruğundan çıkarılır:
   - Kuyruğun son elemanı köke taşınır.
   - Son pozisyon `-1` olarak işaretlenir.
   - Kuyruk boyutu 1 azaltılır.
   - Yeniden `heapifyRow` uygulanır.
4. Bir kuyruk tamamen boşaldığında, boşalma sırası kaydedilir.

### 5. Sonlanma
- Tüm kuyruklar boşaldığında döngü sona erer.
- Kuyrukların boşalma sırası ekrana yazdırılır.
- Dinamik olarak ayrılan tüm bellek `free()` ile serbest bırakılır.

---

## 🧩 Fonksiyon Listesi

| Fonksiyon | Açıklama |
|-----------|----------|
| `swap(int *a, int *b)` | İki tamsayının değerlerini takas eder. |
| `randomMatrix(...)` | Matrisi benzersiz rastgele sayılarla doldurur ve ekrana yazdırır. |
| `heapifyRow(int *row, int length, int index)` | Bir satırda (kuyrukta) belirli bir indeksten başlayarak heap özelliğini sağlar. |
| `heapify(int **matrix, int n, int m)` | Matristeki tüm satırları Max-Heap yapısına dönüştürür. |
| `dequeue(...)` | Tüm kuyruklardan en büyük elemanı bulup çıkarır, heap yapısını korur. |
| `printMatrix(...)` | Matrisi formatlı şekilde ekrana yazdırır. |
| `main()` | Kullanıcı girdilerini alır, program akışını yönetir. |

---

## 🚀 Derleme ve Çalıştırma

### Gereksinimler
- **GCC** (MinGW, MSYS2 vb.) veya herhangi bir C derleyicisi

### Windows (GCC / MinGW)

```bash
# Derleme
gcc -o 21011088 21011088.c

# Çalıştırma
.\21011088.exe
```

### Linux / macOS

```bash
# Derleme
gcc -o 21011088 21011088.c

# Çalıştırma
./21011088
```

---

## 📖 Örnek Kullanım

```
Matris boyutlarini giriniz (N M): 3 4
Her bir kuyrugun kapasitesini giriniz:
Kuyruk 1 kapasitesi: 4
Kuyruk 2 kapasitesi: 3
Kuyruk 3 kapasitesi: 2

Rastgele uretilen 3 adet kuyruktan olusan matris:

 | 7     | 12    | 3     | 15    |
 | 9     | 1     | 11    | -1    |
 | 5     | 8     | -1    | -1    |

Max-Heap ozelligi tasiyan 3 adet kuyruktan olusan matris
 | 15    | 12    | 3     | 7     |
 | 11    | 1     | 9     | -1    |
 | 8     | 5     | -1    | -1    |

Kuyruklardan degerleri okunan elemanlar: 15, 11, 8
Matristen cikarilan en buyuk eleman: 15
...
(işlem tüm kuyruklar boşalana kadar devam eder)
...
Tum kuyruklar bos!
Sirasiyla elemanlari tukenen kuyruklar: 3,2,1
```

> **Not:** Sayılar rastgele üretildiği için her çalıştırmada farklı değerler görülür.

---

## 📂 Dosya Yapısı

```
HW3_21011088/
├── 21011088.c      # Ana kaynak kod dosyası
├── 21011088.pdf    # Ödev açıklaması / rapor
└── README.md       # Bu dosya
```
