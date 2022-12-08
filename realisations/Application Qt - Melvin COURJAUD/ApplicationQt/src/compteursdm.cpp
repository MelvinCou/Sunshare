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
 *  Fabrication   ApplicationQt.pro
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
    // initialisation du taux d'échantillonage (ici : 10 µs)
    if(gpioCfgClock(10, PI_CLOCK_PCM, 0) < 0)
    {
        cout << "Taux d'echantillonnage non initialise\n";
    }
    // les paramètres servent à se connecter à un GPIO sur le réseau, ici la valeur nullptr permet de se connecter au localhost
    if(gpioInitialise(nullptr) < 0)
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
    /* La méthode Lire est appelée à chaque changement d'état, cependant,
     * une impulsion se compose de deux changements d'état, ici, le programme ne détecte que
     * le passage à l’état bas
     */
    if (gpio == 4 && niveau == FALLING_EDGE) {
        nProduction++;// 1 impulsion = 1 Wh : nProduction est incrémenté
    }
}

int CompteurSDM::Get_nProduction()
{
    return nProduction;
}
