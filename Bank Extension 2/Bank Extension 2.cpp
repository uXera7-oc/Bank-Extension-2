// =====================================================================
// Same Previous Project with Second Extension Added
// Comments have been added to functions that were without comments
// Program: Simple Banking System for Managing Client Records and Users
// =====================================================================

// Bank Project Extension 2.cpp 
// A simple console-based banking system to manage client & user records (Add, Delete, Update, Find, and Display)

#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <fstream>
#include <iomanip>


using namespace std;

string CurrentUserPermission = "";
const string FileName = "ClientsRecords.txt";
const string UsersFileName = "Users.txt";

// Structure to store client data - contains all client information
struct stClientData
{
    string PinCode;
    string AccountNumber;
    string Name;
    string Phone;
    float AccountBalance;
};

// Structure to store user data - contains all user information
struct stUserData
{
    string Username;
    string Password;
    string Permission;
};



// Admin menu options enumeration
enum enAdminMenuOptions { eAdShowList = 1, eAdAddNew, eAdDelete, eAdUpdateInfo, eAdFind, eAdTransaction, eManageUsers ,eLogout };

// Manage menu options enumeration
enum enManageMenu { eListU = 1, eAddU, eDeleteU, eUpdateU , eFindU , eMain  };

// Main menu options enumeration
enum enMenuOptions { eShowList = 1, eAddNew, eDelete, eUpdateInfo, eFind, eTransaction, eExit };

// Trnsaction menu options enumeration
enum enTransactionsMenu { eDeposit = 1, eWithdraw, eTotalBalances, eMainMenu };

// Function to ask user to enter account number
string Ask4AccountNumber()
{
    string AccountNumber;


    cout << "Please Enter Account Number " << endl;
    getline(cin, AccountNumber);

    return AccountNumber;
}

// Function to read username from user input
string ReadUsername()
{
    string Username;

    cout << "Enter Username? " ;
    getline(cin, Username);

    return Username;
}

// Function to read password from user input
string ReadPassword()
{
    string Password;

    cout << "Enter Password? ";
    getline(cin, Password);

    return Password;
}


// Function to split a string into parts based on a delimiter
// Example: "User#//#123" becomes ["User", "123"]
vector <string> SplitString(string S1, string Delim)
{
    vector <string> vString;
    short pos = 0;
    string sWord;


    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); //Store the Word
        if (sWord != Delim)
        {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length());//Erasing until position and move to the next word

    }

    if (S1 != Delim)
    {
        vString.push_back(S1);
    }



    return  vString;
}

// Function to convert a text line from file into organized client data
stClientData ConvertLineToRecord(string Line, string Delim = "#//#")
{
    stClientData ClientData;
    vector <string> vClientData;

    vClientData = SplitString(Line, Delim);


    if (vClientData.size() >= 5)
    {
        ClientData.AccountNumber = vClientData[0];
        ClientData.PinCode = vClientData[1];
        ClientData.Name = vClientData[2];
        ClientData.Phone = vClientData[3];
        ClientData.AccountBalance = stof(vClientData[4]);
    }

    return ClientData;

}

// Function to convert line of text to user data structure
stUserData ConvertLineToRecord4User(string Line, string Delim = "#//#")
{
    stUserData UserData;
    vector <string> vUserData;

    vUserData = SplitString(Line,"#//#");


    if (vUserData.size() >= 3)
    {
        UserData.Username = vUserData[0];
        UserData.Password = vUserData[1];
        UserData.Permission = vUserData[2];
        
    }

    // Returns stUserData structure with Username, Password, and Permission
    return UserData;

}

// Function to read all clients data from file and store them in a list
vector<stClientData> LoadClientDataFromFile(string FileName)
{
    vector <stClientData> vClients;

    fstream ClientsRecords;

    ClientsRecords.open(FileName, ios::in);

    if (ClientsRecords.is_open())
    {
        string Line;
        stClientData Client;

        while (getline(ClientsRecords, Line))
        {
            Client = ConvertLineToRecord(Line);

            vClients.push_back(Client);
        }
        ClientsRecords.close();
    }

    return vClients;

}

// Function to load user data from file
vector <stUserData> LoadUserDataFromFile(string UserFileName)
{
    vector <stUserData> vUsers;

    fstream UsersRecords;

    UsersRecords.open(UserFileName, ios::in);

    if (UsersRecords.is_open())
    {
        string Line;
        stUserData User;

        while (getline(UsersRecords, Line))
        {
            User = ConvertLineToRecord4User(Line);

            vUsers.push_back(User);
        }
        UsersRecords.close();
    }

    return vUsers;

    
}

// Function to print one client record in a formatted line
void PrintClientRecord(stClientData ClientData)
{
    cout << "| " << setw(15) << left << ClientData.AccountNumber;
    cout << "| " << setw(10) << left << ClientData.PinCode;
    cout << "| " << setw(40) << left << ClientData.Name;
    cout << "| " << setw(12) << left << ClientData.Phone;
    cout << "| " << setw(12) << left << ClientData.AccountBalance;
}

