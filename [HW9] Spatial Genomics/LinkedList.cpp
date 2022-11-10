#include <iostream>
#include <string>
#include <sstream>
#include "LinkedList.h"
#include "Node.h"
#include <cmath>

using std::cout; 
using std::endl; 
using std::to_string;
using std::string;
using std::ostream;

bool debug = 0; 

LinkedList::LinkedList() : head{ nullptr }, tail{ nullptr } {
	  // Implement this function
    if (debug) cout << "In default constructor" << endl; 
}

LinkedList::~LinkedList() {
	  // Implement this function
    clear(); 
}

LinkedList::LinkedList(const LinkedList &source) : head{ nullptr }, tail{ nullptr } {
    // Implement this function

    debug = 0; 
    if (debug) cout << "In copy constructor" << endl; 

    if (source.head == nullptr)
        return; 

    //if (debug) cout << "   Is source.head a nullptr? " << (source.head == nullptr) << endl;
    Node* s = source.head; 
    CellData d;
    clear(); 
   

    while (s != nullptr) {
        if (debug) cout << "   In for loop of copy construct" << endl;
        d = s->data;
        this->insert(d.id, d.fov, d.volume, d.center_x, d.center_y, d.min_x, d.max_x, d.min_y, d.max_y); 
        s = s->next; 
        // all head / tail business is handled by the insert function 
    }

    if (debug) cout << "    End of copy construct" << endl;

}

LinkedList& LinkedList::operator=(const LinkedList& source) 
{
    // Implement this function
    debug = 0; 
    if (debug) cout << " >>> In the equals operator <<< " << endl;

    Node* s = source.head;
    CellData d;
    this->clear();

    while (s != nullptr) {
        d = s->data;
        this->insert(d.id, d.fov, d.volume, d.center_x, d.center_y, d.min_x, d.max_x, d.min_y, d.max_y);
        s = s->next;
    }

    return *this;
}

void LinkedList::insert(std::string id, int fov, double volume, double center_x, double center_y, 
    double min_x, double max_x, double min_y, double max_y)
{
    if (debug) cout << "In the insert() function " << endl; 

    Node* n = new Node{ id, fov, volume, center_x, center_y, min_x, max_x, min_y, max_y }; 
    // Implement this function
    Node* curr = head; 
    /*if (head != nullptr)
        if (debug) cout << "   Is the new one's fov < curr head ? " << (fov < curr->data.fov) << endl;*/


    if (head == nullptr) {
        if (debug) cout << "   In the empty list case " << endl;
        // empty list 
        head = n;
        tail = n; 
        // next and prev default to nullptr 
        return; 
    }
    else if (*n < *curr) { // insert at head 
        if (debug) cout << "   In the insert at head case " << endl;
        curr->prev = n;
        n->next = curr;
        head = n;  
        return; 
    }

    while (curr != nullptr) {
        if (debug) cout << "   In the general case's loop " << endl;

        if (*n < *curr) {
            if (debug) cout << "     Found a spot to insert at " << endl;
            
            curr->prev->next = n;
            n->prev = curr->prev;
            curr->prev = n;
            n->next = curr; 
            
            return; 
        }

        curr = curr->next; 
    }

    // while loop complete -- add on to the end 

    tail->next = n; 
    n->prev = tail; 
    tail = n; 
    return; 
}

void LinkedList::remove(std::string id, int fov, double volume, double center_x, double center_y, 
    double min_x, double max_x, double min_y, double max_y)
{
    debug = 0; 

    if (debug) cout << "In the remove() function " << endl;
    Node* n = new Node{ id, fov, volume, center_x, center_y, min_x, max_x, min_y, max_y };
    Node* curr = head; 

    // Implement this function
    if (head == nullptr)
        return; 
    else if (*n == *curr) { // delete head
        if (debug) cout << "  delete head case" << endl; 

        if (head->next != nullptr) { // maybe check about the tail with 2 elements total 
            head = head->next;
            delete head->prev;
            head->prev = nullptr;
            delete n;
            return;
        }
        else {
            if (debug) cout << "     in the else block so only one node left" << endl;
            delete head; 
            head = nullptr; 
            tail = nullptr; 
            delete n; 
            return; 
        }
        
    }
    else if (*n == *tail) { // delete tail 
        if (debug) cout << "  delete tail case" << endl;
        tail = tail->prev; 
        delete tail->next; 
        tail->next = nullptr;
        delete n;
        return; 
    }

    while (curr->next != nullptr) {

        if (debug) cout << "  in the general case loop" << endl;

        if (*n == *curr) {
            if (debug) cout << "     found the item to delete" << endl;
            curr->next->prev = curr->prev;
            curr->prev->next = curr->next;
            delete curr; 
            delete n; 
            return;
        }

        curr = curr->next;
    }

    // went thru everything and node not found -- take out the trash 
    delete n;

}

