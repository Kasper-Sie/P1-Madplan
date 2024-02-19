#include "includes.h"

void showFood(recipe* allRecipes, int recipeCount) {
  int menuChoice;
  char** fridge = getExistingIngredients(recipeCount, allRecipes);

  clearTerminal();
  printLogo3();

  while (1) {
    printf("\nMenu:\n");
    printf("1. New meal plan.\n");
    printf("2. Go back.\n");
    scanf("%d", &menuChoice);

    switch (menuChoice) {
    case 1: //Ny madplan
      newMealplan(allRecipes, recipeCount, *fridge);
      break;
    case 2: //Gå tilbage
      clearTerminal();
      return;
    }
  }
}


void newMealplan(recipe* allRecipes, int recipeCount, char fridge[]){
  int dateAmount, userInput;
  char anyInput;
  
  clearTerminal();
  printLogo3();

  printf("\n\nDo you wish to enter ingredients you already have to be used in recipes?\n");
  printf("1. No, create a random plan for me!\n");
  printf("2. Yes!\n");
  scanf("%d", &userInput);
  if(userInput == 2) {
    char** fridge = getExistingIngredients(recipeCount, allRecipes);
    compareArrays(allRecipes, recipeCount, *fridge);
  }
  

  printf("\n\nHow many days would you like to generate? (MAX 7)\n");
  scanf("%d", &dateAmount);

  clearTerminal();
  printf("\n\nHere you can see your foodplan for the next week!\n");

  // Create meal plan with different recipe arrays
  if(userInput == 1) {
    printMealPlan(allRecipes, dateAmount);
  } else if(userInput == 2) {
    printMealPlan(allRecipes, dateAmount);
  }

  char* path = getCurrentDirectoryPath();
  char pathExtension[] = "\\output"; // Append en subfolder og escape backslash
  char* newPath = malloc(strlen(path) + strlen(pathExtension) + 1); // Lav plads til en ny større string af stien

  // Indsæt subfolder til opskrifter i stien til current working directory med string copy og concatenation
  strcpy(newPath, path);
  strcat(newPath, pathExtension);
  free(path); //Frigiv currentPath
  printf("\nYour mealplan and shoppinglist can be found here:\n%s\n", newPath);

  printf("\n\nPress any key to return.\n");
  scanf(" %c", &anyInput);
  clearTerminal();
  printLogo3();
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
    for (int j = 0; j < 40; j++) {
      printf("_");
    }
    printf("\n");
  }
  printf("\n\033[3m\033[4m!Mealplan has been printed and saved to mealplan.txt!\033[0m\n");


  //Write to file

  FILE *mealplan = fopen("./output/mealplan.txt","w");
  
  for (int i = 0; i < dateAmount; i++) {
    fprintf(mealplan,"\n\t\tDay %d\n", i + 1);
    for (int j = 0; j < 40; j++) {
      fprintf(mealplan,"_");
    }
    fprintf(mealplan,"\n\n%s", recipeArray[i].name);
    fprintf(mealplan,"\nSeveringer: %d", recipeArray[i].serving);
    fprintf(mealplan,"\nTid: %s", recipeArray[i].cook_time);
    fprintf(mealplan,"\n\nIngredienser:\n");
    // Print ingredients and amount
    for (int j = 0; j < 20; j++) {
      fprintf(mealplan,"%s %s\n", recipeArray[i].ingredients[j], recipeArray[i].ingredientsAmount[j]);
    }
    // Print directions
    //fprintf(mealplan,"\nFremgangmetode:\n%s\n\n", recipeArray[i].directions);
    for (int j = 0; j < 40; j++) {
      fprintf(mealplan,"_");
    }
    fprintf(mealplan,"\n");
  }

  fclose(mealplan);
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

