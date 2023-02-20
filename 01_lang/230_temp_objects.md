# Temporary Objects
Gecici nesneler, kodun icerisinde bir degisken ismi gorunmese de derleyicinin dilin kurallarina uyarak olusturdugu nesnelerdir. Gecici nesneler bir sinif yada primitive nesne olabilir.

Kaynak kodda dogrudan ismi olmayan ancak uretilen kodda nesnenin hayata getirilmesi durumundaki nesnelere temporary objects denir. 

Bir gecici nesne iki sekilde olusabilir:
1. Implicit olarak derleyici tarafindan olusturulan gecici nesneler
2. Explicit olarak olusturulan gecici nesneler
   ```C++
   Myclass{}
   ```

<!--  -->

* Gecici nesnelerin deger kategorisi `prvalue expr`'dir.
  *Bu nedenle `T&`'e baglanamazlar. Ancak `const T&`'e yada `T&&`'e baglanabilir.*
   <details>
   <summary><b>Ornek</b> (Click to expand)</summary>
   
   ```C++
   Myclass& r = Myclass();           // syntax error: cannot bind lvalue ref to prvalue  expr
   const Myclass& lr = Myclass{};    // legal
   Myclass&& rr = Myclass{1, 3};     // legal
   ```
   </details>
   <!--  -->

* Bir gecici nesnenin hayati, o gecici nesne ifadesinin icinde bulundugu (kapsayan) ifadenin degerlendirilmesi (evaluate edilmesinden) sonra sona erer.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  std::cout << "main basliyor\n";
  Myclass().foo();
  std::cout << "main devam ediyor\n";
  ```
  Output:
  ```
  main basliyor
  Myclass() this = 0x7fffffffd6b7
  Myclass::foo() this = 0x7fffffffd6b7
  ~Myclass this = 0x7fffffffd6b7
  main devam ediyor
  ```
  </details>
  <!--  -->

[Ornek](res/src/temp_obj01.cpp)

## Life extension
Eger bir gecici nesnenin bir referans degiskenine baglandiginda; gecici nesnenin hayati referans degiskenin scope'u boyunca uzatilmasidir.
  ```C++
  std::cout << "[1] main basliyor\n";
  if (1)
  {
      Myclass &&rr = Myclass{3, 5};  // life extension
      const Myclass &r = Myclass{1, 2};  // life extension
      std::cout << "[2] main devam ediyor\n";
      r.foo();
      rr.foo();
  }
  std::cout << "[3] main devam ediyor\n";
  ```
  <details>
  <summary><b>Output</b> (Click to expand)</summary>
  
  ```
  [1] main basliyor
  Myclass(int a, int b) a = 3 b = 5
  [2] main devam ediyor
  Myclass::foo() this = 0x7fffffffd6b5
  ~Myclass this = 0x7fffffffd6b5
  [3] main devam ediyor
  ```
  </details>
  <!--  -->