
#include <iostream>
#include <fstream>
#include<iomanip>
#include<string>
#include<vector>

using namespace std;
const string NameSourceFill = "MyFill.text";

/* ##### defenition Show Main Menue & Show Transactions Menue Screen ##### */
void ShowMainMenue();
void ShowTransactionsMenueScreen();

struct stInfoClient {

    string AccountNumber;
    string PinCode;
    string ClientName;
    string Phone;
    double BalanceAccount = 0;
    bool MakDeleted = false;
};

enum enMainMeuneOption
{
    enListClient = 1, enAddNewClient = 2, enDeleteClient = 3,
    enUpDateClient = 4, enFindClient = 5, enTransactions = 6, enExit = 7
};
enum enTransactionsOption
{
    enDeposit = 1, enWithdraw = 2, enTotalBalances = 3, enMainMenue = 4
};



/* ###### Function used for Load And Get Data From MyFill #####*/

vector <string> SplitString(string S1, string Delim = "#//#") {

    int pos = 0;
    string sWord;
    vector <string> InfoClient;

    while ((pos = S1.find(Delim)) != std::string::npos) {

        sWord = S1.substr(0, pos);
        if (sWord != "")
            InfoClient.push_back(sWord);

        S1 = S1.erase(0, pos + Delim.length());
    }
    if (S1 != "")
        InfoClient.push_back(S1);
    return InfoClient;
}

stInfoClient ConvertLineToRecord(string S1, string Seperator = "#//#") {

    stInfoClient stClient;
    vector <string> vClient;

    vClient = SplitString(S1);

    stClient.AccountNumber = vClient[0];
    stClient.PinCode = vClient[1];
    stClient.ClientName = vClient[2];
    stClient.Phone = vClient[3];
    stClient.BalanceAccount = stod(vClient[4]);

    return stClient;
}

string ConvertRecordToLine(stInfoClient stClient, string Seperator = "#//#") {

    string DataLine;

    DataLine += stClient.AccountNumber + Seperator;
    DataLine += stClient.PinCode + Seperator;
    DataLine += stClient.ClientName + Seperator;
    DataLine += stClient.Phone + Seperator;
    DataLine += to_string(stClient.BalanceAccount);

    return DataLine;
}

vector <stInfoClient> LoadDataClientFromFile(string FileName) {

    fstream MyFill;
    string line;
    stInfoClient stClient;
    vector <stInfoClient> vClient;

    MyFill.open(FileName, ios::in);//Read Mod

    if (MyFill.is_open()) {

        while (getline(MyFill, line)) {

            stClient = ConvertLineToRecord(line);
            vClient.push_back(stClient);
        }
        MyFill.close();
    }
    return vClient;
}

vector <stInfoClient> SaveClientsDataToFile(string FillName, vector <stInfoClient>& vClient) {

    fstream MyFill;
    string DataLine;

    MyFill.open(FillName, ios::out); // Add Mode 
    if (MyFill.is_open()) {

        for (stInfoClient stClient : vClient) {

            if (!stClient.MakDeleted) {
                DataLine = ConvertRecordToLine(stClient);
                MyFill << DataLine << endl;
            }
        }
        MyFill.close();
    }
    return vClient;
}

bool FindClientByAccountNumber(string AccountNumber, vector <stInfoClient>& vClients, stInfoClient& Client)
{
    for (stInfoClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

void AddDataLineToFile(string FileName, string stDataLine) {

    fstream MyFil;
    MyFil.open(FileName, ios::out | ios::app);

    if (MyFil.is_open())
    {
        MyFil << stDataLine << endl;
        MyFil.close();
    }
}

bool ClientExistsByAccountNumber(string AccountNumber, string FilName) {

    vector <stInfoClient> vClient;
    fstream MyFile;
    MyFile.open(FilName, ios::in);//Read Mode

    if (MyFile.is_open())
    {
        string Line;
        stInfoClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }
            vClient.push_back(Client);
        }
        MyFile.close();
    }
    return false;
}

// ################################### Procedure For Print ###################################

void PrintClientCard(stInfoClient client) {

    cout << "\nThe Following are the client details:\n";
    cout << "---------------------------------------\n";
    cout << setw(15) << left << "AccountNumber" << " : " << client.AccountNumber << endl;
    cout << setw(15) << left << "PinCode" << " : " << client.PinCode << endl;
    cout << setw(15) << left << "ClientName" << " : " << client.ClientName << endl;
    cout << setw(15) << left << "Phone" << " : " << client.Phone << endl;
    cout << setw(15) << left << "Account Balance" << " : " << client.BalanceAccount << endl;
    cout << "---------------------------------------\n\n";
}

