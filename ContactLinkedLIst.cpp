#include <iostream>
using namespace std;

class ContactNode {
public:
  ContactNode(string name = "", string phoneNum = "");
  string GetName() const;
  string GetPhoneNumber() const;
  ContactNode* GetNext();
  void InsertAfter(ContactNode* node);
  void PrintContactNode();


private:
  string contactName;
  string contactPhoneNum;
  ContactNode* nextNodePtr;
};

ContactNode::ContactNode(string name, string phoneNum) {
  this->contactName = name;
  this->contactPhoneNum = phoneNum;
  this->nextNodePtr = nullptr;
}

string ContactNode::GetName() const {
  return this->contactName;
}

string ContactNode::GetPhoneNumber() const {
  return this->contactPhoneNum;
}

ContactNode* ContactNode::GetNext() {
  return this->nextNodePtr;
}

void ContactNode::InsertAfter(ContactNode* nodeLoc) {
  ContactNode* tmpNext = nullptr;

  tmpNext = this->nextNodePtr;
  this->nextNodePtr = nodeLoc;
  nodeLoc->nextNodePtr = tmpNext;
}

void ContactNode::PrintContactNode() {
  cout << "Name: " << this->contactName << endl;
  cout << "Phone number: " << this->contactPhoneNum << endl;
}



int main() {
  int personCount = 1;
  string nextContactName;
  string nextContactPhoneNum;
  ContactNode* headNode = nullptr;
  ContactNode* currentNode = nullptr;

  getline(cin, nextContactName);
  cin >> nextContactPhoneNum;
  headNode = new ContactNode(nextContactName, nextContactPhoneNum);
  currentNode = headNode;

  while (!cin.fail()) {
    cout << "Person " << personCount << ": ";
    cout << currentNode->GetName() << ", " << currentNode->GetPhoneNumber() << endl;
    personCount++;

    cin.ignore();
    getline(cin, nextContactName);

    cin >> nextContactPhoneNum;
    currentNode->InsertAfter(new ContactNode(nextContactName, nextContactPhoneNum));
    currentNode = currentNode->GetNext();
  }

  ContactNode* nodeTrack = headNode;
  cout << "CONTACT LIST" << endl;
  while (nodeTrack->GetNext() != nullptr) {
    nodeTrack->PrintContactNode();
    cout << endl;
    nodeTrack = nodeTrack->GetNext();
  }

  return 0;
}
