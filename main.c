#include "includes.h"

void clearTerminal(void);

int main(void) {
  int recipeCount, fridgeCount;
  recipe* allRecipes = createRecipes(&recipeCount);

  char** fridge = getExistingIngredients(recipeCount, allRecipes, &fridgeCount);
  for(int i = 0; i < recipeCount; i++) {
    printf("Opskrift: %s, weight: %d\n", allRecipes[i].name, allRecipes[i].weight);
  }
  //printf("%s", fridge[0]);
  //compareArrays(allRecipes, recipeCount, fridgeCount, fridge);


  

  while(1) {
    int menuChoice;
    printLogo3();
    printf("\nMenu:");
    printf("\n1. Opskrifter");
    printf("\n2. Madplan");
    printf("\n3. Quit\n\n");
    scanf("%d", &menuChoice);

    switch (menuChoice) {
      case 1: //Opskrifter
        showRecipes(allRecipes, recipeCount);
        break;
      case 2: //Madplan
        showFood(allRecipes, recipeCount);
        break;
      case 3: //QUIT
        printf("Exiting.");
        return 0; 
    }
  }
  
  return 0;
}

void clearTerminal(void) {
  #ifdef _WIN32
    system("cls");
	#else
    system("clear");
  #endif
}
