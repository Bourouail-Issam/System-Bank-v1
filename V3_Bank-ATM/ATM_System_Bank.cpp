
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

// #################__Structures And Enums__#################
enum enATM_MainMenueScreen { QuickWithdraw = 1, NormalWithdraw = 2, Deposit = 3, CheckBalance = 4, Logout = 5 };
struct stClient
{
	string AccountNumber;
	string CodePin;
	string Name;
	string Phone;
	double AccountBalance = 0;
	bool MarkDeleted = false;
};

// #################__General__#################
stClient CurrentClient;
const string ClientsFileName = "Clients.txt";

// #################__Declaration function__#################
void ShowAtmMainMenueScreen();
void Login();

// #################__Functions Read__#################
short ReadAtmMainMenueScreen() {
	short Answer;
	cout << "Choose what do want to do ? [1 to 5] : ";
	cin >> Answer;
	return Answer;
}
short ReadQuickWithrawOption() {
	short Choice = 0;
	while (Choice < 1 || Choice>9)
	{
		cout << "Choose what to do Frrom [1 to 8] : ";
		cin >> Choice;
	}
	return Choice;
}
int ReadAmountMultipe_5() {
	int Amount;
	do
	{
		cout << "\nEnter an amount multipe of 5,s : ";
		cin >> Amount;
	} while (Amount % 5 != 0);

	return Amount;
}
double ReadDepositAmount() {
	double Amount;
	do
	{
		cout << "Enter a positive Deposit Amount : ";
		cin >> Amount;
	} while (Amount <= 0);
	return Amount;
}

