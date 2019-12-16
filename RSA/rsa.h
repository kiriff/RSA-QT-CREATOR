#ifndef RSA_H
#define RSA_H

#include <string>

class RSA
{
public:
    RSA();
    std::string encrypt(std::string text);
    std::string decrypt(std::string text);

private:
    long int encrypt(long int i, long int e, long int n);
    long int decrypt(long int i, long int e, long int n);
    long int sundaram();
    long int calculateE(long int t);
    long int calculateD(long int e, long int t);
    long int greatestCommonDivisor(long int e, long int t);
};

#endif // RSA_H
