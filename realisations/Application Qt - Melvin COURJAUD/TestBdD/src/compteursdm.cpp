//------------------------------------------------------------------------------
/** @file         compteursdm.cpp
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

#include <iostream>
using namespace std;

int CompteurSDM::nProduction = 0;// initialisation de l'attribut de classe nProduction

CompteurSDM::CompteurSDM()
{
    if(gpioInitialise() < 0)
    {
        cout << "PIGPIO n'a pas pu etre initialise.\n";
        exit(-1);
    }

    /* cette fonction permet d'appeler la méthode Lire() chaque fois qu'il y a un changement d'état
     * sur la broche 4 du GPIO, et donc de détecter les impulsions
     * @see Lire
     */
    if(gpioSetAlertFunc(4, Lire)    < 0 )
    {
        cout << "L'alerte n'est pas disponible";
        exit(-1);
    }
}

CompteurSDM::~CompteurSDM()
{
    gpioTerminate();
    nProduction = 0;

    cout << "\nCompteur detruit\n";
}

void CompteurSDM::Lire(int gpio, int niveau, uint32_t tick)
{
    /* cette méthode est déclenchée 2 fois par impulsion (passage état haut à état bas puis bas à haut)
     * on incrémente uniquement lors du passage à l'état bas
     */
    if (gpio == 4 && niveau == 0) {
        nProduction++;// 1 impulsion = 1 Wh : nProduction est incrémenté

        //cout << "Compteur : " << nProduction << " Wh\n";
    }
}

int CompteurSDM::Get_nProduction()
{
    return nProduction;
}
