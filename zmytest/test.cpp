#ifndef MYTEST_CPP
#define MYTEST_CPP

#include <iostream>
#include <random>
#include <stack>
#include <queue>

#include "test.hpp"

using namespace std;

int MIN_SIZE = 0;
int MAX_SIZE = 100;
int MIN_NUM INT16_MIN;
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
    // correct&=(v.LinearContainer<int>::operator!=(l));
    v.Clear();
    l.Clear();
    // correct&=(v.LinearContainer<int>::operator==(l));
    return correct;
}

bool TestEqualVector(){
    bool correct=true;
    int temp_size = genSize(gen)+1;
    lasd::Vector<int> v1(temp_size);
    lasd::Vector<int> v2(temp_size);
    for(int i=0; i<temp_size; i++) v2[i]=v1[i]=genNum(gen);
    correct&=(v1==v2);
    //LIMIT
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

bool davtest(){

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

#endif