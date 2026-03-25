# N-Vezir Problemi (N-Queens Problem)

Bu proje, klasik **N-Vezir** problemini 4 farklı algoritma ile çözen bir C konsol uygulamasıdır. Her algoritmanın çalışma süresi ölçülerek performans karşılaştırması yapılabilir.

## Problem Tanımı

N×N boyutundaki bir satranç tahtasına N adet veziri, hiçbiri birbirini tehdit etmeyecek şekilde yerleştirmek. Vezirler aynı satır, sütun veya çaprazda bulunmamalıdır.

## Çözüm Modları

| # | Mod | Açıklama | Karmaşıklık |
|---|-----|----------|-------------|
| 1 | **Brute Force** | Tüm olası yerleşimleri deneyip geçerli olanları kontrol eder | En yavaş |
| 2 | **Optimized 1** | Her satıra bir vezir yerleştirir, üst satırlardaki tehditleri kontrol eder | Orta |
| 3 | **Optimized 2** | Boolean dizileriyle sütun ve çapraz tehditlerini O(1)'de kontrol eder | En hızlı |
| 4 | **Backtracking** | Optimized 1 ile aynı mantık, klasik geri izleme yaklaşımı | Orta |

## Derleme ve Çalıştırma

### Linux / macOS

```bash
gcc -o nqueens asdasd.c -lm
./nqueens
```

### Windows (MinGW / GCC)

```bash
gcc -o nqueens.exe asdasd.c
nqueens.exe
```

## Örnek Kullanım

```
N degerini giriniz: 4

--- Mod Secimleri ---
1. BRUTE_FORCE
2. OPTIMIZED_1
3. OPTIMIZED_2
4. BACKTRACKING
5. TUM MODLARI CALISTIR
Seçiminiz: 4

BACKTRACKING modu cozumleri:
cozum 1:
- Q - -
- - - Q
Q - - -
- - Q -

cozum 2:
- - Q -
Q - - -
- - - Q
- Q - -

BACKTRACKING modu calisma suresi: 0.000012 saniye
toplam cozum sayisi: 2
```

## Notlar

- Maksimum desteklenen tahta boyutu: **25×25** (`MAX_N` sabiti ile ayarlanabilir).
- **Brute Force** modu yüksek N değerlerinde (≥8) çok uzun sürebilir. Performans testleri için Optimized 2 veya Backtracking önerilir.
- Seçenek **5** ile tüm modlar sırayla çalıştırılarak süre karşılaştırması yapılabilir.

## Gereksinimler

- **GCC** derleyicisi (Linux GCC, MinGW-w64 veya MSYS2)
- C99 veya üzeri standart desteği
