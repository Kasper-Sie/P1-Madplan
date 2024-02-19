#ifndef INCLUDES_H_
#define INCLUDES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <direct.h>
#include <errno.h>
#include <dirent.h>

typedef struct RECIPE {
    char name[30];
    int meat;
    int serving;
    char cook_time[6];
    char ingredients[50][50];
    char ingredientsAmount[50][50];
    char directions[20][100];
    int weight;
} recipe;

// Olivers Prototyper
recipe* createRecipes(int *recipeCountOut);
char** getFilesInDir(int *fileCounterOut);
char* getCurrentDirectoryPath(void);
char** listFiles(char* dirname, int *fileCounterOut);
void readFile(char* file, recipe* allRecipes, int i);
char** stringSplit(char *string);

// Prototyper
int strCompare(char str1[50], char str2[50]);
void clearTerminal(void);
void compareArrays(recipe* allRecipes, int recipeCount, int fridgeCount, char** fridge);
int strCompare(char str1[50], char str2[50]);

// Gustaws Prototyper
void showRecipes(recipe* allRecipes, int recipeCount);
void printRecipe(recipe* allRecipes, int index);
void showFood(recipe* allRecipes, int recipeCount);
void printMealPlan(recipe* recipeArray, int dateAmount);
void printLogo(void);
void printLogo2(void);
void printLogo3(void);
void newMealplan(recipe* allRecipes, int recipeCount, char fridge[]);

// Prototyper


//Maries prototyper
void assignValue(recipe *allRecipes, char *fridge[], int recipeCount, int n);
void swap(recipe* xp, recipe* yp);
void bubbleSort(recipe *allRecipes, int recipeCount);
int fillFridge(char* fridge[]);
char** getExistingIngredients(int recipeCount, recipe* allRecipes, int *fridgeCount);

#endif
