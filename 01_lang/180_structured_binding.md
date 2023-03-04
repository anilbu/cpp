# Structured Binding [C++17]
*Yapisal baglama*

Bir [aggregate type](050_basics.md#aggregate-initialization)'in bilesenlerini farkli degiskenler ile iliskilendirilebilmesini saglayan bir aractir.

* Tum ogelerin bind edilmesi gerekiyor, ilk n tane olmaz.
* Dekleratorler ile birlikte kullanilabilir.

**Ornekler**  

* ```C++
  int a[3] = {1, 3, 5};
  auto [x, y, z] = a;
  auto &[rx, ry, rz] = a;
  ```

* ```C++
  struct Data
  {
      int x, y, z;
  };
  Data foo();
     
  Data mdata{10, 56, 78};
  auto [a, b, c] = mdata;
  auto [day,  mon, year] = foo();
  ```

* ```C++
  std::tuple<int, double, float, std::string> foo() {
      return {12, 4.5, 1.2f, "necati" };
  }
  
  // age = int, temp = double, value = float, name = std::string turunden
  auto [age, temp, value, name] = foo();
  ```

* ```C++
  auto &[age, temp, value, name] = foo();
  const auto &[age, temp, value, name] = foo();
  ```

* ```C++
  vector<pair<string, string>> vec;
  rfill(vec, 100, []{ return pair{rname(), rtown()}; });
  for(const auto& [name, town] : vec) {
    std::cout << name << " -> " << town << '\n';
  }
  ```