## SMF'lerin User-defined Kullanimi  
Copy ctor ve copy assignment bolumunde bahsedilen problemlerden dolayi iki adet genel kural bulunmaktadir.

### Rule of Zero
Zorunda olmadikca SMF hicbirini yazma, derleyici kodu uretsin.

> **Not**
> Sinifin SMF'lerinin default hali isinizi bozmuyorsa, derleyicinin yazdigini birakmak daha iyi.


### Rule of Five
Eger sinif tipik olarak bir kaynak kullaniyorsa ve **dtor ile pointer/ref ile yonetilen kaynagi geri veriyorsa**; `dtor` yazilmasi gerekmektedir.

* `dtor`'un yazilmasi durumunda `copy member`larin da yazilmasi **gerekmektedir**.
* `copy member`larin yazilmasi durumunda *verimlilik acisindan* `move member`larinda yazilmasi gerekebilir.

Alternatif olarak sinif:
1. Kopyalamaya ve tasimaya karsi kapatilabilir
2. Kopyalamaya kapatabilir ve tasimaya aciktir
3. Kopyalamaya veya tasimaya karsi aciktir.

> **NOT**  
> `copy assignment` ve `move assignment` fonksiyonlarini yazarken -eger ozel bir idiomatic bir yapi kullanmiyorsaniz- mutlaka **self assignment kontrolu**nu yapin!