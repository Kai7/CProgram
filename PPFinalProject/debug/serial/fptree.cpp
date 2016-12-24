#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <map>
#include <stack>
#include <cmath>
#include <iomanip>
#include <utility>
#include <time.h>

#include "fptree.h"

using std::ifstream;
using std::cout;
using std::endl;
using std::setw;
using std::stoi;
using std::ceil;
using std::make_pair;
using std::stack;

//using namespace std;

void showSupCounter(map<int, int> &mapSup);
void showHTable(map<int, fpnode*> *htable);
void showSupTransList(list<int> *trans, int sup);
void showTransList(vector<int> *trans);
void showTransList(list<int> *trans);

struct condminingInfo{
    fptree *cond_tree;
    list<int> *condtrans;
};

fptree::fptree(){
    root = new fpnode();
    htable = new map<int, fpnode*>();
    lasthtable = new map<int, fpnode*>();
    fpcounter = 0;
}

void fptree::mining(){
    clock_t tStart = clock();
    // collect each item in header table
    vector<pair<int, fpnode*> > fp;
    for (map<int, fpnode*>::iterator it = this->htable->begin();
         it != this->htable->end(); it++) {
        fp.push_back(make_pair(it->first, it->second));
    }

    miningInfo *arg = new miningInfo;
    arg->task_id = 0;
    arg->idx_front = 0;
    arg->idx_end = fp.size() - 1;
    arg->fp = &fp;

    miningInfo_helper *arg_helper = new miningInfo_helper;
    arg_helper->tree = this;
    arg_helper->info = arg;

    cout << "fp.size() = " << fp.size() << endl;

    int result = parallel_mining(arg_helper);

    this->fpcounter = result;
    // we will mining the condition tree for each item
    printf("mining time: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    cout << endl;
    cout << "===== FP-Growth Report ====================" << endl;
    cout << "Frequent Pattern count : " << this->fpcounter << endl;
    cout << "===========================================" << endl;
}

int fptree::parallel_mining(void *helper_arg){
    int counter = 0;
    fptree *main_fptree = ((miningInfo_helper *)helper_arg)->tree;
    miningInfo *mining_info = ((miningInfo_helper *)helper_arg)->info;

    int idx_front = mining_info->idx_front;
    int idx_end = mining_info->idx_end;
    vector<pair<int, fpnode*> > *fp = mining_info->fp;

    for (int i = idx_front; i <= idx_end; i++) {
        int item = (*fp)[i].first;
        //cout << "mining item: " << item << endl;
        counter += 1;
        int support = 0;
        fpnode *nxtPtr = (*fp)[i].second;

        // collect each transaction for this item
        list<pair<int, list<int> > > condTransList;

        map<int, int> condsupCounter;
        while (nxtPtr != nullptr) {
            int sup = nxtPtr->counter;
            support += sup;
            if (nxtPtr->parent->item != -1) {
                list<int> transList;

                fpnode *scanPtr = nxtPtr->parent;
                while (scanPtr->item != -1) {
                    transList.push_front(scanPtr->item);

                    map<int, int>::iterator it = condsupCounter.find(scanPtr->item);
                    if (it == condsupCounter.end()) {
                        condsupCounter[scanPtr->item] = sup;
                    } else {
                        it->second += sup;
                    }

                    scanPtr = scanPtr->parent;
                    if(scanPtr == nullptr){
                        cout << "nullptr error" << endl;
                    }
                }
                condTransList.push_back(make_pair(sup, transList));
            }
            nxtPtr = nxtPtr->nxt;
        }

        fptree *condtree = new fptree();
        condtree->minSupport = main_fptree->minSupport;

        list<pair<int, list<int> > >::iterator it = condTransList.begin();
        for (; it != condTransList.end(); it++) {
            int sup = it->first;
            condtree->addTrans(&(it->second), sup, &condsupCounter);
        }
        
        list<int> condtrans;
        condtrans.push_back(item);

        //showSupTransList(&condtrans, support);

        if(condtree->root->eldest == nullptr){
            continue;
        }

        stack<fptree*> condtree_stack;
        stack<map<int, fpnode*>::iterator> condhtptr_stack;

        condtree_stack.push(condtree);
        map<int, fpnode*>::iterator ht_it = condtree->htable->begin();
        condhtptr_stack.push(ht_it);
        //main_fptree->fpcounter += 1;

        //if(condtree->root->eldest != nullptr){
        //    miningCondTree(&condtrans, condtree);
        //    main_fptree->fpcounter += condtree->fpcounter;
        //}

        while(!condtree_stack.empty()){
            fptree *top_condtree = condtree_stack.top();
            map<int, fpnode*>::iterator top_ht_it = condhtptr_stack.top();
            condhtptr_stack.pop();
            if(top_ht_it == top_condtree->htable->end()){
                condtree_stack.pop();
                condtrans.pop_back();
                continue;
            }

            int p_item = top_ht_it->first;
            counter += 1;
            condtrans.push_back(p_item);
            int p_support = 0;
            fpnode *p_nxtPtr = top_ht_it->second;
            top_ht_it++;
            condhtptr_stack.push(top_ht_it);

            list<pair<int, list<int> > > p_condTransList;

            map<int, int> p_condsupCounter;
            while (p_nxtPtr != nullptr) {
                int p_sup = p_nxtPtr->counter;
                p_support += p_sup;
                if (p_nxtPtr->parent->item != -1) {
                    list<int> p_transList;

                    fpnode *p_scanPtr = p_nxtPtr->parent;
                    while (p_scanPtr->item != -1) {
                        p_transList.push_front(p_scanPtr->item);

                        map<int, int>::iterator p_it = p_condsupCounter.find(p_scanPtr->item);
                        if (p_it == p_condsupCounter.end()) {
                            p_condsupCounter[p_scanPtr->item] = p_sup;
                        } else {
                            p_it->second += p_sup;
                        }
                        p_scanPtr = p_scanPtr->parent;
                    }
                    p_condTransList.push_back(make_pair(p_sup, p_transList));
                }
                p_nxtPtr = p_nxtPtr->nxt;
            }

            fptree *p_condtree = new fptree();
            p_condtree->minSupport = top_condtree->minSupport;

            list<pair<int, list<int> > >::iterator p_itt = p_condTransList.begin();
            for (; p_itt != p_condTransList.end(); p_itt++) {
                int p_sup = p_itt->first;
                p_condtree->addTrans(&(p_itt->second), p_sup, &p_condsupCounter);
            }

            //showSupTransList(&condtrans, p_support);
            //condtree->fpcounter += 1;

            if(p_condtree->root->eldest == nullptr){
                condtrans.pop_back();
                continue;
            }

            condtree_stack.push(p_condtree);
            map<int, fpnode*>::iterator p_ht_it = p_condtree->htable->begin();
            condhtptr_stack.push(p_ht_it);

        }
    }
    return counter;
}

void fptree::buildTree(string transFile, double minsup) {
    ifstream fin;
    fin.open(transFile.c_str());

    if (!fin | minsup <= 0 | minsup >= 1 ) {
        cout << "error !" << endl;
        return;
    };

    clock_t tStart = clock();
    // scan the input database first to calculate the support of each item.
    map<int, int> supCounter;
    int transCounter = 0;

    string delimiter = ", ";
    size_t pos = 0;

    string line, token;
    int item;
    map<int,int>::iterator it;
    while (getline(fin, line)) {
        transCounter += 1;
        while ((pos = line.find(delimiter)) != string::npos) {
            token = line.substr(0, pos);
            item = std::stoi(token);
            it = supCounter.find(item);
            if (it == supCounter.end())
                supCounter[item] = 1;
            else
                it->second += 1;
            line.erase(0, pos + delimiter.length());
        }
        item = std::stoi(line);
        it = supCounter.find(item);
        if (it == supCounter.end())
            supCounter[item] = 1;
        else
            it->second += 1;
    }
    printf("scan first time: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    tStart = clock();
    // set min sup for fp-tree
    this->minSupport = (int)ceil(minsup * transCounter);

    // scan the input database second and build fp-tree.
    fin.clear();
    fin.seekg(0, fin.beg);

    while (getline(fin, line)) {
        vector<int> *transList = new vector<int>;
        while ((pos = line.find(delimiter)) != string::npos) {
            token = line.substr(0, pos);
            item = std::stoi(token);
            it = supCounter.find(item);
            if (it == supCounter.end()){
                cout << "error ..." << endl;
                return;
            }
            if (it->second >= this->minSupport){
                transList->push_back(it->first);
            }
            line.erase(0, pos + delimiter.length());
        }
        item = std::stoi(line);
        it = supCounter.find(item);
        if (it == supCounter.end()){
            cout << "error ..." << endl;
            return;
        }
        if (it->second >= this->minSupport){
            transList->push_back(it->first);
        }

        // sort item in the transaction by descending order of support
        sortTrans(transList, &supCounter, 0, transList->size() - 1);

        // add the sorted transaction to the fptree
        this->addTrans(transList);

        transList->clear();
    }
    printf("build tree time: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    cout << "building fptree complete!" << endl;

    return;
}

// add a transaction to fp-tree by specific support
void fptree::addTrans(list<int> *trans, int sup, map<int, int> *mapSup){
    // top-down insert pointer
    fpnode *currentNode = this->root;

    // for each item in this transaction
    list<int>::iterator it = trans->begin();
    for(; it != trans->end(); it++){
        // get this item number
        int item = (*it);

        // find the support of this item
        map<int, int>::iterator itt = mapSup->find(item);
        // if the support is less than min sup, we will ignore it
        if(itt->second < this->minSupport)
            continue;

        // if currentNode has no child, we will create a node to it as a child,
        if (currentNode->eldest == nullptr){
            fpnode *newNode = new fpnode();
            newNode->item = item;
            newNode->counter = sup;
            newNode->parent = currentNode;
            currentNode->eldest = newNode;
            updateHTable(newNode);

            currentNode = newNode;
            continue;
        }

        // let seachNode be the first child of currentNode
        fpnode *searchNode = currentNode->eldest;
        // if the item of searchNode is actually the same as insert item, we just need to add its sup
        if (searchNode->item == item){
            searchNode->counter += sup;
            currentNode = searchNode;

            continue;
        }

        // linear search the children of currentNode, and chech if the insert item is among them
        bool flag = false;
        while (searchNode->sibling != nullptr) {
            // if the insert item is among the children, we just need to add its sup
            if (searchNode->sibling->item == item){
                searchNode->sibling->counter += sup;

                flag = true;
                currentNode = searchNode->sibling;
                break;
            }
            searchNode = searchNode->sibling;
        }
        if(flag) continue;

        // if the insert item is not among the children, we will create a node to it as a child,
        fpnode *newNode = new fpnode();
        newNode->item = item;
        newNode->counter = sup;
        newNode->parent = currentNode;
        searchNode->sibling = newNode;
        updateHTable(newNode);

        currentNode = newNode;
    }

    return;
}

// add a transaction to fp-tree
void fptree::addTrans(vector<int> *trans) {
    // top-down insert pointer
    fpnode *currentNode = this->root;

    // for each item in this transaction
    for (int i = 0; i < trans->size(); i++) {
        // get this item number
        int item = (*trans)[i];

        // if currentNode has no child, we will create a node to it as a child,
        if (currentNode->eldest == nullptr){
            fpnode *newNode = new fpnode();
            newNode->item = item;
            newNode->counter = 1;
            newNode->parent = currentNode;
            currentNode->eldest = newNode;
            updateHTable(newNode);

            currentNode = newNode;
            continue;
        }

        // let seachNode be the first child of currentNode
        fpnode *searchNode = currentNode->eldest;
        // if the item of searchNode is actually the same as insert item, we just need to add its sup
        if (searchNode->item == item){
            searchNode->counter++;

            currentNode = searchNode;
            continue;
        }
        // linear search the children of currentNode, and chech if the insert item is among them
        bool flag = false;
        while (searchNode->sibling != nullptr) {
            // if the insert item is among the children, we just need to add its sup
            if (searchNode->sibling->item == item){
                searchNode->sibling->counter++;

                flag = true;
                currentNode = searchNode->sibling;
                break;
            }
            searchNode = searchNode->sibling;
        }
        if(flag) continue;
        
        // if the insert item is not among the children, we will create a node to it as a child,
        fpnode *newNode = new fpnode();
        newNode->item = item;
        newNode->counter = 1;
        newNode->parent = currentNode;
        searchNode->sibling = newNode;
        updateHTable(newNode);

        currentNode = newNode;
    }

    return;
}

int fptree::compareItem(int it1, int it2, map<int, int> *mapSup){
    int compare = (*mapSup)[it1] - (*mapSup)[it2];

    if(compare == 0)
        compare = it2 - it1;
    return compare;
}

void fptree::sortTrans(vector<int> *trans, map<int, int> *mapSup){

}

void fptree::sortTrans(vector<int> *trans, map<int, int> *mapSup, int front, int rear){
    if(rear <= front)
       return;
    
    int pivot = (*trans)[front];
    int l = front;
    int c = front + 1;
    
    int tmp;
    while(c <= rear){
        if(compareItem(pivot, (*trans)[c], mapSup) < 0){
            tmp = (*trans)[c];
            l++;
            (*trans)[c] = (*trans)[l];
            (*trans)[l] = tmp;
        }
        c++;
    }
    tmp = (*trans)[l];
    (*trans)[l] = pivot;
    (*trans)[front] = tmp;

    sortTrans(trans, mapSup, front, l-1);
    sortTrans(trans, mapSup, l+1, rear);

    return;
}

void fptree::updateHTable(fpnode *nnode){
    int item = nnode->item;

    map<int, fpnode*>::iterator it;
    it = this->lasthtable->find(item);
    if(it == this->lasthtable->end()){
        (*this->htable)[item] = nnode;
        (*this->lasthtable)[item] = nnode;
    }
    else{
        (*this->lasthtable)[item]->nxt = nnode;
        (*this->lasthtable)[item] = nnode;
    }

}

void showSupCounter(map<int, int> &mapSup){
    cout << setw(8) << "Item" << "|" << setw(8) << "Support" << endl;
    cout << setw(8) << "--------" << "+" << setw(8) << "--------" << endl;
    for(map<int, int>::iterator it = mapSup.begin(); it != mapSup.end(); it++){
        cout << setw(8) <<  it->first << "| " << setw(8) << it->second << endl;
    }

}

void showHTable(map<int, fpnode*> *htable){
    for(map<int, fpnode*>::iterator it = htable->begin(); it != htable->end(); it++){
        fpnode *scanPtr = it->second;
        cout << setw(6) << it->first << " -> " << scanPtr->item << ":" << scanPtr->counter << endl;
        while((scanPtr = scanPtr->nxt) != nullptr){
            cout << "       -> " << scanPtr->item << ":" << scanPtr->counter << endl;
        }
    }
}

void showSupTransList(list<int> *trans, int sup){
    cout << "< " ;
    showTransList(trans);
    cout << " : " << sup << " >" << endl;
}

void showTransList(vector<int> *trans) {
    cout << "[ ";
    for (int i = 0; i < trans->size() - 1; i++) {
        cout << (*trans)[i] << ", ";
    }
    cout << (*trans)[trans->size() - 1] << " ]";
}

void showTransList(list<int> *trans) {
    list<int>::iterator it = trans->begin();
    cout << "[ ";
    for(;it != --trans->end(); it++){
        cout << *it << ", ";
    }
    cout << (*it) << " ] ";
}
