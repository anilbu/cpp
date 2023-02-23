## `final class`
Bir sinifin kalitim yolu ile turetilmesinin engellenmesi icin `final` anahtar sozcugu ile bildirimi yapilir.

```C++
class Base {};
class Der final : public Base {};
```
Yukarida `Der` sinifi `final` olarak bildirilmesi nedeniyle taban sinif olarak kullanilamaz.
```C++
class DerDer : public Der{}; // sentaks hatasi
```

> **DIKKAT!**  
> *Kalitim, genel (her yerde) kullanima uygun bir arac degildir.*
> Teknik olarak final olmayan tum siniflardan kalitim kullanilarak sinif  turetilebilmektedir. Ancak her sinif kalitim ile kullanilmaya uygun bicimde tasarlanmadigini goz onune almayi unutmayin. 

## `final overrider`
Bir sanal fonksiyonun, bildirildigi siniftan turetilen siniflarda `override` edilmesi engellemek icin fonksiyon bildiriminde `final` anahtar sozcugu kullanilir.

```C++
class Base {
public:
  virtual void foo();
  virtual void bar() const;
};

class Der : public Base {
public:
    virtual void foo() final override;
    virtual void bar() const override final;
};

class DerDer : public Der{
public:
    virtual void foo() override;   // sentaks hatasi: Cunku Der::func final
};
```

* Bildirimde `final` ile `override` sirasi degisebilir, ancak eger varsa `const` anahtar sozcugunden sonra yazilmalidir.

* Bir sinifin yada fonksiyonun `final` olmasi, derleyicinin devirtualization optimizasyonu uygulamasina yardimci olabilir.

## Devirtualization Optimization
Derleyicinin statik analiz yaparak, compile-time'da hangi sanal fonksiyon cagrisinin yapilacagini tespit edebildigi durumlarda virtual dispatch yapmak yerine optimizasyon yaparak direkt fonksiyon cagrisi yapmasidir.