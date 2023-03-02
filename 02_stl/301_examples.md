
--------------------------------------------------------------------------------

`svec_src` isimlerinden uzunlugu `len` olan ve icinde `c` karakteri gecenleri `svec_dst`'e yazsin.
```C++
vector<string> svec_src;
rfill(svec_src, 10'000, []{ return rname() + ' ' + rfname(); });

vector<string> svec_dst;

cout << "Uzunluk degerini girin: ";
size_t len;
cin >> len;

cout << "karakter girin: ";
char c;
cin >> c;

copy_if(svec_src.begin(), svec_src.end(), back_inserter(svec_dst), 
    [c, len](const string& s) {
        // return s.lenght() == len && s.contains(c);   // [C++20]
        return s.lenght() == len && s.find(c) != string::npos;
    }
);

std::cout << "svec_dst.size() = " << svec_dst.size() << '\n';
```

--------------------------------------------------------------------------------

```C++
vector<string> svec;

rfill(svec, 30, rname);
print(svec);

// uzunlugu 4 olanlar silenecek
// uzunlugu 5 olanlardan bir tane daha eklenecek
// digerlerinde degisiklik yapilamayacak

for (auto iter = svec.begin(); iter < svec.end(); )
{
    if(iter->size() == 4)
    {
        iter = svec.erase(iter);
    }
    else if(iter->size() == 5)
    {
        iter = svec.insert(iter, *iter);    // iter invalidate olmus olabilir
        advance(iter, 2);   // islenen + yeni eklenen
    }
    else {
        ++iter; // atla
    }
}

print(svec);
```

--------------------------------------------------------------------------------

Bir vector'da bulununa tum ogeleri silen ornekler:
```C++
svec.clear();
svec.erase(svec.begin(), svec.end());
svec.resize(0);
svec = {};
svec.assign({});
svec = vector<string>{};
svec.assign(vector<string>{});
```

--------------------------------------------------------------------------------

```C++

```