#include<iostream>
#include<vector>
#include<algorithm>
#include<typeinfo>
#include<unordered_map>
#include<set>
using namespace std;

template<class T>
void removepaisa(T *val){                   //unit 4 template functions
    int withoutpaisa;                     //function to simplify banking by including only rupee transactions 
    if(*val/1==1)
      return;
    else{
         *val=(int)(*val);
    }

}

class bank{                                 //unit 1 class
    protected:
    string name;
    int age;
    string accno;
    double curbal;
    string password;
    public:
    virtual void getdata()=0;               //unit 3 virtual functions, this is an abstract class
    virtual void deposit()=0;
    virtual void withdrawal()=0;
    virtual void display()=0;
    virtual string accountnum()=0;
    bool passwordVerify(string passwrd);
    bool passwordVerify(string password1,string password2);       //unit 2 function overloading
    string passwrd(){return password;}
};

bool bank::passwordVerify(string passwrd){
    bool len=false;
    bool specialchar=false;
    bool uppercase=false;
    if(passwrd.length()>=8)
        len=true;
    else {
        cout<<"Password too short\n";
        return false;
    }
    if(passwrd[0]>=65 && passwrd[0]<=90)
         uppercase=true;
    else{
        cout<<"Password must begin with a upper case letter\n";
        return false;
    }   
    for(int i=0;i<passwrd.length();i++){
        if(passwrd[i]>=33 && passwrd[i]<=64)
             specialchar=true;
    }
    if(!specialchar){
        cout<<"Password must have a special character\n";
        return false;
    }
    return true;
}
bool bank::passwordVerify(string password1,string password2){
    if(password1==password2)
       return true;
    else
       return false;
}

class savingsaccount:public bank{                           //unit 3 inheritance
    double rate_of_interest;
    int no_of_transactions;
    public:
    savingsaccount(){
        rate_of_interest=2.5;
        no_of_transactions=0;
    }                                    
    void addinterest(){
        curbal=curbal+(curbal*(rate_of_interest/100));
        removepaisa(&curbal);

    }
    void getdata(){
        cout<<"Enter name\n";
        cin>>name;
        cout<<"Enter age\n";
        cin>>age;
        cout<<"Enter password. Your password should be greater than or equal to 8 characters.\n";
        cout<<"Your password must begin with an uppercase letter, have atleast one special character.\n";
        cin>>this->password;
        while(1){
            if(passwordVerify(password))
                break;
            else{
                cout<<"Enter password again\n";
                cin>>password;
            }
        }
        accno="SAVACC"+ to_string(rand()%10000);
        cout<<"Enter initial deposit (should be greater than 500)\n";
        cin>>curbal;
        while(1){
            if(curbal<=500){
                cout<<"Initial deposit not sufficient. Please enter amount greater than 500\n";
                cin>>curbal;
            }
            else
              break;
        }
        removepaisa(&curbal);
    }
    void deposit(){
        double amount;
        if(no_of_transactions>3){
            cout<<"No_of_transactions limit is exceeded\n";
            return;
        }
        addinterest();
        no_of_transactions++;
        cout<<"Enter deposit amount\n";
        cin>>amount;
        curbal+=amount;
        removepaisa(&curbal);

    }
    void withdrawal(){
        double amount;
        if(no_of_transactions>3){
            cout<<"No_of_transactions limit is exceeded\n";
            return;   
        }
        no_of_transactions++;
        cout<<"Enter withdrawal amount\n";
        cin>>amount;
        if(amount>curbal){
            cout<<"Balance not sufficient\n";
            return;
        }
        curbal-=amount;
        removepaisa(&curbal);
    }
    void display(){
        cout<<"Name: "<<name<<endl;
        cout<<"Age: "<<age<<endl;
        cout<<"Account type: Savings Account\n";
        cout<<"Account Number: "<<accno<<endl;
        cout<<"Rate of interest: "<<rate_of_interest<<endl;
        cout<<"Balance: "<<curbal<<endl;
    }
    string accountnum(){
        return accno;
    }

};

