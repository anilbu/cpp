#ifndef MYCLASS_H_
#define MYCLASS_H_

class Myclass{ 

    ~Myclass();
    
private:
    struct pimpl;
    std::unique_ptr<pimpl> impl;
};


#endif // MYCLASS_H_