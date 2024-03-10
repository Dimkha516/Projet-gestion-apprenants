#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define LONG_MAX 100
#define MAX_LENGTH 100

// création structure Admin:

//-----------------FONCTIONS BASICS:

// EFFACER LA CONSOLE:

void backHome()
{
    // #ifdef _WIN32
    // system("cls");
    // #else
    system("clear");
    // #endif
}

//-----------------------PROTOTYPES:
void adminMenu();
void studentMenu();
void saisiUserLogin();

//  MARQUER PRESENCE:
void marquerPresenceAdmin()
{
    printf("------------------ Marquer les présences ----------------\n");

    FILE *listEtudiants = fopen("studentUser.txt", "r");
    if (listEtudiants == NULL)
    {
        printf("Fichier liste étudiants introuvable...");
    }
    FILE *listPresences = fopen("presences.txt", "a+");
    if (listPresences == NULL)
    {
        printf("Fichier liste présences introuvable...");
    }
    char studentList[LONG_MAX][50]; // ZONE STOCKAGE DES ETUDIANTS:
    char studentName[50];
    char studentCode[50];
    int nbrStudent = 0; // ETUDIANT DANS LE FICHIER:

    while (fscanf(listEtudiants, "%s %s",
                  studentName, studentCode) == 2)
    {
        strcpy(studentList[nbrStudent], studentCode);
        strcpy(studentList[nbrStudent + 1], studentName);
        nbrStudent += 2;
    }
    fclose(listEtudiants);

    char codeStudentSaisi[50];
    int codeValid;
    struct tm *temps_info;
    time_t now;

    do
    {
        printf("Entrez le code étudiant (Q pour annuler): \n");
        printf(" => ");
        scanf("%s", codeStudentSaisi);

        if (strcmp(codeStudentSaisi, "Q") == 0)
            adminMenu();
        break;

        codeValid = 0;
        for (int i = 0; i < nbrStudent; i += 2)
        {
            if (strcmp(studentList[i], codeStudentSaisi) == 0)
            {
                codeValid = 1;
                now = time(NULL);
                temps_info = localtime(&now);
                char date[100];

                sprintf(date, "%02d/%02d/%02d", temps_info->tm_mday, temps_info->tm_mon + 1, temps_info->tm_year + 1900);

                fseek(listPresences, 0, SEEK_SET);

                int isSaved = 0;

                char line[100];
                while (fgets(line, sizeof(line), listPresences) != NULL)
                {
                    char studentNameFile[100], dateFile[100];
                    sscanf(line, "%*[^,],%*[^,],%49[^,],%49[^,]", studentNameFile, dateFile);
                    if (strcmp(studentNameFile, studentList[i + 1]) == 0 && strcmp(dateFile, date) == 0)
                    {
                        isSaved = 1;
                        break;
                    }
                }
                if (isSaved)
                {
                    printf("L'étudiant %s est déjà enregistré pour aujourd'hui.\n", studentList[i + 1]);
                }
                else
                {
                    printf("Présence enregistrée pour %s (code: %s) à %02d:%02d:%02d\n", studentList[i + 1], studentList[i], temps_info->tm_hour, temps_info->tm_min, temps_info->tm_sec);
                    fprintf(listPresences, "%s,%s,%02d/%02d/%02d,%02d:%02d\n", studentList[i + 1], codeStudentSaisi, temps_info->tm_mday, temps_info->tm_mon + 1, temps_info->tm_year + 1900, temps_info->tm_hour, temps_info->tm_min);
                }
                break;
            }
        }
        if (!codeValid)
        {
            printf("Code étudiant invalide\n");
        }

    } while (1);
    fclose(listPresences);
}

