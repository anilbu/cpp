* Giris
* Kitaplar
* Yararli Baglantilar
* Temel Kavramlar
  * Data Abstraction
  * Undefined Behaviour (UB)
  * Unspecified Behavior
  * Implementation-defined Behavior
  * contextual keyword
* Terminoloji
  * type cast operator ile tur donusumu
  * C'de gecerli ancak C++'da gecerli olmayan temel farkliliklar
  * Tam sayi turleri
  * Gercek sayi turleri
* Sayi Sistemleri
* Name lookup
* Scope
* Expression
* Operatorler
  * sequence point (sequencing) and order of evaluation
* Functions
  * deleted functions
  * `const` anahtar sozcugu
  * typedef bildirimleri
  * `comma operator`
  * Implicit Type Conversion
    * 1. Usual Arithmetic Conversion
    * 2. Assignment/Copy Conversion
    * Derleyici hangi durumlarda implicit donusum yapmak zorundadir?
  * Explicit Type Conversion
    * `static_cast` operatoru
    * `const_cast` operatoru
    * `reinterpret_cast` operatoru
    * `dynamic_cast` operatoru
* Array
  * Array decay
* Pointers
  * Nullptr
  * `&` operatoru
  * `*` operatoru
  * Pointer aritmetigi
  * functions returns an address
  * Pointers ve `const`
  * Lvalue references
    * Lvalue refs ve `const`
  * pointers vs references
  * Rvalue references
  * Reference collapsing
  * `auto` type deduction
    * `auto&` tur cikarim kurallari
    * `auto&&` tur cikarim kurallari
  * `decltype` type deduction
    * identifier icin cikarim kurallari
    * expression icin cikarim kurallari
* Scoped Enum
  * Function overloading kurallari
  * Best Match Kurallari
  * Ozel Durumlar
  * Ornekler
  * Birden fazla parametreli overloadlarin resolution durumlari
    * Viable Function Examples
* One Definition Rule (ODR)
* Inline Extension
* Inline Functions
* Complete/Incomplete Types
* Inline variables [C++17]
  * `constexpr` functions
  * Name Lookup 
  * Access Control and Specifiers
  * Class Members
  * Non-static data members
  * Non-static member function
    * **`this` keyword**
    * **`const` member functions**
    * **`mutable` keyword**
    * **Reference Qualifiers**
  * Static Data Members
  * Static Member Functions
    * **Named ctor idiom**
    * **Mono-state Pattern**
    * **Singleton Pattern**
  * **Pimple idiom**
  * Fast pimple idiom
  * Friend declarations
    * 1. friend to global function
      * **hidden friend**
    * 2. friend to a class member
    * 3. friend to a class
* Constructors and Destructor
  * Default constructor
  * Constructor Initializer List
  * Default Member Initializer
  * Parametreli Constructor
  * Conversion Constructor
    * `explicit` keyword
  * Delegating a Constructor [C++11]
  * Copy Members
    * **Value Semantics**
    * Copy Constructor
    * Copy Assignment
  * Move Members
    * **Move Semantics**
      * **`std::move` fonksiyonu**
    * Move Constructor
    * Move Assignment
    * Dikkat edilmesi gereken onemli noktalar
    * Rule of Zero
    * Rule of Five
  * Life extension
  * Genel Kurallar
  * Mantiksal Kurallar
  * Global Operator overloading vs Member operator overloading
  * `<<` ve `>>` operatorlerinin overload edilmesi
  * Karsilastirma operatorlerinin overload edilmesi
    * `+` ve `-` isaret operatorleri
    * `+`, `-`, `*`, `/`, `+=`, `-=`, `*=`, `/=` operatorleri
    * `++` ve `--` operatorleri
  * Array-like siniflar
  * Index `[]` operator fonksiyonunun overload edilmesi
  * Pointer-like siniflar
  * Icerik `*` ve ok operatoru `->` fonksiyonlarinin overload edilmesi
  * Fonksiyon cagri `()` operator fonksiyonunun overload edilmesi
  * Genel Kurallar
  * binary scope resolution `::` operatoru
  * `using` declaration
  * `using namespace` bildirimi
  * Argument Dependat Lookup (ADL)
  * Unnamed Namespace
  * Nested Namespace
  * Inline namespace
  * Namespace Alias
