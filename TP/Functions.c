/**
 * @file Functions.c
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

#include "header.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#pragma region Practitioners

 /// @brief Exibe as informações para uma determinada matriz de praticantes
 /// @param praticantes lista atual de praticantes
 /// @param numPractitioners número de praticantes no array
void displayPractitioners(const struct Practitioner *practitioners, int numPractitioners) {
  for (int i = 0; i < numPractitioners; i++) {
    printf("%d - %s - %s - %d anos\n", practitioners[i].number, practitioners[i].name, practitioners[i].phone, practitioners[i].age);
  }
}

/// @brief permite ao usuário adicionar um novo praticante ao array de praticantes
/// @param praticantes lista atual de praticantes
/// @param numPractitioners número de praticantes no array
/// @return novo número de praticantes. Se não houver espaço no array de praticantes para adicionar um novo praticante, a função retorna o número atual de praticantes
int addPractitioner(struct Practitioner *practitioners, int numPractitioners)
{
    // Verifica se há espaço no array para o novo praticante
    if (numPractitioners >= MAX_PRACTITIONERS)
    {
        printf("Error: Não é possível adicionar novo praticante, o array está cheio.\n");
        return numPractitioners;
    }

    // Lê a entrada do usuário
    char name[MAX_NAME_LEN];
    char phone[MAX_NAME_LEN];
    int age;

    printf("Insira o nome do praticante: ");
    scanf("%s", name);
    printf("Insira o numero de telemovel do praticante: ");
    scanf("%s", phone);
    printf("Insira a idade do praticante: ");
    scanf("%d", &age);

    // Atribui o próximo número disponível ao novo praticante
    int number = numPractitioners + 1;

    // Adiciona o novo praticante ao array
    practitioners[numPractitioners].number = number;
    strcpy(practitioners[numPractitioners].name, name);
    strcpy(practitioners[numPractitioners].phone, phone);
    practitioners[numPractitioners].age = age;

    savePractitioners(practitioners, numPractitioners + 1); // Salva o array de praticantes atualizado no arquivo

    return numPractitioners + 1; // Retorna o novo número de praticantes
}

/// @brief permite que o usuário exclua um praticante no array de praticantes
/// @param praticantes lista atual de praticantes
/// @param numPractitioners número de praticantes no array
/// @param practitionerNumber número do praticante a ser deletado
/// @return 0 se o praticante foi removido com sucesso do array e a lista atualizada foi salva no arquivo, e -1 se o praticante não foi encontrado no array in the array
int deletePractitioner(struct Practitioner *practitioners, int numPractitioners, int practitionerNumber) {
    // Encontra o praticante no array
  int i;
  for (i = 0; i < numPractitioners; i++) {
    if (practitioners[i].number == practitionerNumber) {
      break;
    }
  }

  // Se o praticante não foi encontrado, retorna -1
  if (i == numPractitioners) {
    return -1;
  }

  // Desloca os praticantes restantes na matriz para a esquerda para preencher a lacuna
  for (int j = i; j < numPractitioners - 1; j++) {
    practitioners[j] = practitioners[j + 1];
  }

  // Salva a lista atualizada de praticantes no arquivo
  savePractitioners(practitioners, numPractitioners - 1);

  return 0;
}

#pragma endregion Practitioners

#pragma region Activities

/// @brief exibe uma lista de atividades para o usuário
/// @param Activities array de atividades
/// @param numActivities integer numActivities representando o número de elementos no array de atividades
void displayActivities(const struct Activity *activities, int numActivities)
{
    for (int i = 0; i < numActivities; i++) {
        printf("%d - %s - %s - %s - %d minutos - %d %s\n", activities[i].practitionerNumber, activities[i].date, activities[i].name, activities[i].startTime, activities[i].duration, activities[i].distance, activities[i].units);
    }
}

/// @brief permite ao usuário adicionar uma nova atividade ao array de atividades
/// @param Activities array de atividades
/// @param numActivities integer numActivities representando o número de elementos no array de atividades
/// @param array praticantes de struct Practitioner
/// @param numPractitioners inteiro chamado numPractitioners que representa o número de elementos no array praticantes
/// @return Se o elemento com o campo de número correspondente foi encontrado, a função retorna 0. Se o elemento não foi encontrado, a função retorna -1
int addActivity(struct Activity *activities, int numActivities, const struct Practitioner *practitioners, int numPractitioners)
{
    // Verifica se há espaço no array para a nova atividade
    if (numActivities >= MAX_ACTIVITIES)
    {
        printf("Error: Não é possível adicionar nova atividade, o array está cheio.\n");
        return numActivities;
    }

    // Lê a entrada do usuário
    int practitionerNumber;
    char date[MAX_NAME_LEN];
    char name[MAX_NAME_LEN];
    char startTime[MAX_NAME_LEN];
    int duration;
    int distance;
    char units[MAX_NAME_LEN];

    printf("Insira o número do praticante: ");
    scanf("%d", &practitionerNumber);

    // Verifica se o praticante existe
    int practitionerFound = 0;
    for (int i = 0; i < numPractitioners; i++)
    {
        if (practitioners[i].number == practitionerNumber)
        {
            practitionerFound = 1;
            break;
        }
    }

    if (!practitionerFound)
    {
        printf("Error: O praticante com número %d não existe.\n", practitionerNumber);
        return numActivities;
    }

    printf("Insira a data: ");
    scanf("%s", date);
    printf("Insira o nome da atividade: ");
    scanf("%s", name);
    printf("Insira a hora de início: ");
    scanf("%s", startTime);
    printf("Insira a duração (em minutos): ");
    scanf("%d", &duration);
    printf("Insira a distância (em metros): ");
    scanf("%d", &distance);
    printf("Insira as unidades (metros ou milhas): ");
    scanf("%s", units);

    saveActivities(activities, numActivities + 1); // Salva o array de atividades atualizado no arquivo

    // Adiciona a nova atividade ao array
    activities[numActivities].practitionerNumber = practitionerNumber;
    strcpy(activities[numActivities].name, name);
    strcpy(activities[numActivities].date, date);
    strcpy(activities[numActivities].startTime, startTime);
    activities[numActivities].duration = duration;
    activities[numActivities].distance = distance;
    strcpy(activities[numActivities].units, units);

    return numActivities + 1; // Retorna o novo número de atividades
}

/// @brief permite ao usuário deletar uma atividade no array de atividades
/// @param Activities array de atividades
/// @param numActivities integer numActivities representando o número de elementos no array de atividades
/// @param praticanteNumber integer praticanteNumber
/// @return 0 se a atividade foi excluída com sucesso ou -1 se a atividade não foi encontrada no array
int deleteActivity(struct Activity *activities, int numActivities, int practitionerNumber)
{
    // Encontra a atividade no array
    int i;
    for (i = 0; i < numActivities; i++)
    {
        if (activities[i].practitionerNumber == practitionerNumber)
        {
            break;
        }
    }

    // Se a atividade não foi encontrada, retorna -1
    if (i == numActivities)
    {
        return -1;
    }

    // Desloca as atividades restantes no array para a esquerda para preencher a lacuna

    for (int j = i; j < numActivities - 1; j++)
    {
        activities[j] = activities[j + 1];
    }

    saveActivities(activities, numActivities - 1); // Salva o array de atividades atualizado no arquivo

    return 0;
}

#pragma endregion Activities

#pragma region ActivityPlans

/// @brief exibe uma lista de planos de atividades para o usuário
/// @param planes ponteiro para um array de estruturas ActivityPlan representando uma lista de planos de atividades
/// @param numPlans integer representando o número de planos de atividades no array de planos
void displayActivityPlans(const struct ActivityPlan *plans, int numPlans){
    for (int i = 0; i < numPlans; i++) {
        printf("%d - %s %s - %s %s - %s - %d %s\n", plans[i].practitionerNumber, plans[i].startDate, plans[i].startTime, plans[i].endDate, plans[i].endTime, plans[i].activity, plans[i].distance, plans[i].units);
    }
}

/// @brief permite ao usuário adicionar um novo plano de atividades ao array de activityPlan
/// @param plan aponta para um array de planos de atividades
/// @param numPlans número de planos de atividades atualmente no array
/// @param praticantes ponteiro para um array de praticantes
/// @param numPractitioners número de praticantes no array
/// @return numPlans + 1 se um novo plano de atividades foi adicionado ao array, ou numPlans se ocorreu um erro ou o array já estava cheio
int addActivityPlan(struct ActivityPlan *plans, int numPlans, const struct Practitioner *practitioners, int numPractitioners){
    // Verifica se há espaço no array para o novo plano de atividades
    if (numPlans >= MAX_ACTIVITY_PLANS)
    {
        printf("Error: Não é possível adicionar um novo plano de atividades, o array está cheio.\n");
        return numPlans;
    }

    // Lê a entrada do usuário
    int practitionerNumber;
    char startDate[MAX_NAME_LEN];
    char startTime[MAX_NAME_LEN];
    char endDate[MAX_NAME_LEN];
    char endTime[MAX_NAME_LEN];
    char activity[MAX_NAME_LEN];
    int distance;
    char units[MAX_NAME_LEN];

    printf("\nIntroduza o número do praticante: ");
    scanf("%d", &practitionerNumber);

    // Verifica se o praticante com o número informado existe
    int found = 0;
    for (int i = 0; i < numPractitioners; i++)
    {
        if (practitioners[i].number == practitionerNumber)
        {
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Error: O praticante com o número %d não existe.\n", practitionerNumber);
        return numPlans;
    }

    printf("Insira a data de inicio (dd/mm/aaaa): ");
    scanf("%s", startDate);
    printf("Insira a hora de inicio (hh:mm): ");
    scanf("%s", startTime);
    printf("Insira a data de fim (dd/mm/aaaa): ");
    scanf("%s", endDate);
    printf("Insira a hora de fim (hh:mm): ");
    scanf("%s", endTime);
    printf("Insira o nome da atividade: ");
    scanf("%s", activity);
    printf("Insira a distância percorrida: ");
    scanf("%d", &distance);
    printf("Insira a unidade de medida (km ou mi): ");
    scanf("%s", units);

    // Atribuir o próximo número disponível ao novo plano de atividades
    int activityPlanNumber = numPlans + 1;

    // Adiciona o novo plano de atividades ao array
    plans[numPlans].activityPlanNumber = activityPlanNumber;
    plans[numPlans].practitionerNumber = practitionerNumber;
    strcpy(plans[numPlans].startDate, startDate);
    strcpy(plans[numPlans].startTime, startTime);
    strcpy(plans[numPlans].endDate, endDate);
    strcpy(plans[numPlans].endTime, endTime);
    strcpy(plans[numPlans].activity, activity);
    plans[numPlans].distance = distance;
    strcpy(plans[numPlans].units, units);

    saveActivityPlans(plans, numPlans + 1); // Salve o array do plano de atividades atualizado no arquivo

    return numPlans + 1; // Retorna o novo número de planos de atividades
}

/// @brief permite ao usuário deletar um plano de atividades no array de activityPlan
/// @param activityPlans Um ponteiro para uma matriz de estruturas ActivityPlan
/// @param numActivityPlans um inteiro indicando o número de estruturas ActivityPlan no array
/// @param activityPlanNumber um número inteiro representando o número do plano de atividades a ser excluído
/// @return inteiro indicando se a operação foi bem sucedida ou não. Se a função for bem-sucedida, ela retorna 0. Se falhar, ela retorna -1
int deleteActivityPlan(struct ActivityPlan *activityPlans, int numActivityPlans, int activityPlanNumber) {
    // Encontra o plano de atividades no array
  int i;
  for (i = 0; i < numActivityPlans; i++) {
    if (activityPlans[i].activityPlanNumber == activityPlanNumber) {
      break;
    }
  }

  // Se o plano de atividades não foi encontrado, retorna -1
  if (i == numActivityPlans) {
    return -1;
  }

  // Desloca os planos de atividades restantes no array para a esquerda para preencher a lacuna
  for (int j = i; j < numActivityPlans - 1; j++) {
    activityPlans[j] = activityPlans[j + 1];
  }

  saveActivityPlans(activityPlans, numActivityPlans - 1); // Salve o array do plano de atividades atualizado no arquivo

  return 0;
}

#pragma endregion ActivityPlans

#pragma region Exercises

#pragma region Exercise 4

/// @brief conta o número de praticantes que realizaram uma determinada atividade
/// @param praticantes Um ponteiro para um array de objetos struct Practitioner
/// @param numPractitioners O número de elementos no array praticantes
/// @param Activities Um ponteiro para um array de objetos struct Activity
/// @param numActivities O número de elementos no array de atividades
/// @param activityName Uma string que representa o nome da atividade a ser procurada
/// @return um inteiro representando o número de praticantes que concluíram a atividade com o nome especificado
int countPractitionersByActivity(const struct Practitioner *practitioners, int numPractitioners, const struct Activity *activities, int numActivities, const char *activityName) {
    int count = 0;
    for (int i = 0; i < numActivities; i++)
    {
        if (strcmp(activities[i].name, activityName) == 0)
        {
            count++;
        }
    }
    return count;
}

#pragma endregion Exercise 10 (4)

#pragma region Exercise 5

/// Função de comparação @breve que pode ser passada para uma função como qsort para classificar uma matriz de números inteiros em ordem decrescente
/// @param a ponteiros para inteiros
/// @param b ponteiros para inteiros
/// @retorna um inteiro
int compareIntDescending(const void *a, const void *b) {
  int *x = (int *)a;
  int *y = (int *)b;
  return *y - *x;
}

/// @brief lista os nomes dos praticantes que fizeram uma atividade específica, em ordem decrescente de número de praticante
/// @param praticantes ponteiro para um array de structs Practitioner, representando a lista de praticantes
/// @param numPractitioners um inteiro, representando o número de praticantes na lista
/// @param Activities um ponteiro para um array de Activity structs, representando a lista de atividades
/// @param numActivities um inteiro, representando o número de atividades na lista
void listPractitionersByActivity(const struct Practitioner *practitioners, int numPractitioners, const struct Activity *activities, int numActivities) {
  char activity[MAX_NAME_LEN];
  printf("\nIntroduza o nome da atividade: ");
  scanf("%s", activity);

  // Cria um array para armazenar os números dos praticantes da atividade selecionada
  int practitionerNumbers[MAX_PRACTITIONERS];
  int numPractitionersForActivity = 0;

  // Encontra todos os praticantes que fizeram a atividade selecionada
  for (int i = 0; i < numActivities; i++) {
    if (strcmp(activities[i].name, activity) == 0) {
      practitionerNumbers[numPractitionersForActivity] = activities[i].practitionerNumber;
      numPractitionersForActivity++;
    }
  }

  // Classifica os números dos praticantes em ordem decrescente
  qsort(practitionerNumbers, numPractitionersForActivity, sizeof(int), compareIntDescending);

  // Imprime os nomes dos praticantes que realizaram a atividade selecionada, em ordem decrescente de número de praticante
  printf("Praticantes que fizeram a atividade '%s':\n", activity);
  for (int i = 0; i < numPractitionersForActivity; i++) {
    int practitionerNumber = practitionerNumbers[i];
    for (int j = 0; j < numPractitioners; j++) {
      if (practitioners[j].number == practitionerNumber) {
        printf("%d - %s\n", practitioners[j].number, practitioners[j].name);
      }
    }
  }
}

#pragma endregion Exercise 11 (5)

#pragma region Exercise 6

/// @brief exibe uma lista de praticantes e solicita ao usuário que insira um número de praticante, então exibe os planos de atividade para o praticante selecionado
/// @param ponteiro dos praticantes para uma matriz de estruturas Practitioner
/// @param numPractitioners inteiro representando o número de elementos no array de praticantes
/// @param activityPlans ponteiro para um array de estruturas ActivityPlan
/// @param numActivityPlans integer representando o número de elementos no array activityPlans
void listActivityPlans(const struct Practitioner *practitioners, int numPractitioners, const struct ActivityPlan *activityPlans, int numActivityPlans) {
  printf("\nLista de Praticantes:\n");
  displayPractitioners(practitioners, numPractitioners);
  printf("\nInsira o número do Praticante: ");
  int practitionerNumber;
  scanf("%d", &practitionerNumber);

  printf("\nPlano de atividades:\n");
  for (int i = 0; i < numActivityPlans; i++) {
    if (activityPlans[i].practitionerNumber == practitionerNumber) {
      printf("%s - %s - %s - %s - %s - %d %s\n", activityPlans[i].startDate, activityPlans[i].startTime, activityPlans[i].endDate, activityPlans[i].endTime, activityPlans[i].activity, activityPlans[i].distance, activityPlans[i].units);
    }
  }
}

#pragma endregion Exercise 12 (6)

#pragma region Exercise 7

/// @brief exibe os tempos totais e médios de um praticante selecionado calculando a soma e a média das durações das atividades realizadas pelo praticante
/// @param praticantes aponta para um array de estruturas Practitioner. Esta matriz contém informações sobre os praticantes
/// @param numPractitioners inteiro representando o número de praticantes no array de praticantes
/// @param Activities ponteiro para um array de estruturas Activity. Esta matriz contém informações sobre as atividades realizadas pelos praticantes
/// @param numActivities inteiro representando o número de atividades no array de atividades
void calculateTotalAndAverageTimes(const struct Practitioner *practitioners, int numPractitioners, const struct Activity *activities, int numActivities) {
    // Obtém o número do praticante do usuário
  printf("\nLista de Praticantes:\n");
  displayPractitioners(practitioners, numPractitioners);
  int practitionerNumber;
  printf("\nIntroduza o número do praticante: ");
  scanf("%d", &practitionerNumber);

  // Encontra o praticante com o número indicado
  int practitionerIndex = -1;
  for (int i = 0; i < numPractitioners; i++) {
    if (practitioners[i].number == practitionerNumber) {
      practitionerIndex = i;
      break;
    }
  }

  if (practitionerIndex == -1) {
    printf("Praticante com número %d não foi ncontrado.\n", practitionerNumber);
    return;
  }

  // Calcula os tempos totais e médios do praticante
  int totalTime = 0;
  int numActivitiesForPractitioner = 0;
  for (int i = 0; i < numActivities; i++) {
    if (activities[i].practitionerNumber == practitionerNumber) {
      totalTime += activities[i].duration;
      numActivitiesForPractitioner++;
    }
  }
  float averageTime = (float)totalTime / numActivitiesForPractitioner;

  // Imprime os resultados
  printf("Tempo total para o praticante %d foi de: %d minutos\n", practitionerNumber, totalTime);
  printf("Tempo médio para o praticante %d foi de: %.2f minutos\n", practitionerNumber, averageTime);
}

#pragma endregion Exercise 13 (7)

#pragma region Exercise 8

/// @brief primeiro imprime o cabeçalho da tabela. Em seguida, itera sobre cada praticante e suas atividades planejadas e imprime as informações da atividade planejada
/// @param praticantes array de structs contendo informações sobre cada praticante
/// @param numPractitioners número de praticantes no array
/// @param activityPlans array de structs contendo informações sobre as atividades planejadas para cada praticante
/// @param numActivityPlans número de atividades planejadas no array
/// @param Activities array de structs contendo informações sobre as atividades realizadas para cada praticante
/// @param numActivities número de atividades realizadas no array
void generateActivityTable(const struct Practitioner *practitioners, int numPractitioners, const struct ActivityPlan *activityPlans, int numActivityPlans, const struct Activity *activities, int numActivities) {
  printf("Numero do Praticante | Nome | Atividade Planeada | Medição Planeada | Valor Planeado | Atividade Realizada | Data de Início | Data Fim | Medição Realizada | Valor Realizado\n");
  printf("--------------------|------------------------|--------------------------|--------------------|----------------|----------------------------|-------------|-------------|------------------------|-------------------\n");

  for (int i = 0; i < numPractitioners; i++) {
    const struct Practitioner *practitioner = &practitioners[i];
    for (int j = 0; j < numActivityPlans; j++) {
      const struct ActivityPlan *activityPlan = &activityPlans[j];
      if (activityPlan->practitionerNumber == practitioner->number) {
          // Imprime as informações da atividade planejada
        printf("%d                   | %-20s | %-22s | %-18s | %-14d | ", practitioner->number, practitioner->name, activityPlan->activity, activityPlan->units, activityPlan->distance);

        // Encontra as informações da atividade realizada
        char carriedOutActivity[MAX_NAME_LEN];
        char startDate[MAX_DATE_LEN];
        char endDate[MAX_DATE_LEN];
        char carriedOutUnits[MAX_UNIT_LEN];
        int carriedOutDistance = 0;
        for (int k = 0; k < numActivities; k++) {
          const struct Activity *activity = &activities[k];
          if (activity->practitionerNumber == practitioner->number && strcmp(activity->name, activityPlan->activity) == 0 && strcmp(activity->date, activityPlan->startDate) >= 0 && strcmp(activity->date, activityPlan->endDate) <= 0) {
            strcpy(carriedOutActivity, activity->name);
            strcpy(startDate, activity->date);
            endDate[0] = '\0';
            strcpy(carriedOutUnits, activity->units);
            carriedOutDistance += activity->distance;
          }
        }

        // Imprime as informações da atividade realizada
        if (strlen(carriedOutActivity) > 0) {
          printf("%-22s | %-11s | %-11s | %-22s | %d\n", carriedOutActivity, startDate, endDate, carriedOutUnits, carriedOutDistance);
        } else {
          printf("                         |             |             |                         |\n");
        }
      }
    }
  }
}

#pragma endregion Exercise 14 (8)

#pragma region Exercise 9

/// @brief itera através do array "practitioners" e para cada praticante, imprime seu nome e número, seguido por uma lista dos praticantes que eles seguem
/// @param praticantes ponteiro para um array de estruturas "Practitioner"
/// @param numPractitioners integer representando o número de elementos no array "practitioners"
void displayFollows(const struct Practitioner *practitioners, int numPractitioners) {
  for (int i = 0; i < numPractitioners; i++) {
    const struct Practitioner *practitioner = &practitioners[i];
    printf("O praticante %d (%s) segue:\n", practitioner->number, practitioner->name);
    for (int j = 0; j < practitioner->numFollows; j++) {
      int followeeNumber = practitioner->follows[j];
      for (int k = 0; k < numPractitioners; k++) {
        if (practitioners[k].number == followeeNumber) {
          printf("  %d - %s\n", practitioners[k].number, practitioners[k].name);
        }
      }
    }
  }
}

/// @brief lista os praticantes e os seguidores de cada praticante
/// @param praticantes ponteiro para um array de struct Practitioner
/// @param numPractitioners integer representando o número de praticantes no array
void listPractitionersAndFollowers(const struct Practitioner *practitioners, int numPractitioners) {
  printf("Número do Praticante | Nome | Seguidores\n");
  printf("--------------------|------------------------|--------------------------\n");

  for (int i = 0; i < numPractitioners; i++) {
    const struct Practitioner *practitioner = &practitioners[i];
    printf("%d                   | %-20s | ", practitioner->number, practitioner->name);
    displayFollows(&practitioners[i], practitioner->numFollows);
    printf("\n");
  }
}

#pragma endregion Exercise 15 (9)

#pragma region Nao foram bem realizados
/*
#pragma region Exercise 10

void listLongestPractitionersByActivity(const struct Practitioner *practitioners, int numPractitioners, const struct Follow *follows, int numFollows, const struct Activity *activities, int numActivities) {
  // Get the practitioner number from the user
  printf("\nLista de Praticantes:\n");
  displayPractitioners(practitioners, numPractitioners);
  int practitionerNumber;
  printf("Introduza o número do praticante para ver os seus seguidores: ");
  scanf("%d", &practitionerNumber);

  // Find the practitioner with the given number
  int practitionerIndex = -1;
  for (int i = 0; i < numPractitioners; i++) {
    if (practitioners[i].number == practitionerNumber) {
      practitionerIndex = i;
      break;
    }
  }

  if (practitionerIndex == -1) {
    printf("Praticante com número %d não foi encontrado.\n", practitionerNumber);
    return;
  }

  // Find the followers of the practitioner
  int followers[MAX_FOLLOWERS];
  int numFollowers = 0;
  for (int i = 0; i < numFollows; i++) {
    if (follows[i].follower == practitionerNumber) {
      followers[numFollowers] = follows[i].followed;
      numFollowers++;
    }
  }

  if (numFollowers == 0) {
    printf("O praticante %d não tem seguidores.\n", practitionerNumber);
    return;
  }

  // Find the longest time for each activity among the followers
  int longestTimes[MAX_ACTIVITIES];
  char longestPractitioners[MAX_ACTIVITIES][MAX_NAME_LEN];
  for (int i = 0; i < numActivities; i++) {
    longestTimes[i] = 0;
    strcpy(longestPractitioners[i], "");
    for (int j = 0; j < numFollowers; j++) {
      int followerNumber = followers[j];
      if (activities[i].practitionerNumber == followerNumber && activities[i].duration > longestTimes[i]) {
        longestTimes[i] = activities[i].duration;
        strcpy(longestPractitioners[i], practitioners[followerNumber - 1].name);
      }
    }
  }

  // Print the results
  printf("Atividade | Praticante com maior tempo de prática | Tempo (minutos)\n");
  printf("----------|----------------------------------------|----------------\n");
  for (int i = 0; i < numActivities; i++) {
    if (strcmp(longestPractitioners[i], "") != 0) {
      printf("%-10s | %-43s | %d\n", activities[i].name, longestPractitioners[i], longestTimes[i]);
    }
  }
}

#pragma endregion Exercise 10

#pragma region Exercise 11

void listLongestFollowedPractitionersByActivity(const struct Practitioner *practitioners, int numPractitioners, const struct Activity *activities, int numActivities, const struct Follow *follows, int numFollows) {
  // Get the practitioner number from the user
  printf("\nLista de Praticantes:\n");
  displayPractitioners(practitioners, numPractitioners);
  int practitionerNumber;
  printf("Introduza o número do praticante: ");
  scanf("%d", &practitionerNumber);

  // Find the practitioner with the given number
  int practitionerIndex = -1;
  for (int i = 0; i < numPractitioners; i++) {
    if (practitioners[i].number == practitionerNumber) {
      practitionerIndex = i;
      break;
    }
  }

  if (practitionerIndex == -1) {
    printf("Praticante com número %d não foi ncontrado.\n", practitionerNumber);
    return;
  }

  // Find all the practitioners that are followed by the given practitioner
  int followedPractitionerNumbers[MAX_PRACTITIONERS];
  int numFollowedPractitioners = 0;
  for (int i = 0; i < numFollows; i++) {
    if (follows[i].followerNumber == practitionerNumber) {
      followedPractitionerNumbers[numFollowedPractitioners] = follows[i].followedNumber;
      numFollowedPractitioners++;
    }
  }

  // Find the longest times for each activity among the followed practitioners
  char longestActivities[MAX_ACTIVITIES][MAX_NAME_LEN];
  int longestTimes[MAX_ACTIVITIES];
  for (int i = 0; i < MAX_ACTIVITIES; i++) {
    longestTimes[i] = 0;
  }
    for (int i = 0; i < numActivities; i++) {
    for (int j = 0; j < numFollowedPractitioners; j++) {
    if (activities[i].practitionerNumber == followedPractitionerNumbers[j]) {
        // Check if this activity has a longer time than the current longest time
        int activityIndex = -1;
        for (int k = 0; k < MAX_ACTIVITIES; k++) {
          if (strcmp(longestActivities[k], activities[i].name) == 0) {
            activityIndex = k;
            break;
          }
        }
        if (activityIndex == -1 || activities[i].duration > longestTimes[activityIndex]) {
          strcpy(longestActivities[activityIndex], activities[i].name);
          longestTimes[activityIndex] = activities[i].duration;
        }
      }
    }
  }

  // Print the results
  printf("Atividade | Praticante | Tempo\n");
  printf("--------------------|------------------------|-------------------\n");

  for (int i = 0; i < numActivities; i++) {
  if (strcmp(activities[i].name, activity) == 0) {
      // Find the practitioner with the longest time for this activity
      int longestTime = -1;
      int longestTimeIndex = -1;
      for (int j = 0; j < numFollowedPractitioners; j++) {
        if (followedPractitioners[j].totalTime > longestTime) {
        longestTime = followedPractitioners[j].totalTime;
        longestTimeIndex = j;
        }
      }
      if (longestTimeIndex != -1) {
        printf("%-20s | %-20s | %d %s\n", activities[i].name, followedPractitioners[longestTimeIndex].name, followedPractitioners[longestTimeIndex].totalTime, activities[i].units);
      }
    }
  }
}

#pragma endregion Exercise 11
*/
#pragma endregion Nao foram bem realizados