void PrintInfoLineClient(stInfoClient client) {


    cout << "| " << setw(15) << left << client.AccountNumber;
    cout << "| " << setw(15) << left << client.PinCode;
    cout << "| " << setw(30) << left << client.ClientName;
    cout << "| " << setw(16) << left << client.Phone;
    cout << "| " << setw(16) << left << client.BalanceAccount;

}

void ShowAllClientsScreen() {

    vector <stInfoClient> vClient = LoadDataClientFromFile(NameSourceFill);

    cout << "\n\t\t\t\t\tClient List (" << vClient.size() << ") Client(s).\n";
    cout << "\n-------------------------------------------------------------------------------------------------\n\n";
    cout << "| " << setw(15) << left << "Accout Number";
    cout << "| " << setw(15) << left << "Pin Code";
    cout << "| " << setw(30) << left << "Client Name";
    cout << "| " << setw(16) << left << "Phone";
    cout << "| " << setw(16) << left << "Balance";
    cout << "\n\n-------------------------------------------------------------------------------------------------\n\n";

    if (vClient.size() == 0)

        cout << "\n\t\t\t\tNo Client Available In The System!";

    else

        for (stInfoClient& stClient : vClient)
        {
            PrintInfoLineClient(stClient);
            cout << endl;
        }

    cout << "\n-------------------------------------------------------------------------------------------------\n";

}

void PrintBalancesLineClient(stInfoClient client) {


    cout << "| " << setw(15) << left << client.AccountNumber;
    cout << "| " << setw(30) << left << client.ClientName;
    cout << "| " << setw(16) << left << client.BalanceAccount;

}

void ShowAllClientsBalance() {

    vector <stInfoClient> vClient = LoadDataClientFromFile(NameSourceFill);

    cout << "\n\t\t\t\t\tClient List (" << vClient.size() << ") Client(s).\n";
    cout << "\n-------------------------------------------------------------------------------------------------\n\n";
    cout << "| " << setw(15) << left << "Accout Number";
    cout << "| " << setw(30) << left << "Client Name";
    cout << "| " << setw(16) << left << "Balance";
    cout << "\n\n-------------------------------------------------------------------------------------------------\n\n";

    long double AllBalance = 0;

    if (vClient.size() == 0)

        cout << "\n\t\t\t\tNo Client Available In The System!";

    else

        for (stInfoClient& stClient : vClient)
        {
            PrintBalancesLineClient(stClient);
            AllBalance += (long double)stClient.BalanceAccount;
            cout << endl;
        }

    cout << "\n-------------------------------------------------------------------------------------------------\n";
    cout << "\n\t\t\t\t\t Total Balances = " << AllBalance << endl << endl;
}

void ShowEndScreen()
{
    cout << "\n----------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n----------------------------\n\n";
    cout << endl;
}


// ################################### Functions For Read Data ###################################

short ReadMainMenueOption(short From, short To)
{
    short number;
    do
    {
        cout << "Choose what do you to do? [" << From << " to " << To << "] ? ";
        cin >> number;
    } while (number<From || number >To);

    return number;
}

void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause");
    ShowMainMenue();
}

void GoBackToTransactionsMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause");
    ShowTransactionsMenueScreen();
}

stInfoClient ReadNewClient() {

    stInfoClient stClient;

    cout << "Enter Account Number? ";
    getline(cin >> ws, stClient.AccountNumber);

    while (ClientExistsByAccountNumber(stClient.AccountNumber, NameSourceFill))
    {
        cout << "\nClient With [" << stClient.AccountNumber << "] already exist, Enter another Account Number? ";
        getline(cin >> ws, stClient.AccountNumber);
    };

    cout << "Enter PinCode? ";
    getline(cin, stClient.PinCode);
    cout << "Enter Name? ";
    getline(cin, stClient.ClientName);
    cout << "Enter Phone ";
    getline(cin, stClient.Phone);
    cout << "Enter AccountBalance? ";
    cin >> stClient.BalanceAccount;

    return stClient;
}

string ReadClientAccountNumber()
{
    string AccountNumber;
    cout << "\nPlease enter AccountNumber? ";
    getline(cin >> ws, AccountNumber);

    return AccountNumber;
}

/* ##### This For Validation to Read just int data type ##### */

/*bool isInteger(const string& str) {
/*
/*    if (str.empty()) return false;
/*
/*    for (char c : str) {
/*        if (!isdigit(c) && c != '-') {
/*            return false;
/*        }
/*    }
/*    return true;
/*}
/*short ReadIntervalNumber(short From, short To) {
/*    string input;
/*    short number;
/*    bool ValidInput = false;
/*    do {
/*        cout << "Choose what do you to do [" << From << " to " << To << "] : ";
/*        getline(cin >> ws, input);
/*
/*        if (isInteger(input)) {
/*            istringstream iss(input);
/*            iss >> number;
/*            ValidInput = true;
/*        }
/*        else {
/*            cout << "Invalid input. Please enter a valid integer." << endl;
/*        }
/*
/*    } while (((number < From) && (number > To)) || !ValidInput);
/*    return number;
//}
*/

