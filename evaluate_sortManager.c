#include "includes.h"

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

void assignValue(recipe *allRecipes, char *fridge[], int recipeCount, int n) {
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
