/**
 * @file Main.c
 * @author João Meira & Guilherme Azeredo
 * @brief
 * @version 1.1
 *
 * @copyright Copyright (c) 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <errno.h>
#include <time.h>
#include <locale.h>

#include "Header.h"

#ifdef _WIN32
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

int main()
{
    setlocale(LC_ALL, "Portuguese");

    int option;
    do {
        // Load the data from the file
        struct Practitioner practitioners[MAX_PRACTITIONERS];
        struct Activity activities[MAX_ACTIVITIES];
        struct ActivityPlan activityPlans[MAX_ACTIVITY_PLANS];

        int numPractitioners = loadPractitioners(practitioners, MAX_PRACTITIONERS);
        int numActivities = loadActivities(activities, MAX_ACTIVITIES);
        int numActivityPlans = loadActivityPlans(activityPlans, MAX_ACTIVITY_PLANS);

        // Display the menu
        printf("\n\t\tMenu:\n\n");
        printf("\tPraticantes:\n");
        printf("1  - Adicionar um novo Praticante.\n");
        printf("2  - Eliminar um Praticante.\n");
        printf("3  - Listar os Praticantes.\n\n");
        printf("\tAtividades:\n");
        printf("4  - Adicionar uma nova Atividade.\n");
        printf("5  - Eliminar uma Atividade.\n");
        printf("6  - Listar as Atividades.\n\n");
        printf("\tPlanos de Atividades:\n");
        printf("7  - Adicionar um novo Plano de Atividade.\n");
        printf("8  - Eliminar um Plano de Atividades.\n");
        printf("9  - Listar os Planos de Atividades.\n\n");
        printf("\tExercicios:\n");
        printf("10 - Numero de Praticantes que realizaram uma determinada atividade.\n");
        printf("11 - Lista de praticantes por determinada atividade.\n");
        printf("12 - Lista de planos de atividade.\n");
        printf("13 - Calcular tempos total e médio.\n");
        printf("14 - Gerar tabela de atividades.\n");
        printf("15 - Listagem de praticantes e seguidores.\n");
        printf("16 - Lista por atividade com o praticante com o maior tempo de prática da mesma, e o respectivo tempo, entre os seguidores de um determinado praticante.\n");
        printf("17 - Lista por atividade com o praticante com o maior tempo de prática da mesma, e o respectivo tempo, entre os praticantes seguidos por um determinado praticante.\n\n");
        printf(" 0 - Sair\n\n");
        printf("\nInsira uma opção: ");

        // Read the user's choice
        scanf("%d", &option);

        // Perform the selected action
        switch (option) {
        case 0:
            // Quit
            break;
        case 1:
            // Add a new practitioner
            if (numPractitioners < MAX_PRACTITIONERS) {
                int result = addPractitioner(practitioners, numPractitioners);
                if (result == 0) {
                printf("Praticante adicionado com sucesso!\n");
                numPractitioners++;
                } else {
                printf("Erro ao adicionar praticante.\n");
                }
            } else {
                printf("Não é possível adicionar mais praticantes. O limite máximo foi atingido.\n");
            }
            break;
        case 2:
            // Delete a practitioner
            printf("\nLista de Praticantes:\n");
            displayPractitioners(practitioners, numPractitioners);
            printf("Insira o número do praticante a eliminar: ");
            int practitionerNumber;
            scanf("%d", &practitionerNumber);
            int result = deletePractitioner(practitioners, numPractitioners, practitionerNumber);
            if (result == 0) {
                printf("Praticante eliminado com sucesso.\n");
                numPractitioners--;
            } else {
                printf("Praticante não encontrado.\n");
            }
            break;
        case 3:
            // List practitioners
            printf("\nLista de Praticantes:\n");
            displayPractitioners(practitioners, numPractitioners);
            break;
        case 4:
            // Add a new activity
            if (numActivities < MAX_ACTIVITIES) {
                int result = addActivity(activities, numActivities, practitioners, numPractitioners);
                if (result == 0) {
                    printf("Atividade adicionada com sucesso!\n");
                    numActivities++;
                } else {
                    printf("Erro ao adicionar atividade.\n");
                }
            } else {
                printf("Não é possível adicionar mais atividades. O limite máximo foi atingido.\n");
            }
            break;
        case 5:
            // Delete an activity
            printf("\nLista de Atividades:\n");
            displayActivities(activities, numActivities);
            printf("Insira o número do praticante da atividade a eliminar: ");
            scanf("%d", &practitionerNumber);

            result = deleteActivity(activities, numActivities, practitionerNumber);
            if (result == 0) {
                printf("Atividade eliminada com sucesso!\n");
                numActivities--;
            } else {
                printf("Erro ao eliminar atividade.\n");
            }
            break;
        case 6:
            // List activities
            printf("\nLista de Atividades:\n");
            displayActivities(activities, numActivities);
            break;
        case 7:
            // Add a new activity plan
            if (numActivityPlans < MAX_ACTIVITY_PLANS) {
            int result = addActivityPlan(activityPlans, numActivityPlans, practitioners, numPractitioners);
                if (result == 0) {
                printf("Plano de atividade adicionado com sucesso!\n");
                numActivityPlans++;
                } else {
                printf("Erro ao adicionar plano de atividade.\n");
                }
            } else {
                printf("Não é possível adicionar mais planos de atividades. O limite máximo foi atingido.\n");
            }
            break;
        case 8:
            // Delete an activity plan
            printf("\nLista de Planos de Atividades:\n");
            displayActivityPlans(activityPlans, numActivityPlans);
            printf("Insira o número do plano de atividade a eliminar: ");
            int activityPlanNumber;
            scanf("%d", &activityPlanNumber);
            result = deleteActivityPlan(activityPlans, numActivityPlans, activityPlanNumber);
            if (result == 0) {
                printf("Plano de atividade eliminado com sucesso!\n");
                numActivityPlans--;
            } else {
                printf("Erro ao eliminar o plano de atividade.\n");
            }
            break;
        case 9:
            // List activity plans
            printf("\nLista de Planos de Atividades:\n");
            displayActivityPlans(activityPlans, numActivityPlans);
        case 10:
            // Count practitioners by activity
            printf("Insira o nome da atividade: ");
            char activityName[MAX_NAME_LEN];
            scanf("%s", activityName);

            printf("Insira a data de inicio (formato dd/mm/aaaa): ");
            char startDate[MAX_NAME_LEN];
            scanf("%s", startDate);

            printf("Insira a data de fim (formato dd/mm/aaaa): ");
            char endDate[MAX_NAME_LEN];
            scanf("%s", endDate);

            int count = countPractitionersByActivity(practitioners, numPractitioners, activities, numActivities, activityName);
            printf("O numero de praticantes que realizaram a atividade '%s' entre as datas '%s' e '%s' é: %d\n", activityName, startDate, endDate, count);
            break;
        case 11:
            // List practitioners by activity, sorted in descending order of practitioner number
            listPractitionersByActivity(practitioners, numPractitioners, activities, numActivities);
            break;
        case 12:
            // List activity plans for a given practitioner
            listActivityPlans(practitioners, numPractitioners, activityPlans, numActivityPlans);
            break;
        case 13: 
            // Calculate total and average times
            calculateTotalAndAverageTimes(practitioners, numPractitioners, activities, numActivities);
            break;
        case 14:
            // Generate a table of activities
            generateActivityTable(practitioners, numPractitioners, activityPlans, numActivityPlans, activities, numActivities);
            break;
        case 15:
            // List practitioners and their followers
            printf("Não foi bem realizado, so aparece os praticantes");
            // listPractitionersAndFollowers(practitioners, numPractitioners);
            break;
        case 16:
            // Present a list by activity with the practitioner with the longest time of practice of that activity, and the respective time, among the followers of a certain practitioner defined by the user
            printf("Não foi bem realizado");
            // listLongestPractitionersByActivity(practitioners, numPractitioners, activities, numActivities, activityPlans, numActivityPlans);
            break;
        case 17:
            // Present a list by activity with the exerciser with the longest time practicing that activity, and the respective time, among the practitioners followed by a certain practitioner defined by the user
            printf("Não foi bem realizado");
            //listLongestFollowedPractitionersByActivity(practitioners, numPractitioners, activities, numActivities);
            break;
        default:
            printf("Opção Inválida.\n");
            break;
        }
    } while (option != 0);

    return 0;

}

