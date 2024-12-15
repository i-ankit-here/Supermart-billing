#include "iostream"
#include "iomanip"
#include "string.h"
using namespace std;
class item{
    friend class inventory;
    friend class bill;
protected:
    int itemid;
    char type[30];
    char name[50];
    float price;
    int quantity;
    float discount;
    float tax;
public:
    item(){
        try{
            setName();
            setId();
            setPrice();
            setQuantity();
        }catch(char const str[]){
            cout<<"str"<<endl;
        }
        catch(...){
            cout<<"Some error occured while creating item"<<endl;
        }
    };
    item(int a){};
    item(char str[],float prc,float qty){
        strcpy(name,str);
        price = prc;
        quantity = qty;
    }
    ~item(){};
    
    void setName(){
        cout<<"Enter name of item: ";
        cin>>name;
        if(!name || !name[0])throw("No item name provided!");
    };
    void setId(){
        cout<<"Enter productId: ";
        cin>>itemid;
        if(!itemid)throw("ItemId is required");
    }
    void setPrice(){
        cout<<"Enter price of item: ";
        cin>>price;
        if(price==0)throw("Zero price is set");
    };
    void setQuantity(){
        cout<<"Enter quantity of item: ";
        cin>>quantity;
    };

    virtual void display() = 0;
    virtual float calculate_discount() = 0;
    virtual float calculate_tax() = 0;
    virtual float getDiscount_percent() = 0;
    virtual float getTax_percent() = 0;
};

class electronic:public item{
    float static tax_percent;
    float static discount_percent;
    friend class inventory;
public:
    electronic():item(){
        tax = calculate_tax();
        discount = calculate_discount();
        strcpy(type,"electronic");
    }
    electronic(int a):item(a){};
    void display(){
        cout<<"============================================================="<<endl;
        cout<<setw(25)<<"Name of item: "<<name<<endl;
        cout<<setw(25)<<"Product Id: "<<itemid<<endl;
        cout<<setw(25)<<"Product Type: "<<type<<endl;
        cout<<setw(25)<<"Price of item: "<<price<<endl;
        cout<<setw(25)<<"Quantity of item: "<<quantity<<endl;
        cout<<setw(25)<<"Tax(%): "<<tax_percent<<endl;
        cout<<setw(25)<<"Discout(%): "<<discount_percent<<endl;
        cout<<setw(25)<<"Final Price of item: "<<price+tax-discount<<endl;
        cout<<"============================================================="<<endl;
    }
    float calculate_discount(){
        return price*discount_percent/(float)100;
    }
    float calculate_tax(){
        return price*tax_percent/(float)100;
    }
    virtual float getDiscount_percent(){
        return this->discount_percent;
    }
    virtual float getTax_percent(){
        return this->tax_percent;
    };
};

float electronic::tax_percent = 12;
float electronic::discount_percent = 10;

class grocery:public item{
    float static tax_percent;
    float static discount_percent;
    friend class inventory;
public:
    grocery():item(){
        tax = calculate_tax();
        discount = calculate_discount();
        strcpy(type,"grocery");
    }
    grocery(int a):item(a){};
    void display(){
        cout<<"============================================================="<<endl;
        cout<<setw(25)<<"Name of item: "<<name<<endl;
        cout<<setw(25)<<"Product Id: "<<itemid<<endl;
        cout<<setw(25)<<"Product Type: "<<type<<endl;
        cout<<setw(25)<<"Price of item: "<<price<<endl;
        cout<<setw(25)<<"Quantity of item: "<<quantity<<endl;
        cout<<setw(25)<<"Tax(%): "<<tax_percent<<endl;
        cout<<setw(25)<<"Discout(%): "<<discount_percent<<endl;
        cout<<setw(25)<<"Final Price of item: "<<price+tax-discount<<endl;
        cout<<"============================================================="<<endl;
    }
    float calculate_discount(){
        return price*discount_percent/(float)100;
    }
    float calculate_tax(){
        return price*tax_percent/(float)100;
    }
    virtual float getDiscount_percent(){
        return this->discount_percent;
    }
    virtual float getTax_percent(){
        return this->tax_percent;
    };
};

float grocery::tax_percent = 12;
float grocery::discount_percent = 5;