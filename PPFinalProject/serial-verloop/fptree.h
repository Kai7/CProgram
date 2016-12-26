#include <string>
#include <cstddef>
#include <list>
#include <vector>
#include <map>

#define nullptr NULL

using std::list;
using std::map;
using std::string;
using std::vector;
using std::pair;

struct fpnode {
    int item;
    int counter;
    struct fpnode *parent;
    struct fpnode *eldest;
    struct fpnode *sibling;
    struct fpnode *nxt;

    fpnode(){
        item = -1;
        counter = 0;
        parent = eldest = sibling = nxt = nullptr;
    }
};

struct miningInfo{
    int task_id;
    int idx_front;
    int idx_end;
    vector<pair<int, fpnode*> > *fp;
};

class fptree{
public:
    fptree();
    void mining();
    void buildTree(string transFile, double minsup);
    int getFPCount();

private:
    struct fpnode *root;
    map<int, struct fpnode*> *htable;
    map<int, struct fpnode*> *lasthtable;
    int minSupport;
    int fpcounter;

    static int parallel_mining(void *helper_arg);
    void parallel(miningInfo *mining_info);
    void miningCondTree(list<int> *condtrans, fptree *condtree);
    void addTrans(vector<int> *trans);
    void addTrans(list<int> *trans, int sup, map<int, int> *mapSup);
    void sortTrans(vector<int> *trans, map<int, int> *mapSup);
    void sortTrans(vector<int> *trans, map<int, int> *mapSup, int front, int rear);
    fpnode* getPtrWithChildID(fpnode *parent, int item);
    int compareItem(int it1, int it2, map<int, int> *mapSup);
    void updateHTable(fpnode *nnode);
};

struct miningInfo_helper{
    fptree *tree;
    miningInfo *info;
};
