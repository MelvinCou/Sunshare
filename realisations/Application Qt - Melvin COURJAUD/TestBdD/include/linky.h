#ifndef LINKY_H
#define LINKY_H

#include <QSerialPort>
#include <QTimer>
#include <QDateTime>

/**
 * @brief La classe Linky permet de collecter la TIC et d'en faire le traitement
 */

class Linky : public QObject
{
    Q_OBJECT
signals:
    /**
     * @brief Signal émis à la fin du traitement, il transmet les indicateurs à la classe BaseDeDonnees
     * @param nSoutirage    Index de soutirage
     * @param nInjection    Index d'injection
     * @param nProduction   Index de production
     * @param oDate         Date de collecte des indicateurs
     */
    void TraitementTermine(int nSoutirage, int nInjection, int nProduction, QDateTime oDate);

public:
    /**
     * @brief Constructeur paramétré de la classe Linky
     * @param InfosPortSerie    Classe fournissant les informations sur le port série
     * @param nDebit            Débit en baud du port série (1200, 9600...)
     * @param NbreBitsDonnees   Nombre de bits de données (7 ou 8)
     * @param Parite            Périté du port série (paire, impaire)
     * @param NbreBitsStop      Nombre de bits de stop (1 ou 2)
     */
    explicit Linky(QString cNomPort, qint32 nDebit, QSerialPort::DataBits NbreBitsDonnees,
                   QSerialPort::Parity Parite, QSerialPort::StopBits NbreBitsStop, QObject *parent = nullptr);
    /**
     * @brief Destructeur de la classe Linky.
     * Ferme le port série au cas où il ne l'aurait pas été
     */
    ~Linky();

// Méthodes métier
    /**
     * @brief Ouvre le port série en lecture seule
     */
    void OuvrirPort();
    /**
     * @brief Ferme le port série
     */
    void FermerPort();

    /**
     * @brief Lance l'Acquisition de la trame, qui sera stockée dans l'attribut oTrame
     */
    void LancerAcquisition();

    /**
     * @brief Lance le décodage de la trame, avec la fonction ExtraireEtiquette
     */
    void DecoderTrame();

private slots:
    /**
     * @brief Slot déclenché à chaque fois qu'une donnée est lisible sur le port série
     */
    void on_Lire();
    /**
     * @brief Slot déclenché à la fin de l'acquisition (timeout de pTimerAcquisition)
     */
    void on_TerminerAcquisition();
    /**
     * @brief Slot déclenché en cas d'erreur sur le port (exemple : oubli d'exécution en "sudo")
     * @param error Erreur
     */
    void on_Erreur(QSerialPort::SerialPortError error);

private:
    /**
     * @brief Permet d'extraire la valeur d'un index à partir de son étiquette correspondante
     * @param cEtiquette    Étiquette en question
     * @param nDonnee       Nombre de caractères de donnée
     * @param bHorodatage   Si l'étiquette est horodatée ou non (par défaut à faux)
     * @return L'index correspondant à l'étiquette
     */
    int ExtraireEtiquette(QByteArray cEtiquette, int nDonnee, bool bHorodatage = false);

    /**
     * @brief Extrait l'étiquette DATE de la TIC et la stock dans l'attribut cDate
     */
    void ExtraireDate();

// Attributs
    /**
     * @brief Port série
     */
    QSerialPort oPortSerie;
    /**
     * @brief Timer permettant de limiter la durée d'acquisition
     */
    QTimer oTimerAcquisition;

    /**
     * @brief Attribut dans lequel est stocké la trame complète
     */
    QByteArray oTrame;

// Instantannées
    /**
     * @brief Variable dans laquelle est stockée l'instantannée de consommation (Étiquette SINSTS)
     */
    int nSoutirage;
    /**
     * @brief Variable dans laquelle est stockée l'instantannée d'injection (Étiquette SINSTI)
     */
    int nInjection;
    /**
     * @brief Variable dans laquelle est stockée la date (Étiquette DATE) au format : AAAA-MM-JJ HH:MM:SS
     */
    QDateTime oDate;
};

#endif // LINKY_H
