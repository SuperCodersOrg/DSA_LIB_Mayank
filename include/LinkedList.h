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
            length=0;
            for(const T& value:init){
                push_back(value);
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

        int size(){
            return length;
        }

        bool isEmpty(){
            return head==nullptr;
        }

        T& front(){
            return head->data;
        }

        const T& front()const{
            return head->data;
        }

        T& back(){
            return tail->data;
        }

        const T& back()const{
            return tail->data;
        }

        T& operator [](size_t index){
            if (index >= length) throw std::out_of_range("Index out of range");
            Node* temp=head;
            size_t i=0;
            while(i<=index){
                if(i==index){
                    return temp->data;
                }
                i++;
                temp=temp->next;
            }

        }
        const T& operator [](size_t index)const {
            if (index >= length) throw std::out_of_range("Index out of range");
            Node* temp=head;
            size_t i=0;
            while(i<=index){
                if(i==index){
                    return temp->data;
                }
                i++;
                temp=temp->next;
            }

        }

        void print(){
            Node* temp=head;
            while(temp!=nullptr){
                std::cout<<temp->data<<"->";
                temp=temp->next;
            }
        }

};