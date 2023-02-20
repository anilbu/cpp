// traditional impl.
// modern versiyonda smart pointer kullanilacak.

#ifndef NEC_H_
#define NEC_H_

class Nec { 
public:
    Nec();
    ~Nec();
    void nfoo();
    void nbar();
    void nbaz();
private:
    struct pimpl;  // nested incomplete type bildirimi
    pimpl* mp;     // Nec sinifi degismedikce bagimliliklarinin degismesine gerek yok.
};

#endif // NEC_H_