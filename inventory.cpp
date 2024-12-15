#include "product.cpp"
#include "conio.h"
#include "fstream"
#include "vector"
class inventory{
    vector<item*> products;
    fstream file;
    friend class bill;
public:
    inventory(){
        file.open("inventory.dat",ios::binary|ios::in);
        if(!file){
            file.close();
            file.open("inventory.dat",ios::binary|ios::out);
            file.close();
            return;
        }
        file.seekg(0,ios::end);
        long long e = file.tellg();
        file.seekg(0,ios::beg);
        
        while(true){
            // cout<<file.tellg()<<" ";
            electronic temp(1);
            item* it = new electronic(1);
            file.read((char*)&temp,sizeof(temp));
            *it = temp;
            products.push_back(it);
            if(file.tellg()==e)break;
        }  
        file.close();
    };
    void add(){
        system("cls");
        cout<<"Choose the type of product"<<endl;
        cout<<"1. Electronic"<<endl; 
        cout<<"2. Grocery"<<endl; 
        cout<<"0. Cancel add"<<endl; 
        int p;
        cin>>p;
        // if(!file)inventory();
        if(file)file.close();
        file.open("inventory.dat",ios::binary|ios::out|ios::app);
        if(p==1){
            item* it = new electronic();
            products.push_back(it);
            this->file.write((char*)it,sizeof(*it));
            it->display();
        }else if(p==2){
            item* it = new grocery();
            this->file.write((char*)it,sizeof(*it));
            it->display();
            products.push_back(it);
        }
        cout<<"Product added succesfully"<<endl;
        cout<<"Enter anything: ";
        file.close();
        string a;
        cin>>a;
        cin.ignore();
    }
    int searchByid(int id){
        int i = 0;
        while(i<products.size() && products[i]->itemid!=id)i++;
        if(i>=products.size())return -1;
        else return i;
    }
    int searchByName(char name[]){
        int i = 0;
        while(i<products.size() && strcmpi(name,products[i]->name)!=0)i++;
        if(i>=products.size())return -1;
        else return i;
    }

    void search(){
        system("cls");
        cout<<"1. Search by name"<<endl;
        cout<<"2. Search by Product Id"<<endl;
        cout<<"0. Back"<<endl;
        cout<<"Enter your response: ";
        int n;
        cin>>n;
        try{
            int i;
            switch (n){
            case 1:
                char name[50];
                cout<<"\nEnter the Name of Product: ";
                cin>>name;
                i = searchByName(name);
                if(-1 == i)throw ("Product does not exists");
                break;
            case 2:
                cout<<"\nEnter the id of Product: ";
                int id;
                cin>>id; 
                i = searchByid(id);
                if(-1 == i)throw ("Product does not exists");
                break;
            case 0:
                return;
                break;
            
            default:
                return;
                break;
            }
            products[i]->display();
            cout<<"Enter anything: ";
            string a;
            cin>>a;
            cin.ignore();
        }
        catch(char const err[]){
            cout<<err<<endl;
        }
        catch(...){
            cout<<"some error occured while Searching the product\n";
        }
        cout<<"Enter anything: ";
        string a;
        cin>>a;
        cin.ignore();
    }

    void update(){
        system("cls");
        cout<<"1. Update by name"<<endl;
        cout<<"2. Update by Product Id"<<endl;
        cout<<"0. Back"<<endl;
        cout<<"Enter your response: ";
        int n;
        cin>>n;
        try{
            int i;
            switch (n)
            {
            case 1:
                char name[50];
                cout<<"\nEnter the name of Product: ";
                cin>>name;
                i = searchByName(name);
                if(-1 == i)throw "Product does not exists";
                break;
            case 2:
                cout<<"\nEnter the id of Product: ";
                int id;
                cin>>id; 
                i = searchByid(id);
                if(-1 == i)throw "Product does not exists";
                break;
            case 0:
                return;
                break;

            default:
                return;
                break;
            }

            file.open("inventory.dat",ios::binary|ios::in|ios::out);
            if(!file){
                throw("File does not exists!!");
            };

            products[i]->display();
            products[i]->setName();
            products[i]->setId();
            products[i]->setPrice();
            products[i]->setQuantity();
            products[i]->tax = products[i]->calculate_tax();
            products[i]->discount = products[i]->calculate_discount();
            file.seekp(i*sizeof(*products[i]));
            file.write((char*)products[i],sizeof(*products[i]));
            file.close();
            cout<<"Product Updated successfully"<<endl;
            products[i]->display();
        }
        catch(char const err[]){
            cout<<err<<endl;
        }
        catch(...){
            cout<<"some error occured while removing the product\n";
        }
        cout<<"Enter anything: ";
        string a;
        cin>>a;
        cin.ignore();
    }

    void remove(){
        system("cls");
        cout<<"1. Remove by name"<<endl;
        cout<<"2. Remove by Product Id"<<endl;
        cout<<"0. Back"<<endl;
        cout<<"Enter your response: ";
        int n;
        cin>>n;
        try{
            int i;
            switch (n)
            {
            case 1:
                char name[50];
                cout<<"\nEnter the name of Product: ";
                cin>>name;
                i = searchByName(name);
                if(-1 == i)throw "Product does not exists";
                break;
            case 2:
                cout<<"\nEnter the id of Product: ";
                int id;
                cin>>id; 
                i = searchByid(id);
                if(-1 == i)throw "Product does not exists";
                break;
            case 0:
                return;
                break;

            default:
                return;
                break;
            }
        
            products[i]->display();
            products.erase(products.begin()+i);
            if(file)file.close();
            this->file.open("inventory.dat",ios::binary|ios::out);
            if(!this->file)throw("File not updated!!");
            for(auto it:products){
                this->file.write((char*)it,sizeof(*it));
            }
            this->file.close();
            cout<<"Product removed successfully"<<endl;
        }
        catch(char const err[]){
            cout<<err<<endl;
            return;
        }
        catch(...){
            cout<<"some error occured while removing the product\n";
            return;
        }
        cout<<"Enter anything: ";
        string a;
        cin>>a;
        cin.ignore();
        
    }
    void show(){
        cout<<"============================================================================================================================================================"<<endl;
        cout<<std::left<<setw(25)<<"Name"<<setw(20)<<"Product Id"<<setw(20)<<"Type"<<setw(20)<<"Price"<<setw(20)<<"Quantity"<<setw(20)<<"Tax"<<setw(20)<<"Discount"<<setw(20)<<"Final Price"<<endl;
        for(auto it:products){
            cout<<std::left<<setw(25)<<it->name<<setw(20)<<it->itemid<<setw(20)<<it->type<<setw(20)<<it->price<<setw(20)<<it->quantity<<setw(20)<<it->tax<<setw(20)<<it->discount<<setw(20)<<it->price+it->tax-it->discount<<endl;
        }
        cout<<"============================================================================================================================================================"<<endl;
        cout<<"Enter anything: ";
        string a;
        cin>>a;
        cin.ignore();
    }
    ~inventory(){
        if(file)file.close();
        file.open("inventory.dat",ios::binary|ios::out);
        for(auto it:products)file.write((char*)it,sizeof(*it));
        file.close();

    }
};