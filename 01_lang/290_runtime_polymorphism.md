# Runtime Polymorphismm

<!-- Ders 21 @ 3:11:48'den itibaren giris yapildi -->

Nesne yonelimli programinin kalitim araci cogu zaman **runtime polymorphism** ile birlikte kullanilmaktadir.

`Base` class'in uye fonksiyonlarini belirli kategorilere ayrilir:
`Base` sinifin oyle bir metodu ki;
1. `derived` siniflara hem bir **interface** hemde bir **implementasyon** sagliyor.
   
   <details>
   <summary><b>Ornek</b> (Click to expand)</summary>
   
   ```C++
   class Base {
    public:
        void func();
   };
   ```
   </details>
   <!--  -->
   
   *Taban sinif turemis siniflara diyor ki; senin de boyle bir metodun var, ve benim sana vermis oldugum kodu kullanmak zorundasin, kendi metodunu uretemezsin.*
   

2. `derived` siniflara hem bir **interface** hem de **default implementasyon** sagliyor.
   
   *virtual functions*
   
   <details>
   <summary><b>Ornek</b> (Click to expand)</summary>
   
   ```C++
   class Base {
   public:
       virtual void func();             // virtual function
   };
   ```
   Turemis sinif `func` fonksiyonunu *isterse* kendisi tekrardan tanimlayabilir:
   ```C++
   class Der : public Base {
   public:
       virtual void func() override;    // override
   };
   ```
   </details>
   <!--  -->
   
   
   *Taban sinif turemis siniflara diyor ki; senin de boyle bir metodun var, ama ben sana default bir kod veriyorum. Istersen bu kodu kullanabilir veya kendi kodunu (override) uretebilirsin.*
    
3. `derived` siniflara **sadece interface** saglar.

   *pure virtual function*
   
   <details>
   <summary><b>Ornek</b> (Click to expand)</summary>
   
   ```C++
   class Base {
   public:
       virtual void func() = 0;         // pure virtual function
   };
   
   class Der : public Base {
   public:
       virtual void func() override;    // override
   };
   ```
   </details>
   <!--  -->
   
   *Taban sinif turemis siniflara diyor ki; senin de boyle bir metodun var, ancak sana herhangi bir implementasyon vermiyorum ve bunu sen saglamak zorundasin.*

## Terminoloji

#### polymorphic class
En az bir tane *virtual function*a sahip siniflardir.

#### abstract/concrete class
En az bir tane *pure virtual function*'a sahip siniflara *abstract class* denir. Abstract olmayan siniflara ise *concrete class* denir. Abstract class'lardan dogrudan bir nesne uretilemez.

#### static binding
*(early binding)*
Bir fonksiyon cagrisinin hangi implementasyonun runtime'da calisacagi compile-time'da biliniyor ise; buna **static binding/early binding** denir. Runtime ek maliyeti yoktur.

#### dynamic binding
*(late binding)*
Bir fonksiyon cagrisinin hangi implementasyonun runtime'da calisacagini runtime'da calisan kodun durumuna gore degisebiliyor ise; buna **dynamic binding/late binding** denir. Runtime ek maliyeti bulunur.


#### Static typing ve Dynamic typing

Eger bir verinin turu, compile-time'da *derleyicinin koda bakmasi ile* anlasilabiliyor ise, bu tip diller **static typing** bir dildir. Ancak turler runtime'da anlasilabiliyor ise **dynamic typing** dildir. 

C++ dili static typing bir dildir. Ancak belirli bir olcude dynamic typing'i de desteklemektedir. C++'da, bir sinif icin polymorphic davranis soz konusu degil ise dynamic typing soz konusu degildir.

* Access control static tur ile ilgili bir kavramdir.  
  *Access control'un assembly ile ilgili hicbir karsiligi yok.*
  ```C++
  class Base {
  public:
      virtual void vfunc();
  };
  
  class Der : public Base {
  private:
      void vfunc() override;
  };
  ```
  `baseref` ifadesinin static turu `Base&`'dir, dolayisi ile `Base` sinifininin access kontrol tanimlari gecerli olacaktir.
  ```C++
  Der der;
  Base& baseref = der;
  baseref.vfunc();  // legal: static-type = Base, Access control statik tur ile ilgilenir.
  der.vfunc();      // illegal: static-typing, access-control'e takilir
  ```

* Default arguman statik tur ile ilgili bir kavramdir. Isim arama kurallari geregi hangi fonksiyon bulunmus ise orada tanimli olan default arguman kullanilir.  
  *Bu durumun virtual dispatch ile ilgisi yoktur. Bu nedenle taban sinifin sanal fonksiyonunun default argumaninin degistirilmesi onerilmez.*
  ```C++
  class Base {
  public:
      virtual void vfunc(int x = 10) {
          std::cout << "Base::vfunc() x = " << x << '\n'
      }
  };
  
  class Der : public Base {
  public:
      void vfunc(int x = 20) override {
          std::cout << "Der::vfunc() x = " << x << '\n'
      }
  };
  ```
  ```C++
  Der der;
  Base& baseref = der;
  baseref.vfunc();    // Der::vfunc cagrilir ancak 10 yazar.
                      // Isim arama Base icinde yapilir
                      // virt.disp. ile Der::vfunc cagrilir.
  
  der.vfunc();        // Der::vfunc cagrilir ancak 20 yazar.
                      // Isim arama Der icinde yapilir
                      // virt disp uygulanmaz.
                      
  der.Base::vfunc();  // Base::vfunc cagrilir ancak 10 yazar.
                      // Isim arama Base icinde yapilir 
                      // Nitelenmis isim olmasindan dolayi virt disp uygulanmaz.
  ```