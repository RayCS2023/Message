//
//  main.cpp
//  project 4
//
//  Created by Raymond Chen on 2018-11-26.
//  Copyright © 2018 Raymond Chen. All rights reserved.
//

#include <iostream>
#include "Message.h"
#include "assert.h"
#ifndef MARMOSET_TESTING
int main();
#endif

#ifndef MARMOSET_TESTING
int main(){
    bool running = true;
    Message *message = new Message{};
    while (running){
        int input = 0;
        std::cin >> input;
        if(input >= 0){
            std::string frags = "";
            std::cin >> frags;
            message->insert(input, frags);
        }
        else if(input == -2){
            running = false;
        }
        else{
            message->print_message();
        }
    }
}
#endif

Node::Node(unsigned int id, std::string frag){
    identifier = id;
    fragment = frag;
    p_next = nullptr;
}

Node *Node::get_next(){
    return p_next;
}

std::string Node::get_fragment(){
    return fragment;
}

Message::Message(){
    head = nullptr;
}

void Message::insert(unsigned int id, std::string fragment){
    if(head == nullptr){
        head = new Node{id,fragment};
    }
    else if(id < head->identifier){
        Node * p_new = new Node{id,fragment};
        p_new->p_next = head;
        head = p_new;
    }
    else if(id > head->identifier){
        Node * p_new = new Node{id,fragment};
        Node * p_temp = head;
        while(p_new->identifier > p_temp->identifier){
            if(p_temp->p_next == nullptr){
                p_temp->p_next = p_new;
                break;
            }
            if(p_temp->p_next->identifier > p_new->identifier){
                p_new->p_next = p_temp->p_next;
                p_temp->p_next = p_new;
            }
            p_temp = p_temp->p_next;
        }
    }
    
}

void Message::print_message(){
    Node *p_node = head;
    int count = 0;
    if(head == nullptr){
        std::cout << "???";
    }
    while(p_node != nullptr){
        if(count!=p_node->identifier){
            std::cout << "... ";
            count++;
        }
        else{
            if(p_node->fragment == "EOT"){
                break;
            }
            std::cout << p_node->fragment << " ";
            if(p_node->p_next == nullptr  && p_node->fragment != "EOT"){
                std::cout << "???";
            }
            p_node = p_node->p_next;
            count++;
        }
    }
    std::cout << std::endl;
}

Message::~Message(){
    while(head != nullptr){
        Node * p_temp = head->p_next;
        delete head;
        head = p_temp;
    }
}

