#define VER1

namespace nec {
#ifdef VER1
inline
#endif
    namespace version_1 {
        class Myclass {};
    }

#ifdef VER2
inline
#endif
    namespace version_2 
    {
        class Myclass {};
    }
}

int main() {
    nec::Myclass m; // version degistiginde client code degismesin istenmekte
}