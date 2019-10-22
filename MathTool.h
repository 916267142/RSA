/*@author KN 916267142@qq.com*/
#ifndef MATH_TOOL_H
#define MATH_TOOL_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;
typedef long long ll;

//This class contain all math tool that RSA can be used.
class Math {
private:
    //The number of Miller iteration
    ll iteration = 30ll;
public:
    //Generates a random number of any specified bit
    ll randomDigit(ll num);
    //Generates a random prime number of any specified bit
    ll randomDigitPrime(ll num);
    ll mulmod(ll a, ll b, ll mod);
    ll modpow(ll base, ll exponent, ll mod);
    //Miller prime test. Judge whether a number is a prime
    bool Miller(ll p,ll iteration);
    //Extend Euclid to get the inverse
    ll modInverse(ll a, ll m);
    //Extend Euclid
    ll extgcd(ll a, ll b, ll& x, ll& y);
    //greatest common divisor
    ll gcd(ll a, ll b);
};

#endif // MATH_TOOL_H
