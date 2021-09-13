#ifndef __VOITURE__
#define __VOITURE__


class Voiture{
public:
    Voiture();
    Voiture(Voiture & v);
    ~Voiture();
    int getImat() const;

private:
    int immatriculation;
};

#endif