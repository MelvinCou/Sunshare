#ifndef BASDEDONNEES_H
#define BASDEDONNEES_H

#include <QtSql>

/**
 * @brief La classe BaseDeDonnees permet d'envoyer des requêtes à la base de données
 */
class BaseDeDonnees : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructeur paramétré de la classe BaseDeDonnees
     * @param nIPBdD            Adresse IP de la base de données
     * @param nPortBdD          Numéro de port de
     * @param cNomUtilisateur   Nom d'utilisateur
     * @param cMotDePasse       Mot de passe pour l'utilisateur
     * @param cNomDeBdD         Nom de la base de données
     */
    BaseDeDonnees(QString nIPBdD, int nPortBdD, QString cNomUtilisateur, QString cMotDePasse, QString cNomDeBdD, QObject *parent = nullptr);
    ~BaseDeDonnees();

    /**
     * @brief Permet de se connecter à la base de données
     */
    void OuvrirBdD();
    /**
     * @brief Permet de fermer la connexion à la base de données
     */
    void FermerBdD();

public slots:
    /**
     * @brief Envoie la requête avec les indicateurs, déclenché quand le traitement de la TIC est terminé
     * @param nSoutirage    Index de soutirage
     * @param nInjection    Index d'injection
     * @param nProduction   Index de production
     * @param oDate         Date de collecte des indicateurs
     */
    void on_Envoyerindicateurs(int nSoutirage, int nInjection, int nProduction, QDateTime oDate);
private:
    /**
     * @brief Permet d'envoyer une requête INSERT INTO à la base de données
     * @param cTable        Table dans laquelle doit être stockée les indicateurs
     * @param nSoutirage    Index de soutirage
     * @param nInjection    Index d'injection
     * @param nProduction   Index de production
     * @param cDate         Date d'acquisition
     */
    void EnvoyerRequete(QByteArray cTable, int nSoutirage, int nInjection, int nProduction, QDateTime oDate);
    /**
     * @brief Objet Qt permettant de gérer la connexion à une base de données
     */
    QSqlDatabase oBdD;

    /**
     * @brief Date actuelle
     */
    QDateTime oDate;
};

#endif // BASDEDONNEES_H
