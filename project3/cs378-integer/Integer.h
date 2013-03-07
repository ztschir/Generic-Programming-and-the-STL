// --------------------------
// projects/integer/Integer.h
// Copyright (C) 2012
// Glenn P. Downing
// --------------------------

#ifndef Integer_h
#define Integer_h

// --------
// includes
// --------

#include <cassert>   // assert
#include <iostream>  // ostream
#include <stdexcept> // invalid_argument
#include <string>    // string
#include <vector>    // vector
#include <deque>     // deque
#include <sstream>   // ostringstream





// -----------------
// shift_left_digits
// -----------------

/**
 * @param b an iterator to the beginning of an input  sequence (inclusive)
 * @param e an iterator to the end       of an input  sequence (exclusive)
 * @param x an iterator to the beginning of an output sequence (inclusive)
 * @return  an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the shift left of the input sequence into the output sequence
 * (s << n) => x
 */
template <typename II, typename OI>
OI shift_left_digits (II b, II e, int n, OI x) {
    while(b != e){
        *x = *b;
        ++b;
        ++x;   
    }
    for(int i=0; i<n; ++i){
        *x = 0;
        ++x;
    }
    return x;}

// ------------------
// shift_right_digits
// ------------------

/**
 * @param b an iterator to the beginning of an input  sequence (inclusive)
 * @param e an iterator to the end       of an input  sequence (exclusive)
 * @param x an iterator to the beginning of an output sequence (inclusive)
 * @return  an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the shift right of the input sequence into the output sequence
 * (s >> n) => x
 */
template <typename II, typename OI>
OI shift_right_digits (II b, II e, int n, OI x) {
    int len = e-b;
    for(int i = 0; i< len-n; ++i){
        *x = *b;
        ++b;
        ++x;
    }
    return x;}

// -----------
// plus_digits
// -----------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the sum of the two input sequences into the output sequence
 * (s1 + s2) => x
 */
template <typename II1, typename II2, typename OI>
OI plus_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {           
    int len = e1 - b1;
    if((e2-b2)>(e1-b1)) len = e2 - b2;
    OI endx = x+len;
    bool stop = false;
    int carryOver = 0;
    while(!stop){   
                if (b1 != e1 && b2 != e2){
                    //std::cout << "Normal Case" << std::endl;
                    int temp = *(e1-1) + *(e2-1) + carryOver;
                    carryOver = 0;
                    if(temp >= 10){
                        carryOver = 1;
                        temp -= 10;
                    }
                    *(x+len) = temp;
                    --e1;
                    --e2;
                    --len;
                } else if(b1 != e1){
                    //std::cout << "b1 longer Case" << std::endl;
                    int temp = *(e1-1) + carryOver;
                    carryOver = 0;
                    if(temp >= 10){
                        carryOver = 1;
                        temp -= 10;
                    }
                     *(x+len) = temp;
                    --e1;
                    --len;
                } else if(b2 != e2){
                    //std::cout << "b2 longer Case" << std::endl;
                    int temp = *(e2-1) + carryOver;
                    carryOver = 0;
                    if(temp >= 10){
                        carryOver = 1;
                        temp -= 10;
                    }
                     *(x+len) = temp;
                    --e2;
                    --len;         
                } else{
                    //std::cout << "Else Case" << std::endl;
                    if(carryOver != 0){
                        *(x+len) = carryOver;
                        carryOver = 0;
                        ++endx;
                    } else{
                        endx = shift_left_digits (x+1, endx+1, 1, x);
                        --endx;
                    }
                    stop = true;
                }
            }
            return endx;
      }

// ------------
// minus_digits
// ------------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the difference of the two input sequences into the output sequence
 * (s1 - s2) => x
 */
