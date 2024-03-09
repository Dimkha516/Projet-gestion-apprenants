#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
    printf("--------- A BIENTÔT..... -----------\n");
    // #endif
}

//  MARQUER PRESENCE:
void marquerPresenceAdmin()
{

    FILE *listEtudiants = fopen("studentUser.txt", "r");
    if (listEtudiants == NULL)
    {
        printf("Fichier liste étudiants introuvable...");
    }
    FILE *listPresences = fopen("presences.txt", "a");
    if (listPresences == NULL)
    {
        printf("Fichier liste présences introuvable...");
    }

    char studentList[LONG_MAX][50]; // ZONE STOCKAGE DES ETUDIANTS:
    char codeStudentSaisi[50];
    char studentName[50];
    char studentCode[50];
    char codeStudentFichier[50];
    int codeValid;
    struct tm *temps_info;
    time_t now;
    int nbrStudent = 0; // ETUDIANT DANS LE FICHIER:

    while (fscanf(listEtudiants, "%s"
                                 "%s",
                  studentName, studentCode) == 2)
    {
        strcpy(studentList[nbrStudent], studentCode);
        nbrStudent++;
    }
    fclose(listEtudiants);

    do
    {
        printf("Entrez le code étudiant (Q pour annuler): ");
        scanf("%s", codeStudentSaisi);

        codeValid = 0;
        for (int i = 0; i < nbrStudent; i++)
        {
            if (strcmp(studentList[i], codeStudentSaisi) == 0)
            {
                codeValid = 1;
                break;
            }
        }
        if (codeValid)
        {
            now = time(NULL);
            temps_info = localtime(&now);
            printf("Présence enregistrée à %02d:%02d:%02d\n", temps_info->tm_hour, temps_info->tm_min, temps_info->tm_sec);
            fprintf(listPresences, "L'étudiant %s est présent à l'heure %02d:%02d:%02d\n", studentName, temps_info->tm_hour, temps_info->tm_min, temps_info->tm_sec);
        }
        else if (strcmp(codeStudentSaisi, "Q") != 0)
        {
            printf("Code étudiant invalide\n");
        }

    } while (strcmp(codeStudentSaisi, "Q") != 0);
}

//------------------LES DIFFERENTS MENUS:
// MENU ADMIN:
void adminMenu()
{
    int adminOption;
    printf("----------------BIENVENU ADMIN------------------------\n");
    printf("1: GESTION DES ÉTUDIANT\n");
    printf("2: GENERATION DE FICHIERS\n");
    printf("3: MARQUER LES PRÉSENCES\n");
    printf("4: ENVOYER UN MESSAGE\n");
    printf("5: QUITTER\n");
    printf(" => ");
    scanf("%d", &adminOption);

    switch (adminOption)
    {
    case 1:
        printf("Gestion des étudiant (en cours...)\n");
        break;
    case 2:
        printf("Générer fichier (en cours...)\n");
        break;
    case 3:
        marquerPresenceAdmin();
        break;
    case 4:
        printf("Envoyer message(en cours...)\n");
        break;
    case 5:
        backHome();
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
    printf("----------------BIENVENU APPRENANT------------------------\n");
    printf("1: MARQUER MA PRÉSENCE\n");
    printf("2: NOMBRE DE MINUTES D'ABSENCE\n");
    printf("3: MES MESSAGES\n");
    printf("4: QUITTER\n");
    printf(" => ");
    scanf("%d", &studentOption);
    if (studentOption == 4)
    {
        backHome();
    }
}

//--------------------FONCTIONS:--------------------

// SAISI ACCES:
void saisiUserLogin()
{
    char userPseudoSaisi[LONG_MAX];
    char userPassSaisi[LONG_MAX];
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

    // PARCOURS DU FICHIER POUR RECUPÉRER LE PROFIL DE L'UTILISATEUR:

    // SAISIE DE L'UTILISATEUR:
    printf("  -----------CONNECTEZ-VOUS----------- \n");
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

// CONTROLE SAISI ACCES

/*
void loginValidate(char pseudo[50], int password){
}
*/

//-----------------------------DIFFERENTS MENUS----------------------

/*
LE MOT PASSE LE CACHÉ
MARQUER PRESENCE COTE ADMIN (entrez votre code Q pour quitter)
*/