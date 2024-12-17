#include "bill.cpp"

using namespace std;

void menu(inventory &i){
    cout<<"1. Create bill"<<endl;
    cout<<"2. Add a product to inventory"<<endl;
    cout<<"3. Remove a product from inventory"<<endl;
    cout<<"4. Search a product in inventory"<<endl;
    cout<<"5. Update a product from inventory"<<endl;
    cout<<"6. List of all products from inventory"<<endl;
    cout<<"0. Exit"<<endl;
    cout<<"Enter your choice: ";
    int n;
    cin>>n;
    switch (n){
    case 0:
        delete &i;
        exit(1);
    case 1:
        {
            try{bill b(i);}
            catch(int a){if(-1 == a)cout<<"Bill Cancled!!"<<endl;}
            catch(...){cout<<"Unknown issue in bill generation!!"<<endl;}
            cout<<"Enter something: ";
            string a;
            cin>>a;
            cin.ignore();
            system("cls");
            menu(i);
        }
        
    case 2:
        i.add();
        system("cls");
        menu(i);
    case 3:
        i.remove();
        system("cls");
        menu(i);
    case 4:
        i.search();
        system("cls");
        menu(i);
    case 5:
        i.update();
        system("cls");
        menu(i);
    case 6:
        i.show();
        system("cls");
        menu(i);
    
    default:
        system("cls");
        menu(i);
    }
}

int main(int argc, char const *argv[]){
    inventory I;
    menu(I);
    return 0;
}
