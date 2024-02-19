#include "includes.h"

char** getExistingIngredients(int recipeCount, recipe* allRecipes, int *fridgeCount) {
  int n = 0;
    
  printf("Hvor mange madvarer har du? \n");
  scanf("%d", &n);
  
  char** fridge = malloc(n * sizeof(char *));
  char buffer[50];
  for (int i = 0; i < n; i++){
    fridge[i] = calloc(50, sizeof(char));
    printf("Indtast madvarer: \n");
    scanf("%s", buffer);
    if(fridge[i] == NULL){
      printf("exit");
      exit(EXIT_FAILURE);
    }
    strcpy(fridge[i], buffer);
  }

  assignValue(allRecipes, fridge, recipeCount, n);
  bubbleSort(allRecipes, recipeCount);

  *fridgeCount = n;
  return fridge;
}

int strCompare(char str1[50], char str2[50]) {
	char haystack[50];
	char needle[50];

	for (size_t i = 0; i < 50; ++i) {
			haystack[i] = tolower((unsigned char) str1[i]);
	}

	for (size_t i = 0; i < 50; ++i) {
			needle[i] = tolower((unsigned char) str2[i]);
	}

	char *pch = strstr(haystack, needle);
  return pch != NULL; 
}

void assignValue(recipe *allRecipes, char *fridge[], int recipeCount, int n){
  int k;
  recipe* r;
  r = allRecipes;
  for(int i = 0; i < recipeCount; i++, r++){
    k = 0;
    for(int j = 0; j < 20 && k < n; j++){
      int contains = strCompare(r->ingredients[j], fridge[k]);
      if(contains){
        r->weight += 1;
        k++;
        j = 0;
      }
    }
  }
}

void swap(recipe* xp, recipe* yp){
  recipe temp = *xp;
  *xp = *yp;
  *yp = temp;
}

// A function to implement bubble sort
void bubbleSort(recipe *allRecipes, int recipeCount){
  int i, j;
  recipe *r;
  r = allRecipes;
  for (i = 0; i < recipeCount - 1; i++){
    for (j = 0; j < recipeCount - i - 1; j++){
      if ((r+j)->weight < (r+j+1)->weight){
        swap(r+j, r+j+1); 
      }
    }
  }
}

