#include "includes.h"

//array1Size = recipeCount = 10
//Fridge = n fra existingIngredients
void compareArrays(recipe* allRecipes, int recipeCount, int fridgeCount, char** fridge) {
  int counter = 0;

  printf("---------Inkoebsliste----------\n");
  /*
  char** shoppingArray = malloc(sizeof(char *) * 100);
  for(int i = 0; i < 100; i++) {
    shoppingArray[i] = malloc(sizeof(int) * 20);
    memset(shoppingArray[i], 0, 20);
  }
  
  for(int q = 0; q < recipeCount; q++) {
    for(int t = 0; t < fridgeCount; t++) {
      for(int s = 0; s < 50; s++) {
        if(strcmp(allRecipes[q].ingredients[s], "") != 0 && strcmp(allRecipes[q].ingredients[s], fridge[t]) != 0) {
          strcpy(shoppingArray[counter], allRecipes[q].ingredients[s]);
          counter++;
        }
      }
    }
  }

  for (int i = 0; i < 100; i++) {
    if(strcmp(shoppingArray[i], "") != 0) {
      printf("%s\n", shoppingArray[i]);
    }
  }
  */

 int k = 0;

 for (int t = 0; t < recipeCount; t++) {
    char** newArray = malloc(sizeof(char*) * 20);
    newArray[t] = malloc(sizeof(char) * 20);
    memset(newArray[t], 0, 20);
    for (int i = 0; i < fridgeCount; i++) {
      
      for (int j = 0; j < 20; j++) {
        if (strcmp(fridge[i], allRecipes[k].ingredients[j]) == 0 || newArray[j] == NULL) {
          counter++;
        }
        if (counter == 0) {
          newArray[j] = allRecipes[k].ingredients[j];
        }
        if (counter != 0) {
          newArray[j] = NULL;
          counter = 0;
        }
      }
   }


  for (int i = 0; i < 20; i++) {
      if (newArray[i] != NULL && strcmp(newArray[i], "") != 0) {
      printf("%s %s \n", newArray[i], allRecipes[k].ingredientsAmount[i]);

    }
    
  }
  printf("\n\n");
  k++;
}


}