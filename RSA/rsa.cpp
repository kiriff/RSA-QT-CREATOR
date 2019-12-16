#include "rsa.h"
#include <math.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

long int p;
long int q;
long int n;
long int t;
long int e;
long int d;

using namespace std;

RSA::RSA()
{
    srand (time(0));
    p = sundaram();
    q = sundaram();
    while (p==q && p > 0 && q > 0) {
        p = sundaram();
        q = sundaram();
    }

    n = p * q;
    t = (p - 1) * (q - 1);
    e = calculateE(t);
    d = calculateD(e, t);
}

long int RSA::sundaram()
{
    int n = rand() % 100 + 10;

    int *a = new int [n], i, j, k;
    memset(a, 0, sizeof(int) * n);
    for(i = 1; 3*i+1 < n; i++)
    {
        for(j = 1; (k = i+j+2*i*j) < n && j <= i; j++)
            a[k] = 1;
    }

    for(i = n-1; i >= 1; i--)
        if(a[i] == 0)
        {
            return (2 * i + 1);
            break;
        }
    delete [] a;
    return -1;
}

long int RSA::greatestCommonDivisor( long int e, long int t )
{
    while ( e > 0 )
    {
        long int myTemp;

        myTemp = e;
        e = t % e;
        t = myTemp;
    }

    return t;
}

long int RSA::calculateE( long int t )
{
    // Выбирается целое число e ( 1 < e < t ) // взаимно простое со значением функции Эйлера (t)

    long int e;

    for ( e = 2; e < t; e++ )
    {
        if (greatestCommonDivisor( e, t ) == 1 )
        {
            return e;
        }
    }

    return -1;
}


long int RSA::calculateD( long int e, long int t)
{
    // Вычисляется число d, мультипликативно обратное к числу e по модулю φ(n), то есть число, удовлетворяющее сравнению:
    //    d ⋅ e ≡ 1 (mod φ(n))

    long int d;
    long int k = 1;

    while ( 1 )
    {
        k = k + t;

        if ( k % e == 0)
        {
            d = (k / e);
            return d;
        }
    }

}


long int RSA::encrypt( long int i, long int e, long int n)
{
    long int current, result;

    current = i;
    result = 1;

    for ( long int j = 0; j < e; j++ )
    {
        result = result * current;
        result = result % n;
    }

    return result;
}

std::string RSA::encrypt(std::string text)
{
    std::string encryptedText = "";

    long int encrypted[text.length()];
    memset(encrypted, 0, sizeof(encrypted));

    for(unsigned long int i = 0; i < text.size(); i++)
    {
        encrypted[i] = encrypt(text[i], e, n);
        encryptedText = encryptedText + std::to_string(encrypted[i]) + " ";
    }

    encryptedText += "\n\n\n{e, n} = {" + std::to_string(e) + ", " + std::to_string(n) + "}";
    encryptedText += "\n\n\n{p, q} = {" + std::to_string(p) + ", " + std::to_string(q) + "}";

    return encryptedText;
}

long int RSA::decrypt(long int i, long int d, long int n)
{
    long int current, result;

    current = i;
    result = 1;

    for ( long int j = 0; j < d; j++ )
    {
        result = result * current;
        result = result % n;
    }

    return result;
}

std::string RSA::decrypt(std::string text)
{
    std::vector<long int> arr;
    std::string delimiter = " ";



    std::istringstream is(text);
        std::string s;
        while (std::getline(is, s, ' '))
        {
            long int lint;
            try {
                lint = std::stol(s);
            } catch (std::invalid_argument) {
                return "error: invalid argument";
            }
            arr.push_back(lint);
        }


    std::string decryptedText = "";

    for(unsigned long int i = 0; i < arr.size(); i++)
    {
        decryptedText = decryptedText + (char)decrypt(arr.at(i), d, n);
    }

    decryptedText += "\n\n\n{d, n} = {" + std::to_string(d) + ", " + std::to_string(n) + "}";
    decryptedText += "\n\n\n{p, q} = {" + std::to_string(p) + ", " + std::to_string(q) + "}";

    return decryptedText;

}
