#ifndef MYTEST_CPP
#define MYTEST_CPP

#include <iostream>
#include <random>
#include <stack>
#include <queue>
#include <time.h>


#include "../container/mappable.hpp"

#include "test.hpp"

using namespace std;



int MIN_SIZE = 0;
int MAX_SIZE = 100;
int MIN_NUM = INT16_MIN;
int MAX_NUM = INT16_MAX;
int ITERAZIONI = 1;

bool output;

default_random_engine gen(random_device{}());
uniform_int_distribution<int> genSize(MIN_SIZE,MAX_SIZE);
uniform_int_distribution<int> genNum(MIN_NUM,MAX_NUM);

/*


    L'UTILIZZO DELLE FUNZIONI E' AL TERMINE DELLA LORO DEFINIZIONE


*/

bool TestAssVector() {
    lasd::Vector<int> s1(genSize(gen));
    for(ulong i=0; i<s1.Size(); i++) s1[i]=genNum(gen);
    lasd::Vector<int> s2(genSize(gen));
    for(ulong i=0; i<s2.Size(); i++) s2[i]=genNum(gen);
    s1=s2;
    return (s1==s2);
}

bool TestAssList() {
    int temp_size1 = genSize(gen);
    int temp_size2 = genSize(gen);
    lasd::List<int> s1;
    for(int i=0; i<temp_size1; i++) s1.Insert(genNum(gen));
    lasd::List<int> s2;
    for(int i=0; i<temp_size2; i++) s2.Insert(genNum(gen));
    s1=s2;
    return (s1==s2);
}

bool TestAssStackLst() {
    int temp_size1 = genSize(gen);
    int temp_size2 = genSize(gen);
    lasd::StackLst<int> s1;
    for(int i=0; i<temp_size1; i++) s1.Push(genNum(gen));
    lasd::StackLst<int> s2;
    for(int i=0; i<temp_size2; i++) s2.Push(genNum(gen));
    s1=s2;
    return (s1==s2);
}

bool TestAssStackVec() {
    int temp_size1 = genSize(gen);
    int temp_size2 = genSize(gen);
    lasd::StackVec<int> s1;
    for(int i=0; i<temp_size1; i++) s1.Push(genNum(gen));
    lasd::StackVec<int> s2;
    for(int i=0; i<temp_size2; i++) s2.Push(genNum(gen));
    s1=s2;
    return (s1==s2);
}

bool TestAssQueueLst() {
    int temp_size1 = genSize(gen);
    int temp_size2 = genSize(gen);
    lasd::QueueLst<int> s1;
    for(int i=0; i<temp_size1; i++) s1.Enqueue(genNum(gen));
    lasd::QueueLst<int> s2;
    for(int i=0; i<temp_size2; i++) s2.Enqueue(genNum(gen));
    s1=s2;
    return (s1==s2);
}

bool TestAssQueueVec() {
    int temp_size1 = genSize(gen);
    int temp_size2 = genSize(gen);
    lasd::QueueVec<int> s1;
    for(int i=0; i<temp_size1; i++) s1.Enqueue(genNum(gen));
    lasd::QueueVec<int> s2;
    for(int i=0; i<temp_size2; i++) s2.Enqueue(genNum(gen));
    s1=s2;
    return (s1==s2);
}

bool TestEqualLinear(){
    bool correct=true;
    int temp_size = genSize(gen)+1;
    lasd::Vector<int> v(temp_size);
    lasd::List<int> l;
    for(int i=0; i<temp_size; i++){
        int temp_num = genNum(gen);
        v[i]=temp_num;
        l.InsertAtBack(temp_num);
    }
    correct&=(v.LinearContainer<int>::operator==(l));
    v[genSize(gen)%temp_size]=genNum(gen);
    correct&=(v.LinearContainer<int>::operator!=(l));
    v.Clear();
    l.Clear();
    correct&=(v.LinearContainer<int>::operator==(l));
    return correct;
}

bool TestEqualVector(){
    bool correct=true;
    int temp_size = genSize(gen)+1;
    lasd::Vector<int> v1(temp_size);
    lasd::Vector<int> v2(temp_size);
    for(int i=0; i<temp_size; i++) v2[i]=v1[i]=genNum(gen);
    correct&=(v1==v2);
    v1[genSize(gen)%temp_size]=genNum(gen);
    correct&=!(v1==v2);
    v1.Clear();
    correct&=(v1!=v2);
    v2.Clear();
    correct&=(v1==v2);
    return correct;
}

bool TestEqualList(){
    bool correct=true;
    int temp_size = genSize(gen)+1;
    lasd::List<int> l1;
    lasd::List<int> l2;
    for(int i=0; i<temp_size; i++){
        int temp_num = genNum(gen);
        l1.InsertAtFront(temp_num);
        l2.InsertAtFront(temp_num);
    } 
    correct&=(l1==l2);
    l1[genSize(gen)%temp_size]=genNum(gen);
    correct&=(l1!=l2);
    l1.Clear();
    correct&=(l1!=l2);
    l2.Clear();
    correct&=(l1==l2);
    return correct;
}

bool TestEqualStackVec(){
    bool correct=true;
    int temp_size = genSize(gen)+1;
    lasd::StackVec<int> s1;
    lasd::StackVec<int> s2;
    for(int i=0; i<temp_size; i++){
        int temp_num = genNum(gen);
        s1.Push(temp_num);
        s2.Push(temp_num);
    } 
    correct&=(s1==s2);
    s2.Clear();
    correct&=(s1!=s2);
    s1.Clear();
    correct&=(s1==s2);
    return correct;
}

bool TestEqualStackLst(){
    bool correct=true;
    int temp_size = genSize(gen)+1;
    lasd::StackLst<int> s1;
    lasd::StackLst<int> s2;
    for(int i=0; i<temp_size; i++) {
        int temp_num = genNum(gen);
        s1.Push(temp_num);
        s2.Push(temp_num);
    } 
    correct&=(s1==s2);
    s2.Pop();
    s2.Push(genNum(gen));
    correct&=(s1!=s2);
    s1.Clear();
    s2.Clear();
    correct&=(s1==s2);
    return correct;
}

bool TestEqualQueueVec(){
    bool correct=true;
    int temp_size = genSize(gen)+1;
    lasd::QueueVec<int> s1;
    lasd::QueueVec<int> s2;
    for(int i=0; i<temp_size; i++) {
        int temp_num = genNum(gen);
        s1.Enqueue(temp_num);
        s2.Enqueue(temp_num);
    } 
    correct&=(s1==s2);
    s2.Dequeue();
    s2.Enqueue(genNum(gen));
    correct&=(s1!=s2);
    s1.Clear();
    s2.Clear();
    correct&=(s1==s2);
    return correct;
}

bool TestEqualQueueLst(){
    bool correct=true;
    int temp_size = genSize(gen)+1;
    lasd::QueueLst<int> s1;
    lasd::QueueLst<int> s2;
    for(int i=0; i<temp_size; i++) {
        int temp_num = genNum(gen);
        s1.Enqueue(temp_num);
        s2.Enqueue(temp_num);
    } 
    correct&=(s1==s2);
    s2.Dequeue();
    s2.Enqueue(genNum(gen));
    correct&=(s1!=s2);
    s1.Clear();
    s2.Clear();
    correct&=(s1==s2);
    return correct;
}

bool CCVec(){
    if(output) cout<<"\n**********TEST CCVec**********\n";
    bool correct=true;
    lasd::Vector<int> s1(genSize(gen));
    for(ulong i=0; i<s1.Size(); i++) s1[i]=genNum(gen);
    lasd::Vector<int> s2(s1);
    if(output){
        cout<<"Vettore1: ";
        for(ulong i{0}; i<s1.Size(); i++) cout<<s1[i]<<"\t";
        cout<<endl;
        cout<<"Vettore2: ";
        for(ulong i{0}; i<s2.Size(); i++) cout<<s2[i]<<"\t";
        cout<<endl;
    }
    correct&=(s1==s2);
    s1.Clear();
    s2.Clear();
    correct&=(s1==s2);
    return correct;
}

bool MCVec(){
    if(output) cout<<"\n**********TEST MCVec**********\n";
    bool correct=true;
    lasd::Vector<int> s1(genSize(gen));
    for(ulong i=0; i<s1.Size(); i++) s1[i]=genNum(gen);
    lasd::Vector<int> s3(s1);
    lasd::Vector<int> s2(move(s1));
    if(output){
        cout<<"Vettore1: ";
        for(ulong i{0}; i<s1.Size(); i++) cout<<s1[i]<<"\t";
        cout<<endl;
        cout<<"Vettore2: ";
        for(ulong i{0}; i<s2.Size(); i++) cout<<s2[i]<<"\t";
        cout<<endl;
    }
    correct&=s1.Empty();
    correct&=(s2==s3);
    s1.Clear();
    s2.Clear();
    correct&=(s1==s2);
    return correct;
}

bool TestaLista(lasd::List<int>& s){
    ulong init_size = s.Size();
    int temp_size = genSize(gen);
    for(int i{0}; i<temp_size; i++){ s.InsertAtFront(genNum(gen)); }
    while(s.Size()>0) { s.RemoveFromFront(); temp_size--; }
    if(temp_size+init_size!=0) {
        cout<<"\ntemp: "<<temp_size<<"\tinit: "<<init_size;
        cout<<"\nVettore svuotato NON correttamente\n\n";
    }
    return temp_size+init_size==0;
}

bool TestaLista(lasd::List<int>&& s){
    ulong init_size = s.Size();
    int temp_size = genSize(gen);
    for(int i{0}; i<temp_size; i++){ s.InsertAtFront(genNum(gen)); }
    while(s.Size()>0) { s.RemoveFromFront(); temp_size--; }
    if(temp_size+init_size!=0) {
        cout<<"\ntemp: "<<temp_size<<"\tinit: "<<init_size;
        cout<<"\nVettore svuotato NON correttamente\n\n";
    }
    return temp_size+init_size==0;
}

bool CCLst(){
    if(output) cout<<"\n**********TEST CCLst**********\n";
    bool correct=true;
    lasd::List<int> s1;
    int temp_size = genSize(gen);
    for(int i=0; i<temp_size; i++) s1.InsertAtFront(genNum(gen)); 
    lasd::List<int> s2(s1);
    if(output){
        cout<<"Lista1: ";
        for(ulong i{0}; i<s1.Size(); i++) cout<<s1[i]<<"\t";
        cout<<endl;
        cout<<"Lista2: ";
        for(ulong i{0}; i<s2.Size(); i++) cout<<s2[i]<<"\t";
        cout<<endl;
    }
    correct&=(s1==s2);
    correct&=TestaLista(s2);
    correct&=TestaLista(s1);
    s1.Clear();
    s2.Clear();
    correct&=(s1==s2);
    return correct;
}

bool MCLst(){
    if(output) cout<<"\n**********TEST MCLst**********\n";
    bool correct=true;
    lasd::List<int> s1;
    int temp_size = genSize(gen);
    for(int i=0; i<temp_size; i++) s1.InsertAtFront(genNum(gen)); 
    lasd::List<int> s3(s1);
    lasd::List<int> s2(move(s1));
    correct&=(s1.Empty());
    correct&=(s3==s2);
    if(output){
        cout<<"Lista1: ";
        for(ulong i{0}; i<s1.Size(); i++) cout<<s1[i]<<"\t";
        cout<<endl;
        cout<<"Lista2: ";
        for(ulong i{0}; i<s2.Size(); i++) cout<<s2[i]<<"\t";
        cout<<endl;
    }
    correct&=TestaLista(move(s2));
    s1.Clear();
    s2.Clear();
    correct&=(s1==s2);
    return correct;
}

bool CCStackVec(){
    if(output) cout<<"\n**********TEST CCStackVec**********\n";
    bool correct=true;
    lasd::StackVec<int> s1;
    int temp_size = genSize(gen);
    for(int i=0; i<temp_size; i++) s1.Push(genNum(gen));
    lasd::StackVec<int> s2(s1);
    correct&=(s1==s2);
    if(output){
        cout<<"StackVec1: ";
        while(s1.Size()>0) cout<<s1.TopNPop()<<"\t";
        cout<<endl;
        cout<<"StackVec2: ";
        while(s2.Size()>0)  cout<<s2.TopNPop()<<"\t";
        cout<<endl;
    }
    correct&=(s1==s2);
    s1.Clear();
    s2.Clear();
    correct&=(s1==s2);
    return correct;
}

bool MCStackVec(){
    if(output) cout<<"\n**********TEST MCStackVec**********\n";
    bool correct=true;
    lasd::StackVec<int> s1;
    int temp_size = genSize(gen);
    for(int i=0; i<temp_size; i++) s1.Push(genNum(gen));
    lasd::StackVec<int> s3(s1);
    lasd::StackVec<int> s2(move(s1));
    correct&=(s3==s2);
    correct&=(s1.Empty());
    if(output){
        cout<<"StackVec1: ";
        while(s1.Size()>0) cout<<s1.TopNPop()<<"\t";
        cout<<endl;
        cout<<"StackVec2: ";
        while(s2.Size()>0)  cout<<s2.TopNPop()<<"\t";
        cout<<endl;
    }
    s1.Clear();
    s2.Clear();
    correct&=(s1==s2);
    return correct;
}

bool CCStackLst(){
    if(output) cout<<"\n**********TEST CCStackLst**********\n";
    bool correct=true;
    lasd::StackLst<int> s1;
    int temp_size = genSize(gen);
    for(int i=0; i<temp_size; i++) s1.Push(genNum(gen));
    lasd::StackLst<int> s2(s1);
    correct&=(s1==s2);
    if(output){
        cout<<"StackLst1: ";
        while(s1.Size()>0) cout<<s1.TopNPop()<<"\t";
        cout<<endl;
        cout<<"StackLst2: ";
        while(s2.Size()>0)  cout<<s2.TopNPop()<<"\t";
        cout<<endl;
    }
    s1.Clear();
    s2.Clear();
    correct&=(s1==s2);
    return correct;
}

bool MCStackLst(){
    if(output) cout<<"\n**********TEST MCStackLst**********\n";
    bool correct=true;
    lasd::StackLst<int> s1;
    int temp_size = genSize(gen);
    for(int i=0; i<temp_size; i++) s1.Push(genNum(gen));
    lasd::StackLst<int> s3(s1);
    lasd::StackLst<int> s2(move(s1));
    correct&=(s1.Empty());
    correct&=(s2==s3);
    if(output){
        cout<<"StackLst: ";
        while(s1.Size()>0) cout<<s1.TopNPop()<<"\t";
        cout<<endl;
        cout<<"StackLst: ";
        while(s2.Size()>0)  cout<<s2.TopNPop()<<"\t";
        cout<<endl;
    }
    s1.Clear();
    s2.Clear();
    correct&=(s1==s2);
    return correct;
}

bool CCQueueLst(){
    if(output) cout<<"\n**********TEST CCQueueLst**********\n";
    bool correct=true;
    lasd::QueueLst<int> s1;
    int temp_size = genSize(gen);
    for(int i=0; i<temp_size; i++) s1.Enqueue(genNum(gen));
    lasd::QueueLst<int> s2(s1);
    correct&=(s1==s2);
    if(output){
        cout<<"QueueLst1: ";
        while(s1.Size()>0) cout<<s1.HeadNDequeue()<<"\t";
        cout<<endl;
        cout<<"QueueLst2: ";
        while(s2.Size()>0)  cout<<s2.HeadNDequeue()<<"\t";
        cout<<endl;
    }
    s1.Clear();
    s2.Clear();
    correct&=(s1==s2);
    return correct;
}

bool MCQueueLst(){
    if(output) cout<<"\n**********TEST MCQueueLst**********\n";
    bool correct=true;
    lasd::QueueLst<int> s1;
    int temp_size = genSize(gen);
    for(int i=0; i<temp_size; i++) s1.Enqueue(genNum(gen));
    lasd::QueueLst<int> s3(s1);
    lasd::QueueLst<int> s2(move(s1));
    correct&=(s2==s3);
    correct&=(s1.Empty());
    if(output){
        cout<<"QueueLst1: ";
        while(s1.Size()>0) cout<<s1.HeadNDequeue()<<"\t";
        cout<<endl;
        cout<<"QueueLst2: ";
        while(s2.Size()>0)  cout<<s2.HeadNDequeue()<<"\t";
        cout<<endl;
    }
    s1.Clear();
    s2.Clear();
    correct&=(s1==s2);
    return correct;
}

