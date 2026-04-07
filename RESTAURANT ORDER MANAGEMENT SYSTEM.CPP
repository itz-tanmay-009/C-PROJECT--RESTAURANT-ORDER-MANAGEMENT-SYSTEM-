#include <iostream>
#include <iomanip>  // for setw()
using namespace std;

// ====================================================
// RESTAURANT ORDER MANAGEMENT SYSTEM
// ====================================================
const int MENU_SIZE = 10;

int itemId[MENU_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

string itemName[MENU_SIZE] = {
    "Burger",
    "Pizza",
    "Maggie",
    "Fries",
    "Coke",
    "Roll",
    "Biriyani",
    "Roti",
    "Lacha Paratha",
    "Itli Vada"
};

int itemPrice[MENU_SIZE] = {50, 100, 40, 70, 40, 90, 150, 10, 20, 40};

// ---------- Arrays to store ordered items (for final bill) ----------

const int MAX_ORDERS = 50;

int orderedId[MAX_ORDERS];
string orderedName[MAX_ORDERS];
int orderedPrice[MAX_ORDERS];
int orderedQty[MAX_ORDERS];
int orderedAmount[MAX_ORDERS];

int orderCount = 0;  // how many different items ordered


// ====================================================
// STEP 1: Function to display menu
// ====================================================
void displayMenu() {
    cout << "====================================================\n";
    cout << "                RESTAURANT MENU\n";
    cout << "====================================================\n";
    cout << left << setw(5)  << "ID"
         << left << setw(20) << "Item Name"
         << right << setw(10) << "Price" << "\n";
    cout << "----------------------------------------------------\n";

    for (int i = 0; i < MENU_SIZE; i++) {
        cout << left << setw(5)  << itemId[i]
             << left << setw(20) << itemName[i]
             << right << setw(10) << itemPrice[i] << "\n";
    }

    cout << "----------------------------------------------------\n";
    cout << "Use the Item ID to place your order.\n";
    cout << "====================================================\n";
}

// ====================================================
// STEP 3: Function to search item by ID
// Returns index if found, -1 if not found
// ====================================================
int searchItemById(int id) {
    for (int i = 0; i < MENU_SIZE; i++) {
        if (itemId[i] == id) {
            return i;   // found
        }
    }
    return -1;          // not found
}

// ====================================================
// STEP 2 + 3: Take order for ONE item
// - Ask for ID and quantity
// - Validate ID and quantity
// - Calculate amount and store in order arrays
// ====================================================
void takeOrderForOneItem() {
    int inputId;
    int qty;

    cout << "\nEnter Item ID to order: ";
    cin >> inputId;

    // STEP 3: Search ID
    int index = searchItemById(inputId);

    // Handle invalid ID
    if (index == -1) {
        cout << "Invalid Item ID! Please check the menu.\n";
        return; // do not add anything
    }

    cout << "Enter quantity for " << itemName[index] << ": ";
    cin >> qty;

    if (qty <= 0) {
        cout << "Invalid quantity! It must be more than 0.\n";
        return;
    }

    if (orderCount >= MAX_ORDERS) {
        cout << "Maximum number of orders reached. Cannot add more items.\n";
        return;
    }

    int price = itemPrice[index];
    int amount = price * qty;

    // Store ordered item details
    orderedId[orderCount]     = itemId[index];
    orderedName[orderCount]   = itemName[index];
    orderedPrice[orderCount]  = price;
    orderedQty[orderCount]    = qty;
    orderedAmount[orderCount] = amount;
    orderCount++;

    cout << "\nItem added successfully!\n";
    cout << "---------------------------------------------\n";
    cout << "Item      : " << itemName[index] << "\n";
    cout << "Quantity  : " << qty << "\n";
    cout << "---------------------------------------------\n";
}

// ====================================================
// STEP 4: Loop for multiple orders
// Keeps asking user if they want to order more
// ====================================================
void takeOrdersLoop() {
    int more = 0;

    do {
        takeOrderForOneItem();

        cout << "\nDo you want to order another item? (1 = Yes, 0 = No): ";
        cin >> more;

        if (more != 0 && more != 1) {
            cout << "Invalid choice! Taking it as No.\n";
            more = 0;
        }

    } while (more == 1);
}

// ====================================================
// STEP 5: Final bill printing function
// Shows all ordered items and total bill
// ====================================================
void printFinalBill() {
    cout << "\n\n====================================================\n";
    cout << "                    FINAL BILL\n";
    cout << "====================================================\n";

    if (orderCount == 0) {
        cout << "No items were ordered.\n";
        cout << "====================================================\n";
        cout << "Thank you for visiting!\n";
        cout << "====================================================\n";
        return;
    }

    cout << left << setw(5)  << "ID"
         << left << setw(20) << "Item Name"
         << left << setw(8)  << "Qty"
         << right << setw(10) << "Price"
         << right << setw(10) << "Amount" << "\n";

    cout << "----------------------------------------------------\n";

    int grandTotal = 0;

    for (int i = 0; i < orderCount; i++) {
        cout << left << setw(5)  << orderedId[i]
             << left << setw(20) << orderedName[i]
             << left << setw(8)  << orderedQty[i]
             << right << setw(10) << orderedPrice[i]
             << right << setw(10) << orderedAmount[i] << "\n";

        grandTotal += orderedAmount[i];
    }

    cout << "----------------------------------------------------\n";
    cout << left << setw(43) << "TOTAL BILL AMOUNT"
         << right << setw(10) << grandTotal << "\n";
    cout << "====================================================\n";
    cout << "           Thank you for visiting!\n";
    cout << "====================================================\n";
}

// ====================================================
// main() – Program starts here
// ====================================================
int main() {

    cout << "********************************************\n";
    cout << "*    WELCOME TO THE RESTAURANT SYSTEM      *\n";
    cout << "********************************************\n\n";

    // STEP 1: Display menu
    displayMenu();

    // STEP 4: Loop to take multiple orders
    takeOrdersLoop();

    // STEP 5: Print final bill
    printFinalBill();

    return 0;
}
