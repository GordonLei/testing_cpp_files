//
//  rec11.cpp
//  rec11
//
//  Created by Gordon Lei on 4/19/19.
//  Copyright © 2019 Gordon Lei. All rights reserved.
//

#include <iostream>
#include <vector>
#include<unordered_set>

using namespace std;

/*
 functions for use with CS2124 rec11
 -jbs
 */


//bruh does this work

// Node to be used a part of linked list
struct Node {
    Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
    int data;
    Node* next;
};

// listAddHead: adds a data item to the beginning of a [possibly empty] list
void listAddHead(Node*& headPtr, int entry) {
    headPtr = new Node(entry, headPtr);
}

// listClear: frees up all the nodes in a list
void listClear(Node*& headPtr) {
    while (headPtr) {
        Node* next = headPtr->next;
        delete headPtr;
        headPtr = next;
    }
}

// listBuild: constructs a list from a vector of data items. Note that
// you can use a curly-braced sequence.
// This may be useful for setting up test cases. Feel free to use it
// or not as you like.
// Example of using would be:
//    Node* myList = listBuild({1, 4, 9, 16}); // builds a list of: 1 4 9 16
Node* listBuild(const vector<int>& vals) {
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
        listAddHead(result, vals[index-1]);
    }
    return result;
}

void splice(Node* add_this, Node* location){
    //keep track of the old next
    Node* old_next = location -> next;
    location -> next = add_this;
    Node* curr_node = add_this;
    //traverse through the node until you reach the last node
    while (curr_node -> next){
        curr_node = curr_node -> next;
    }
    //set the current node's next to the old one to connect both lists
    curr_node -> next = old_next;
    //add_this -> next = old_next;
}

Node* is_sublist(Node* query, Node* original_list){
    Node* o_curr;
    Node* q_curr;
    bool matching = false;
    if (!query){
        return nullptr;
    }
    while(original_list){
        //if the data matches, check the rest along the lists
        if (original_list -> data == query -> data){
            q_curr = query -> next;
            o_curr = original_list -> next;
            matching = true;
            //check while q_curr and o_curr are not null + still are matching
            while(q_curr && o_curr && matching){
                //if they begin to not match and the query is not null, sublist not found
                // thus break out of loop
                if (q_curr -> data != o_curr -> data){
                    matching = false;
                }
                //if your query still has more nodes but you are at end of original list,
                // break out of loop because sublist not found
                else if ((q_curr -> next) && !(o_curr -> next)){
                    matching = false;
                }
                //keep on going along the original_list + query
                q_curr = q_curr -> next;
                o_curr = o_curr -> next;
            }
            //if at the end of the while loop it still matches, return the original starting position
            if (matching){
                return original_list;
            }
        }
        //go along the original list
        original_list = original_list -> next;
    }
    //it is not a sublist
    return nullptr;
}

Node* shared_brute(Node* l1, Node* l2){
    Node* l2_curr ;
    if (!l1 || !l2){
        return nullptr;
    }
    while(l1){
        l2_curr = l2;
        while(l2_curr){
            if(l1 == l2_curr){
                return l1;
            }
            l2_curr = l2_curr -> next;
        }
        l1 = l1->next;
    }
    return nullptr;
}

Node* shared_set(Node* l1, Node* l2){
    unordered_set<Node*> node_ptrs;
    while(l1){
        node_ptrs.insert(l1);
        l1 = l1 ->next;
    }
    while(l2){
        if (node_ptrs.find(l2) != node_ptrs.end()){
            return l2;
        }
        l2 = l2 -> next;
    }
    return nullptr;
}

size_t length_list(Node* l1){
    size_t counter = 0;
    while(l1){
        ++counter;
        l1 = l1 -> next;
    }
    return counter;
}

Node* shared_const_space(Node* l1, Node* l2){
    size_t l1_size = length_list(l1);
    size_t l2_size = length_list(l2);
    while(l1_size > l2_size){
        l1 = l1 -> next;
        --l1_size;
    }
    while (l2_size > l1_size){
        l2 = l2 -> next;
        --l2_size;
    }
    while(l1 != l2){
        l1 = l1 -> next;
        l2 = l2 -> next;
    }
    return l1; //if they dont meet, then l1 = nullptr;
}

void print_list(Node* curr_list){
    while (curr_list != nullptr){
        cout << curr_list -> data << " ";
        curr_list = curr_list -> next;
    }
    cout << endl;
    //cout << "wow";
}

int main() {
    Node* original = listBuild({5,7,9,1});
    cout << "original: ";
    print_list(original);
    Node* add_this = listBuild({6,3,2});
    cout << "add this: ";
    print_list(add_this);
    
    cout << "============================" << endl;
    cout << "begin this splice at 7:" << endl;
    splice(add_this, original -> next);
    cout << "should return: 5 7 6 3 2 9 1" << endl << endl;
    cout << "new: ";
    print_list(original);
    cout << "addded portion: ";
    print_list(add_this);
    
    
    cout << "============================" << endl;
    cout << "testing sublists: " << endl;
    Node* original_list = listBuild({1,2,3,2,3,2,4,5,6});
    cout << "ORIGINAL LIST: ";
    print_list(original_list);
    cout << endl;
    
    cout << "Attempt match: 1" << endl;
    cout << "should return 1 2 3 2 3 2 4 5 6" << endl;
    print_list(is_sublist(listBuild({1}), original_list));
    cout << "---" << endl;
    
    cout << "Attempt match: 3 9" << endl;
    cout << "should return nothing" << endl;
    print_list(is_sublist(listBuild({3,9}), original_list));
    cout << "---" << endl;
    
    cout << "Attempt match: 2 3" << endl;
    cout << "should return 2 3 2 3 2 4 5 6" << endl;
    print_list(is_sublist(listBuild({2,3}), original_list));
    cout << "---" << endl;
    
    cout << "Attempt match: 2 4 5 6" << endl;
    cout << "should return 2 4 5 6" << endl;
    print_list(is_sublist(listBuild({2,4,5,6}), original_list));
    cout << "---" << endl;
    
    cout << "Attempt match: 2 3 2 4" << endl;
    cout << "should return 2 3 2 4 5 6" << endl;
    print_list(is_sublist(listBuild({2,3,2,4}), original_list));
    cout << "---" << endl;
    
    cout << "Attempt match: 5 6 7" << endl;
    cout << "should return nothing" << endl;
    print_list(is_sublist(listBuild({5,6,7}), original_list));
    
    
    cout << "=======================" << endl << "TAKSE 3" << endl;
    Node* cool_list = listBuild({2,2,3});
    Node* cooler_list = listBuild({2,3});
    Node* even_more_cooler_list = listBuild({4,5});
    splice(even_more_cooler_list, cool_list -> next -> next);
    splice(even_more_cooler_list, cooler_list -> next);
    
    cout << "Cool list: ";
    print_list(cooler_list);
    cout << endl << "Cooler list: ";
    print_list(cooler_list);
    cout << endl << "Brute force: " << endl;
    print_list(shared_brute(cool_list, cooler_list));
    cout << endl << "Set force: " << endl;
    print_list(shared_set(cool_list, cooler_list));
    cout << endl << "Const_space linear runtime thing:" << endl;
    print_list(shared_const_space(cool_list, cooler_list));
    
}
