# Function Objects



## Function Wrappers

## Function Invocation

## Partial Function Application
### `std::bind`

## Negators
### `std::not_fn`

## Reference Wrappers
### `std::reference_wrapper` / `ref` / `cref`

## Operator Function Objects
**Arithmetic operations**  
`plus` `minus` `multiplies` `divides` `modulus` `negate`  
**Comparisons**  
`equal_to` `not_equal_to` `greater` `less` `greater_equal` `less_equal`  
**Logical operations**  
`logical_and` `logical_or` `logical_not`  
**Bitwise operations**  
`bit_and` `bit_or` `bit_xor` `bit_not`  

* Transparent function object olmalari nedeniyle template argumani belirtilmese de cikarim yapilabilmektedir.  
  *Bu ozellik CTAD'dan farkli*

[Ornekler](res/src/operator_func_obj01.cpp)