#include "includes.h"

void showFood(recipe* allRecipes) {
  int menuChoice;

  clearTerminal();
  printLogo3();

  while (1) {
    printf("\nMenu:\n");
    printf("1. New meal plan.\n");
    printf("2. Go back.\n");
    scanf("%d", &menuChoice);

    switch (menuChoice) {
    case 1: //Ny madplan
      newMealplan(allRecipes);
      break;
    case 2: //Gå tilbage
      clearTerminal();
      return;
    default:
      clearTerminal();
      return;
    }
  }
}

void showRecipes(recipe* allRecipes, int recipeCount) {
  while(1) {
    char userInput[2];

    clearTerminal();
    printLogo2();
    printf("\nHere you can see your recipes!\n");
    //Recipes
    for(int i = 0; i < recipeCount; i++) {
      printf("%d: %s\n", i, allRecipes[i].name);
    }
    
    //GO BACK
    printf("\n\n\n\n\n\n\nEnter q to return, or select a recipe number to view the recipe!\n");
    scanf(" %c", userInput);
    
    if(userInput[0] == 113 || userInput[0] == 81) {
      clearTerminal();
      return;
    } else if(isdigit(userInput[0])) {
      clearTerminal();
      printRecipe(allRecipes, atoi(userInput));
      printf("\n\n\n\n\n\n\nEnter any key to return.\n");
      scanf(" %c", userInput);
    }
  }
}

void printRecipe(recipe* allRecipes, int index) {
  printf("\n\n\033[4m%s:\033[0m", allRecipes[index].name);
  printf("\nSeveringer: %d", allRecipes[index].serving);
  printf("\nTid: %s", allRecipes[index].cook_time);
  printf("\n\n\033[4mIngredienser:\033[0m\n");
  // Print ingredients and amount
  
  for (int j = 0; j < 10; j++) {
    printf("%s %s\n", allRecipes[index].ingredients[j], allRecipes[index].ingredientsAmount[j]);
  }
  printf("\n\n\033[4mFremgangsmetode:\033[0m\n");
  for(int j = 1; j < 30; j++) {
    if(strcmp(allRecipes[index].directions[j], "") != 0) {
      printf("%d) %s", j, allRecipes[index].directions[j]);
    }
  }   
}

void printMealPlan(recipe* recipeArray, int dateAmount) {
  // Print mealplan with recipes
  for (int i = 0; i < dateAmount; i++) {
    printf("\n\t\tDay %d\n", i + 1);
    for (int j = 0; j < 40; j++) {
      printf("_");
    }
    printf("\n\n\033[4m%s \033[0m", recipeArray[i].name);
    printf("\nSeveringer: %d", recipeArray[i].serving);
    printf("\nTid: %s", recipeArray[i].cook_time);
    printf("\n\nIngredienser:\n");
    // Print ingredients and amount
    for (int j = 0; j < 10; j++) {
      printf("%s %s\n", recipeArray[i].ingredients[j], recipeArray[i].ingredientsAmount[j]);
    }
    // Print directions
    /*
    printf("\nFremgangmetode:\n%s\n\n", allRecipes[i].directions);
    for (int j = 0; j < 40; j++) {
      printf("_");
    }
    */
    printf("\n");
  }
  printf("\n\033[3m\033[4m!Mealplan has been printed and saved to mealplan.txt!\033[0m\n");
}

void newMealplan(recipe* allRecipes) {
  int dateAmount, userInput;

  clearTerminal();
  printLogo3();

  printf("\n\nDo you wish to enter ingredients you already have to be used in recipes?\n");
  printf("1. No, create a random plan for me!\n");
  printf("2. Yes!\n");
  scanf("%d", &userInput);
  if(userInput == 2) {
    // Kør køleskabsflow
  }

  printf("\n\nHow many days would you like to generate? (MAX 7)\n");
  scanf("%d", &dateAmount);

  clearTerminal();
  printf("\n\nHere you can see your foodplan for the next week!\n");

  clearTerminal();
  printLogo3();

  if(userInput == 1) {
    printMealPlan(allRecipes, dateAmount);
  } else if(userInput == 2) {
    //printMealPlan(customRecipeArray, dateAmount);
  }

  char* path = getCurrentDirectoryPath();
  char pathExtension[] = "\\output";
  char* newPath = malloc(strlen(path) + strlen(pathExtension) + 1);

  strcpy(newPath, path);
  strcat(newPath, pathExtension);
  free(path);
  printf("\nYour mealplan and shopping list, can be found here:\n%s\n", newPath);

  //Write to file
  /*
  FILE *mealplan = fopen("mealplan.txt","w");
  mealplan = fopen("mealplan.txt","w");

  for (int i = 0; i < dateAmount; i++) {
    fprintf(mealplan,"\n\t\tDay %d\n", i + 1);
    for (int j = 0; j < 40; j++) {
      fprintf(mealplan,"%c", underscore);
    }
    fprintf(mealplan,"\n\n%s", allRecipes[i].name);
    fprintf(mealplan,"\nSeveringer: %d", allRecipes[i].serving);
    fprintf(mealplan,"\nTid: %s", allRecipes[i].cook_time);
    fprintf(mealplan,"\n\nIngredienser:\n");
    // Print ingredients and amount
    for (int j = 0; j < 20; j++) {
      fprintf(mealplan,"%s %s\n", allRecipes[i].ingredients[j], allRecipes[i].ingredientsAmount[j]);
    }
    //  
    }
    fprintf(mealplan,"\n");
  }

  fclose(mealplan);
  */
}
