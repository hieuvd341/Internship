#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{
   
   protected: 
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};
class LRUCache : public Cache{
public:
    LRUCache(int capacity) {
        this->cp = capacity;
    }
    void set(int k, int v) override{
        auto iterator = mp.find(k);
        if(mp.size()==0)
        {
            mp[k]=new Node(k,v);
            tail=mp[k];
            head=mp[k];
            return;
        }
        if(mp.size()<cp) {
            if(iterator != mp.end()) {
                Node * found = new Node(k, v);
                found ->next = head;
                head ->prev = found;
                found -> prev = nullptr;
                head = found;
                if(mp[k] -> next != nullptr) {
                    (mp[k]->next)->prev = mp[k]->prev;
                }
                if(mp[k] ->prev != nullptr) {
                    (mp[k]->prev)->next=mp[k]->next;
                }
                mp[k]= found;
            } else {
                mp[k] = new Node(k, v);
                mp[k]  ->next = head;
                head ->prev = mp[k] ;
                mp[k]  ->prev = nullptr;
                head = mp[k];
            }
        } else {
                mp.erase(tail->key);  
                (tail -> prev) ->next = nullptr;
                tail ->prev = nullptr;
                tail = tail->prev;
                
                mp[k] = new Node(k, v);
                mp[k]  ->next = head;
                head ->prev = mp[k] ;
                mp[k]  ->prev = nullptr;
                head = mp[k];  

        }
        
    }
    int get(int k) override
    {
        if(mp.find(k)!=mp.end())
        {
            return mp[k]->value;
        }
       return -1; 
    }
    
};
int main() {
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      } 
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}
