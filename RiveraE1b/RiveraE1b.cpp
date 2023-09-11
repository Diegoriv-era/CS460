/*                   
                    _______________________________________
                    |      CS460 Excercise 1 - Part B     |
                    |       Fall 2023   Dr. Tia Watts     |
                    |                                     |
                    |        Diego Rivera 08-23-23        |
                    |_____________________________________|
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <stdio.h>
#include <vector>
using namespace std;


/*________________________________________________________________
 |  The printCoins function is used to print the ammount of      |  
 |  coins given with the proper plurization. Reduces Redundancy  |
 |                                                               |   
 |  - moneyName = The name of the denomination given             |
 |  - coinAmmount = The number of coins given                    |
 |________________________________________________________________*/
void printCoins(string moneyName, int coinAmmount){ 
    cout << coinAmmount << moneyName;
    if(coinAmmount > 1){
        cout << "s"; // Makes the coin/bill/denomination plural
    }
    cout << endl;

}

int main(int argc, char **argv) {
    cout << argv[1] << endl;
    string purchases = argv[1], transaction;
    float transaction_Total, payment;
    int transaction_Count = 0;
    ifstream purchases_File;


/*__________________________________________________________________________
 |  Decided to use vectors since the goal is to give the least             |  
 |  ammount of change necessary. By adding the names of the denominations  |   
 |  into a list and adding the coin ammount into another list relative     |
 |  to the denomiations we can traverse from the highest to the lowest     |
 |  coin ammount (working with coins rather than bills to avoid demimals)  |
 |                                                                         |
 |  - change_Names = Name of bills/coins                                   |
 |  - change_Coins = Corresponding value of bills/coins (all in coins)     |
 |__________________________________________________________________________*/
    vector<string> change_Names = {
        " $50 bill", " $20 bill", " $10 bill", " $5 bill", " $1 bill", " 50-cent coin" , " 25-cent coin",
        " 10-cent coin", " 5-cent coin", " 1-cent coin"
    };

    vector<int> change_Coins = {
        5000, 2000, 1000, 500, 100, 50, 25, 10, 5, 1
    };

    purchases_File.open(purchases);
    if (!purchases_File.is_open()){
        cout << "Could NOT open: " << purchases << endl;
    }
    else{
        while(!purchases_File.eof()){
            int change = 0;
            transaction_Count += 1;
            
            getline(purchases_File, transaction);
            stringstream ssTransaction(transaction);
            
            ssTransaction >> transaction_Total;  // Converting the string line into two separate float numbers
            ssTransaction >> payment;

            if (payment == 0.0 && transaction_Total == 0.0){  
                break;                          // If both the transaction total and payment are 0 then break;
            }
            else if (payment == transaction_Total){
                cout << "TRANSACTION #" << transaction_Count << ':' << endl;
                cout << "$0.00" << endl << endl;
            }
            else {
                cout << "TRANSACTION #" << transaction_Count << ':' << endl;
                cout << "$" << fixed << setprecision(2) << payment - transaction_Total << endl;

                int payment_Cents = round(payment * 100);                           //Converts both payment and transaction total into cents.
                int transaction_TotalCents = round(transaction_Total * 100);        //To avoid decimals and for precision error its also rounded.
                change = (payment_Cents - transaction_TotalCents);
                
                for (int i = 0; i < 10; i++){ //Looping through all money denominations
                    int coin_Ammount = change / change_Coins.at(i);
                    if (coin_Ammount > 0){
                        change -= change_Coins.at(i) * coin_Ammount;
                        printCoins(change_Names.at(i), coin_Ammount);
                    }
                }
                cout << endl;
            }
        }
    }
    return 0;
}