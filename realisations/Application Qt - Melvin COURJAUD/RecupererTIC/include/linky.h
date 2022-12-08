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

public:
    /**
     * @brief Constructeur paramétré de la classe Linky
     * @param InfosPortSerie    Classe fournissant les informations sur le port série
     * @param nDebit            Débit en baud du port série (1200, 9600...)
     * @param NbreBitsDonnees   Nombre de bits de données (7 ou 8)
     * @param Parite            Périté du port série (paire, impaire)
     * @param NbreBitsStop      Nombre de bits de stop (1 ou 2)
     */
    explicit Linky(QSerialPortInfo InfosPortSerie, qint32 nDebit, QSerialPort::DataBits NbreBitsDonnees,
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
     * @brief Lit toutes les données transmises chaque fois qu'une donnée est disponible
     */
    void on_Lire();
    void on_TerminerAcquisition();
    void on_Erreur(QSerialPort::SerialPortError error);

private:
    /**
     * @brief Permet d'extraire la valeur d'un index à partir de son étiquette correspondante
     * @param Étiquette en question
     * @param Nombre de caractères de donnée
     * @param Si l'étiquette est horodatée ou non (par défaut à faux)
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
     * @brief Variable dans laquelle est stockée la date (Étiquette DATE)
     */
    QDateTime oDate;
};

#endif // LINKY_H
