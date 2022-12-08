#ifndef GESTIONNAIRE_H
#define GESTIONNAIRE_H

#include <QSettings>
#include "basededonnees.h"
#include "linky.h"
#include "compteursdm.h"

/**
 * @brief La classe Gestionnaire gère
 */
class Gestionnaire : QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructeur de la classe Gestionnaire
     */
    Gestionnaire(QObject *parent = nullptr);

    ~Gestionnaire();

    /**
     * @brief Lance le timer d'acquisition
     */
    void DemarrerLeTimerAcquisition();

private slots:
    /**
     * @brief Déclenche l'acquisition des indicateurs et l'envoie dans la base de données
     */
    void on_DemarrerAcquisition();
private:
    /**
     * @brief Attribut permettant de récupérer des paramètres stockés dans un fichier,
     * sans avoir à recompiler le projet
     */
    QSettings oParametres;

    /**
     * @brief Attribut collectant les indicateurs de soutirage, injection et la date
     */
    Linky uTeleInfo;

    /**
     * @brief Attribut permettant de communiquer avec la base de données
     */
    BaseDeDonnees BdD;

    CompteurSDM SDM120D;

    /**
     * @brief Timer permettant de contrôler le délai entre chaque acquisition
     */
    QTimer oTimerAcquisition;

    int nDelaiAcquisition;
};

#endif // GESTIONNAIRE_H
