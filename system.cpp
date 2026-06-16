#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <climits>

//for colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

using namespace std;

// Represents a computer in the distributed cluster
// Stores total and available memory information
class ComputerNode
{
public:
    int computerID;
    int totalMemory;
    int freeMemory;

    ComputerNode()
    {
        computerID = 0;
        totalMemory = 0;
        freeMemory = 0;
    }

    ComputerNode(int id, int memory)
    {
        computerID = id;
        totalMemory = memory;
        freeMemory = memory;
    }
};

// Represents a memory block stored in a computer
// Each block has an ID, size and storage location
class MemoryBlock
{
public:
    int blockID;
    int size;
    int frequency;
    int storedComputer;

    MemoryBlock()
    {
        blockID = 0;
        size = 0;
        frequency = 0;
        storedComputer = 0;
    }

    MemoryBlock(int id, int s, int comp)
    {
        blockID = id;
        size = s;
        storedComputer = comp;
        frequency = 0;
    }
};

// Represents a memory access request
// Requests are processed using FIFO order
class Request
{
public:
    int requestID;
    int computerID;
    int blockID;

    Request()
    {
        requestID = 0;
        computerID = 0;
        blockID = 0;
    }

    Request(int rid, int cid, int bid)
    {
        requestID = rid;
        computerID = cid;
        blockID = bid;
    }
};

// Stores movement history of memory blocks
// Used for Undo/Rollback functionality
class Operation
{
public:
    int blockID;
    int oldComputer;
    int newComputer;

    Operation(int b, int oldC, int newC)
    {
        blockID = b;
        oldComputer = oldC;
        newComputer = newC;
    }
};

// Stack used for rollback operations
// Last move is undone first (LIFO)
stack<Operation> rollbackStack;

// Saves block movement details into the stack
void saveOperation(int blockID,
                   int oldComputer,
                   int newComputer)
{
    rollbackStack.push(
        Operation(blockID,
                  oldComputer,
                  newComputer));
}


// AVL Tree node storing a memory block
// AVL Tree provides fast searching and insertion
class AVLNode
{
public:
    MemoryBlock block;

    AVLNode* left;
    AVLNode* right;

    int height;

    AVLNode(MemoryBlock b)
    {
        block = b;

        left = NULL;
        right = NULL;

        height = 1;
    }
};

// Returns height of an AVL node
int getHeight(AVLNode* node)
{
    if(node == NULL)
        return 0;

    return node->height;
}

// Calculates AVL balance factor
int getBalance(AVLNode* node)
{
    if(node == NULL)
        return 0;

    return getHeight(node->left)
           -
           getHeight(node->right);
}

// Performs right rotation to balance AVL Tree
AVLNode* rightRotate(AVLNode* y)
{
    AVLNode* x = y->left;

    AVLNode* T2 = x->right;

    x->right = y;

    y->left = T2;

    y->height =
        max(getHeight(y->left),
            getHeight(y->right))
            + 1;

    x->height =
        max(getHeight(x->left),
            getHeight(x->right))
            + 1;

    return x;
}

// Performs left rotation to balance AVL Tree
AVLNode* leftRotate(AVLNode* x)
{
    AVLNode* y = x->right;

    AVLNode* T2 = y->left;

    y->left = x;

    x->right = T2;

    x->height =
        max(getHeight(x->left),
            getHeight(x->right))
            + 1;

    y->height =
        max(getHeight(y->left),
            getHeight(y->right))
            + 1;

    return y;
}

// Inserts a memory block into AVL Tree
// Tree is rebalanced if required
AVLNode* insertAVL(
    AVLNode* root,
    MemoryBlock block)
{
    if(root == NULL)
        return new AVLNode(block);

    if(block.blockID <
       root->block.blockID)
    {
        root->left =
            insertAVL(root->left,
                      block);
    }

    else if(block.blockID >
            root->block.blockID)
    {
        root->right =
            insertAVL(root->right,
                      block);
    }

    else
    {
        return root;
    }

    root->height =
        1 +
        max(getHeight(root->left),
            getHeight(root->right));

    int balance =
        getBalance(root);

    if(balance > 1 &&
       block.blockID <
       root->left->block.blockID)
    {
        return rightRotate(root);
    }

    if(balance < -1 &&
       block.blockID >
       root->right->block.blockID)
    {
        return leftRotate(root);
    }

    if(balance > 1 &&
       block.blockID >
       root->left->block.blockID)
    {
        root->left =
            leftRotate(root->left);

        return rightRotate(root);
    }

    if(balance < -1 &&
       block.blockID <
       root->right->block.blockID)
    {
        root->right =
            rightRotate(root->right);

        return leftRotate(root);
    }

    return root;
}

