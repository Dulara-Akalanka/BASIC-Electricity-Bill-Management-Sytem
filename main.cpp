#include <iostream>
#include <fstream>
#include <ctime>
//#include <cstdio>

using namespace std;

void add_customer(){
    string accnt_number, customer_name, customer_address;

    cout << "Enter an Account number : ";
    cin >> accnt_number;
    cin.ignore();
    cout << "Enter customer name : ";
    getline(cin,customer_name);
    cout << "Enter customer address : ";
    getline(cin,customer_address);

    fstream file, file1;
    file1.open( accnt_number + "history.txt", ios::out);
    file.open(accnt_number + ".txt", ios::out);

    file << customer_name << endl;
    file << customer_address << endl;

    file1.close();
    file.close();

}

void display_record(){
    string accnt_no, text;

    cout << "Enter the Account Number : ";
    cin >> accnt_no;

    fstream file, file1;
    file.open(accnt_no + ".txt", ios::in);
    file1.open(accnt_no + "history.txt", ios::in);

    while(getline(file,text)){
       cout << text << endl;
    }
    cout << endl;

    cout << "Records of the customer: " << endl;
    while(getline(file1,text)){
        cout << text << endl ;
    }

}

 void compute_bill(){

    string months[] = {"No records yet","January", "February", "March","April", "May", "June",
    "July", "August", "September", "October", "November", "December"};
    int month_number = 0;
    string month_name, account_number, text;
    fstream file1,file2;
    double lastreading = 0, meter_reading = 0, Charge = 0;
    const double tax = 50;

    bool flag;

    do{
    flag = false;
    cout << "Enter the Account Number : ";
    cin >> account_number;
    cout <<endl;

    file1.open(account_number+".txt", ios::in);

    if(!file1){
        cout << "Invalid Account Number" << endl;
        flag = true;
       }
    }while(flag);


// get line by line from file

    getline(file1,text);
    cout << "Owner      :"+text << endl;
    getline(file1,text);
    cout << "Address    :"+text << endl <<endl;
    file1.close();
    cout << endl;

    bool flag1 ;
    do {
    flag1=true;
    cout << "Enter the month number :  ";
    while(!(cin >> month_number)){
        cout << "Invalid Input, Enter a Number : ";
        cin.clear();
        cin.ignore(123, '\n');
    }
    if (month_number > 0 && month_number < 13) {
        flag1=false;
        }
    }while(flag1);
    file2.open(account_number+"history.txt", ios::in);

    while(getline(file2,text)){
        if (text == months[month_number -1] ){
            cout << "LastMonth :" + text << endl;
            getline(file2,text);
            lastreading = stoi(text);// convert string to int
            cout << "Last month meter reading : " << lastreading << endl;
            getline(file2,text);
            cout << "Last month charge : " + text << endl;
        }}
    file2.close();

    cout << "Enter the meter reading : ";
    while(!(cin >> meter_reading)){
        cout << "Invalid Input, Enter a Number : ";
        cin.clear();
        cin.ignore(123, '\n');
    }

    double CurrentUsage = meter_reading - lastreading;

    if(CurrentUsage >= 1 && CurrentUsage <=30 ){
       Charge = CurrentUsage * 7.85;
        }
        else if(CurrentUsage >= 31 && CurrentUsage <=60){
            Charge = (30 * 7.85) + (CurrentUsage - 30) * 7.85 ;
            }
                else if(CurrentUsage >= 61 && CurrentUsage <=90){
                    Charge = (60 * 7.85) + (CurrentUsage - 60) * 10.00;
                        }
                        else if(CurrentUsage >= 91 && CurrentUsage <=120){
                            Charge = (60 * 7.85) + 30 * 10.00 + (CurrentUsage - 90) * 27.75;
                            }
                            else if(CurrentUsage >= 121 && CurrentUsage <=180){
                                Charge = (60 * 7.85) + 30 * 10.00 + 30 * 27.75 + (CurrentUsage - 120) * 32.00;
                                }
                                else{
                                    Charge = (60 * 7.85) + 30 * 10.00 + 30 * 27.75 + 60 * 32.00 + (CurrentUsage - 180) * 45.00;
                                    }


    cout << "\n\t\t Electricity Bill for the month of " << months[month_number] << " \n" << endl;
    cout <<  "\nYour current month usage is : "<< CurrentUsage << endl << endl;
    cout <<  "The payment for the meter reading Rs. " << Charge << endl << endl;
    cout << "Tax for the month : " << tax << endl << endl;
    cout <<  "Total payment for the month is Rs. " << Charge + tax << endl;

    ofstream file3 ;
    file3.open(account_number+"history.txt", fstream::app);
    file3 << months[month_number] << endl;// insert values to file of current month
    file3 << meter_reading << endl;
    file3 << Charge << endl;
    file3 << endl;
    file3.close();
}

void delete_record(){

    char accnt_name[20];
    int value;

    cout << "Enter the account number of the file to be deleted (sample.txt): ";
    cin >> accnt_name;

    value = remove(accnt_name);// can insert only char type within brackets - remove("sample.txt") possible
    if(value == 0)
       cout << "File Deleted Successfully";
    else
       cout << "Error Occur in Deleting File";

}

int main()
{
    int option_number;
    cout << "\t\t\t .....Electricity Management System....." << endl;
    cout << endl;
    cout << "\t 1 --> Add a New Customer." << endl;
    cout << "\t 2 --> Display Customer Records." << endl;
    cout << "\t 3 --> Compute Customer Bill." << endl;
    cout << "\t 4 --> Delete a Customer Record File" << endl;
    cout << "\t 5 --> Exit." << endl;
    cout << endl;

    cout << "Enter the option number you need : ";
    while(!(cin >> option_number)){
        cout << "Invalid Input, Enter a Number : ";
        cin.clear();
        cin.ignore(123, '\n');
    }
    cout << endl;

    switch(option_number){
        case(1):
            add_customer();
            break;
        case(2):
           display_record();
            break;
        case(3):
            compute_bill();
            break;
        case(4):
            delete_record();
            break;
        case(5):
            return 0;
            break;
        default:
            cout << "Invalid Number";
            return 0;
    }

    return 0;
}
  //declaring argument for time()
    //time_t tt;
    //declaring variable to store return value of localtime()
    //struct tm * ti;
    //applying time
    //time(&tt);
    //using localtime()
    //ti = localtime(&tt);
   // cout << "Day date and time is :" << asctime(ti);