template <typename II1, typename II2, typename OI>
OI minus_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
    int len1 = e1 - b1;
    //b1 is the larger number at the point
    --len1;
    OI endx = x+len1;
    
    bool stop = false;
    int carryOver = 0;
    while(!stop){   
                if (b1 != e1 && b2 != e2){
                    //std::cout << "Normal Case" << std::endl;
                    int temp = *(e1-1) - *(e2-1) + carryOver;
                    carryOver = 0;
                    if(temp < 0){
                        carryOver = -1;
                        temp += 10;
                    }
                    *(x+len1) = temp;
                    --e1;
                    --e2;
                    --len1;
                } else if(b1 != e1){
                    //std::cout << "b1 longer Case" << std::endl;
                    int temp = *(e1-1) + carryOver;
                    carryOver = 0;
                    if(temp < 0){
                        carryOver = -1;
                        temp += 10;
                    }
                     *(x+len1) = temp;
                    --e1;
                    --len1;
                } else{
                    //std::cout << "Else Case" << std::endl;
                    if(carryOver != 0){
                        *(x+len1) = carryOver;
                        carryOver = 0;
                    } else{
                        int counter = 0;
                        OI counterX = x;
                        while(counterX != endx){
                            if(*counterX != 0) break;
                            ++counter;
                            ++counterX;
                        }
                        endx = shift_left_digits (x+counter, endx+1, counter, x);
                        endx -= counter;
                    }
                    stop = true;
                }
            }
            return endx;}

// -----------------
// multiplies_digits
// -----------------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the product of the two input sequences into the output sequence
 * (s1 * s2) => x
 */
 
 
 template <typename II>
void printVector (II b, II e, std::string vectorName){
    std::cout << "Vector " << vectorName << ": ";
    while (b != e){
        std::cout << *b ;
        ++b;
    }
    std::cout << std::endl;
}
 
template <typename II1, typename II2, typename OI>
OI multiplies_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
    using namespace std;
    vector< vector<int> > cache(10);
    for(int i=0; i<10; ++i){
        vector<int> temp = multiply_helper(b1, e1, i);
        cache[i] = temp;
    }
    
   
    vector<int>::reverse_iterator productb = cache[*(e2-1)].rbegin();
    vector<int>::reverse_iterator producte = cache[*(e2-1)].rend();
    int len = (e2-b2);
    vector<int> tempCons((e1-b1) + len + 1);
    
    for(int i=1; i<len; ++i){
        --e2;
        vector<int>::reverse_iterator cb = cache[*(e2-1)].rbegin();
        vector<int>::reverse_iterator ce = cache[*(e2-1)].rend();
        vector<int> temp((e1-b1)+1+i);
        vector<int>::iterator tempe = shift_left_digits (cb, ce, i, temp.begin());      
        producte = plus_digits(productb, producte, temp.begin(), tempe, tempCons.rbegin());
        productb = tempCons.rbegin();
    }

    while(productb != producte){
        *x = *productb;
        ++x;
        ++productb;
    }

    return x;}
    
    
template <typename II>
std::vector<int> multiply_helper(II b1, II e1, int n) {
    using namespace std;
    vector<int> result;
    if(n == 0){
        result.push_back(0);
        return result;
    }
    int carryOver = 0;
    int temp;
    //int len = e1-b1;
    //OI endx = x+len;
    while(b1 != e1){
        temp = (*(e1-1) * n) + carryOver;
        carryOver = 0;
        if(temp >= 10){
            result.push_back(temp%10);
            carryOver = temp / 10;
        } else{
            result.push_back(temp);
        }
        //--len;
        --e1;
    }
    if(carryOver != 0){
        result.push_back(carryOver);
    }
    return result;
}

// --------------
// divides_digits
// --------------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the division of the two input sequences into the output sequence
 * (s1 / s2) => x
 */
template <typename II1, typename II2, typename OI>
OI divides_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
    
    return x;}


using namespace std;

// -------
// Integer
// -------

template < typename T, typename C = std::vector<T> >
class Integer {

    // -----------
    // operator ==
    // -----------

