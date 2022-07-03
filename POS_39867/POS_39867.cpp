#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Structures

struct Inventory {
	int id;
	string name;
	int quantity;
	int price;
	string inStock;
};

//  Featured Functions

bool loginUser(string username, string password) {
	if (username == "admin" && password == "admin") {
		return true;
	}
	else {
		return false;
	}
}

void checkForStock(struct Inventory data[10]) {
	for (int i = 0; i < 10; i++) {
		if (data[i].quantity > 0) {
			data[i].inStock = "Yes";
		}
		else {
			data[i].inStock = "No";
		}
	}
}


void displayInventory(struct Inventory data[10], string user) {
	cout  << "----- Inventory -----" << endl << endl;
	cout << setw(4) << "Id" << setw(25) << "Products Name" << setw(9) << "Price" << setw(12) << "Quantity" << setw(10) << "InStock" << endl << endl;
	for (int i = 0; i < 10; i++) {
		if (user == "admin") {
			cout << setw(4) << data[i].id << setw(25) << data[i].name << setw(9) << data[i].price << setw(12) << data[i].quantity << setw(10) << data[i].inStock << endl;
		}
		else {
			if (data[i].name != "empty") {
				cout << setw(4) << data[i].id << setw(25) << data[i].name << setw(9) << data[i].price << setw(12) << data[i].quantity << setw(10) << data[i].inStock << endl;
			}
			else {
				break;
			}
		}
	}
	cout << endl;
}

void addProduct(struct Inventory data[10], struct Inventory product) {
	for (int i = 0; i < 10; i++) {
		if (data[i].name == "empty") {
			data[i].name = product.name;
			data[i].price = product.price;
			data[i].quantity = product.quantity;
			break;
		}
		else if (i == 9) {
			cout << endl << "----- Inventory is Full -----" << endl;
		}
	}

}

void deleteProduct(struct Inventory data[10], int id) {
	for (int i = 0; i < 10; i++) {
		if (data[i].id == id) {
			data[i].name = "empty";
			data[i].price = 0;
			data[i].quantity = 0;
			break;
		}
	}

}

string toLowerString(string data) {
	for (int i = 0; i < data.length(); i++) {
		data[i] = tolower(data[i]);
	}
	return data;
}

bool checkForNoInt(string name) {
	for (int i = 0; i < name.length(); i++) {
		if (isdigit(name[i]) == 0) {
			return true;
		}
	}
	return false;
}
// Main Function

