#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

//##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##
struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance = 0;
    bool MarkForDelete = false;
};
struct stUser
{
    string Username;
    string Password;
    int Permissions = 0;
    bool MarkForDelete = false;
};

//##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##
enum enTransactionsMenueOptions {
    eDeposit = 1, eWithdraw = 2, eShowTotalBalance = 3,
    eShowMainMenue = 4
};
enum enMangerUsersMenueOptions {
    eShowListUser = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4,
    eFindUser = 5, eMainMenue = 6
};
enum enMainMenueOptions {
    eListClients = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClient = 4,
    eFindClient = 5, eShowTransactionsMenue = 6, ManageUsers = 7, Logout = 8
};
enum enMainMenuePermissions {
    pAll = -1, pListClient = 1, pAddNewClient = 2, pDeleteClient = 4,
    pUpdateClient = 8, pFindClient = 16, pShowTransactionsMenue = 32, pManageUsers = 64
};

//##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##
const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";
stUser CurrentUser;

//##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##
void ShowMainMenue();
void ShowManagerUsers();
void ShowTransactionsMenue();
void Login();

//##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##
string ReadClientAccountNumber()
{
    string AccountNumber = "";

    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;

}
string ReadUsername()
{
    string Username = "";

    cout << "\nPlease enter Username? ";
    getline(cin >> ws, Username);
    return Username;

}
short ReadTransactionsMenueOption()
{
    cout << "Choose what do you want to do? [1 to 4]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}
short ReadManagerUserMenueOption()
{
    cout << "Choose what do you want to do? [1 to 6]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}
void ReadLoginInfo(string& Username, string& Password) {

    cout << "\nEnter Username? : ";
    getline(cin >> ws, Username);

    cout << "Enter Password? : ";
    getline(cin >> ws, Password);
}
short ReadMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 8]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}
int ReadPermissionsToSet() {
    int Permissions = 0;
    char Answer = 'n';
    cout << "\nDo you want to give full access? y/n? ";
    cin >> Answer;

    if (tolower(Answer) == 'y')
    {
        return -1;
    }
    cout << "\nDo you want to give access to : \n ";

    cout << "\nShow Client List? y/n? ";
    cin >> Answer;
    if (tolower(Answer) == 'y')
    {
        Permissions += enMainMenuePermissions::pListClient;
    }
    cout << "\nAdd New Client? y/n? ";
    cin >> Answer;
    if (tolower(Answer) == 'y')
    {
        Permissions += enMainMenuePermissions::pAddNewClient;
    }
    cout << "\nDelete Client? y/n? ";
    cin >> Answer;
    if (tolower(Answer) == 'y')
    {
        Permissions += enMainMenuePermissions::pDeleteClient;
    }
    cout << "\nUpdate Client? y/n? ";
    cin >> Answer;
    if (tolower(Answer) == 'y')
    {
        Permissions += enMainMenuePermissions::pUpdateClient;
    }
    cout << "\nFind  Client? y/n? ";
    cin >> Answer;
    if (tolower(Answer) == 'y')
    {
        Permissions += enMainMenuePermissions::pFindClient;
    }
    cout << "\nTransactions? y/n? ";
    cin >> Answer;
    if (tolower(Answer) == 'y')
    {
        Permissions += enMainMenuePermissions::pShowTransactionsMenue;
    }
    cout << "\nManage Users? y/n? ";
    cin >> Answer;
    if (tolower(Answer) == 'y')
    {
        Permissions += enMainMenuePermissions::pManageUsers;
    }
    return Permissions;
}
bool CheckAccessPermission(enMainMenuePermissions Permmission)
{
    if (CurrentUser.Permissions == enMainMenuePermissions::pAll)
        return true;

    if ((Permmission & CurrentUser.Permissions) == Permmission)
        return true;
    else
        return false;
}

