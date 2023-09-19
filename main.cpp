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
struct Base;
struct Derived;
void vf(Base*);
void nov(Base*);
void vf(Derived*);
void nov(Derived*);
void nf(Derived*);


struct TI {
    std::string class_name;
};

struct BaseVtbl {
    TI* type_info;
    void (*vf)(Base*);
    void (*nov)(Base*);
};

struct Base {
    int m_x;
    BaseVtbl* vptr;
};

void vf(Base* ob){
  std::cout << ob->vptr->type_info->class_name << "::vf" << std::endl;
}

void nov(Base* ob){
  std::cout << ob->vptr->type_info->class_name << "::nov" << std::endl; 
}

void ctor(Base* ob) {
    TI* ti = new TI;
    ti->class_name = typeid(*ob).name();
    ob->vptr->type_info = ti;
    ob->vptr->vf = &vf;
    ob->vptr->nov = &nov;
}

struct DerivedVtbl{
  TI* type_info;
  void (*vf)(Derived*);
  void (*nov)(Derived*);
  void (*nf)(Derived*);
};



struct Derived {
    int m_y;
    DerivedVtbl* vptr;
};

void vf(Derived* ob) {
  std::cout << ob->vptr->type_info->class_name << "::vf" << std::endl;
}

void nov(Derived* ob) {
 std::cout << ob->vptr->type_info->class_name << "::nov" << std::endl;
}

void nf(Derived* ob) { 
    std::cout << ob->vptr->type_info->class_name << "::nf" << std::endl; \
}

void ctor(Derived* ob) {
    TI* ti = new TI;
    ti->class_name = typeid(*ob).name();
    ob->vptr->type_info = ti;
    ob->vptr->vf = &vf;
    ob->vptr->nov = &nov;
    ob->vptr->nf = &nf;
}

int main() {
     Base baseOb;
     //compile generation
     BaseVtbl baseVtbl;
     baseOb.vptr = &baseVtbl;
     ctor(&baseOb);
     baseOb.vptr->vf(&baseOb);

     Derived derivedOb;
     //compile generation
     DerivedVtbl derivedVtbl;
     derivedOb.vptr = &derivedVtbl;
     ctor(&derivedOb);
     derivedOb.vptr->vf(&derivedOb);

    return 0;
}