int main() {

	Inventory shopInventory[10] = {
		{1, "Peanuts 100 Grams", 5, 800},
		{2, "Noodles", 10, 100},
		{3, "Oil 1Kg", 3, 400},
		{4, "Rice 40Kg", 5, 2000},
		{5, "Gala Biscuit", 50, 30},
		{6, "Oats 300 Grams", 5, 400},
		{7, "empty", 0, 0},
		{8, "empty", 0, 0},
		{9, "empty", 0, 0},
		{10, "empty", 0, 0},
	};

	bool shopOpen = true;
	string user = "a";

	cout << "Welcome to JOHN's Mart........................." << endl;
	cout << "..............................................." << endl;

	while (shopOpen) {

		/*
		cout << "Enter (A) For Admin || (C) For Customer || (X) to Close Shop: ";
		cin >> user;
		cout << endl;
		*/

		if (toLowerString(user) == "a") {

			//Admin Panel ..................................................

			bool loginProcess;
			do {
				string username, password;
				cout << "Username: ";
				cin >> username;
				cout << "Password: ";
				cin >> password;
				if (loginUser(username, password)) {
					loginProcess = false;

					// Inventory Management
					cout << endl << "----- Manage Inventory -----" << endl << endl;

					string process;
					bool inventoryManagingProcess = true;

					do {
						cout << "Enter CHECK for checking inventory." << endl;
						cout << "Enter ADD for adding products." << endl;
						cout << "Enter Del for Deleting products." << endl;
						cout << "Enter UPDATE for updating products." << endl;
						cout << "Enter (M) to get back to main page." << endl << endl;
						cout << "What You wana do: ";
						cin >> process;
						cout << endl;

						if (toLowerString(process) == "check") {
							checkForStock(shopInventory);
							displayInventory(shopInventory, "admin");
						}
						else if (toLowerString(process) == "add") {
							// Add New Product in Invetory

							Inventory newProduct;
							newProduct.id = 0;
							cout << "Enter Product Name: "; cin >> newProduct.name;
							cout << "Enter Product Price: "; cin >> newProduct.price;
							cout << "Enter Product Quantity: "; cin >> newProduct.quantity;
							cout << endl;

							addProduct(shopInventory, newProduct);
							checkForStock(shopInventory);
							displayInventory(shopInventory, "admin");

						}
						else if (toLowerString(process) == "del") {
							// delete Product

							int deleteId;
							displayInventory(shopInventory, "admin");
							cout << "Enter Product ID: "; cin >> deleteId;
							cout << endl;
							deleteProduct(shopInventory, deleteId);
							checkForStock(shopInventory);
							displayInventory(shopInventory, "admin");
						}
						else if (toLowerString(process) == "update") {
							// Update Product
							bool updateAttemptProcess = true;
							string updateId;
							string updateAttempt;
						

							do {
								checkForStock(shopInventory);
								displayInventory(shopInventory, "admin");
								// Getting and Validating Id
								int gettingIdProcess = true;
								bool onMainPage = false;
								do {
									cout << "Which Producut you wana update. Enter Product ID: "; cin >> updateId;
									cout << endl;
									if (updateId == "back") {
										onMainPage = true;
										break;
									}
									if (checkForNoInt(updateId)) {
										cout << "----- Invalid Product Id -----" << endl << endl;
									}
									else {
										if (stoi(updateId) < 1 || stoi(updateId) > 10) {
											cout << "----- No Product With Entered Id -----" << endl << endl;
										}
										else {
											gettingIdProcess = false;
										}
									}
								} while (gettingIdProcess);

								if (onMainPage) break;

								// Products Updating State
								cout << "Enter (P) to update Price." << endl;
								cout << "Enter (Q) to update Quantity." << endl;
								cout << "Enter (N) to update Name" << endl;
								cout << "Enter BACK to return to Inventory Management." << endl << endl;
								cout << "What you wana update: ";
								cin >> updateAttempt;
								cout << endl;
						
								
								if (toLowerString(updateAttempt) == "p") {
									string updatePrice;
									cout << "New Price: "; cin >> updatePrice;
									cout << endl;
									if (checkForNoInt(updatePrice)) {
										cout << "----- Invalid Product Price -----" << endl << endl;
									}
									else {
										for (int i = 0; i < 10; i++) {
											if (shopInventory[i].id == stoi(updateId)) {
												shopInventory[i].price = stoi(updatePrice);
											}
										}
									}
								}
								else if (toLowerString(updateAttempt) == "q") {
									string updateQuantity;
									cout << "New Quantity: "; cin >> updateQuantity; cout << endl;
									if (checkForNoInt(updateQuantity)) {
										cout << "----- Invalid Product Quantity -----" << endl << endl;
									} 
									else {
										for (int i = 0; i < 10; i++) {
											if (shopInventory[i].id == stoi(updateId)) {
												shopInventory[i].quantity = stoi(updateQuantity);
											}
										}
									}
								}
								else if (toLowerString(updateAttempt) == "n") {
									char updateName[30];
									cout << "New Name: ";
									cin.ignore();
									cin.getline(updateName, 30);
									cout << endl;
									for (int i = 0; i < 10; i++) {
										if (shopInventory[i].id == stoi(updateId)) {
											shopInventory[i].name = updateName;
										}
									}
								}
								else if (toLowerString(updateAttempt) == "back") {
									updateAttemptProcess = false;
								}
								else {
									cout << endl << "----- Invalid Command -----" << endl << endl;
								} 
							} while (updateAttemptProcess);
						}
						else if (toLowerString(process) == "m") {
							inventoryManagingProcess = false;
						}
						else {
							cout << "----- Invalid Commad -----" << endl << endl;
						}
					} while (inventoryManagingProcess);
					
				}
				else {
					cout << endl << "----- Invalid Credentials -----" << endl << endl;
					string failedAttempt;
					bool failedAttemptProcess;
					do {
						cout << "Enter (T) to try again || (M) to jump to Main Page: ";
						cin >> failedAttempt;
						cout << endl;
						if (toLowerString(failedAttempt) == "t") {
							loginProcess = true;
							failedAttemptProcess = false;
						}
						else if (toLowerString(failedAttempt) == "m") {
							loginProcess = false;
							failedAttemptProcess = false;
						}
						else {
							cout << endl << "----- Invalid Commad -----" << endl << endl;
							failedAttemptProcess = true;
						}
					} while (failedAttemptProcess);
				}
			} while (loginProcess);

			// Admin Panel End ...............................................
		}
		else if (toLowerString(user) == "c") {

			// Customer Panel ...............................................

		}
		else if (toLowerString(user) == "x") {
			shopOpen = false;
		}
		else {
			cout << endl << "----- Invalid Commad -----" << endl << endl;
		}
	}


	// Testing

	//checkForStock(shopInventory);
	//displayInventory(shopInventory, "admin");

	return 0;
}