//##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##
vector<string> SplitString(string S1, string Delim)
{

    vector<string> vString;

    short pos = 0;
    string sWord; // define a string variable  

    // use find() function to get the position of the delimiters  
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word   
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
    }

    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }

    return vString;

}
sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{

    sClient Client;
    vector<string> vClientData;

    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);//cast string to double


    return Client;

}
string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{

    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;

}
stUser ConvertLinetoUserRecord(string Line, string Seperator = "#//#") {

    stUser user;
    vector<string> vUsersData;

    vUsersData = SplitString(Line, Seperator);
    user.Username = vUsersData[0];
    user.Password = vUsersData[1];
    user.Permissions = stoi(vUsersData[2]);

    return user;
}
string ConvertUserRecordToLine(stUser User, string seperator = "#//#") {
    string Line;
    Line += User.Username + seperator;
    Line += User.Password + seperator;
    Line += to_string(User.Permissions);

    return Line;
}

//##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##
vector <sClient> LoadCleintsDataFromFile(string FileName)
{

    vector <sClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {

            Client = ConvertLinetoRecord(Line);

            vClients.push_back(Client);
        }

        MyFile.close();

    }

    return vClients;

}
vector <stUser> LoadUsersDataFromFile(string fileName) {
    vector <stUser> vUsers;
    fstream MyFill;

    MyFill.open(fileName, ios::in); //read only
    if (MyFill.is_open())
    {
        string Line;
        stUser User;
        while (getline(MyFill, Line))
        {
            User = ConvertLinetoUserRecord(Line);
            vUsers.push_back(User);
        }
        MyFill.close();
    }

    return vUsers;
}
vector <sClient> SaveClientsDataToFile(string FileName, vector <sClient> vClients)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {

        for (sClient C : vClients)
        {

            if (C.MarkForDelete == false)
            {
                //we only write records that are not marked for delete.  
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;

            }

        }

        MyFile.close();

    }

    return vClients;

}
vector <stUser> SaveUsersDataToFile(string NameFile, vector <stUser>& vUsers) {

    fstream MyFile;
    MyFile.open(NameFile, ios::out);

    if (MyFile.is_open())
    {
        string DataLine;

        for (stUser& user : vUsers)
        {

            if (!user.MarkForDelete)
            {
                DataLine = ConvertUserRecordToLine(user);
                MyFile << DataLine << endl;
            }

        }

        MyFile.close();
    }

    return LoadUsersDataFromFile(UsersFileName);
}
void AddDataLineToFile(string FileName, string  stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {

        MyFile << stDataLine << endl;

        MyFile.close();
    }

}

// ##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##
void ShowAccessDeniedMessage() {
    cout << "\nThe following are the User details:\n";
    cout << "-----------------------------------";
    cout << "\nAccess Denied,\nYou dont Have Permission To Do this,\nPlease Send Contact Your Admin";
    cout << "\n-----------------------------------\n";
}
void PrintUserCard(stUser User)
{
    cout << "\nThe following are the User details:\n";
    cout << "-----------------------------------";
    cout << "\nUsername           : " << User.Username;
    cout << "\nPassword           : " << User.Password;
    cout << "\nPermission         : " << User.Permissions;
    cout << "\n-----------------------------------\n";

}
void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PinCode;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n-----------------------------------\n";

}
sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;

}
bool FindClientByAccountNumber(string AccountNumber, vector <sClient> vClients, sClient& Client)
{

    for (sClient C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }

    }
    return false;

}
bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    for (sClient& C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }

    }

    return false;

}
bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{

    vector <sClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {

            Client = ConvertLinetoRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }


            vClients.push_back(Client);
        }

        MyFile.close();

    }

    return false;


}
sClient ReadNewClient()
{
    sClient Client;

    cout << "Enter Account Number? ";

    // Usage of std::ws will extract allthe whitespace character
    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }


    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;

}
bool MarkUserForDeleteUsername(string Username, vector <stUser>& vUser) {

    for (stUser& user : vUser)
    {
        if (user.Username == Username)
        {
            user.MarkForDelete = true;
            return true;
        }
    }
    return false;
}
stUser ChangeUserRecord(string Username)
{
    stUser User;

    User.Username = Username;

    cout << "\n\nEnter Password? ";
    getline(cin >> ws, User.Password);

    User.Permissions = ReadPermissionsToSet();


    return User;

}