void LinkedList::clear() 
{	
    // Implement this function
    if (head == nullptr)
        return; 
    else {
        Node* temp; 
        while (head != nullptr) { 
            temp = head; 
            head = head->next; 
            delete temp;
        }
        tail = nullptr; 
    }
}

Node* LinkedList::getHead() const 
{
    // Implement this function it will be used to help grade other functions
    return head; 
}

string LinkedList::print() const 
{
   	// Implement this function
    debug = 0; 

    if (debug) cout << "In the print() function" << endl; 

    std::stringstream ss;  

    Node* curr = head; 
    // if (debug) cout << "   Head is not a nullptr : " << (head != nullptr) << endl;
    CellData c; // no idea if head is nullptr yet do a check in the while first! 

    ss << "fov,volume,center_x,center_y,min_x,max_x,min_y,max_y" << '\n';

    while (curr != nullptr) {
        c = curr->data;

        //if (debug) cout << "   In the while loop " << endl;

        ss << c.id << ',' << c.fov << ',' << c.volume << ',' << c.center_x << ',' << c.center_y 
            << ',' << c.min_x << ',' << c.max_x << ',' << c.min_y << ',' << c.max_y << '\n'; 

        //if (debug) cout << "   sstream was able to handle all that mess " << endl;

        curr = curr->next; 
    }

    string retString = ss.str(); 
    
    return retString; 

}

ostream& operator<<(ostream& os, const LinkedList& ll) {
	/* Do not modify this function */
	os << ll.print();
	return os;
}

// given a fov number, count the cells observed in that fov
int LinkedList::countN(int fov)
{
	/* Do not modify this function */
    int count = 0;
    Node* cur = head;
    while (cur)
    {
        if (cur->data.fov == fov)
            count++;
        cur = cur->next;
    }
    return count;
}

/* given a fov number, compute the average volume of all the cells observed in
 * that fov
 */
double LinkedList::average(int fov)
{
    // Implement this function
    //bool found = false; 
    Node* curr = head; 
    size_t numCells = 0;
    double volSum = 0;

    while (curr != nullptr) {
        if (curr->data.fov == fov) {
            volSum += curr->data.volume; 
            numCells++;  
        }

        curr = curr->next; 
    }

    if (numCells != 0) {
        return volSum / numCells;  
    }
    else {
        return -1;
    }
    
}

/* given a fov number, compute the variance volume of all the cells observed in
 * that fov
 */
double LinkedList::variance(int fov)
{
	/* Do not modify this function */
    double sum = 0;
    double avg = average(fov);
    int count = countN(fov);

    if (count == 0)
        return -1;

    Node* cur = head;
    while (cur)
    {
        if (fov == cur->data.fov)
            sum += (cur->data.volume - avg) * (cur->data.volume - avg);
        cur = cur->next;
    }

    return sum/count;
}

/* given a fov number, remove outliers

     - if count(k) < N, return a message “Less than N cells in fov k”.
     - otherwise, let delta(k) be the square root of var(k). Remove those cells 
       such that vol(i) is not in the range
       [avg(k) − j * delta(k),   avg(k) + j * delta(k)] from the linked list.

    Return a message “# cells are removed.”, where # is the number of cells
    removed.
 */
string LinkedList::outliers(int fov, int k, int N)
{
    // Implement this function
    if (countN(fov) < N) 
        return "Less than " + to_string(N) + " cells in fov " + to_string(fov);
    else {
        //bool found = false;
        Node* curr = head;
        Node* future; 
        size_t removeCount = 0; 
        CellData d; 
        
        double lowerbound = average(fov) - k * sqrt(variance(fov)); 
        double upperbound = average(fov) + k * sqrt(variance(fov));

        while (curr != nullptr) {
            future = curr->next; 
            if (curr->data.fov == fov) {
                if (lowerbound > curr->data.volume || upperbound < curr->data.volume) {
                    d = curr->data; 
                    remove(d.id, d.fov, d.volume, d.center_x, d.center_y, d.min_x, d.max_x, d.min_y, d.max_y); 
                    removeCount++; 
                }
            }

            curr = future; 
        }

        return to_string(removeCount) + " cells are removed.";
    }

}