// Function to check if an account number exists in the clients list
void CheckClient(string AccountNumber, vector<stClientData> vClientData)
{
    stClientData ClientData;

    for (stClientData& Client : vClientData)
    {

        if (AccountNumber == Client.AccountNumber)
        {
            cout << "Client With Account Number (" << AccountNumber << ") is Already exists , Please Enter Another Account Number ? ";
            return;
        }
    }


}

// Function to print a table containing all clients data
void PrintAllClientsData(vector <stClientData> vClients)
{
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";

    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    for (stClientData ClientData : vClients)
    {
        PrintClientRecord(ClientData);
        cout << endl;
    }

    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}

// Function to print one client data in detail (each field in a separate line)
void PrintClientData(stClientData ClientData)
{
    cout << "Account Number : " << ClientData.AccountNumber << endl;
    cout << "Pin Code       : " << ClientData.PinCode << endl;
    cout << "Name           : " << ClientData.Name << endl;
    cout << "Phone          : " << ClientData.Phone << endl;
    cout << "Account Balance : " << ClientData.AccountBalance << endl;
}

// Function to delete a client record from file
void DeleteRecordFromFile()
{

    vector <stClientData> vClient = LoadClientDataFromFile(FileName);

    string AccountNumber;
    AccountNumber = Ask4AccountNumber();



    bool Found = false;
    stClientData Client;

    // Search for the client
    for (stClientData& C : vClient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            Found = true;
            break;
        }
    }
    if (!Found)
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n";
        return;

    }

    PrintClientData(Client);

    char Answer;

    cout << "\nAre you sure you want to delete this client? (y/n): ";
    cin >> Answer;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');


    if (Answer == 'Y' || Answer == 'y')
    {


        fstream ClientsRecords;

        ClientsRecords.open(FileName, ios::out);

        if (ClientsRecords.is_open())
        {
            // Rewrite all clients except the one to be deleted
            for (stClientData& Client : vClient)
            {
                //U can not Delete a line directly
                if (Client.AccountNumber != AccountNumber)
                {
                    ClientsRecords << Client.AccountNumber << "#//#" << Client.PinCode << "#//#" << Client.Name << "#//#" << Client.Phone << "#//#" << Client.AccountBalance << endl;

                }
            }
            ClientsRecords.close();


        }

        cout << "\n\nClient Deleted Successfully !\n";
    }
    else
    {
        cout << "\nDeletion Cancelled\n";
    }
}

// Function to display the delete client screen
void DeleteClientScreen()
{
    cout << "------------------------------------\n";
    cout << "\tDelete Clients Screen";
    cout << "\n------------------------------------\n";

    DeleteRecordFromFile();
}

// Function to check if an account number exists in clients list (returns true if exists)
bool IsAccountNumberExist(string AccountNumber, vector<stClientData>& vClientData)
{
    for (const stClientData& Client : vClientData)
    {
        if (AccountNumber == Client.AccountNumber)
        {
            cout << "Client With Account Number (" << AccountNumber << ") already exists. Please enter another number.\n";
            return true;
        }
    }
    return false;
}


// Function to read new client data from user
stClientData ReadClientData()
{
    stClientData ClientData;
    vector <stClientData> vClientData = LoadClientDataFromFile(FileName);


    do
    {

        cout << "Enter Account Number ?";
        //ws Will Extract All The Whitespaces Character
        getline(cin >> ws, ClientData.AccountNumber);


    } while (IsAccountNumberExist(ClientData.AccountNumber, vClientData));


    cout << "Enter PIN Code ?";
    getline(cin, ClientData.PinCode);


    cout << "Enter Name ?";
    getline(cin, ClientData.Name);


    cout << "Enter Phone ?";
    getline(cin, ClientData.Phone);


    cout << "Enter Account Balance ?";
    cin >> ClientData.AccountBalance;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');


    return ClientData;



}

// Function to convert client data into a text line ready to save in file
string Convert2Line(stClientData ClientData, string Delim = "#//#")
{
    string ClientRecord = "";

    ClientRecord += ClientData.AccountNumber + Delim;
    ClientRecord += ClientData.PinCode + Delim;
    ClientRecord += ClientData.Name + Delim;
    ClientRecord += ClientData.Phone + Delim;
    ClientRecord += to_string(ClientData.AccountBalance);

    return ClientRecord;
}

// Function to save a new client record in file
void SavingClientReccord(string ClientRecord)
{
    fstream ClientsRecordsFile;

    ClientsRecordsFile.open("ClientsRecords.txt", ios::out | ios::app);

    if (ClientsRecordsFile.is_open())
    {
        ClientsRecordsFile << ClientRecord << endl;

        ClientsRecordsFile.close();
    }

}

// Function to add a new client (reads data then saves it)
void AddNewClient()
{
    stClientData ClientData;

    ClientData = ReadClientData();

    SavingClientReccord(Convert2Line(ClientData, "#//#"));

}

