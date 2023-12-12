#include<iostream>
using namespace std;

void gr4ss () {
    cout << "luv meow";
}
class lgl{
public:
    void foo() {
        gr4ss();
    }
};
int main() {
    auto cat = new lgl();
    cat->foo();
    return 0;
}