    /**
     * @param lhs an Integer object that you are comparing
     * @param rhs an Integer object that you are comparing
     * @return    a bool value, true if they are equal, false otherwise
     * Verify that two Integer objects are equal
     * output a bool to identify whether they are equal
     */
    friend bool operator == (const Integer& lhs, const Integer& rhs) {
        if(lhs.container.size() != rhs.container.size() ) return false;
        if(lhs.sign != rhs.sign) return false;
        typename C::const_reverse_iterator lp = lhs.container.rbegin();
        typename C::const_reverse_iterator rp = rhs.container.rbegin();
        while(lp != lhs.container.rend()){
            if(*lp != *rp) return false;
            ++lp;
            ++rp;
        }
        return true;}

    // -----------
    // operator !=
    // -----------

    /**
     * @param lhs an Integer object that you are comparing
     * @param rhs an Integer object that you are comparing
     * @return    a bool value, false if they are equal, true otherwise
     * Verify that two Integer objects are not equal
     * output a bool to identify whether they are equal
     */
    friend bool operator != (const Integer& lhs, const Integer& rhs) {
        return !(lhs == rhs);}

    // ----------
    // operator <
    // ----------

    /**
     * @param lhs an Integer object that you are comparing
     * @param rhs an Integer object that you are comparing
     * @return    a bool value, true if rhs is larger than lhs, false otherwise
     * Verify that the rhs is larger than the lhs
     * output a bool to identify whether the above is true
     */
    friend bool operator < (const Integer& lhs, const Integer& rhs) {
        // - < +
        if(lhs.sign == false && rhs.sign == true) return true;
        // + < -
        if(lhs.sign == true && rhs.sign == false) return false;
        
        typename C::const_reverse_iterator lp;
        typename C::const_reverse_iterator rp;
        // + < +
        if(lhs.sign == true && rhs.sign == true){
        	if(lhs.container.size() < rhs.container.size()) return true;
        	if(lhs.container.size() > rhs.container.size()) return false;
        	lp = lhs.container.rbegin();
            rp = rhs.container.rbegin();
        }
        // - < -
        if(lhs.sign == false && rhs.sign == false){
        	if(lhs.container.size() < rhs.container.size()) return false;
        	if(lhs.container.size() > rhs.container.size()) return true;
        	lp = rhs.container.rbegin();
            rp = lhs.container.rbegin();
        }
        
        while(lp != lhs.container.rend()){
            if(*lp < *rp) return true;
            ++lp;
            ++rp;
        }
        return false;}

    // -----------
    // operator <=
    // -----------

    /**
     * @param lhs an const Integer object that you are comparing
     * @param rhs an const Integer object that you are comparing
     * @return    a bool value, true if rhs is larger or equal to lhs, false otherwise
     * Verify that the rhs is larger or equal to lhs
     * output a bool to identify whether the above is true
     */
    friend bool operator <= (const Integer& lhs, const Integer& rhs) {
        return !(rhs < lhs);}

    // ----------
    // operator >
    // ----------

    /**
     * @param lhs an const Integer object that you are comparing
     * @param rhs an const Integer object that you are comparing
     * @return    a bool value, true if lhs is larger than rhs, false otherwise
     * Verify that the lhs is larger than the rhs
     * output a bool to identify whether the above is true
     */
    friend bool operator > (const Integer& lhs, const Integer& rhs) {
        return (rhs < lhs);}

    // -----------
    // operator >=
    // -----------

    /**
     * @param lhs an const Integer object that you are comparing
     * @param rhs an const Integer object that you are comparing
     * @return    a bool value, true if lhs is larger or equal to rhs, false otherwise
     * Verify that the lhs is larger or equal to rhs
     * output a bool to identify whether the above is true
     */
    friend bool operator >= (const Integer& lhs, const Integer& rhs) {
        return !(lhs < rhs);}

    // ----------
    // operator +
    // ----------

