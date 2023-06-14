#include <locale.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "debug.h"

#include "accelerations.h"

// make && ./sysol05 365 100 STL.DAT > data.csv
// Fonctionne uniquement sur macos (setlocale)

bool debug_mode = true; // Change si le fichier csv est séparé en ';' ou en '\t'

	/*
	 * Projet Math 2023
	 * Groupe : 05
	 * Noms : IZQUIERDO Guillaume, DERGHOUM Loïc
	 */

double jours, ppjour, h;

typedef struct 
{
	long double x;
	long double y;
} Vector2;

typedef struct 
{
	char name[10];
	long double weight;
	Vector2 position;
	Vector2 velocity;
    Vector2 acceleration;
} Astre;

Astre Soleil;
Astre Terre;
Astre Lune;

Astre Systeme[3];

void getData();

void usage(char *pgm) {
	printf("\nUsage : %s jours ppj fichier\n", pgm);
	printf(
		"\nOù\n    jours est la durée de la simulation en jours (entier),\n"
		"    ppj est le nombre de points de calcul par jour,\n"
		"    chemin désigne le fichier contenant les corps célestes\n");
	exit(EXIT_FAILURE);
}


int main(int argc, char *argv[]) {
	int i, imax;

	if (setlocale(LC_NUMERIC ,"fr_FR")==NULL)
		exit_error("Localisation française impossible !");
	if (argc != 4) {
		usage(argv[0]);
	} else {
		
		/*
		 * Traitement des arguments  argv[1] à argv[3]
		 * atoi -> chaîne (ascii) vers entier
		 * atof -> chaîne (ascii) vers réel
		 */

		// exit_error("erreur");

		/*
		 *	Traitement des données :
		 *	 - Récupération des paramètres
		 *	 - Récupération du contenu du fichier STL.dat 
		*/

		// Récupération des paramètres
		jours = atoi(argv[1]);
		ppjour = atoi(argv[2]);
        h = 86400/ppjour;

		//debug("jour = %f", jours);
		//debug("ppj = %f", ppjour);

		// Récupération du contenu du fichier STL.dat 
		getData();

		debug("Liste des astres enreigstrés:");
		for(int i = 0; i < 3; i++)
		{
			debug("\t- '%s'", Systeme[i].name);	
		}

        debug("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");

        if(debug_mode)
            printf("Temps;Soleil_x;Soleil_y;Soleil_vx;Soleil_vy;Soleil_ax;Soleil_ay;Terre_x;Terre_y;Terre_vx;Terre_vy;Terre_ax;Terre_ay;Lune_x;Lune_y;Lune_vx;Lune_vy;Lune_ax;Lune_ay;Lune-Terre_x;Lune-Terre_y;dist_Terre-Lune\n");
        else
            printf("Temps\tSoleil_x\tSoleil_y\tSoleil_vx\tSoleil_vy\tSoleil_ax\tSoleil_ay\tTerre_x\tTerre_y\tTerre_vx\tTerre_vy\tTerre_ax\tTerre_ay\tLune_x\tLune_y\tLune_vx\tLune_vy\tLune_ax\tLune_ay\tLune-Terre_x\tLune-Terre_y\tdist_Terre-Lune\n");


        Soleil = Systeme[0];
        Terre = Systeme[1];
        Lune = Systeme[2];

        //printf("%LF;%LF;%LF;%LF;%LF;%LF;\n", Soleil.position.x, Soleil.position.y, Terre.position.x, Terre.position.y, Lune.position.x, Lune.position.y);

        //printf("%lf", axT(Soleil.position.x, Soleil.position.y, Terre.position.x, Terre.position.y, Lune.position.x, Lune.position.y));

        double k1Sx = 0;
        double k1Sy = 0;
        double k1Tx = 0;
        double k1Ty = 0;
        double k1Lx = 0;
        double k1Ly = 0;
        double k2Sx = 0;
        double k2Sy = 0;
        double k2Tx = 0;
        double k2Ty = 0;
        double k2Lx = 0;
        double k2Ly = 0;
        double k3Sx = 0;
        double k3Sy = 0;
        double k3Tx = 0;
        double k3Ty = 0;
        double k3Lx = 0;
        double k3Ly = 0;
        double k4Sx = 0;
        double k4Sy = 0;
        double k4Tx = 0;
        double k4Ty = 0;
        double k4Lx = 0;
        double k4Ly = 0;

        double x2 = 0;
        double y2 = 0;
        double x3 = 0;
        double y3 = 0;
        double x4 = 0;
        double y4 = 0;

        double d = distance(Terre.position.x, Terre.position.y, Lune.position.x, Lune.position.y);

        Vector2 SoleilPosBuff;
        Vector2 SoleilVelBuff;
        Vector2 TerrePosBuff;
        Vector2 TerreVelBuff;
        Vector2 LunePosBuff;
        Vector2 LuneVelBuff;

        //debug("d = %le", d);

        for(int i = 1; i <= jours * ppjour + 2; i++)
        {

            // Affichage :

            if(debug_mode)
                printf("%f;%Le;%Le;%Le;%Le;%Le;%Le;%Le;%Le;%Le;%Le;%Le;%Le;%Le;%Le;%Le;%Le;%Le;%Le;%Le;%Le;", i / ppjour, Soleil.position.x, Soleil.position.y, Soleil.velocity.x, Soleil.velocity.y, Soleil.acceleration.x, Soleil.acceleration.y, Terre.position.x, Terre.position.y, Terre.velocity.x, Terre.velocity.y, Terre.acceleration.x, Terre.acceleration.y, Lune.position.x, Lune.position.y, Lune.velocity.x, Lune.velocity.y, Lune.acceleration.x, Lune.acceleration.y, (Lune.position.x - Terre.position.x), (Lune.position.y - Terre.position.y));
            else
                printf("%f\t%Le\t%Le\t%Le\t%Le\t%Le\t%Le\t%Le\t%Le\t%Le\t%Le\t%Le\t%Le\t%Le\t%Le\t%Le\t%Le\t%Le\t%Le\t%Le\t%Le\t", i / ppjour, Soleil.position.x, Soleil.position.y, Soleil.velocity.x, Soleil.velocity.y, Soleil.acceleration.x, Soleil.acceleration.y, Terre.position.x, Terre.position.y, Terre.velocity.x, Terre.velocity.y, Terre.acceleration.x, Terre.acceleration.y, Lune.position.x, Lune.position.y, Lune.velocity.x, Lune.velocity.y, Lune.acceleration.x, Lune.acceleration.y, (Lune.position.x - Terre.position.x), (Lune.position.y - Terre.position.y));
            
            printf("%le\n", d); // Jsp pas pq mais ça marche pas si je mets la distance dans le printf précédent

            // Calculs :

            // On calcule l'accélération du soleil

            Soleil.acceleration.x = axS(Soleil.position.x, Soleil.position.y, Terre.position.x, Terre.position.y, Lune.position.x, Lune.position.y);
            Soleil.acceleration.y = ayS(Soleil.position.x, Soleil.position.y, Terre.position.x, Terre.position.y, Lune.position.x, Lune.position.y);

            // On calcule l'accélération de la terre

            Terre.acceleration.x = axT(Soleil.position.x, Soleil.position.y, Terre.position.x, Terre.position.y, Lune.position.x, Lune.position.y);
            Terre.acceleration.y = ayT(Soleil.position.x, Soleil.position.y, Terre.position.x, Terre.position.y, Lune.position.x, Lune.position.y);

            // On calcule l'accélération de la lune

            Lune.acceleration.x = axL(Soleil.position.x, Soleil.position.y, Terre.position.x, Terre.position.y, Lune.position.x, Lune.position.y);
            Lune.acceleration.y = ayL(Soleil.position.x, Soleil.position.y, Terre.position.x, Terre.position.y, Lune.position.x, Lune.position.y);

            // RK4 Soleil
            
            // k = [ [kX], [kY] ]

            k1Sx = axS(Soleil.position.x, Soleil.position.y, Terre.position.x, Terre.position.y, Lune.position.x, Lune.position.y);
            k1Sy = ayS(Soleil.position.x, Soleil.position.y, Terre.position.x, Terre.position.y, Lune.position.x, Lune.position.y);

            k2Sx = axS(Soleil.position.x + Soleil.velocity.x * h / 2, Soleil.position.y + Soleil.velocity.y * h / 2,
                        Terre.position.x + Terre.velocity.x * h / 2, Terre.position.y + Terre.velocity.y * h / 2,
                        Lune.position.x + Lune.velocity.x * h / 2, Lune.position.y + Lune.velocity.y * h / 2);

            k2Sy = ayS(Soleil.position.x + Soleil.velocity.x * h / 2, Soleil.position.y + Soleil.velocity.y * h / 2,
                        Terre.position.x + Terre.velocity.x * h / 2, Terre.position.y + Terre.velocity.y * h / 2,
                        Lune.position.x + Lune.velocity.x * h / 2, Lune.position.y + Lune.velocity.y * h / 2);

            k3Sx = axS(Soleil.position.x + Soleil.velocity.x * h / 2 + h * h / 4 * k1Sx, Soleil.position.y + Soleil.velocity.y * h / 2 + h * h / 4 * k1Sy,
                        Terre.position.x + Terre.velocity.x * h / 2 + h * h / 4 * k1Sx, Terre.position.y + Terre.velocity.y * h / 2 + h * h / 4 * k1Sy,
                        Lune.position.x + Lune.velocity.x * h / 2 + h * h / 4 * k1Sx, Lune.position.y + Lune.velocity.y * h / 2 + h * h / 4 * k1Sy);
            
            k3Sy = ayS(Soleil.position.x + Soleil.velocity.x * h / 2 + h * h / 4 * k1Sx, Soleil.position.y + Soleil.velocity.y * h / 2 + h * h / 4 * k1Sy,
                        Terre.position.x + Terre.velocity.x * h / 2 + h * h / 4 * k1Sx, Terre.position.y + Terre.velocity.y * h / 2 + h * h / 4 * k1Sy,
                        Lune.position.x + Lune.velocity.x * h / 2 + h * h / 4 * k1Sx, Lune.position.y + Lune.velocity.y * h / 2 + h * h / 4 * k1Sy);

            k4Sx = axS(Soleil.position.x + Soleil.velocity.x * h + h * h / 2 * k2Sx, Soleil.position.y + Soleil.velocity.y * h + h * h / 2 * k2Sy,
                        Terre.position.x + Terre.velocity.x * h + h * h / 2 * k2Sx, Terre.position.y + Terre.velocity.y * h + h * h / 2 * k2Sy,
                        Lune.position.x + Lune.velocity.x * h + h * h / 2 * k2Sx, Lune.position.y + Lune.velocity.y * h + h * h / 2 * k2Sy);

            k4Sy = ayS(Soleil.position.x + Soleil.velocity.x * h + h * h / 2 * k2Sx, Soleil.position.y + Soleil.velocity.y * h + h * h / 2 * k2Sy,
                        Terre.position.x + Terre.velocity.x * h + h * h / 2 * k2Sx, Terre.position.y + Terre.velocity.y * h + h * h / 2 * k2Sy,
                        Lune.position.x + Lune.velocity.x * h + h * h / 2 * k2Sx, Lune.position.y + Lune.velocity.y * h + h * h / 2 * k2Sy);

            // RK4 Terre

            // k = [ [kX], [kY] ]

            k1Tx = axT(Soleil.position.x, Soleil.position.y, Terre.position.x, Terre.position.y, Lune.position.x, Lune.position.y);
            k1Ty = ayT(Soleil.position.x, Soleil.position.y, Terre.position.x, Terre.position.y, Lune.position.x, Lune.position.y);

            k2Tx = axT(Soleil.position.x + Soleil.velocity.x * h / 2, Soleil.position.y + Soleil.velocity.y * h / 2,
                        Terre.position.x + Terre.velocity.x * h / 2, Terre.position.y + Terre.velocity.y * h / 2,
                        Lune.position.x + Lune.velocity.x * h / 2, Lune.position.y + Lune.velocity.y * h / 2);

            k2Ty = ayT(Soleil.position.x + Soleil.velocity.x * h / 2, Soleil.position.y + Soleil.velocity.y * h / 2,
                        Terre.position.x + Terre.velocity.x * h / 2, Terre.position.y + Terre.velocity.y * h / 2,
                        Lune.position.x + Lune.velocity.x * h / 2, Lune.position.y + Lune.velocity.y * h / 2);

            k3Tx = axT(Soleil.position.x + Soleil.velocity.x * h / 2 + h * h / 4 * k1Sx, Soleil.position.y + Soleil.velocity.y * h / 2 + h * h / 4 * k1Sy,
                        Terre.position.x + Terre.velocity.x * h / 2 + h * h / 4 * k1Sx, Terre.position.y + Terre.velocity.y * h / 2 + h * h / 4 * k1Sy,
                        Lune.position.x + Lune.velocity.x * h / 2 + h * h / 4 * k1Sx, Lune.position.y + Lune.velocity.y * h / 2 + h * h / 4 * k1Sy);

            k3Ty = ayT(Soleil.position.x + Soleil.velocity.x * h / 2 + h * h / 4 * k1Sx, Soleil.position.y + Soleil.velocity.y * h / 2 + h * h / 4 * k1Sy,
                        Terre.position.x + Terre.velocity.x * h / 2 + h * h / 4 * k1Sx, Terre.position.y + Terre.velocity.y * h / 2 + h * h / 4 * k1Sy,
                        Lune.position.x + Lune.velocity.x * h / 2 + h * h / 4 * k1Sx, Lune.position.y + Lune.velocity.y * h / 2 + h * h / 4 * k1Sy);

            k4Tx = axT(Soleil.position.x + Soleil.velocity.x * h + h * h / 2 * k2Sx, Soleil.position.y + Soleil.velocity.y * h + h * h / 2 * k2Sy,
                        Terre.position.x + Terre.velocity.x * h + h * h / 2 * k2Sx, Terre.position.y + Terre.velocity.y * h + h * h / 2 * k2Sy,
                        Lune.position.x + Lune.velocity.x * h + h * h / 2 * k2Sx, Lune.position.y + Lune.velocity.y * h + h * h / 2 * k2Sy);

            k4Ty = ayT(Soleil.position.x + Soleil.velocity.x * h + h * h / 2 * k2Sx, Soleil.position.y + Soleil.velocity.y * h + h * h / 2 * k2Sy,
                        Terre.position.x + Terre.velocity.x * h + h * h / 2 * k2Sx, Terre.position.y + Terre.velocity.y * h + h * h / 2 * k2Sy,
                        Lune.position.x + Lune.velocity.x * h + h * h / 2 * k2Sx, Lune.position.y + Lune.velocity.y * h + h * h / 2 * k2Sy);

            // RK4 Lune

            // k = [ [kX], [kY] ]

            k1Lx = axL(Soleil.position.x, Soleil.position.y, Terre.position.x, Terre.position.y, Lune.position.x, Lune.position.y);
            k1Ly = ayL(Soleil.position.x, Soleil.position.y, Terre.position.x, Terre.position.y, Lune.position.x, Lune.position.y);

            k2Lx = axL(Soleil.position.x + Soleil.velocity.x * h / 2, Soleil.position.y + Soleil.velocity.y * h / 2,
                        Terre.position.x + Terre.velocity.x * h / 2, Terre.position.y + Terre.velocity.y * h / 2,
                        Lune.position.x + Lune.velocity.x * h / 2, Lune.position.y + Lune.velocity.y * h / 2);

            k2Ly = ayL(Soleil.position.x + Soleil.velocity.x * h / 2, Soleil.position.y + Soleil.velocity.y * h / 2,
                        Terre.position.x + Terre.velocity.x * h / 2, Terre.position.y + Terre.velocity.y * h / 2,
                        Lune.position.x + Lune.velocity.x * h / 2, Lune.position.y + Lune.velocity.y * h / 2);

            k3Lx = axL(Soleil.position.x + Soleil.velocity.x * h / 2 + h * h / 4 * k1Sx, Soleil.position.y + Soleil.velocity.y * h / 2 + h * h / 4 * k1Sy,
                        Terre.position.x + Terre.velocity.x * h / 2 + h * h / 4 * k1Sx, Terre.position.y + Terre.velocity.y * h / 2 + h * h / 4 * k1Sy,
                        Lune.position.x + Lune.velocity.x * h / 2 + h * h / 4 * k1Sx, Lune.position.y + Lune.velocity.y * h / 2 + h * h / 4 * k1Sy);

            k3Ly = ayL(Soleil.position.x + Soleil.velocity.x * h / 2 + h * h / 4 * k1Sx, Soleil.position.y + Soleil.velocity.y * h / 2 + h * h / 4 * k1Sy,
                        Terre.position.x + Terre.velocity.x * h / 2 + h * h / 4 * k1Sx, Terre.position.y + Terre.velocity.y * h / 2 + h * h / 4 * k1Sy,
                        Lune.position.x + Lune.velocity.x * h / 2 + h * h / 4 * k1Sx, Lune.position.y + Lune.velocity.y * h / 2 + h * h / 4 * k1Sy);

            k4Lx = axL(Soleil.position.x + Soleil.velocity.x * h + h * h / 2 * k2Sx, Soleil.position.y + Soleil.velocity.y * h + h * h / 2 * k2Sy,
                        Terre.position.x + Terre.velocity.x * h + h * h / 2 * k2Sx, Terre.position.y + Terre.velocity.y * h + h * h / 2 * k2Sy,
                        Lune.position.x + Lune.velocity.x * h + h * h / 2 * k2Sx, Lune.position.y + Lune.velocity.y * h + h * h / 2 * k2Sy);

            k4Ly = ayL(Soleil.position.x + Soleil.velocity.x * h + h * h / 2 * k2Sx, Soleil.position.y + Soleil.velocity.y * h + h * h / 2 * k2Sy,
                        Terre.position.x + Terre.velocity.x * h + h * h / 2 * k2Sx, Terre.position.y + Terre.velocity.y * h + h * h / 2 * k2Sy,
                        Lune.position.x + Lune.velocity.x * h + h * h / 2 * k2Sx, Lune.position.y + Lune.velocity.y * h + h * h / 2 * k2Sy);

            // On enregistre les positions une fois qu'on a tout calculé

            Soleil.position.x = Soleil.position.x + h * Soleil.velocity.x + h * h / 6 * (k1Sx + k2Sx + k3Sx);
            Soleil.position.y = Soleil.position.y + h * Soleil.velocity.y + h * h / 6 * (k1Sy + k2Sy + k3Sy);

            Soleil.velocity.x = Soleil.velocity.x + h / 6 * (k1Sx + 2 * k2Sx + 2 * k3Sx + k4Sx);
            Soleil.velocity.y = Soleil.velocity.y + h / 6 * (k1Sy + 2 * k2Sy + 2 * k3Sy + k4Sy);

            Terre.position.x = Terre.position.x + h * Terre.velocity.x + h * h / 6 * (k1Tx + k2Tx + k3Tx);
            Terre.position.y = Terre.position.y + h * Terre.velocity.y + h * h / 6 * (k1Ty + k2Ty + k3Ty);

            Terre.velocity.x = Terre.velocity.x + h / 6 * (k1Tx + 2 * k2Tx + 2 * k3Tx + k4Tx);
            Terre.velocity.y = Terre.velocity.y + h / 6 * (k1Ty + 2 * k2Ty + 2 * k3Ty + k4Ty);

            Lune.position.x = Lune.position.x + h * Lune.velocity.x + h * h / 6 * (k1Lx + k2Lx + k3Lx);
            Lune.position.y = Lune.position.y + h * Lune.velocity.y + h * h / 6 * (k1Ly + k2Ly + k3Ly);

            Lune.velocity.x = Lune.velocity.x + h / 6 * (k1Lx + 2 * k2Lx + 2 * k3Lx + k4Lx);
            Lune.velocity.y = Lune.velocity.y + h / 6 * (k1Ly + 2 * k2Ly + 2 * k3Ly + k4Ly);

            // On calcule la distance

            d = distance(Terre.position.x, Terre.position.y, Lune.position.x, Lune.position.y);
        }
		
	}

    debug("Simulation terminée.");
    debug("Cette fois-ci on print en km !");

	/* Simulation */
	
	return EXIT_SUCCESS;
}

