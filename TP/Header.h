/**
 * @file Header.h
 * @author João Meira & Guilherme Azeredo
 * @brief
 * @version 1.1
 *
 * @copyright Copyright (c) 2022
 */


#ifndef _HEADER
#define _HEADER

// Constants
#define MAX_PRACTITIONERS 50
#define MAX_ACTIVITIES 200
#define MAX_ACTIVITY_PLANS 50
#define MAX_NAME_LEN 100
#define MAX_DATE_LEN 20
#define MAX_UNIT_LEN 50


#pragma region Structs

struct Practitioner {
  int number;
  char name[MAX_NAME_LEN];
  char phone[MAX_NAME_LEN];
  int age;
  int follows[MAX_PRACTITIONERS]; // Array to store the numbers of the practitioners that this practitioner follows
  int numFollows; // Number of practitioners that this practitioner follows
};

struct Activity {
  int practitionerNumber;
  char date[MAX_NAME_LEN];
  char name[MAX_NAME_LEN];
  char startTime[MAX_NAME_LEN];
  int duration;
  int distance;
  char units[MAX_NAME_LEN];
};

struct ActivityPlan {
  int activityPlanNumber;
  int practitionerNumber;
  char startDate[MAX_NAME_LEN];
  char startTime[MAX_NAME_LEN];
  char endDate[MAX_NAME_LEN];
  char endTime[MAX_NAME_LEN];
  char activity[MAX_NAME_LEN];
  int distance;
  char units[MAX_NAME_LEN];
};



#pragma endregion Structs

#pragma region Practitioner Methods

void displayPractitioners(const struct Practitioner *practitioners, int numPractitioners);

int addPractitioner(struct Practitioner *practitioners, int numPractitioners);

int deletePractitioner(struct Practitioner *practitioners, int numPractitioners, int practitionerNumber);

#pragma endregion Practitioner Methods

#pragma region Activities

void displayActivities(const struct Activity *activities, int numActivities);

int addActivity(struct Activity *activities, int numActivities, const struct Practitioner *practitioners, int numPractitioners);

int deleteActivity(struct Activity *activities, int numActivities, int practitionerNumber);

#pragma endregion Activities

#pragma region ActivityPlans

void displayActivityPlans(const struct ActivityPlan *plans, int numPlans);

int addActivityPlan(struct ActivityPlan *plans, int numPlans, const struct Practitioner *practitioners, int numPractitioners);

int deleteActivityPlan(struct ActivityPlan *activityPlans, int numActivityPlans, int activityPlanNumber);

#pragma endregion ActivityPlans

#pragma region Exercises

#pragma region Exercise 4

int countPractitionersByActivity(const struct Practitioner *practitioners, int numPractitioners, const struct Activity *activities, int numActivities, const char *activityName);

#pragma endregion Exercise 4

#pragma region Exercise 5

void listPractitionersByActivity(const struct Practitioner *practitioners, int numPractitioners, const struct Activity *activities, int numActivities);

#pragma endregion Exercise 5

#pragma region Exercise 6

void listActivityPlans(const struct Practitioner *practitioners, int numPractitioners, const struct ActivityPlan *activityPlans, int numActivityPlans);

#pragma endregion Exercise 6

#pragma region Exercise 7

void calculateTotalAndAverageTimes(const struct Practitioner *practitioners, int numPractitioners, const struct Activity *activities, int numActivities);

#pragma endregion Exercise 7

#pragma region Exercise 8

void generateActivityTable(const struct Practitioner *practitioners, int numPractitioners, const struct ActivityPlan *activityPlans, int numActivityPlans, const struct Activity *activities, int numActivities);

#pragma endregion Exercise 8

#pragma region Exercise 9

void addFollow(struct Practitioner *practitioners, int numPractitioners, int followerNumber, int followeeNumber);

void displayFollows(const struct Practitioner *practitioners, int numPractitioners);

void listPractitionersAndFollowers(const struct Practitioner *practitioners, int numPractitioners);

#pragma endregion Exercise 9

#pragma region Nao foram bem realizados devido aos seguidores
/*
#pragma region Exercise 10

void listLongestPractitionersByActivity(const struct Practitioner *practitioners, int numPractitioners, const struct Activity *activities, int numActivities, const struct Follow *follows, int numFollows);

#pragma endregion Exercise 10

#pragma region Exercise 11

void listLongestFollowedPractitionersByActivity(const struct Practitioner *practitioners, int numPractitioners, const struct Follow *follows, int numFollows, const struct Activity *activities, int numActivities);

#pragma endregion Exercise 11
*/
#pragma endregion Nao foram bem realizados devido aos seguidores

#pragma endregion Exercises

// exercise 1, 2, 3
#pragma region LoadDataFile

int loadPractitioners(struct Practitioner *practitioners, int maxPractitioners);
int loadActivities(struct Activity *activities, int maxActivities);
int loadActivityPlans(struct ActivityPlan *plans, int maxPlans);

#pragma endregion LoadDataFile

// exercise 12
#pragma region SaveDataFile

int savePractitioners(const struct Practitioner *practitioners, int numPractitioners);

int saveActivities(const struct Activity *activities, int numActivities);

int saveActivityPlans(const struct ActivityPlan *plans, int numPlans);


#pragma endregion SaveDataFile

#endif