* Composition
* Inheritance
  * Terminoloji
  * Genel kurallar
  * Name-lookup kurallari
  * Access Control
  * Type casting
    * Upcasting
    * Downcasting
  * Inheritance ve Ctors/Dtor
  * Inheritance ve diger SMF'ler
    * Copy ve Move Constructor
    * Copy ve Move Assignment
  * Sinif tanimi icinde yapilan `using` bildirimi
    * Inherited Constructor [C++11]
* Runtime Polymorphismm
  * Terminoloji
      * polymorphic class
      * abstract/concrete class
      * static binding
      * dynamic binding
      * Static typing ve Dynamic typing
  * Overriding a member function
    * `override` contextual keyword
  * Virtual dispatch uygulanan ve uygulanmayan durumlar
  * Non-Virtual Interface
  * Covariance
  * Virtual Constructor Idiom (Clone Idiom)
  * Virtual Destructor
* Virtual Function Table Pointer (vtable)
  * Sanal bir fonksiyona cagri yapilmasi ve maliyeti
  * `final overrider`
  * Devirtualization Optimization
* private inheritance
  * Private inheritance usacases
    * Containment
    * Empty Base Optimization (EBO)
    * Restricted Polymorphism
* protected inheritance
* Multiple Inheritance
  * Name-lookup kurallari
  * Diamond Formation  
  * Virtual Inheritance
  * Traditional Error Handling
  * Genel Kurallar
    * **uncaught exception**
  * Stack unwinding
  * Rethrowing an exception
  * Exception dispatcher idiom
  * Throwing an exception from a constructor
  * Destructors ve exception handling
  * [deprecated] Dynamic exception specification
  * `noexcept` keyword
    * `noexcept` specifier
    * `noexcept()` operatoru
  * function-try block
  * exception safety
  * Kaynak ve Referanslar
  * `dynamic_cast` operatoru
  * `typeid` operatoru
* Generic Programming - Templates
  * Tanimlar
  * template parameters
    * template parameter categories
  * template arguments
    * template argument deduction  
    * explicit template argument
    * default template arguments
    * CTAD [C++17]
    * abbreviated template syntax [C++20]
  * Partial Template Specialization
* Perfect Forwarding
  * Neden Perfect Forwarding?
  * Template Parameter Pack
  * `sizeof...` operatoru
  * Pack expansion
    * Pack expansion ile parametreler nasil kullanilir
      * Compile-time recursive pack expansion
      * [Virgul operatoru](051_basics2.md#comma-operator) ile parameter pack expansion
      * [if-constexpr](#TODO) kullanilarak
    * Pack expansion ile ilgili bazi idiomlar
  * Templateler ile ilgili Onemli Noktalar
* Lambda Expressions - 1
  * Lambda Capture
    * Stateless/Stateful Lambda
  * Closure type
  * Trailing return type
  * Generalized Lambda Expression / Overload Resolution
  * Kullanimi ve idiomatik ifadeler
    * (IIFE) Immediately Invoked Function Expression
    * Positive Lambda Idiom
* `std::pair`
* `std::tuple`
* String Sinifi
  * Tipik parametrik yapilar
  * std::string nested types
  * std::string constructors
    * Default ctor 
    *  Copy ctor
    * Move ctor
    * cstring ctor
    * data ctor
    * range ctor
    * initializer_list ctor
    * fill ctor
    * substring ctor
  * std::string member functions
    * `string::size` ve `string::length`
    * `string::capacity`
    * `string::empty`
    * `operator[]` ve `at()`
    * `front()` ve `back()`
    * `c_str()` ve `data()`
    * `resize()`
    * `operator=`
    * `assign()`
    * `push_back()`, `operator+=` ve `apend()`
    * `string::npos`
* String (Devam)
    * `reserve()` ve `shrink_to_fit()`
    * `begin()` ve `end()`
    * Ekleme islemleri
    * Arama islemleri
    * `substr`
    * Karsilastirma islemleri
      * operator overloading
      * `compare()`
    * `swap()`
    * `replace()`
    * global `operator+` 
    * Donusum fonksiyonlari
      * `stoX` fonksiyonlari
      * `to_string` fonksiyonu
    * Bazi algoritma ornekleri
* auto trailing return type
* Most vexing parse
* AAA (almost always auto)
* as if rule
* type-punning
* static binding
* dynamic binding
* name hiding
* header only library
* data hiding
* static initialization fiasco
* RAII
* copy & swap idiom
* NVRO
* ABI
* first-class functions
* Allocator kavrami
* Serialize/Deserialize