// Function to ask user if they want to add more clients
void Asking2AddClients()
{
    char Answer;

    do
    {

        cout << "\nAdding New Client : \n" << endl;
        AddNewClient();

        cout << "\n\nClient Add Successfully , do You Want to Add More ? [Y/N]\n";
        cin >> Answer;

    } while (Answer == 'Y' || Answer == 'y');
}

// Function to display add new client screen
void AddNewClientScreen()
{
    cout << "------------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n------------------------------------\n";



    Asking2AddClients();
}

// Function to update existing client data
void UpdateClientRecord(string AccountNumber)
{

    vector <stClientData> vClient = LoadClientDataFromFile(FileName);

    bool Found = false;
    stClientData Client;

    // Search for the client
    for (stClientData& C : vClient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            Found = true;
            break;
        }
    }
    if (!Found)
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n";
        return;

    }

    cout << "Current Client Data :\n";
    PrintClientData(Client);

    char Answer;

    cout << "\nAre you sure you want to Update this client? (y/n): ";
    cin >> Answer;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');


    if (Answer != 'Y' && Answer != 'y')
    {
        cout << "\nUpdate Cancelled.\n";
        return;
    }


    // Read new data
    cout << "Enter Pin Code :";
    getline(cin, Client.PinCode);

    cout << "Enter Name :";
    getline(cin, Client.Name);

    cout << "Enter Phone :";
    getline(cin, Client.Phone);

    cout << "Enter Account Balance :";
    cin >> Client.AccountBalance;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Update data in the list
    for (stClientData& C : vClient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C = Client;
            break;
        }
    }

    // Save all data to file
    fstream ClientsRecords;

    ClientsRecords.open(FileName, ios::out);

    if (ClientsRecords.is_open())
    {

        for (stClientData& Client : vClient)
        {
            ClientsRecords << Client.AccountNumber << "#//#" << Client.PinCode << "#//#" << Client.Name << "#//#" << Client.Phone << "#//#" << Client.AccountBalance << endl;
        }
        ClientsRecords.close();


    }

    cout << "\nClient Updated Successfully !\n";
}

// Function to display update client screen
void UpdateClientInfoScreen()
{
    cout << "------------------------------------\n";
    cout << "\tUpdate Clients Screen";
    cout << "\n------------------------------------\n";

    UpdateClientRecord(Ask4AccountNumber());

}

// Function to search for a client and print their data
void CheckClient2Find(string AccountNumber, vector<stClientData> vClientData)
{
    stClientData ClientData;

    for (stClientData& Client : vClientData)
    {

        if (AccountNumber == Client.AccountNumber)
        {
            PrintClientData(Client);
            return;
        }
    }
    cout << "Client With Account Number (" << AccountNumber << ") Not Found ! " << endl;

}

// Function to check user credentials during login
// Compares entered username and password with stored user data
bool CheckUserInLogin(string Password,string Username )
{

    vector <stUserData> vUserData = LoadUserDataFromFile(UsersFileName);

    for (stUserData& User : vUserData)
    {

        if (Username == User.Username && Password == User.Password)
        {
            // Returns true if credentials match, false otherwise
            return true;
        }
        
    }
            return false;
 
}

// Function to display find client screen
void FindClientScreen()
{
    vector <stClientData> vClient = LoadClientDataFromFile(FileName);
    cout << "\n------------------------------------\n";
    cout << "\tFind Clients Screen";
    cout << "\n------------------------------------\n";

    CheckClient2Find(Ask4AccountNumber(), vClient);

}

// Function to ask user to press any key to return to main menu
void PressAnyKeyFunction()
{

    cout << "Press Any Key to go back to Main Menu...";
    system("pause>0");

}

// Function to ask user for the desired action in the transactions menu
short AskWhatToDo()
{
    short Number;
    cout << "Choose What Do you Want to do ? [1 to 4] ?";
    cin >> Number;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return Number;

}

// Function to ask for operation choice in menu (1 to 6)
short AskWhatToDo1to6()
{
    short Number;
    cout << "Choose What Do you Want to do ? [1 to 6] ?";
    cin >> Number;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return Number;

}

// Function to display the transaction menu screen
void TransactionMenuScreen()
{
    system("cls");
    cout << "================================================\n";
    cout << "\t\Transaction Menu Screen\n";
    cout << "================================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balance.\n";
    cout << "\t[4] Main Menu.\n";
    cout << "================================================\n";


}

