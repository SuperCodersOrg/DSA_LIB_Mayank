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

        T pop_front(){
            if(head==nullptr){
                throw std::out_of_range("List is empty");
            }
            T temp;
            Node* temp_ptr;
            if(head==tail){
                temp=head->data;
                temp_ptr=head;
                head=tail=nullptr;
            }else{
                temp=head->data;
                temp_ptr=head;
                head=head->next;
            }
            allocator.Destroy(temp_ptr);
            allocator.Deallocate(temp_ptr);
            length--;
            return temp;
        }

        T pop_back(){
            if(tail==nullptr){
                throw std::out_of_range("List is empty");
            }
            T temp_data;
            Node* temp_ptr=tail;
            if(tail==head){
                temp_data=tail->data;
                temp_ptr=tail;
                head=tail=nullptr;
            }else{
                temp_data=tail->data;
                Node* temp = head;
                while(temp->next->next!=nullptr){
                    temp=temp->next;
                }
                temp->next=nullptr;
                temp_ptr=tail;
                tail=temp;
            }
            allocator.Destroy(temp_ptr);
            allocator.Deallocate(temp_ptr);
            length--;
            return temp_data;
        }

        int size(){
            return length;
        }

        bool isEmpty(){
            return head==nullptr;
        }

        T& front(){
            if(head == nullptr) throw std::out_of_range("List is empty");
            return head->data;
        }

        const T& front() const {
            if(head == nullptr)
                throw std::out_of_range("List is empty");
            return head->data;
        }

        T& back() {
            if(tail == nullptr)
                throw std::out_of_range("List is empty");
            return tail->data;
        }

        const T& back() const {
            if(tail == nullptr)
                throw std::out_of_range("List is empty");
            return tail->data;
        }

        T& operator [](size_t index){
            if (index >= length) throw std::out_of_range("Index out of range");
            if(index==0){
                return head->data;
            }
            if(index==length-1){
                return tail->data;
            }
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
            if(index==0){
                return head->data;
            }
            if(index==length-1){
                return tail->data;
            }
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

        int find(const T& value){
            Node* temp=head;
            int i=0;
            while(temp!=nullptr){
                if(temp->data==value){
                    return i;
                }
                temp=temp->next;
                i++;
            }
            return -1;
        }

        void insert(size_t index,const T& value){
            if(index>length) throw std::out_of_range("Index out of range");
            if(index==0){
                push_front(value);
            }
            else if(index==length){
                push_back(value);
            }else{
                Node* temp=head;
                Node* newnode = allocator.Allocate();
                allocator.Construct(newnode,value);
                int i=0;
                while(i<index-1){
                    temp=temp->next;
                    i++;
                }
                newnode->next=temp->next;
                temp->next=newnode;
                length++;
            }
        }


        T remove(size_t index){
            if(index>=length) throw std::out_of_range("Index out of range");
            T temp_data;
            if(index==0){
              temp_data= pop_front();
            }
            else if(index==length-1){
               temp_data= pop_back();
            }
            else{
            Node* temp=head;
            Node* prev=nullptr;
            int i=0;
            while(i<index){
                prev=temp;
                temp=temp->next;
                i++;
            }
            prev->next=temp->next;
            temp_data=temp->data;
            allocator.Destroy(temp);
            allocator.Deallocate(temp);
            length--;
            }
            return temp_data;
        }


        void print(){
            Node* temp=head;
            while(temp!=nullptr){
                std::cout<<temp->data<<"->";
                temp=temp->next;
            }
        }

        void clear(){
            Node* temp = head;

            while (temp != nullptr){
                Node* next = temp->next;

                allocator.Destroy(temp);
                allocator.Deallocate(temp);

                temp = next;
            }

            head = nullptr;
            tail = nullptr;
            length = 0;
        }
        LinkedList(const LinkedList& other){
            head = nullptr;
            tail = nullptr;
            length = 0;

            Node* temp = other.head;

            while (temp != nullptr)
            {
                push_back(temp->data);
                temp = temp->next;
            }
        }

        LinkedList& operator=(const LinkedList& other){
            if(this == &other){
                return *this;
            }

            clear();

            Node* temp = other.head;

            while(temp != nullptr){
                push_back(temp->data);
                temp = temp->next;
            }

            return *this;
        }
        
        ~LinkedList(){
            clear();
        }
};