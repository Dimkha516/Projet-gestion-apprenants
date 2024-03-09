#include <stdio.h>
#include "functions.h"


int choice;
int homeMenu()
{
    printf("     --------------------ACCUEIL/BIENVENU--------------------\n");
    printf("Connectez vous...\n");
    saisiUserLogin();
}

int main()
{
    // createAdminFile();
    homeMenu();
    return 0;
}

/*
POUR LUNDI: C a valider pour venir

1°) Si présence marquée: sur la partie admin.
    DEUX Options générer fichier:
        1) Génrer toutes les présences classées par date les dates
          seront les principaux entêtes

        2) Option par date: l'admin saisit une date et on lui génére
         un fichier qui affiche les absences de cette date.
        configurer le format de date d'abord.
*/

/*
Gestion des messages:
3 options:

1) Message pour tous les étudiants (broadcast): si un apprenant se
connecte le nbr de message non lus à actualiser expl: (1). s'il lit,
le nbr message remis à 0

2) Message par classe: sélectionner une classe: envoi pour une classe
ou pour toutes les classes. le choix de classe doit être saisi et non
sélectionné.

3) Message par étudiant: il met le message. on lui demande d'entrer le
matricule de ou des étudiants séparée par virgule. une fois qu'il valide
un rapport sera affiché lui renseignant les matricules valide et
envoyés et pour les matricules non valides.

*/