void marquerPresenceStudent()
{
    printf("-------------   Marquer ma présence   ------------\n");
    FILE *listEtudiants = fopen("studentUser.txt", "r");
    if (listEtudiants == NULL)
    {
        printf("Fichier liste étudiants introuvable...");
    }
    FILE *listPresences = fopen("presences.txt", "a+");
    if (listPresences == NULL)
    {
        printf("Fichier liste présences introuvable...");
    }
    char studentList[LONG_MAX][50]; // ZONE STOCKAGE DES ETUDIANTS:
    char studentName[50];
    char studentCode[50];
    int nbrStudent = 0; // ETUDIANT DANS LE FICHIER:

    while (fscanf(listEtudiants, "%s %s",
                  studentName, studentCode) == 2)
    {
        strcpy(studentList[nbrStudent], studentCode);
        strcpy(studentList[nbrStudent + 1], studentName);
        nbrStudent += 2;
    }
    fclose(listEtudiants);

    char codeStudentSaisi[50];
    int codeValid;
    struct tm *temps_info;
    time_t now;

    do
    {
        printf("Entrez votre code\n");
        printf(" => ");
        scanf("%s", codeStudentSaisi);

        // if(strcmp(codeStudentSaisi, "Q")==0)
        // break;

        codeValid = 0;
        for (int i = 0; i < nbrStudent; i += 2)
        {
            if (strcmp(studentList[i], codeStudentSaisi) == 0)
            {
                codeValid = 1;
                now = time(NULL);
                temps_info = localtime(&now);
                char date[100];

                sprintf(date, "%02d/%02d/%02d", temps_info->tm_mday, temps_info->tm_mon + 1, temps_info->tm_year + 1900);

                fseek(listPresences, 0, SEEK_SET);

                int isSaved = 0;

                char line[100];
                while (fgets(line, sizeof(line), listPresences) != NULL)
                {
                    char studentNameFile[100], dateFile[100];
                    sscanf(line, "%*[^,],%*[^,],%49[^,],%49[^,]", studentNameFile, dateFile);
                    if (strcmp(studentNameFile, studentList[i + 1]) == 0 && strcmp(dateFile, date) == 0)
                    {
                        isSaved = 1;
                        break;
                    }
                }
                if (isSaved)
                {
                    printf("vous vous êtes déjà enregistré pour aujourd'hui.\n");
                }
                else
                {
                    printf("Vous êtes Présent à %02d:%02d:%02d\n", temps_info->tm_hour, temps_info->tm_min, temps_info->tm_sec);
                    fprintf(listPresences, "%s,%s,%02d/%02d/%02d,%02d:%02d\n", studentList[i + 1], codeStudentSaisi, temps_info->tm_mday, temps_info->tm_mon + 1, temps_info->tm_year + 1900, temps_info->tm_hour, temps_info->tm_min);
                }
                break;
            }
        }
        if (!codeValid)
        {
            printf("Votre code est invalide\n");
        }

    } while (1);
    fclose(listPresences);
}
// FONCTIONS POUR GÉNÉRER FICHIERS:
void fichierToutesPresences()
{
    printf("--------- Voici la liste de toutes les présences : -----------\n");
    printf("\n");
    printf("\t");

    FILE *presences = fopen("presences.txt", "r");
    if (presences == NULL)
    {
        printf("Fichier Introuvable...");
    }

    char listPresence[LONG_MAX][50];
    char presentName[50];
    char presentCode[50];
    int nbrPresence = 0;

    while (fscanf(presences, "%s %s", presentName, presentCode) == 2)
    {
        // backHome();
        strcpy(listPresence[nbrPresence], presentCode);
        strcpy(listPresence[nbrPresence], presentCode);
        nbrPresence += 2;
        printf("%s\t \n\n %s\t\n\n", presentName, presentCode);
    }
    fclose(presences);

    int backMenu;
    printf("Taper 1 pour retourner au menu...\n");
    printf(" => ");
    scanf("%d", &backMenu);

    while (backMenu != 1)
    {
        printf("Choix invalide");
    }

    if (backMenu == 1)
    {
        backHome();
        adminMenu();
    }
}