// Searches a memory block using Block ID
AVLNode* searchAVL(
        AVLNode* root,
        int blockID)
{
    if(root == NULL)
        return NULL;

    if(root->block.blockID ==
       blockID)
    {
        return root;
    }

    if(blockID <
       root->block.blockID)
    {
        return searchAVL(
                root->left,
                blockID);
    }

    return searchAVL(
            root->right,
            blockID);
}

// Displays memory blocks in sorted order
void inorder(AVLNode* root)
{
    if(root == NULL)
        return;

    inorder(root->left);

    cout<< GREEN << "Block ID : " << RESET
        <<root->block.blockID
        << GREEN << " | Size : " << RESET
        <<root->block.size
        << GREEN << " | Stored At : " << RESET
        <<root->block.storedComputer
        <<endl;

    inorder(root->right);
}

// Root node of AVL Tree
AVLNode* memoryRoot = NULL;

// Searches and displays memory block details
void searchMemoryBlock()
{
    int id;

    cout<<"Enter Block ID : ";
    cin>>id;

    AVLNode* result =
        searchAVL(
            memoryRoot,
            id);

    if(result == NULL)
    {
        cout<<RED<<"Not Found\n"<<RESET;
    }
    else
    {
        cout<<GREEN<<"\nBlock Found\n"<<RESET;

        cout<< GREEN << "Size : " << RESET
            <<result->block.size
            <<endl;

        cout<< GREEN << "Stored At Computer : " << RESET
            <<result->block.storedComputer
            <<endl;
    }
}

// Hash table storing all computers
// Provides fast computer lookup
unordered_map<int, ComputerNode> computers;

// Adds a new computer to the cluster
void addComputer()
{
    int id;
    int memory;

    cout << "Computer ID : ";
    cin >> id;

    cout << "Total Memory : ";
    cin >> memory;

    if(computers.find(id) != computers.end())
{
    cout<<RED<<"Computer ID Already Exists\n"<<RESET;
    return;
}

    computers[id] =
        ComputerNode(id,memory);

    cout<<GREEN<<"Computer Added Successfully\n"<<RESET;
}

// Verifies whether a computer exists
void verifyComputer()
{
    int id;

    cout << "Enter Computer ID : ";
    cin >> id;

    if(computers.find(id)
        != computers.end())
    {
        cout << GREEN << "\nComputer Found\n"<< RESET;

        cout << "ID : "
             << computers[id].computerID
             << endl;

        cout << "Free Memory : "
             << computers[id].freeMemory
             << endl;
    }
    else
    {
        cout<<RED<<"Computer Not Found\n"<<RESET;
    }
}

// Stores access frequency information
// Used by the priority queue
class FrequencyNode
{
public:

    int frequency;
    int blockID;

    FrequencyNode(
        int f,
        int b)
    {
        frequency = f;
        blockID = b;
    }

    bool operator<
    (
        const FrequencyNode& other
    ) const
    {
        return frequency <
               other.frequency;
    }
};

// Max Heap storing most accessed blocks
priority_queue<
    FrequencyNode
> frequencyHeap;

// Queue storing pending memory requests
// First request added is processed first
queue<Request> requestQueue;

// Adds a new request into the queue
void addRequest(int rid,
                int cid,
                int bid)
{
    // Check if computer exists
    if(computers.find(cid)
       == computers.end())
    {
        cout<<RED
            <<"Computer Not Found\n"
            <<RESET;

        return;
    }

    // Check if block exists
    if(searchAVL(memoryRoot,bid)
       == NULL)
    {
        cout<<RED
            <<"Memory Block Not Found\n"
            <<RESET;

        return;
    }

    requestQueue.push(
        Request(rid,cid,bid));

    cout<<GREEN
        <<"Request Added\n"
        <<RESET;
}

