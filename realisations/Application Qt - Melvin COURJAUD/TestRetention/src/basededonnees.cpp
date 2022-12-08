//------------------------------------------------------------------------------
/** @file         basededonnees.cpp
 *
 *  @brief        Code source de la classe permettant d'envoyer
 *  des requêtes SQLs à la base de données
 *
 *  @author       Me. Courjaud
 *  @author       STS SN-IR, Lycée Nicolas APPERT, ORVAULT (FRANCE)
 *  @since        2020-12-03
 *  @version      1.0
 *  @date         2022-05-22
 *
 *  Fabrication   TestRetention.pro
 *
 *  @todo         Rien
 *
 *  @bug          Aucun
 */
//------------------------------------------------------------------------------
#include "basededonnees.h"

#include <iostream>
using namespace std;

#include <QCoreApplication>

#define FormatDate "yyyy-MM-dd hh:mm:ss" // format de la date utilisé pour l'affichage

BaseDeDonnees::BaseDeDonnees(QString nIPBdD, int nPortBdD, QString cNomUtilisateur, QString cMotDePasse, QString cNomDeBdD,
                             int nNombreJoursRetention, QObject *parent):
    QObject(parent),
    oBdD(QSqlDatabase::addDatabase("QMYSQL")),
    oDate(),

    nJour(0),
    nJoursRetention(nNombreJoursRetention)
{
    // Date de test
    oDate.setDate(QDate(2022, 3, 23)); // Date : 23/03/2022
    oDate.setTime(QTime(11, 55, 00));  // Heure : 11:55:00

    oBdD.setHostName(nIPBdD);
    oBdD.setPort(nPortBdD);

    oBdD.setUserName(cNomUtilisateur);
    oBdD.setPassword(cMotDePasse);

    oBdD.setDatabaseName(cNomDeBdD);


    oTimer.setInterval(100);// interval, ici comme c'est un test, il est relativement court

    connect(&oTimer, SIGNAL(timeout() ),
            this,    SLOT(on_LancerRetention() ));

    // le timer est démarré directement
    oTimer.start();

    // affichage du nombre de jours de rétention
    cout << "Retention au bout de " << this->nJoursRetention << " jour" << (this->nJoursRetention>1?"s":"") << "\n";
}

BaseDeDonnees::~BaseDeDonnees()
{

}

void BaseDeDonnees::ConnexionBdD()
{
    if(oBdD.open())
    {
        cout << "Connexiooon a " << this->oBdD.hostName().toStdString() << " reussie !\n";
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

void BaseDeDonnees::on_Envoyerindicateurs(int nSoutirage, int nInjection, QDateTime oDate)
{
    ConnexionBdD();

    this->oDate = oDate;
    cout << "Envoi de requete\n";

    EnvoyerRequete("Energies_TempsReel", nSoutirage, nInjection, 0, oDate);

    FermerBdD();
}

void BaseDeDonnees::on_LancerRetention()
{
    QDateTime oDate;

    this->nJour++;

    // rétention : suppression des anciennes données
    if(this->nJour == this->nJoursRetention) // si on atteint le nombre de jours pour lancer la rétention
    {
        cout << "Debut de la retention\n";
        oDate = this->oDate.addDays(-this->nJoursRetention); // on décrémente le nombre

        cout << "Les donnees anterieures a " << oDate.toString(FormatDate).toStdString() <<  " seront supprimees.\n";

        ConnexionBdD();

        QSqlQuery oRequete (this->oBdD);// objet permettant d'envoyer des requêtes SQL
        if(!oRequete.prepare("DELETE FROM Energies WHERE date < ?") )// on détruit les lignes comportant les dates antérieurs
        {
            cout << "La requete n'a pas pu etre preparee : " << oRequete.lastError().text().toStdString() << "\n";// s'il y a un problème (syntaxe)
        } else {
            cout << "Requete envoyee.\n\n";
        }
        oRequete.bindValue(0, oDate);

        if(!oRequete.exec() )
        {
            cout << "Erreur lors de l'envoi de la requete : " << oRequete.lastError().text().toStdString() << "\n";
        }

        FermerBdD();

        QCoreApplication::quit();
    }

}

void BaseDeDonnees::EnvoyerRequete(QByteArray cTable, int nSoutirage, int nInjection, int nProduction, QDateTime oDate)
{
    QSqlQuery oRequete (this->oBdD);
    // envoi des valeurs dans la table
    if(!oRequete.prepare("INSERT INTO " + cTable + "(energie_soutiree, energie_injectee, energie_produite, date) "
                         "VALUES( ?, ?, ?, ?)") )
    {
        cout << "La requete n'a pas pu etre preparee : " << oRequete.lastError().text().toStdString() << "\n";
    } else {
        cout << "Requete envoyee.\n\n";
    }
    oRequete.bindValue(0, nSoutirage);// le premier ? prend la valeur nSoutirage
    oRequete.bindValue(1, nInjection);
    oRequete.bindValue(2, nProduction);
    oRequete.bindValue(3, oDate);

    if(!oRequete.exec() )
    {
        cout << "Erreur lors de l'envoi de la requete : " << oRequete.lastError().text().toStdString() << "\n";
    }
}

int BaseDeDonnees::EnvoyerRequeteMoy(QByteArray cTable, QByteArray cChamp, QDateTime oDate)
{
    int nMoyenne (0);
    QSqlQuery oRequete (this->oBdD);

    // récupération de la moyenne pour une date supérieur à celle donnée : on fait la moyenne de cDate à aujourd'hui
    oRequete.prepare("SELECT AVG(" + cChamp + ") FROM " + cTable + " WHERE  date > ?");
    oRequete.bindValue(0, oDate);
    if(!oRequete.exec() )
    {
        cout << "Erreur lors de l'envoi de la requete : " << oRequete.lastError().text().toStdString() << "\n";
    }
    while(oRequete.next())
    {
        nMoyenne = oRequete.value(0).toInt();
    }
    cout << "Valeur de " << cChamp.toStdString() << " : " << nMoyenne << "\n";
    return nMoyenne;
}
