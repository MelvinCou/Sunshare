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
    BaseDeDonnees(QString nIPBdD, int nPortBdD, QString cNomUtilisateur, QString cMotDePasse, QString cNomDeBdD,
                  int nNombreJoursRetention, QObject *parent = nullptr);
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
    /**
     * @brief Slot lançant l'acquisition des valeurs moyennes afin de les stocker dans d'autres tables sur le long terme
     */
    void on_CalculerMoyennes();
    /**
     * @brief Slot déclanchant la rétention
     */
    void on_LancerRetention();
private:
    /**
     * @brief Permet d'envoyer une requête INSERT INTO à la base de données
     * @param cTable        Table dans laquelle doit être stockée les indicateurs
     * @param nSoutirage    Index de soutirage
     * @param nInjection    Index d'injection
     * @param nProduction   Index de production
     * @param cDate         Date d'acquisition
     * @param TableAnnuelle     Si les les indicateurs sont envoyés dans la table annuelle ou non
     */
    void EnvoyerRequete(QByteArray cTable, int nSoutirage, int nInjection, int nProduction, QDateTime oDate, bool TableAnnuelle = false);
    /**
     * @brief Permet de collecter la moyenne d'un champ avec la requête SELECT AVG
     * @param cTable    Table du champ
     * @param cChamp    Champ en question
     * @param cDate     Date à partir de laquelle commence la moyenne
     * @return La moyenne
     */
    int EnvoyerRequeteMoy(QByteArray cTable, QByteArray cChamp, QDateTime oDate);

// Attributs
    /**
     * @brief Objet Qt permettant de gérer la connexion à une base de données
     */
    QSqlDatabase oBdD;

    /**
     * @brief Date actuelle
     */
    QDateTime oDate;

    /**
     * @brief Timer déclenchant le calcul de valeur moyenne quotidienne
     */
    QTimer oTimer;
    /**
     * @brief Nombre de jours avant la moyenne hebdomadaire
     */
    int nSemaine;
    /**
     * @brief Nombre de jours avant la moyenne mensuelle
     */
    int nMois;
    /**
     * @brief Nombre de jours avant la moyenne annuelle
     */
    int nAnnee;
    /**
     *  @brief Nombre de jours avant la rétention
     */
    int nJour;
    /**
     * @brief Attribut contenant l'interval entre chaque rétention
     */
    int nJoursRetention;
};

#endif // BASDEDONNEES_H
