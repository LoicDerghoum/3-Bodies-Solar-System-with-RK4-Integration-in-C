#include <math.h>

double mS = 1.9891e30;
double mT = 5.9722e24;
double mL = 7.342e22;
double G = 6.6742e-20;

double distance(double x1, double y1, double x2, double y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double axS(double _xS, double _yS, double _xT, double _yT, double _xL, double _yL){
    // A = -G * mT / ((_xS - _xT)**2 + (_yS - _yT)**2)**(3/2) - G * mL / ((_xS - _xL)**2 + (_yS - _yL)**2)**(3/2)
    // B = G * mT * _xT / ((_xS - _xT)**2 + (_yS - _yT)**2)**(3/2) + G * mL * _xL / ((_xS - _xL)**2 + (_yS - _yL)**2)**(3/2)

    return -G * ( mT * (_xS - _xT) / pow(( ((_xS - _xT) * (_xS - _xT)) + ((_yS - _yT) * (_yS - _yT)) ), 1.5) + mL * (_xS - _xL) / pow(( ((_xS - _xL) * (_xS - _xL)) + ((_yS - _yL) * (_yS - _yL)) ), 1.5) );
}

double ayS(double _xS, double _yS, double _xT, double _yT, double _xL, double _yL){
    // A = -G * mT / ((_xS - _xT)**2 + (_yS - _yT)**2)**(3/2) - G * mL / ((_xS - _xL)**2 + (_yS - _yL)**2)**(3/2)
    // C = G * mT * _yT / ((_xS - _xT)**2 + (_yS - _yT)**2)**(3/2) + G * mL * _yL / ((_xS - _xL)**2 + (_yS - _yL)**2)**(3/2)

    return -G * ( mT * (_yS - _yT) / pow(( ((_xS - _xT) * (_xS - _xT)) + ((_yS - _yT) * (_yS - _yT)) ), 1.5) + mL * (_yS - _yL) / pow(( ((_xS - _xL) * (_xS - _xL)) + ((_yS - _yL) * (_yS - _yL)) ), 1.5) );
}

double axT(double _xS, double _yS, double _xT, double _yT, double _xL, double _yL){
    // D = -G * mS / ((_xT - _xS)**2 + (_yT - _yS)**2)**(3/2) - G * mL / ((_xT - _xL)**2 + (_yT - _yL)**2)**(3/2)
    // E = G * mS * _xS / ((_xT - _xS)**2 + (_yT - _yS)**2)**(3/2) + G * mL * _xL / ((_xT - _xL)**2 + (_yT - _yL)**2)**(3/2)

    return -G * ( mS * (_xT - _xS) / pow(( ((_xT - _xS) * (_xT - _xS)) + ((_yT - _yS) * (_yT - _yS)) ), 1.5) + mL * (_xT - _xL) / pow(( ((_xT - _xL) * (_xT - _xL)) + ((_yT - _yL) * (_yT - _yL)) ), 1.5) );
}

double ayT(double _xS, double _yS, double _xT, double _yT, double _xL, double _yL){
    // D = -G * mS / ((_xT - _xS)**2 + (_yT - _yS)**2)**(3/2) - G * mL / ((_xT - _xL)**2 + (_yT - _yL)**2)**(3/2)
    // F = G * mS * _yS / ((_xT - _xS)**2 + (_yT - _yS)**2)**(3/2) + G * mL * _yL / ((_xT - _xL)**2 + (_yT - _yL)**2)**(3/2)

    return -G * ( mS * (_yT - _yS) / pow(( ((_xT - _xS) * (_xT - _xS)) + ((_yT - _yS) * (_yT - _yS)) ), 1.5) + mL * (_yT - _yL) / pow(( ((_xT - _xL) * (_xT - _xL)) + ((_yT - _yL) * (_yT - _yL)) ), 1.5) );
}

double axL(double _xS, double _yS, double _xT, double _yT, double _xL, double _yL){
    // H = -G * mS / ((_xL - _xS)**2 + (_yL - _yS)**2)**(3/2) - G * mT / ((_xL - _xT)**2 + (_yL - _yT)**2)**(3/2)
    // I = G * mS * _xS / ((_xL - _xS)**2 + (_yL - _yS)**2)**(3/2) + G * mT * _xT / ((_xL - _xT)**2 + (_yL - _yT)**2)**(3/2)

    return -G * ( mS * (_xL - _xS) / pow(( ((_xL - _xS) * (_xL - _xS)) + ((_yL - _yS) * (_yL - _yS)) ), 1.5) + mT * (_xL - _xT) / pow(( ((_xL - _xT) * (_xL - _xT)) + ((_yL - _yT) * (_yL - _yT)) ), 1.5) );
}

double ayL(double _xS, double _yS, double _xT, double _yT, double _xL, double _yL){
    // H = -G * mS / ((_xL - _xS)**2 + (_yL - _yS)**2)**(3/2) - G * mT / ((_xL - _xT)**2 + (_yL - _yT)**2)**(3/2)
    // J = G * mS * _yS / ((_xL - _xS)**2 + (_yL - _yS)**2)**(3/2) + G * mT * _yT / ((_xL - _xT)**2 + (_yL - _yT)**2)**(3/2)

    return -G * ( mS * (_yL - _yS) / pow(( ((_xL - _xS) * (_xL - _xS)) + ((_yL - _yS) * (_yL - _yS)) ), 1.5) + mT * (_yL - _yT) / pow(( ((_xL - _xT) * (_xL - _xT)) + ((_yL - _yT) * (_yL - _yT)) ), 1.5) );
}