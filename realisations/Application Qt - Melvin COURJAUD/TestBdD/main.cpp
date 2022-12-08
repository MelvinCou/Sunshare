//------------------------------------------------------------------------------
/** @file         main.cpp
 *
 *  @brief        Programme permettant d'envoyer des données à la base de données
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
