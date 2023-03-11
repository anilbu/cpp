## Variable Templates
*Degisken sablonlari*  

Variable template, specialization'i olusturuldugunda bir degisken tanimi ureten bir sablon kategorisidir. [C++14] ile dile eklenmistir. Cogunlukla kullanim alani TMP[^tmp]'dir.

[^tmp]: TMP: Template-meta programming

**Ornek**  
```C++
template <typename T>
constexpr static bool IsPointer_v = std::is_pointer<T>::value;

IsPointer_v<int>        // = false
IsPointer_v<int*>       // = true
```

`pi` degiskeninin `T` turunden tanimi:  
[Ornek](res/src/variable_template01.cpp)
```C++
template <typename T>
constexpr T pi = T(3.141592L);

pi<double>  // = double(3.141592L)
pi<float>   // = float(3.141592L)
```