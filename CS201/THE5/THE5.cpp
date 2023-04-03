#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

#include "prompt.h"
#include "strutils.h"
#include "Products.h"

using namespace std;


void fileCheck(ifstream &input, string file) {
	string inputFile;
	while (input.fail()) {
		cout << "\nThe " << file << " file does not exists" << endl;
		input.clear();
		inputFile = PromptString("Please enter a filename for "+file+" database: ");
		input.open(inputFile.c_str());
	}
}


int getOption(){
    int option;
    cout << "MENU" << endl;
    cout << "1. Add item to the shopping list" << endl;
    cout << "2. Delete item from the shopping list" << endl;
    cout << "3. Edit the amount of existing item" << endl;
    cout << "4. Print current receipt" << endl;
    cout << "5. Print current receipt in order" << endl;
    cout << "6. Print current receipt in reverse order" << endl;
    cout << "7. Exit" << endl;
    cout << "---" << endl;
    cout << "Enter your choice: ";
    cin >> option;
    return option;
}


void addItem(Products & item_list){
    string qr_code;
    int amount;
    bool flag_qr, flag_shoplist;

    cout << "Please enter the QR code to add: ";
    cin >> qr_code;
    ToUpper(qr_code);
    flag_qr = item_list.find(qr_code); 
    flag_shoplist = item_list.findInShopList(qr_code); 
    if(flag_qr == false){
        cout << "Invalid QR code, try again" << endl;
    }
    else if(flag_shoplist){
        cout << "Item is already in the shoplist, if you want to edit the amount please choose option 3" << endl;
    }
    else{
        cout << "Please enter the amount to add: ";
        cin >> amount;
        if(amount < 1 || amount > 25){
            cout << "Invalid amount, try again" << endl;
        }
        else{
            item_list.add_item(qr_code, amount);
        }
    }
}


void deleteItem(Products & item_list){
    string qr_code;
    cout << "Please enter the QR code to delete: ";
    cin >> qr_code;
    ToUpper(qr_code);
    if(item_list.findInShopList(qr_code) == false){
        cout << "Shoplist does not contain given QR code" << endl;
    }
    else{
        item_list.remove_item(qr_code);
    }
}


void editItem(Products & item_list){
    string qr_code;
    int amount;
    cout << "Please enter the QR code to edit: ";
    cin >> qr_code;
    ToUpper(qr_code);
    if(item_list.findInShopList(qr_code) == false){
        cout << "Shoplist does not contain the given QR code." << endl;
    }
    else{
        cout << "Please enter the amount to edit: ";
        cin >> amount;
        if(amount < 1 || amount > 25){
            cout << "Invalid amount, try again" << endl;
        }
        else{
            item_list.edit_item(qr_code, amount);
        }
    }
}


void printCurrentReceipt(Products & item_list){
    item_list.printCurrentReceipt();
}


void printReceiptInOrder(Products & item_list){
    item_list.printCurrentReceiptAscending();
}


void printReceiptReverse(Products & item_list){
    item_list.printCurrentReceiptDescending();
}


void openFiles(ifstream & qrReader, ifstream & priceReader){
    string qrCode="", line = "", qrLine = "", priceLine = "";
	int itemCount= 0;
	bool found = false;
    
	string qrFile = PromptString("Please enter a filename for QR database: ");
	qrReader.open(qrFile.c_str());
	fileCheck(qrReader, "QR");
    
	string priceFile = PromptString("\nPlease enter a filename for Price database: ");
	priceReader.open(priceFile.c_str());
	fileCheck(priceReader, "Price");
    
}


void runner(Products & item_list){
    int option;
    do{
        option = getOption();
        if (option == 1)
            addItem(item_list);
        else if (option == 2)
            deleteItem(item_list);
        else if (option == 3)
            editItem(item_list);
        else if (option == 4)
            printCurrentReceipt(item_list);
        else if (option == 5)
            printReceiptInOrder(item_list);
        else if (option == 6)
            printReceiptReverse(item_list);
        else if (option == 7)
            cout << "Goodbye!" << endl;
        else
            cout << "Invalid option" << endl;
    }while(option != 7);
}

int main() {
    Products item_list;
	ifstream qrReader, priceReader;
    openFiles(qrReader, priceReader);

    item_list.read_files(qrReader, priceReader);
    runner(item_list);
	return 0;
}
