#include <iostream>
#include <sstream>
#include <bits/stdc++.h>//fast working
#include <windows.h>//GUI FEATURES
#include <conio.h>//CONSLOE INPUT /output functions like getch()
#include <iomanip>//align text,control decimal places
using namespace std;
// Console manipulation functions for UI
COORD coord = {0, 0};
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void animation() {
    for (int i = 45; i >= 1; i--) {
        Sleep(30);
        gotoxy(1, i);
    }
    for (int i = 1; i <= 20; i++) {
        Sleep(40);
        gotoxy(1, i);
    }
}
// Stack Implementation
//its usage:-
     //When a customer buys products, trolleyStack.pop() is called to assign and display a trolley number, 
	 //simulating a real shopping experience.
//The Stack class represents a linked list-based stack data structure used for
// managing trolley numbers in the shopping system.
// Stack class represents a single node in the trolley stack
class Stack {
public:
    int data;      // Stores the unique trolley number
    Stack* link;   // Pointer to the next node in the stack, creating a linked list structure
};

class StackManager {
public:
    Stack* top = NULL; // Pointer to the topmost node of the stack, initially set to NULL (empty stack)

    // Function to add a new trolley number to the stack (push operation)
    void push(int data) {
        // Create a new Stack node dynamically in heap memory
        Stack* temp = new Stack();

        // Check if memory allocation failed (heap overflow)
        if (!temp) {
            cout << "\nHeap Overflow";  // Print error message if no memory available
            exit(1);  // Terminate the program
        }

        // Set the data of the new node to the trolley number
        temp->data = data;

        // Link the new node to the current top of the stack
        temp->link = top;

        // Update the top to point to the newly added node
        top = temp;
    }

    // Function to check if the stack is empty
    bool isEmpty() {
        // Returns true if top is NULL, meaning no elements in stack
        return top == NULL;
    }

    // Function to view the top element without removing it
    int peek() {
        // If stack is not empty, return the data of the top node
        if (!isEmpty())
            return top->data;
        else
            // Exit if stack is empty (error handling)
            exit(1);
    }

    // Function to remove and display the top trolley number (pop operation)
    void pop() {
        // Check if stack is empty before popping
        if (isEmpty()) {
            cout << "\nStack Underflow" << endl;  // Error message if no elements to remove
            return;
        }

        // Store the top node in a temporary pointer
        Stack* temp = top;

        // Move the top pointer to the next node
        top = top->link;
        
        // Display the trolley number
        cout << "Your Trolley No is: " << temp->data << endl;

        // ASCII art representation of a trolley
        cout << "                  ___" << endl;
        cout << "                 /  |" << endl;
        cout << "  ______________/   --" << endl;
        cout << " |___/__ /___/_|     " << endl;
        cout << " |__/___/___/__|     " << endl;
        cout << " |_/___/___/___|     " << endl;
        cout << "    _______/         " << endl;
        cout << "     O   O           " << endl;

        // Free the memory of the removed node
        delete temp;
    }

    // Function to display all trolley numbers in the stack
    void displayStack() {
        // Create a temporary pointer to traverse the stack
        Stack* temp = top;

        // Iterate through all nodes and print their data
        while (temp != NULL) {
            cout << temp->data << " ";  // Print trolley number
            temp = temp->link;  // Move to next node
        }
        cout << endl;
    }
};
// Queue Implementation
class Node {
public:
    string cname;
    Node* link;
    Node(string name) : cname(name), link(NULL) {}
};

class Queue {
public:
    Node *front, *rear;
    
    Queue() : front(NULL), rear(NULL) {}

    bool isEmpty() {
        return front == NULL;
    }

    void enqueue(string name) {
        Node* newNode = new Node(name);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->link = newNode;
            rear = newNode;
        }
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return;
        }
        Node* temp = front;
        front = front->link;
        if (front == NULL) rear = NULL;
        delete temp;
    }

    void displayQueue() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return;
        }
        Node* temp = front;
        while (temp != NULL) {
            cout << "\t" << temp->cname << "\n";
            temp = temp->link;
        }
    }
};

// Sales Record Structure
class SaleRecord {
public:
    string productName;
    int quantity;
    double revenue;
};

// Product Summary class
class ProductSummary {
public:
    string name;
    int quantity;
    double revenue;
};

// Product Class
class Product {
public:
    int ID;
    string proName;
    double prePrice;
    int quantity;
    int totalSold;
    Product* next;

    Product(int id, string name, double price, int qty) 
        : ID(id), proName(name), prePrice(price), quantity(qty), totalSold(0), next(NULL) {}
};

// Sales Report Class
class SalesReport {
public:
    static const int MAX_SALES = 1000;
    static const int MAX_ITEMS = 100;
    SaleRecord dailySales[MAX_SALES];
    int salesCount;
    double dailyRevenue;
    
    SalesReport() : salesCount(0), dailyRevenue(0.0) {}

