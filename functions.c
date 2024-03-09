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
    // #endif
}

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

        if(strcmp(codeStudentSaisi, "Q")==0)
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
                while(fgets(line, sizeof(line), listPresences)!=NULL){
                    char studentNameFile[100], dateFile[100];
                    sscanf(line,"%*[^,],%*[^,],%49[^,],%49[^,]",studentNameFile, dateFile);
                    if(strcmp(studentNameFile, studentList[i + 1])==0 && strcmp(dateFile, date)==0){
                        isSaved = 1;
                        break;
                    } 
                }
                if(isSaved){
                    printf("L'étudiant %s est déjà enregistré pour aujourd'hui.\n", studentList[i + 1]);
                }
                else{
                    printf("Présence enregistrée pour %s (code: %s) à %02d:%02d:%02d\n", studentList[i + 1], studentList[i], temps_info->tm_hour, temps_info->tm_min, temps_info->tm_sec);
                    fprintf(listPresences, "%s,%s,%02d/%02d/%02d,%02d:%02d\n", studentList[i + 1], codeStudentSaisi, temps_info->tm_mday, temps_info->tm_mon + 1, temps_info->tm_year + 1900, temps_info->tm_hour, temps_info->tm_min);
                }
                break;  
            }
        }
        if(!codeValid){
            printf("Code étudiant invalide\n");
        }

    } while (1);
    fclose(listPresences);
}

void marquerPresenceStudent(){
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
                while(fgets(line, sizeof(line), listPresences)!=NULL){
                    char studentNameFile[100], dateFile[100];
                    sscanf(line,"%*[^,],%*[^,],%49[^,],%49[^,]",studentNameFile, dateFile);
                    if(strcmp(studentNameFile, studentList[i + 1])==0 && strcmp(dateFile, date)==0){
                        isSaved = 1;
                        break;
                    } 
                }
                if(isSaved){
                    printf("vous vous êtes déjà enregistré pour aujourd'hui.\n");
                }
                else{
                    printf("Vous êtes Présent à %02d:%02d:%02d\n",temps_info->tm_hour, temps_info->tm_min, temps_info->tm_sec);
                    fprintf(listPresences, "%s,%s,%02d/%02d/%02d,%02d:%02d\n", studentList[i + 1], codeStudentSaisi, temps_info->tm_mday, temps_info->tm_mon + 1, temps_info->tm_year + 1900, temps_info->tm_hour, temps_info->tm_min);
                }
                break;  
            }
        }
        if(!codeValid){
            printf("Votre code est invalide\n");
        }

    } while (1);
    fclose(listPresences);
}

//------------------LES DIFFERENTS MENUS:
// MENU ADMIN:
void adminMenu()
{
    int adminOption;
    printf("----------------BIENVENU ADMIN------------------------\n");
    printf("1: GESTION DES ÉTUDIANTS\n");
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
        backHome();
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