void getData()
{
    FILE *file;
    Astre astre;
    Vector2 vector2;
    char line[100];
    char *token;
    int escapeBuffer = 0;
    int i = 0;

    // On ouvre le fichier en mode lecture
    file = fopen("STL.dat", "r");

    debug("Lecture du fichier STL.dat en cours...");

    while (fgets(line, 100, file))
    {
        //debug("escapeBuffer = %d", escapeBuffer);
        //debug("'%s'", line);

        // On échappe le premier retour à la ligne
        if (escapeBuffer == 0 && line[0] == '\n')
            escapeBuffer = 1;

        // On ignore les lignes commençant par '#' ou '\n'
        if (line[0] != '#' && line[0] != '\n')
        {
            if (escapeBuffer == 1)
            {
                // On récupère le nom de l'astre
                strcpy(astre.name, strtok(line, "\n"));
                debug("Nom = %s", astre.name);
                escapeBuffer = 2;
            }
            else if (escapeBuffer == 2)
            {
                // On récupère le poids de l'astre
                astre.weight = atof(strtok(line, "\n"));
                debug("Weight = %LF", astre.weight);
                escapeBuffer = 3;
            }
            else if (escapeBuffer == 3)
            {
                char *xPosC;
                char *yPosC;

                // On récupère la position Y en premier

				/* On recupère Y en premier car le strtok sur le X va modifier le pointeur line
				 * On applique d'abord un strstr pour récupérer une chaine qui commence à partir
				 * des deux \t. Ensuite on retire les \t\t. Ensuite on retire le \n. Ensuite on
				 * convertie yPosC en double.
				 */

                yPosC = strtok(
							strtok(
								strstr(line, "\t\t")
							, "\t\t")
						, "\n");
                vector2.y = atof(yPosC);

                // On récupère la position X
                xPosC = strtok(strtok(line, "\t\t"), "\n");
                vector2.x = atof(xPosC);

                astre.position = vector2;
                debug("xPos = %LF km, yPos = %LF km", astre.position.x, astre.position.y);
                escapeBuffer = 4;
            }
            else if (escapeBuffer == 4)
            {
                char *xSpeedC;
                char *ySpeedC;

                // On récupère les vitesse en Y en premier

				/* Idem */

                ySpeedC = strtok(
								strtok(
									strstr(line, "\t\t")
								, "\t\t")
							, "\n");
                vector2.y = atof(ySpeedC);

                // On récupère la vitesse en X
                xSpeedC = strtok(strtok(line, "\t\t"), "\n");
                vector2.x = atof(xSpeedC);

                astre.velocity = vector2;
                debug("xSpeed = %LF km/s, ySpeed = %LF km/s", astre.velocity.x, astre.velocity.y);
                escapeBuffer = 5;

                vector2.x = 0;
                vector2.y = 0;
                astre.acceleration = vector2;

				// On enregistre l'astre dans le tableau pour le traitement des données
                Systeme[i] = astre;
				debug("Astre %s enregistré à l'indice %d\n", astre.name, i);

				// On réinitialise le buffer
                escapeBuffer = 0;

				// On incrémente i pour le prochain astre
                i++;
                
            }

            Systeme[1].position.y = 0; // Parce que yTerre = 8km -> Pourquoi ?? Je ne sais point

            //debug("%s", line);
        }
    }

    debug("Fichier STL.dat entièrement analysé. Fermeture en cours...");

    fclose(file);
}