// ################################### Add Client  ###################################

void AddNewClient()
{
    stInfoClient Client;
    Client = ReadNewClient();
    AddDataLineToFile(NameSourceFill, ConvertRecordToLine(Client));
}

void AddNewClients()
{
    cout << "\nAdding New Client : \n\n";

    AddNewClient();
    cout << "Client Added Successfully, do you want to add more client Y/N? ";

}

void ShowAddNewClientScreen()
{
    char AddMore = 'y';
    do
    {
        system("cls");
        cout << "\n----------------------------\n";
        cout << "  Add New Clients Screnn";
        cout << "\n----------------------------\n";

        AddNewClients();
        cin >> AddMore;

    } while (tolower(AddMore) == 'y');

}

// ################################### Remove Client ###################################

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <stInfoClient>& vClient) {

    for (stInfoClient& stClient : vClient) {

        if (stClient.AccountNumber == AccountNumber) {

            stClient.MakDeleted = true;
            return true;
        }
    }
    return  false;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector <stInfoClient>& vClients)
{
    char Anwsor = 'n';
    stInfoClient stClient;

    if (FindClientByAccountNumber(AccountNumber, vClients, stClient)) {

        PrintClientCard(stClient);

        cout << "Are you sure you want delete this client? y/n ? ";
        cin >> Anwsor;

        if (tolower(Anwsor) == 'y') {

            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveClientsDataToFile(NameSourceFill, vClients);

            vClients = LoadDataClientFromFile(NameSourceFill);

            cout << "\n\nClient Deleted Successfully\n";

            return true;
        }
        else {

            return false;
        }


    }
    else {

        cout << "\nClient With Accout Number (" << AccountNumber << ") is Not Found\n\n";
        return false;
    }
}

void ShowDeleteClientScreen()
{
    cout << "\n----------------------------------\n";
    cout << "      Delete Clients Screnne";
    cout << "\n----------------------------------\n";

    vector <stInfoClient> vClient = LoadDataClientFromFile(NameSourceFill);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClient);
}

// ################################### UpDate Client ###################################

stInfoClient ChangeClientRecord(string NumberAccount)
{
    stInfoClient stClient;

    stClient.AccountNumber = NumberAccount;

    cout << "Enter PinCode? ";
    getline(cin >> ws, stClient.PinCode);

    cout << "Enter Name? ";
    getline(cin >> ws, stClient.ClientName);

    cout << "Enter Phone? ";
    getline(cin >> ws, stClient.Phone);

    cout << "Enter AccountBalance? ";
    cin >> stClient.BalanceAccount;

    return stClient;
}

bool UdateClientByAccountNumber(string AccountNumber, vector <stInfoClient>& vClients) {

    stInfoClient stClient;
    char Answer = 'n';

    //ShowAllClientsScreen();

    if (FindClientByAccountNumber(AccountNumber, vClients, stClient))
    {
        PrintClientCard(stClient);
        cout << "\n\nAre you sure want UpDate this Client? y/n ? ";
        cin >> Answer;

        if (tolower(Answer) == 'y')
        {
            for (stInfoClient& client : vClients) {

                if (client.AccountNumber == AccountNumber) {

                    client = ChangeClientRecord(AccountNumber);
                    break;
                }
            }

            SaveClientsDataToFile(NameSourceFill, vClients);

            cout << "\n\nClient UpDated Successfuly\n";

            return true;
        }

    }
    else {

        cout << "\nClient With Accout Number (" << AccountNumber << ") is Not Found\n\n";
        return false;
    }

}

void ShowUpDateClientScreen()
{
    cout << "\n----------------------------------\n";
    cout << "      UpDate Clients ScrennE";
    cout << "\n----------------------------------\n";

    vector <stInfoClient> vClients = LoadDataClientFromFile(NameSourceFill);
    string AccountNumber = ReadClientAccountNumber();
    UdateClientByAccountNumber(AccountNumber, vClients);
}

// ################################### Find Client ###################################

bool FindClientByAccoutNumber(string AccountNumber, vector <stInfoClient>& vClients) {

    stInfoClient stClient;

    if (FindClientByAccountNumber(AccountNumber, vClients, stClient)) {

        PrintClientCard(stClient);
        return true;
    }
    else {

        cout << "\nClient With Accout Number (" << AccountNumber << ") is Not Found\n\n";
        return false;
    }
}

void ShowFindClientScreen()
{
    cout << "\n----------------------------------\n";
    cout << "      Find Clients Screnn";
    cout << "\n----------------------------------\n";

    vector <stInfoClient> vClients = LoadDataClientFromFile(NameSourceFill);
    string AccountNumber = ReadClientAccountNumber();
    FindClientByAccoutNumber(AccountNumber, vClients);
}