    /**
     * @param lhs an Integer object that you are adding
     * @param rhs an const Integer object that you are adding
     * @return    an Integer that sums the rhs and lhs
     * Add the lhs to the rhs
     * output a new Integer with the above properties
     */
    friend Integer operator + (Integer lhs, const Integer& rhs) {
        return lhs += rhs;}

    // ----------
    // operator -
    // ----------

    /**
     * @param lhs an Integer object that you are subtracting
     * @param rhs an const Integer object that you are subtracting
     * @return    an Integer that subtracts the rhs from lhs
     * Subtract the rhs from the lhs
     * output a new Integer with the above properties
     */
    friend Integer operator - (Integer lhs, const Integer& rhs) {
        return lhs -= rhs;}

    // ----------
    // operator *
    // ----------

    /**
     * @param lhs an Integer object that you are multipling
     * @param rhs an const Integer object that you are multipling
     * @return    an Integer that multiplies the rhs and lhs
     * Multiply the rhs and lhs
     * output a new Integer with the above properties
     */
    friend Integer operator * (Integer lhs, const Integer& rhs) {
        return lhs *= rhs;}

    // ----------
    // operator /
    // ----------

    /**
     * @param lhs an Integer object that you are dividing
     * @param rhs an const Integer object that you are dividing
     * @return    an Integer that divides the rhs from lhs
     * Divide the rhs from lhs
     * output a new Integer with the above properties
     * @throws invalid_argument if (rhs == 0)
     */
    friend Integer operator / (Integer lhs, const Integer& rhs) {
        if (rhs == 0)
            throw invalid_argument("Can not divid by 0");
        return lhs /= rhs;}

    // ----------
    // operator %
    // ----------

    /**
     * @param lhs an Integer object that is the moduloee
     * @param rhs an const Integer object that is the modulo of
     * @return    an Integer that modulo the rhs from lhs
     * Modulo the rhs from lhs
     * output a new Integer with the above properties
     * @throws invalid_argument if (rhs <= 0)
     */
    friend Integer operator % (Integer lhs, const Integer& rhs) {
        if (rhs == 0)
            throw invalid_argument("Can not mod by 0");        
        return lhs %= rhs;}

    // -----------
    // operator <<
    // -----------

    /**
     * @param lhs an Integer object that will be shifted
     * @param rhs an int that specifies the number to shit by
     * @return    a new Integer object 
     * shift left digits by rhs of the lhs
     * output a new Integer with the above properties
     */
    friend Integer operator << (Integer lhs, int rhs) {
        return lhs <<= rhs;}

    // -----------
    // operator >>
    // -----------

    /**
     * @param lhs an Integer object that will be shifted
     * @param rhs an int that specifies the number to shit by
     * @return    a new Integer object 
     * shift right digits by rhs of the lhs
     * output a new Integer with the above properties
     */
    friend Integer operator >> (Integer lhs, int rhs) {
        return lhs >>= rhs;}

    // -----------
    // operator <<
    // -----------

    /**
     * @param lhs an ostream object that will be the subject of the output
     * @param rhs an const Integer that specifies the printing object
     * @return    the ostream output reference
     * output the full container of numbers or digits of the rhs
     */
    friend std::ostream& operator << (std::ostream& lhs, const Integer& rhs) {
        typename C::const_reverse_iterator rp = rhs.container.rbegin();
        if(rhs.sign == false)
            lhs << "-";
        while(rp != rhs.container.rend()){
            lhs << *rp;
            ++rp;
        }
        return lhs;}

    // ---
    // pow
    // ---

    /**
     * power
     * does NOT modify the argument
     * @param x an Integer object that will be the subject to the power function
     * @param e an int that specifies the number that will be taking the power of
     * @return    a new Integer object 
     * take the power of the Integer to the e value
     * output a new Integer with the above properties
     * @throws invalid_argument if (x == 0) && (e == 0)
     * @throws invalid_argument if (e < 0)
     */
    friend Integer pow (Integer x, int e) {
        if( x == 0 && e == 0)
            throw invalid_argument("Can not take the power of 0 of 0");
        if( e < 0 )
            throw invalid_argument("Can not take the power to a neg number");
        return x.pow(e);}

