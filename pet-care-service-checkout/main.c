#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>
#include<string.h>

struct Services 
{
    
    int id;
    char describe[50];
    int petType;
    float price;
    
    
};

struct Pet
{
   char name[50];
   int type;
   char gender;
   char owner[100];
};




int loadServices(struct Services allServices[]);
int loadPets(struct Pet allPets[]);
int findName(char petName[],char ownerName[],struct Pet allPets[], int *petAmountPtr);
struct Pet createCustomer(char petName[], char ownerName[]);
int choose(struct Services allServices[],struct Services customer[], struct Pet newPet);
void enterCard(int *creditPtr, int *monthPtr, int *yearPtr, int *cvvPtr);
void receipt(int *creditPtr, int *monthPtr, int *yearPtr, int *cvvPtr, int *numberPtr, struct Services customer[], struct Pet newPet );
int main()

{
 
    
    struct Services allServices[15]={};
    struct Services customer[4]={};
    struct Pet allPets[30] = {};
    struct Pet newPet;
    int serviceAmount;
    serviceAmount = loadServices(allServices);
    int petAmount = loadPets(allPets);
    int number = 0;
    int credit;
    int month;
    int year;
    int cvv;
    char more;
    char ownerName[50]={};
    char petName[50] ={};
    int pets = 0;
    int total = 0;
   while( more != 'n' && more != 'N')
    {
    printf("What is the Onwers Name?\n");
    getchar();
    fgets(ownerName,50,stdin);
    printf("What is the Pets Name?\n");
    getchar();
    fgets(petName,50,stdin);
    
   int index = findName(petName,ownerName,allPets,&petAmount);
   
  if(index == -1)
{
    newPet = createCustomer(petName, ownerName);
    allPets[petAmount] = newPet;
    index = petAmount;
    petAmount++;
}
else
{
    newPet = allPets[index];
}
    number = choose(allServices,customer,newPet);
    
    enterCard(&credit, &month, &year, &cvv);
    receipt(&credit, &month, &year, &cvv, &number,customer,newPet );
    pets++;
    
    printf("Is there another customer?\n");
    scanf(" %c", &more);
    }
    
    printf("Total amount of Pets: %d\n",pets);
    for(int x = 0; x < pets; x++)
    {
        total += customer[x].price;
    }
    printf("Total cost: $%.2f", total);

    return 0;
}



int loadServices(struct Services allServices[])
{
    
    FILE *input = fopen("allServices.txt","r");
    
    if (input == NULL)
    {
        printf("Error reading file");
        exit(0);
    }
    
    
    char line[300];
    char *sp;
    
    int x = 0;
    while(fgets(line,300,input) != NULL)
    {
       sp = strtok(line,",");
       allServices[x].id = atoi(sp);
       
       sp = strtok(NULL,",");
       strcpy(allServices[x].describe,sp);
       
       sp = strtok(NULL,",");
       allServices[x].petType = atoi(sp);
       
       sp = strtok(NULL,",");
       allServices[x].price = atof(sp);
       
       x++;
    }
    
    
    
    
    fclose(input);
    
    return x;
    
    
}


int loadPets(struct Pet allPets[])
{
    
    FILE *input = fopen("allPets.txt","r");
    
    if (input == NULL)
    {
        printf("Error reading file");
        exit(0);
    }
    
    
    char line[300];
    char *sp;
    
    int x = 0;
    while(fgets(line,300,input) != NULL)
    {
       sp = strtok(line,",");
       strcpy(allPets[x].name,sp);
       sp = strtok(NULL,",");
       allPets[x].type = atoi(sp);
       
       sp = strtok(NULL,",");
       allPets[x].gender = *sp;
       
       sp = strtok(NULL,",");
       strcpy(allPets[x].owner,sp);
       
       x++;
    }
    
    
    
    
    fclose(input);
    
    return x;
}



int findName(char petName[],char ownerName[],struct Pet allPets[], int *petAmountPtr)
{
    int index = 0;
    for(int x = 0; x < *petAmountPtr;x++)
    {
        if( strcmp(allPets[x].name,petName) == 0 && strcmp(allPets[x].owner,ownerName) == 0)
        {
            return index;
        }
        
        
    }
    
    return -1;
    
    
    
    
}


struct Pet createCustomer(char petName[], char ownerName[])
{
    struct Pet newPet;
    char gender;
    
    strcpy(newPet.name,petName);
    strcpy(newPet.owner,ownerName);
    
    printf("Owner and pet not found in system, creating new account!");
    
    printf("Enter 1 for Dog or 2 for Cat:");
    scanf("%d", &newPet.type);
    
    while( newPet.type != 1 && newPet.type != 2)
    {
        printf("You have entered an invalid type, please try again!");
        printf("Enter 1 for Dog or 2 for Cat:");
        scanf("%d", &newPet.type);
        
    }
    
    printf("Enter M for Male or F for Female:");
    scanf(" %c", &gender);
    
    while( gender != 'M' && gender != 'm' && gender != 'F' && gender != 'f')
    {
        printf("You have entered an invalid type, please try again!");
        printf("Enter M for Male or F for Female:");
        scanf(" %c", &gender);
        
    }
    
    newPet.gender = toupper(gender);
    
    return newPet;
}


int choose(struct Services allServices[],struct Services customer[], struct Pet newPet)
{
   int this = 0;    
   int code ;
   printf("DEBUG pet type is: %d\n", newPet.type);
   while( this != 4 )
   {
    for(int x = 0; x < 15;x++)
    {
        
        if(allServices[x].petType == newPet.type)
        {
            printf("%d    %s.      $. %.2f\n", allServices[x].id, allServices[x].describe, allServices[x].price);
        }
        
        if(allServices[x].petType == 3)
        {
            printf("%d    %s.      $. %.2f\n", allServices[x].id, allServices[x].describe, allServices[x].price);
        }
        
    }
    
    
    printf("Choose a service code or 0 to quit:");
    scanf("%d", &code);
    if( code == 0)
    return this;
    
    for(int x = 0; x < 15;x++)
    {
        if(code == allServices[x].id)
            customer[this] = allServices[x];
    }
    
    this++;
     
    return this;
    
   }
}



void enterCard(int *creditPtr, int *monthPtr, int *yearPtr, int *cvvPtr)
{
    printf("Enter Payment Information:\n");
    printf("Enter credit card number:\n");
    scanf("%d", creditPtr);
    
    printf("Enter card expiration Month:\n");
    scanf("%d", monthPtr);
    
    printf("Enter card expiration Year:\n");
    scanf("%d", yearPtr);
    
    printf("Enter card cvv code:\n");
    scanf("%d", cvvPtr);
    
    
}

void receipt(int *creditPtr, int *monthPtr, int *yearPtr, int *cvvPtr, int *numberPtr, struct Services customer[], struct Pet newPet )
{
    float total = 0;
    printf("Payment receipt for services on %s:\n", newPet.name);
    
    for( int x = 0; x < *numberPtr; x++)
   {
    printf("%d. %s     $ %.2f\n", customer[x].id, customer[x].describe, customer[x].price);
    total+= customer[x].price;
   }
   
   printf("Total cost: %.2f", total);
   
   printf("Card Number: %d\n", *creditPtr);
   printf("Expiration Date: %d/%d\n", *monthPtr, *yearPtr);
   printf("CVV Code: %d\n", *cvvPtr);
   
    
   
    
    

}