bool CCQueueVec(){
    if(output) cout<<"\n**********TEST CCQueueVec**********\n";
    bool correct=true;
    lasd::QueueLst<int> s1;
    int temp_size = genSize(gen);
    for(int i=0; i<temp_size; i++) s1.Enqueue(genNum(gen));
    lasd::QueueLst<int> s2(s1);
    correct&=(s1==s2);
    if(output){
        cout<<"QueueLst1: ";
        while(s1.Size()>0) cout<<s1.HeadNDequeue()<<"\t";
        cout<<endl;
        cout<<"QueueLst2: ";
        while(s2.Size()>0)  cout<<s2.HeadNDequeue()<<"\t";
        cout<<endl;
    }
    s1.Clear();
    s2.Clear();
    correct&=(s1==s2);
    return correct;
}

bool MCQueueVec(){
    if(output) cout<<"\n**********TEST MCQueueVec**********\n";
    bool correct=true;
    lasd::QueueVec<int> s1;
    int temp_size = genSize(gen);
    for(int i=0; i<temp_size; i++) s1.Enqueue(genNum(gen));
    lasd::QueueVec<int> s3(s1);
    lasd::QueueVec<int> s2(move(s1));
    correct&=(s2==s3);
    correct&=(s1.Empty());
    if(output){
        cout<<"QueueLst1: ";
        while(s1.Size()>0) cout<<s1.HeadNDequeue()<<"\t";
        cout<<endl;
        cout<<"QueueLst2: ";
        while(s2.Size()>0)  cout<<s2.HeadNDequeue()<<"\t";
        cout<<endl;
    } 
    s1.Clear();
    correct&=(s1.Empty());
    s2.Clear();
    correct&=(s2.Empty());
    correct&=(s1==s2);
    return correct;
}

bool TestSCVecFromList() {
    if(output) cout<<"\n**********TEST SCVecFromList**********\n";
    bool correct = true;
    lasd::List<int> l;
    int temp_size = genSize(gen);
    for(int i=0; i<temp_size; i++) l.InsertAtFront(genNum(gen));
    lasd::Vector<int> v(l);
    for(ulong i{0}; i<v.Size(); i++) correct&=(v[i]==l[i]);
    return correct;
}

bool TestSCListFromVector(){
    if(output) cout<<"\n**********TEST SCListFromVector**********\n";
    bool correct = true;
    lasd::Vector<int> v(genSize(gen));
    for(ulong i=0; i<v.Size(); i++) v[i] = genNum(gen);
    lasd::List<int> l(v);
    for(ulong i{0}; i<v.Size(); i++) correct&=(v[i]==l[i]);
    return correct;
}

bool TestSCStackVecFromList() {
    if(output) cout<<"\n**********TEST SCStackVecFromList**********\n";
    bool correct = true;
    lasd::List<int> l;
    int temp_size = genSize(gen);
    for(int i=0; i<temp_size; i++) l.InsertAtFront(genNum(gen));
    lasd::StackVec<int> v(l);
    for(long i = l.Size()-1; i>=0; i--) correct&=(v.TopNPop()==l[i]);
    return correct;
}

bool TestSCStackVecFromVector(){
    if(output) cout<<"\n**********TEST SCStackVecFromVector**********\n";
    bool correct = true;
    lasd::Vector<int> v(genSize(gen));
    for(ulong i=0; i<v.Size(); i++) v[i] = genNum(gen);
    lasd::StackVec<int> l(v);
    for(long i = v.Size()-1; i>=0; i--) correct&=(l.TopNPop()==v[i]);
    return correct;
}

bool TestSCStackLstFromList() {
    if(output) cout<<"\n**********TEST SCStackLstFromList**********\n";
    bool correct = true;
    lasd::List<int> l;
    int temp_size = genSize(gen);
    for(int i=0; i<temp_size; i++) l.InsertAtFront(genNum(gen));
    lasd::StackLst<int> v(l);
    for(ulong i{0}; i<v.Size(); i++) correct&=(v.TopNPop()==l[i]);
    return correct;
}

bool TestSCStackLstFromVector(){
    if(output) cout<<"\n**********TEST SCStackLstFromVector**********\n";
    bool correct = true;
    lasd::Vector<int> v(genSize(gen));
    for(ulong i=0; i<v.Size(); i++) v[i] = genNum(gen);
    lasd::StackLst<int> l(v);
    for(ulong i{0}; i<v.Size(); i++) correct&=(l.TopNPop()==v[i]);
    return correct;
}

bool TestSCQueueVecFromList() {
    if(output) cout<<"\n**********TEST SCQueueVecFromList**********\n";
    bool correct = true;
    lasd::List<int> l;
    int temp_size = genSize(gen);
    for(int i=0; i<temp_size; i++) l.InsertAtFront(genNum(gen));
    lasd::QueueVec<int> v(l);
    for(ulong i{0}; i<v.Size(); i++) correct&=(v.HeadNDequeue()==l[i]);
    return correct;
}

bool TestSCQueueVecFromVector(){
    if(output) cout<<"\n**********TEST SCQueueVecFromVector**********\n";
    bool correct = true;
    lasd::Vector<int> v(genSize(gen));
    for(ulong i=0; i<v.Size(); i++) v[i] = genNum(gen);
    lasd::QueueVec<int> l(v);
    for(ulong i{0}; i<v.Size(); i++) correct&=(l.HeadNDequeue()==v[i]);
    return correct;
}

bool TestSCQueueLstFromList() {
    if(output) cout<<"\n**********TEST SCQueueLstFromList**********\n";
    bool correct = true;
    lasd::List<int> l;
    int temp_size = genSize(gen);
    for(int i=0; i<temp_size; i++) l.InsertAtFront(genNum(gen));
    lasd::QueueLst<int> v(l);
    for(ulong i{0}; i<v.Size(); i++) correct&=(v.HeadNDequeue()==l[i]);
    return correct;
}

bool TestSCQueueLstFromVector(){
    if(output) cout<<"\n**********TEST SCQueueLstFromVector**********\n";
    bool correct = true;
    lasd::Vector<int> v(genSize(gen));
    for(ulong i=0; i<v.Size(); i++) v[i] = genNum(gen);
    lasd::QueueLst<int> l(v);
    for(ulong i{0}; i<v.Size(); i++) correct&=(l.HeadNDequeue()==v[i]);
    return correct;
}

bool TestMSCVecFromList() {
    if(output) cout<<"\n**********TEST MSCVecFromList**********\n";
    bool correct = true;
    lasd::List<int> l;
    int temp_size = genSize(gen);
    for(int i=0; i<temp_size; i++) l.InsertAtFront(genNum(gen));
    lasd::Vector<int> v1(l);
    lasd::Vector<int> v2(move(l));
    for(ulong i{0}; i<v1.Size(); i++) correct&=(v1[i]==v2[i]);
    return correct;
}

bool TestMSCListFromVector(){
    if(output) cout<<"\n**********TEST MSCListFromVector**********\n";
    bool correct = true;
    lasd::Vector<int> v(genSize(gen));
    for(ulong i=0; i<v.Size(); i++) v[i] = genNum(gen);
    lasd::List<int> l1(v);
    lasd::List<int> l2(move(v));
    for(ulong i{0}; i<l1.Size(); i++) correct&=(l1[i]==l2[i]);
    return correct;
}

bool TestMSCStackVecFromList() {
    if(output) cout<<"\n**********TEST MSCStackVecFromList**********\n";
    bool correct = true;
    lasd::List<int> l;
    int temp_size = genSize(gen);
    for(int i=0; i<temp_size; i++) l.InsertAtFront(genNum(gen));
    lasd::StackVec<int> v1(l);
    lasd::StackVec<int> v2(move(l));
    while(v2.Size()>0) correct&=(v1.TopNPop()==v2.TopNPop());
    return correct;
}

bool TestMSCStackVecFromVector(){
    if(output) cout<<"\n**********TEST MSCStackVecFromVector**********\n";
    bool correct = true;
    lasd::Vector<int> v(genSize(gen));
    for(ulong i=0; i<v.Size(); i++) v[i] = genNum(gen);
    lasd::StackVec<int> l1(v);
    lasd::StackVec<int> l2(move(v));
    while(l2.Size()>0) correct&=(l1.TopNPop()==l2.TopNPop());
    return correct;
}

bool TestMSCStackLstFromList() {
    if(output) cout<<"\n**********TEST MSCStackLstFromList**********\n";
    bool correct = true;
    lasd::List<int> l;
    int temp_size = genSize(gen);
    for(int i=0; i<temp_size; i++) l.InsertAtFront(genNum(gen));
    lasd::StackVec<int> v1(l);
    lasd::StackVec<int> v2(move(l));
    while(v2.Size()>0) correct&=(v1.TopNPop()==v2.TopNPop());
    return correct;
}

bool TestMSCStackLstFromVector(){
    if(output) cout<<"\n**********TEST MSCStackLstFromVector**********\n";
    bool correct = true;
    lasd::Vector<int> v(genSize(gen));
    for(ulong i=0; i<v.Size(); i++) v[i] = genNum(gen);
    lasd::StackLst<int> l1(v);
    lasd::StackLst<int> l2(move(v));
    while(l2.Size()>0) correct&=(l1.TopNPop()==l2.TopNPop());
    return correct;
}

bool TestMSCQueueVecFromList() {
    if(output) cout<<"\n**********TEST MSCQueueVecFromList**********\n";
    bool correct = true;
    lasd::List<int> l;
    int temp_size = genSize(gen);
    for(int i=0; i<temp_size; i++) l.InsertAtFront(genNum(gen));
    lasd::QueueVec<int> v1(l);
    lasd::QueueVec<int> v2(move(l));
    while(v2.Size()>0) correct&=(v1.HeadNDequeue()==v2.HeadNDequeue());
    return correct;
}

bool TestMSCQueueVecFromVector(){
    if(output) cout<<"\n**********TEST MSCQueueVecFromVector**********\n";
    bool correct = true;
    lasd::Vector<int> v(genSize(gen));
    for(ulong i=0; i<v.Size(); i++) v[i] = genNum(gen);
    lasd::QueueVec<int> l1(v);
    lasd::QueueVec<int> l2(move(v));
    while(l2.Size()>0) correct&=(l1.HeadNDequeue()==l2.HeadNDequeue());
    return correct;
}

bool TestMSCQueueLstFromList() {
    if(output) cout<<"\n**********TEST MSCQueueLstFromList**********\n";
    bool correct = true;
    lasd::List<int> l;
    int temp_size = genSize(gen);
    for(int i=0; i<temp_size; i++) l.InsertAtFront(genNum(gen));
    lasd::QueueVec<int> v1(l);
    lasd::QueueVec<int> v2(move(l));
    while(v2.Size()>0) correct&=(v1.HeadNDequeue()==v2.HeadNDequeue());
    return correct;
}

bool TestMSCQueueLstFromVector(){
    if(output) cout<<"\n**********TEST MSCQueueLstFromVector**********\n";
    bool correct = true;
    lasd::Vector<int> v(genSize(gen));
    for(ulong i=0; i<v.Size(); i++) v[i] = genNum(gen);
    lasd::QueueLst<int> l1(v);
    lasd::QueueLst<int> l2(move(v));
    while(l2.Size()>0) correct&=(l1.HeadNDequeue()==l2.HeadNDequeue());
    return correct;
}

bool TestStackVSSTD(){
    if(output) cout<<"\n**********TEST StackVSSTD**********\n";
    bool correct = true;
    int temp_size = genSize(gen);
    std::stack<int> stdStack;
    lasd::StackVec<int> lasdStackVec;
    lasd::StackLst<int> lasdStackLst;
    for(int i{0}; i<temp_size; i++){
        int temp_num = genNum(gen);
        stdStack.push(temp_num);
        lasdStackVec.Push(temp_num);
        lasdStackLst.Push(temp_num);
    }
    correct&=((stdStack.size()==lasdStackLst.Size()) && (stdStack.size()==lasdStackVec.Size()));
    if(output) cout<<"STDSize: "<<stdStack.size()<<"\tlasdVecSize: "<<lasdStackVec.Size()<<"\tlasdLst: "<<lasdStackLst.Size()<<endl;
    for(int i{0}; i<temp_size; i++){
        if(output) cout<<"\n"<<i<<"\tSTD: "<<stdStack.top()<<"\tlasdVec: "<<lasdStackVec.Top()<<"\tlasdLst: "<<lasdStackLst.Top();
        correct&=((stdStack.top()==lasdStackLst.Top()) && (stdStack.top()==lasdStackVec.Top()));
        stdStack.pop();
        lasdStackVec.Pop();
        lasdStackLst.Pop();
    }
    return correct;
}

bool TestQueueVSSTD(){
    if(output) cout<<"\n**********TEST QueueVSSTD**********\n";
    bool correct = true;
    int temp_size = genSize(gen);
    std::queue<int> stdQueue;
    lasd::QueueVec<int> lasdQueueVec;
    lasd::QueueLst<int> lasdQueueLst;
    for(int i{0}; i<temp_size; i++){
        int temp_num = genNum(gen);
        stdQueue.push(temp_num);
        lasdQueueVec.Enqueue(temp_num);
        lasdQueueLst.Enqueue(temp_num);
    }
    correct&=((stdQueue.size()==lasdQueueLst.Size()) && (stdQueue.size()==lasdQueueVec.Size()));
    if(output) cout<<"STDSize: "<<stdQueue.size()<<"\tlasdVecSize: "<<lasdQueueVec.Size()<<"\tlasdLst: "<<lasdQueueLst.Size()<<endl;
    for(int i{0}; i<temp_size; i++){
        if(output) cout<<"\n"<<i<<"\tSTD: "<<stdQueue.front()<<"\tlasdVec: "<<lasdQueueVec.Head()<<"\tlasdLst: "<<lasdQueueLst.Head();
        correct&=((stdQueue.front()==lasdQueueLst.Head()) && (stdQueue.front()==lasdQueueVec.Head()));
        stdQueue.pop();
        lasdQueueVec.Dequeue();
        lasdQueueLst.Dequeue();
    }
    return correct;
}

bool TestSortVec(){
    if(output) cout<<"\n**********TEST SortVec**********\n";
    bool correct = true;
    lasd::Vector<int> v(genSize(gen));
    for(ulong i{0}; i<v.Size(); i++) v[i]=genNum(gen);
    if(output){
        cout<<"\nVettore non ordinato: ";
        for(ulong i{0}; i<v.Size(); i++) cout<<v[i]<<"\t";
        cout<<endl;
    }
    v.Sort();
    if(output){
        cout<<"\nVettore ordinato: ";
        for(ulong i{0}; i<v.Size(); i++) cout<<v[i]<<"\t";
        cout<<endl;
    }
    for(ulong i{1}; i<v.Size();i++) correct&=(v[i]>=v[i-1]);
    return correct;
}