//Function to perform deposit operation
//Searches for client, requests amount, updates balance, and saves changes to file
void DepositOperation()
{
    vector <stClientData> vClientData = LoadClientDataFromFile(FileName);


    string AccountNumber = Ask4AccountNumber();

    CheckClient2Find(AccountNumber, vClientData);

    float Amount;
    float NewBalance = 0;
    char Answer;


    cout << "\nPlease Enter Deposit Amount? ";
    cin >> Amount;

    for (stClientData& Client : vClientData)
    {

        if (AccountNumber == Client.AccountNumber)
        {
            Client.AccountBalance += Amount;
            NewBalance = Client.AccountBalance;

            break;
        }
    }


    cout << "\n\nAre you sure you want perform this transaction [Y/N] ? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        // Save all data to file
        fstream ClientsRecords;

        ClientsRecords.open(FileName, ios::out);

        if (ClientsRecords.is_open())
        {

            for (stClientData& Client : vClientData)
            {
                ClientsRecords << Client.AccountNumber << "#//#" << Client.PinCode << "#//#" << Client.Name << "#//#" << Client.Phone << "#//#" << Client.AccountBalance << endl;
            }
            ClientsRecords.close();

        }
        cout << "Deposit Done Successfully , New Balance is : " << NewBalance << endl << endl;

    }
    else
    {
        cout << "Deposit Cancelled ! " << endl;
    }
    vClientData = LoadClientDataFromFile(FileName);




}

// Displays screen title and calls the deposit operation function
void DepositScreen()
{
    cout << "\n------------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n------------------------------------\n";

    DepositOperation();


}

// Function to perform withdraw operation
// Searches for client, verifies sufficient balance, executes withdrawal, and saves changes
void WithdrawOperation()
{
    vector <stClientData> vClientData = LoadClientDataFromFile(FileName);

    string AccountNumber = Ask4AccountNumber();

    CheckClient2Find(AccountNumber, vClientData);

    float Amount;
    float NewBalance = 0;
    char Answer;

    cout << "\nPlease Enter Withdraw Amount? ";
    cin >> Amount;

    for (stClientData& Client : vClientData)
    {

        if (AccountNumber == Client.AccountNumber)
        {
            if (Amount > Client.AccountBalance)
            {
                cout << "Amount Exceeds the balance, You can withdraw up to : " << Client.AccountBalance << endl;
                cout << "\nPlease Enter Another Amount? ";
                cin >> Amount;
            }
            else
            {
                Client.AccountBalance -= Amount;
                NewBalance = Client.AccountBalance;
            }

            break;
        }
    }


    cout << "\n\nAre you sure you want perform this transaction [Y/N] ? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        // Save all data to file
        fstream ClientsRecords;

        ClientsRecords.open(FileName, ios::out);

        if (ClientsRecords.is_open())
        {

            for (stClientData& Client : vClientData)
            {
                ClientsRecords << Client.AccountNumber << "#//#" << Client.PinCode << "#//#" << Client.Name << "#//#" << Client.Phone << "#//#" << Client.AccountBalance << endl;
            }
            ClientsRecords.close();

        }
        cout << "Withdraw Done Successfully , New Balance is : " << NewBalance << endl << endl;

    }
    else
    {
        cout << "Withdraw Cancelled ! " << endl;
    }
    vClientData = LoadClientDataFromFile(FileName);



}

// Function to display the withdraw screen
void WithdrawScreen()
{
    cout << "\n------------------------------------\n";
    cout << "\tWithdraw Screen";
    cout << "\n------------------------------------\n";

    WithdrawOperation();

}

// Function to print a single client record in the total balances list
void PrintClientRecordForTotalBalances(stClientData ClientData)
{
    cout << "| " << setw(15) << left << ClientData.AccountNumber;
    cout << "| " << setw(40) << left << ClientData.Name;
    cout << "| " << setw(12) << left << ClientData.AccountBalance;


}

// Function to print all client data and calculate total balances
void PrintAllClientsDataForTotalBalances(vector <stClientData> vClients)
{
    float TotalBalances = 0;

    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";

    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    for (stClientData ClientData : vClients)
    {
        PrintClientRecordForTotalBalances(ClientData);
        TotalBalances += ClientData.AccountBalance;
        cout << endl;
    }

    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;


    cout << "\t\t\t\nTotalBalances = " << TotalBalances << endl;

}

// Function to display the total balances screen
void ToalBalancesScreen()
{
    // Loads client data and displays the balances table with total
    vector <stClientData> vClients = LoadClientDataFromFile(FileName);

    PrintAllClientsDataForTotalBalances(vClients);

}


// Function to display the main menu of the program
void MainMenuScreen()
{
    system("cls");
    cout << "================================================\n";
    cout << "\t\tMain Menu Screen\n";
    cout << "================================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transaction.\n";
    cout << "\t[7] Exit.\n";
    cout << "================================================\n";

}

// Function to display admin main menu screen
void AdminMainMenuScreen()
{
    system("cls");
    cout << "================================================\n";
    cout << "\t\tMain Menu Screen\n";
    cout << "================================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transaction.\n";
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Logout.\n";
    cout << "================================================\n";
}

// Function to display manage users menu screen
void ManageUsersMenuScreen()
{
    system("cls");
    cout << "================================================\n";
    cout << "\t\tManage Users Menu Screen\n";
    cout << "================================================\n";
    cout << "\t[1] List Users.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menu.\n";
    cout << "================================================\n";
}

// Function to print a single user record in formatted table row
void PrintUserRecord(stUserData UserData)
{
    cout << "| " << setw(20) << left << UserData.Username;
    cout << "| " << setw(15) << left << UserData.Password;
    cout << "| " << setw(15) << left << UserData.Permission;
}