#pragma endregion Exercises

#pragma region LoadDataFiles

/// @brief Funções para carregar os dados do praticante
/// @param Practitioner aponta para um array de objetos struct Practitioner. A função lê dados de um arquivo e os armazena neste array
/// @param maxPractitioners inteiro representando o número máximo de praticantes que podem ser armazenados no array de praticantes
/// @return um inteiro representando o número de praticantes que foram realmente armazenados no array de praticantes. Se ocorrer um erro ao abrir o arquivo, a função retornará 0
int loadPractitioners(struct Practitioner *practitioners, int maxPractitioners) {
    // Abre o arquivo para leitura
  FILE *fp = fopen("Trabalho1\\practitioners.txt", "r");
  if (fp == NULL) {
    perror("Error opening file");
    return 0;
  }

   // Lê os dados do arquivo linha por linha
  int numPractitioners = 0;
  struct Practitioner practitioner;
  while (fscanf(fp, "%d;%[^;];%[^;];%d", &practitioner.number, practitioner.name, practitioner.phone, &practitioner.age) == 4) {
    if (numPractitioners < maxPractitioners) {
      practitioners[numPractitioners] = practitioner;
      numPractitioners++;
    } else {
      break;
    }
  }

  // Fecha o arquivo
  fclose(fp);

  return numPractitioners;
}

