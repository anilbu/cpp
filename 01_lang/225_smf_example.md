```C++
class Myclass {
public:
  // Derleyicinin urettigi default ctor
  Myclass(){}

  // Derleyicinin urettigi dtor
  ~Myclass(){}

  // Derleyicinin urettigi default copy ctor
  Myclass(const Myclass& other) : ax(other.ax),
                                  bx(other.bx),
                                  cx(other.cx)
  {
  }
  
  // Derleyicinin urettigi default move ctor
  Myclass(Myclass&& other) : ax(std::move(other.ax)),
                             bx(std::move(other.bx)),
                             cx(std::move(other.cx))
  {
  }
  
  // Derleyicinin urettigi default copy assignment
  Myclass& operator=(const Myclass& other)
  {
    ax = other.ax;
    bx = other.bx;
    cx = other.cx;
    return *this;
  }
  
  // Derleyicinin urettigi default move assignment
  Myclass& operator=(Myclass&& other)
  {
    ax = std::move(other.ax);
    bx = std::move(other.bx);
    cx = std::move(other.cx);
    return *this;
  }
  
private:
  A ax;
  B bx;
  C cx;
};
```