// #################__Functions-General in System__#################
vector <string> SplitString(string S, string Separator = "#//#") {
	int pos = 0;
	string word;
	vector <string> vClient;
	while ((pos = S.find(Separator)) != std::string::npos)
	{
		word = S.substr(0, pos);
		if (word != "")
		{
			vClient.push_back(word);
		}
		S.erase(0, pos + Separator.length());
	}
	if (S != "")
		vClient.push_back(S);

	return vClient;
}
stClient ConvertLineStringToRecordClient(string Line) {

	stClient Client;
	vector <string> vClient = SplitString(Line);

	Client.AccountNumber = vClient[0];
	Client.CodePin = vClient[1];
	Client.Name = vClient[2];
	Client.Phone = vClient[3];
	Client.AccountBalance = stod(vClient[4]);

	return Client;
}
string ConvertRecordClientToClient(stClient client, string Seperator = "#//#") {

	string Line;

	Line += client.AccountNumber + Seperator;
	Line += client.CodePin + Seperator;
	Line += client.Name + Seperator;
	Line += client.Phone + Seperator;
	Line += to_string(client.AccountBalance);

	return Line;
}
vector <stClient> LoadClientsDataFromFile(string NameFile) {
	vector <stClient> vClientsData;

	fstream MyFile;
	MyFile.open(NameFile, ios::in); // Read Only

	if (MyFile.is_open())
	{
		string Line;

		while (getline(MyFile, Line))
			vClientsData.push_back(ConvertLineStringToRecordClient(Line));

		MyFile.close();
	}

	return vClientsData;
}
bool FindClientByAcountNumberAndPinCode(string AccountNumber, string PinCode, stClient& Client) {

	vector <stClient> vClientsData = LoadClientsDataFromFile(ClientsFileName);

	for (stClient& C : vClientsData)
	{
		if (C.AccountNumber == AccountNumber && C.CodePin == PinCode)
		{
			Client = C;
			return true;
		}
	}

	return false;
}
bool LoadClientInfo(string AccountNumber, string PinCode) {

	if (FindClientByAcountNumberAndPinCode(AccountNumber, PinCode, CurrentClient))
		return true;
	else
		return false;
}
vector <stClient> SaveClientsDataToFile(string FileName, vector <stClient>& vClients) {

	fstream MyFile;
	MyFile.open(FileName, ios::out);

	if (MyFile.is_open())
	{
		string DataLine;

		for (stClient& C : vClients)
		{
			if (C.MarkDeleted == false)
			{
				DataLine = ConvertRecordClientToClient(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return LoadClientsDataFromFile(ClientsFileName);
}
bool DepositBalanceToClientByAccountNumber(vector <stClient>& vClients, double Amount) {

	char Answer = 'n';
	cout << "\nAre you sure you want perform this transaction? y/n : ";
	cin >> Answer;
	if (tolower(Answer) == 'y')
	{
		for (stClient& C : vClients)
		{
			if (CurrentClient.AccountNumber == C.AccountNumber)
			{
				C.AccountBalance += Amount;
				SaveClientsDataToFile(ClientsFileName, vClients);
				cout << "\n\nDone Sucessfully. New Balance is " << C.AccountBalance << endl;
				CurrentClient.AccountBalance = C.AccountBalance;
				return true;
			}
		}
		return false;
	}
}

// #################__Go back__#################
void GobackToAtmMainMenueScreen() {
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowAtmMainMenueScreen();
}

// #################__Function ATM Menue__#################
void WithdarwAmount(int Amount) {

	if (Amount > CurrentClient.AccountBalance)
		cout << "\nAmount Exceeds the balance, you can withdraw up to : "
		<< CurrentClient.AccountBalance << endl;
	else
	{
		vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
		DepositBalanceToClientByAccountNumber(vClients, Amount * -1);
	}
}
void NormalWithdrawScreen() {
	cout << "===========================================\n";
	cout << "\tNormal Withdraw Screen\n";
	cout << "===========================================\n";

	int Amount = ReadAmountMultipe_5();
	WithdarwAmount(Amount);

}
short GetQuickWithdrawAmount(short QuickWithDrawOption) {
	switch (QuickWithDrawOption)
	{
	case 1:
		return 20;
	case 2:
		return 50;
	case 3:
		return 100;
	case 4:
		return 200;
	case 5:
		return 400;
	case 6:
		return 600;
	case 7:
		return 800;
	case 8:
		return 1000;
	default:
		return 0;
	}
}
void PerfromQuickWithdrawOption(short QuickWithdraw)
{
	if (QuickWithdraw == 9)
		return;

	short WithDrawBalance = GetQuickWithdrawAmount(QuickWithdraw);
	WithdarwAmount(WithDrawBalance);
}
void ShowQuickWithDraw() {
	cout << "===========================================\n";
	cout << "\tQuick Withdraw\n";
	cout << "===========================================\n";
	cout << "\t[1] 20\t\t[2] 50\n";
	cout << "\t[3] 100\t\t[4] 200\n";
	cout << "\t[5] 400\t\t[6] 600\n";
	cout << "\t[7] 800\t\t[8] 1000\n";
	cout << "\t[9] Exit\n";
	cout << "=========================================\n";
	cout << "Your Balance is " << CurrentClient.AccountBalance << endl;
	PerfromQuickWithdrawOption(ReadQuickWithrawOption());
}
void PerformDepositOption() {

	cout << "\nYour Balance is " << CurrentClient.AccountBalance << endl;
	double Amount = ReadDepositAmount();

	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	DepositBalanceToClientByAccountNumber(vClients, Amount);
}
void ShowDepositATM() {
	cout << "===========================================\n";
	cout << "\t\Deposit Screen\n";
	cout << "===========================================\n";

	PerformDepositOption();
}
void checkBalanceClient() {
	cout << "===========================================\n";
	cout << "\tCheck Balance Screen\n";
	cout << "===========================================\n";

	cout << "\nYour Balance is " << CurrentClient.AccountBalance << endl;
}

// #################__ATM Main Menue Screen__#################
void PerfromATM_MainMenueOptions(enATM_MainMenueScreen ATM_MainMenueOption) {
	switch (ATM_MainMenueOption)
	{
	case QuickWithdraw:
		system("cls");
		ShowQuickWithDraw();
		GobackToAtmMainMenueScreen();
		break;

	case NormalWithdraw:
		system("cls");
		NormalWithdrawScreen();
		GobackToAtmMainMenueScreen();
		break;

	case Deposit:
		system("cls");
		ShowDepositATM();
		GobackToAtmMainMenueScreen();
		break;

	case CheckBalance:
		system("cls");
		checkBalanceClient();
		GobackToAtmMainMenueScreen();
		break;

	case Logout:
		system("cls");
		Login();
		break;
	}
}
void ShowAtmMainMenueScreen() {
	system("cls");
	cout << "===========================================\n";
	cout << "\t\tATM Main Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Quick Withdraw.\n";
	cout << "\t[2] Normal Withdraw.\n";
	cout << "\t[3] Deposit.\n";
	cout << "\t[4] Check Balance.\n";
	cout << "\t[5] Logout.\n";
	cout << "===========================================\n";

	PerfromATM_MainMenueOptions(enATM_MainMenueScreen(ReadAtmMainMenueScreen()));
}
void Login() {

	bool LoginFaild = false;
	string AccountNumber, PinCode;

	do {
		system("cls");
		cout << "-----------------------------------\n";
		cout << "\tLogin Screen";
		cout << "\n-----------------------------------\n";

		if (LoginFaild) {
			cout << "Invlaid Account Number/PinCode!\n";
		}

		cout << "AccountNumber : ";
		cin >> AccountNumber;
		cout << "Enter PinCode : ";
		cin >> PinCode;

		LoginFaild = !LoadClientInfo(AccountNumber, PinCode);

	} while (LoginFaild);
	ShowAtmMainMenueScreen();
}

int main()
{
	Login();
	return 0;
}