class currentaccount:public bank{
    double minimum_balance;
    public:
    currentaccount(){
        minimum_balance=3000;
    }
    void getdata(){
        cout<<"Enter name\n";
        cin>>name;
        cout<<"Enter age\n";
        cin>>age;
        cout<<"Enter password. Your password should be greater than or equal to 8 characters.\n";
        cout<<"Your password must begin with an uppercase letter, have atleast one special character.\n";
        cin>>password;
        while(1){
            if(this->passwordVerify(password))
                break;
            else{
                cout<<"Enter password again\n";
                cin>>password;
            }
        }
        accno="CURACC"+ to_string(rand()%10000);
        cout<<"Enter initial deposit (should be greater than 3000)\n";
        cin>>curbal;
        while(1){
            if(curbal<=3000){
                cout<<"Initial deposit not sufficient. Please enter amount greater than 3000\n";
                cin>>curbal;
            }
            else
              break;
        }
        removepaisa(&curbal);

    }
    void deposit(){
        double amount;
        cout<<"Enter deposit amount\n";
        cin>>amount;
        curbal+=amount;
        removepaisa(&curbal);

    }
    void withdrawal(){
        double amount;
        cout<<"Enter withdrawal amount\n";
        cin>>amount;
        if(amount>(curbal-minimum_balance)){
            cout<<"Balance not sufficient\n";
            return;
        }
        curbal-=amount;
        removepaisa(&curbal);

    }
    void display(){
        cout<<"Name: "<<name<<endl;
        cout<<"Age: "<<age<<endl;
        cout<<"Account type: Current Account\n";
        cout<<"Account Number: "<<accno<<endl;
        cout<<"Balance: "<<curbal<<endl;
    }
    string accountnum(){
        return accno;
    }
};

bank *factory(int ch){
    if(ch==1)
       return new savingsaccount;
    else if(ch==2)
       return new currentaccount; 
    return NULL;     
}

bank *create_account(unordered_map<string,bank *>& map){
    bank *bp;
    int ch;
    cout<<"Enter 1 to create savings bank account and 2 for current account\n";
    cin>>ch;
    bp=factory(ch);
    if(typeid(*bp)==typeid(savingsaccount)){                //unit 5 RTTI
        cout<<"You have chosen savings type account\n";
        bp->getdata();
        map[bp->accountnum()]=bp;
        cout<<"Your accno is "<<bp->accountnum()<<" Please note down the account number\n";
    }     
    else if(typeid(*bp)==typeid(currentaccount)){
        cout<<"You have chosen current type account\n";
        bp->getdata();
        map[bp->accountnum()]=bp;
        cout<<"Your accno is "<<bp->accountnum()<<" Please note down the account number\n";
    }
    return bp;
}


int main(int argc, char const *argv[])
{
    unordered_map<string,bank*> map;
    bank *bp;
    string acno,choice,pass;
    vector<bank*> v;                                              //unit 5 standard template library
    int ch;
    do{
        cout<<"1.Create account\n";
        cout<<"2.Deposit amount\n";
        cout<<"3.Withdraw amount\n";
        cout<<"4.Display your account information\n";
        cout<<"5.Display all the account holder's information\n";
        cout<<"6.Delete an account\n";
        cout<<"Enter your choice\n";
        cin>>ch;
        switch(ch){
            case 1:
            bp=create_account(map);
            v.push_back(bp);
            break;

            case 2:
            cout<<"Enter account number\n";
            cin>>acno;
            if(map.find(acno)==map.end()){
                cout<<"Incorrect account number\n";
                break;
            }
            cout<<"Enter passsword\n";
            cin>>pass;
            if(!map[acno]->passwordVerify(map[acno]->passwrd(),pass)){
                cout<<"Password Incorrect\n";
                break;
            }
            map[acno]->deposit();
            break;

            case 3:
            cout<<"Enter account number\n";
            cin>>acno;
            if(map.find(acno)==map.end()){
                cout<<"Incorrect account number\n";
                break;
            }
            cout<<"Enter passsword\n";
            cin>>pass;
            if(!map[acno]->passwordVerify(map[acno]->passwrd(),pass)){
                cout<<"Password Incorrect\n";
                break;
            }
            map[acno]->withdrawal();
            break;

            case 4:
            cout<<"Enter account number\n";
            cin>>acno;
             if(map.find(acno)==map.end()){
                cout<<"Incorrect account number\n";
                break;
            }
            cout<<"Enter passsword\n";
            cin>>pass;
            if(!map[acno]->passwordVerify(map[acno]->passwrd(),pass)){
                cout<<"Password Incorrect\n";
                break;
            }
            map[acno]->display();
            break;

            case 5:  
            cout<<"Displaying all account holder's information\n";
            for(int i=0;i<v.size();i++){
                v[i]->display();
                cout<<endl;
            }
            break;

            case 6:
            cout<<"Enter account number\n";
            cin>>acno;
             if(map.find(acno)==map.end()){
                cout<<"Incorrect account number\n";
                break;
            } 
            cout<<"Enter passsword\n";
            cin>>pass;
            if(!map[acno]->passwordVerify(map[acno]->passwrd(),pass)){
                cout<<"Password Incorrect\n";
                break;
            }
            bp=map[acno];
            cout<<"Your account with account number "<<bp->accountnum()<<" has been deleted successfully\n";
            map.erase(acno);
            vector<bank*>::iterator it;
            it=find(v.begin(),v.end(),bp);
            v.erase(it);
            delete bp;
            break;

            defualt:
            cout<<"Enter correct choice\n";
            cin>>ch;
        }
        cout<<"Do you want to continue?(yes/no)\n";
        cin>>choice;
    }while(choice=="yes");
    return 0;
}