    private:
        // ----
        // data
        // ----

        C container;

	    // true = positive value, false otherwise
	    bool sign;

    private:
        // -----
        // valid
        // -----

        bool valid () const {
	        typename C::const_reverse_iterator beginningIt = container.rbegin();
	        //int *p = container.rbegin();
	        while(beginningIt != container.rend()){
	            if(*beginningIt < 0 || *beginningIt > 9) return false;
                ++beginningIt;
            }
	        return true;
	}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * @param value int a starting value to create the Integer Object with
         * constructs a new Integer object
         */
        Integer (int value) {
	        if(value < 0){
		        sign = false;
		        value = -value;
	        }else if(value == 0){
	            sign = true;
	            container.push_back(0);
	        }else
		        sign = true;

            while(value > 0){
                container.push_back(value%10);
                value /= 10;
            }
            assert(valid());}

        /**
         * @param value const std::string& a starting value to create the Integer Object with
         * constructs a new Integer object with the number in the string
         * @throws invalid_argument if value is not a valid representation of an Integer
         */
        explicit Integer (const std::string& value) {
	        int stop;
	        if(value[0] == '-'){
	            sign = false;
	            stop = 1;
	        }else{
	            sign = true;
	            stop = 0;
	        }

            for(int i = value.length()-1; i >= stop; --i){
                if(value[i] < '0' || value[i] > '9') throw std::invalid_argument("Integer::Integer()");
		        container.push_back(value[i] - '0');
            }
            if (!valid())
                throw std::invalid_argument("Integer::Integer()");}
                

        // Default copy, destructor, and copy assignment.
        // Integer (const Integer&);
        // ~Integer ();
        // Integer& operator = (const Integer&);

        // ----------
        // operator -
        // ----------

         /**
          * @return    a new Integer object
          * output a new Integer that is negated copy of the original
          */
        Integer operator - () const {
            Integer result = *this;
            if(result != 0)
                result.sign = !(result.sign);
            return result;}

        // -----------
        // operator ++
        // -----------

         /**
          * @return    a reference to the original Integer object
          * Bumps the value up by one in the form of ++(Object)
          */
        Integer& operator ++ () {
            *this += 1;
            return *this;}

         /**
          * @return    a New Integer object
          * output a new Integer object with an increment of 1 from the original Integer value
          */
        Integer operator ++ (int) {
            Integer x = *this;
            ++(*this);
            return x;}

        // -----------
        // operator --
        // -----------

         /**
          * @return    a reference to the original Integer object
          * Bumps the value down by one in the form of ++(Object)
          */
        Integer& operator -- () {
            *this -= 1;
            return *this;}

         /**
          * @return    a New Integer object
          * output a new Integer object with an decrement of 1
          */
        Integer operator -- (int) {
            Integer x = *this;
            --(*this);
            return x;}

        // -----------
        // operator +=
        // -----------

         /**
          * +=
          * @param rhs an Integer object that will have the value rhs added to it
          * @return    a reference to the original Integer object lhs
          * output a reference to the original lhs Integer
          */
        Integer& operator += (const Integer& rhs) {
            Integer lhs = *this;
            
            C result(lhs.container.size() + rhs.container.size());
            typename C::iterator endPlus;
            
            if(lhs.sign == true && rhs.sign == false)
                endPlus = minus_digits(lhs.container.rbegin(), lhs.container.rend(), rhs.container.rbegin(), rhs.container.rend(), result.begin());
            else if(lhs.sign == false && rhs.sign == true){
                endPlus = minus_digits(lhs.container.rbegin(), lhs.container.rend(), rhs.container.rbegin(), rhs.container.rend(), result.begin());
            }else if(lhs.sign == false && rhs.sign == false){                
                endPlus = plus_digits(lhs.container.rbegin(), lhs.container.rend(), rhs.container.rbegin(), rhs.container.rend(), result.begin());;
                sign = false;
            }else{
                endPlus = plus_digits(lhs.container.rbegin(), lhs.container.rend(), rhs.container.rbegin(), rhs.container.rend(), result.begin());
            }
            
            result.erase(endPlus, result.end());
            container.resize(result.size());
            typename C::reverse_iterator beginCont = container.rbegin();
            typename C::iterator beginResult = result.begin();
            while(beginResult != result.end()){
                *beginCont = *beginResult;
                ++beginResult;
                ++beginCont;
            }
            
            return *this;}

