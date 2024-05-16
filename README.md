# System-Bank-v1
This system appears to be a basic bank management application implemented in C++. Here are the key components and functionalities:

1.Struct stInfoClient:
  -Represents client information, including account number, PIN code, client name, phone, balance, and 
   a flag for deletion.
  -Each client’s data is stored in an instance of this struct.
  
2.Functions and Procedures:
  -Backup(): Displays a message and waits for a key press to return to the main menu.
  -PrintMainMenueScreen(): Prints the main menu options.
  -PrintClient(stInfoClient client): Displays details of a single client.
  -PrintInfoLineClient(stInfoClient client): Prints a formatted line of client information.
  -PrintAllInfoClients(vector<stInfoClient>& vClient): Prints a table of all clients’ information.
  -EndProgram(): Displays a program-ending message and waits for a key press.
  
3.Enum enChoose:
  -Represents menu options (e.g., show client list, add new client, etc.).
  
4.Data Handling Functions:
  -SplitString(string S1, string Delim = "#//#"): Splits a string into a vector of substrings using a 
   delimiter.
  -ConvertLineToRecord(string S1, string Seperator = "#//#"): Converts a line of data (from a file) 
   into a stInfoClient record.
5.Usage:
   The program likely reads data from a file (e.g., “MyFill.text”) to populate the stInfoClient structs.
   It provides menu options for managing clients (showing, adding, updating, deleting, finding).
   The PrintAllInfoClients function displays a table of client information.
