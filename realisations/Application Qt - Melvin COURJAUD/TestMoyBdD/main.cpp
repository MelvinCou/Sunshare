//------------------------------------------------------------------------------
/** @file         main.cpp
 *
 *  @brief        Programme testant l'envoi des moyennes à la base de données
 *
 *  @author       Me. Courjaud
 *  @author       STS SN-IR, Lycée Nicolas APPERT, ORVAULT (FRANCE)
 *  @since        2020-12-03
 *  @version      1.0
 *  @date         2022-05-22
 *
 *  Fabrication   TestMoyBdD.pro
 *
 *  @todo         Rien
 *
 *  @bug          Aucun
 */
//------------------------------------------------------------------------------
#include <QCoreApplication>
#include "basededonnees.h"

int main()
{
    int argc (0);
    char * argv[0];

    QCoreApplication a(argc, argv);

    BaseDeDonnees MaBdD("127.0.0.1", 3306, "admin", "admin", "SunshareBDD");

    return a.exec();
}
