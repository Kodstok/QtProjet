#include "annonce.h"

Annonce::Annonce(QString _num, QString _code, QString _ville, QString _type, int _piece, double _surfaceT, double _surfaceH, QString _nom, QString _prenom, QString _mail, QString _tel, QString _typeV, double _prix, QString _titre, QString _descr, QString _image1, QString _image2, QString _image3, QString _image4)
{
    num = _num;
    code = _code;
    ville = _ville;
    type = _type;
    piece = _piece;
    surfaceT = _surfaceT;
    surfaceH = _surfaceH;
    nom = _nom;
    prenom = _prenom;
    mail = _mail;
    tel = _tel;
    typeV = _typeV;
    prix = _prix;
    titre = _titre;
    descr = _descr;
    image1 = _image1;
    image2 = _image2;
    image3 = _image3;
    image4 = _image4;
}


Annonce::~Annonce()
{
}