void printLogo(void) {
 

    printf("                                                                 dddddddd                                                                                                                                          \n");
    printf("     MMMMMMMM               MMMMMMMM                             d::::::d                   lllllll                                     333333333333333        000000000          000000000          000000000     \n");
    printf("     M:::::::M             M:::::::M                             d::::::d                   l:::::l                                    3:::::::::::::::33    00:::::::::00      00:::::::::00      00:::::::::00   \n");
    printf("     M::::::::M           M::::::::M                             d::::::d                   l:::::l                                    3::::::33333::::::3 00:::::::::::::00  00:::::::::::::00  00:::::::::::::00 \n");
    printf("     M:::::::::M         M:::::::::M                             d:::::d                    l:::::l                                    3333333     3:::::30:::::::000:::::::00:::::::000:::::::00:::::::000:::::::0\n");
    printf("     M::::::::::M       M::::::::::M  aaaaaaaaaaaaa      ddddddddd:::::dppppp   ppppppppp    l::::l   aaaaaaaaaaaaa  nnnn  nnnnnnnn                3:::::30::::::0   0::::::00::::::0   0::::::00::::::0   0::::::0\n");
    printf("     M:::::::::::M     M:::::::::::M  a::::::::::::a   dd::::::::::::::dp::::ppp:::::::::p   l::::l   a::::::::::::a n:::nn::::::::nn              3:::::30:::::0     0:::::00:::::0     0:::::00:::::0     0:::::0\n");
    printf("     M:::::::M::::M   M::::M:::::::M  aaaaaaaaa:::::a d::::::::::::::::dp:::::::::::::::::p  l::::l   aaaaaaaaa:::::an::::::::::::::nn     33333333:::::3 0:::::0     0:::::00:::::0     0:::::00:::::0     0:::::0\n");
    printf("     M::::::M M::::M M::::M M::::::M           a::::ad:::::::ddddd:::::dpp::::::ppppp::::::p l::::l            a::::ann:::::::::::::::n    3:::::::::::3  0:::::0 000 0:::::00:::::0 000 0:::::00:::::0 000 0:::::0\n");
    printf("     M::::::M  M::::M::::M  M::::::M    aaaaaaa:::::ad::::::d    d:::::d p:::::p     p:::::p l::::l     aaaaaaa:::::a  n:::::nnnn:::::n    33333333:::::3 0:::::0 000 0:::::00:::::0 000 0:::::00:::::0 000 0:::::0\n");
    printf("     M::::::M   M:::::::M   M::::::M  aa::::::::::::ad:::::d     d:::::d p:::::p     p:::::p l::::l   aa::::::::::::a  n::::n    n::::n            3:::::30:::::0     0:::::00:::::0     0:::::00:::::0     0:::::0\n");
    printf("     M::::::M    M:::::M    M::::::M a::::aaaa::::::ad:::::d     d:::::d p:::::p     p:::::p l::::l  a::::aaaa::::::a  n::::n    n::::n            3:::::30:::::0     0:::::00:::::0     0:::::00:::::0     0:::::0\n");
    printf("     M::::::M     MMMMM     M::::::Ma::::a    a:::::ad:::::d     d:::::d p:::::p    p::::::p l::::l a::::a    a:::::a  n::::n    n::::n            3:::::30::::::0   0::::::00::::::0   0::::::00::::::0   0::::::0\n");
    printf("     M::::::M               M::::::Ma::::a    a:::::ad::::::ddddd::::::ddp:::::ppppp:::::::pl::::::la::::a    a:::::a  n::::n    n::::n3333333     3:::::30:::::::000:::::::00:::::::000:::::::00:::::::000:::::::0\n");
    printf("     M::::::M               M::::::Ma:::::aaaa::::::a d:::::::::::::::::dp::::::::::::::::p l::::::la:::::aaaa::::::a  n::::n    n::::n3::::::33333::::::3 00:::::::::::::00  00:::::::::::::00  00:::::::::::::00 \n");
    printf("     M::::::M               M::::::M a::::::::::aa:::a d:::::::::ddd::::dp::::::::::::::pp  l::::::l a::::::::::aa:::a n::::n    n::::n3:::::::::::::::33    00:::::::::00      00:::::::::00      00:::::::::00   \n");
    printf("     MMMMMMMM               MMMMMMMM  aaaaaaaaaa  aaaa  ddddddddd   dddddp::::::pppppppp    llllllll  aaaaaaaaaa  aaaa nnnnnn    nnnnnn 333333333333333        000000000          000000000          000000000     \n");
    printf("                                                                         p:::::p                                                                                                                                   \n");
    printf("                                                                         p:::::p                                                                                                                                   \n");
    printf("                                                                        p:::::::p                                                                                                                                  \n");
    printf("                                                                        p:::::::p                                                                                                                                  \n");
    printf("                                                                        p:::::::p                                                                                                                                  \n");
    printf("                                                                        ppppppppp                                                                                                                                  \n");


}

void printLogo2(void) {

    printf("\n");
    printf(" _____       _     _         ___ ___ ___ ___ \n");
    printf("|     |___ _| |___| |___ ___|_  |   |   |   |\n");
    printf("| | | | .'| . | . | | .'|   |_  | | | | | | |\n");
    printf("|_|_|_|__,|___|  _|_|__,|_|_|___|___|___|___|\n");
    printf("              |_|                            \n");


}

void printLogo3(void) {
    printf("\n");
    printf(" __  __           _       _             ____   ___   ___   ___  \n");
    printf("|  \\/  |         | |     | |           |___ \\ / _ \\ / _ \\ / _ \\ \n");
    printf("| \\  / | __ _  __| |_ __ | | __ _ _ __   __) | | | | | | | | | |\n");
    printf("| |\\/| |/ _` |/ _` | '_ \\| |/ _` | '_ \\ |__ <| | | | | | | | | |\n");
    printf("| |  | | (_| | (_| | |_) | | (_| | | | |___) | |_| | |_| | |_| |\n");
    printf("|_|  |_|\\__,_|\\__,_| .__/|_|\\__,_|_| |_|____/ \\___/ \\___/ \\___/\n");
    printf("                   | |                                          \n");
    printf("                   |_|                                          \n");
}
