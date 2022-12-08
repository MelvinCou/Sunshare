//------------------------------------------------------------------------------
/** @file         main.cpp
 *
 *  @brief        Programme final remplissant toutes les fonctions
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
#include <QCoreApplication>

#include <iostream>
using namespace std;

#include "gestionnaire.h"

int main()
{
    int argc (0);
    char *argv[0];
    QCoreApplication a(argc, argv);

    Gestionnaire LeGestionnaire;

    LeGestionnaire.DemarrerLeTimerAcquisition();


    return a.exec();
}
