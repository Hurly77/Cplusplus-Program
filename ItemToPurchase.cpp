#include <iostream>
#include <string>


using namespace std;
class ItemToPurchase {
public:
  ItemToPurchase();
  void SetName(string name);
  string GetName();
  void SetPrice(int price);
  int GetPrice();
  void SetQuantity(int quantity);
  int GetQuantity();
private:
  string itemName;
  int itemPrice;
  int itemQuantity;
};

ItemToPurchase::ItemToPurchase() {
  itemName = "none";
  itemPrice = 0;
  itemQuantity = 0;
}

void ItemToPurchase::SetName(string name) {
  itemName = name;
}

string ItemToPurchase::GetName() {
  return itemName;
}

void ItemToPurchase::SetPrice(int price) {
  itemPrice = price;
}

int ItemToPurchase::GetPrice() {
  return itemPrice;
}

void ItemToPurchase::SetQuantity(int quantity) {
  itemQuantity = quantity;
}

int ItemToPurchase::GetQuantity() {
  return itemQuantity;
}


void GetItemDetails(ItemToPurchase& currentItem, int itemNumber) {
  string inputName;
  int inputPrice;
  int inputQuantity;

  cout << "Item " << itemNumber << endl; // Display item number

  // Prompt User for Item Name
  cout << "Enter the item name:" << endl;
  getline(cin, inputName);
  currentItem.SetName(inputName);

  // Prompt User for Item Price
  cout << "Enter the item price:" << endl;
  cin >> inputPrice;
  currentItem.SetPrice(inputPrice);

  // Prompt User for Item Quantity
  cout << "Enter the item quantity:" << endl;
  cin >> inputQuantity;
  currentItem.SetQuantity(inputQuantity);

  cout << endl;
  cin.ignore(); // Clear input buffer
}

void DisplayTotalCost(ItemToPurchase item1, ItemToPurchase item2) {
  int totalCostOfItems1 = item1.GetPrice() * item1.GetQuantity();
  int totalCostOfItems2 = item2.GetPrice() * item2.GetQuantity();

  cout << "TOTAL COST" << endl;
  cout << item1.GetName() << " " << item1.GetQuantity() << " @ $" << item1.GetPrice() << " = $" << totalCostOfItems1 << endl;
  cout << item2.GetName() << " " << item2.GetQuantity() << " @ $" << item2.GetPrice() << " = $" << totalCostOfItems2 << endl;
  cout << endl;

  cout << "Total: $" << totalCostOfItems1 + totalCostOfItems2 << endl;
}

int main() {
  ItemToPurchase item1;
  ItemToPurchase item2;

  GetItemDetails(item1, 1);
  GetItemDetails(item2, 2);

  DisplayTotalCost(item1, item2);

  return 0;
}