# Type traits
[[bknz: type_traits kutuphanesi - genel calisma mantigi](521_type_traits_details.md)]  

Bir tur hakkinda belirli ozelliklere sahip olup olmadigini compile-time'da bilgi edinilmesini/sinanmasini saglayan *meta fonksiyonlardan[^metafunc]* olusan bir kutuphanedir. Farkli turler icin farkli kodlarin secimini saglanmasi, uyumsuz olarak kullanilan turlerde sentaks hatasi uretilebilmesi gibi olanaklara imkan saglamaktadir. 

[^metafunc]: **Meta fonksiyonlar**: Compile-time'da hesaplanan fonksiyonlar
 
`<type_traits>` baslik dosyasinda tanimlanmistir.  

| Yardimci sinif    | Aciklama                                         |
| ----------------- | ------------------------------------------------ |
| integral_constant | Belirtilen tur ve deger icin compile-time sabiti |
| true_type         | `std::integral_constant<bool, true>`             |
| false_type        | `std::integral_constant<bool, false>`            |

:triangular_flag_on_post: Yazim kolayligi icin standart kutuphanede type traits icin [variable_templates](variable_templates.md)'ler tanimlanmistir.  
* Deger hesaplayan meta fonksiyonlar icin sonu `_v` ile biten, statik veri elemani `::value`'u ifade eden variable template tanimlari bulunmaktadir.  
 Ornegin: `is_class<Myclass>::value` yerine `is_class_v<Myclass>` kullanilabilir.   
* Tur hesaplayan meta fonksiyonlar icin sonu `_t` ile biten, nested type `::type`'i ifade eden variable template tanimlari bulunmaktadir.  
 Ornegin: `typename remove_reference<int&&>::type` yerine `remove_reference_t<int&&>` kullanilabilir.  

<!--  -->

**Tipik kullanim senaryolari**  
1. [static_assert](../01_lang/321_static_assert.md#static_assert)  
2. [tag dispatch](../04_advanced/002_tag_dispatch.md)  
3. [constexpr *(static if)*](../01_lang/171_constexpr_if.md#if-constexpr)  
4. [SFINAE](../04_advanced/003_sfinae.md#sfinae)
5. concepts  

<!--  -->

**Ornekler**  

* [Turler ile ilgili compile-time hesaplari](res/src/type_traits01.cpp)
* [Bir template fonksiyonun sadece pointer turleri icin kullanilmasinin saglanmasi](res/src/type_traits02.cpp)
* [Pointer turler icin ayri, olmayan turler icin ayri implementasyonlarin yapilmasi (tag dispatch metodu)](res/src/type_traits03.cpp)
* [lvalue ref icin ayri rvalue ref icin ayri implementasyon (if-constexpr)](res/src/type_traits04.cpp)
* [is_same ve static_assert](res/src/type_traits05.cpp)  

<!--  -->

<br/>
<br/>
<br/>

## Metaprogramming library[C++11] fonksiyonlari

<details>
<summary><b>Primary type categories</summary>

`is_void` `is_null_pointer` `is_integral` `is_floating_point` `is_array` `is_enum` `is_union` `is_class` `is_function` `is_pointer` `is_lvalue_reference` `is_rvalue_reference` `is_member_object_pointer` `is_member_function_pointer`  
</details>
<!--  -->

<details>
<summary><b>Composite type categories</summary>

`is_fundamental` `is_arithmetic` `is_scalar` `is_object` `is_compound` `is_reference` `is_member_pointer`  
</details>
<!--  -->

<details>
<summary><b>Type properties</summary>

`is_const` `is_volatile` `is_trivial` `is_trivially_copyable` `is_standard_layout` `has_unique_object_representations` `is_empty` `is_polymorphic` `is_abstract` `is_final` `is_aggregate` `is_implicit_lifetime` `is_signed` `is_unsigned` `is_bounded_array` `is_unbounded_array` `is_scoped_enum`  
</details>
<!--  -->

<details>
<summary><b>Supported operations</summary>

`is_constructible` `is_trivially_constructible` `is_nothrow_constructible` `is_default_constructible` `is_trivially_default_constructible` `is_nothrow_default_constructible` `is_copy_constructible` `is_trivially_copy_constructible` `is_nothrow_copy_constructible` `is_move_constructible` `is_trivially_move_constructible` `is_nothrow_move_constructible` `is_assignable` `is_trivially_assignable` `is_nothrow_assignable` `is_copy_assignable` `is_trivially_copy_assignable` `is_nothrow_copy_assignable` `is_move_assignable` `is_trivially_move_assignable` `is_nothrow_move_assignable` `is_destructible` `is_trivially_destructible` `is_nothrow_destructible` `has_virtual_destructor` `is_swappable_with` `is_swappable` `is_nothrow_swappable_with` `is_nothrow_swappable`  
</details>
<!--  -->

<details>
<summary><b>Property queries</summary>

`alignment_of` `rank` `extent`  
</details>
<!--  -->

<details>
<summary><b>Type relationships</summary>

`is_same` `is_base_of` `is_convertible` `is_nothrow_convertible` `is_layout_compatible` `is_pointer_interconvertible_base_of` `is_invocable` `is_invocable_r` `is_nothrow_invocable` `is_nothrow_invocable_r`  
</details>
<!--  -->

<details>
<summary><b>Operations on traits</summary>

`conjunction` `disjunction` `negation` 
</details>
<!--  -->

<details>
<summary><b>Type modifications</summary>

* Const-volatility specifiers  
  `remove_cv` `remove_const` `remove_volatile`  
  `add_cv` `add_const` `add_volatile`  
* References  
  `remove_reference` `add_lvalue_reference` `add_rvalue_reference`  
* Pointers  
  `remove_pointer` `add_pointer`  
* Sign modifiers  
  `make_signed` `make_unsigned`  
* Arrays  
  `remove_extent` `remove_all_extents`  
</details>
<!--  -->

<details>
<summary><b>Miscellaneous transformations</summary>

`decay` `remove_cvref` [`enable_if`](../04_advanced/003_sfinae.md#stdenable_if) `conditional` `common_type` `common_reference` `basic_common_reference` `underlying_type` `void_t` `type_identity`  

> :pushpin: `type_identity`, template tur cikarimi yapilmak istenmeyen kapsamlarda kullanilabilmektedir. 

> :pushpin: `enable_if` genellikle [SFINAE](../04_advanced/003_sfinae.md) ile birlikte kullanilir.

</details>
<!--  -->
