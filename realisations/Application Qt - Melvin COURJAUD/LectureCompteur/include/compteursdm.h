#ifndef COMPTEURSDM_H
#define COMPTEURSDM_H

#include <pigpio.h>

/**
 * @brief La classe CompteurSDM permet de détecter les impulsions du compteur SDM120D et d'en déduire l'index de production
 */
class CompteurSDM
{
public:
    /**
     * @brief Constructeur de la classe CompteurSDM
     */
    CompteurSDM();
    /**
     * @brief Destructeur de la classe CompteurSDM
     */
    ~CompteurSDM();

    /**
     * @brief Permet de détecter les impulsions
     * @param gpio      Broche du GPIO concernée
     * @param niveau    État de la broche (0: bas, 1: haut, 2: pas de changement)
     * @param tick      Nombre de microsecondes écoulées depuis le démarrage du RPI (non utilisé)
     */
    static void Lire(int gpio, int niveau, uint32_t tick);
    /**
     * @brief Accesseur de l'attribut nProduction
     * @return L'attribut de classe nProduction
     */
    static int Get_nProduction();

private:
    /**
     * @brief nProduction contient l'index de production en Wh.
     * Cet attribut est statique pour être utilisé utilisé par la classe Linky lors de l'émission du signal TraitementTermine
     */
    static int nProduction;// static : partagé entre tous les objets de la classe
};

#endif // COMPTEURSDM_H