// ################# Fuctions For Transactions #################

// ################################### Deposit Screen ###################################

bool ClientsDeposit(string AccountNumber, vector <stInfoClient>& vClients, double DepositAmount)
{

    char Anwser = 'y';

    cout << "Are you sure you want perfrom this transaction? y/n? ";
    cin >> Anwser;
    if (tolower(Anwser) == 'y')
    {
        for (stInfoClient& stClient : vClients)
        {
            if (stClient.AccountNumber == AccountNumber)
            {
                stClient.BalanceAccount += DepositAmount;
                SaveClientsDataToFile(NameSourceFill, vClients);
                cout << "\n\nDone Successfuly. New Balance is " << stClient.BalanceAccount;
                return true;
            }
        }
    }

    return false;
}

void ShowDepositScreen()
{
    cout << "\n----------------------------------\n";
    cout << "      Deposit Screnn";
    cout << "\n----------------------------------\n";

    vector <stInfoClient> vClients = LoadDataClientFromFile(NameSourceFill);
    stInfoClient stClient;
    string AccountNumber = ReadClientAccountNumber();;

    while (!FindClientByAccountNumber(AccountNumber, vClients, stClient))
    {
        cout << "\nClient With [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    };

    PrintClientCard(stClient);

    double DepositAmount;
    cout << "\nPlease enter deposit amount? ";
    cin >> DepositAmount;

    ClientsDeposit(AccountNumber, vClients, DepositAmount);
}

// ################################### Withdraw Screen ###################################

void ShowWithdrawScreen()
{
    cout << "\n----------------------------------\n";
    cout << "      Withdraw Screnn";
    cout << "\n----------------------------------\n";

    vector <stInfoClient> vClients = LoadDataClientFromFile(NameSourceFill);
    stInfoClient stClient;
    string AccountNumber = ReadClientAccountNumber();;

    while (!FindClientByAccountNumber(AccountNumber, vClients, stClient))
    {
        cout << "\nClient With [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    };

    PrintClientCard(stClient);

    double DepositAmount = 0;
    bool solde = true;

    cout << "\nPlease enter Withdraw amount? ";
    cin >> DepositAmount;

    while (DepositAmount > stClient.BalanceAccount)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to :" << stClient.BalanceAccount << endl;
        cout << "\nPlease enter Withdraw amount? ";
        cin >> DepositAmount;
    }

    ClientsDeposit(AccountNumber, vClients, DepositAmount * -1);
}


void PerformTransactionsOption(enTransactionsOption Answer) {

    switch (Answer)
    {
    case enDeposit:
        system("cls");
        ShowDepositScreen();
        GoBackToTransactionsMenue();
        break;

    case enWithdraw:
        system("cls");
        ShowWithdrawScreen();
        GoBackToTransactionsMenue();
        break;

    case enTotalBalances:
        system("cls");
        ShowAllClientsBalance();
        GoBackToTransactionsMenue();
        break;

    case enMainMenue:
        GoBackToMainMenue();
        break;

    }

}

void PerformMainMenueOption(enMainMeuneOption Answer) {

    switch (Answer)
    {
    case enMainMeuneOption::enListClient:
        system("cls");
        ShowAllClientsScreen();
        GoBackToMainMenue();
        break;

    case enMainMeuneOption::enAddNewClient:
        system("cls");
        ShowAddNewClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMeuneOption::enDeleteClient:
        system("cls");
        ShowDeleteClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMeuneOption::enUpDateClient:
        system("cls");
        ShowUpDateClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMeuneOption::enFindClient:
        system("cls");
        ShowFindClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMeuneOption::enTransactions:
        system("cls");
        ShowTransactionsMenueScreen();
        break;

    case enMainMeuneOption::enExit:
        system("cls");
        ShowEndScreen();
        break;

    }

}

void ShowMainMenue() {

    system("cls");
    cout << "\n=================================================\n";
    cout << "\t\tMain Menue Screen";
    cout << "\n=================================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client\n";
    cout << "\t[4] UpDate Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Exit.\n";
    cout << "=================================================\n\n";
    PerformMainMenueOption((enMainMeuneOption)ReadMainMenueOption(1, 7));
}

void ShowTransactionsMenueScreen() {

    system("cls");
    cout << "\n=================================================\n";
    cout << "\tTransactions Menue Screen";
    cout << "\n=================================================\n";
    cout << "\t[1] Deposit..\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances\n";
    cout << "\t[4] Main Menue.\n";
    cout << "=================================================\n\n";
    PerformTransactionsOption((enTransactionsOption)ReadMainMenueOption(1, 4));
}
int main()
{
    ShowMainMenue();
    system("pause");
}

