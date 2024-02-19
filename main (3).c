#include <stdio.h>
#include "includes.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define RECIPES 4

typedef struct {
    char name[30];
    int meat;
    int serving;
    char cook_time[6];
    char ingredients[20][30];
    char ingredientsAmount[20][30];
    char directions[20][100];
    int weight;
} recipe;

// Prototyper
int strCompare(char str1[25], char str2[25]);
recipe* createRecipes(void);
void recipeArgumentTest(recipe* allRecipes);
void compareArrays(recipe* allRecipes, int array1Size, int array2Size);



int main(void) {
  FILE *f = fopen("shoppinglist.txt", "w");

  if(f==NULL){
    EXIT_FAILURE;
  }

  recipe* allRecipes = createRecipes();

  recipeArgumentTest(allRecipes); // Funktionskald som medsender pointer til vores array af structs

  //shoppinglist(f, allRecipes);

  compareArrays(allRecipes, 4, 20);


  fclose(f);

  return 0;
}

recipe* createRecipes(void) {
  recipe recipe1 = {"Boller i karry", 1, 4, "1:20", {"Hakket Oksekoed", "Fint hakkede loeg", "Maelk", "Aeg", "Havregryn", "Smoer", "Karry", "Stødt spidskommen", "Koriander", "Hvedemel", "Maelk", "Groentsagsbouillon", "Basmati ris", "Aeble", "Mango", "bredbladet persille"},{"400g", "1 stk", "0.5 dl", "1 stk", "1 dl", "2 spsk", "2 tsk", "1 tsk", "1 tsk", "3 spsk", "3 dl", "3 dl"}, {"HAk them loeg"}, 0};
  recipe recipe2 = {"Pita med kylling", 1, 4, "1:30", {"Kyllingfillet", "Oeko citron", "Roeget paprika", "Soed paprika", "Hvidloeg", "Olivenolie", "Creme fraiche", "Mayonnaise", "Parmasan", "Pesto", "Oeko citron"},{"400g", "0.5 stk", "0.5 tsk", "1 tsk", "2 fed", "1 tsk", "1 dl", "1 spsk", "50g", "1 spsk", "0.5 stk"}, {"HAk them loeg"}, 0};
  recipe recipe3 = {"Maccaroni and cheese", 1, 4, "1:40", {"Loeg", "Hvidloeg", "Smoer", "Groentsagsbouillon", "Squash", "Macaroni", "Floedeost", "Frisk Mozzarella", "Parmasan", "Muskatnød", "Soed paprika", "Baby spinat"},{"1 stk", "2 fed", "10g", "4 dl", "300g", "350g", "75g", "125g", "50g", "1 knivspids", "1 tsk", "100g"}, {"HAk them loeg"}, 0};
  recipe recipe4 = {"Falafler", 1, 4, "0:20", {"Toerrede kikaerter", "Persille", "Hvidloeg", "Loeg", "Stoedt koriander", "Stoedt spidskommen", "Kartofler", "Aeg", "Rasp", "Chili", "Citron", "Fritureolie", "Pitabroed", "Tomat", "Agurk", "Salat", "Cremefraiche 18%%"},{"400g", "2 haandfulde", "4 fed", "2 stk", "4 tsk", "4 tsk", "2 tsk", "2 stk", "3 stk", "4 spsk", "0.5 tsk", "1.5 stk", "1 L", "4 stk", "2 stk", "0.5 stk", "70g", "1 dl"}, {"HAk them loeg"}, 0};
  recipe* allRecipes = malloc(sizeof(recipe) * RECIPES);
  
  allRecipes[0] = recipe1;
  allRecipes[1] = recipe2;
  allRecipes[2] = recipe3;
  allRecipes[3] = recipe4;

  return allRecipes;
}

void recipeArgumentTest(recipe* allRecipes) {
  printf("%s\n", allRecipes[0].name);
  printf("%s\n", allRecipes[1].name);
  printf("%s\n", allRecipes[2].name);
  printf("%s\n", allRecipes[3].name);
}


int strCompare(char str1[25], char str2[25]) {
	char str1Lower[25];
	char str2Lower[25];

	for (size_t i = 0; i < 25; ++i) {
			str1Lower[i] = tolower((unsigned char) str1[i]);
	}

	for (size_t i = 0; i < 25; ++i) {
			str2Lower[i] = tolower((unsigned char) str2[i]);
	}

	char *pch = strstr(str2Lower, str1Lower);

	if (pch) {
			return 1;
	} else {
			return 0;
	}
}

