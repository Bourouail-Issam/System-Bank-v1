
#include <iostream>
#include <fstream>
#include<iomanip>
#include<string>
#include<vector>

using namespace std;
const string NameSourceFill = "MyFill.text";

enum enChoose { showClientList = 1, AddNewClient = 2, DeleteClient = 3, UpDateClient = 4, FindClient = 5, Exit = 6 };
struct stInfoClient {

    string AccountNumber;
    string PinCode;
    string ClientName;
    string Phone;
    double BalanceAccount = 0;
    bool MakDeleted = false;
};

void Backup() {
    cout << "\nPress nay key to go back to main Menue...";
    cout << system("pause");
}
//Fuction and Procedure For Print
void PrintMainMenueScreen() {

    cout << "\n=================================================\n";
    cout << "\t\tMain Menue Screen";
    cout << "\n=================================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client\n";
    cout << "\t[4] UpDate Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Exit.\n";
    cout << "=================================================\n";
}
void PrintClient(stInfoClient client) {

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

    cout << endl;
    cout << "| " << setw(15) << left << client.AccountNumber;
    cout << "| " << setw(10) << left << client.PinCode;
    cout << "| " << setw(40) << left << client.ClientName;
    cout << "| " << setw(13) << left << client.Phone;
    cout << "| " << setw(10) << left << client.BalanceAccount;

}
void PrintAllInfoClients(vector<stInfoClient>& vClient) {

    cout << "\n\t\t\t\t\tClient List (" << vClient.size() << ") Client(s).\n";
    cout << "\n-------------------------------------------------------------------------------------------------\n\n";
    cout << "| " << setw(15) << left << "Accout Number";
    cout << "| " << setw(10) << left << "Pin Code";
    cout << "| " << setw(40) << left << "Client Name";
    cout << "| " << setw(13) << left << "Phone";
    cout << "| " << setw(10) << left << "Balance";
    cout << "\n\n-------------------------------------------------------------------------------------------------\n";

    for (stInfoClient& stClient : vClient) {
        PrintInfoLineClient(stClient);
    }
    cout << "\n\n-------------------------------------------------------------------------------------------------\n";

}
bool EndProgram() {

    cout << "\n---------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n---------------------------------\n";
    Backup();
    return true;
}