//################__Function in Main Menue Screen__################
bool FindUserByUsername(string Username, vector <stUser> vUser, stUser& User)
{

    for (stUser C : vUser)
    {

        if (C.Username == Username)
        {
            User = C;
            return true;
        }

    }
    return false;

}
void PrintClientRecordLine(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;

}
void ShowAllClientsScreen()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pListClient)) {
        ShowAccessDeniedMessage();
        return;
    }
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {

            PrintClientRecordLine(Client);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}
//---------------------------------------------------------------
void AddNewClient()
{
    sClient Client;
    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));

}
void AddNewClients()
{
    char AddMore = 'Y';
    do
    {
        //system("cls");
        cout << "Adding New Client:\n\n";

        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";


        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}
void ShowAddNewClientsScreen()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pAddNewClient)) {
        ShowAccessDeniedMessage();
        return;
    }
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";

    AddNewClients();
}
//---------------------------------------------------------------
bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveClientsDataToFile(ClientsFileName, vClients);

            //Refresh Clients 
            vClients = LoadCleintsDataFromFile(ClientsFileName);

            cout << "\n\nClient Deleted Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }

}
void ShowDeleteClientScreen()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pDeleteClient)) {
        ShowAccessDeniedMessage();
        return;
    }
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);

}
//---------------------------------------------------------------
bool UpdateClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);
        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {

            for (sClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }

            }

            SaveClientsDataToFile(ClientsFileName, vClients);

            cout << "\n\nClient Updated Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }

}
void ShowUpdateClientScreen()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pUpdateClient)) {
        ShowAccessDeniedMessage();
        return;
    }
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);

}
//---------------------------------------------------------------
void ShowFindClientScreen()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pFindClient)) {
        ShowAccessDeniedMessage();
        return;
    }
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        PrintClientCard(Client);
    else
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";

}
//---------------------------------------------------------------


//################__Function in Transactions Menue Screen__################
bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <sClient>& vClients)
{
    char Answer = 'n';

    cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {

        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveClientsDataToFile(ClientsFileName, vClients);
                cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;

                return true;
            }
        }

        return false;
    }

}
//---------------------------------------------------------------
void ShowDepositScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";


    sClient Client;

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();


    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }


    PrintClientCard(Client);

    double Amount = 0;
    cout << "\nPlease enter deposit amount? ";
    cin >> Amount;

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);

}
//---------------------------------------------------------------
void ShowWithDrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tWithdraw Screen";
    cout << "\n-----------------------------------\n";

    sClient Client;

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();


    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }

    PrintClientCard(Client);

    double Amount = 0;
    cout << "\nPlease enter withdraw amount? ";
    cin >> Amount;

    //Validate that the amount does not exceeds the balance
    while (Amount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
        cout << "Please enter another amount? ";
        cin >> Amount;
    }

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);

}
//---------------------------------------------------------------
void PrintClientRecordBalanceLine(sClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;

}
void ShowTotalBalances()
{

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    double TotalBalances = 0;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {

            PrintClientRecordBalanceLine(Client);
            TotalBalances += Client.AccountBalance;

            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "\t\t\t\t\t   Total Balances = " << TotalBalances;

}
void ShowTotalBalancesScreen()
{
    ShowTotalBalances();
}
//---------------------------------------------------------------
void ShowEndScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";

}
void LoginScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tLogin Screen";
    cout << "\n-----------------------------------\n";

}

//##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##

void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue();

}
void GoBackToTransactionsMenue()
{
    cout << "\n\nPress any key to go back to Transactions Menue...";
    system("pause>0");
    ShowTransactionsMenue();

}
void GoBackToManagerUsersMenue()
{
    cout << "\n\nPress any key to go back to Manager Users menue...";
    system("pause>0");
    ShowManagerUsers();

}

//################### General Fun###################

