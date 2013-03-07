// -----------
// Allocator.h
// -----------

#include <cassert>  // assert
#include <cstddef>  // ptrdiff_t, size_t
#include <iostream> // cout, endl
#include <new>      // new

/*
namespace std {

void* operator new (size_t, void* p) {
    return p;}

} // std
*/

template <typename T>
struct My_Allocator {
    typedef T                 value_type;

    typedef std::size_t       size_type;
    typedef std::ptrdiff_t    difference_type;

    typedef value_type*       pointer;
    typedef const value_type* const_pointer;

    typedef value_type&       reference;
    typedef const value_type& const_reference;

    friend bool operator == (const My_Allocator&, const My_Allocator&) {
        return true;}

    friend bool operator != (const My_Allocator&, const My_Allocator&) {
        return false;}

    // Default constructor, copy, destructor, and copy assignment
    // Allocator  ();
    // My_Allocator  (const My_Allocator<T>&);
    // ~My_Allocator ();
    // My_Allocator& operator = (const My_Allocator&);

    pointer allocate (size_type n) {
        return static_cast<pointer>(operator new(n * sizeof(value_type)));}

    void construct (pointer p, const_reference v) {
        new (p) value_type(v);}

    void deallocate (pointer p, size_type) {
        assert(p);
        operator delete(p);}

    void destroy (pointer p) {
        p->~value_type();}

    template <typename U>
    struct rebind {
        typedef My_Allocator<U> other;};};
