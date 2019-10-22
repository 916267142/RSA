/*@author KN 916267142@qq.com*/
#include <iostream>
#include <fstream>
#include "MathTool.h"
using namespace std;

int RandomSeed = 2;

class Generator
{
public:
    ll p, q, n, eulerN, e, d;
    Math math;
    Generator() //generate the RSA key
    {
        while(RandomSeed--) {
            p = math.randomDigitPrime(15);
            q = math.randomDigitPrime(15);
        }
        n = p * q;
        eulerN = (p - 1) * (q - 1);
        e = 0;
        while(e == 0 || math.gcd(e, eulerN) != 1) {
            e = math.randomDigit(30);
        }
        d = math.modInverse(e, eulerN);
    }
    void check()
    {
        cout << "-----------------------" << endl;
        cout << "RSA Information:" << endl;
        cout << "p:" << p << endl;
        cout << "q:" << q << endl;
        cout << "n:" << n << endl;
        cout << "l:" << eulerN << endl;
        cout << "e:" << e << endl;
        cout << "d:" << d << endl;
        cout << "-----------------------" << endl;
    }
    ll encryption(ll plaintext)
    {
        return math.modpow(plaintext, e, n) % n;
    }
    ll decryption(ll chiper)
    {
        return math.modpow(chiper, d, n);
    }

    //change long long to char
    void longToChar(ll l, char c[], ll& len) {
        if((l / (256 * 256)) != 0) len = 3;
        else if((l / 256) != 0) len = 2;
        else len = 1;
        for(ll i = 1; i <= len; ++i) {
            c[len - i] = l % 256;
            l /= 256;
        }
    }

    //change char to long long
    void charTolong(char c[], ll& l, ll len) {
        l = 0;
        for(ll i = 0; i < len; ++i) {
            l = l * 256 + (ll)c[i];
        }
    }
};


/*
If you want to generate a difference key pairs,
only need to change the "RandomSeed"
*/
int main()
{
    Generator generator;
    char plaintext[3];
    ll chipertext;

    //The encryption process
    ifstream cin1("plainBefore.txt");
    ofstream cout1("chiper.txt");
    int counter;
    int counter2 = 0;   //Input 24bit every time. char=8bit  char[3]=24bit
    for(counter = 1; cin1 >> noskipws >> plaintext[counter - 1];) {
        if(counter == 3) {
            generator.charTolong(plaintext, chipertext, counter);
            chipertext = generator.encryption(chipertext);
            cout1 << chipertext << " ";
            counter = 1;
        } else {
            counter++;
            counter2++;
        }
    }
    if(counter != 1) {   //deal with the last several digit
        generator.charTolong(plaintext, chipertext, counter - 1);
        chipertext = generator.encryption(chipertext);
        cout1 << chipertext << " ";
    }
    cin1.close();
    cout1.close();

    //The decryption process
    ifstream cin2("chiper.txt");
    ofstream cout2("plainAfter.txt");
    while(cin2 >> chipertext) {
        chipertext = generator.decryption(chipertext);
        ll len;
        generator.longToChar(chipertext, plaintext, len);
        for(int i = 0; i < len; ++i) {
            cout2 << plaintext[i];
        }
    }
    cin2.close();
    cout2.close();

    //print process information
    generator.check();
    cout << "File digit number:" << counter2 * 8 << "b" << endl;
    cout << "Public key:" << generator.e << endl;
    cout << "Private key:" << generator.d << endl;
    cout << "-----------------------" << endl;
    return 0;
}
