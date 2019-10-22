/*@author KN 916267142@qq.com*/
#include "MathTool.h"

ll Math::randomDigit(ll num)
{
    ll random = 1ll << (num - 1);
    for(ll i = 0; i <= num - 2; ++i) {
        //srand(time(NULL));
        random += (rand() % 2) << i;
    }
    return random;
}

ll Math::mulmod(ll a, ll b, ll mod)
{
    ll x = 0,y = a % mod;
    while(b > 0) {
        if(b % 2 == 1) {
            x = (x + y) % mod;
        }
        y = (y * 2) % mod;
        b /= 2;
    }
    return x % mod;
}

ll Math::modpow(ll base, ll exponent, ll mod)
{
    ll res = 1;
    while(exponent > 0) {
        if(exponent & 1) res = res * base % mod;
        base = base * base % mod;
        exponent >>= 1;
    }
    return res;
}

bool Math::Miller(ll p,ll iteration)
{
    if(p < 2) {
        return false;
    }
    if(p != 2 && p % 2==0) {
        return false;
    }

    ll s = p - 1;
    while(s % 2 == 0) {
        s /= 2;
    }
    for(ll i = 0; i < iteration; i++) {
        ll a = rand() % (p - 1) + 1, temp = s;
        ll mod = modpow(a, temp, p);
        while(temp != p - 1 && mod != 1 && mod != p - 1) {
            mod = mulmod(mod, mod, p);
            temp *= 2;
        }
        if(mod != p - 1 && temp % 2 == 0) {
            return false;
        }
    }
    return true;
}

ll Math::modInverse(ll a, ll m) {
    ll x, y;
    extgcd(a, m, x, y);
    return (m + x % m) % m;
}

ll Math::extgcd(ll a, ll b, ll& x, ll& y)
{
    ll d = a;
    if(b != 0ll) {
        d = extgcd(b, a % b, y, x);
        y -= (a / b) * x;
    } else {
        x = 1ll;
        y = 0ll;
    }
    return d;
}

ll Math::gcd(ll a, ll b)
{
    if(b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

ll Math::randomDigitPrime(ll num)
{
    ll random = 0;
    while(random == 0 || !this->Miller(random, this->iteration)) {
        random = this->randomDigit(num);
    }
    return random;
}