//Process Request

// Processes the oldest request from the queue
void processRequest()
{
    if(requestQueue.empty())
    {
        cout<<RED
            <<"No Pending Requests\n"
            <<RESET;

        return;
    }

    Request r =
        requestQueue.front();

    requestQueue.pop();

    AVLNode* block =
        searchAVL(memoryRoot,
                  r.blockID);

    if(block == NULL)
    {
        cout<<RED
            <<"Memory Block Missing\n"
            <<RESET;

        return;
    }

    // Increase access frequency
    block->block.frequency++;

    frequencyHeap.push(
        FrequencyNode(
            block->block.frequency,
            block->block.blockID
        )
    );

    cout<<CYAN
        <<"\nProcessing Request\n"
        <<RESET;

    cout<<YELLOW
        <<"Request ID : "
        <<RESET
        <<r.requestID
        <<endl;

    cout<<YELLOW
        <<"Computer ID : "
        <<RESET
        <<r.computerID
        <<endl;

    cout<<YELLOW
        <<"Block ID : "
        <<RESET
        <<r.blockID
        <<endl;

    cout<<GREEN
        <<"\nAccess Granted\n"
        <<RESET;

    cout<<"Computer "
        <<r.computerID
        <<" accessed Block "
        <<r.blockID
        <<endl;

    cout<<"Block Stored At Computer "
        <<block->block.storedComputer
        <<endl;

    cout<<"Access Frequency : "
        <<block->block.frequency
        <<endl;
}

// Records block access and updates frequency
void accessMemoryBlock()
{
    int id;

    cout << "Enter Block ID : ";
    cin >> id;

    AVLNode* block =
        searchAVL(memoryRoot,id);

    if(block == NULL)
    {
        cout<<RED<<"Block Not Found\n"<<RESET;
        return;
    }

    block->block.frequency++;

    frequencyHeap.push(
        FrequencyNode(
            block->block.frequency,
            id
        )
    );

    cout<<GREEN<<"Access Recorded\n"<<RESET;
}

// Displays blocks with highest access frequency
void showMostUsedBlocks()
{
    if(frequencyHeap.empty())
    {
        cout<<YELLOW<<"No Access Data\n"<<RESET;
        return;
    }

    priority_queue<
        FrequencyNode
    > temp = frequencyHeap;

    cout<<MAGENTA<<"\nTop Accessed Blocks\n"<<RESET;

    int count = 0;

    while(!temp.empty()
          && count < 10)
    {
        FrequencyNode current =
            temp.top();

        temp.pop();

        cout
        << "Block "
        << current.blockID << endl
        << " Frequency "
        << current.frequency
        << endl;

        count++;
    }
}

// Graph representing network topology
// Nodes = Computers, Edges = Connections
unordered_map<
    int,
    vector<pair<int,int>>
> graph;

// Creates a network connection between computers
void addConnection()
{
    int source;
    int destination;
    int latency;

    cout<<"Source Computer : ";
    cin>>source;

    cout<<"Destination Computer : ";
    cin>>destination;

    cout<<"Latency : ";
    cin>>latency;

    graph[source].push_back(
        {destination,latency});

    graph[destination].push_back(
        {source,latency});

    cout<<GREEN<<"Connection Added\n"<<RESET;
}

// Displays all computer connections
void displayNetwork()
{
    cout<<MAGENTA<<"\nCluster Topology\n"<<RESET;

    for(auto node : graph)
    {
        cout
        << node.first
        << " -> ";

        for(auto neighbour :
            node.second)
        {
            cout
            << "("
            << neighbour.first
            << ","
            << neighbour.second
            << ") ";
        }

        cout<<endl;
    }
}