void compareArrays(recipe* allRecipes, int array1Size, int array2Size) {
  int counter = 0;
  int k= 0;
    char frigde[4][50] = {
    "ost",
    "Aeg",
    "Karry",
    "Maelk"
  };

  printf("---------inkøbsliste----------\n");
  
  for (int t = 0; t < array1Size; t++) {
    char** newArray = malloc(sizeof(char*) * array2Size);
    newArray[t] = malloc(sizeof(char) * 20);
    memset(newArray[t], 0, 20);
    for (int i = 0; i < array1Size; i++) {
      
      for (int j = 0; j < array2Size; j++) {
        if (strcmp(frigde[i], allRecipes[k].ingredients[j]) == 0 /*|| newArray[j] == NULL*/) {
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


  for (int i = 0; i < array2Size; i++) {
      if (newArray[i] != NULL && strcmp(newArray[i], "") != 0) {
      printf("%s %s \n", newArray[i], allRecipes[k].ingredientsAmount[i]);

    }
    
  }
  printf("\n\n");
  k++;
}
}



/*
void shoppinglist(FILE * f, recipe * allRecipes) {
  int size = 20;
  int k = 0;
  int b = 0;
  char frigde[3][50] = {
    "ost",
    "Aeg",
    "Karry"
  };
  char * list[50];
  printf("\n\nShopping list as follows--------------\n");

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < size; j++) {
      printf("%s\n", allRecipes[i].ingredients[j]);
      fprintf(f, "%s\n", allRecipes[i].ingredients[j]);

      if ( * allRecipes[i].ingredients[j] == '\0') {
        break;
      }
    }
  }

  int testt = 0;
  printf("shopping list needed----------");
  for (int i = 0; i < 5; i++) {
    b = 0;
      for (int j = 0; j < 20; j++) {
        if (strcmp(frigde[b], allRecipes[i].ingredients[j]) != 0) {
          //testt = strcmp(frigde[b], allRecipes[i].ingredients[j]);
          //printf("test %d", testt);
          list[k] = allRecipes[i].ingredients[j];
          k++;
        }
        b++;
      }
      
  }

  for (int i = 0; i < 50; i++) {
    printf("\n%s ", list[i]);
  }

}
*/

/*
int removeDuplicates(char fridg[], recipe *allRecipes, char lis[]){
  int k = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 20; j++){
            if(strcmp(fridg[i], allRecipes[i].ingredients[j]) == 0){
                lis[j] = allRecipes[i].ingredients[j];
            }
        }
        k++;
    }
    // Print list
    for(int i = 0; i < 20; i++){
        printf("%s", lis[i]);
    }
}
*/
/*
void compare(char stra[], recipe* allRecipes, int size, char list[20]) {
    int i, j, k = 0;
    printf("Common elements are: ");
   
    for (i = 0; i < 3; i++) {
       

      for (j = 0; j < 20; j++) {

        if (strcmp(&stra[i], allRecipes[j]) != 0 ) {
          list[k] = allRecipes[j];
          k++;
        } 
      }
    }    

     for (int i = 0; i < 20; i++){
      printf("%s", list[i]);

    }  
}

*/

  /*
    while (allRecipes[i].ingredients[j] != '\n' && allRecipes[i].ingredients[j] != '\0')
    {
        printf("%s\n", allRecipes[i].ingredients[j]);
        fprintf(f,"%s\n",allRecipes[i].ingredients[j]);
        i++;
        j++;

    }



    for (int i = 0; i < 4; i++)
    {
      size = sizeof(allRecipes[i].ingredients[j]); //kør indtil
      printf("%d\n", size);
      
        while (*allRecipes[i].ingredients[j] != '\n' && *allRecipes[i].ingredients[j] != '\0')
        {
        printf("%s\n", allRecipes[i].ingredients[j]);
        fprintf(f,"%s\n",allRecipes[i].ingredients[j]);
        j++;
        }

    }
*/


/*
      for (j = 0; j < size; j++)
      {
        printf("%s\n", allRecipes[i].ingredients[j]);
        fprintf(f,"%s\n",allRecipes[i].ingredients[j]);
      }


for (int i = 0; i < 4; i++)
    {
      size = sizeof(allRecipes[i].ingredients[j]); //kør indtil
      printf("%d\n", size);

      for (j = 0; j < size; j++)
      {
        printf("%s\n", allRecipes[i].ingredients[j]);
        fprintf(f,"%s\n",allRecipes[i].ingredients[j]);
      }
      
      
    }
*/