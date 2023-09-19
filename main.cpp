//user-written code
// class Base{
//    public:
    
//    public:
//     virtual void vf() = 0;
//     virtual void nov() = 0;
//   private:
//    int m_x;
// };



// class Derived : public Base {
//   public:
//    void vf() override {
//      std::cout << "B::vf" << std::endl;
//    }
//    virtual void nf() = 0;
// };

#include <iostream>
#include <string>

//written by the compiler

struct TI {
    std::string class_name;
};

struct BaseVtbl {
    TI* type_info;
    void (*vf)();
    void (*nov)();
};

void vf() {
    std::cout << "Base::vf" << std::endl;
}

void vf_D() {
    std::cout << "Derived::vf" << std::endl;
}

void nov() {
    std::cout << "Base::nov" << std::endl;
}

void nf() {
    std::cout << "Derived::nov" << std::endl;
}

struct Base {
    int m_x;
    BaseVtbl* vptr;
};

void ctor(Base* ob) {
    TI* ti = new TI;
    ti->class_name = typeid(*ob).name();;
    ob->vptr->type_info = ti;
    ob->vptr->vf = &vf;
    ob->vptr->nov = &nov;
}

struct DerivedVtbl{
  TI* type_info;
  void (*vf)();
  void (*nov)();
  void (*nf)();
};

struct Derived {
    int m_y;
    DerivedVtbl* vptr;
};

void ctor(Derived* ob) {
    TI* ti = new TI;
    ti->class_name = "Derived";
    ob->vptr->type_info = ti;
    ob->vptr->vf = &vf_D;
    ob->vptr->nov = &nf;
    ob->vptr->nf = &nf;
}

int main() {
     Base baseOb;
     BaseVtbl baseVtbl;
     baseOb.vptr = &baseVtbl;
     ctor(&baseOb);
     baseOb.vptr->vf();

     Derived derivedOb;
     DerivedVtbl derivedVtbl;
     derivedOb.vptr = &derivedVtbl;
     ctor(&derivedOb);
     derivedOb.vptr->vf();

    return 0;
}