// Function used for Load And Get Data From MyFill
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
vector <stInfoClient> LoadDataClientFromMyFil(string FileName) {

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
vector <stInfoClient> SaveClientsToMyFill(string FillName, vector <stInfoClient>& vClient) {

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
bool FindClientByAccountNumber(string AccountNumber, stInfoClient& client, vector <stInfoClient>& vClient) {

    for (stInfoClient& stClient : vClient) {

        if (stClient.AccountNumber == AccountNumber) {
            client = stClient;
            return true;
        }
    }
    return false;
}

// Read Function

 //This For Validation to Read just int data type
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

short ReadIntervalNumber(short From, short To) {

    double number;
    do {
        cout << "Choose what do you to do [" << From << " to " << To << "] : ";
        cin >> number;

    } while (number < From || number > To);
    return number;
}
stInfoClient ReadClientRecord(vector <stInfoClient> vClient) {

    stInfoClient stClient;

    cout << "Enter Account Number? ";
    getline(cin >> ws, stClient.AccountNumber);

    while (FindClientByAccountNumber(stClient.AccountNumber, stClient, vClient)) {
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
string ReadNumberAccout() {
    string AccountNumber;
    cout << "\nPlease enter AccountNumber? ";
    getline(cin >> ws, AccountNumber);
    return AccountNumber;
}
void ClientNotFound(string AccountNumber) {

    cout << "\nClient With Accout Number (" << AccountNumber << ") is Not Found\n\n";
    Backup();
}

// Add Client in MyFill
bool AddClientToMyFill(string FileName, vector <stInfoClient>& vClient) {

    char Anwsor = 'n';
    stInfoClient stClient;

    do {
        system("cls");
        cout << "\n----------------------------\n";
        cout << "  Add New Clients Screnn";
        cout << "\n----------------------------\n";
        cout << "  New Client : \n\n";

        stClient = ReadClientRecord(vClient);
        vClient.push_back(stClient);

        cout << "Client Added Successfully, do you want to add more client Y/N? ";
        cin >> Anwsor;
    } while (tolower(Anwsor) == 'y');
    SaveClientsToMyFill(FileName, vClient);
    Backup();
    return true;
}

// Remove Client Fom MyFill
bool MarkClientDelete(string AccountNumber, vector <stInfoClient>& vClient) {

    for (stInfoClient& stClient : vClient) {

        if (stClient.AccountNumber == AccountNumber) {

            stClient.MakDeleted = true;
            return true;
        }
    }
    return  false;
}
bool RomoveClientByAccountNumber(string FileName, vector <stInfoClient>& vClient) {

    char Anwsor = 'n';
    stInfoClient stClient;

    cout << "\n----------------------------------\n";
    cout << "      Add New Clients Screnn";
    cout << "\n----------------------------------\n";

    cout << "\nPlease enter AccountNumber? ";
    getline(cin >> ws, stClient.AccountNumber);

    if (FindClientByAccountNumber(stClient.AccountNumber, stClient, vClient)) {

        PrintClient(stClient);

        cout << "Are you sure you want delete this client? y/n ? ";
        cin >> Anwsor;
        if (tolower(Anwsor) == 'y') {

            MarkClientDelete(stClient.AccountNumber, vClient);
            SaveClientsToMyFill(FileName, vClient);


            cout << "\n\nClient Deleted Successfully\n";
            Backup();

            return true;
        }
        else {

            Backup();
            return false;
        }


    }
    else {

        ClientNotFound(stClient.AccountNumber);
        return false;
    }
}

// Udate Client By Account Number
stInfoClient ChangeClientRecord(string NumberAccount) {

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
bool UdateClientByAccountNumber(string FileName, vector <stInfoClient>& vClient) {

    stInfoClient stClient;
    char Answer = 'y';

    cout << "\n----------------------------------\n";
    cout << "      UpDate Clients Screnn";
    cout << "\n----------------------------------\n";

    PrintAllInfoClients(vClient);
    stClient.AccountNumber = ReadNumberAccout();

    if (FindClientByAccountNumber(stClient.AccountNumber, stClient, vClient)) {

        PrintClient(stClient);
        cout << "\n\nAre you sure want UpDate this Client? y/n ? ";
        cin >> Answer;

        if (tolower(Answer) == 'y') {
            for (stInfoClient& client : vClient) {

                if (client.AccountNumber == stClient.AccountNumber) {

                    client = ChangeClientRecord(stClient.AccountNumber);
                    break;
                }
            }
            SaveClientsToMyFill(FileName, vClient);

            cout << "\n\nClient UpDated Successfuly\n";
            Backup();

            return true;
        }

    }
    else {

        ClientNotFound(stClient.AccountNumber);
        return false;
    }

}

// Find Client By Accout Number
bool FindClientByAccoutNumber(string FileName, vector <stInfoClient>& vClient) {

    stInfoClient stClient;
    char Answer = 'y';

    cout << "\n----------------------------------\n";
    cout << "      Find Clients Screnn";
    cout << "\n----------------------------------\n";

    stClient.AccountNumber = ReadNumberAccout();

    if (FindClientByAccountNumber(stClient.AccountNumber, stClient, vClient)) {

        PrintClient(stClient);
        Backup();
        return true;
    }
    else {

        ClientNotFound(stClient.AccountNumber);
        return false;
    }
}

void StartProgram() {

    vector <stInfoClient> vClient = LoadDataClientFromMyFil(NameSourceFill);
    bool FinishProgram = false;
    while (!FinishProgram)
    {
        vector <stInfoClient> vClient = LoadDataClientFromMyFil(NameSourceFill);

        system("cls");
        PrintMainMenueScreen();
        int Answer = ReadIntervalNumber(1, 6);

        if (Answer == enChoose::showClientList) {
            system("cls");
            PrintAllInfoClients(vClient);
            Backup();
        }
        else if (Answer == enChoose::AddNewClient) {
            system("cls");
            AddClientToMyFill(NameSourceFill, vClient);
        }
        else if (Answer == enChoose::DeleteClient) {
            system("cls");
            RomoveClientByAccountNumber(NameSourceFill, vClient);
        }
        else if (Answer == enChoose::UpDateClient) {
            system("cls");
            UdateClientByAccountNumber(NameSourceFill, vClient);
        }
        else if (Answer == enChoose::FindClient) {
            system("cls");
            FindClientByAccoutNumber(NameSourceFill, vClient);
        }
        else if (Answer == enChoose::Exit) {
            system("cls");
            FinishProgram = EndProgram();
        }
    }
}
int main()
{
    StartProgram();
}