// Uses Dijkstra Algorithm to find minimum latency path
void shortestPath()
{
    int source;
    int destination;

    cout<<"Source : ";
    cin>>source;

    cout<<"Destination : ";
    cin>>destination;

    unordered_map<int,int> distance;

    for(auto node : graph)
    {
        distance[node.first] =
            INT_MAX;
    }

    priority_queue
    <
        pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>
    > pq;

    distance[source] = 0;

    pq.push({0,source});

    while(!pq.empty())
    {
        int currentDistance =
            pq.top().first;

        int currentNode =
            pq.top().second;

        pq.pop();

        for(auto neighbour :
            graph[currentNode])
        {
            int nextNode =
                neighbour.first;

            int weight =
                neighbour.second;

            if(currentDistance
               + weight
               <
               distance[nextNode])
            {
                distance[nextNode]
                =
                currentDistance
                + weight;

                pq.push(
                {
                    distance[nextNode],
                    nextNode
                });
            }
        }
    }

    if(distance[destination]
       == INT_MAX)
    {
        cout<<RED<<"No Path Found\n"<<RESET;
    }
    else
    {
        cout << GREEN 
        << "\nMinimum Latency = "
        << distance[destination]
        << endl << RESET;
    }
}

// Allocates memory using Best Fit strategy
// Chooses computer with minimum memory waste
void allocateMemory()
{
    int blockID;
    int blockSize;

    cout<<"Block ID : ";
    cin>>blockID;

    if(searchAVL(memoryRoot,blockID) != NULL)
{
    cout<<RED<<"Block ID Already Exists\n"<<RESET;
    return;
}

    cout<<"Block Size : ";
    cin>>blockSize;

    int bestComputer = -1;
    int minimumWaste = INT_MAX;

    for(auto &computer : computers)
    {
        int freeSpace =
            computer.second.freeMemory;

        if(freeSpace >= blockSize)
        {
            int waste =
                freeSpace - blockSize;

            if(waste < minimumWaste)
            {
                minimumWaste = waste;
                bestComputer =
                    computer.first;
            }
        }
    }

    if(bestComputer == -1)
    {
        cout<<RED<<"No Computer Has Enough Memory\n"<<RESET;
        return;
    }

    computers[bestComputer].freeMemory
        -= blockSize;

    MemoryBlock block(
        blockID,
        blockSize,
        bestComputer);

    memoryRoot =
        insertAVL(memoryRoot,
                  block);

    cout<<GREEN << "\nAllocated To Computer "
        <<bestComputer
        <<endl<< RESET;
}

// Moves a memory block to another computer
// Movement is saved for rollback
void moveBlock()
{
    int blockID;
    int newComputer;

    cout<<"Block ID : ";
    cin>>blockID;

    cout<<"New Computer ID : ";
    cin>>newComputer;

    AVLNode* block =
        searchAVL(memoryRoot,
                  blockID);

    if(block == NULL)
    {
        cout<<RED<<"Block Not Found\n"<<RESET;
        return;
    }

    if(computers.find(newComputer)
       == computers.end())
    {
        cout<<RED <<"Computer Not Found\n"<< RESET;
        return;
    }

    if(computers[newComputer].freeMemory < block->block.size)
{
    cout<<RED
        <<"Not Enough Memory In Destination Computer\n"
        <<RESET;

    return;
}

   int oldComputer =
    block->block.storedComputer;

// Release memory from old computer
computers[oldComputer].freeMemory
    += block->block.size;

// Consume memory in new computer
computers[newComputer].freeMemory
    -= block->block.size;

saveOperation(
    blockID,
    oldComputer,
    newComputer);

    block->block.storedComputer =
    newComputer;

    cout<<GREEN<<"Block Moved Successfully\n"<<RESET;
}

// Restores the most recent block movement
void undoOperation()
{
    if(rollbackStack.empty())
    {
        cout<<YELLOW<<"Nothing To Undo\n"<<RESET;
        return;
    }

    Operation op =
        rollbackStack.top();

    rollbackStack.pop();

    AVLNode* block =
        searchAVL(memoryRoot,
                  op.blockID);

if(block != NULL)
{
    computers[op.newComputer].freeMemory
        += block->block.size;

    computers[op.oldComputer].freeMemory
        -= block->block.size;

    block->block.storedComputer =
        op.oldComputer;
}

    cout<<GREEN<<"\nRollback Successful\n"<<RESET;

    cout<<"Block "
        <<op.blockID
        <<" restored to Computer "
        <<op.oldComputer
        <<endl;
}

