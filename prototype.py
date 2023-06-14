import numpy as np
import matplotlib.pyplot as plt

xS = 0.1
yS = 0.3

xT = -1.471000e8
yT = 0

xL = -1.474850e8
yL = 0

A = 0
B = 0
C = 0
D = 0
E = 0
F = 0
H = 0
I = 0
J = 0

k1 = np.array([0, 0])
k2 = np.array([0, 0])
k3 = np.array([0, 0])
k4 = np.array([0, 0])

# On définit les constantes:

sep = ";"

mS = 1.9891e30
mT = 5.9722e24
mL = 7.342e22
G = 6.6742e-11

nbrJour = 365
ppJour = 10
dt = 86400/ppJour

# On initialise les positions et vitesses initiales:

soleil = np.array([np.array([0.0, 0.0]), np.array([0, 9.2e-5 * 1000]), np.array([0, 0])])
terre = np.array([np.array([-1.471000e8 * 1000, 0.0]), np.array([0, -30.28036 * 1000]), np.array([0, 0])])
lune = np.array([np.array([-1.474850e8 * 1000, 0.0]), np.array([0, -31.285 * 1000]), np.array([0, 0])])

def axS(_xS, _yS, _xT, _yT, _xL, _yL):
    # A = -G * mT / ((_xS - _xT)**2 + (_yS - _yT)**2)**(3/2) - G * mL / ((_xS - _xL)**2 + (_yS - _yL)**2)**(3/2)
    # B = G * mT * _xT / ((_xS - _xT)**2 + (_yS - _yT)**2)**(3/2) + G * mL * _xL / ((_xS - _xL)**2 + (_yS - _yL)**2)**(3/2)

    return -G * ( mT * (_xS - _xT) / ( (_xS - _xT)**2 + (_yS - _yT)**2 )**(3/2) + mL * (_xS - _xL) / ( (_xS - _xL)**2 + (_yS - _yL)**2 )**(3/2) )

def ayS(_xS, _yS, _xT, _yT, _xL, _yL):
    # A = -G * mT / ((_xS - _xT)**2 + (_yS - _yT)**2)**(3/2) - G * mL / ((_xS - _xL)**2 + (_yS - _yL)**2)**(3/2)
    # C = G * mT * _yT / ((_xS - _xT)**2 + (_yS - _yT)**2)**(3/2) + G * mL * _yL / ((_xS - _xL)**2 + (_yS - _yL)**2)**(3/2)

    return -G * ( mT * (_yS - _yT) / ( (_xS - _xT)**2 + (_yS - _yT)**2 )**(3/2) + mL * (_yS - _yL) / ( (_xS - _xL)**2 + (_yS - _yL)**2 )**(3/2) )

def axT(_xS, _yS, _xT, _yT, _xL, _yL):
    # D = -G * mS / ((_xT - _xS)**2 + (_yT - _yS)**2)**(3/2) - G * mL / ((_xT - _xL)**2 + (_yT - _yL)**2)**(3/2)
    # E = G * mS * _xS / ((_xT - _xS)**2 + (_yT - _yS)**2)**(3/2) + G * mL * _xL / ((_xT - _xL)**2 + (_yT - _yL)**2)**(3/2)

    return -G * ( mS * (_xT - _xS) / ( (_xT - _xS)**2 + (_yT - _yS)**2 )**(3/2) + mL * (_xT - _xL) / ( (_xT - _xL)**2 + (_yT - _yL)**2 )**(3/2) )

def ayT(_xS, _yS, _xT, _yT, _xL, _yL):
    # D = -G * mS / ((_xT - _xS)**2 + (_yT - _yS)**2)**(3/2) - G * mL / ((_xT - _xL)**2 + (_yT - _yL)**2)**(3/2)
    # F = G * mS * _yS / ((_xT - _xS)**2 + (_yT - _yS)**2)**(3/2) + G * mL * _yL / ((_xT - _xL)**2 + (_yT - _yL)**2)**(3/2)

    return -G * ( mS * (_yT - _yS) / ( (_xT - _xS)**2 + (_yT - _yS)**2 )**(3/2) + mL * (_yT - _yL) / ( (_xT - _xL)**2 + (_yT - _yL)**2 )**(3/2) )

def axL(_xS, _yS, _xT, _yT, _xL, _yL):
    # H = -G * mS / ((_xL - _xS)**2 + (_yL - _yS)**2)**(3/2) - G * mT / ((_xL - _xT)**2 + (_yL - _yT)**2)**(3/2)
    # I = G * mS * _xS / ((_xL - _xS)**2 + (_yL - _yS)**2)**(3/2) + G * mT * _xT / ((_xL - _xT)**2 + (_yL - _yT)**2)**(3/2)

    return -G * ( mS * (_xL - _xS) / ( (_xL - _xS)**2 + (_yL - _yS)**2 )**(3/2) + mT * (_xL - _xT) / ( (_xL - _xT)**2 + (_yL - _yT)**2 )**(3/2) )

