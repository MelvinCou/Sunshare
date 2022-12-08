//------------------------------------------------------------------------------
/** @file         main.cpp
 *
 *  @brief        Classe cerveau
 *
 *  @author       Me. Courjaud
 *  @author       STS SN-IR, Lycée Nicolas APPERT, ORVAULT (FRANCE)
 *  @since        2020-12-03
 *  @version      1.0
 *  @date         2022-05-22
 *
 *  Fabrication   ApplicationQt.pro
 *
 *  @todo         Rien
 *
 *  @bug          Aucun
 */
//------------------------------------------------------------------------------
#include "gestionnaire.h"

#include <iostream>
using namespace std;

Gestionnaire::Gestionnaire(QObject *parent):
    QObject(parent),
    // le fichier de configuration doit être placé dans le même dossier que l'exécutable
    oParametres("Sunshare.ini", QSettings::IniFormat),

    /* Rappel des paramètres du port série :
     * 9600 baud
     * 7 bits de donnée
     * Parité paire
     * 1 bit de stop
     */
    uTeleInfo("ttyUSB0", QSerialPort::Baud9600, QSerialPort::Data7, QSerialPort::EvenParity, QSerialPort::OneStop, this),

    // les paramètres de la base de donnée sont stockés dans le fichier .ini
    BdD(oParametres.value("Connexion/IP", "127.0.0.1").toString(),          //
        oParametres.value("Connexion/Port", 3306).toInt(),                  //
        oParametres.value("Connexion/Utilisateur", "admin").toString(),     // paramètres de connexion à la BdD
        oParametres.value("Connexion/mdp", "admin").toString(),             //
        oParametres.value("Connexion/NomBdD", "SunshareBDD").toString(),    //
        oParametres.value("Delais/Retention", 1).toInt(),// délai de rétention
        this),

    SDM120D(),

    // les attributs prennent les valeurs contenues dans le fichier .ini
    nDelaiAcquisition(oParametres.value("Delais/Acquisition", 60).toInt() )// valeur par défaut : 60 secondes
{
    cout << "Groupe [Connexion]\n";
    cout << "IP de la BdD : " << oParametres.value("Connexion/IP","Non lu").toString().toStdString() << "\n";
    cout << "Port : " << oParametres.value("Connexion/Port","Non lu").toInt() << "\n";
    cout << "Nom d'utilisateur : " << oParametres.value("Connexion/Utilisateur","Non lu").toString().toStdString() << "\n";

    cout << "\nGroupe [Delais]\n";
    cout << "Delai d'acquisition : " << nDelaiAcquisition << "\n\n";

    /* Afin d'éviter une aquisition de données trop importante, elle doit se faire entre 1 minute et 1 heure
     * la limite maximum est fixée à 1 heure pour éviter les valeurs absurdes
     */
/*
    if (nDelaiAcquisition < 60) {
        nDelaiAcquisition = 60;
        cout << "L'acquisition doit se faire entre 1 minute et 1 heure\n";

    }
    if (nDelaiAcquisition > 3600) {
        nDelaiAcquisition = 3600;
        cout << "L'acquisition doit se faire entre 1 minute et 1 heure\n";
    }
*/
    // La rétension doit se faire entre 1 jour et 24 jours
    // 2³¹-1/(1000 * 60 * 60 * 24) ~= 25 : limite de valeur pour un integer en paramètre dans la méthode "setInterval" d'un QTimer (plus bas)
/*
    if (nDelaiRetention < 1) {
        nDelaiRetention = 1;
    }
    if (nDelaiRetention > 24) {
        nDelaiRetention = 24;
    }
*/
    oTimerAcquisition.setInterval(nDelaiAcquisition * 1000);// conversion en secondes

    // signal émis pour démarrer les acquisitions
    connect(&oTimerAcquisition, SIGNAL(timeout() ),
            this,               SLOT(on_DemarrerAcquisition() ) );

    // signal émis lors de la fin des acquisitions
    connect(&uTeleInfo, &Linky::TraitementTermine ,
            &BdD,       &BaseDeDonnees::on_Envoyerindicateurs );

}

Gestionnaire::~Gestionnaire()
{

}

void Gestionnaire::DemarrerLeTimerAcquisition()
{
    // le timer n'est relancé qu'après sont timeout
    if(!oTimerAcquisition.isActive() )
    {
        this->oTimerAcquisition.start();
        cout << "Timer d'acquisition démarré !\n";
    }
}


void Gestionnaire::on_DemarrerAcquisition()
{
    uTeleInfo.LancerAcquisition();
}
