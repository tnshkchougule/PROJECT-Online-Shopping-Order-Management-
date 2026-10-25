#include <stdio.h>
#include <string.h>
#include <time.h>

struct Order
{
    int orderId;
    char customerName[50];
    char productName[50];
    int quantity;
    float unitPrice;
    char status[20];
    char orderDate[11];
};

struct Order orders[1000];
int count = 0;

/* Add Order */
void addOrder()
{
    if (count >= 1000)
    {
        printf("Order storage is full!\n");
        return;
    }
    printf("Enter Order ID: ");
    scanf("%d", &orders[count].orderId);

    printf("Enter Customer Name: ");
    scanf(" %49[^\n]", orders[count].customerName);

    printf("Enter Product Name: ");
    scanf(" %49[^\n]", orders[count].productName);

    printf("Enter Quantity: ");
    scanf("%d", &orders[count].quantity);

    printf("Enter Unit Price: ");
    scanf("%f", &orders[count].unitPrice);

    printf("Enter Order Date (DD-MM-YYYY): ");
    scanf("%10s", orders[count].orderDate);

    strcpy(orders[count].status, "Pending");

    count++;

    printf("Order added successfully!\n");
}

/* Calculate Total and Discount */
void calculateTotal()
{
    int id, i;
    float total, discount;
    printf("Enter Order ID: ");
    scanf("%d", &id);

    for (i = 0; i < count; i++)
    {
        if (orders[i].orderId == id)
        {
            total = orders[i].quantity *
                    orders[i].unitPrice;
            discount = 0;
            if (total > 5000)
                discount = total * 0.10;
            printf("Order Total: Rs. %.2f\n", total);
            printf("Discount: Rs. %.2f\n", discount);
            printf("Final Amount: Rs. %.2f\n",
                   total - discount);
            return;
        }
    }
    printf("Order not found!\n");
}

/* Update Order Status */
void updateStatus()
{
    int id, i;
    printf("Enter Order ID: ");
    scanf("%d", &id);

    for (i = 0; i < count; i++)
    {
        if (orders[i].orderId == id)
        {
            if (strcmp(orders[i].status, "Pending") == 0)
            {
                strcpy(orders[i].status, "Shipped");
            }
            else if (strcmp(orders[i].status, "Shipped") == 0)
            {
                strcpy(orders[i].status, "Delivered");
            }
            else
            {
                printf("Order is already Delivered!\n");
                return;
            }
            printf("New Status: %s\n", orders[i].status);
            return;
        }
    }
    printf("Order not found!\n");
}

/* Convert Order Date into time */

time_t convertDate(char date[])
{
    int day, month, year;
    struct tm t = {0};

    sscanf(date, "%d-%d-%d", &day, &month, &year);

    t.tm_mday = day;
    t.tm_mon = month - 1;
    t.tm_year = year - 1900;

    return mktime(&t);
}

/* Display Delayed Orders */
void displayDelayed()
{
    int i, found = 0;

    time_t now = time(NULL);

    printf("\n--- Delayed Orders ---\n");

    for (i = 0; i < count; i++)
    {
        time_t orderTime = convertDate(orders[i].orderDate);

        if (orderTime == (time_t)-1)
            continue;

        if (strcmp(orders[i].status, "Pending") == 0 &&
            difftime(now, orderTime) > 3 * 24 * 60 * 60)
        {
            printf("Order ID: %d\n", orders[i].orderId);
            printf("Customer: %s\n", orders[i].customerName);
            printf("Product: %s\n", orders[i].productName);
            printf("Status: Delayed\n\n");

            found = 1;
        }
    }
    if (found == 0)
        printf("No delayed orders found.\n");
}

/* Calculate Revenue */
void calculateRevenue()
{
    int i;
    float total, discount, revenue = 0;

    for (i = 0; i < count; i++)
    {
        if (strcmp(orders[i].status, "Delivered") == 0)
        {
            total = orders[i].quantity *
                    orders[i].unitPrice;

            discount = 0;

            if (total > 5000)
                discount = total * 0.10;

            revenue = revenue + total - discount;
        }
    }
    printf("Total Delivered Revenue: Rs. %.2f\n", revenue);
}

/* Display All Orders */
void displayOrders()
{
    int i;

    if (count == 0)
    {
        printf("No orders available!\n");
        return;
    }
    for (i = 0; i < count; i++)
    {
        printf("\nOrder ID: %d\n", orders[i].orderId);
        printf("Customer: %s\n", orders[i].customerName);
        printf("Product: %s\n", orders[i].productName);
        printf("Quantity: %d\n", orders[i].quantity);
        printf("Unit Price: Rs. %.2f\n", orders[i].unitPrice);
        printf("Status: %s\n", orders[i].status);
        printf("Order Date: %s\n", orders[i].orderDate);
    }
}

/* Main Function */
int main()
{
    int choice;
    do
    {
        printf("\n=== ONLINE SHOPPING ORDER MANAGEMENT ===\n");
        printf("1. Add Order\n");
        printf("2. Calculate Order Total\n");
        printf("3. Update Order Status\n");
        printf("4. Display Delayed Orders\n");
        printf("5. Calculate Total Revenue\n");
        printf("6. Display All Orders\n");
        printf("7. Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addOrder();
                break;

            case 2:
                calculateTotal();
                break;

            case 3:
                updateStatus();
                break;

            case 4:
                displayDelayed();
                break;

            case 5:
                calculateRevenue();
                break;

            case 6:
                displayOrders();
                break;

            case 7:
                printf("Program Ended.\n");
                break;

            default:
                printf("Invalid Choice!\n");
        }
    } while (choice != 7);
    return 0;
}