bool davtest_ex1(){

    MIN_SIZE = 0;
    MAX_SIZE = 100;
    MIN_NUM = INT16_MIN;
    MAX_NUM = INT16_MAX;

    cout<<"\n\n*********** CONFIGURAZIONE DEI TEST: ***********"<<endl;
    cout<<"Necessiti degli output di debug?"<<endl;
    cout<<"1. Voglio visualizzare gli output di debug. (La dimensione delle strutture sara' ridotta)."<<endl;
    cout<<"2. No, voglio proseguire senza visualizzare gli output di debug."<<endl;
    cout<<"Inserisci l'opzione: ";
    int choose = -1;
    while(choose!=1 && choose!=2) cin>>choose;
    output = (choose==1);
    cout<<"\nChe tipo di test vuoi eseguire?"<<endl;
    cout<<"1. Test su casi limite (La dimensione massima delle strutture sara' impostata ad 1 in modo da forzare interazioni tra strutture vuote)"<<endl;
    cout<<"2. Test generale (L'esecuzione puo' apparire rallentata)"<<endl;
    cout<<"Inserisci l'opzione: ";
    choose = -1;
    while(choose!=1 && choose!=2) cin>>choose;
    if(choose==1){
        MAX_SIZE = 1;
    }else{
        MAX_SIZE = (output) ? 20 : 100;
    }
    uniform_int_distribution<int> select_genSize(MIN_SIZE,MAX_SIZE);
    genSize = select_genSize;
    cout<<"\nL'output sara' sospeso per velocizzare l'esecuzione se i test devono essere ripetuti piu' di 50 volte.";
    cout<<"\nInserisci il numero di iterazioni del test (consigliato 50): ";
    choose = -1;
    while(choose<0) cin>>choose;

    ITERAZIONI = choose;
    if(ITERAZIONI>50) output=false;
    bool total = true;

    while(ITERAZIONI>0){

        //VS STD
        bool StackVSSTD = false;
        bool QueueVSSTD = false;

        //Sort
        bool testSort = false;

        //Operator==
        bool testEqualLinear = false;
        bool testEqualVector = false;
        bool testEqualList = false;
        bool testEqualStackLst = false;
        bool testEqualStackVec = false;
        bool testEqualQueueLst = false;
        bool testEqualQueueVec = false;

        //Assignement
        bool testAssVector = false;
        bool testAssList = false;
        bool testAssStackLst = false;
        bool testAssStackVec = false;
        bool testAssQueueLst = false;
        bool testAssQueueVec = false;

        //Constructor
        bool testCCVec = false;
        bool testMCVec = false;
        bool testCCList = false;
        bool testMCList = false;
        bool testCCStackVec = false;
        bool testMCStackVec = false;
        bool testCCStackLst = false;
        bool testMCStackLst = false;
        bool testCCQueueLst = false;
        bool testMCQueueLst = false;
        bool testCCQueueVec = false;
        bool testMCQueueVec = false;

        //Specific constructor (Non mutable)
        bool testSCVecFromList = false;
        bool testSCListFromVector = false;
        bool testSCStackVecFromList = false;
        bool testSCStackVecFromVector = false;
        bool testSCStackLstFromList = false;
        bool testSCStackLstFromVector = false;
        bool testSCQueueVecFromList = false;
        bool testSCQueueVecFromVector = false;
        bool testSCQueueLstFromList = false;
        bool testSCQueueLstFromVector = false;

        //Specific constructor (Mutable)
        bool testMSCVecFromList = false;
        bool testMSCListFromVector = false;
        bool testMSCStackVecFromList = false;
        bool testMSCStackVecFromVector = false;
        bool testMSCStackLstFromList = false;
        bool testMSCStackLstFromVector = false;
        bool testMSCQueueVecFromList = false;
        bool testMSCQueueVecFromVector = false;
        bool testMSCQueueLstFromList = false;
        bool testMSCQueueLstFromVector = false;

        if(!output) cout<<"\nComparison with STD...";
        try { StackVSSTD = TestStackVSSTD(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { QueueVSSTD = TestQueueVSSTD(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }

        if(!output) cout<<"\nTesting sort...";
        try { testSort = TestSortVec(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }

        if(!output) cout<<"\nTesting comparison operators...";
        try { testEqualLinear = TestEqualLinear(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testEqualVector = TestEqualVector(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testEqualList = TestEqualList(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testEqualStackLst = TestEqualList(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testEqualStackVec = TestEqualStackVec(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testEqualQueueLst = TestEqualQueueLst(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testEqualQueueVec = TestEqualQueueVec(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }

        if(!output) cout<<"\nTesting assignment operators...";
        try { testAssVector = TestAssVector(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testAssList = TestAssList(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testAssStackLst = TestAssList(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testAssStackVec = TestAssStackVec(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testAssQueueLst = TestAssQueueLst(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testAssQueueVec = TestAssQueueVec(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }

        if(!output) cout<<"\nTesting constructors...";
        try { testCCVec = CCVec(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testCCList = CCLst(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testCCStackVec = CCStackVec(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testCCStackLst = CCStackLst(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testCCQueueLst = CCQueueLst(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testCCQueueVec = CCQueueVec(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        
        if(!output) cout<<"\nTesting move constructors...";
        try { testMCVec = MCVec(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testMCList = MCLst(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testMCStackVec = MCStackVec(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testMCStackLst = MCStackLst(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testMCQueueLst = MCQueueLst(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testMCQueueVec = MCQueueVec(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }

        if(!output) cout<<"\nTesting non-mutable specific constructors...";
        try { testSCVecFromList = TestSCVecFromList(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testSCListFromVector = TestSCListFromVector(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testSCStackVecFromList = TestSCStackVecFromList(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testSCStackVecFromVector = TestSCStackVecFromVector(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testSCStackLstFromList = TestSCStackLstFromList(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testSCStackLstFromVector = TestSCStackLstFromVector(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testSCQueueVecFromList = TestSCQueueVecFromList(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testSCQueueVecFromVector = TestSCQueueVecFromVector(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testSCQueueLstFromList = TestSCQueueLstFromList(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testSCQueueLstFromVector = TestSCQueueLstFromVector(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }

        if(!output) cout<<"\nTesting mutable specific constructors...";
        try { testMSCVecFromList = TestMSCVecFromList(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testMSCListFromVector = TestMSCListFromVector(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testMSCStackVecFromList = TestMSCStackVecFromList(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testMSCStackVecFromVector = TestMSCStackVecFromVector(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testMSCStackLstFromList = TestMSCStackLstFromList(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testMSCStackLstFromVector = TestMSCStackLstFromVector(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testMSCQueueVecFromList = TestMSCQueueVecFromList(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testMSCQueueVecFromVector = TestMSCQueueVecFromVector(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testMSCQueueLstFromList = TestMSCQueueLstFromList(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testMSCQueueLstFromVector = TestMSCQueueLstFromVector(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }


        if(output) {
            cout<<"\n\n*********** RESULTS ***********"<<endl;
            cout<<"\nCOMPARISION WITH STD:"<<endl;
            cout<<"lasd::StackVec == lasd::StackLst == std::Stack: "<<((StackVSSTD) ? "Corretto" : "Errore")<<endl;
            cout<<"lasd::QueueVec == lasd::QueueLst == std::Queue: "<<((QueueVSSTD) ? "Corretto" : "Errore")<<endl;

            cout<<"\nSORT:"<<endl;
            cout<<"Vector: "<<((testSort) ? "Corretto" : "Errore")<<endl;

            cout<<"\nCOMPARISION OPERATORS:"<<endl;
            cout<<"Linear == Linear: "<<((testEqualLinear) ? "Corretto" : "Errore")<<endl;
            cout<<"Vector == Vector: "<<((testEqualVector) ? "Corretto" : "Errore")<<endl;
            cout<<"List == List: "<<((testEqualList) ? "Corretto" : "Errore")<<endl;
            cout<<"StackLst == Stacklst: "<<((testEqualStackLst) ? "Corretto" : "Errore")<<endl;
            cout<<"StackVec == StackVec: "<<((testEqualStackVec) ? "Corretto" : "Errore")<<endl;
            cout<<"QueueVec == QueueVec: "<<((testEqualQueueLst) ? "Corretto" : "Errore")<<endl;
            cout<<"QueueLst == QueueLst: "<<((testEqualQueueVec) ? "Corretto" : "Errore")<<endl;

            cout<<"\nASSIGNAMENT OPERATORS:"<<endl;
            cout<<"Vector = Vector: "<<((testAssVector) ? "Corretto" : "Errore")<<endl;
            cout<<"List = List: "<<((testAssList) ? "Corretto" : "Errore")<<endl;
            cout<<"StackLst = Stacklst: "<<((testAssStackLst) ? "Corretto" : "Errore")<<endl;
            cout<<"StackVec = StackVec: "<<((testAssStackVec) ? "Corretto" : "Errore")<<endl;
            cout<<"QueueVec = QueueVec: "<<((testAssQueueLst) ? "Corretto" : "Errore")<<endl;
            cout<<"QueueLst = QueueLst: "<<((testAssQueueVec) ? "Corretto" : "Errore")<<endl;

            cout<<"\nCOPY CONSTRUCTORS: "<<endl;
            cout<<"Vector(Vector): "<<((testCCVec) ? "Corretto" : "Errore")<<endl;
            cout<<"List(List): "<<((testCCList) ? "Corretto" : "Errore")<<endl;
            cout<<"StackVec(StackVec): "<<((testCCStackVec) ? "Corretto" : "Errore")<<endl;
            cout<<"StackLst(StackLst): "<<((testCCStackLst) ? "Corretto" : "Errore")<<endl;
            cout<<"QueueLst(QueueLst): "<<((testCCQueueLst) ? "Corretto" : "Errore")<<endl;
            cout<<"QueueVec(QueueVec): "<<((testCCQueueVec) ? "Corretto" : "Errore")<<endl;

            cout<<"\nMOVE CONSTRUCTORS: "<<endl;
            cout<<"Vector(move(Vector)): "<<((testMCVec) ? "Corretto" : "Errore")<<endl;
            cout<<"List(move(List)): "<<((testMCList) ? "Corretto" : "Errore")<<endl;
            cout<<"StackVec(move(StackVec)): "<<((testMCStackVec) ? "Corretto" : "Errore")<<endl;
            cout<<"StackLst(move(StackLst)): "<<((testMCStackLst) ? "Corretto" : "Errore")<<endl;
            cout<<"QueueLst(move(QueueLst)): "<<((testMCQueueLst) ? "Corretto" : "Errore")<<endl;
            cout<<"QueueVec(move(QueueVec)): "<<((testMCQueueVec) ? "Corretto" : "Errore")<<endl;
            
            cout<<"\nSPECIFIC NON-MUTABLE SPECIFIC CONSTRUCTORS: "<<endl;
            cout<<"Vector(List): "<<((testSCVecFromList) ? "Corretto" : "Errore")<<endl;
            cout<<"List(Vector): "<<((testSCListFromVector) ? "Corretto" : "Errore")<<endl;
            cout<<"StackVec(Vector): "<<((testSCStackVecFromVector) ? "Corretto" : "Errore")<<endl;
            cout<<"StackVec(List): "<<((testSCStackVecFromList) ? "Corretto" : "Errore")<<endl;
            cout<<"StackLst(Vector): "<<((testSCStackLstFromVector) ? "Corretto" : "Errore")<<endl;
            cout<<"StackLst(List): "<<((testSCStackLstFromList) ? "Corretto" : "Errore")<<endl;
            cout<<"QueueLst(Vector): "<<((testSCQueueLstFromVector) ? "Corretto" : "Errore")<<endl;
            cout<<"QueueLst(List): "<<((testSCQueueLstFromList) ? "Corretto" : "Errore")<<endl;
            cout<<"QueueVec(Vector): "<<((testSCQueueVecFromVector) ? "Corretto" : "Errore")<<endl;
            cout<<"QueueVec(List): "<<((testSCQueueVecFromList) ? "Corretto" : "Errore")<<endl;

            cout<<"\nSPECIFIC MUTABLE SPECIFIC CONSTRUCTORS: "<<endl;
            cout<<"Vector(List): "<<((testMSCVecFromList) ? "Corretto" : "Errore")<<endl;
            cout<<"List(Vector): "<<((testMSCListFromVector) ? "Corretto" : "Errore")<<endl;
            cout<<"StackVec(Vector): "<<((testMSCStackVecFromVector) ? "Corretto" : "Errore")<<endl;
            cout<<"StackVec(List): "<<((testMSCStackVecFromList) ? "Corretto" : "Errore")<<endl;
            cout<<"StackLst(Vector): "<<((testMSCStackLstFromVector) ? "Corretto" : "Errore")<<endl;
            cout<<"StackLst(List): "<<((testMSCStackLstFromList) ? "Corretto" : "Errore")<<endl;
            cout<<"QueueLst(Vector): "<<((testMSCQueueLstFromVector) ? "Corretto" : "Errore")<<endl;
            cout<<"QueueLst(List): "<<((testMSCQueueLstFromList) ? "Corretto" : "Errore")<<endl;
            cout<<"QueueVec(Vector): "<<((testMSCQueueVecFromVector) ? "Corretto" : "Errore")<<endl;
            cout<<"QueueVec(List): "<<((testMSCQueueVecFromList) ? "Corretto" : "Errore")<<endl;
        }

        if (StackVSSTD && QueueVSSTD && testSort && testEqualLinear && testEqualVector && testEqualList && testEqualStackLst 
            && testEqualStackVec && testEqualQueueLst && testEqualQueueVec && testAssVector && testAssList && testAssStackLst 
            && testAssStackVec && testAssQueueLst && testAssQueueVec && testCCVec && testMCVec && testCCList && testMCList 
            && testCCStackVec && testMCStackVec && testCCStackLst && testMCStackLst && testCCQueueLst && testMCQueueLst 
            && testCCQueueVec && testMCQueueVec && testSCVecFromList && testSCListFromVector && testSCStackVecFromList 
            && testSCStackVecFromVector && testSCStackLstFromList && testSCStackLstFromVector && testSCQueueVecFromList 
            && testSCQueueVecFromVector && testSCQueueLstFromList && testSCQueueLstFromVector && testMSCVecFromList 
            && testMSCListFromVector && testMSCStackVecFromList && testMSCStackVecFromVector && testMSCStackLstFromList 
            && testMSCStackLstFromVector && testMSCQueueVecFromList && testMSCQueueVecFromVector && testMSCQueueLstFromList 
            && testMSCQueueLstFromVector
        )
        {
            total&=true;
        } else {
            total&=false;
        }

        if(!total) break;

        ITERAZIONI--;
    }

    if(total==true){
        cout<<"\nTUTTI I TEST SONO STATI SUPERATI!! :D ";
    }else{
        cout<<"\nCi sono test che non sono stati superati :(";
    }

    cout<<endl;

    return true;
}


/************************************************************************************************



 *          INIZIO TEST SU BT



*************************************************************************************************/



bool TestEqualBT(){
    if(output) cout<<"\n**********TEST TestEqualBT**********\n";
    bool correct=true;
    int temp_size = genSize(gen)+1;
    lasd::Vector<int> v1(temp_size);
    for(int i=0; i<temp_size; i++){
        int temp_num = genNum(gen);
        v1[i]=temp_num;
    } 
    lasd::BinaryTreeLnk<int> s1(v1);
    lasd::BinaryTreeVec<int> s2(v1);
    if(output) { 
        cout<<"\nS1: ";
        s1.Map( [](int& dat){ cout<<"\t"<<dat; } );
    }
    if(output) { 
        cout<<"\nS2: ";
        s2.Map( [](int& dat){ cout<<"\t"<<dat; } );
    }
    correct&=(s1.BinaryTree<int>::operator==(s2));
    v1[genSize(gen)%temp_size]=genNum(gen);
    lasd::BinaryTreeVec<int> s3(v1);
    correct&=(s1.BinaryTree<int>::operator!=(s3));
    s1.Clear();
    s2.Clear();
    correct&=(s1.BinaryTree<int>::operator==(s2));
    return correct;
}

bool TestEqualBTLnk(){
    if(output) cout<<"\n**********TEST TestEqualBTLnk**********\n";
    bool correct=true;
    int temp_size = genSize(gen)+1;
    lasd::Vector<int> v1(temp_size);
    for(int i=0; i<temp_size; i++){
        int temp_num = genNum(gen);
        v1[i]=temp_num;
    } 
    lasd::BinaryTreeLnk<int> s1(v1);
    lasd::BinaryTreeLnk<int> s2(v1);
    v1[genSize(gen)%temp_size]=genNum(gen);
    lasd::BinaryTreeLnk<int> s3(v1);
    if(output) { 
        cout<<"\nS1: ";
        s1.Map( [](int& dat){ cout<<"\t"<<dat; } );
    }
    if(output) { 
        cout<<"\nS2: ";
        s2.Map( [](int& dat){ cout<<"\t"<<dat; } );
    }
    if(output) { 
        cout<<"\nS2: ";
        s3.Map( [](int& dat){ cout<<"\t"<<dat; } );
    }
    correct&=(s1==s2);
    correct&=(s1!=s3);
    s2.Clear();
    correct&=(s1!=s2);
    s1.Clear();
    correct&=(s1==s2);
    return correct;
}

bool TestEqualBTVec(){
    if(output) cout<<"\n**********TEST TestEqualBTVec**********\n";
    bool correct=true;
    int temp_size = genSize(gen)+1;
    lasd::Vector<int> v1(temp_size);
    for(int i=0; i<temp_size; i++){
        int temp_num = genNum(gen);
        v1[i]=temp_num;
    } 
    lasd::BinaryTreeVec<int> s1(v1);
    lasd::BinaryTreeVec<int> s2(v1);
    v1[genSize(gen)%temp_size]=genNum(gen);
    lasd::BinaryTreeVec<int> s3(v1);
    if(output) { 
        cout<<"\nS1: ";
        s1.Map( [](int& dat){ cout<<"\t"<<dat; } );
    }
    if(output) { 
        cout<<"\nS2: ";
        s2.Map( [](int& dat){ cout<<"\t"<<dat; } );
    }
        if(output) { 
        cout<<"\nS1: ";
        s1.Map( [](int& dat){ cout<<"\t"<<dat; } );
    }
    if(output) { 
        cout<<"\nS3: ";
        s2.Map( [](int& dat){ cout<<"\t"<<dat; } );
    }
    correct&=(s1==s2);
    correct&=(s1!=s3);
    s2.Clear();
    correct&=(s1!=s2);
    s1.Clear();
    correct&=(s1==s2);
    return correct;
}

bool TestEqualBST(){
    if(output) cout<<"\n**********TEST TestEqualBST**********\n";
    bool correct=true;
    int temp_size = genSize(gen)+1;
    lasd::Vector<int> v1(temp_size);
    for(int i=0; i<temp_size; i++){
        int temp_num = genNum(gen);
        v1[i]=temp_num;
    } 
    lasd::BST<int> s1(v1);
    lasd::BST<int> s2(v1);
    v1[genSize(gen)%temp_size]=genNum(gen);
    lasd::BST<int> s3(v1);
    correct&=(s1==s2);
    correct&=(s1!=s3);
    s2.Clear();
    correct&=(s1!=s2);
    s1.Clear();
    correct&=(s1==s2);
    return correct;
}

bool TestAssBTVec(){
    if(output) cout<<"\n**********TEST TestAssBTVec**********\n";
    bool correct=true;
    int temp_size = genSize(gen);
    lasd::Vector<int> v1(temp_size);
    for(int i=0; i<temp_size; i++) v1[i]=genNum(gen);
    lasd::BinaryTreeVec<int> s1(v1);
    lasd::BinaryTreeVec<int> s2;
    s2 = s1;
    if(output) { 
        cout<<"\nS1: ";
        s1.Map( [](int& dat){ cout<<"\t"<<dat; } );
    }
    if(output) { 
        cout<<"\nS2: ";
        s2.Map( [](int& dat){ cout<<"\t"<<dat; } );
    }
    correct&=(s1==s2);
    s2.Clear();
    s1.Clear();
    correct&=(s1==s2);
    return correct;
}

bool TestAssBTLnk(){
    if(output) cout<<"\n**********TEST TestAssBTLnk**********\n";
    bool correct=true;
    int temp_size = genSize(gen);
    lasd::Vector<int> v1(temp_size);
    for(int i=0; i<temp_size; i++) v1[i]=genNum(gen);
    lasd::BinaryTreeLnk<int> s1(v1);
    lasd::BinaryTreeLnk<int> s2;
    s2 = s1;
    if(output) { 
        cout<<"\nS1: ";
        s1.Map( [](int& dat){ cout<<"\t"<<dat; } );
    }
    if(output) { 
        cout<<"\nS2: ";
        s2.Map( [](int& dat){ cout<<"\t"<<dat; } );
    }
    correct&=(s1==s2);
    s2.Clear();
    s1.Clear();
    correct&=(s1==s2);
    return correct;
}

bool TestAssBST(){
    if(output) cout<<"\n**********TEST TestAssBST**********\n";
    bool correct=true;
    int temp_size = genSize(gen);
    lasd::Vector<int> v1(temp_size);
    for(int i=0; i<temp_size; i++) v1[i]=genNum(gen);
    lasd::BST<int> s1(v1);
    lasd::BST<int> s2;
    s2 = s1;
    correct&=(s1==s2);
    s2.Clear();
    s1.Clear();
    correct&=(s1==s2);
    return correct;
}

bool TestMAssBTVec(){
    if(output) cout<<"\n**********TEST TestMAssBTVec**********\n";
    bool correct=true;
    int temp_size1 = genSize(gen)+1;
    int temp_size2 = genSize(gen)+1;
    lasd::Vector<int> v1(temp_size1);
    lasd::Vector<int> v2(temp_size2);
    for(int i=0; i<v1.Size(); i++) v1[i]=genNum(gen);
    for(int i=0; i<v2.Size(); i++) v2[i]=genNum(gen);
    lasd::BinaryTreeVec<int> s1(v1);
    int r1 = s1.Root().Element();
    if(output) { 
        cout<<"\nS1: ";
        s1.Map( [](int& dat){ cout<<"\t"<<dat; } );
    }
    lasd::BinaryTreeVec<int> s2(v2);
    if(output) { 
        cout<<"\nS2: ";
        s2.Map( [](int& dat){ cout<<"\t"<<dat; } );
    }
    int r2 = s2.Root().Element();

    if(output) cout<<"\ns1.root(): "<<r1<<"\ts2.Root(): "<<r2;
    lasd::BinaryTreeVec<int> s3(v1);
    lasd::BinaryTreeVec<int> s4(v2);
    lasd::BinaryTreeVec<int> s5;
    s2 = move(s1);
    if(output) cout<<"\ns1.root(): "<<s1.Root().Element()<<"\ts2.Root(): "<<s2.Root().Element()<<"\n";
    correct&= (s2.Root().Element() == r1);
    correct&=(s1==s4);
    s1.Map(
        [](int& dat){
            dat+=dat;
        }
    );
    correct&=(s1!=s4);
    correct&=(s2==s3);
    s1 = move(s5);
    correct&=(s1.Empty());
    s2.Clear();
    correct&=(s1==s2);
    return correct;
}

bool TestMAssBTLnk(){
    if(output) cout<<"\n**********TEST TestMAssBTLnk**********\n";
    bool correct=true;
    int temp_size1 = genSize(gen)+1;
    int temp_size2 = genSize(gen)+1;
    lasd::Vector<int> v1(temp_size1);
    lasd::Vector<int> v2(temp_size2);
    for(int i=0; i<v1.Size(); i++) v1[i]=genNum(gen);
    for(int i=0; i<v2.Size(); i++) v2[i]=genNum(gen);
    lasd::BinaryTreeLnk<int> s1(v1);
    if(output) { 
        cout<<"\nV1: ";
        v1.Map( [](int& dat){ cout<<"\t"<<dat; } );
    }
    if(output) { 
        cout<<"\nV2: ";
        v2.Map( [](int& dat){ cout<<"\t"<<dat; } );
    }
    int r1 = s1.Root().Element();
    lasd::BinaryTreeLnk<int> s2(v2);
    int r2 = s2.Root().Element();
    lasd::BinaryTreeLnk<int> s3(v1);
    lasd::BinaryTreeLnk<int> s4(v2);
    lasd::BinaryTreeLnk<int> s5;
    s2 = move(s1);
    if(output) { 
        cout<<"\nS1: ";
        s1.Map( [](int& dat){ cout<<"\t"<<dat; } );
    }
    if(output) { 
        cout<<"\nS2: ";
        s2.Map( [](int& dat){ cout<<"\t"<<dat; } );
    }
    correct&= (s2.Root().Element() == r1);
    correct&=(s1==s4);
    s1.Map(
        [](int& dat){
            dat+=dat;
        }
    );
    correct&=(s1!=s4);
    correct&=(s2==s3);
    s1 = move(s5);
    correct&=(s1.Empty());
    s2.Clear();
    correct&=(s1==s2);
    return correct;
}

bool TestMAssBST(){
    if(output) cout<<"\n**********TEST TestMAssBST**********\n";
    bool correct=true;
    int temp_size = genSize(gen);
    lasd::Vector<int> v1(temp_size);
    for(int i=0; i<temp_size; i++){
        v1[i]=genNum(gen);
    }
    lasd::BST<int> s1(v1);
    lasd::BST<int> s2;
    s2 = move(s1);
    correct&=(s1.Empty());
    s2.Clear();
    correct&=(s1==s2);
    return correct;
}

bool CCBTLnk(){
    if(output) cout<<"\n**********TEST CCBTLnk**********\n";
    bool correct=true;
    lasd::Vector<int> v1(genSize(gen));
    for(ulong i=0; i<v1.Size(); i++) v1[i]=genNum(gen);
    lasd::BinaryTreeLnk<int> s1(v1);
    lasd::BinaryTreeLnk<int> s2(s1);
    if(output) { 
        cout<<"\nS1: ";
        s1.Map( [](int& dat){ cout<<"\t"<<dat; } );
    }
    if(output) { 
        cout<<"\nS2: ";
        s2.Map( [](int& dat){ cout<<"\t"<<dat; } );
    }
    correct&=(s1==s2);
    s1.Clear();
    correct&=(s1.Empty());
    s2.Clear();
    correct&=(s1==s2);
    return correct;
}

bool CCBTVec(){
    if(output) cout<<"\n**********TEST CCBTVec**********\n";
    bool correct=true;
    lasd::Vector<int> v1(genSize(gen));
    for(ulong i=0; i<v1.Size(); i++) v1[i]=genNum(gen);
    lasd::BinaryTreeVec<int> s1(v1);
    lasd::BinaryTreeVec<int> s2(s1);
    correct&=(s1==s2);
    if(output) { 
        cout<<"\nS1: ";
        s1.Map( [](int& dat){ cout<<"\t"<<dat; } );
    }
    if(output) { 
        cout<<"\nS2: ";
        s2.Map( [](int& dat){ cout<<"\t"<<dat; } );
    }
    s1.Clear();
    correct&=(s1.Empty());
    s2.Clear();
    correct&=(s1==s2);
    return correct;
}

bool CCBST(){
    if(output) cout<<"\n**********TEST CCBST**********\n";
    bool correct=true;
    lasd::Vector<int> v1(genSize(gen));
    for(ulong i=0; i<v1.Size(); i++) v1[i]=genNum(gen);
    lasd::BST<int> s1(v1);
    lasd::BST<int> s2(s1);
    correct&=(s1==s2);
    s1.Clear();
    correct&=(s1.Empty());
    s2.Clear();
    correct&=(s1==s2);
    return correct;
}

bool MCBTLnk(){
    if(output) cout<<"\n**********TEST MCBTLnk**********\n";
    bool correct=true;
    int temp_size1 = genSize(gen);
    lasd::Vector<int> v1(temp_size1);
    for(int i=0; i<v1.Size(); i++) v1[i]=genNum(gen);
    lasd::BinaryTreeLnk<int> s1(v1);
    lasd::BinaryTreeLnk<int> s2(v1);
    lasd::BinaryTreeLnk<int> s3(move(s1));
    correct&=(s1.Empty());
    correct&=(s2==s3);
    s3.Clear();
    correct&=(s3.Empty());
    s2.Clear();
    correct&=(s3==s2);
    return correct;
}

bool MCBTVec(){
    if(output) cout<<"\n**********TEST MCBTVec**********\n";
    bool correct=true;
    int temp_size1 = genSize(gen);
    lasd::Vector<int> v1(temp_size1);
    for(int i=0; i<v1.Size(); i++) v1[i]=genNum(gen);
    lasd::BinaryTreeVec<int> s1(v1);
    lasd::BinaryTreeVec<int> s2(v1);
    lasd::BinaryTreeVec<int> s3(move(s1));
    correct&=(s1.Empty());
    correct&=(s2==s3);
    s3.Clear();
    correct&=(s3.Empty());
    s2.Clear();
    correct&=(s3==s2);
    return correct;
}

bool MCBST(){
    if(output) cout<<"\n**********TEST MCBST**********\n";
    bool correct=true;
    lasd::Vector<int> v1(genSize(gen));
    for(int i=0; i<v1.Size(); i++)v1[i]=genNum(gen);
    lasd::BST<int> s1(v1);
    lasd::BST<int> s2(move(s1));
    lasd::BST<int> s3(v1);
    correct&=(s1.Empty());
    correct&=(s2==s3);
    s2.Clear();
    correct&=(s1==s2);
    return correct;
}

bool MSCBTVecVec(){
    if(output) cout<<"\n**********TEST MSCBTVecVec**********\n";
    bool correct=true;
    int temp_size = genSize(gen);
    lasd::Vector<int> l1(temp_size);
    lasd::Vector<int> l2(temp_size);
    for(int i=0; i<temp_size; i++) {
        int temp_num = genNum(gen);
        l1[i]=temp_num;
        l2[i]=temp_num;
    }
    lasd::BinaryTreeVec<int> s1(move(l1));
    lasd::BTBreadthIterator<int> itr(s1);
    l2.PreOrderMap(
        [&correct, &itr](const int& dat){
            correct&= ((*itr)==dat);
            ++itr;
        }
    );
    return correct;
}


bool MSCBTVecLst(){
    if(output) cout<<"\n**********TEST MSCBTVecLst**********\n";
    bool correct=true;
    int temp_size = genSize(gen);
    lasd::List<int> l1;
    lasd::List<int> l2;
    for(int i=0; i<temp_size; i++) {
        int temp_num = genNum(gen);
        l1.Insert(temp_num);
        l2.Insert(temp_num);
    }
    lasd::BinaryTreeVec<int> s1(move(l1));
    lasd::BTBreadthIterator<int> itr(s1);
    l2.PreOrderMap(
        [&correct, &itr](const int& dat){
            correct&= ((*itr)==dat);
            ++itr;
        }
    );
    return correct;
}

bool MSCBTLnkVec(){
    if(output) cout<<"\n**********TEST MSCBTLnkVec**********\n";
    bool correct=true;
    int temp_size = genSize(gen);
    lasd::Vector<int> l1(temp_size);
    lasd::Vector<int> l2(temp_size);
    for(int i=0; i<temp_size; i++) {
        int temp_num = genNum(gen);
        l1[i]=temp_num;
        l2[i]=temp_num;
    }
    lasd::BinaryTreeLnk<int> s1(move(l1));
    lasd::BTBreadthIterator<int> itr(s1);
    l2.PreOrderMap(
        [&correct, &itr](const int& dat){
            correct&= ((*itr)==dat);
            ++itr;
        }
    );
    return correct;
}

bool MSCBTLnkLst(){
    if(output) cout<<"\n**********TEST MSCBTLnkLst**********\n";
    bool correct=true;
    int temp_size = genSize(gen);
    lasd::List<int> l1;
    lasd::List<int> l2;
    for(int i=0; i<temp_size; i++) {
        int temp_num = genNum(gen);
        l1.Insert(temp_num);
        l2.Insert(temp_num);
    }
    lasd::BinaryTreeLnk<int> s1(move(l1));
    lasd::BTBreadthIterator<int> itr(s1);
    l2.PreOrderMap(
        [&correct, &itr](const int& dat){
            correct&= ((*itr)==dat);
            ++itr;
        }
    );
    return correct;
}

bool MSCBSTVec(){
    if(output) cout<<"\n**********TEST MSCBSTVec**********\n";
    bool correct=true;
    int temp_size = genSize(gen);
    lasd::Vector<int> l1(temp_size);
    lasd::Vector<int> l2(temp_size);
    for(int i=0; i<temp_size; i++) {
        int temp_num = genNum(gen);
        l1[i]=temp_num;
        l2[i]=temp_num;
    }
    lasd::BST<int> s1(move(l1));
    l2.PreOrderMap(
        [&correct, &s1](const int& dat){
            correct&=s1.Exists(dat);
        }
    );
    return correct;
}

bool MSCBSTLst(){
    if(output) cout<<"\n**********TEST MSCBSTLst**********\n";
    bool correct=true;
    int temp_size = genSize(gen);
    lasd::List<int> l1;
    lasd::List<int> l2;
    for(int i=0; i<temp_size; i++) {
        int temp_num = genNum(gen);
        l1.Insert(temp_num);
        l2.Insert(temp_num);
    }
    lasd::BST<int> s1(move(l1));
    l2.PostOrderMap(
        [&correct, &s1](const int& dat){
            correct&=s1.Exists(dat);
        }
    );
    return correct;
}

template <typename Data>
bool SCBTLnk(const lasd::MappableContainer<Data>* cont){
    const lasd::BinaryTreeLnk<int> s1(*cont);
    bool correct=true;
    lasd::BTBreadthIterator<int> itr(s1);
    (*cont).Map(
        [&correct, &itr](const Data& dat){
            correct&= ((*itr)==dat);
            ++itr;
        }
    );
    return correct;
}

bool SCBTLnkVec(){
    if(output) cout<<"\n**********TEST SCBTLnkVec**********\n";
    bool correct=true;
    lasd::Vector<int> s1(genSize(gen));
    for(int i=0; i<s1.Size(); i++)s1[i]=genNum(gen);
    const lasd::Vector<int>s2(s1);
    correct&=(SCBTLnk(&s1));
    return correct;
}

bool SCBTLnkLst(){
    if(output) cout<<"\n**********TEST SCBTLnkLst**********\n";
    bool correct=true;
    lasd::List<int> s1;
    int temp_size = genSize(gen);
    for(int i=0; i<temp_size; i++) s1.Insert(genNum(gen));
    const lasd::List<int>s2(s1);
    correct&=SCBTLnk(&s2);
    return correct;
}

template <typename Data>
bool SCBTVec(const lasd::MappableContainer<Data>* cont){
    const lasd::BinaryTreeVec<int> s1(*cont);
    bool correct=true;
    lasd::BTBreadthIterator<int> itr(s1);
    (*cont).Map(
        [&correct, &itr](const Data& dat){
            correct&= ((*itr)==dat);
            ++itr;
        }
    );
    return correct;
}

bool SCBTVecVec(){
    if(output) cout<<"\n**********TEST SCBTVecVec**********\n";
    bool correct=true;
    lasd::Vector<int> s1(genSize(gen));
    for(int i=0; i<s1.Size(); i++)s1[i]=genNum(gen);
    const lasd::Vector<int>s2(s1);
    correct&=(SCBTVec(&s2));
    return correct;
}

bool SCBTVecLst(){
    if(output) cout<<"\n**********TEST SCBTVecLst**********\n";
    bool correct=true;
    lasd::List<int> s1;
    int temp_size = genSize(gen);
    for(int i=0; i<temp_size; i++) s1.Insert(genNum(gen));
    const lasd::List<int>s2(s1);
    correct&=SCBTVec(&s2);
    return correct;
}

template <typename Data>
bool SCBST(const lasd::MappableContainer<Data>* cont){
    const lasd::BST<int> s1(*cont);
    bool correct=true;
    (*cont).Map(
        [&correct, &s1](const Data& dat){
            correct&=s1.Exists(dat);
        }
    );
    return correct;
}

bool SCBSTVec(){
    if(output) cout<<"\n**********TEST SCBSTVec**********\n";
    bool correct=true;
    lasd::Vector<int> s1(genSize(gen));
    for(int i=0; i<s1.Size(); i++) s1[i]=genNum(gen);
    const lasd::Vector<int>s2(s1);
    correct&=(SCBST(&s2));
    return correct;
}

bool SCBSTLst(){
    if(output) cout<<"\n**********TEST SCBSTLst**********\n";
    bool correct=true;
    lasd::List<int> s1;
    int temp_size = genSize(gen);
    for(int i=0; i<temp_size; i++) s1.Insert(genNum(gen));
    const lasd::List<int>s2(s1);
    correct&=SCBST(&s2);
    return correct;
}

bool TestBSTMax(){
    if(output) cout<<"\n**********TEST TestBSTMax**********\n";
    bool correct=true;
    int temp_size = genSize(gen);
    lasd::Vector<int> v1(temp_size);
    lasd::List<int> l1;
    for(int i=0; i<v1.Size(); i++) v1[i]=genNum(gen);
    v1.Sort();
    for(int i{0}; i<v1.Size(); i++) l1.Insert(v1[i]);
    temp_size = l1.Size();
    lasd::BST<int> bst(l1);
    if(output) { 
        cout<<"\nSorted list1: ";
        l1.PostOrderMap( [](int& dat){ cout<<"\t"<<dat; } );
    }
    temp_size--;
    if(output) cout<<"\nBST: ";
    while(!(bst.Empty())){
        if(output) cout<<"\t"<<bst.Max();
        correct&=(bst.MaxNRemove()==l1[temp_size--]);
    }
    return correct;
}

bool TestBSTMin(){
    if(output) cout<<"\n**********TEST TestBSTMin**********\n";
    bool correct=true;
    int temp_size = genSize(gen);
    lasd::Vector<int> v1(temp_size);
    lasd::List<int> l1;
    for(int i=0; i<v1.Size(); i++) v1[i]=genNum(gen);
    v1.Sort();
    for(int i{0}; i<v1.Size(); i++) l1.Insert(v1[i]);
    temp_size = l1.Size();
    lasd::BST<int> bst(l1);
    if(output) { 
        cout<<"\nSorted list1: ";
        l1.PostOrderMap( [](int& dat){ cout<<"\t"<<dat; } );
    }
    int cursor=0 ;
    if(output) cout<<"\nBST: ";
    while(!(bst.Empty())){
        if(output) cout<<"\t"<<bst.Min();
        correct&=(bst.MinNRemove()==l1[cursor++]);
    }
    return correct;
}

bool TestBSTPred(){
    if(output) cout<<"\n**********TEST TestBSTPred**********\n";
    bool correct=true;
    int temp_size = genSize(gen);
    lasd::Vector<int> v1(temp_size);
    lasd::List<int> l1;
    for(int i=0; i<v1.Size(); i++) v1[i]=genNum(gen);
    v1.Sort();
    for(int i{0}; i<v1.Size(); i++) l1.Insert(v1[i]);
    temp_size = l1.Size();
    lasd::BST<int> bst(l1);
    if(output) { 
        cout<<"\nSorted list1: ";
        l1.PostOrderMap( [](int& dat){ cout<<"\t"<<dat; } );
    }
    temp_size--;
    if(bst.Size()>3) correct&= ((bst.Predecessor(bst.Min()+1))==bst.Min());
    if(bst.Size()>3) correct&= (bst.Successor(bst.Predecessor(bst.Max()))==bst.Max());
    if(output) cout<<"\nBST: ";
    while(bst.Size()>1){
        if(output) cout<<"\t"<<bst.Predecessor(l1[temp_size]);
        correct&=(bst.PredecessorNRemove(l1[temp_size])==l1[temp_size-1]);
        temp_size--;
    }
    return correct;
}

bool TestBSTSucc(){
    if(output) cout<<"\n**********TEST TestBSTSucc**********\n";
    bool correct=true;
    int temp_size = genSize(gen);
    lasd::Vector<int> v1(temp_size);
    lasd::List<int> l1;
    for(int i=0; i<v1.Size(); i++) v1[i]=genNum(gen);
    v1.Sort();
    for(int i{0}; i<v1.Size(); i++) l1.Insert(v1[i]);
    temp_size = l1.Size();
    lasd::BST<int> bst(l1);
    if(output) { 
        cout<<"\nSorted list1: ";
        l1.PostOrderMap( [](int& dat){ cout<<"\t"<<dat; } );
    }
    if(bst.Size()>3) correct&= (bst.Successor((bst.Max()-1))==bst.Max());
    if(bst.Size()>3) correct&= (bst.Predecessor(bst.Successor(bst.Min()))==bst.Min());
    if(output) cout<<"\nBST: ";
    int cursor = 0;
    while(bst.Size()>1){
        if(output) cout<<"\t"<<bst.Successor(l1[cursor]);
        correct&=(bst.SuccessorNRemove(l1[cursor])==l1[cursor+1]);
        cursor++;
    }
    return correct;
}

void MapPrint(int value){
  cout<<"\t"<<value;
}

bool TestMapsBTLnk(){
    cout<<"\n**********TEST TestMapsBTLnk**********\n";
    lasd::Vector<int> v1(genSize(gen));
    for(int i=0; i<v1.Size(); i++) v1[i]=genNum(gen);
    cout<<"\nVettore: ";
    v1.PreOrderMap(MapPrint);
    lasd::BinaryTreeLnk<int> bt(v1);
    cout<<"\nBTLnk:\n";
    bt.printBT();
    cout<<"\nPreOrderMap: ";
    bt.PreOrderMap(MapPrint);
    cout<<"\nPostOrderMap: ";
    bt.PostOrderMap(MapPrint);
    cout<<"\nInOrderMap: ";
    bt.InOrderMap(MapPrint);
    cout<<"\nBreadthMap: ";
    bt.BreadthMap(MapPrint);
    cout<<endl<<"Si prega di verificare l'esattezza delle map e comunicarne il risultato:\n1. Le map sono corrette\n2. Una o piu' map non sono corrette.\nInserisci l'opzione: ";
    int choose = -1;
    while(choose!=1 && choose!=2) cin>>choose;
    return (choose==1);
}

bool TestMapsBTVec(){
    cout<<"\n**********TEST TestMapsBTVec**********\n";
    lasd::Vector<int> v1(genSize(gen));
    for(int i=0; i<v1.Size(); i++) v1[i]=genNum(gen);
    cout<<"\nVettore: ";
    v1.PreOrderMap(MapPrint);
    lasd::BinaryTreeVec<int> bt(v1);
    cout<<"\nBTVec:\n";
    bt.printBT();
    cout<<"\nPreOrderMap: ";
    bt.PreOrderMap(MapPrint);
    cout<<"\nPostOrderMap: ";
    bt.PostOrderMap(MapPrint);
    cout<<"\nInOrderMap: ";
    bt.InOrderMap(MapPrint);
    cout<<"\nBreadthMap: ";
    bt.BreadthMap(MapPrint);
    cout<<endl<<"Si prega di verificare l'esattezza delle map e comunicarne il risultato:\n1. Le map sono corrette.\n2. Una o piu' map non sono corrette.\nInserisci l'opzione: ";
    int choose = -1;
    while(choose!=1 && choose!=2) cin>>choose;
    return (choose==1);
}

bool TestMapsBST(){
    cout<<"\n**********TEST TestMapsBST**********\n";
    lasd::Vector<int> v1(genSize(gen));
    for(int i=0; i<v1.Size(); i++) v1[i]=genNum(gen);
    cout<<"\nVettore: ";
    v1.PreOrderMap(MapPrint);
    const lasd::BST<int> bt(v1);
    cout<<"\nBST:\n";
    bt.printBT();
    cout<<"\nPreOrderMap: ";
    bt.PreOrderMap(MapPrint);
    cout<<"\nPostOrderMap: ";
    bt.PostOrderMap(MapPrint);
    cout<<"\nInOrderMap: ";
    bt.InOrderMap(MapPrint);
    cout<<"\nBreadthMap: ";
    bt.BreadthMap(MapPrint);
    cout<<endl<<"Si prega di verificare l'esattezza delle map e comunicarne il risultato:\n1. Le map sono corrette.\n2. Una o piu' map non sono corrette.\nInserisci l'opzione: ";
    int choose = -1;
    while(choose!=1 && choose!=2) cin>>choose;
    return (choose==1);
}

bool TestInsertRemoveBST(){
    bool correct = true;
    lasd::Vector<int> v1(genSize(gen));
    for(int i{0}; i<v1.Size(); i++) v1[i]=genNum(gen);
    lasd::BST<int> bst(v1);
    int actual_size = bst.Size();
    for(int i{0}; i<v1.Size(); i++){
        if(genNum(gen)%2==0) if(bst.Insert(genNum(gen))) actual_size++;
        else {
            while(!(bst.Remove(genNum(gen)))) ;
            actual_size--;
        }
    }
    correct&=(actual_size==bst.Size());
    bst.Clear();
    correct&=(!(bst.Remove(genNum(gen))));
    correct&=(bst.Insert(genNum(gen)));
    return correct;
}

bool TestPreOrdItrLnk(){
    if(output)cout<<"\n**********TEST TestPreOrdItrLnk**********\n";
    bool correct = true;
    int temp_size = genSize(gen);
    lasd::List<int> l1;
    for(int i{0}; i<temp_size; i++) l1.Insert(genNum(gen));
    temp_size = l1.Size();
    lasd::BinaryTreeLnk<int> bt(l1);
    lasd::BTPreOrderIterator<int> itr(bt);
    bt.PreOrderMap(
        [&itr, &correct](const int dat){
            correct&= ((*itr)==dat);
            ++itr;
        }
    );
    itr.Reset();
    bt.PreOrderMap(
        [&itr, &correct](const int dat){
            correct&= ((*itr)==dat);
            ++itr;
        }
    );
    try{ *itr; correct=false; } catch (const std::out_of_range& e) { correct&=true; }
    try{ ++itr; correct=false; } catch (const std::out_of_range& e) { correct&=true; }
    return correct;
}

bool TestPostOrdItrLnk(){
    if(output)cout<<"\n**********TEST TestPostOrdItrLnk**********\n";
    bool correct = true;
    int temp_size = genSize(gen);
    lasd::List<int> l1;
    for(int i{0}; i<temp_size; i++) l1.Insert(genNum(gen));
    temp_size = l1.Size();
    lasd::BinaryTreeLnk<int> bt(l1);
    lasd::BTPostOrderIterator<int> itr(bt);
    bt.PostOrderMap(
        [&itr, &correct](const int dat){
            correct&= ((*itr)==dat);
            ++itr;
        }
    );
    itr.Reset();
    bt.PostOrderMap(
        [&itr, &correct](const int dat){
            correct&= ((*itr)==dat);
            ++itr;
        }
    );
    try{ *itr; correct=false; } catch (const std::out_of_range& e) { correct&=true; }
    try{ ++itr; correct=false; } catch (const std::out_of_range& e) { correct&=true; }
    return correct;
}

bool TestInOrdItrLnk(){
    if(output)cout<<"\n**********TEST TestInOrdItrLnk**********\n";
    bool correct = true;
    int temp_size = genSize(gen);
    lasd::List<int> l1;
    for(int i{0}; i<temp_size; i++) l1.Insert(genNum(gen));
    temp_size = l1.Size();
    lasd::BinaryTreeLnk<int> bt(l1);
    lasd::BTInOrderIterator<int> itr(bt);
    bt.InOrderMap(
        [&itr, &correct](const int dat){
            correct&= ((*itr)==dat);
            ++itr;
        }
    );
    itr.Reset();
    bt.InOrderMap(
        [&itr, &correct](const int dat){
            correct&= ((*itr)==dat);
            ++itr;
        }
    );
    try{ *itr; correct=false; } catch (const std::out_of_range& e) { correct&=true; }
    try{ ++itr; correct=false; } catch (const std::out_of_range& e) { correct&=true; }
    return correct;
}

bool TestBreadthItrLnk(){
    if(output)cout<<"\n**********TEST TestBreadthItrLnk**********\n";
    bool correct = true;
    int temp_size = genSize(gen);
    lasd::List<int> l1;
    for(int i{0}; i<temp_size; i++) l1.Insert(genNum(gen));
    temp_size = l1.Size();
    lasd::BinaryTreeLnk<int> bt(l1);
    lasd::BTBreadthIterator<int> itr(bt);
    bt.BreadthMap(
        [&itr, &correct](const int dat){
            correct&= ((*itr)==dat);
            ++itr;
        }
    );
    itr.Reset();
    bt.BreadthMap(
        [&itr, &correct](const int dat){
            correct&= ((*itr)==dat);
            ++itr;
        }
    );
    try{ *itr; correct=false; } catch (const std::out_of_range& e) { correct&=true; }
    try{ ++itr; correct=false; } catch (const std::out_of_range& e) { correct&=true; }
    return correct;
}

bool TestPreOrdItrVec(){
    if(output)cout<<"\n**********TEST TestPreOrdItrVec**********\n";
    bool correct = true;
    int temp_size = genSize(gen);
    lasd::List<int> l1;
    for(int i{0}; i<temp_size; i++) l1.Insert(genNum(gen));
    temp_size = l1.Size();
    lasd::BinaryTreeVec<int> bt(l1);
    lasd::BTPreOrderIterator<int> itr(bt);
    bt.PreOrderMap(
        [&itr, &correct](const int dat){
            correct&= ((*itr)==dat);
            ++itr;
        }
    );
    itr.Reset();
    bt.PreOrderMap(
        [&itr, &correct](const int dat){
            correct&= ((*itr)==dat);
            ++itr;
        }
    );
    try{ *itr; correct=false; } catch (const std::out_of_range& e) { correct&=true; }
    try{ ++itr; correct=false; } catch (const std::out_of_range& e) { correct&=true; }
    return correct;
}

bool TestPostOrdItrVec(){
    if(output)cout<<"\n**********TEST TestPostOrdItrVec**********\n";
    bool correct = true;
    int temp_size = genSize(gen);
    lasd::List<int> l1;
    for(int i{0}; i<temp_size; i++) l1.Insert(genNum(gen));
    temp_size = l1.Size();
    lasd::BinaryTreeVec<int> bt(l1);
    lasd::BTPostOrderIterator<int> itr(bt);
    bt.PostOrderMap(
        [&itr, &correct](const int dat){
            correct&= ((*itr)==dat);
            ++itr;
        }
    );
    itr.Reset();
    bt.PostOrderMap(
        [&itr, &correct](const int dat){
            correct&= ((*itr)==dat);
            ++itr;
        }
    );
    try{ *itr; correct=false; } catch (const std::out_of_range& e) { correct&=true; }
    try{ ++itr; correct=false; } catch (const std::out_of_range& e) { correct&=true; }
    return correct;
}

bool TestInOrdItrVec(){
    if(output)cout<<"\n**********TEST TestInOrdItrVec**********\n";
    bool correct = true;
    int temp_size = genSize(gen);
    lasd::List<int> l1;
    for(int i{0}; i<temp_size; i++) l1.Insert(genNum(gen));
    temp_size = l1.Size();
    lasd::BinaryTreeVec<int> bt(l1);
    lasd::BTInOrderIterator<int> itr(bt);
    bt.InOrderMap(
        [&itr, &correct](const int dat){
            correct&= ((*itr)==dat);
            ++itr;
        }
    );
    itr.Reset();
    bt.InOrderMap(
        [&itr, &correct](const int dat){
            correct&= ((*itr)==dat);
            ++itr;
        }
    );
    try{ *itr; correct=false; } catch (const std::out_of_range& e) { correct&=true; }
    try{ ++itr; correct=false; } catch (const std::out_of_range& e) { correct&=true; }
    return correct;
}

bool TestBreadthItrVec(){
    if(output)cout<<"\n**********TEST TestBreadthItrVec**********\n";
    bool correct = true;
    int temp_size = genSize(gen);
    lasd::List<int> l1;
    for(int i{0}; i<temp_size; i++) l1.Insert(genNum(gen));
    temp_size = l1.Size();
    lasd::BinaryTreeVec<int> bt(l1);
    lasd::BTBreadthIterator<int> itr(bt);
    bt.BreadthMap(
        [&itr, &correct](const int dat){
            correct&= ((*itr)==dat);
            ++itr;
        }
    );
    itr.Reset();
    bt.BreadthMap(
        [&itr, &correct](const int dat){
            correct&= ((*itr)==dat);
            ++itr;
        }
    );
    try{ *itr; correct=false; } catch (const std::out_of_range& e) { correct&=true; }
    try{ ++itr; correct=false; } catch (const std::out_of_range& e) { correct&=true; }
    return correct;
}

bool davtest_ex2(){

    MIN_SIZE = 0;
    MAX_SIZE = 100;
    MIN_NUM = INT16_MIN;
    MAX_NUM = INT16_MAX;

    cout<<"\n\n*********** CONFIGURAZIONE DEI TEST: ***********"<<endl;
    cout<<"Necessiti degli output di debug?"<<endl;
    cout<<"1. Voglio visualizzare gli output di debug. (La dimensione delle strutture sara' ridotta)."<<endl;
    cout<<"2. No, voglio proseguire senza visualizzare gli output di debug. (Consigliato)"<<endl;
    cout<<"Inserisci l'opzione: ";
    int choose = -1;
    while(choose!=1 && choose!=2) cin>>choose;
    output = (choose==1);
    cout<<"\nChe tipo di test vuoi eseguire?"<<endl;
    cout<<"1. Test su casi limite (La dimensione massima delle strutture sara' impostata ad 1 in modo da forzare interazioni tra strutture vuote)"<<endl;
    cout<<"2. Test generale (L'esecuzione puo' apparire rallentata)"<<endl;
    cout<<"Inserisci l'opzione: ";
    choose = -1;
    while(choose!=1 && choose!=2) cin>>choose;
    if(choose==1){
        MAX_SIZE = 1;
    }else{
        MAX_SIZE = (output) ? 20 : 100;
    }
    uniform_int_distribution<int> select_genSize(MIN_SIZE,MAX_SIZE); genSize = select_genSize;
    uniform_int_distribution<int> select_genNum(MIN_NUM,MAX_NUM); genNum = select_genNum;

    cout<<"\nL'output sara' sospeso per velocizzare l'esecuzione se i test devono essere ripetuti piu' di 50 volte.";
    cout<<"\nInserisci il numero di iterazioni del test (consigliato 20): ";
    choose = -1;
    while(choose<0) cin>>choose;

    ITERAZIONI = choose;
    if(ITERAZIONI>50) output=false;
    bool total = true;

    // while(false){
    while(ITERAZIONI>0){
        
        //Operator==
        bool testEqualBT = false;
        bool testEqualBTVec = false;
        bool testEqualBTLnk = false;
        bool testEqualBST = false;

        //Assignement
        bool testAssBTVec = false;
        bool testAssBTLnk = false;
        bool testAssBST = false;
        bool testMAssBTVec = false;
        bool testMAssBTLnk = false;
        bool testMAssBST = false;

        //Constructor
        bool testCCBTLnk = false;
        bool testMCBTLnk = false;
        bool testCCBTVec = false;
        bool testMCBTVec = false;
        bool testCCBST = false;
        bool testMCBST = false;

        //Specific constructor (Non mutable)
        bool testSCBTLnkVec = false;
        bool testSCBTLnkLst = false;
        bool testSCBTVecVec = false;
        bool testSCBTVecLst = false;
        bool testSCBSTVec = false;
        bool testSCBSTLst = false;

        //Specific constructor (Mutable)
        bool testMSCBTLnkVec = false;
        bool testMSCBTLnkLst = false;
        bool testMSCBTVecVec = false;
        bool testMSCBTVecLst = false;
        bool testMSCBSTVec = false;
        bool testMSCBSTLst = false;

        //Specific functions
        bool testBSTMax = false;
        bool testBSTMin = false;
        bool testBSTSucc = false;
        bool testBSTPred = false;
        bool testInsertRemoveBST = false;

        //Iterators
        bool testPreOrdItrLnk = false;
        bool testPostOrdItrLnk = false;
        bool testInOrdItrLnk = false;
        bool testBreadthItrLnk = false;
        bool testPreOrdItrVec = false;
        bool testPostOrdItrVec = false;
        bool testInOrdItrVec = false;
        bool testBreadthItrVec = false;

        if(!output) cout<<"\nTesting comparison operators...";
        try { testEqualBT = TestEqualBT(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testEqualBTVec = TestEqualBTVec(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testEqualBTLnk = TestEqualBTLnk(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testEqualBST = TestEqualBST(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }

        if(!output) cout<<"\nTesting assignment operators...";
        try { testAssBTVec = TestAssBTVec(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testAssBTLnk = TestAssBTLnk(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testAssBST = TestAssBST(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }

        if(!output) cout<<"\nTesting move assignment operators...";
        try { testMAssBTVec = TestMAssBTVec(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testMAssBTLnk = TestMAssBTLnk(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testMAssBST = TestMAssBST(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }

        if(!output) cout<<"\nTesting constructors...";
        try { testCCBTLnk = CCBTLnk(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testCCBTVec = CCBTVec(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testCCBST = CCBST(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        
        if(!output) cout<<"\nTesting move constructors...";
        try { testMCBTLnk = MCBTLnk(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testMCBTVec = MCBTVec(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testMCBST = MCBST(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }

        if(!output) cout<<"\nTesting non-mutable specific constructors...";
        try { testSCBTLnkVec = SCBTLnkVec(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testSCBTLnkLst = SCBTLnkLst(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testSCBTVecVec = SCBTVecVec(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testSCBTVecLst = SCBTVecLst(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testSCBSTVec = SCBSTVec(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testSCBSTLst = SCBSTLst(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }

        if(!output) cout<<"\nTesting mutable specific constructors...";
        try { testMSCBTLnkVec = MSCBTLnkVec(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testMSCBTLnkLst = MSCBTLnkLst(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testMSCBTVecVec = MSCBTVecVec(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testMSCBTVecLst = MSCBTVecLst(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testMSCBSTVec = MSCBSTVec(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testMSCBSTLst = MSCBSTLst(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }

        if(!output) cout<<"\nTesting BST specific functions...";
        try { testBSTMax = TestBSTMax(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testBSTMin = TestBSTMin(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testBSTPred = TestBSTPred(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testBSTSucc = TestBSTSucc(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testInsertRemoveBST = TestInsertRemoveBST(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }

        if(!output) cout<<"\nTesting iterators...";
        try { testPreOrdItrLnk = TestPreOrdItrLnk(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testPostOrdItrLnk = TestPostOrdItrLnk(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testInOrdItrLnk = TestInOrdItrLnk(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testBreadthItrLnk = TestBreadthItrLnk(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testPreOrdItrVec = TestPreOrdItrVec(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testPostOrdItrVec = TestPostOrdItrVec(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testInOrdItrVec = TestInOrdItrVec(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testBreadthItrVec = TestBreadthItrVec(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }

        if(output) {
            cout<<"\n\n*********** RESULTS ***********"<<endl;

            cout<<"\nCOMPARISION OPERATORS:"<<endl;
            cout<<"BinaryTree == BinaryTree: "<<((testEqualBT) ? "Corretto" : "Errore")<<endl;
            cout<<"BinaryTreeLnk == BTLnk: "<<((testEqualBTLnk) ? "Corretto" : "Errore")<<endl;
            cout<<"BinaryTreeVec == BinaryTreeVec: "<<((testEqualBTVec) ? "Corretto" : "Errore")<<endl;
            cout<<"BinarySearchTree == BinarySearchTree: "<<((testEqualBST) ? "Corretto" : "Errore")<<endl;

            cout<<"\nASSIGNAMENT OPERATORS:"<<endl;
            cout<<"BinaryTreeLnk = BinaryTreeLnk: "<<((testAssBTLnk) ? "Corretto" : "Errore")<<endl;
            cout<<"BinaryTreeVec = BinaryTreeVec: "<<((testAssBTVec) ? "Corretto" : "Errore")<<endl;
            cout<<"BinarySearchTree = BinarySearchTree: "<<((testAssBST) ? "Corretto" : "Errore")<<endl;

            cout<<"\nMOVE ASSIGNAMENT OPERATORS:"<<endl;
            cout<<"BinaryTreeLnk = move(BinaryTreeLnk): "<<((testMAssBTLnk) ? "Corretto" : "Errore")<<endl;
            cout<<"BinaryTreeVec = move(BinaryTreeVec): "<<((testMAssBTVec) ? "Corretto" : "Errore")<<endl;
            cout<<"BinarySearchTree = move(BinarySearchTree): "<<((testMAssBST) ? "Corretto" : "Errore")<<endl;

            cout<<"\nCOPY CONSTRUCTORS: "<<endl;
            cout<<"BinaryTreeLnk(BinaryTreeLnk): "<<((testCCBTLnk) ? "Corretto" : "Errore")<<endl;
            cout<<"BinaryTreeVec(BinaryTreeVec): "<<((testCCBTVec) ? "Corretto" : "Errore")<<endl;
            cout<<"BinarySearchTree(BinarySearchTree): "<<((testCCBST) ? "Corretto" : "Errore")<<endl;

            cout<<"\nMOVE CONSTRUCTORS: "<<endl;
            cout<<"BinaryTreeLnk(move(BinaryTreeLnk)): "<<((testMCBTLnk) ? "Corretto" : "Errore")<<endl;
            cout<<"BinaryTreeVec(move(BinaryTreeVec)): "<<((testMCBTVec) ? "Corretto" : "Errore")<<endl;
            cout<<"BinarySearchTree(move(BinarySearchTree)): "<<((testMCBST) ? "Corretto" : "Errore")<<endl;
            
            cout<<"\nSPECIFIC NON-MUTABLE SPECIFIC CONSTRUCTORS: "<<endl;
            cout<<"BinaryTreeLnk(Vector): "<<((testSCBTLnkVec) ? "Corretto" : "Errore")<<endl;
            cout<<"BinaryTreeLnk(List): "<<((testSCBTLnkLst) ? "Corretto" : "Errore")<<endl;
            cout<<"BinaryTreeVec(Vector): "<<((testSCBTVecVec) ? "Corretto" : "Errore")<<endl;
            cout<<"BinaryTreeVec(List): "<<((testSCBTVecLst) ? "Corretto" : "Errore")<<endl;
            cout<<"BinarySearchTree(Vector): "<<((testSCBSTVec) ? "Corretto" : "Errore")<<endl;
            cout<<"BinarySearchTree(List): "<<((testSCBSTVec) ? "Corretto" : "Errore")<<endl;

            cout<<"\nSPECIFIC MUTABLE SPECIFIC CONSTRUCTORS: "<<endl;
            cout<<"BinaryTreeLnk(Vector): "<<((testMSCBTLnkVec) ? "Corretto" : "Errore")<<endl;
            cout<<"BinaryTreeLnk(List): "<<((testMSCBTLnkLst) ? "Corretto" : "Errore")<<endl;
            cout<<"BinaryTreeVec(Vector): "<<((testMSCBTVecVec) ? "Corretto" : "Errore")<<endl;
            cout<<"BinaryTreeVec(List): "<<((testMSCBTVecLst) ? "Corretto" : "Errore")<<endl;
            cout<<"BinarySearchTree(Vector): "<<((testMSCBSTVec) ? "Corretto" : "Errore")<<endl;
            cout<<"BinarySearchTree(List): "<<((testMSCBSTVec) ? "Corretto" : "Errore")<<endl;

            cout<<"\nBST SPECIFIC FUNCTIONS: "<<endl;
            cout<<"BST.Max(): "<<((testBSTMax) ? "Corretto" : "Errore")<<endl;
            cout<<"BST.Min(): "<<((testBSTMin) ? "Corretto" : "Errore")<<endl;
            cout<<"BST.Predecessor(): "<<((testBSTPred) ? "Corretto" : "Errore")<<endl;
            cout<<"BST.Successor(): "<<((testBSTSucc) ? "Corretto" : "Errore")<<endl;
            cout<<"BST.Insert/Remove(): "<<((testInsertRemoveBST) ? "Corretto" : "Errore")<<endl;

            cout<<"\nITERATORS: "<<endl;
            cout<<"PreOrderIterator(BTLnk): "<<((testPreOrdItrLnk) ? "Corretto" : "Errore")<<endl;
            cout<<"PostOrderIterator(BTLnk): "<<((testPostOrdItrLnk) ? "Corretto" : "Errore")<<endl;
            cout<<"InOrderIterator(BTLnk): "<<((testInOrdItrLnk) ? "Corretto" : "Errore")<<endl;
            cout<<"BreadthIterator(BTLnk): "<<((testBreadthItrLnk) ? "Corretto" : "Errore")<<endl;
            cout<<"PreOrderIterator(BTVec): "<<((testPreOrdItrVec) ? "Corretto" : "Errore")<<endl;
            cout<<"PostOrderIterator(BTVec): "<<((testPostOrdItrVec) ? "Corretto" : "Errore")<<endl;
            cout<<"InOrderIterator(BTVec): "<<((testInOrdItrVec) ? "Corretto" : "Errore")<<endl;
            cout<<"BreadthIterator(BTVec): "<<((testBreadthItrVec) ? "Corretto" : "Errore")<<endl;
        }

        if (testEqualBT && testEqualBTVec && testEqualBTLnk && testEqualBST && testAssBTVec &&
            testAssBTLnk && testAssBST && testMAssBTVec && testMAssBTLnk && testMAssBST &&
            testCCBTLnk && testMCBTLnk && testCCBTVec && testMCBTVec && testCCBST && testMCBST &&
            testSCBTLnkVec && testSCBTLnkLst && testSCBTVecVec && testSCBTVecLst && testSCBSTVec &&
            testSCBSTLst && testMSCBTLnkVec && testMSCBTLnkLst && testMSCBTVecVec && testMSCBTVecLst &&
            testMSCBSTVec && testMSCBSTLst && testBSTMax && testBSTPred && testBSTSucc && testPreOrdItrLnk &&
            testPostOrdItrLnk && testInOrdItrLnk && testBreadthItrLnk && testPreOrdItrVec &&
            testPostOrdItrVec && testInOrdItrVec && testBreadthItrVec && testInsertRemoveBST)
        {
            total&=true;
        } else {
            total&=false;
        }

        if(!total) break;

        if(ITERAZIONI==1){
            //Maps
            bool testMapsBTVec = true;
            bool testMapsBTLnk = true;
            bool testMapsBST = true;
            cout<<"\n\n*********** SEZIONE DI TEST STATICI ***********";
            cout<<"\nVuoi eseguire dei test per la verifica delle map? Sara' necessaria l'attenzione dell'utente."<<endl;
            cout<<"1. Voglio procedere con il test."<<endl;
            cout<<"2. No, voglio proseguire senza eseguire i test (Risulteranno superati)."<<endl;
            cout<<"Inserisci l'opzione: ";
            choose = -1;
            while(choose!=1 && choose!=2) cin>>choose;
            if(choose==1){
                MAX_SIZE = 10;
                MIN_SIZE = 6;
                MIN_NUM = -9;
                MAX_NUM = 9;
                uniform_int_distribution<int> select_genSize(MIN_SIZE,MAX_SIZE); genSize = select_genSize;
                uniform_int_distribution<int> select_genNum(MIN_NUM,MAX_NUM); genNum = select_genNum;
                try { testMapsBTLnk = TestMapsBTLnk(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
                try { testMapsBTVec = TestMapsBTVec(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
                try { testMapsBST = TestMapsBST(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
            }
            total&= (testMapsBTVec && testMapsBTLnk && testMapsBST);
        }

        ITERAZIONI--;
    }

    if(total){
        cout<<"\nTUTTI I TEST SONO STATI SUPERATI!! :D ";
    }else{
        cout<<"\nCi sono test che non sono stati superati :(";
    }

    cout<<endl;

    return true;
}



/************************************************************************************************



 *          INIZIO TEST SULLE HT



*************************************************************************************************/

bool StressTestOpen(){                   // Un test probabilmente inutile ma divertente
    bool correct=true;
    int num = 30000;
    lasd::HashTableOpnAdr<int> s1;
    cout<<endl;
    clock_t tStart = clock();
    for(int i{0}; i<num; i++){

        if(i%10000==0) std::cout << "\b\b\b\b\b\b\b\b\b\bLoading.. " << std::flush;    // Ahahahahahahaha thread?? ahahahahhaa
        
        if(i%10000==5000) std::cout << "\b\b\b\b\b\b\b\b\b\bLoading..." << std::flush;

        if(s1.Size()<5000){
            int in = genSize(gen);
            lasd::List<int> l1;
            for(int j{0}; j<in; j++) l1.Insert(genNum(gen));
            s1.InsertAll(l1);
            for(int j{0}; j<l1.Size(); j++) correct &= (s1.Exists(l1[j]));
        }
        
        int out = genSize(gen);
        lasd::List<int> l2;
        for(int j{0}; j<out; j++) l2.Insert(genNum(gen));
        s1.RemoveAll(l2);
        for(int j{0}; j<l2.Size(); j++) correct &= (!s1.Exists(l2[j]));
    }
    // cout<<"\nSize(): "<<s1.Size()<<"\tSizeVec: "<<s1.vecSize<<"\n"; s1.printTable();
    cout<<"\tTime taken (Open): "<<((double)(clock() - tStart)/CLOCKS_PER_SEC);
    return correct;
}

bool StressTestClose(){    // Un test probabilmente inutile ma divertente
    bool correct=true;
    int num = 30000;
    lasd::HashTableClsAdr<int> s1;
    cout<<endl;
    clock_t tStart = clock();
    for(int i{0}; i<num; i++){

        if(i%10000==0) std::cout << "\b\b\b\b\b\b\b\b\b\bLoading.. " << std::flush;    // Ahahahahahahaha thread?? ahahahahhaa
        
        if(i%10000==5000) std::cout << "\b\b\b\b\b\b\b\b\b\bLoading..." << std::flush;

        if(s1.Size()<5000){
            int in = genSize(gen);
            lasd::List<int> l1;
            for(int j{0}; j<in; j++) l1.Insert(genNum(gen));
            s1.InsertAll(l1);
            for(int j{0}; j<l1.Size(); j++) correct &= (s1.Exists(l1[j]));
        }
        
        int out = genSize(gen);
        lasd::List<int> l2;
        for(int j{0}; j<out; j++) l2.Insert(genNum(gen));
        s1.RemoveAll(l2);
        for(int j{0}; j<l2.Size(); j++) correct &= (!s1.Exists(l2[j]));
    }
    // cout<<"\nSize(): "<<s1.Size()<<"\tSizeVec: "<<s1.vecSize<<"\n"; s1.printTable();
    cout<<"\tTime taken (Close): "<<((double)(clock() - tStart)/CLOCKS_PER_SEC);
    return correct;
}

bool TestEqualHT(){
    if(output) cout<<"\n**********TEST TestEqualHT**********\n";
    bool correct=true;
    int temp_size = genSize(gen)+1;
    lasd::Vector<int> v1(temp_size);
    for(int i=0; i<temp_size; i++){
        int temp_num = genNum(gen);
        v1[i]=temp_num;
    } 
    lasd::HashTableClsAdr<int> s1(v1);
    lasd::HashTableOpnAdr<int> s2(v1);
    if(output) { 
        cout<<"\nS1: ";
        s1.printTable();
    }
    if(output) { 
        cout<<"\nS2: ";
        s2.printTable();
    }
    correct&=(s1.HashTable<int>::operator==(s2));
    v1[genSize(gen)%temp_size]=genNum(gen);
    lasd::HashTableOpnAdr<int> s3(v1);
    correct&=(s1.HashTable<int>::operator!=(s3));
    s1.Clear();
    s2.Clear();
    correct&=(s1.HashTable<int>::operator==(s2));
    return correct;
}

bool TestEqualHTOpen(){
    if(output) cout<<"\n**********TEST TestEqualHTOpen**********\n";
    bool correct=true;
    int temp_size = genSize(gen)+1;
    lasd::Vector<int> v1(temp_size);
    for(int i=0; i<temp_size; i++){
        int temp_num = genNum(gen);
        v1[i]=temp_num;
    } 
    lasd::HashTableOpnAdr<int> s1(v1);
    lasd::HashTableOpnAdr<int> s2(v1);
    v1[genSize(gen)%temp_size]=genNum(gen);
    lasd::HashTableOpnAdr<int> s3(v1);
    if(output) { 
        cout<<"\nS1: ";
        s1.printTable();
    }
    if(output) { 
        cout<<"\nS2: ";
        s2.printTable();
    }
        if(output) { 
        cout<<"\nS1: ";
        s1.printTable();
    }
    if(output) { 
        cout<<"\nS3: ";
        s2.printTable();
    }
    correct&=(s1==s2);
    correct&=(s1!=s3);
    s2.Clear();
    s2.Resize(0);
    correct&=(s1!=s2);
    s1.Clear();
    s1.Resize(0);
    correct&=(s1==s2);
    return correct;
}

bool TestEqualHTClose(){
    if(output) cout<<"\n**********TEST TestEqualHTClose**********\n";
    bool correct=true;
    int temp_size = genSize(gen)+1;
    lasd::Vector<int> v1(temp_size);
    for(int i=0; i<temp_size; i++){
        int temp_num = genNum(gen);
        v1[i]=temp_num;
    } 
    lasd::HashTableClsAdr<int> s1(v1);
    lasd::HashTableClsAdr<int> s2(v1);
    v1[genSize(gen)%temp_size]=genNum(gen);
    lasd::HashTableClsAdr<int> s3(v1);
    if(output) { 
        cout<<"\nS1: ";
        s1.printTable();
    }
    if(output) { 
        cout<<"\nS2: ";
        s2.printTable();
    }
        if(output) { 
        cout<<"\nS1: ";
        s1.printTable();
    }
    if(output) { 
        cout<<"\nS3: ";
        s2.printTable();
    }
    correct&=(s1==s2);
    correct&=(s1!=s3);
    s2.Clear();
    s2.Resize(0);
    correct&=(s1!=s2);
    s1.Clear();
    s1.Resize(0);
    correct&=(s1==s2);
    return correct;
}

bool TestAssHTOpen(){
    if(output) cout<<"\n**********TEST TestAssHTOpen**********\n";
    bool correct=true;
    int temp_size = genSize(gen);
    lasd::Vector<int> v1(temp_size);
    for(int i=0; i<temp_size; i++) v1[i]=genNum(gen);
    lasd::HashTableOpnAdr<int> s1(v1);
    lasd::HashTableOpnAdr<int> s2(v1);
    s2 = s1;
    if(output) { 
        cout<<"\nS1: ";
        s1.printTable();
    }
    if(output) { 
        cout<<"\nS2: ";
        s2.printTable();
    }
    correct&=(s1==s2);
    s2.Clear();
    s1.Clear();
    correct&=(s1==s2);
    return correct;
}

bool TestAssHTClose(){
    if(output) cout<<"\n**********TEST TestAssHTClose**********\n";
    bool correct=true;
    int temp_size = genSize(gen);
    lasd::Vector<int> v1(temp_size);
    for(int i=0; i<temp_size; i++) v1[i]=genNum(gen);
    lasd::HashTableClsAdr<int> s1(v1);
    lasd::HashTableClsAdr<int> s2;
    s2 = s1;
    if(output) { 
        cout<<"\nS1: ";
        s1.printTable();
    }
    if(output) { 
        cout<<"\nS2: ";
        s2.printTable();
    }
    correct&=(s1==s2);
    s2.Clear();
    s1.Clear();
    correct&=(s1==s2);
    return correct;
}

bool TestMAssHTOpen(){
    if(output) cout<<"\n**********TEST TestMAssHTOpen**********\n";
    bool correct=true;
    int temp_size1 = genSize(gen)+1;
    int temp_size2 = genSize(gen)+1;
    lasd::Vector<int> v1(temp_size1);
    lasd::Vector<int> v2(temp_size2);
    for(int i=0; i<v1.Size(); i++) v1[i]=genNum(gen);
    for(int i=0; i<v2.Size(); i++) v2[i]=genNum(gen);
    lasd::HashTableOpnAdr<int> s1(v1);
    if(output) { 
        cout<<"\nS1: ";
        s1.printTable();
    }
    lasd::HashTableOpnAdr<int> s2(v2);
    if(output) { 
        cout<<"\nS2: ";
        s2.printTable();
    }
    lasd::HashTableOpnAdr<int> s3(v1);
    lasd::HashTableOpnAdr<int> s4(v2);
    lasd::HashTableOpnAdr<int> s5;
    s2 = move(s1);
    correct&=(s1==s4);
    while(!s1.Insert(genNum(gen)));
    correct&=(s1!=s4);
    correct&=(s2==s3);
    s1 = move(s5);
    correct&=(s1.Empty());
    s2.Clear();
    correct&=(s1==s2);
    return correct;
}

bool TestMAssHTClose(){
    if(output) cout<<"\n**********TEST TestMAssHTClose**********\n";
    bool correct=true;
    int temp_size1 = genSize(gen)+1;
    int temp_size2 = genSize(gen)+1;
    lasd::Vector<int> v1(temp_size1);
    lasd::Vector<int> v2(temp_size2);
    for(int i=0; i<v1.Size(); i++) v1[i]=genNum(gen);
    for(int i=0; i<v2.Size(); i++) v2[i]=genNum(gen);
    lasd::HashTableClsAdr<int> s1(v1);
    if(output) { 
        cout<<"\nS1: ";
        s1.printTable();
    }
    lasd::HashTableClsAdr<int> s2(v2);
    if(output) { 
        cout<<"\nS2: ";
        s2.printTable();
    }
    lasd::HashTableClsAdr<int> s3(v1);
    lasd::HashTableClsAdr<int> s4(v2);
    lasd::HashTableClsAdr<int> s5;
    s2 = move(s1);
    correct&=(s1==s4);
    while(!s1.Insert(genNum(gen)));
    correct&=(s1!=s4);
    correct&=(s2==s3);
    s1 = move(s5);
    correct&=(s1.Empty());
    s2.Clear();
    correct&=(s1==s2);
    return correct;
}

bool TestCCHTOpen(){
    if(output) cout<<"\n**********TEST TestCCHTOpen**********\n";
    bool correct=true;
    lasd::Vector<int> v1(genSize(gen));
    for(ulong i=0; i<v1.Size(); i++) v1[i]=genNum(gen);
    lasd::HashTableOpnAdr<int> s1(v1);
    lasd::HashTableOpnAdr<int> s2(s1);
    if(output) { 
        cout<<"\nS1: ";
        s1.printTable();
    }
    if(output) { 
        cout<<"\nS2: ";
        s2.printTable();
    }
    correct&=(s1==s2);
    s1.Clear();
    correct&=(s1.Empty());
    s2.Clear();
    correct&=(s1==s2);
    return correct;
}

bool TestCCHTClose(){
    if(output) cout<<"\n**********TEST TestCCHTClose**********\n";
    bool correct=true;
    lasd::Vector<int> v1(genSize(gen));
    for(ulong i=0; i<v1.Size(); i++) v1[i]=genNum(gen);
    lasd::HashTableClsAdr<int> s1(v1);
    lasd::HashTableClsAdr<int> s2(s1);
    if(output) { 
        cout<<"\nS1: ";
        s1.printTable();
    }
    if(output) { 
        cout<<"\nS2: ";
        s2.printTable();
    }
    correct&=(s1==s2);
    s1.Clear();
    correct&=(s1.Empty());
    s2.Clear();
    correct&=(s1==s2);
    return correct;
}

bool TestMCHTOpen(){
    if(output) cout<<"\n**********TEST TestMCHTOpen**********\n";
    bool correct=true;
    int temp_size1 = genSize(gen);
    lasd::Vector<int> v1(temp_size1);
    for(int i=0; i<v1.Size(); i++) v1[i]=genNum(gen);
    lasd::HashTableOpnAdr<int> s1(v1);
    lasd::HashTableOpnAdr<int> s2(v1);
    lasd::HashTableOpnAdr<int> s3(move(s1));
    correct&=(s1.Empty());
    correct&=(s2==s3);
    s3.Clear();
    correct&=(s3.Empty());
    s2.Clear();
    correct&=(s3==s2);
    return correct;
}

bool TestMCHTClose(){
    if(output) cout<<"\n**********TEST TestMCHTClose**********\n";
    bool correct=true;
    int temp_size1 = genSize(gen);
    lasd::Vector<int> v1(temp_size1);
    for(int i=0; i<v1.Size(); i++) v1[i]=genNum(gen);
    lasd::HashTableClsAdr<int> s1(v1);
    lasd::HashTableClsAdr<int> s2(v1);
    lasd::HashTableClsAdr<int> s3(move(s1));
    correct&=(s1.Empty());
    correct&=(s2==s3);
    s3.Clear();
    correct&=(s3.Empty());
    s2.Clear();
    correct&=(s3==s2);
    return correct;
}

bool TestSCSizeHTOpen(){
    if(output) cout<<"\n**********TEST TestSCSizeHTOpen**********\n";
    bool correct=true;
    int temp_size = genSize(gen);
    lasd::List<int> l1;
    lasd::Vector<int> v1(temp_size);
    for(int i=0; i<temp_size; i++) {
        int temp_num = genNum(gen);
        v1[i]=temp_num;
        l1.Insert(temp_num);
    }
    lasd::HashTableOpnAdr<int> s1(genSize(gen));
    for(int i{0}; i<v1.Size(); i++){
        s1.Insert(v1[i]);
    }
    correct&=(s1.Size()==l1.Size());
    l1.Map(
        [&correct, &s1](const int& dat){
            correct&= s1.Exists(dat);
        }
    );
    return correct;
}

bool TestSCSizeHTClose(){
    if(output) cout<<"\n**********TEST TestSCSizeHTClose**********\n";
    bool correct=true;
    int temp_size = genSize(gen);
    lasd::List<int> l1;
    lasd::Vector<int> v1(temp_size);
    for(int i=0; i<temp_size; i++) {
        int temp_num = genNum(gen);
        v1[i]=temp_num;
        l1.Insert(temp_num);
    };
    lasd::HashTableClsAdr<int> s1(genSize(gen));
    for(int i{0}; i<v1.Size(); i++){
        s1.Insert(v1[i]);
    }
    correct&=(s1.Size()==l1.Size());
    l1.Map(
        [&correct, &s1](const int& dat){
            correct&= s1.Exists(dat);
        }
    );
    return correct;
}

bool TestSCHTOpenList(){
    if(output) cout<<"\n**********TEST TestSCHTOpenList**********\n";
    bool correct=true;
    int temp_size = genSize(gen);
    lasd::List<int> l1;
    lasd::Vector<int> v1(temp_size);
    for(int i=0; i<temp_size; i++) {
        int temp_num = genNum(gen);
        v1[i]=temp_num;
        l1.Insert(temp_num);
    };
    lasd::HashTableOpnAdr<int> s1(l1);
    for(int i{0}; i<v1.Size(); i++){
        correct&=(!(s1.Insert(v1[i])));
    }
    correct&=(s1.Size()==l1.Size());
    l1.Map(
        [&correct, &s1](const int& dat){
            correct&= s1.Exists(dat);
        }
    );
    return correct;
}

bool TestSCHTCloseList(){
    if(output) cout<<"\n**********TEST TestSCHTCloseList**********\n";
    bool correct=true;
    int temp_size = genSize(gen);
    lasd::List<int> l1;
    lasd::Vector<int> v1(temp_size);
    for(int i=0; i<temp_size; i++) {
        int temp_num = genNum(gen);
        v1[i]=temp_num;
        l1.Insert(temp_num);
    };
    lasd::HashTableClsAdr<int> s1(l1);
    for(int i{0}; i<v1.Size(); i++){
        correct&=(!(s1.Insert(v1[i])));
    }
    correct&=(s1.Size()==l1.Size());
    l1.Map(
        [&correct, &s1](const int& dat){
            correct&= s1.Exists(dat);
        }
    );
    return correct;
}

bool TestSCHTOpenVec(){
    if(output) cout<<"\n**********TEST TestSCHTOpenVec**********\n";
    bool correct=true;
    int temp_size = genSize(gen);
    lasd::List<int> l1;
    lasd::Vector<int> v1(temp_size);
    for(int i=0; i<temp_size; i++) {
        int temp_num = genNum(gen);
        v1[i]=temp_num;
        l1.Insert(temp_num);
    };
    lasd::HashTableOpnAdr<int> s1(v1);
    for(int i{0}; i<v1.Size(); i++){
        correct&=(!(s1.Insert(v1[i])));
    }
    correct&=(s1.Size()==l1.Size());
    l1.Map(
        [&correct, &s1](const int& dat){
            correct&= s1.Exists(dat);
        }
    );
    return correct;
}

bool TestSCHTCloseVec(){
    if(output) cout<<"\n**********TEST TestSCHTCloseVec**********\n";
    bool correct=true;
    int temp_size = genSize(gen);
    lasd::List<int> l1;
    lasd::Vector<int> v1(temp_size);
    for(int i=0; i<temp_size; i++) {
        int temp_num = genNum(gen);
        v1[i]=temp_num;
        l1.Insert(temp_num);
    };
    lasd::HashTableClsAdr<int> s1(v1);
    for(int i{0}; i<v1.Size(); i++){
        correct&=(!(s1.Insert(v1[i])));
    }
    correct&=(s1.Size()==l1.Size());
    l1.Map(
        [&correct, &s1](const int& dat){
            correct&= s1.Exists(dat);
        }
    );
    return correct;
}

bool TestMSCHTCloseVec(){
    if(output) cout<<"\n**********TEST TestMSCHTCloseVec**********\n";
    bool correct=true;
    int temp_size = genSize(gen);
    lasd::List<int> l1;
    lasd::Vector<int> v1(temp_size);
    for(int i=0; i<temp_size; i++) {
        int temp_num = genNum(gen);
        v1[i]=temp_num;
        l1.Insert(temp_num);
    };
    lasd::HashTableClsAdr<int> s1(move(v1));
    for(int i{0}; i<l1.Size(); i++){
        correct&=(!(s1.Insert(l1[i])));
    }
    correct&=(s1.Size()==l1.Size());
    l1.Map(
        [&correct, &s1](const int& dat){
            correct&= s1.Exists(dat);
        }
    );
    return correct;
}

bool TestMSCHTOpenVec(){
    if(output) cout<<"\n**********TEST TestMSCHTOpenVec**********\n";
    bool correct=true;
    int temp_size = genSize(gen);
    lasd::List<int> l1;
    lasd::Vector<int> v1(temp_size);
    for(int i=0; i<temp_size; i++) {
        int temp_num = genNum(gen);
        v1[i]=temp_num;
        l1.Insert(temp_num);
    };
    lasd::HashTableOpnAdr<int> s1(move(v1));
    for(int i{0}; i<l1.Size(); i++){
        correct&=(!(s1.Insert(l1[i])));
    }
    correct&=(s1.Size()==l1.Size());
    l1.Map(
        [&correct, &s1](const int& dat){
            correct&= s1.Exists(dat);
        }
    );
    return correct;
}

bool TestMSCHTCloseList(){
    if(output) cout<<"\n**********TEST TestMSCHTCloseList**********\n";
    bool correct=true;
    int temp_size = genSize(gen);
    lasd::List<int> l1;
    lasd::List<int> v1;
    for(int i=0; i<temp_size; i++) {
        int temp_num = genNum(gen);
        v1.InsertAtBack(temp_num);
        l1.Insert(temp_num);
    };
    lasd::HashTableClsAdr<int> s1(move(v1));
    for(int i{0}; i<l1.Size(); i++){
        correct&=(!(s1.Insert(l1[i])));
    }
    correct&=(s1.Size()==l1.Size());
    l1.Map(
        [&correct, &s1](const int& dat){
            correct&= s1.Exists(dat);
        }
    );
    return correct;
}

bool TestMSCHTOpenList(){
    if(output) cout<<"\n**********TEST TestMSCHTOpenList**********\n";
    bool correct=true;
    int temp_size = genSize(gen);
    lasd::List<int> l1;
    lasd::List<int> v1;
    for(int i=0; i<temp_size; i++) {
        int temp_num = genNum(gen);
        v1.InsertAtBack(temp_num);
        l1.Insert(temp_num);
    };
    lasd::HashTableOpnAdr<int> s1(move(v1));
    for(int i{0}; i<l1.Size(); i++){
        correct&=(!(l1.Insert(l1[i])));
    }
    correct&=(s1.Size()==l1.Size());
    l1.Map(
        [&correct, &s1](const int& dat){
            correct&= s1.Exists(dat);
        }
    );
    return correct;
}

bool davtest_ex3(){

    MIN_SIZE = 0;
    MAX_SIZE = 500;
    MIN_NUM = INT16_MIN;
    MAX_NUM = INT16_MAX;

    cout<<"\n\n*********** CONFIGURAZIONE DEI TEST: ***********"<<endl;
    cout<<"Necessiti degli output di debug?"<<endl;
    cout<<"1. Voglio visualizzare gli output di debug. (La dimensione delle strutture sara' ridotta)."<<endl;
    cout<<"2. No, voglio proseguire senza visualizzare gli output di debug. (Consigliato)"<<endl;
    cout<<"Inserisci l'opzione: ";
    int choose = -1;
    while(choose!=1 && choose!=2) cin>>choose;
    output = (choose==1);
    MAX_SIZE = (output) ? 20 : MAX_SIZE;
    uniform_int_distribution<int> select_genSize(MIN_SIZE,MAX_SIZE); genSize = select_genSize;
    uniform_int_distribution<int> select_genNum(MIN_NUM,MAX_NUM); genNum = select_genNum;

    cout<<"\nVuoi eseguire uno stress test sulle Exists() (L'esecuzione puo' apparire rallentata)?"<<endl;
    cout<<"1. Voglio eseguire lo stress test (Sconsigliato con Valgrind)."<<endl;
    cout<<"2. No voglio proseguire velocemente."<<endl;
    cout<<"Inserisci l'opzione: ";
    choose = -1;
    while(choose!=1 && choose!=2) cin>>choose;
    bool wantStressTest = (choose==1);
    bool total = true;

    int ITERAZIONI = 2;
        
    while(ITERAZIONI!=0) {
        
        cout<<"\n\n*********** TESTING "<<((ITERAZIONI==1) ? "LIMIT" : "GENERAL")<<" CASES ***********"<<endl;
        if(ITERAZIONI==1) cout<<"(La dimensione massima delle strutture e' impostata a 0)"<<endl;

        //Operator==
        bool testEqualHTOpen = false;
        bool testEqualHTClose = false;
        bool testEqualHT = false;

        //Assignement
        bool testAssHTOpen = false;
        bool testAssHTClose = false;
        bool testMAssHTOpen = false;
        bool testMAssHTClose = false;

        //Constructor
        bool testCCHTOpen = false;
        bool testMCHTOpen = false;
        bool testCCHTClose = false;
        bool testMCHTClose = false;

        //Specific constructor (Non mutable)
        bool testSCSizeHTOpen = false;
        bool testSCSizeHTClose = false;
        bool testSCHTOpenList = false;
        bool testSCHTCloseList = false;
        bool testSCHTOpenVec = false;
        bool testSCHTCloseVec = false;

        //Specific constructor (Mutable)
        bool testMSCHTOpenList = false;
        bool testMSCHTCloseList = false;
        bool testMSCHTOpenVec = false;
        bool testMSCHTCloseVec = false;

        //Specific functions
        bool stressTestOnExistsOpen = false;
        bool stressTestOnExistsClose = false;
        bool testResizeHTOpen = false;
        bool testResizeHTClose = false;


        cout<<"\nTesting "<<((ITERAZIONI==1) ? "limit" : "")<<" comparison operators...";
        try { testEqualHT = TestEqualHT(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testEqualHTOpen = TestEqualHTOpen(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testEqualHTClose = TestEqualHTClose(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }

        cout<<"\nTesting "<<((ITERAZIONI==1) ? "limit" : "")<<" assignment operators...";
        try { testAssHTOpen = TestAssHTOpen(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testAssHTClose = TestAssHTClose(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }

        cout<<"\nTesting "<<((ITERAZIONI==1) ? "limit" : "")<<" move assignment operators...";
        try { testMAssHTOpen = TestMAssHTOpen(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testMAssHTClose = TestMAssHTClose(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }

        cout<<"\nTesting "<<((ITERAZIONI==1) ? "limit" : "")<<" constructors...";
        try { testCCHTOpen = TestCCHTOpen(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testCCHTClose = TestCCHTClose(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }

        cout<<"\nTesting "<<((ITERAZIONI==1) ? "limit" : "")<<" move constructors...";
        try { testMCHTOpen = TestMCHTOpen(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testMCHTClose = TestMCHTClose(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        
        cout<<"\nTesting "<<((ITERAZIONI==1) ? "limit" : "")<<" non-mutable specific constructors..";
        try { testSCSizeHTOpen = TestSCSizeHTOpen(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testSCSizeHTClose = TestSCSizeHTClose(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testSCHTOpenList = TestSCHTOpenList(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testSCHTCloseList = TestSCHTCloseList(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testSCHTOpenVec = TestSCHTOpenVec(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testSCHTCloseVec = TestSCHTCloseVec(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }

        cout<<"\nTesting "<<((ITERAZIONI==1) ? "limit" : "")<<" mutable specific constructors...";
        try { testMSCHTOpenList = TestMSCHTOpenList(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testMSCHTCloseList = TestMSCHTCloseList(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testMSCHTOpenVec = TestMSCHTOpenVec(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        try { testMSCHTCloseVec = TestMSCHTCloseVec(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }

        if(wantStressTest){

            if(ITERAZIONI==2){
                uniform_int_distribution<int> select2_genSize(0,100); genSize = select2_genSize;
                uniform_int_distribution<int> select2_genNum(0,1000); genNum = select2_genNum;
            }

            cout<<"\nTesting "<<((ITERAZIONI==1) ? "limit" : "")<<" exists...";
            try { stressTestOnExistsOpen = StressTestOpen(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
            try { stressTestOnExistsClose = StressTestClose(); } catch (const std::exception& e) { std::cerr<<e.what()<<endl; }
        } else {
            stressTestOnExistsOpen = stressTestOnExistsClose = true;
        }

        uniform_int_distribution<int> select3_genSize(0,0); genSize = select3_genSize;

        cout<<"\n\n*********** RESULTS ***********"<<endl;

        cout<<"\nCOMPARISION OPERATORS:"<<endl;
        cout<<"HashTableOpnAdr == HashTableClsAdr: "<<((testEqualHT) ? "Corretto" : "Errore")<<endl;
        cout<<"HashTableOpnAdr == HashTableOpnAdr: "<<((testEqualHTOpen) ? "Corretto" : "Errore")<<endl;
        cout<<"HashTableClsAdr == HashTableClsAdr: "<<((testEqualHTClose) ? "Corretto" : "Errore")<<endl;

        cout<<"\nASSIGNAMENT OPERATORS:"<<endl;
        cout<<"HashTableOpnAdr = HashTableOpnAdr: "<<((testAssHTOpen) ? "Corretto" : "Errore")<<endl;
        cout<<"HashTableClsAdr = HashTableClsAdr: "<<((testAssHTClose) ? "Corretto" : "Errore")<<endl;

        cout<<"\nMOVE ASSIGNAMENT OPERATORS:"<<endl;
        cout<<"HashTableOpnAdr = move(HashTableOpnAdr): "<<((testMAssHTOpen) ? "Corretto" : "Errore")<<endl;
        cout<<"HashTableClsAdr = move(HashTableClsAdr): "<<((testMAssHTClose) ? "Corretto" : "Errore")<<endl;

        cout<<"\nCOPY CONSTRUCTORS: "<<endl;
        cout<<"HashTableOpnAdr(HashTableOpnAdr): "<<((testCCHTOpen) ? "Corretto" : "Errore")<<endl;
        cout<<"HashTableClsAdr(HashTableClsAdr): "<<((testCCHTClose) ? "Corretto" : "Errore")<<endl;

        cout<<"\nMOVE CONSTRUCTORS: "<<endl;
        cout<<"HashTableOpnAdr(move(HashTableOpnAdr)): "<<((testMCHTOpen) ? "Corretto" : "Errore")<<endl;
        cout<<"HashTableClsAdr(move(HashTableClsAdr)): "<<((testMCHTClose) ? "Corretto" : "Errore")<<endl;

        cout<<"\nNON-MUTABLE SPECIFIC CONSTRUCTORS: "<<endl;
        cout<<"HashTableOpnAdr(size): "<<((testSCSizeHTOpen) ? "Corretto" : "Errore")<<endl;
        cout<<"HashTableClsAdr(size): "<<((testSCSizeHTClose) ? "Corretto" : "Errore")<<endl;
        cout<<"HashTableOpnAdr(Vector): "<<((testSCHTOpenVec) ? "Corretto" : "Errore")<<endl;
        cout<<"HashTableOpnAdr(List): "<<((testSCHTOpenList) ? "Corretto" : "Errore")<<endl;
        cout<<"HashTableClsAdr(Vector): "<<((testSCHTCloseVec) ? "Corretto" : "Errore")<<endl;
        cout<<"HashTableClsAdr(List): "<<((testSCHTCloseList) ? "Corretto" : "Errore")<<endl;

        cout<<"\nMUTABLE SPECIFIC CONSTRUCTORS: "<<endl;
        cout<<"HashTableOpnAdr(Vector): "<<((testMSCHTOpenVec) ? "Corretto" : "Errore")<<endl;
        cout<<"HashTableOpnAdr(List): "<<((testMSCHTOpenList) ? "Corretto" : "Errore")<<endl;
        cout<<"HashTableClsAdr(Vector): "<<((testMSCHTCloseVec) ? "Corretto" : "Errore")<<endl;
        cout<<"HashTableClsAdr(List): "<<((testMSCHTCloseList) ? "Corretto" : "Errore")<<endl;

        cout<<"\nSTRESS TEST ON EXISTS: "<<endl;
        cout<<"HashTableOpnAdr: "<<((stressTestOnExistsOpen) ? "Corretto" : "Errore")<<endl;
        cout<<"HashTableClsAdr: "<<((stressTestOnExistsClose) ? "Corretto" : "Errore")<<endl;


        if (testEqualHTOpen &&
            testEqualHTClose &&
            testAssHTOpen &&
            testAssHTClose &&
            testMAssHTOpen &&
            testMAssHTClose &&
            testCCHTOpen &&
            testMCHTOpen &&
            testCCHTClose &&
            testMCHTClose &&
            testSCSizeHTOpen &&
            testSCSizeHTClose &&
            testSCHTOpenList &&
            testSCHTCloseList &&
            testSCHTOpenVec &&
            testSCHTCloseVec &&
            testMSCHTOpenList &&
            testMSCHTCloseList &&
            testMSCHTOpenVec &&
            testMSCHTCloseVec &&
            stressTestOnExistsOpen &&
            stressTestOnExistsClose &&
            testEqualHT
            // testResizeHTOpen &&
            // testResizeHTClose
            )
        {
            total &= true;
        } else {
            total &= false;
        }

        ITERAZIONI--;

    }

    if(total){
        cout<<"\nTUTTI I TEST SONO STATI SUPERATI!! :D ";
    }else{
        cout<<"\nCi sono test che non sono stati superati :(";
    }

    cout<<endl;

    return true;
}

#endif