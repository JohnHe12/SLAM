#include<iostream>

// const end of the function 
// explain under the link 
// https://stackoverflow.com/questions/3141087/what-is-meant-with-const-at-end-of-function-declaration

class A
{
public:

    A(){};

    A(int p1, int p2): a(p1), b(p2){};

    void foo(int arg) const;
    
    void foo2(int arg) const;

public:
    int a;
    int b;
};

void A::foo(int arg) const
{
    //this->a = 3;
};

void A::foo2(int arg) const
{


};

int main(int argc, char** argv)
{
    int a = 1;

    int b = 2;

    double c = 3;

    int d = 3;

    int * p1 = &a; // pointer to int 

    *p1 = 5;

    std::cout << "a: " << a << std::endl;

    int const * p2 = &a; // pointer to const int

    a = 3;

    //*p2 = 4; is not allowed

    std::cout << *p2 << std::endl;

    p2 = &b;

    int * const p3 = &a; // const pointer to int

    // p3 = &b; is not allowed

    int const * const p4 = &d; // const pointer to const int

    const int * p5 = &d; // const can be put in the both side 
                        // is equal to int const * 


    const int e = 7;

    // e = 8; is not allowed
    return 0;
}