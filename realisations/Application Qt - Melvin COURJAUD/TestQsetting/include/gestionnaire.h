#ifndef GESTIONNAIRE_H
#define GESTIONNAIRE_H

#include <QSettings>

class Gestionnaire
{
public:
    Gestionnaire();
    ~Gestionnaire();

private:

    QSettings oParametres;
/*
    QTimer oTimerAcquisition;
    QTimer oTimerRetention;
*/
    int nDelaiAcquisition;
    int nDelaiRetention;
};

#endif // GESTIONNAIRE_H
