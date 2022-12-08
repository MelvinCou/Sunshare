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
 *  Fabrication   ApplicationQt.pro
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

BaseDeDonnees::BaseDeDonnees(QString nIPBdD, int nPortBdD, QString cNomUtilisateur, QString cMotDePasse, QString cNomDeBdD,
                             int nNombreJoursRetention, QObject *parent):
    QObject(parent),
    oBdD(QSqlDatabase::addDatabase("QMYSQL")),
    oDate(),

    nSemaine(0),
    nMois(0),
    nAnnee(0),

    nJour(0),
    nJoursRetention(nNombreJoursRetention)
{
    oBdD.setHostName(nIPBdD);
    oBdD.setPort(nPortBdD);

    oBdD.setUserName(cNomUtilisateur);
    oBdD.setPassword(cMotDePasse);

    oBdD.setDatabaseName(cNomDeBdD);

    oTimer.setInterval(1000 * 60 * 60 * 24);// interval d'un jour entre chaque calcul de moyenne

    connect(&oTimer, SIGNAL(timeout() ),
            this,    SLOT(on_CalculerMoyennes() ));
    connect(&oTimer, SIGNAL(timeout() ),
            this,    SLOT(on_LancerRetention() ));


    // le timer est démarré directement
    oTimer.start();

    // affichage du nombre de jours de rétention
    cout << "Retention au bout de " << this->nJoursRetention << " jour" << (this->nJoursRetention>1?"s":"") << "\n";
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


void BaseDeDonnees::on_CalculerMoyennes()
{
    cout << "Calcul des moyennes. " << this->oDate.toString(FormatDate).toStdString() << "\n";
    // variable qui contient la date à partir de laquelle commence la moyenne
    QDateTime oDate;
    // variables qui contiennent les moyennes
    int nSoutirageMoy (0);
    int nInjectionMoy (0);
    int nProductionMoy (0);

    // 1 jour passe : on incrémente les comptes
    this->nSemaine++;
    this->nMois++;
    this->nAnnee++;

    OuvrirBdD();

    /** Fonctionnement global des moyennes :
     *  Par exemple, pour les moyennes quotidiennes, la moyenne est calculée de la veille à aujourd'hui.
     *  La technique utilisée est de décrémenter le jour, sans toucher à l'heure.
     *
     *  Ainsi, pour la moyenne mensuelle, on décrémente le mois, et pour la moyenne annuelle, l'année est décrémentée
     */

//**************************************************************

    cout << "Moyenne journaliere\n";
    oDate = this->oDate.addDays(-1);// On prend la date par rapport à la veille

    cout << "La moyenne sera faite de " << oDate.toString(FormatDate).toStdString() << " a aujourd'hui.\n";

    // récupération de la moyenne de soutirage
    nSoutirageMoy = EnvoyerRequeteMoy("Energies_TempsReel", "energie_soutiree", oDate);
    // récupération de la moyenne d'injection
    nInjectionMoy = EnvoyerRequeteMoy("Energies_TempsReel", "energie_injectee", oDate);
    // récupération de la moyenne de production
    nProductionMoy = EnvoyerRequeteMoy("Energies_TempsReel", "energie_produite", oDate);

    // envoi des valeurs dans la table journalière
    EnvoyerRequete("Energies_Journaliere", nSoutirageMoy, nInjectionMoy, nProductionMoy, this->oDate);

//**************************************************************

    if(this->nSemaine >= 7) // si on atteint 7 jours (1 semaine)
    {
        cout << "Moyenne hebdomadaire\n";
        oDate = this->oDate.addDays(-7);// On soustrait 7 jours (1 semaine)

        cout << "La moyenne sera faite de " << oDate.toString(FormatDate).toStdString() << " a aujourd'hui.\n";

        // récupération de la moyenne de soutirage
        nSoutirageMoy = EnvoyerRequeteMoy("Energies_Journaliere", "energie_soutiree", oDate);
        // récupération de la moyenne d'injection
        nInjectionMoy = EnvoyerRequeteMoy("Energies_Journaliere", "energie_injectee", oDate);
        // récupération de la moyenne de production
        nProductionMoy = EnvoyerRequeteMoy("Energies_Journaliere", "energie_produite", oDate);

        // envoi des valeurs dans la table hebdomadaire
        EnvoyerRequete("Energies_Hebdomadaire", nSoutirageMoy, nInjectionMoy, nProductionMoy, this->oDate);

        // on reset le nombre de jours pour pouvoir faire la nouvelle moyenne de la semaine prochaine
        this->nSemaine = 0;
    }

//**************************************************************

    if(this->nMois >= 30) // si on atteint 30 jours (1 mois)
    {
        cout << "Moyenne mensuelle\n";
        oDate = this->oDate.addMonths(-1);// On soustrait 1 mois
        cout << "La moyenne sera faite de " << oDate.toString(FormatDate).toStdString() << " a aujourd'hui.\n";

        // récupération de la moyenne de soutirage
        nSoutirageMoy = EnvoyerRequeteMoy("Energies_Journaliere", "energie_soutiree", oDate);
        // récupération de la moyenne d'injection
        nInjectionMoy = EnvoyerRequeteMoy("Energies_Journaliere", "energie_injectee", oDate);
        // récupération de la moyenne de production
        nProductionMoy = EnvoyerRequeteMoy("Energies_Journaliere", "energie_produite", oDate);

        // envoi des valeurs dans la table mensuelle
        EnvoyerRequete("Energies_Mensuelle", nSoutirageMoy, nInjectionMoy, nProductionMoy, this->oDate);

        // on reset le nombre de jours pour pouvoir faire la nouvelle moyenne du mois prochain
        this->nMois = 0;
    }

//**************************************************************

    if(this->nAnnee >= 365) // si on atteint 365 jours (1 an)
    {
        cout << "Moyenne annuelle\n";
        oDate = this->oDate.addYears(-1);// On soustrait 1 an

        cout << "La moyenne sera faite de " << oDate.toString(FormatDate).toStdString() << " a aujourd'hui.\n";

        // récupération de la moyenne de soutirage
        nSoutirageMoy = EnvoyerRequeteMoy("Energies_Mensuelle", "energie_soutiree", oDate);
        // récupération de la moyenne d'injection
        nInjectionMoy = EnvoyerRequeteMoy("Energies_Mensuelle", "energie_injectee", oDate);
        // récupération de la moyenne de production
        nProductionMoy = EnvoyerRequeteMoy("Energies_Mensuelle", "energie_produite", oDate);

        // envoi des valeurs dans la table annuelle
        EnvoyerRequete("Energies_Annuelle", nSoutirageMoy, nInjectionMoy, nProductionMoy, this->oDate, true);

        // on reset le nombre de jours pour pouvoir faire la nouvelle moyenne l'année prochaine
        this->nAnnee = 0;
    }

//**************************************************************


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

        OuvrirBdD();

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

    }

}




