// Josh Post
// CSC 344
// Assignment #2

// Program for keeping track of orders and seafood stock.
// Opened stock gets first priority to be sold,
// then the oldest stock gets priority after that.
// When an order can not be fulfilled, it is added to 
// a queue in a postition based on the order date.


#include <iostream>
#include <string.h>
#include <sstream>
#include <iomanip>
#include <vector>
using namespace std;

struct SEAFOOD {
  string type;
  string day,month,year;
  int quantity,cap;
};
struct ORDER {
  string type;
  int amount;
  string day,month,year;
};

void hello();
void insert(vector <SEAFOOD> &stock);
void oinsert (vector <ORDER> &orders);
void print(vector <SEAFOOD> &stock,string type);
void add(vector <SEAFOOD> &stock, string date, string item, int amount);
void sell(vector <ORDER> &stock, string date, string item, int amount);
bool checkOrders(vector <ORDER> &orders,vector <SEAFOOD> &seafood, string type);

int main ()
{
	hello();
	vector<SEAFOOD> stock;
	vector<ORDER> orders;
	string event="",date,item;
	int amount;
	while (event != "0")
	{
		cout<<"\n\nEvent: ";cin>>event;cout<<"Date: ";cin>>date;cout<<"Item: ";cin>>item;cout<<"Amount: ";cin>>amount;
		if(!cin)
		{
			cin.clear();
			cin.ignore( numeric_limits <streamsize> ::max(), '\n' );
			if(event == "0")
				break;
			cout<<"\42Amount\42 field requires a number.";
			continue;
		}
		if(date.length() <10)
		{
			if(event == "0")
                                break;
			cout<<"\42Date\42 must be formatted in xx/xx/xxxx form.";
			continue;
		}
		if(event == "stock")
			add(stock,date,item,amount);
		else if(event == "buy")
			sell(orders,date,item, amount);
		else if(event == "0")
			break;
		else
			cout<<"\nOptions:\nstock - add to the stock\nbuy - customer buys from stock\n0 - exit program\n";
		while(checkOrders(orders,stock,item));
	}
	cout<<"\n\nHave a nice day!\n";
	return 0;
}

void hello()
{
	for(int x = 1;x <= 140;x++)
	{
		if((((x < 20)||(x > 120))&&(x%20 != 0))||(x%20 == 1))
			cout<<char(219);
		else if(x%20 == 0)
			cout<<char(219)<<endl;
		else if(x == 47)
		{
			cout<<"Josh's";
			x+=5;
		}
		else if(x == 67)
		{
			cout<<"seafood";
			x+=6;
		}
		else if(x == 87)
		{
			cout<<"shop";
			x+=3;
		}
		else
			cout<<" ";
	}
	return;
}

void add(vector <SEAFOOD> &stock, string date, string item, int amount)
{
	SEAFOOD x;
	if(item == "swordfish")
                x.cap = 8;
        else if(item == "crab")
                x.cap = 6;
        else if(item == "lobster")
                x.cap = 4;
        else if(item == "shrimp")
                x.cap = 50;
        else
        {
                cout<<"\nWe don't carry "<<item<<". Sell that to someone else!";
                return;
        }
	cout<<"\nAdding "<<item<<" to stockpile.";
	string m,d,y;
	m = date.substr(0,2);
	d = date.substr(3,2);
	y = date.substr(6,4);
	x.type = item;
	x.day = d;
	x.month = m;
	x.year = y;
	x.quantity = x.cap;
	for(;amount > 0;amount--)
	{
		stock.insert(stock.begin(),x);
		insert(stock);
	}
	return;
}

void sell(vector <ORDER> &orders,string date, string item, int amount)
{
	if(!((item == "swordfish") || (item == "crab") || (item == "shrimp") || (item == "lobster")))
	{
		cout<<"\nSorry, we don't sell any "<<item<<"!";
		return;
	}
	ORDER x;
        cout<<"\nChecking stockpile for "<<item<<".";
        string m,d,y;
        m = date.substr(0,2);
        d = date.substr(3,2);
        y = date.substr(6,4);
        x.type = item;
        x.day = d;
        x.month = m;
        x.year = y;
        x.amount = amount;
	orders.insert(orders.begin(),x); 
        oinsert(orders);
	return;
}

bool checkOrders(vector <ORDER> &orders, vector <SEAFOOD> &stock, string type)
{
	if(orders.size() != 0)
	{
		cout<<"\nChecking order...";
		if (stock.size() == 0)
		{
                        cout<<"\nNo orders on the queue can be filled yet.";
			print(stock, type);
			return false;
		}
		bool oflag = false;
		bool flag;
		vector<int>deletes;
		int num;
		for(int a = 0;a < orders.size(); a++)
		{
			deletes.clear();
			flag = false;
			num = orders[a].amount;
			for(int b = 0;b <= stock.size()-1; b++)
			{
				if(orders[a].type == stock[b].type)
				{
					if(flag == true)
						continue;
					if(num <= stock[b].quantity)
					{
						deletes.insert(deletes.begin(),b); 
						deletes.insert(deletes.begin(),stock[b].quantity - num);
						flag = true;
					}
					else
					{
						deletes.insert(deletes.begin(),b);
						num -= stock[b].quantity;
					}
				}
			}
			if (flag == true)
			{	
				oflag = true;
				cout<<"Order for "<<orders[a].amount<<" "<<orders[a].type<<" fullfilled.";
				int y = 2;
				if(deletes[0] != 0)
					stock[deletes[1]].quantity = deletes[0];
				else
					y--;
				for (;y < deletes.size(); y++)
				{
					stock.erase(stock.begin() + deletes[y]);
				}
				
				orders.erase(orders.begin() + a);
				return true;
			}
		}
		if (oflag == false)
			cout<<"\nNo orders on the queue can be filled yet.";
	}
	print(stock, type);
	return false;
}
void print (vector <SEAFOOD> &stock, string type)
{
	cout<<"\n"<<type<<": ";
	int flag = 0;
	for(int i = 0; i < stock.size(); i++)
	{
		if(stock[i].type == type)
		{
			if (flag != 0)
				cout<<",";
			cout<<" ["<<stock[i].cap<<"("<<stock[i].quantity<<")"<<stock[i].month<<"/"<<stock[i].day<<"/"<<stock[i].year<<"]";
			flag++;
		}
	}
	return;
}

void insert (vector <SEAFOOD> &stock)
{
	string date = stock[0].year + stock[0].month + stock[0].day, d;
	if(stock.size() <= 1)
		return;
	SEAFOOD s = stock[0];
	stock.erase(stock.begin());
	bool flag = false;
	for (int x = 0; x < stock.size(); x++)
	{
		d = stock[x].year + stock[x].month + stock[x].day;
		if((stock[x].quantity != stock[x].cap) || (d < date));
		else
		{
			stock.insert(stock.begin() + x,s);
			flag = true;
			break;
		}
	}
	if(flag == false)
		stock.push_back(s);
	return;
}

void oinsert (vector <ORDER> &orders)
{
        string date = orders[0].year + orders[0].month + orders[0].day, d;
	if(orders.size() <= 1)
		return;
	ORDER o = orders[0];
	bool flag = false;
	orders.erase(orders.begin());
	for (int x = 1; x < orders.size(); x++)
        {
                d = orders[x].year + orders[x].month + orders[x].day;
                if(d < date)
                        continue;
                else
		{
			orders.insert(orders.begin() + x,o);
        		flag = true;
			break;
		}
	}
	if(flag == false)
                orders.push_back(o);
        return;
}