void presencesParDate()
{
    char date[11]; // Format j/m/a (ex: 10/3/2024)
    char line[MAX_LENGTH];
    FILE *file;

    // Demande à l'utilisateur de saisir une date
    printf("Veuillez entrer une date au format j/m/a : ");
    scanf("%10s", date); // Lecture de la date saisie par l'utilisateur

    // Ouvre le fichier
    file = fopen("presences.txt", "r");

    if (file == NULL)
    {
        printf("Erreur: Impossible d'ouvrir le fichier.\n");
    }

    printf("Lignes correspondant à la date %s :\n", date);

    // Parcours du fichier ligne par ligne
    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Vérifie si la ligne contient la date spécifiée
        if (strstr(line, date) != NULL)
        {
            printf("%s", line); // Affiche la ligne si la date est
            adminMenu();
        }
        else
        {
            printf("Aucune correspondance pour cette date\n");
            // backHome();
            // adminMenu();
        }
    }

    fclose(file); // Ferme le fichier
}

int optionsFichier()
{
    int option;
    printf("---------------------GÉNÉRER FICHIER-----------------\n");
    printf("1: TOUTES LES PRÉSENCES\n");
    printf("2: PRÉSENCES PAR DATE\n");
    printf(" => ");
    scanf("%d", &option);

    while (option != 1 && option != 2 && option != 0)
    {
        printf("Cette option est invalide réessayez\n");
        printf("1: TOUTES LES PRÉSENCES\n");
        printf("2: PRÉSENCES PAR DATE\n");
        printf("0: Annuler\n");
        printf(" => ");
        scanf("%d", &option);
    }
    if (option == 1)
    {
        fichierToutesPresences();
    }
    else if (option == 2)
    {
        presencesParDate();
    }
    else
    {
        backHome();
    }
}

void msgToAll()
{
    backHome();
    char message[200];
    int confirm;

    printf("\t  Saisir message...\n ");
    scanf("%s", message);

    printf("Tapez 1 pour confirmer ou 0 pour annuler\n");
    printf(" => ");
    scanf("%d", &confirm);

    switch (confirm)
    {
    case 1:
        printf("Message envoyé à tous les étudiants avec succès\n");
        adminMenu();
        break;
    case 2:
        printf("Annulation validée\n");
        adminMenu();
        break;

    default:
        printf("Choix invalid\n");
        adminMenu();
        break;
    }

    /*
    if (confirm == 1)
    {
        printf("Message envoyé à tous les étudiants avec suucès!");
    }
    else if (confirm == 0)
    {
        backHome();
    }
    else
    {
        printf("Choix invalide");
    }
    */ 
}

void msgToClassroom()
{
    backHome();
    char classTarget[60];
    char classRoom1[50] = ("dev-web");
    char classRoom2[50] = ("ref-dig");
    char classRoom3[50] = ("dev-data");
    char message[200];

    printf("Saisir la classe destinatrice (dev-web / ref-dig / dev-data) : \n");
    printf(" => ");
    scanf("%s", classTarget);

    if (strcmp(classTarget, classRoom1) == 1 && strcmp(classTarget, classRoom2) == 1 && strcmp(classTarget, classRoom3) == 1)
    {
        printf("Cette classe n'existe pas");
    }
    else
    {
        printf("Saisir message pour les étudiants %s : \n", classTarget);
        printf(" ... ");
        scanf("%s", message);
        printf("Message envoyé aux %s avec succès\n", classTarget);
        adminMenu();
    }

}

void msgPerso()
{
    backHome();
    printf("Envoi message personnel");
}

void selectMessageType()
{
    int msgType;
    printf("Choisir destinataire(s) \n");
    printf("\t 1: Message à tous les étudiants \n");
    printf("\t 2: Message par classe \n");
    printf("\t 3: Message Personnel\n");
    printf("\t => ");
    scanf("%d", &msgType);

    switch (msgType)
    {
    case 1:
        msgToAll();
        break;

    case 2:
        msgToClassroom();
        break;

    case 3:
        msgPerso();
        break;

    default:
        printf("Option destinataire invalide\n");
        break;
    }
}

