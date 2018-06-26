#pragma once
/*-------------------------------------------------------------------------
 * Derived from https://mattmccutchen.net/bigint/index.html
 * From the website under the Legal section: I, Matt McCutchen, the sole author
 * of the original Big Integer Library, waive my copyright to it, placing it
 * in the public domain.  The library comes with absolutely no warranty.
 *------------------------------------------------------------------------*/
#include "basetypes.h"
#include "biguint.h"
#include "bigint.h"

namespace qblocks {

    extern ostream& operator<<(ostream& os, const SFUintBN& x);
    extern ostream& operator<<(ostream& os, const SFIntBN& x);

    extern SFUintBN gcd(SFUintBN a, SFUintBN b);
    extern SFUintBN modinv(const SFIntBN& x, const SFUintBN& n);
    extern SFUintBN modexp(const SFIntBN& base, const SFUintBN& exponent, const SFUintBN& modulus);

}  // namespace qblocks
