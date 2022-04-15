#include "namespace.cpp"

class Account
{
private:
    string uname;
    string pword;
    string enc_code;
    string dec_code;

public:
    void signup();
    void login();

    void encrypt(string &u, string &p, string &enc);

    void savedata(string &enc);

    void decrypt(string &u, string &p, string &dec);

    void checkdata(string &dec,string &ufile);

    bool validate(string &val, string &dec,string &ufile);
};

int main()
{
    Account reg_acc, log_acc;

    int welcome_choice;
    cout << "\n \n Welcome to notes mangement software" << endl;
    cout << "\n 1) Register Your New Account \n 2) Login To Your Account \n \n Choose an option = ";

    cin >> welcome_choice;

    switch (welcome_choice)
    {

    case 1:
        cout << "\n You reach to register Page \n " << endl;
        reg_acc.signup();
        break;
    case 2:
        cout << "\n You reach to Login Page" << endl;
        log_acc.login();
        break;
    default:
        cout << "\n You entered invalid input" << endl;
    }

    return 0;
}

void Account::checkdata(string &dec,string &ufile)
{

    fstream myFile;
    myFile.open("u_account.txt", ios::in);

    if (myFile.is_open())
    {
        bool status;
        string line;
        string word;
        while (getline(myFile, line))
        {
            status = validate(line, dec,ufile);
        }
        if(status == false){
            cout<<"\n Invalid Login";
        }
        myFile.close();
    }
}

bool Account::validate(string &line, string &dec,string &fname)
{
    if (dec == line)
    {
        cout << "\n Successful login \n";

        while (true)
        {
            cout << "\n Choose Option \n 1) Enter new notes \n 2) View your previous notes \n 3) Logout " << endl;
            int choice;

            cout << "\n Your choice = ";

            cin >> choice;

            fstream ufile;

            if (choice == 1)
            {
                
                string fi = fname+".txt";
                ufile.open(fi,ios::out);
                if (ufile.is_open())
                {
                    string userdata;
                    cout << "\n Enter your notes = ";
                    getline(cin >> ws, userdata);

                    ufile << userdata;

                    cout << "\n \n Your detail is saved";
                    ufile.close();
                }
            }
            else if (choice == 2)
            {
                string fi = fname+".txt";
                ufile.open(fi, ios::in);
                if (ufile.is_open())
                {
                    string udetail;

                    while (getline(ufile, udetail))
                    {
                        cout << udetail << endl;
                    }

                    ufile.close();
                }
            }

            else
            {
                exit;

                cout << "\n You are logged out\n \n";
                break;
            }

            cout << "\n Do you want to look other option ? Enter 1 for yes = ";
            int ques;
            cin >> ques;
            if (ques == 1)
            {
                continue;
            }
            else
            {
                cout << "\n You are logged out";
                break;
            }
        }

        return true;
    }

    return false;
}

void Account::decrypt(string &u, string &p, string &dec)
{
    dec = u + p;
    reverse(dec.begin(), dec.end());

    checkdata(dec,u);
}

void Account::savedata(string &enc)
{
    fstream myFile;
    myFile.open("u_account.txt", ios::app);

    if (myFile.is_open())
    {
        myFile << enc << endl;
        myFile.close();
        cout << "\n Register Process completed! \n"
             << endl;

        cout << "Press 1 to login to your account = ";
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            login();
        }
    }

    else
        cout << "\n some error occured";
}

void Account::encrypt(string &u, string &p, string &enc)
{
    enc = u + p;
    reverse(enc.begin(), enc.end());
}

void Account::signup()
{
    cout << "\n Enter your username = ";
    cin >> uname;
    cout << "\n Enter your password = ";
    cin >> pword;

    fstream mynote;
    string name = uname+".txt";
    mynote.open(name,ios::out);
    
    mynote.close();

    encrypt(uname, pword, enc_code);

    savedata(enc_code);

    
}

void Account::login()
{
    cout << "\n Enter your username = ";
    cin >> uname;
    cout << "\n Enter your password = ";
    cin >> pword;

    decrypt(uname, pword, dec_code);
}
