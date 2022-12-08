#include "gestionnaire.h"

#include <iostream>
using namespace std;

Gestionnaire::Gestionnaire():
    oParametres("Sunshare.ini", QSettings::IniFormat),
    // les attributs prennent les valeurs contenues dans le fichier .ini
    nDelaiAcquisition(oParametres.value("Delais/Acquisition").toInt()),
    nDelaiRetention(oParametres.value("Delais/Retention").toInt())
{
    cout << "Test de la lecture dans le fichier Sunshare.ini\nGroupe [Connexion]\n" <<
            "IP de la BdD : " << oParametres.value("Connexion/IP").toString().toStdString() << "\n" <<
            "Port : " << oParametres.value("Connexion/Port").toInt() << "\n" <<
            "Nom d'utilisateur : " << oParametres.value("Connexion/Utilisateur").toString().toStdString() << "\n"<<
            "Mot de passe : " << oParametres.value("Connexion/mdp").toString().toStdString() << "\n"<<
            "Nom de la base de donnees : " << oParametres.value("Connexion/NomBdD").toString().toStdString() << "\n";


    cout << "\nGroupe [Delais]\n";
    cout << "Delai d'acquisition : " << nDelaiAcquisition << "\nDelai de retention : " << nDelaiRetention << "\n";

}

Gestionnaire::~Gestionnaire()
{

}
