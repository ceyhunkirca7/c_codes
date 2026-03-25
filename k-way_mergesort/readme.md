# K-Way Merge Sort

Bu proje, **k-way Merge Sort** algoritmasını C dilinde uygulayan bir konsol uygulamasıdır. Kullanıcının belirlediği `N` elemanlı rastgele bir dizi oluşturulur ve kullanıcının girdiği `k` değerine göre k-yollu birleştirmeli sıralama yapılır. Sıralama süresi 10 tekrar ortalaması ile ölçülür.

## Nasıl Çalışır?

1. Kullanıcıdan sıralanacak eleman sayısı (`N`) istenir.
2. `1` ile `N` arasında benzersiz (unique) rastgele bir dizi oluşturulur (Fisher-Yates Shuffle).
3. Kullanıcıdan `k` değeri istenir (`0` girilirse program sonlanır).
4. Dizi `k` parçaya bölünür, her parça rekürsif olarak sıralanır ve ardından k-yollu birleştirme (merge) yapılır.
5. Sıralama öncesi ve sonrası dizi ekrana yazdırılır.
6. Sıralama süresi (10 tekrarın ortalaması) hesaplanıp yazdırılır.
7. Kullanıcı farklı `k` değerleri ile tekrar deneyebilir.

## Algoritma Detayları

| Bileşen | Açıklama |
|---------|----------|
| **unique_random_array** | 1-N arası sayıları Fisher-Yates algoritmasıyla karıştırarak benzersiz dizi üretir |
| **k_way_merge_sort** | Diziyi `k` parçaya böler, her parçayı rekürsif sıralar, sonra k-yollu birleştirir |
| **zaman_olc** | Sıralama işlemini 10 kez tekrarlayıp ortalama süreyi `clock_gettime` ile ölçer |

## Derleme ve Çalıştırma

### Linux / macOS (GCC)

```bash
gcc -o kway_merge_sort asdasd.c -lrt
./kway_merge_sort
```

### Windows (MinGW / GCC)

```bash
gcc -o kway_merge_sort.exe asdasd.c
kway_merge_sort.exe
```

> **Not:** Windows'ta `clock_gettime` ve `CLOCK_MONOTONIC` desteği için MinGW-w64 veya MSYS2 ortamı gereklidir. Alternatif olarak WSL (Windows Subsystem for Linux) kullanılabilir.

### WSL (Windows Subsystem for Linux)

```bash
gcc -o kway_merge_sort asdasd.c -lrt
./kway_merge_sort
```

## Örnek Kullanım

```
Lutfen siralanacak eleman sayisini (N) girin: 10
Lutfen birlestirme isleminde kullanilacak k degerini girin. Programi sonlandirmak icin 0a basin. 3
Siralama oncesi dizi:
7 3 10 5 1 8 2 6 9 4
Siralama sonrasi dizi:
1 2 3 4 5 6 7 8 9 10
Siralama suresi (k = 3): 0.000002 saniye
```

## Gereksinimler

- **GCC** derleyicisi (MinGW-w64, MSYS2 veya Linux GCC)
- C99 veya üzeri standart desteği
- `clock_gettime` desteği için POSIX uyumlu ortam (`-lrt` flag'i Linux'ta gerekebilir)
