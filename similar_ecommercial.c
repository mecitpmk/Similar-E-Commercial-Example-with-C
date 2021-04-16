
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>



typedef struct Product
{
    int id;
    char name[50];
    char category[50];
    float price;
    struct Product *next;
}Product;

typedef struct Basket
{
    int id;
    int amount;
    struct Product* productList;
    struct Basket* next;
}Basket;

typedef struct Customer
{
    char name[50];
    char surname[50];
    int id;
    struct Customer* next;
    struct Basket* basketList;
}Customer;


static int customer_id = 1;
static bool isFirst = true;
Customer *HEAD = NULL;
Customer *currentlyCustomer = NULL;


Product *createProduct(int *id, char*name , char *category, float *price)
{
    Product *newProduct = (Product *) malloc(sizeof(Product));
    strcpy(newProduct->name,name);
    strcpy(newProduct->category,category);
    newProduct->price = *price;
    newProduct->id = *id;
    newProduct->next = NULL;
    return newProduct;
}




void addProducttoCustomer(Customer *customer, Product *productObj)
{
    // check firstly..
    if (customer->basketList->productList != NULL)
    {
        Product *prList = customer->basketList->productList;
        while (1)
        {
            if (prList->next == NULL)break;
            prList = prList->next;
        }
        prList->next = productObj;
        return;
    }
    customer->basketList->productList = productObj; //if null add directly.

}


Customer *createCustomer(char *customerName, char *Surname)
{
    Customer *newCustomer = (Customer *) malloc(sizeof(Customer));
    strcpy(newCustomer->name , customerName);
    strcpy(newCustomer->surname , Surname);
    newCustomer->id = customer_id;
    newCustomer->next = NULL;
    newCustomer->basketList = NULL;
    if (isFirst)
    {
        HEAD = newCustomer;
        isFirst = false;
        currentlyCustomer = newCustomer;
    }
    else
    {
        currentlyCustomer->next = newCustomer;
        currentlyCustomer = newCustomer;
    }
    customer_id++;
    return newCustomer;

}

void prntSpecificCatforCust(Customer *customerP,char *specificCategory)
{
    Product *productPt;
    if (customerP->basketList->productList != NULL)
    {
        productPt =customerP->basketList->productList;
    }
    while (productPt != NULL)
    {
        if (strcmp(productPt->category, specificCategory) == 0)
        {
            printf("The customer %s has Specific Category %s and Product is %s \n",customerP->name,specificCategory,productPt->name);
        }
        productPt = productPt->next;
    }

}
void printCustomerProducts(Customer *customer)
{
    Product *productPt = customer->basketList->productList;
    while (productPt != NULL)
    {
        printf("Name : %s , Category %s , price %f \n",productPt->name , productPt->category , productPt->price);
        productPt = productPt->next;
    }
}

void printCustomers()
{
    Customer *customerPt = HEAD;
    while (customerPt != NULL)
    {
        printf("Cust name %s , Cust surname %s\n",customerPt->name,customerPt->surname);
        customerPt = customerPt->next;
    }
}


Basket *createBasket(int *id, int *amount)
{
    Basket *newBasket = (Basket *) malloc(sizeof(Basket));
    newBasket->id = *id;
    newBasket->amount = *amount;
    newBasket->next = NULL;
    newBasket->productList = NULL;
    return newBasket;
}




Customer *findCustByID(int *givenID)
{
    Customer *customerPt = HEAD;
    while (customerPt != NULL)
    {
        if (customerPt->id == *givenID)
        {
            printf("Customer id = %d , Customer name %s finded!!\n",customerPt->id,customerPt->name);
            if (customerPt->basketList == NULL)
            {
                printf("Customer basket is not available creating now...\n");
                // Basket create ettik specific id'li user icin..
                int amount = 24 ; //Edit!!
                Basket *createBasketForCust = createBasket(&customerPt->id , &amount);
                customerPt->basketList = createBasketForCust;
                break;
            }
        }
        customerPt = customerPt->next;
    }
    return customerPt;
}


int main()
{
    

    char created_name[50] = "Mecit";
    char created_surname[50] = "Pamuk";
    Customer *mecit = createCustomer(created_name,created_surname);
    
    char created_nameS[50] = "Hasan";
    Customer *hasan = createCustomer(created_nameS,created_surname);
    
    printCustomers();

    int hamburgerID = 1;
    char foodName[50]= "Hamburger";
    char categoryFood[50] = "Food";
    float price = 50.1;
    Product *hamburger = createProduct(&hamburgerID,foodName,categoryFood,&price);



    int givenID = 1;
    Customer *findedCustomer = findCustByID(&givenID);
    printf("finded Customer basket id = %d , finded Customer basket amount = %d \n ---\n",findedCustomer->basketList->id , findedCustomer->basketList->amount);
    

    addProducttoCustomer(findedCustomer,hamburger);

    char food[50] = "Pasta";
    char cat[50] = "Food";
    float priceT = 11.2;
    Product *pasta = createProduct(&hamburgerID,food,cat,&priceT);

    addProducttoCustomer(findedCustomer,pasta);
    

    char drink[50] = "Coke";
    char drinkCat[50] = "Drink" ;
    float drinkPrice = 5.5;
    Product *coke = createProduct(&hamburgerID,drink,drinkCat,&drinkPrice);

    addProducttoCustomer(findedCustomer,coke);
    printCustomerProducts(findedCustomer);
    printf("------\n");

    prntSpecificCatforCust(findedCustomer,drinkCat); // print category for drinks.
    printf("------\n");
    prntSpecificCatforCust(findedCustomer,categoryFood); // print category for foods.


    

    

}