        // -----------
        // operator -=
        // -----------

         /**
          * -=
          * @param rhs an const Integer object that will be what is subtracted from the lhs
          * @return    a reference to the original Integer object lhs
          * output a reference to the original lhs Integer
          */
        Integer& operator -= (const Integer& rhs) {
            if(*this == rhs){
                container.clear();
                container.push_back(0);
                return *this;
            }
            Integer lhs = *this;
            
            C result(lhs.container.size() + rhs.container.size());
            typename C::iterator endMinus;
            
            if(lhs.sign == true && rhs.sign == false)
                endMinus = plus_digits(lhs.container.rbegin(), lhs.container.rend(), rhs.container.rbegin(), rhs.container.rend(), result.begin());
            else if(lhs.sign == false && rhs.sign == true){
                endMinus = plus_digits(lhs.container.rbegin(), lhs.container.rend(), rhs.container.rbegin(), rhs.container.rend(), result.begin());
                
            }else if(lhs.sign == false && rhs.sign == false){                
                if(rhs > lhs){
                    endMinus = minus_digits(lhs.container.rbegin(), lhs.container.rend(), rhs.container.rbegin(), rhs.container.rend(), result.begin());;
                }else{  
                    endMinus = minus_digits(rhs.container.rbegin(), rhs.container.rend(), lhs.container.rbegin(), lhs.container.rend(), result.begin());
                    sign = true;  
                }
            }else{
                if(rhs > lhs){
                    endMinus = minus_digits(rhs.container.rbegin(), rhs.container.rend(), lhs.container.rbegin(), lhs.container.rend(), result.begin());
                    sign = false;
                }else{  
                    endMinus = minus_digits(lhs.container.rbegin(), lhs.container.rend(), rhs.container.rbegin(), rhs.container.rend(), result.begin()); 
                }
                
            }
            
            result.erase(endMinus, result.end());
            container.resize(result.size());
            typename C::reverse_iterator beginCont = container.rbegin();
            typename C::iterator beginResult = result.begin();
            while(beginResult != result.end()){
                *beginCont = *beginResult;
                ++beginResult;
                ++beginCont;
            }
            
            return *this;}

        // -----------
        // operator *=
        // -----------

         /**
          * *=
          * @param rhs an const Integer object that will be what is multiplied from the lhs
          * @return    a reference to the original Integer object lhs
          * output a reference to the original lhs Integer
          */
        Integer& operator *= (const Integer& rhs) {
            
            C originalContainer(container.begin(), container.end());
            const C originalRHSContainer(rhs.container.begin(), rhs.container.end());
            C result(container.size() + rhs.container.size());
            typename C::iterator contEnd = multiplies_digits(originalContainer.rbegin(), originalContainer.rend(), originalRHSContainer.rbegin(), originalRHSContainer.rend(), result.begin());
            result.erase(contEnd, result.end());
            container.resize(result.size());
            typename C::iterator resultb = result.begin();
            typename C::reverse_iterator containerb = container.rbegin();
            while(resultb != result.end()){
                *containerb = *resultb;
                ++resultb;
                ++containerb;
            }
            return *this;}

        // -----------
        // operator /=
        // -----------