/// @brief Funções para carregar os dados das atividades
/// @param Activities ponteiro para um array de structs "Activity". Representa uma lista de atividades
/// @param maxActivities integer que especifica o número máximo de atividades que podem ser armazenadas no array "activities"
/// @return um inteiro representando o número de atividades que foram lidas do arquivo e armazenadas no array "atividades"
int loadActivities(struct Activity *activities, int maxActivities) {
    // Abre o arquivo para leitura
  FILE *fp = fopen("Trabalho1\\activities.txt", "r");
  if (fp == NULL) {
    perror("Error opening file");
    return 0;
  }

  // Lê os dados do arquivo linha por linha
  int count = 0;
  while (count < maxActivities && fscanf(fp, "%d;%[^;];%[^;];%[^;];%d;%d;%s", &activities[count].practitionerNumber, activities[count].date, activities[count].startTime, activities[count].name, &activities[count].duration, &activities[count].distance, activities[count].units) == 7) {
    count++;
  }

  // Fecha o arquivo
  fclose(fp);

  return count;
}

/// @brief Funções para carregar os dados dos planos de atividades
/// @param planeja array de estruturas ActivityPlan para armazenar os dados do arquivo
/// @param maxPlans O número máximo de planos de atividades que podem ser armazenados na matriz de planos
/// @return inteiro representando o número de planos de atividades que foram realmente lidos do arquivo e armazenados no array de planos
int loadActivityPlans(struct ActivityPlan *plans, int maxPlans) {
    // Abre o arquivo para leitura
  FILE *fp = fopen("Trabalho1\\activity_plans.txt", "r");
  if (fp == NULL) {
    perror("Error opening file");
    return 0;
  }

  // Lê os dados do arquivo linha por linha
  int count = 0;
  while (count < maxPlans && fscanf(fp, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%d;%s", &plans[count].practitionerNumber, plans[count].startDate, plans[count].startTime, plans[count].endDate, plans[count].endTime, plans[count].activity, &plans[count].distance, plans[count].units) == 8) {
    count++;
  }

  // Fecha o arquivo
  fclose(fp);

  return count;
}

#pragma endregion LoadDataFiles

#pragma region SaveDataFiles

/// @brief Função para escrever os dados no arquivo dos praticantes
/// @param array praticantes de struct Practitioner contendo os dados dos praticantes a serem gravados no arquivo
/// @param numPractitioners inteiro representando o número de elementos no array de praticantes
/// @return inteiro indicando o sucesso ou falha da operação. Um valor de 0 indica sucesso e um valor diferente de zero indica falha
int savePractitioners(const struct Practitioner *practitioners, int numPractitioners) {
    // Abre o arquivo para escrita
  FILE *fp = fopen("Trabalho1\\practitioners.txt", "w");
  if (fp == NULL) {
    perror("Error opening file");
    return 0;
  }

  // Escreve os dados no arquivo
  for (int i = 0; i < numPractitioners; i++) {
    fprintf(fp, "%d;%s;%s;%d\n", practitioners[i].number, practitioners[i].name, practitioners[i].phone, practitioners[i].age);
  }

  // Fecha o arquivo
  fclose(fp);

  return 1;
}

/// @brief Função para gravar os dados no arquivo de atividades
/// @param array de atividades de estruturas de atividade contendo os dados a serem gravados no arquivo
/// @param numActivities integer indicando o número de elementos no array de atividades
/// @return inteiro indicando o sucesso ou falha da operação. Um valor de 0 indica sucesso e um valor diferente de zero indica falha
int saveActivities(const struct Activity *activities, int numActivities) {
    // Abre o arquivo para escrita
  FILE *fp = fopen("Trabalho1\\activities.txt", "w");
  if (fp == NULL) {
    perror("Error opening file");
    return 0;
  }

  // Escreve os dados no arquivo
  for (int i = 0; i < numActivities; i++) {
    fprintf(fp, "%d;%s;%s;%s;%d;%d;%s\n", activities[i].practitionerNumber, activities[i].date, activities[i].startTime, activities[i].name, activities[i].duration, activities[i].distance, activities[i].units);
  }

  // Fecha o arquivo
  fclose(fp);

  return 1;
}

/// @brief Função para gravar os dados no arquivo de planos de atividades
/// @param planeja o array de objetos struct ActivityPlan a serem gravados no arquivo
/// @param numPlans número de elementos no array de planos
/// @return inteiro indicando o sucesso ou falha da operação. Um valor de 0 indica sucesso e um valor diferente de zero indica falha
int saveActivityPlans(const struct ActivityPlan *plans, int numPlans) {
    // Abre o arquivo para escrita
  FILE *fp = fopen("Trabalho1\\activity_plans.txt", "w");
  if (fp == NULL) {
    perror("Error opening file");
    return 0;
  }

  // Escreve os dados no arquivo
  for (int i = 0; i < numPlans; i++) {
    fprintf(fp, "%d;%s;%s;%s;%s;%s;%d;%s\n", plans[i].practitionerNumber, plans[i].startDate, plans[i].startTime, plans[i].endDate, plans[i].endTime, plans[i].activity, plans[i].distance, plans[i].units);
  }

  // Fecha o arquivo
  fclose(fp);

  return 1;
}


#pragma endregion SaveDataFiles


