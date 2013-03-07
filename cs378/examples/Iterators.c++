// -------------
// Iterators.c++
// -------------

#include <algorithm> // lexicographical_compare
#include <cassert>   // assert
#include <cstddef>   // ptrdiff_t, size_t
#include <iostream>  // cout, endl
#include <iterator>  // input_iterator_tag
#include <vector>    // vector

template <typename T>
class my_vector {
    private:
        std::vector<T> _x;

    public:
        class const_iterator;

        class iterator {
            public:
                typedef std::input_iterator_tag iterator_category;
                typedef T                       value_type;
                typedef std::ptrdiff_t          difference_type;
                typedef value_type*             pointer;
                typedef value_type&             reference;

            public:
                friend bool operator == (const iterator& lhs, const iterator& rhs) {
                    return (lhs._p == rhs._p) && (lhs._i == rhs._i);}

                friend bool operator != (const iterator& lhs, const iterator& rhs) {
                    return !(lhs == rhs);}

            private:
                my_vector*  _p;
                std::size_t _i;

            public:
                iterator (my_vector* p, std::size_t i) :
                        _p (p),
                        _i (i)
                    {}

                T& operator * () {
                    return _p->_x[_i];}

                iterator& operator ++ () {
                    ++_i;
                    return *this;}

                const iterator operator ++ (int) {
                    iterator x(*this);
                    ++*this;
                    return x;}

                operator const_iterator () {
                    return const_iterator(_p, _i);}};

        class const_iterator {
            public:
                typedef std::input_iterator_tag iterator_category;
                typedef const T                 value_type;
                typedef std::ptrdiff_t          difference_type;
                typedef value_type*             pointer;
                typedef value_type&             reference;

            public:
                friend bool operator == (const const_iterator& lhs, const const_iterator& rhs) {
                    return (lhs._p == rhs._p) && (lhs._i == rhs._i);}

                friend bool operator != (const const_iterator& lhs, const const_iterator& rhs) {
                    return !(lhs == rhs);}

            private:
                const my_vector*  _p;
                std::size_t       _i;

            public:
                const_iterator (const my_vector* p, std::size_t i) :
                        _p (p),
                        _i (i)
                    {}

                const T& operator * () {
                    return _p->_x[_i];}

                const_iterator& operator ++ () {
                    ++_i;
                    return *this;}

                const const_iterator operator ++ (int) {
                    const_iterator x(*this);
                    ++*this;
                    return x;}};

        iterator begin () {
            return iterator(this, 0);}

        const_iterator begin () const {
            return const_iterator(this, 0);}

        iterator end () {
            return iterator(this, _x.size());}

        const_iterator end () const {
            return const_iterator(this, _x.size());}

        void push_back (T v) {
            _x.push_back(v);}};

template <typename C>
void test () {
    C x;
    x.push_back(2);
    x.push_back(3);
    typename C::iterator       b = x.begin();
    typename C::const_iterator e = x.end();
    assert(*b == 2);
    ++b;
    assert(*b == 3);
    *b = 4;
    assert(*b == 4);
    ++b;
    assert(b == e);
    assert(!(b != e));
    assert(!std::lexicographical_compare(b, b, e, e));}

int main () {
    using namespace std;
    cout << "Iterators.c++" << endl;

    test<    vector<int> >();
    test< my_vector<int> >();

    cout << "Done." << endl;
    return 0;}
