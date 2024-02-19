#include "includes.h"

recipe* createRecipes(int *recipeCountOut) {
  int recipeCount;
  char** recipeFiles = getFilesInDir(&recipeCount);

  recipe* allRecipes = malloc(sizeof(recipe) * recipeCount);
  for(int i = 0; i < recipeCount; i++) {
    readFile(recipeFiles[i], allRecipes, i);
  }
  *recipeCountOut = recipeCount;
  return allRecipes;
}

char** getFilesInDir(int *fileCounterOut) {
  char* currentPath = getCurrentDirectoryPath(); // Hent filstien til .exe filen
  char recipeFolderPathExtension[] = "\\recipes"; // Append en subfolder og escape backslash
  char* recipePath = malloc(strlen(currentPath) + strlen(recipeFolderPathExtension) + 1); // Lav plads til en ny større string af stien

  //Indsæt subfolder til opskrifter i stien til current working directory med string copy og concatenation
  strcpy(recipePath, currentPath);
  strcat(recipePath, recipeFolderPathExtension);
  free(currentPath); //Frigiv currentPath
  
  int fileCounter;
  char** recipeFiles = listFiles(recipePath, &fileCounter);
  *fileCounterOut = fileCounter;
  return recipeFiles;
}

char* getCurrentDirectoryPath(void) {
  char *pathPTR = _getcwd(NULL, 1024);

  if (pathPTR == NULL)
  {
    printf("Error: reading current directory.\n");

    if (errno == ERANGE)
      printf("Error: Path too long.\n");
    else if (errno == ENOMEM)
      printf("Memory cannot be allocated for path.\n");

    EXIT_FAILURE;
  }
  return pathPTR;
}

char** listFiles(char* dirname, int *fileCounterOut) {
  char ** recipeFilenameArray = malloc(50 * sizeof(char *));
  for(int i = 0; i < 50; i++){
      recipeFilenameArray[i] = malloc(50 * sizeof(char));
  }

  int  fileCounter = 0;
  struct dirent *dirEntry;

  DIR *dr = opendir(dirname);

  if (dr == NULL) {
    printf("Error: Could not open directory %s", dirname);
    EXIT_FAILURE;
  }
  while ((dirEntry = readdir(dr)) != NULL) {
    // "." og ".." kommer med i listen af filer. Slip af med dem her.
    if(strcmp(dirEntry->d_name, ".") && strcmp(dirEntry->d_name, "..") != 0) {
      strcpy(recipeFilenameArray[fileCounter], dirEntry->d_name);
      fileCounter++;
    }
  }

  closedir(dr);
  *fileCounterOut = fileCounter;
  return recipeFilenameArray;
}

void readFile(char* file, recipe* allRecipes, int i) {
    char lineBuffer[500];
    char subFolderPathExtension[] = "./recipes/"; // Append en subfolder og escape backslash
    char* recipePath = malloc(strlen(file) + strlen(subFolderPathExtension) + 1);
    strcpy(recipePath, subFolderPathExtension);
    strcat(recipePath, file);

    FILE* fp = fopen(recipePath, "r");

    fscanf(fp, "%*s %[^\n]s", allRecipes[i].name); // Scan af navn
    fscanf(fp, "%*s %d", &allRecipes[i].meat); // Scan af kød bool
    fscanf(fp, "%*s %d", &allRecipes[i].serving); // Scan af portion størrelse
    fscanf(fp, "%*s %[^\n]s", allRecipes[i].cook_time); // Scan af tid
    fscanf(fp, "%*s %[^\n]s", lineBuffer); // Buffer til at holde én string med ingredienser som skal splittes.
    char** ingredients = stringSplit(lineBuffer); // Scan af ingredienser
    memset(lineBuffer,0,strlen(lineBuffer)); // Ryd buffer
    fscanf(fp, "%*s %[^\n]s", lineBuffer); // Buffer til at holde én string med ingrediensmængder som skal splittes.
    char** ingredientAmount = stringSplit(lineBuffer);

    // Læsning af ingredienser
    for(int j = 0; j < 50; j++) {
      if(strcmp(ingredients[j],"") || strcmp(ingredientAmount[j],"") != 0) {
        strcpy(allRecipes[i].ingredients[j], ingredients[j]);
        strcpy(allRecipes[i].ingredientsAmount[j], ingredientAmount[j]);
      }
    }
    fscanf(fp, "%*s"); // ignorer "directions" linje
    // Læsning af fremgangsmåde
    for(int j = 0; j < 30; j++) {
      char buffer[100];
      memset(buffer, 0, 100);
      if(fgets(buffer, 100, fp) != NULL) {
        strcpy(allRecipes[i].directions[j], buffer);
      }
    }
    
    fclose(fp);
    //Frigiv da vi har kopieret værdierne ind i struct
    free(ingredients);
    free(ingredientAmount);
    free(recipePath);
}

char** stringSplit(char *string) {
    char ** array = malloc(50 * sizeof(char *));
    for(int i = 0; i < 50; i++){
        array[i] = malloc(50 * sizeof(char));
        memset(array[i],0,50);
    }

    char * token = strtok(string, ",");

    int j = 0;
    while( token != NULL ) {
        strcpy(array[j], token);
        token = strtok(NULL, ",");
        j++;
   }
   return array;
}