// Function to display all users data in formatted table
void PrintAllUsersData(vector<stUserData> vUsers)
{
    cout << "\n\t\t\t\t\tUser List (" << vUsers.size() << ") User(s).";

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(20) << "Username";
    cout << "| " << left << setw(15) << "Password";
    cout << "| " << left << setw(15) << "Permission";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    for (stUserData UserData : vUsers)
    {
        PrintUserRecord(UserData);
        cout << endl;
    }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

// Function to display list of all users screen
void ListUsersScreen()
{
    vector <stUserData> vUsers = LoadUserDataFromFile(UsersFileName);
    PrintAllUsersData(vUsers);

}

// Function to check if username already exists in system
bool IsUsernameExist(string Username, vector <stUserData>& vUserData)
{
    // Searches through existing user data to prevent duplicate usernames
    for (stUserData& User : vUserData)
    {
        if (Username == User.Username)
        {
            cout << "User with Username (" << Username << ") Already exists. Please enter another Username !\n";
            return true;
            // Returns true if username exists, false otherwise

        }
    }
    return false;
}

// Function to read permission settings for new user
// Returns permission value as bitmask (or -1 for full access)
short ReadPermissions()
{
    short Permission = 0;
    char Answer;

    cout << "\nDo you want to give full access? (y/n)";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        return Permission = -1;
    }


     cout << "\nDo you want to give Access to : \n";

     cout << "\nShow Client List ? (y/n) ?";
     cin >> Answer;
     if (Answer == 'y' || Answer == 'Y')
     {
         Permission |= (1 << 0);
     }
     
     cout << "\nAdd New Client ? (y/n) ?";
     cin >> Answer;
     if (Answer == 'y' || Answer == 'Y')
     {
         Permission |= (1 << 1);
     }

     cout << "\nDelete Client ? (y/n) ?";
     cin >> Answer;
     if (Answer == 'y' || Answer == 'Y')
     {
         Permission |= (1 << 2);
     }


     cout << "\nUpdate Client ? (y/n) ?";
     cin >> Answer;
     if (Answer == 'y' || Answer == 'Y')
     {
         Permission |= (1 << 3);
     }



     cout << "\nFind Client ? (y/n) ?";
     cin >> Answer;
     if (Answer == 'y' || Answer == 'Y')
     {
         Permission |= (1 << 4);
     }


     cout << "\nTransactions ? (y/n) ?";
     cin >> Answer;
     if (Answer == 'y' || Answer == 'Y')
     {
         Permission |= (1 << 5);
     }



     cout << "\nManage Users ? (y/n) ?";
     cin >> Answer;
     if (Answer == 'y' || Answer == 'Y')
     {
         Permission |= (1 << 6);
     }

     return Permission;

}

// Function to check if user has specific permission
bool CheckPermission(string UserPermission, short RequiredPermissionBit)
{
    if (UserPermission == "-1")
        return true;

    try 
    {
        short PermValue = stoi(UserPermission);
        return(PermValue & (1 << RequiredPermissionBit)) != 0;
    }
    catch (...)
    {
        return false;
    }
}

// Function to get current user's permission level
string GetCurrentUserPermission(string Username)
{
    vector<stUserData> vUserData = LoadUserDataFromFile(UsersFileName);

    for (stUserData& User : vUserData)
    {
        if (Username == User.Username)
        {
            return User.Permission;
        }
    }
    return"0"; //No Permissions
}

// Function to read new user data from console input
stUserData ReadNewUserData()
{
    stUserData UserData;
    vector<stUserData> vUserData = LoadUserDataFromFile(UsersFileName);

    
        
        do
        {
            cout << "\nEnter Username? ";
            getline(cin >> ws, UserData.Username);
        } while (IsUsernameExist(UserData.Username, vUserData));

        cout << "Enter Password? ";
        getline(cin, UserData.Password);

        short PermissionValue = ReadPermissions();
        UserData.Permission = to_string(PermissionValue);

        return UserData;
    
}

// Function to convert user data structure to formatted string line
string ConvertUser2Line(stUserData UserData, string Delim = "#//#")
{
    string UserRecord = "";
    UserRecord += UserData.Username + Delim;
    UserRecord += UserData.Password + Delim;
    UserRecord += UserData.Permission;
    
    return UserRecord;
}

// Function to save user record to file
// Appends new user information to Users.txt file
void SavingUserRecord(string UserRecord)
{
    fstream UsersRecordFile;
    UsersRecordFile.open(UsersFileName, ios::out | ios::app);

    if (UsersRecordFile.is_open())
    {
        UsersRecordFile << UserRecord << endl;
        UsersRecordFile.close();
    }
}

// Function to add new user to system
void AddNewUser()
{
    stUserData UserData = ReadNewUserData();
    SavingUserRecord(ConvertUser2Line(UserData, "#//#"));

}