    void generateSalesReport() {
        system("cls");
        cout << "\n================== Sales Report ==================\n\n";
        cout << "Total Revenue: $" << fixed << setprecision(2) << dailyRevenue << "\n\n";
        
        ProductSummary summary[MAX_ITEMS];
        int summaryCount = 0;
        
        // Aggregate sales by product
        for (int i = 0; i < salesCount; i++) {
            bool found = false;
            for (int j = 0; j < summaryCount; j++) {
                if (summary[j].name == dailySales[i].productName) {
                    summary[j].quantity += dailySales[i].quantity;
                    summary[j].revenue += dailySales[i].revenue;
                    found = true;
                    break;
                }
            }
            if (!found && summaryCount < MAX_ITEMS) {
                summary[summaryCount].name = dailySales[i].productName;
                summary[summaryCount].quantity = dailySales[i].quantity;
                summary[summaryCount].revenue = dailySales[i].revenue;
                summaryCount++;
            }
        }
        
        // Sort by revenue
        for (int i = 0; i < summaryCount - 1; i++) {
            for (int j = 0; j < summaryCount - i - 1; j++) {
                if (summary[j].revenue < summary[j + 1].revenue) {
                    ProductSummary temp = summary[j];
                    summary[j] = summary[j + 1];
                    summary[j + 1] = temp;
                }
            }
        }
        
        cout << "Products by Sales Volume:\n";
        cout << "Product Name\t\tQuantity Sold\tRevenue\n";
        cout << "================================================\n";
        for (int i = 0; i < summaryCount; i++) {
            cout << summary[i].name << "\t\t\t"
                 << summary[i].quantity << "\t\t$"
                 << fixed << setprecision(2) << summary[i].revenue << "\n";
        }
        
        cout << "\nTotal Transactions: " << salesCount << "\n";
        double avgTransactionValue = (salesCount > 0) ? dailyRevenue / salesCount : 0;
        cout << "Average Transaction Value: $" 
             << fixed << setprecision(2) << avgTransactionValue << "\n";
    }
};

// Shopping System Class
class ShoppingSystem {
public:
    Product* head;
    Queue customerQueue;
    StackManager trolleyStack;
    static const int MAX_ITEMS = 100;
    string purchasedItems[MAX_ITEMS];
    int purchaseCount;
    SalesReport salesReport;

    ShoppingSystem() : head(NULL), purchaseCount(0) {}

    string toLowerCase(string str) {
        string lower = str;
        for (char& c : lower) {
            c = tolower(c);
        }
        return lower;
    }

    void searchProducts() {
        system("cls");
        if (head == NULL) {
            cout << "No products in inventory.\n";
            return;
        }

        string searchTerm;
        cout << "Enter product name to search (partial name is ok): ";
        cin >> searchTerm;
        
        string searchTermLower = toLowerCase(searchTerm);
        bool found = false;
        Product* temp = head;
        
        cout << "\nSearch Results:\n";
        cout << "ID\t\tProduct Name\t\tPrice\t\tQuantity\n";
        cout << "=================================================================|\n";
        
        while (temp != NULL) {
            string productNameLower = toLowerCase(temp->proName);
            if (productNameLower.find(searchTermLower) != string::npos) {
                cout << temp->ID << "\t\t" 
                     << temp->proName << "\t\t\t" 
                     << temp->prePrice << "\t\t\t" 
                     << temp->quantity << "\n";
                found = true;
            }
            temp = temp->next;
        }
        
        if (!found) {
            cout << "No products found matching '" << searchTerm << "'\n";
        }
    }

    void addProduct() {
        system("cls");
        int id, quantity;
        string name;
        double price;

        cout << "\t\t\tEnter product ID: ";
        cin >> id;
        cout << "\t\t\tEnter product Name: ";
        cin >> name;
        cout << "\t\t\tEnter product price: ";
        cin >> price;
        cout << "\t\t\tEnter product quantity: ";
        cin >> quantity;

        Product* newProduct = new Product(id, name, price, quantity);
        
        if (head == NULL) {
            head = newProduct;
        } else {
            Product* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newProduct;
        }

        system("cls");
        cout << "\n\n\t\t\t\tProduct has been added!\n\n\n";
    }

