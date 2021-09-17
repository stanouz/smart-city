#ifndef ARGUMENT_H_INCLUDED
#define ARGUMENT_H_INCLUDED

class Argument{
private:
    float age;
    float handicap;
    float tmpStationnement;
    float fidelite;

public:
    Argument();
    ~Argument();
    float calculTaux();
};

#endif // ARGUMENT_H_INCLUDED