// Function to prompt for adding multiple users
void Asking2AddUsers()
{
    char Answer;

    do
    {
        cout << "\nAdding New User : \n" << endl;
        AddNewUser();

        cout << "\n\nUser Added Successfully, do You want to add More ? (y/n)\n";
        cin >> Answer;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (Answer == 'y' || Answer == 'Y');
}

// Function to display add new user screen interface
void AddNewUserScreen()
{
    cout << "------------------------------------\n";
    cout << "\tAdd New User Screen";
    cout << "\n------------------------------------\n";

    Asking2AddUsers();

}

// Function to delete user from file system
void DeleteUserFromFile(string Username)
{
    vector<stUserData> vUsers = LoadUserDataFromFile(UsersFileName);
    

    bool Found = false;
    stUserData User;

    //Search for the User
    for (stUserData& U : vUsers)
    {
        if (U.Username == Username)
        {
            User = U;
            Found = true;
            break;
        }
    }

    if (!Found)
    {
        cout << "\nUser With Username (" << Username << ") is Not Found!\n";
        return;
    }

    cout << "\nUser Data to Delete : \n";
    cout << "Username : " << User.Username << endl;
    cout << "Password : " << User.Password << endl;
    cout << "Permission : " << User.Permission << endl;

    char Answer;
    cout << "\nAre You sure you want to delete this user? (y/n)";
    cin >> Answer;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (Answer == 'y' || Answer == 'Y')
    {
        fstream UsersRecords;
        UsersRecords.open(UsersFileName, ios::out);

        if (UsersRecords.is_open())
        {
            //Rewrite All users Except the one to be deleted
            for (stUserData& U : vUsers)
            {
                if (U.Username != Username)
                {
                    UsersRecords << U.Username << "#//#" << U.Password << "#//#" << U.Permission << endl;
                }
            }
        UsersRecords.close();
        cout << "\n\nUser Deleted Successfully!\n";
        }
    }
    else
        cout << "\nDeletion Cancelled\n";
}

// Function to display delete user screen interface
void DeleteUserScreen()
{
    cout << "------------------------------------\n";
    cout << "\tDelete User Screen";
    cout << "\n------------------------------------\n";

    string Username;
    cout << "\nPlease Enter Username to Delete : ";
    getline(cin, Username);

    DeleteUserFromFile(Username);

}

// Function to update existing user record
void UpdateUserRecord(string Username)
{
    vector<stUserData> vUsers = LoadUserDataFromFile(UsersFileName);

    bool Found = false;
    stUserData User;

    //Search fo User
    for (stUserData& U : vUsers)
    {
        if (U.Username == Username)
        {
            User = U;
            Found = true;
            break;
        }
    }

    if (!Found)
    {
        cout << "\nUser with Username (" << Username << ") is Not Found!\n";
        return;
    }

    cout << "Current User Data:\n";
    cout << "Username : " << User.Username << endl;
    cout << "Password : " << User.Password << endl;
    cout << "Permission : " << User.Permission << endl;

    char Answer;
    cout << "Are you sure you want to update this user? (y/n) : ";
    cin >> Answer;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (Answer != 'Y' && Answer != 'y')
    {
        cout << "\nUpdate Cancelled.\n";
        return;
    }

    //Read New Data
    cout << "Enter New Password ?  ";
    getline(cin, User.Password);

    cout << "\nUpdate Permissions :\n";
    short PermissionValue = ReadPermissions();
    User.Permission = to_string(PermissionValue);

    //Update data in the list
    for (stUserData& U : vUsers)
    {
        if (U.Username == Username)
        {
            U = User;
            break;
        }
    }

    //Save All data to file
    fstream UsersRecord;
    UsersRecord.open(UsersFileName, ios::out);

    if (UsersRecord.is_open())
    {
        for (stUserData& User : vUsers)
        {
            UsersRecord << User.Username << "#//#" << User.Password << "#//#" << User.Permission << endl;
        }

        UsersRecord.close();
        cout << "\nUser Updated Successfully!\n";
        
    }

}

// Function to display update user screen interface
void UpdateUserScreen()
{
    cout << "------------------------------------\n";
    cout << "\tUpdate User Screen";
    cout << "\n------------------------------------\n";

    string Username;
    cout << "Please Enter Username to Update : ";
    getline(cin, Username);

    UpdateUserRecord(Username);
}

// Function to find and display user information
void FindUser(string Username)
{
    vector <stUserData> vUsers = LoadUserDataFromFile(UsersFileName);

    for (stUserData& User : vUsers)
    {
        if (Username == User.Username)
        {
            cout << "\n User Found :\n";
            cout << "Username : " << User.Username << endl;
            cout << "Password : " << User.Password << endl;
            cout << "Permission : " <<User.Permission << endl;
            return;
        }
    }
    cout << "\nUser with Username (" << Username << ")Not Found!\n";

}

// Function to display find user screen interface
void FindUserScreen()
{
    cout << "------------------------------------\n";
    cout << "\tFind User Screen";
    cout << "\n------------------------------------\n";

    string Username;
    cout << "Please Enter Username to Find: ";
    getline(cin, Username);

    FindUser(Username);
}


// Function to ask user to choose an option from the menu
short AskForOperation()
{
    short Number;
    cout << "Choose What Do you Want to do ? [1 to 8] ?";
    cin >> Number;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return Number;
}

// Function to convert option number to enum value
enMenuOptions ChoosingOption(short Number)
{

    switch (Number)
    {
    case 1:      return eShowList;

    case 2:      return eAddNew;

    case 3:      return eDelete;

    case 4:      return eUpdateInfo;

    case 5:      return eFind;

    case 6:      return eTransaction;

    case 7:      return eExit;

    }

}

// Function to convert option number to enum value in transactions menu
enTransactionsMenu ChoosingOperation(short Number)
{
    switch (Number)
    {
    case 1:      return eDeposit;

    case 2:      return eWithdraw;

    case 3:      return eTotalBalances;

    case 4:      return eMainMenu;
    }
}

// Function to convert option number to admin menu enum value
enAdminMenuOptions ChoosingAdminOperation(short Number)
{
    switch (Number)
    {
    case 1: return eAdShowList;

    case 2: return eAdAddNew;

    case 3: return eAdDelete;

    case 4: return eAdUpdateInfo;

    case 5: return eAdFind;

    case 6: return eAdTransaction;

    case 7: return eManageUsers;

    case 8: return eLogout;
    }
}

// Function to convert option number to manage users menu enum value
enManageMenu ChoosingManagingOperation(short Number)
{
    switch (Number)
    {
    case 1:  return eListU;

    case 2:  return eAddU;

    case 3:  return eDeleteU;

    case 4:  return eUpdateU;

    case 5:  return eFindU;

    case 6:  return eMain;
    }
}

// Function to execute manage users menu operations
void PerformManagingMenuOption()
{
    vector <stUserData> vUsers = LoadUserDataFromFile(UsersFileName);

    enManageMenu Operation;
    do
    {
        ManageUsersMenuScreen();

        Operation = (enManageMenu)AskWhatToDo1to6();

        switch (Operation)
        {
        case eListU :
            system("cls");
            ListUsersScreen();  // gg
            PressAnyKeyFunction();
            break;

        case eAddU : 
            system("cls");
            AddNewUserScreen(); //gg
            PressAnyKeyFunction();
            break;

        case eDeleteU : 
            system("cls");
            DeleteUserScreen(); // gg
            PressAnyKeyFunction();
             break; 


        case eUpdateU : 
            system("cls");
            UpdateUserScreen(); // gg
            PressAnyKeyFunction();
            break;


        case eFindU:
            system("cls");
            FindUserScreen(); // gg
            PressAnyKeyFunction();
            break;


        case eMain : 
            return;



        default:
            system("cls");
            cout << "\nError: Invalid Option! Please enter a number between 1 and 6.\n";
            PressAnyKeyFunction();
            break;





        }



    } while (Operation != eMain);
}

//Displays menu and performs selected option until user chooses to return to main
void PerformTransactionMenuOption()
{

    enTransactionsMenu Operation;
    do
    {

        TransactionMenuScreen();

        vector <stClientData> vClient;
        vClient = LoadClientDataFromFile(FileName);

        Operation = (enTransactionsMenu)AskWhatToDo();


        switch (Operation)
        {
        case eDeposit:
            system("cls");
            DepositScreen();
            PressAnyKeyFunction();
            break;

        case eWithdraw:
            system("cls");
            WithdrawScreen();
            PressAnyKeyFunction();
            break;



        case eTotalBalances:
            system("cls");
            ToalBalancesScreen();
            PressAnyKeyFunction();
            break;



        case eMainMenu:
            return;



        default:
            system("cls");
            cout << "\nError: Invalid Option! Please enter a number between 1 and 4.\n";
            PressAnyKeyFunction();
            break;
        }





    } while (Operation != eMainMenu);

}

// Function to display exit screen
void ExitScreen()
{
    cout << "\n------------------------------------\n";
    cout << "\tProgram Ends : )\n";
    cout << "\n------------------------------------\n";

    system("pause>0");

}


// Function to execute the option chosen by user from the main menu
void PerformMenuOption()
{
    enMenuOptions Option;

    MainMenuScreen();
    vector <stClientData> vClient;
    vClient = LoadClientDataFromFile(FileName);

    do
    {
        MainMenuScreen();
        Option = ChoosingOption(AskForOperation());


        switch (Option)
        {
        case eShowList:
            system("cls");
            PrintAllClientsData(LoadClientDataFromFile(FileName));
            PressAnyKeyFunction();
            break;


        case eAddNew:
            system("cls");
            AddNewClientScreen();
            vClient = LoadClientDataFromFile(FileName);
            PressAnyKeyFunction();
            break;


        case eDelete:
            system("cls");
            DeleteClientScreen();
            vClient = LoadClientDataFromFile(FileName);
            PressAnyKeyFunction();
            break;


        case eUpdateInfo:
            system("cls");
            UpdateClientInfoScreen();
            vClient = LoadClientDataFromFile(FileName);
            PressAnyKeyFunction();
            break;

        case eFind:
            system("cls");
            FindClientScreen();
            PressAnyKeyFunction();
            break;


        case eTransaction:
            system("cls");
            PerformTransactionMenuOption();
            break;


        case eExit:
            system("cls");
            ExitScreen();
            break;

        default:
            system("cls");
            cout << "\nError: Invalid Option! Please enter a number between 1 and 7.\n";
            PressAnyKeyFunction();
            break;



        }

    } while (Option != eExit);



}

// Function to display login screen
void LoginScreen()
{
    string Username, Password;

    vector <stUserData> vUserData = LoadUserDataFromFile(UsersFileName);

    cout << "\n------------------------------------\n";
    cout << "\tLogin Screen";
    cout << "\n------------------------------------\n";

    while (true)
    {
       Username =  ReadUsername();
       Password = ReadPassword();

       if (!(CheckUserInLogin(Password, Username)))
       {
           system("cls");
           cout << "\n------------------------------------\n";
           cout << "\tLogin Screen";
           cout << "\n------------------------------------\n";
           cout << "Invalid Username/Password!\n";

       }
       else
       {
           CurrentUserPermission = GetCurrentUserPermission(Username);

           return;


       }

    }   

}

// Function to display access denied message
void ShowAccessDeniedMessage()
{
    cout << "\n------------------------------------------------------------\n";
    cout << "Access Denied,\n";
    cout << "You don't Have Permission to do this,\n";
    cout << "Please Contact Your Admin\n";
    cout << "------------------------------------------------------------\n";
}

// Function to execute admin main menu operations
void PerformAdminMenuOption()
{
    enAdminMenuOptions Option;

    vector <stUserData> vUserData = LoadUserDataFromFile(UsersFileName);
    vector <stClientData> vClient = LoadClientDataFromFile(FileName);


        LoginScreen();
    do
    {
        AdminMainMenuScreen();

        Option = ChoosingAdminOperation(AskForOperation());


        switch (Option)
        {
        case eAdShowList:
            if (!CheckPermission(CurrentUserPermission, 0))
            {
                system("cls");
                ShowAccessDeniedMessage();
                PressAnyKeyFunction();
                break;

            }
            system("cls");
            PrintAllClientsData(LoadClientDataFromFile(FileName));
            PressAnyKeyFunction();
            break;


        case eAdAddNew:
            if (!CheckPermission(CurrentUserPermission, 1))
            {
                system("cls");
                ShowAccessDeniedMessage();
                PressAnyKeyFunction();
                break;

            }
            system("cls");
            AddNewClientScreen();
            vClient = LoadClientDataFromFile(FileName);
            PressAnyKeyFunction();
            break;


        case eAdDelete:
            if (!CheckPermission(CurrentUserPermission, 2))
            {
                system("cls");
                ShowAccessDeniedMessage();
                PressAnyKeyFunction();
                break;

            }
            system("cls");
            DeleteClientScreen();
            vClient = LoadClientDataFromFile(FileName);
            PressAnyKeyFunction();
            break;


        case eAdUpdateInfo:
            if (!CheckPermission(CurrentUserPermission, 3))
            {
                system("cls");
                ShowAccessDeniedMessage();
                PressAnyKeyFunction();
                break;

            }
            system("cls");
            UpdateClientInfoScreen();
            vClient = LoadClientDataFromFile(FileName);
            PressAnyKeyFunction();
            break;



        case eAdFind:
            if (!CheckPermission(CurrentUserPermission, 4))
            {
                system("cls");
                ShowAccessDeniedMessage();
                PressAnyKeyFunction();
                break;

            }
            system("cls");
            FindClientScreen();
            PressAnyKeyFunction();
            break;


        case eAdTransaction:
            if (!CheckPermission(CurrentUserPermission, 5))
            {
                system("cls");
                ShowAccessDeniedMessage();
                PressAnyKeyFunction();
                break;

            }
            system("cls");
            PerformTransactionMenuOption();
            break;
            
        case eManageUsers:
            if (!CheckPermission(CurrentUserPermission, 6))
            {
                system("cls");
                ShowAccessDeniedMessage();
                PressAnyKeyFunction();
                break;

            }
            system("cls");
            PerformManagingMenuOption(); //will be changed!!!!!!
            break;


        case eLogout:
            system("cls");
            CurrentUserPermission = ""; //Clean User Permissions
            break;

        default:
            system("cls");
            cout << "\nError: Invalid Option! Please enter a number between 1 and 8.\n";
            PressAnyKeyFunction();
            break;



        }

    } while (Option != eLogout);



}

// Function to initialize login process
void Login()
{
    PerformAdminMenuOption();
}


// Main function - starting point of the program
int main()
{
   

    //You should Start by "[2] Add New Client" to Create The txt File !

    Login();

    system("pause>0");
    return 0;
}







