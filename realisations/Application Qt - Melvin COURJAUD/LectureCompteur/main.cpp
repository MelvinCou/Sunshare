//------------------------------------------------------------------------------
/** @file         main.cpp
 *
 *  @brief        Programme permettant de traiter les impulsions du compteur SDM120D
 *
 *  @author       Me. Courjaud
 *  @author       STS SN-IR, Lycée Nicolas APPERT, ORVAULT (FRANCE)
 *  @since        2020-12-03
 *  @version      1.0
 *  @date         2022-06-01
 *
 *  Fabrication   LectureCompteur.pro
 *
 *  @todo         Rien
 *
 *  @bug          Aucun
 */
//------------------------------------------------------------------------------
#include "compteursdm.h"

#include <unistd.h>
#include <iostream>
using namespace std;

int main()
{
    CompteurSDM MonCompteur;

    // cette boucle permet de lancer le programme indéfiniement
    while (true) {
        sleep(1);
    }

    return 0;
}
