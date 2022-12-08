//------------------------------------------------------------------------------
/** @file         main.cpp
 *
 *  @brief        Programme permettant de tester l'objet Linky
 *
 *  @author       Me. Courjaud
 *  @author       STS SN-IR, Lycée Nicolas APPERT, ORVAULT (FRANCE)
 *  @since        2020-12-03
 *  @version      1.0
 *  @date         2022-05-22
 *
 *  Ce programme sert à collecter la TIC et d'en faire le traitement
 *
 *  Fabrication   RecupererTIC.pro
 *
 *  @todo         Rien
 *
 *  @bug          Aucun
 */
//------------------------------------------------------------------------------
#include <qserialportinfo.h>
#include <QCoreApplication>

#include <iostream>
using namespace std;

#include "linky.h"

int main(int argc, char *argv[])
{
    QSerialPortInfo LePort("ttyUSB0");
    if(LePort.isNull() )
    {
        cout << "L'appareil n'est pas branche\n";
        exit(-1);
    } else {
        cout << "Description du port : " << LePort.description().toStdString()
             << "\nNom du port : " << LePort.portName().toStdString()
             << "\nEmplacement : " << LePort.systemLocation().toStdString()
             << "\nOccupe : " << (LePort.isBusy()?"Oui":"Non") << "\n\n" ;
    }


    QCoreApplication coreApplication(argc, argv);


    Linky PortSerie(LePort, QSerialPort::Baud9600, QSerialPort::Data7, QSerialPort::EvenParity, QSerialPort::OneStop);

    PortSerie.LancerAcquisition();

    return coreApplication.exec();
}
