//------------------------------------------------------------------------------
/** @file         linky.cpp
 *
 *  @brief        Programme permettant de collecter la TIC et d'en faire le traitement
 *
 *  @author       Me. Courjaud
 *  @author       STS SN-IR, Lycée Nicolas APPERT, ORVAULT (FRANCE)
 *  @since        2020-12-03
 *  @version      1.0
 *  @date         2021-11-09
 *
 *  Fabrication   TestBdD.pro
 *
 *  @todo         Rien
 *
 *  @bug          Aucun
 */
//------------------------------------------------------------------------------
#include "linky.h"
#include "compteursdm.h"

#include <QSerialPortInfo>

#include <iostream>
using namespace std;

#define nDureeAcquisition (3500) // durée d'acquisition de la TIC, 3.5 seconde : permet de collecter 2 cycles
#define bEstHorodate (true)      // pour les étiquettes horodatées
#define FormatDate "yyyy-MM-dd hh:mm:ss" // format de la date utilisé pour l'affichage

Linky::Linky(QString cNomPort, qint32 nDebit, QSerialPort::DataBits NbreBitsDonnees,
             QSerialPort::Parity Parite, QSerialPort::StopBits NbreBitsStop, QObject *parent) :
    QObject(parent),
    oPortSerie(cNomPort),
    nSoutirage(0),
    nInjection(0),
    oDate()
{
    // Test si le port est bien branché
    QSerialPortInfo InfoPort(cNomPort);
    if(InfoPort.isNull())
    {
        cout << "Dongle USB non branche.\n";
        exit(-1);
    }

    /** Le port série est initialisé ici
     *  S'il y a une erreur, celui-ci est inutilisable, c'est pourquoi le programme est quitté si c'est le cas
     */
    if (!this->oPortSerie.setBaudRate(nDebit)) {
        cout << "Le debit est incorrect\n";
        exit(-1);
    }
    if (!this->oPortSerie.setDataBits(NbreBitsDonnees)) {
        cout << "Le nombre de bits de donnee est incorrect\n";
        exit(-1);
    }
    if (!this->oPortSerie.setParity(Parite)) {
        cout << "La parite est incorrecte\n";
        exit(-1);
    }
    if (!this->oPortSerie.setStopBits(NbreBitsStop)) {
        cout << "Nombre de bits de stop incorrect\n";
        exit(-1);
    }

    oTimerAcquisition.setInterval(nDureeAcquisition);

    // signal émis à chaque fois qu'une donnée est lisible : il faut la lire
    connect(&oPortSerie,        &QSerialPort::readyRead,
            this,               &Linky::on_Lire );
    // signal émis en cas d'erreur sur le port série
    connect(&oPortSerie,        &QSerialPort::errorOccurred,
            this,               &Linky::on_Erreur);
    // signal émis lorsque le timer d'acquisition prend fin : l'acquisition est terminée
    connect(&oTimerAcquisition, SIGNAL(timeout() ),
            this,               SLOT(on_TerminerAcquisition() ) );

}

Linky::~Linky()
{
    cout << "\nAu revoir Linky !\n";
    FermerPort();
}

void Linky::OuvrirPort()
{
    // si le port série ne peut pas être ouvert en lecture seule, le programme est quitté
    if (!oPortSerie.open(QIODevice::ReadOnly)) {
        cout << "Erreur lors de l'ouverture du port.\n";
        exit(-1);
    }
}

void Linky::FermerPort()
{
    oPortSerie.close();
}

void Linky::LancerAcquisition()
{
    // ouvre le port série pour acquérir les données
    this->OuvrirPort();

    cout << "Debut de l'acquisition\n";

    // démarre le timer d'acquisition
    oTimerAcquisition.start();
}