//------------------LES DIFFERENTS MENUS:
// MENU ADMIN:
void adminMenu()
{
    int adminOption;
    printf("\n");
    printf("    \t----------------   INTERFACE ADMIN   ------------------------\n");
    printf("\n");
    printf("1: GESTION DES ÉTUDIANTS\n");
    printf("2: GENERATION DE FICHIERS\n");
    printf("3: MARQUER LES PRÉSENCES\n");
    printf("4: ENVOYER UN MESSAGE\n");
    printf("5: QUITTER\n");
    printf("\t--------------------------------------------\n");
    printf(" => ");
    scanf("%d", &adminOption);

    switch (adminOption)
    {
    case 1:
        printf("Gestion des étudiant (en cours...)\n");
        backHome();
        saisiUserLogin();
        break;
    case 2:
        optionsFichier();
        break;
    case 3:
        backHome();
        marquerPresenceAdmin();
        break;
    case 4:
        backHome();
        selectMessageType();
        break;
    case 5:
        backHome();
        saisiUserLogin();
        break;

    default:
        printf("Option invalide\n");
        break;
    }
}

// MENU STUDENT:
void studentMenu(void)
{
    int studentOption;
    printf("\t--------------------  INTERFACE ÉTUDIANT  --------------------\n");
    printf("\n");
    printf("1: MARQUER MA PRÉSENCE\n");
    printf("2: NOMBRE DE MINUTES D'ABSENCE\n");
    printf("3: MES MESSAGES\n");
    printf("4: QUITTER\n");
    printf(" => ");
    scanf("%d", &studentOption);

    switch (studentOption)
    {
    case 1:
        backHome();
        marquerPresenceStudent();
        break;
    case 2:
        printf("Mon cumul de retard\n");
        break;
    case 3:
        printf("Boite de réception");
        break;
    case 4:
        backHome();
        break;
    default:
        printf("Option invalide\n");
        break;
    }
}

//--------------------FONCTIONS:--------------------

// SAISI ACCES:
void saisiUserLogin()
{
    char userPseudoSaisi[5];
    char userPassSaisi[5];
    char userProfil[LONG_MAX] = "";
    //...
    //...
    char userAdmin[100];
    strcpy(userAdmin, "admin");
    char userStudent[100];
    strcpy(userStudent, "student");
    char nomFichier[] = "allUsers.txt";

    FILE *allUsers = fopen(nomFichier, "r");
    if (allUsers == NULL)
        printf("Fichier introuvable");

    // SAISIE DE L'UTILISATEUR:

    printf("  -----------CONNECTEZ-VOUS----------- \n");
    printf("\n");

    printf("Entrez Pseudo: ");
    scanf("%s", userPseudoSaisi);
    printf("Entrez mot de passe: ");
    scanf("%s", userPassSaisi);

    // RECHERCHE DANS LE FICHIER:
    char ligne[MAX_LENGTH * 2];
    int isUserFounded = 0;

    while (fgets(ligne, sizeof(ligne), allUsers) != NULL)
    {

        char *jeton = strtok(ligne, ",");
        char *nomFichier = jeton;
        jeton = strtok(NULL, ",");
        // char *numeroFichier = jeton;
        char *motDePassFichier = jeton;
        jeton = strtok(NULL, ",");
        char *profilFichier = jeton;

        // Suppression saut de ligne de fgets
        if (profilFichier != NULL && profilFichier[strlen(profilFichier) - 1] == '\n')
        {
            profilFichier[strlen(profilFichier) - 1] = '\0';
        }

        if (strcmp(userPseudoSaisi, nomFichier) == 0 && strcmp(userPassSaisi, motDePassFichier) == 0)
        {
            isUserFounded = 1;
            strcpy(userProfil, profilFichier);
            break;
        }
    }

    // TRAITEMENT APRES PERCOURS DU FICHIER:

    if (!isUserFounded)
    {
        printf("Utilisateur non trouvé");
    }
    else
    {
        if (strcmp(userProfil, "admin") == 0)
        {
            adminMenu();
        }
        else if (strcmp(userProfil, "student") == 0)
        {
            studentMenu();
        }
        else
        {
            printf("Profil Inconnu");
        }
    }

    fclose(allUsers);
}
