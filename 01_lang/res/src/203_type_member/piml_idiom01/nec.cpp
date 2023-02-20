#include "nec.h"
#include <iostream>

// Nec::pimpl bagimliliklari 
//  baslik dosyasinda degil, bir kaynak dosyasinda eklenmistir.
#include <string>
#include "date.h"
#include "cint.h"

// once pimple definition yapilmasi gerekiyor
struct Nec::pimpl
{
    void nbar()
    {
        std::cout << "Nec::nbar()\n";
        mdate.set(1, 4, 1987);
        ++mc;
        std::cout << mc;
        mstr += "can";
    }

    Date mdate;
    Cint mc;
    std::string mstr;
};

Nec::Nec(): mp{ new pimpl } {}

Nec::~Nec()
{
    if (mp) {
        delete mp;
    }
}

void Nec::nbaz() {
    std::cout << "Nec::nbaz()\n";
}

void Nec::nfoo()
{
    std::cout << "Nec::nfoo()\n";
    
    // Alternatif 1: 
    // veri elemanlarina mp pointeri uzerinden erisilmesi
    mp->mdate.set(1, 4, 1987);
    mp->mc++;
    std::cout << mp->mc << '\n';
    mp->mstr += "can";
}

void Nec::nbar() {
    // Alternatif 2:
    // pimpl interface'ine ayni imzali fonksiyon 
    // eklenerek cagriyi tekrarlarmak cagrilmasi
    mp->nbar();
}

