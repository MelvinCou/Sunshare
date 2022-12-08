//------------------------------------------------------------------------------
/** @file         main.cpp
 *
 *  @brief        Code source de la classe gérant la base de données
 *
 *  @author       Me. Courjaud
 *  @author       STS SN-IR, Lycée Nicolas APPERT, ORVAULT (FRANCE)
 *  @since        2020-12-03
 *  @version      1.0
 *  @date         2022-05-22
 *
 *  Fabrication   TestBdD.pro
 *
 *  @todo         Rien
 *
 *  @bug          Aucun
 */
//------------------------------------------------------------------------------
#include "basededonnees.h"

#include <iostream>
using namespace std;

#define FormatDate "yyyy-MM-dd hh:mm:ss" // format de la date utilisé pour l'affichage

BaseDeDonnees::BaseDeDonnees(QString nIPBdD, int nPortBdD, QString cNomUtilisateur, QString cMotDePasse, QString cNomDeBdD, QObject *parent):
    QObject(parent),
    oBdD(QSqlDatabase::addDatabase("QMYSQL"))
{
    oBdD.setHostName(nIPBdD);
    oBdD.setPort(nPortBdD);

    oBdD.setUserName(cNomUtilisateur);
    oBdD.setPassword(cMotDePasse);

    oBdD.setDatabaseName(cNomDeBdD);
}

BaseDeDonnees::~BaseDeDonnees()
{
    FermerBdD();
}

void BaseDeDonnees::OuvrirBdD()
{
    if(oBdD.open())
    {
        cout << "Connexion a " << this->oBdD.hostName().toStdString() << " reussie !\n";
    } else {
        cout << "Erreur lors de la connexion a la BdD : " << oBdD.lastError().text().toStdString() << "\n";
        exit(-1);
    }
}

void BaseDeDonnees::FermerBdD()
{
    cout << "Deconnexion !\n\n";

    oBdD.close();
}


void BaseDeDonnees::on_Envoyerindicateurs(int nSoutirage, int nInjection, int nProduction, QDateTime oDate)
{
    // connexion à la base de données pour envoyer les indicateurs
    OuvrirBdD();

    this->oDate = oDate;
    cout << "Envoi des indicateurs :\nSoutirage\t" << nSoutirage <<
            "\nInjection\t" << nInjection << "\nProduction\t" << nProduction <<
            "\nDate\t\t" << oDate.toString(FormatDate).toStdString() << "\n";

    EnvoyerRequete("Energies_TempsReel", nSoutirage, nInjection, nProduction, oDate);

    // la requête est envoyée, la connexion peut être fermée
    FermerBdD();
}

void BaseDeDonnees::EnvoyerRequete(QByteArray cTable, int nSoutirage, int nInjection, int nProduction, QDateTime oDate)
{
    QSqlQuery oRequete (this->oBdD);
    // envoi des valeurs dans la table
    if(!oRequete.prepare("INSERT INTO " + cTable + "(energie_soutiree, energie_injectee, energie_produite, date) "
                         "VALUES( ?, ?, ?, ?)") )
    {
        cout << "La requete n'a pas pu etre preparee : " << oRequete.lastError().text().toStdString() << "\n";
    }
    oRequete.bindValue(0, nSoutirage);// le premier ? prend la valeur de nSoutirage
    oRequete.bindValue(1, nInjection);
    oRequete.bindValue(2, nProduction);
    oRequete.bindValue(3, oDate);

    if(!oRequete.exec() )
    {
        cout << "Erreur lors de l'envoi de la requete : " << oRequete.lastError().text().toStdString() << "\n";
    } else {
        cout << "Requete envoyee.\n";
    }
}
