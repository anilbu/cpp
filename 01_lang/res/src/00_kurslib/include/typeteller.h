#ifndef TYPETELLER_H_
#define TYPETELLER_H_

template <typename T>
class TypeTeller;
 
template <typename T>
void type_is(T&)
{
  TypeTeller<T> x;    // incomplete oldugu icin tip bilgisi ile hata mesaji verecek.
}

#endif // TYPETELLER_H_