// Displays all computers and memory information
void displayComputers()
{
    cout<<MAGENTA<<"\nCluster Computers\n"<<RESET;

    for(auto computer :
        computers)
    {
        cout
        <<BLUE << "ID : "<<RESET
        <<computer.second.computerID<<endl

        <<YELLOW << " Memory : "<< RESET
        <<computer.second.totalMemory<<endl

        <<CYAN << " Free : " << RESET
        <<computer.second.freeMemory

        <<endl;
    }
}

// Displays all memory blocks from AVL Tree
void displayMemoryBlocks()
{
    cout<<MAGENTA<<"\nMemory Index\n"<<RESET;

    inorder(memoryRoot);
}

// Displays all available user operations
void menu()
{
    // cout<<"\n";
    cout<<CYAN;
    cout<<"====================================\n";
    cout<<"           MemGrid Menu             \n";
    cout<<"====================================\n";
    cout<<RESET;

    cout<<"1. Add Computer\n";
    cout<<"2. Verify Computer\n";

    cout<<"3. Allocate Memory Block\n";
    cout<<"4. Search Memory Block\n";

    cout<<"5. Display Memory Blocks\n";

    cout<<"6. Move Memory Block\n";
    cout<<"7. Undo Last Move\n";

    cout<<"8. Add Request\n";
    cout<<"9. Process Request\n";

    cout<<"10. Access Memory Block\n";
    cout<<"11. Show Most Used Blocks\n";

    cout<<"12. Add Network Connection\n";
    cout<<"13. Display Network\n";

    cout<<"14. Find Shortest Path\n";

    cout<<"15. Display Computers\n";

    cout<<"16. Exit\n";

    cout<<YELLOW<<"Choice : "<<RESET;
}

// Program execution starts here


void displayBanner()
{
    cout << MAGENTA << BOLD;

    cout << R"(
╔═════════════════════════════════════════════════╗
║                                                 ║
║   __  __                 _____      _     _     ║
║  |  \/  |               / ____|    (_)   | |    ║
║  | \  / | ___ _ __ ___ | |  __ _ __ _  __| |    ║
║  | |\/| |/ _ \ '_ ` _ \| | |_ | '__| |/ _` |    ║
║  | |  | |  __/ | | | | | |__| | |  | | (_| |    ║
║  |_|  |_|\___|_| |_| |_|\_____|_|  |_|\__,_|    ║
║                                                 ║
╚═════════════════════════════════════════════════╝

)";

    cout << RESET;
}

int main()
{
    displayBanner();
    int choice;

    while(true)
    {
        menu();

        cin>>choice;

        switch(choice)
        {
            case 1:
                addComputer();
                break;

            case 2:
                verifyComputer();
                break;

            case 3:
                allocateMemory();
                break;

            case 4:
                searchMemoryBlock();
                break;

            case 5:
                displayMemoryBlocks();
                break;

            case 6:
                moveBlock();
                break;

            case 7:
                undoOperation();
                break;

            case 8:
            {
                int rid;
                int cid;
                int bid;

                cout<<"Request ID : ";
                cin>>rid;

                cout<<"Computer ID : ";
                cin>>cid;

                cout<<"Block ID : ";
                cin>>bid;

                addRequest(
                    rid,
                    cid,
                    bid);

                break;
            }

            case 9:
                processRequest();
                break;

            case 10:
                accessMemoryBlock();
                break;

            case 11:
                showMostUsedBlocks();
                break;

            case 12:
                addConnection();
                break;

            case 13:
                displayNetwork();
                break;

            case 14:
                shortestPath();
                break;

            case 15:
                displayComputers();
                break;

            case 16:
                cout<<MAGENTA<<"Program Ended\n"<<RESET;
                return 0;

            default:
                cout<<RED<<"Invalid Choice\n"<<RESET;
        }
    }

    return 0;
}