void Linky::DecoderTrame()
{
    cout << "Traitement de la TIC.\n";

    if(ExtraireEtiquette("VTIC",2) == 2)
    {
        // extraction des étiquettes pour en extraire les valeurs et les stocker dans l'attribut correspondant
        this->nSoutirage = ExtraireEtiquette("SINSTS", 5);
        this->nInjection = ExtraireEtiquette("SINSTI", 5);
        ExtraireDate();// stock la date dans l'attribut cDate

        // traitement fini : on libère l'espace mémoire utilisé par la chaîne de caractères comportant la trame complète
        this->oTrame.clear();

        // le traitement est terminé : un signal est émis à la classe BaseDeDonnees avec les indicateurs
        emit TraitementTermine(this->nSoutirage, this->nInjection, CompteurSDM::Get_nProduction(), this->oDate);
    } else {
        cout << "Traitement impossible\n";
    }
    cout << "\n";
}


void Linky::on_Lire()
{
    // place le dernier bit lu à la fin du tableau
    oTrame.append(oPortSerie.readAll());

    if (!oTimerAcquisition.isActive())
    {
        oTimerAcquisition.start();
    }
}

void Linky::on_TerminerAcquisition()
{
    // comme l'acquisition est terminée, il faut fermer le port, sinon les ressources de la machine sont utilisées pour rien
    FermerPort();
    // on arrête le timer
    oTimerAcquisition.stop();

    cout << "Fin de l'acquisition\n";

    // affiche un message d'erreur si aucune donnée n'a été lue
    if (oTrame.isEmpty()) {
        cout << "Aucune donnee n'est diponible.\n";
    } else {
//        cout << "Donnees recuperees :\n" << oTrame.toStdString() << "\n\n";
    }


    // après l'acquisition de la TIC, il faut extraire les données de la TIC et les stocker dans les attributs de la classe
    DecoderTrame();
}

void Linky::on_Erreur(QSerialPort::SerialPortError serialPortError)
{
    // affiche une erreur s'il y en a eu une
    if (serialPortError == QSerialPort::ReadError) {
        cout << "Il y a eu une erreur lors de la tentative de lecture.\n";
        exit(-1);
    }
}

int Linky::ExtraireEtiquette(QByteArray cEtiquette, int nDonnee, bool bHorodatage)
{
    int nRetour (0);// variable qui contiendra la valeur de l'étiquette
    int nIndex (0);// numéro de case de l'attribut oTrame (chaîne de caractères)

    // Première étape, se placer au début de l'étiquette qui nous intéresse
    nIndex = this->oTrame.indexOf(cEtiquette, 0);// 0 correspond au premier caractère
    // on passe le nom de l'étiquette + caractère '\t'
    nIndex += cEtiquette.length() + 1;
    // Si l'étiquette est horodatée
    if(bHorodatage)
    {
        nIndex += 13; // Les prochains caractères correspondent à la date, ils ne nous intéressent pas
    }
    // Extraction de la valeur chiffrée
    nRetour = this->oTrame.mid(nIndex, nDonnee).toInt();

    //cout << cEtiquette.toStdString() << " : " << nRetour << "\n";

    return nRetour;
}

void Linky::ExtraireDate()
{
    int nIndex (0);
    QTime Heure;
    QDate Date;

    nIndex = this->oTrame.indexOf("DATE", 0);

    nIndex += 4 + 1 +1; // on zappe le nom de l'étiquette, caractère '\t' et le caractère de saison

    // on récupère l'année, le mois et le jour
    Date.setDate(2000 + this->oTrame.mid(nIndex, 2).toInt(),
                 this->oTrame.mid(nIndex + 2, 2).toInt(), this->oTrame.mid(nIndex + 4, 2).toInt());
    // on récupère l'heure, les minutes et les secondes
    Heure.setHMS(this->oTrame.mid(nIndex + 6, 2).toInt(),
                 this->oTrame.mid(nIndex + 8, 2).toInt(), this->oTrame.mid(nIndex + 10, 2).toInt());

    // on les applique dans l'attribut
    this->oDate.setDate(Date);
    this->oDate.setTime(Heure);

    //cout << "Date : " << this->oDate.toString(FormatDate).toStdString() << "\n";
}