    void displayProducts() {
        system("cls");
        if (head == NULL) {
            cout << "No products available.\n";
            return;
        }

        cout << "Current products:\n";
        cout << "ID\t\tProduct Name\t\tPrice\t\tQuantity\t\tTotal Sold\n";
        cout << "================================================================================|\n";
        
        Product* temp = head;
        int count = 0;
        while (temp != NULL) {
            cout << temp->ID << "\t\t" 
                 << temp->proName << "\t\t\t" 
                 << temp->prePrice << "\t\t\t" 
                 << (temp->quantity > 0 ? to_string(temp->quantity) : "Out of stock!") 
                 << "\t\t\t" << temp->totalSold << "\n";
            temp = temp->next;
            count++;
        }
        cout << "\nTotal products: " << count << "\n\n";
    }
//it follows the stack functions
    void buyProducts() {
        system("cls");
        displayProducts();

        if (head == NULL) {
            cout << "\nNo products available for purchase.\n";
            return;
        }

        int numItems;
        cout << "How many items do you want to buy? ";
        cin >> numItems;

        if (numItems > MAX_ITEMS) {
            cout << "Cannot purchase more than " << MAX_ITEMS << " items at once.\n";
            return;
        }

        double totalCost = 0;
        string customer;
        purchaseCount = 0;

        for (int i = 0; i < numItems; i++) {
            int id, quantity;
            cout << "Enter product ID: ";
            cin >> id;
            
            Product* temp = head;
            while (temp != NULL && temp->ID != id) {
                temp = temp->next;
            }

            if (temp == NULL) {
                cout << "Product not found!\n";
                i--;
                continue;
            }

            cout << "Enter quantity: ";
            cin >> quantity;

            if (quantity > temp->quantity) {
                cout << "Insufficient stock!\n";
                i--;
                continue;
            }

            double itemCost = temp->prePrice * quantity;
            totalCost += itemCost;
            temp->quantity -= quantity;
            temp->totalSold += quantity;
            purchasedItems[purchaseCount++] = temp->proName;

            // Record sale
            if (salesReport.salesCount < SalesReport::MAX_SALES) {
                salesReport.dailySales[salesReport.salesCount].productName = temp->proName;
                salesReport.dailySales[salesReport.salesCount].quantity = quantity;
                salesReport.dailySales[salesReport.salesCount].revenue = itemCost;
                salesReport.salesCount++;
            }
        }

        cout << "\nEnter your name: ";
        cin >> customer;
        customerQueue.enqueue(customer);

        double finalCost = totalCost * 0.9;  // 10% discount
        salesReport.dailyRevenue += finalCost;

        system("cls");
        cout << "\nPurchased items: ";
        for (int i = 0; i < purchaseCount; i++) {
            cout << purchasedItems[i];
            if (i < purchaseCount - 1) cout << ", ";
        }
        cout << "\nOriginal cost: $" << totalCost;
        cout << "\nFinal cost (10% discount): $" << finalCost;
        cout << "\nThank you for shopping!\n\n";

        trolleyStack.pop();
    }
//its for stack trolleys initializing loop
    void initialize() {
        for (int i = 1; i <= 50; i++) {
            trolleyStack.push(i);
        }
    }

    void adminMenu() {
        int choice;
        do {
            system("cls");
            cout << "\n\t\t============================================" << endl;
            cout << "\t\t|          Administrator Portal             |" << endl;
            cout << "\t\t============================================" << endl;
            cout << "\t\t     1. Add new product" << endl;
            cout << "\t\t     2. Display all products" << endl;
            cout << "\t\t     3. View customer queue" << endl;
            cout << "\t\t     4. Remove customer from queue" << endl;
            cout << "\t\t     5. Search products" << endl;
            cout << "\t\t     6. Generate sales report" << endl;
            cout << "\t\t     0. Return to main menu" << endl;
            cout << "\nEnter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: addProduct(); 
				break;
                case 2: displayProducts(); system("pause"); break;
                case 3: 
                    system("cls");
                    cout << "Current customers:\n";
                    customerQueue.displayQueue();
                    system("pause");
                    break;
                case 4:
                    customerQueue.dequeue();
                    cout << "Customer removed from queue.\n";
                    system("pause");
                    break;
                case 5:
                    searchProducts();
                    system("pause");
                    break;
                case 6:
                    salesReport.generateSalesReport();
                    system("pause");
                    break;
            }
        } while (choice != 0);
    }

     void mainMenu() {
        int choice;
        do {
            system("cls");
            cout << "\n\t\t|--------<Main Menu>-----------|\n\n";
            cout << "\t\t 1) Administrator Login\n";
            cout << "\t\t 2) Customer Portal\n";
            cout << "\t\t 3) Search Products\n";  // Added customer search option
            cout << "\t\t 4) Exit\n";
            cout << "\nEnter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: adminMenu(); 
				break;
                case 2: buyProducts(); system("pause"); 
				break;
                case 3: searchProducts(); system("pause"); 
				break;
                case 4: 
                    cout << "\n\nThank you for using our system!\n";
                    break;
            }
        } while (choice != 4);
    }
};

int main() {
    system("color F5");
    ShoppingSystem shop;
    shop.initialize(); // This creates a stack of 50 trolley numbers
    gotoxy(23,5);
    cout << "--------------------------------------------------" << endl;
    gotoxy(23,7);
    cout << "||            Shopping Club System                ||" << endl;
    gotoxy(23,9);
    cout << "--------------------------------------------------" << endl;
    gotoxy(23,11);
    cout << ">>>----Project Implemented By-----<<<" << endl;
    gotoxy(23,13);
    	cout<<"IQTIDAR HUSSAIN (485)"<<endl;
   	gotoxy(23,14);
   	cout<<"SYEDA ZAINAB BATOOL  (586)"<<endl;
   	gotoxy(23,15);
   	cout<<"UBAID-UR-REHMAN   (591)"<<endl;   
    system("pause");
    system("cls");
    system("color F5");
    shop.mainMenu();
    return 0;
}