bool UserExistsByUsername(string UserName, string FileName)
{

    vector <stUser> vUsers;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        stUser User;

        while (getline(MyFile, Line))
        {

            User = ConvertLinetoUserRecord(Line);
            if (User.Username == UserName)
            {
                MyFile.close();
                return true;
            }


            vUsers.push_back(User);
        }

        MyFile.close();

    }

    return false;
}
stUser ReadUser()
{
    stUser User;
    cout << "\nEnter Username : ";
    getline(cin >> ws, User.Username);

    while (UserExistsByUsername(User.Username, UsersFileName))
    {
        cout << "User with [" << User.Username << "] already exists, Enter another Username? : ";
        getline(cin >> ws, User.Username);
    }
    cout << "\nEnter Password : ";
    getline(cin >> ws, User.Password);

    User.Permissions = ReadPermissionsToSet();

    return User;
}

//################__Function in  Manager Users Memue Screen__################
void PrintUserRecordLine(stUser user)
{
    cout << "| " << setw(35) << left << user.Username;
    cout << "| " << setw(35) << left << user.Password;
    cout << "| " << setw(20) << left << user.Permissions;
}
void ShowAllUsersScreen()
{
    vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);

    cout << "\n\t\t\t\t\tClient List (" << vUsers.size() << ") Users(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(35) << "User Name";
    cout << "| " << left << setw(35) << "Password";
    cout << "| " << left << setw(20) << "Permissions";

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vUsers.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else
        for (stUser user : vUsers)
        {
            PrintUserRecordLine(user);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}
//---------------------------------------------------------------
void AddNewUser() {

    stUser User;
    User = ReadUser();
    AddDataLineToFile(UsersFileName, ConvertUserRecordToLine(User));
}
void AddNewUsers()
{
    char AddUser = 'y';
    do {
        AddNewUser();
        cout << "User Added Successfully, do you want add more users y/n ? : ";
        cin >> AddUser;
    } while (tolower(AddUser) == 'y');

}
void ShowAddNewUsersScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New User Screen";
    cout << "\n-----------------------------------\n";

    AddNewUsers();
}
////---------------------------------------------------------------
bool DeleteUser(vector <stUser>& vUser, string Username) {

    if (Username == "IssamBR") {
        cout << "\n\nYou cannot Delete This User.";
        return false;
    }
    stUser user;
    vector <stUser> vUsersNew;
    if (FindUserByUsername(Username, vUser, user))
    {
        PrintUserCard(user);
        char Answer = 'n';
        cout << "Are you sure you want delete this User? y/n : ";
        cin >> Answer;

        if (tolower(Answer) == 'y')
        {
            MarkUserForDeleteUsername(Username, vUser);
            vUser = SaveUsersDataToFile(UsersFileName, vUser);
            cout << "\n\nClient Deleted Successfully.";
            return true;
        }
        return false;
    }
    else
    {
        cout << "\nUser with Username (" << Username << ") is Not Found!";
        return false;
    }


}
void ShowDeleteUserScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New User Screen";
    cout << "\n-----------------------------------\n";

    vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
    string username = ReadUsername();
    DeleteUser(vUsers, username);

}
////---------------------------------------------------------------
bool UpdateUserWithUsername(string Username, vector <stUser>& vUsers) {

    stUser user;
    if (FindUserByUsername(Username, vUsers, user)) {
        PrintUserCard(user);
        char Answer = 'n';
        cout << "Are you sure you want Update this User? y/n : ";
        cin >> Answer;

        if (tolower(Answer) == 'y') {

            for (stUser& U : vUsers)
            {
                if (U.Username == Username)
                {
                    U = ChangeUserRecord(Username);
                    break;
                }
            }

            vUsers = SaveUsersDataToFile(UsersFileName, vUsers);
            cout << "\n\nClient Deleted Successfully.";
            return true;
        }
        return false;
    }
    else
    {
        cout << "\nUser with Username (" << Username << ") is Not Found!";
        return false;
    }
}
void ShowUpdateUserScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Users Screen";
    cout << "\n-----------------------------------\n";

    vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
    string username = ReadUsername();
    UpdateUserWithUsername(username, vUsers);
}
////---------------------------------------------------------------
void ShowFindUserScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tFind Users Screen";
    cout << "\n-----------------------------------\n";
    vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
    string username = ReadUsername();

    stUser user;
    if (FindUserByUsername(username, vUsers, user))
        PrintUserCard(user);
    else
        cout << "\nUser with Username [ " << username << " ] is not found!";
}

