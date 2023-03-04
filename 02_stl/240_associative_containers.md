## Associative Containers

Binary search tree *(red-black tree)* ile implement edilmislerdir.

* Arama: *$\mathcal{O}(\log{}n)$*
* Ekleme: *$\mathcal{O}(\log{}n)$*
* Silme: *$\mathcal{O}(\log{}n)$*

| Container       | Value Type |     Multikey?      | header  |
| --------------- | :--------: | :----------------: | :-----: |
| `std::set`      |    key     | :heavy_minus_sign: | `<set>` |
| `std::multiset` |    key     | :heavy_plus_sign:  | `<set>` |
| `std::map`      | key-value  | :heavy_minus_sign: | `<map>` |
| `std::multimap` | key-value  | :heavy_plus_sign:  | `<map>` |

> :warning: STL Associative container'lar ogelerini nodelar icerisinden tutmaktadir.

* Iteratorleri **Bidirectional iterator** kategorisindedir.

### **Comparator ve Equivalance**  
Ogeler arasinda karsilastirma *equility* ile degil, bir *comparator* kullanilarak *equivalance* ile yapilir.  
```C++
a == b                   // comparing by equality
!(a < b) && !(b < a)     // comparing by equivalance
```
*Default comparator olarak `less` kullanilir.*

**Custom Comparator Gereksinimleri**  
Custom comparator olarak kullanilacak bir $\oplus$ islemi **UB** durumlarina neden olmamasi icin bazi ozelliklere sahip olmalidir:
1. **Antisymmetric**  
   $a \oplus b = true$ ise $b \oplus a = false$
2. **Irreflexive**  
   $a \oplus a = false$
3. **Transitive**  
   $a \oplus b = true$ ve $b \oplus c = true$ ise $a \oplus c = true$
4. **Transitivity of equivalence**  
   $!(a \oplus b)$ && $!(b \oplus a) = true$ ve $!(b \oplus c)$ && $!(c \oplus b) = true$ ise;  
   $!(a \oplus c)$ && $!(c \oplus a) = true$

[Ornek: Custom comparator](res/src/comparator01.cpp)
[Ornek: Date](res/src/comparator02.cpp)

> :warning: Comparator olarak kullanilacak bir functor sinifin `operator()` fonksiyonu `const` olmalidir.

[Ornek](res/src/set01.cpp)

Bir associative container icinde bulunan bir anahtar degeri, ogenin konumu ile iliskili olmasi nedeniyle dogrudan container icinde degistirilemez. 
```C++
set<string> sset { "ali", "ayse", "tarken", "tekin", "yelda" };
*sset.begin() = "zeynep";     // sentaks hatasi
```
Tur donusum operatorleri ile bu durumu sentaks acisindan gecerli yapilmasi **UB**'a neden olur.

Bir anahtar degerinin degistirilebilmesi icin 2 farkli yol bulunur:
1. Sil/Ekle yontemi
   ```C++
   set<int> iset { 1, 3, 5, 6, 9};
   int old_key = 6, new_key = 7;
   
   if(auto iter = iset.find(old_key); iter != iset.end()){
        iset.erase(iter);
        iset.insert(new_key);
   }
   ```
2. `extract()`[C++17] uye fonskiyonu 
   ```C++
   set<int> iset { 1, 3, 5, 6, 9};
   int old_key = 6, new_key = 7;

   if (auto handle = sset.extract(old_key); handle) {
      // key set'ten cikarildi ancak oge yada ogeyi tutan node destroy edilmedi
       handle.value() = new_key;
       sset.insert(std::move(handle));
   }
   ```