def ayL(_xS, _yS, _xT, _yT, _xL, _yL):
    # H = -G * mS / ((_xL - _xS)**2 + (_yL - _yS)**2)**(3/2) - G * mT / ((_xL - _xT)**2 + (_yL - _yT)**2)**(3/2)
    # J = G * mS * _yS / ((_xL - _xS)**2 + (_yL - _yS)**2)**(3/2) + G * mT * _yT / ((_xL - _xT)**2 + (_yL - _yT)**2)**(3/2)

    return -G * ( mS * (_yL - _yS) / ( (_xL - _xS)**2 + (_yL - _yS)**2 )**(3/2) + mT * (_yL - _yT) / ( (_xL - _xT)**2 + (_yL - _yT)**2 )**(3/2) )

k1x = 0
k1y = 0
k2x = 0
k2y = 0
k3x = 0
k3y = 0
k4x = 0
k4y = 0

if __name__ == "__main__":

    # On initialise les tableaux pour les graphiques:

    plotXSoleil = np.zeros(nbrJour * ppJour)
    plotYSoleil = np.zeros(nbrJour * ppJour)

    plotXTerre = np.zeros(nbrJour * ppJour)
    plotYTerre = np.zeros(nbrJour * ppJour)

    plotXLune = np.zeros(nbrJour * ppJour)
    plotYLune = np.zeros(nbrJour * ppJour)

    # On affiche les entêtes des colonnes:
    print(f"temps{sep}position_xS{sep}position_yS{sep}vitesse_xS{sep}vitesse_yS{sep}acce_xS{sep}acce_yS{sep}position_xT{sep}position_yT{sep}vitesse_xT{sep}vitesse_yT{sep}acce_xT{sep}acce_yT{sep}position_xL{sep}position_yL{sep}vitesse_xL{sep}vitesse_yL{sep}acce_xL{sep}acce_yL{sep}position_xL_T{sep}position_yL_T{sep}d_TL")

    # print(axS(soleil[0][0], soleil[0][1], terre[0][0], terre[0][1], lune[0][0], lune[0][1]))

    for i in range(nbrJour * ppJour):

        # On affiche les valeurs

        print(f"{i}{sep}{soleil[0][0] / 1000}{sep}{soleil[0][1] / 1000}{sep}{soleil[1][0] / 1000}{sep}{soleil[1][1] / 1000}{sep}{soleil[2][0] / 1000}{sep}{soleil[2][1] / 1000}{sep}{terre[0][0]}{sep}{terre[0][1]}{sep}{terre[1][0]}{sep}{terre[1][1]}{sep}{terre[2][0]}{sep}{terre[2][1]}{sep}{lune[0][0]}{sep}{lune[0][1]}{sep}{lune[1][0]}{sep}{lune[1][1]}{sep}{lune[2][0]}{sep}{lune[2][1]}{sep}{lune[0][0] - terre[0][0]}{sep}{lune[0][1] - terre[0][1]}{sep}{np.sqrt((lune[0][0] - terre[0][0])**2 + (lune[0][1] - terre[0][1])**2)}")
        
        # On ajoute les positions dans un tableau pour pouvoir les tracer ensuite:

        plotXSoleil[i] = soleil[0][0]
        plotYSoleil[i] = soleil[0][1]

        plotXTerre[i] = terre[0][0]
        plotYTerre[i] = terre[0][1]

        plotXLune[i] = lune[0][0]
        plotYLune[i] = lune[0][1]

        # Détermination des positions et vitesses pour un code plus lisible:

        xS = soleil[0][0]
        yS = soleil[0][1]
        xT = terre[0][0]
        yT = terre[0][1]
        xL = lune[0][0]
        yL = lune[0][1]

        vxS = soleil[1][0]
        vyS = soleil[1][1]
        vxT = terre[1][0]
        vyT = terre[1][1]
        vxL = lune[1][0]
        vyL = lune[1][1]

        # Calcul de l'accélérations du soleil

        soleil[2][0] = axS(xS, yS, xT, yT, xL, yL)
        soleil[2][1] = ayS(xS, yS, xT, yT, xL, yL)

        # Calcul de l'accélérations de la terre

        terre[2][0] = axT(xS, yS, xT, yT, xL, yL)
        terre[2][1] = ayT(xS, yS, xT, yT, xL, yL)

        # Calcul de l'accélérations de la lune

        lune[2][0] = axL(xS, yS, xT, yT, xL, yL)
        lune[2][1] = ayL(xS, yS, xT, yT, xL, yL)


        # RK4 Soleil

        # k = [ [kX], [kY] ]

        k1x = soleil[2][0]
        k1y = soleil[2][1]

        x2 = xS + vxS * dt / 2
        y2 = yS + vyS * dt / 2

        v2x = vxS + k1x * dt / 2
        v2y = vyS + k1y * dt / 2

        k2x = axS(x2, y2, xT, yT, xL, yL)
        k2y = ayS(x2, y2, xT, yT, xL, yL)

        x3 = xS + v2x * dt / 2
        y3 = yS + v2y * dt / 2

        v3x = vxS + k2x * dt / 2
        v3y = vyS + k2y * dt / 2

        k3x = axS(x3, y3, xT, yT, xL, yL)
        k3y = ayS(x3, y3, xT, yT, xL, yL)

        x4 = xS + v3x * dt + dt * dt / 2 * k2x
        y4 = yS + v3y * dt + dt * dt / 2 * k2y

        v4x = vxS + k3x * dt
        v4y = vyS + k3y * dt

        k4x = axS(x4, y4, xT, yT, xL, yL)
        k4y = ayS(x4, y4, xT, yT, xL, yL)

        soleil[0][0] = xS + dt * vxS + dt * dt / 6 * (k1x + k2x + k3x)
        soleil[0][1] = yS + dt * vyS + dt * dt / 6 * (k1y + k2y + k3y)

        soleil[1][0] = vxS + dt / 6 * (k1x + 2 * k2x + 2 * k3x + k4x)
        soleil[1][1] = vyS + dt / 6 * (k1y + 2 * k2y + 2 * k3y + k4y)

        # print(f"xS = {xS}, dt = {dt}, vxS = {vxS}, k1 = {k1[0]};{k1[1]}, k2 = {k2[0]};{k2[1]}, k3 = {k3[0]};{k3[1]}, k4 = {k4[0]};{k4[1]}")

        # RK4 Terre

        k1x = axT(xS, yS, xT, yT, xL, yL)
        k1y = ayT(xS, yS, xT, yT, xL, yL)

        x2 = xT + vxT * dt / 2
        y2 = yT + vyT * dt / 2

        v2x = vxT + k1x * dt / 2
        v2y = vyT + k1y * dt / 2

        k2x = axT(xS, yS, x2, y2, xL, yL)
        k2y = ayT(xS, yS, x2, y2, xL, yL)

        x3 = xT + v2x * dt / 2
        y3 = yT + v2y * dt / 2

        v3x = vxT + k2x * dt / 2
        v3y = vyT + k2y * dt / 2

        k3x = axT(xS, yS, x3, y3, xL, yL)
        k3y = ayT(xS, yS, x3, y3, xL, yL)

        x4 = xT + v3x * dt / 2
        y4 = yT + v3y * dt / 2

        v4x = vxT + k3x * dt / 2
        v4y = vyT + k3y * dt / 2

        k4x = axT(xS, yS, x4, y4, xL, yL)
        k4y = ayT(xS, yS, x4, y4, xL, yL)

        terre[0][0] = xT + dt * vxT + dt * dt / 6 * (k1x + k2x + k3x)
        terre[0][1] = yT + dt * vyT + dt * dt / 6 * (k1y + k2y + k3y)

        terre[1][0] = vxT + dt / 6 * (k1x + 2 * k2x + 2 * k3x + k4x)
        terre[1][1] = vyT + dt / 6 * (k1y + 2 * k2y + 2 * k3y + k4y)

        # print(f"xS = {xS}, dt = {dt}, vxS = {vxS}, k1 = {k1x};{k1y}, k2 = {k2x};{k2y}, k3 = {k3x};{k3y}, k4 = {k4x};{k4y}")

        # RK4 Lune

        k1x = axL(xS, yS, xT, yT, xL, yL)
        k1y = ayL(xS, yS, xT, yT, xL, yL)

        x2 = xL + vxL * dt / 2
        y2 = yL + vyL * dt / 2

        v2x = vxL + k1x * dt / 2
        v2y = vyL + k1y * dt / 2

        k2x = axL(xS, yS, xT, yT, x2, y2)
        k2y = ayL(xS, yS, xT, yT, x2, y2)

        x3 = xL + v2x * dt / 2
        y3 = yL + v2y * dt / 2

        v3x = vxL + k2x * dt / 2
        v3y = vyL + k2y * dt / 2

        k3x = axL(xS, yS, xT, yT, x3, y3)
        k3y = ayL(xS, yS, xT, yT, x3, y3)

        x4 = xL + v3x * dt / 2
        y4 = yL + v3y * dt / 2

        v4x = vxL + k3x * dt / 2
        v4y = vyL + k3y * dt / 2

        k4x = axL(xS, yS, xT, yT, x4, y4)
        k4y = ayL(xS, yS, xT, yT, x4, y4)

        lune[0][0] = xL + dt * vxL + dt * dt / 6 * (k1x + k2x + k3x)
        lune[0][1] = yL + dt * vyL + dt * dt / 6 * (k1y + k2y + k3y)

        lune[1][0] = vxL + dt / 6 * (k1x + 2 * k2x + 2 * k3x + k4x)
        lune[1][1] = vyL + dt / 6 * (k1y + 2 * k2y + 2 * k3y + k4y)

        


    # Plot des positions

    # plt.plot(plotXSoleil, plotYSoleil, label='Soleil', color='orange')
    plt.plot(plotXTerre, plotYTerre, label='Terre', color='cyan')
    plt.plot(plotXLune, plotYLune, label='Lune', color='black')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title('Position des astres')
    plt.show()