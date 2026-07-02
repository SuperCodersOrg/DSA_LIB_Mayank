#pragma once

#include<stdexcept>
#include<iostream>
#include"Allocator.h"

template<typename T>
class LinkedList{
    private:
        class Node{
            public:
                T data;
                Node* next;
                Node(const T& value){
                    data=value; 
                    next=nullptr;
                }
        };
        MyAllocator<Node> allocator;
        Node* head;
        Node* tail;
        int length;
    public:
        LinkedList(){
            head=nullptr;
            tail=nullptr;
            length=0;
        }
        LinkedList(std::initializer_list<T> init){
            head=nullptr;
            tail=nullptr;
            for(const T& value:init){
                push_back(value);
                length++;
            }
        }
        void push_front(const T& value){
            Node* newnode = allocator.Allocate();
            allocator.Construct(newnode,value);
            if(head==nullptr){
                head=newnode;
                tail=newnode;
                length++;
            }else{
                newnode->next=head;
                head=newnode;
                length++;
            }
        }

        void push_back(const T& value){
            Node* newnode = allocator.Allocate();
            allocator.Construct(newnode,value);
            if(head==nullptr && tail==nullptr){
                head=newnode;
                tail=newnode;
            }
            else if(head==tail){
                tail->next=newnode;
                tail=newnode;
            }else{
                tail->next=newnode;
                tail=newnode;
            }
            length++;
        }

        void print(){
            Node* temp=head;
            while(temp!=nullptr){
                std::cout<<temp->data<<"->";
                temp=temp->next;
            }
        }

};