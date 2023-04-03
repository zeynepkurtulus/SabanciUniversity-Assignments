#include "Products.h"
#include <vector>
#include <string>
// #include <algorithm>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include "strutils.h"

Products::Products(){

}

vector<Product> Products::get_item_list()const{
    return item_list;
}
vector<Product> Products::get_shop_list()const{
    return shop_list;
}

Products::Products(const Products & p){
    item_list = p.get_item_list();
    shop_list = p.get_shop_list();
}



int argQR(vector<Product> & item_list, string qr){
    for(int i=0; i<item_list.size(); i++){
        if(item_list[i].qr_code == qr){
            return i;
        }
    }
    return -1;
}


void Products::read_files(ifstream & qr, ifstream & price){
    string line, word;
    while(getline(qr, line)){
        string qrCode, name="";
        istringstream lineStream(line);
        lineStream >> qrCode;
        ToUpper(qrCode);
        while(lineStream >> word){
            name += word + " ";
        }
        name = name.substr(0, name.length()-1);
        Product p(name, -1, -1, qrCode);
        item_list.push_back(p);
    }

    while(getline(price, line)){
        double price;
        string qrCode;
        istringstream lineStream(line);
        lineStream >> qrCode >> price;
        ToUpper(qrCode);
        int index = argQR(item_list, qrCode);
        item_list[index].price = price;
    }
}


bool Products::find(string qr){
    int index = argQR(item_list, qr);
    return index != -1;
}


bool Products::findInShopList(string qr){
    int index = argQR(shop_list, qr);
    return index != -1;
}
    

void Products::add_item(string qr, int amount){
    int index = argQR(item_list, qr);
    Product p = item_list[index];
    p.amount = amount;
    shop_list.push_back(p);
}


void Products::edit_item(string qr, int amount){
    int index = argQR(shop_list, qr);
    shop_list[index].amount = amount;
}


void Products::remove_item(string qr){
    int index = argQR(shop_list, qr);
    vector<Product> temp;
    for(int i=0; i<shop_list.size(); i++){
        if(shop_list[i].qr_code != qr){
            temp.push_back(shop_list[i]);
        }
    }
    /*
    for(auto p: shop_list){
        if(p.qr_code != qr){
            temp.push_back(p);
        }
    }
    */
    shop_list = temp;
}


void printReceipt(vector<Product> & shop_list){
    double sum = 0;
    for(int i=0; i<shop_list.size(); i++){
        int widthSet = shop_list[i].name.length();
        cout << setw(5) << shop_list[i].name << " *" << setw(3) << shop_list[i].amount << setw(31-widthSet) << (shop_list[i].price*shop_list[i].amount) << endl;
        sum += (shop_list[i].price*shop_list[i].amount);
    }
    /*
    for(auto p: shop_list){
        int widthSet = p.name.length();
        cout << setw(5) << p.name << " *" << setw(3) << p.amount << setw(31-widthSet) << (p.price*p.amount) << endl;
        sum += (p.price*p.amount);
    }
    */
    cout << "\nVAT(18%):" << setw(27) << (0.18*sum) << endl;
	cout << "_______________________________________" << endl;
	cout << "Total:"  << setw(30) << (sum*1.18) <<endl<<endl;
}


void Products::printCurrentReceipt(){
    printReceipt(shop_list);
}


bool ascending(const Product & p1, const Product & p2){
    double price1 = p1.amount*p1.price, price2 = p2.amount*p2.price;
    if(price1 < price2){
        return true;
    }
    else if (price1 == price2 && (p1.name < p2.name)){
        return true;
    }
    return false;
}


bool descending(const Product & p1, const Product & p2){
    return !ascending(p1,p2);
}

void swap(Product & p1, Product & p2){
    Product temp = p1;
    p1 = p2;
    p2 = temp;
}

void sort(vector<Product> & temp, string type){
    if(type == "ascending"){
        for(int i=0; i<temp.size(); i++){
           for(int j=i+1; j<temp.size(); j++){
               if(descending(temp[i], temp[j])){
                   swap(temp[i], temp[j]);
               }
           }
        }
    }
    else{
        for(int i=0; i<temp.size(); i++){
           for(int j=i+1; j<temp.size(); j++){
               if(ascending(temp[i], temp[j])){
                   swap(temp[i], temp[j]);
               }
           }
        }
    }
}


void Products::printCurrentReceiptAscending(){
    vector<Product> temp = shop_list;
    sort(temp, "ascending");
    printReceipt(temp);
}


void Products::printCurrentReceiptDescending(){
    vector<Product> temp = shop_list;
    sort(temp, "descending");
    printReceipt(temp);
}