void BaseDeDonnees::EnvoyerRequete(QByteArray cTable, int nSoutirage, int nInjection, int nProduction, QDateTime oDate, bool TableAnnuelle)
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
    if (TableAnnuelle) { // si la requête est envoyée à la table annuelle
        oRequete.bindValue(3, oDate.toString("yyyy"));// la date envoyée ne contient que l'année
    } else {
        oRequete.bindValue(3, oDate);// sinon elle envoyée dans son format normal
    }

    if(!oRequete.exec() )
    {
        cout << "Erreur lors de l'envoi de la requete : " << oRequete.lastError().text().toStdString() << "\n";
    }
}


int BaseDeDonnees::EnvoyerRequeteMoy(QByteArray cTable, QByteArray cChamp, QDateTime oDate)
{
    int nMoyenne (0);
    QSqlQuery oRequete (this->oBdD);

    // récupération de la moyenne pour une date supérieur à celle donnée : on fait la moyenne de oDate à aujourd'hui
    oRequete.prepare("SELECT AVG(" + cChamp + ") FROM " + cTable + " WHERE  date > ?");
    oRequete.bindValue(0, oDate);

    if(!oRequete.exec() )
    {
        cout << "Erreur lors de l'envoi de la requete : " << oRequete.lastError().text().toStdString() << "\n";
    }
    // boucle pour récupérer le résultat de la requête SQL
    while(oRequete.next())// la requête SQL ne retourne qu'une valeur, la boucle n'est donc exécutée qu'une fois
    {
        nMoyenne = oRequete.value(0).toInt();// la valeur est stockée dans une variable
    }
    cout << "Valeur de " << cChamp.toStdString() << " : " << nMoyenne << "\n";
    return nMoyenne;
}