//##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##
void PerfromManagerMenueOption(enMangerUsersMenueOptions UserManagerMenueOption)
{
    switch (UserManagerMenueOption)
    {
    case enMangerUsersMenueOptions::eShowListUser:
    {
        system("cls");
        ShowAllUsersScreen();
        GoBackToManagerUsersMenue();
        break;
    }
    case enMangerUsersMenueOptions::eAddNewUser:
    {
        system("cls");
        ShowAddNewUsersScreen();
        GoBackToManagerUsersMenue();
        break;
    }
    case enMangerUsersMenueOptions::eDeleteUser:
    {
        system("cls");
        ShowDeleteUserScreen();
        GoBackToManagerUsersMenue();
        break;
    }
    case enMangerUsersMenueOptions::eUpdateUser:
    {
        system("cls");
        ShowUpdateUserScreen();
        GoBackToManagerUsersMenue();
        break;
    }
    case enMangerUsersMenueOptions::eFindUser:
    {
        system("cls");
        ShowFindUserScreen();
        GoBackToManagerUsersMenue();
        break;
    }
    case enMangerUsersMenueOptions::eMainMenue:
        ShowMainMenue();
    }

}
void ShowManagerUsers()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pManageUsers)) {
        ShowAccessDeniedMessage();
        GoBackToMainMenue();
        return;
    }
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tManager Users Memue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] List Users.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menue.\n";
    cout << "===========================================\n";
    PerfromManagerMenueOption((enMangerUsersMenueOptions)ReadManagerUserMenueOption());
}

//##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##
void PerfromTranactionsMenueOption(enTransactionsMenueOptions TransactionMenueOption)
{
    switch (TransactionMenueOption)
    {
    case enTransactionsMenueOptions::eDeposit:
    {
        system("cls");
        ShowDepositScreen();
        GoBackToTransactionsMenue();
        break;
    }

    case enTransactionsMenueOptions::eWithdraw:
    {
        system("cls");
        ShowWithDrawScreen();
        GoBackToTransactionsMenue();
        break;
    }


    case enTransactionsMenueOptions::eShowTotalBalance:
    {
        system("cls");
        ShowTotalBalancesScreen();
        GoBackToTransactionsMenue();
        break;
    }


    case enTransactionsMenueOptions::eShowMainMenue:
    {
        ShowMainMenue();
    }
    }

}
void ShowTransactionsMenue()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pShowTransactionsMenue)) {
        ShowAccessDeniedMessage();
        GoBackToMainMenue();
        return;
    }
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tTransactions Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menue.\n";
    cout << "===========================================\n";
    PerfromTranactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());
}

//##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##_##
void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
    switch (MainMenueOption)
    {
    case enMainMenueOptions::eListClients:
        system("cls");
        ShowAllClientsScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eAddNewClient:
        system("cls");
        ShowAddNewClientsScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eDeleteClient:
        system("cls");
        ShowDeleteClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eUpdateClient:
        system("cls");
        ShowUpdateClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eFindClient:
        system("cls");
        ShowFindClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eShowTransactionsMenue:
        system("cls");
        ShowTransactionsMenue();
        break;

    case enMainMenueOptions::ManageUsers:
        system("cls");
        ShowManagerUsers();
        break;

    case  enMainMenueOptions::Logout:
        system("cls");
        Login();
    }
}
void ShowMainMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Logout.\n";
    cout << "===========================================\n";
    PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}

//################__Start Program Login__################
bool checkUser(vector <stUser>& vUser, string Username, string Password, stUser& User) {

    for (stUser U : vUser)
    {
        if (U.Username == Username && U.Password == Password)
        {
            User = U;
            return true;
        }
    }
    return false;
}
void Login() {

    system("cls");
    LoginScreen();
    vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);

    string Username, Password;
    ReadLoginInfo(Username, Password);


    while (!checkUser(vUsers, Username, Password, CurrentUser))
    {
        system("cls");
        LoginScreen();
        cout << "\Invlaid Username/Password? : ";
        ReadLoginInfo(Username, Password);
    }
    ShowMainMenue();

}
int main() {
    Login();
    system("pause>0");
    return 0;
}