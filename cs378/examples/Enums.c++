// ---------
// Enums.c++
// ---------

#include <cassert>  // assert
#include <iostream> // cout, endl

namespace Color1 {
    enum Color {
        red,
        green,
        blue,
        yellow = blue,
        purple};}

namespace Color2 {
    enum Color {
        red,
        green,
        blue,
        yellow = blue,
        purple};}

void f (Color1::Color c) {
    assert(c == Color1::blue);}

int main () {
    using namespace std;
    cout << "Enums.c++" << endl;

    assert(Color1::red   == Color1::red);
    assert(Color1::green != Color1::blue);
    assert(Color1::red   <  Color1::blue);

    assert(Color1::red == Color2::red); // warning: comparison between 'enum Color1::Color' and 'enum Color2::Color'

    assert(Color1::red    == 0);
    assert(Color1::yellow == 2);
    assert(Color1::purple == 3);

    {
    Color1::Color x = Color1::red;
    Color1::Color y = Color1::green;
    Color1::Color z = Color1::blue;
    switch (x) {
        case Color1::red:
        break;

        case Color1::green:
        break;

        default:
        break;}
    }

    {
    int i = Color1::blue;
    assert(i == 2);
//  Color1::Color t = 2;                             // error: invalid conversion from 'int' to 'Color1::Color'
    Color1::Color t = static_cast<Color1::Color>(2);
    assert(t == 2);
    }

    f(Color1::blue);
//  f(2);                             // error: invalid conversion from 'int' to 'Color1::Color'
    f(static_cast<Color1::Color>(2));

    cout << "Done." << endl;
    return 0;}
