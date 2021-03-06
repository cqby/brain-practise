/* 
 * CS:APP Data Lab 
 * 
 * qy
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */

#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y)
{
  return ~(~(~x & y) & ~(x & ~y));
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void)
{
  return ~0 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x)
{
  // if x is max(0x7fff ffff), i is 0x8000 0000
  int i = x + 1;
  // then x + i is 0xffff ffff,
  // flip 0xffff ffff will be 0, now res is 0
  // we can use !res to know if the input is max
  int res = ~(x + i);

  // however, if x is -1(0xffff ffff), res, ~((x + 1) + x) is also 0. we
  // need to exclude such situation.
  // To do so, we cache x+1, which is i.
  // If x is max, i is 0x8000 0000, res(0) + !i = 0
  // if x is -1, i is 0, res(0) + !i = 1
  // so, we add res with !i
  res = res + (!i);
  return !res;
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x)
{
  // construct mask 0xAAAAAAAA
  int mask = (0xAA << 8) + 0xAA;
  mask = (mask << 16) + mask;
  // test mask
  return !((x & mask) ^ mask);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x)
{
  // -1: 1111 1111; 1 0000 0001
  // -2: 1111 1110; 2 0000 0010
  // -3: 1111 1101; 3 0000 0011
  return (~x) + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x)
{
  // if x is 0x3., secondLast4bit will be 0
  int secondLast4bitGood = !(0x3 ^ (x >> 4));
  // last4bit, should less than 1001
  int last4bit = x & 0xf;
  int biggerThan1000 = (last4bit & 0x8) >> 3;
  int lastBitIsOneOrZero = !(last4bit & 0x6);
  return secondLast4bitGood & ((biggerThan1000 & lastBitIsOneOrZero) | !biggerThan1000);
}

int isAsciiDigit2(int x)
{
  int sign = 0x1 << 31;
  int larger = (((x + (~(0x39 | sign))) & sign) >> 31);
  int small = ((x + (~0x30 + 1)) & sign) >> 31;
  return !(small | larger);
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z)
{
  // if x = 0, mask is ffffffff. ow 00000000
  int mask = ~(!x) + 1;
  return (~mask & y) | (mask & z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y)
{
  int leftSign = x >> 31 & 1;
  int rightSign = y >> 31 & 1;

  return (!rightSign & leftSign) | (!(rightSign ^ leftSign) & !((y + ~(x) + 1) >> 31));
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x)
{
  return ((x | (~x + 1)) >> 31) + 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5 => 0x01010
 *            howManyBits(298:256+ 32 + 8 + 2) = 10 => 0x0100101010
 *            howManyBits(-5: -0101 => 1011) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x)
{
  // for positive numbers, the number of digits start
  // from the first 1 from right to left and the rest, plus 1 for leading zero sign
  // for negative numbers, the number of digits start
  // from the first 0 from right to left and the rest.

  // to unify the operation for both positive and negative numbers, we find
  // that negative number's minimal bit is the same as it's complement
  // positive number's minimal bit. So, if x is negative, we change it to its
  // positive complement

  // get x sign with 32 bits
  int b16, b8, b4, b2, b1, b0;
  int sign = x >> 31;
  x = (sign & ~x) | (~sign & x);

  // use Bisection method for 32 bit x
  // check if the first 16 bit is all zero, use !!(x >> 16)
  // if has 1, result is 1, result is at least 16, we use b16 = 1 << 4 = 16 to count it
  // if all 0, result is 0, then b16 = 0 << 4 = 0
  b16 = !!(x >> 16) << 4;
  // if has, we need check the fist 16 bits, else, we need check the last 16 bits
  x = x >> b16;

  // repeat the operation for the first 8 bits on current x
  b8 = !!(x >> 8) << 3;
  x = x >> b8;

  // repeat the operation for the first 4 bits on current x
  b4 = !!(x >> 4) << 2;
  x = x >> b4;

  // repeat the operation for the first 2 bits on current x
  b2 = !!(x >> 2) << 1;
  x = x >> b2;

  // repeat the operation for the first bits on current x
  b1 = !!(x >> 1);
  x = x >> b1;

  // if the last bit is 1 or 0
  b0 = x;

  // sum up with sign digit length 1
  return b16 + b8 + b4 + b2 + b1 + b0 + 1;
}

//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf)
{
  int expMask = 0xff << 23;
  int exp = (uf & expMask) >> 23;
  int sign = uf & (1 << 31);

  if (exp == 0)
    // subnormal, if shift change to normal, equation still work
    return uf << 1 | sign;

  if (exp == 255)
    // infinity or NaN
    return uf;

  exp++;

  if (exp == 255)
    // infinity
    return expMask | sign;

  return (exp << 23) | (uf & ~expMask);
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf)
{
  // (-1)^{sign}×-2^{exp-127}×1.fraction
  //　全为０
  if (!(uf & 0x7fffffff))
    return 0;

  int exp, signMask, frac;

  // 取指数位并消除 bias
  exp = ((uf & 0x7f800000) >> 23) - 127;

  if (exp > 31)
    // int overflow or infinity
    return 0x80000000;

  // exp 全为０(normal), 或者exp小于bias, 使ＥMax = -1 2^-1 = 0.
  // fraction < 2, 结果位于　0 ~ 1, -1 ~ 0, 向下取整, 为０
  if (exp < 0)
    return 0;

  // 1.fraction, 取23位并在最前方补一位
  frac = (uf & 0x007fffff) | 0x00800000;

  // frac 右移 23 位，再左移 exp 位，取 23 和 exp 的差值防止丢失
  if (exp > 23)
    frac <<= (exp - 23);
  else
    frac >>= (23 - exp);

  signMask = uf >> 31;
  if (!((frac >> 31) ^ signMask))
    // frac 和 输入的 sign 一致
    return frac;
  else if (frac >> 31)
    // frac 为负数，输入为正数，说明溢出了
    return 0x80000000;
  else
    // frac 为正数，输入为负数，取反返回
    return ~frac + 1;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x)
{
  int INF = 0xff << 23;
  int exp = x + 127;
  if (exp <= 0)
    return 0;
  if (exp >= 255)
    return INF;
  return exp << 23;
}
