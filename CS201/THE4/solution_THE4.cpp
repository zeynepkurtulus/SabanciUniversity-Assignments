//
//  main.cpp
//  CS201-201101-HW6
//
//  Created by altop on 12/9/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#include "prompt.h"
#include "strutils.h"

using namespace std;

void fileCheck(ifstream &input, string file)
{
	string inputFile;
	while (input.fail())
	{
		cout << "\nThe " << file << " file does not exists" << endl;
		input.clear();
		inputFile = PromptString("Please enter a filename for "+file+" database: ");
		input.open(inputFile.c_str());
	}
}


int main()
{
	ifstream qrReader, priceReader, shopListReader;
    
	string qrCode="", line = "", qrLine = "", priceLine = "";
	int itemCount= 0;
	bool found = false;
    
	string qrFile = PromptString("Please enter a filename for QR database: ");
	qrReader.open(qrFile.c_str());
	fileCheck(qrReader, "QR");
    
    
	string priceFile = PromptString("\nPlease enter a filename for Price database: ");
	priceReader.open(priceFile.c_str());
	fileCheck(priceReader, "Price");
    
    string shopFile = PromptString("\nPlease enter a filename for your shopping list: ");
	shopListReader.open(shopFile.c_str());
    
    cout << endl;
    
	string itemName = "";
	double price, sum=0.0;
    
    while(getline(shopListReader, line))
	{
		itemName = "";
		price = 0.0;
		found = false;
        
        istringstream lineStream(line);
        
        lineStream >> qrCode >> itemCount;
        ToUpper(qrCode);
        
        while(getline(qrReader, qrLine) && found == false)
        {
            istringstream qrLineStream(qrLine);
            string fileCode;
            qrLineStream >> fileCode;
            if(fileCode == qrCode)
            {
                found = true;
                string tmp;
                while (qrLineStream >> tmp)
                {
                    if(itemName=="")
                        itemName=tmp;
                    else
                        itemName = itemName + " " + tmp;
                }
            }
        }
        if(found==true)
        {
            found=false;
            while(getline(priceReader, priceLine) && found==false)
            {
                istringstream priceLineStream(priceLine);
                string fileCode;
                priceLineStream >> fileCode;
                if(fileCode == qrCode)
                {
                    found = true;
                    priceLineStream >> price;
                }
            }
            
            int widthSet = itemName.length();
            
            cout << setw(5) << itemName << " *" << setw(3) << itemCount << setw(31-widthSet) << (price*itemCount) << endl;
            sum = sum + (price*itemCount);
        }
        
        
		qrReader.clear();
		qrReader.seekg(0);
        
		priceReader.clear();
		priceReader.seekg(0);
	}
    
	cout << "\nVAT(18%):" << setw(27) << (0.18*sum) << endl;
	cout << "_______________________________________" << endl;
	cout << "Total:"  << setw(30) << (sum*1.18) <<endl;
    
	qrReader.close();
	priceReader.close();
    shopListReader.close();
    
	return 0;
}
