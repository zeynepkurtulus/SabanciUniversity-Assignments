#include <iostream>
#include <string>

using namespace std;



bool budgetCheck( int budget){ //func1 checks if the budget is positive
    if( budget >= 0){
        return true;
    }
    else{
        return false;
    }
}

bool quantityCheck( int x, int y, int z){ //func2 checks whether the quantites are positive
    if(x > 0 && y > 0 && z > 0 ){
        return true;
    }
    else{
        return false;
    }
}

int totalPrice(int v1, int v2,int v3){ //func3 assignes the current price
    int totalV;
    totalV = (5 * v1) + (10 * v2) + (15 * v3);
    return totalV;
}

int maxOperation(int previous_max_price, int current_price, int budget){ //func 4 decides on the max price
    if( previous_max_price > current_price){
        return previous_max_price;
    }
    else if(current_price > budget){
        return previous_max_price;
    }
    else{
        return current_price;
    }
    
    return 0;
}

void utilize(int v1, int v2, int v3, int budget, int & max_price){ //func 5
    
    int currentPrice = totalPrice(v1, v2, v3); // assignes the current price first
    max_price = maxOperation(max_price, currentPrice, budget); // assignes the max price
        
    
}

int permutations(int v1, int v2, int v3, int budget){ //func 6
    
    int maxPrice; //all combinations
    utilize(v1, v2, v3, budget, maxPrice);
    utilize(v1, v3, v2, budget, maxPrice);
    utilize(v2, v1, v3, budget, maxPrice);
    utilize(v2, v3, v1, budget, maxPrice);
    utilize(v3, v2, v1, budget, maxPrice);
    utilize(v3, v1, v2, budget, maxPrice);
    
    
    return maxPrice;
    
}

int runner(){ // func 7 uses functions within
    
    int budget, v1, v2, v3;
    cout << "Please enter your budget: " ; //takes budget input
    cin >> budget;
    if (budgetCheck(budget) == false ){ //if budgetCheck returns false i.e. if it is < 0
        cout << "Budget cannot be negative." << endl;
    }
    if(budgetCheck(budget) == true){ // if it is > 0
        cout << "Please enter three quantities: "; //cont execution of qs.
        cin >> v1 >> v2 >> v3;
        
        if(quantityCheck(v1, v2, v3) == false){ //if quantities are negative
            cout << "All quantities must be positive." << endl;
        }
        else if(quantityCheck(v1, v2, v3) == true){ //if quantites are ok.
            if( budget < v1+v2+v3){ //but cannot afford anything
                cout<<"You cannot afford any of the permutations with these quantities and budget."<<endl;
            }
            else{ //if it is affordable
                cout << "You have " << budget - permutations(v1, v2, v3, budget) << " liras left." << endl;
            }
            
        }
         
    }
    
  

    return 0;
}


int main() {
    
    runner();
    cout<<endl;
    runner();
    cout << endl << "Goodbye!" << endl;

    return 0;
}