         /**
          * /=
          * @param rhs an const Integer object that will be what is divided by the lhs
          * @return    a reference to the original Integer object lhs
          * output a reference to the original lhs Integer
          */
        Integer& operator /= (const Integer& rhs) {
            // <your code>
            if(rhs == 0)
                throw invalid_argument("Can not divid by zero");
            
            return *this;}

        // -----------
        // operator %=
        // -----------

        /**
         * %=
         * @param rhs an const Integer object that will be what is modulo from the lhs
         * @return    a reference to the original Integer object lhs
         * output a reference to the original lhs Integer
         * @throws invalid_argument if (rhs <= 0)
         */
        Integer& operator %= (const Integer& rhs) {
            if(rhs <= 0)
                throw invalid_argument("Right hand side can not be zero");
            // <your code>
            return *this;}

        // ------------
        // operator <<=
        // ------------

         /**
          * <<==
          * @param n an int that will be what lhs will shift left digits to
          * @return    a reference to the original Integer object lhs
          * output a reference to the original lhs Integer shifted left
          */
        Integer& operator <<= (int n) {
            Integer lhs = *this;
            container.resize(lhs.container.size() + n);
            typename C::reverse_iterator endMinus = shift_left_digits(lhs.container.rbegin(), lhs.container.rend(), n, container.rbegin());
            return *this;}

        // ------------
        // operator >>=
        // ------------

         /**
          * >>==
          * @param n an int that will be what lhs will shift right digits to
          * @return    a reference to the original Integer object lhs
          * output a reference to the original lhs Integer shifted right
          */
        Integer& operator >>= (int n) {
            Integer lhs = *this;
            container.resize(lhs.container.size() - n);
            typename C::reverse_iterator endMinus = shift_right_digits(lhs.container.rbegin(), lhs.container.rend(), n, container.rbegin());
            return *this;}

        // ---
        // abs
        // ---

         /**
          * absolute value
          * @return    a reference to the original Integer object lhs
          * output a reference to the original lhs Integer absolute value
          */
        Integer& abs () {
            sign = true;
            return *this;}
            
            
        bool isPowerOfTwo(int i){
            while(i > 2){
                if(i%2 != 0) return false;
                i /= 2;
            }
            return true;
        }    
            
        int processE(int e){
            while(e > 1){
                if(isPowerOfTwo(e)) return e;
                --e;
            }
            if(e == 1) return 1;
            else return -1;
        }
        
        Integer quickExp(int e){
            if(e == 1){
                Integer<T, C> r(1);
                return r;
            }
            if(e > 2){
                *this *= quickExp(e/2);
                return *this;
            } else{
                *this *= *this;
                return *this;
            }
        }
        // ---
        // pow
        // ---



        Integer pow_helper(int e){
            if(e == 1){
                return *this;
            } 
            else if(e == 0){
                Integer<T, C> result(1);
                return result;
            }else{
                int newE = processE(e);
                int nextE = e-newE;               
                Integer<T, C> st = *this;
                Integer<T, C> p = st.pow_helper(nextE);
                Integer<T, C> q = quickExp(newE);
                Integer<T, C> r = q * p;
                return r;
            }
        }

        /**
         * power
         * @param e an int that will be what lhs is to the power of
         * @return    a reference to the original Integer object lhs
         * output a reference to the original lhs Integer to the power of e
         * @throws invalid_argument if (this == 0) && (e == 0)
         * @throws invalid_argument if (e < 0)
         */
        Integer& pow (int e) {
            if(this == 0 && e == 0)
                throw invalid_argument("Can not raise to the power of zero");
            if(e<0)
                throw invalid_argument("Can not raise to the power of a negitive number");
            
            Integer<T, C> result = pow_helper(e);
            
            *this = result;
            
            return *this;

            }};

// ---
// abs
// ---

/**
 * absolute value
 * does NOT modify the argument
 */
template <typename T, typename C>
Integer<T, C> abs (Integer<T, C> x) {
    return x.abs();}

#endif // Integer_h
