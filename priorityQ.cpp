/*
Name: Jack Knapp, 302.6
Purpose: Use a Priority Queue Baby!
Description: Determine the finish order of a Mario Kart race!
Input: Racers + Distances from a text file
What to do?:  Keep the order of the racers with a priority queue, then update them and output results
Output: The results of the race, along with any errors and some status updates
*/
#include "priorityQ.h"
#include <cstdlib>
#include <iostream>
using namespace std;

/* 
 * priorityQ : Default Constructor
 * parameters: N/A
 * return value: N/A
 */
template <class t1, class t2>
priorityQ<t1, t2>::priorityQ() 
{   
    size = 0;
    capacity = 5;
    heapArray = new priorityType[capacity];
}

/* 
 * priorityQ : Copy Constructor
 * parameters: A priorityQ obj to copy
 * return value: N/A
 */
template <class t1, class t2>
priorityQ<t1, t2>::priorityQ(const priorityQ<t1, t2>& copy) 
{
    this->capacity = copy.capacity;
    this->size = copy.size;
    this->itemToPQ = copy.itemToPQ;

    heapArray = new priorityType[capacity];
    for (int i=1; i< capacity; i++) {
        this->heapArray[i] = copy.heapArray[i];
    }
}

/* 
 * operator= : Equality Operator Overload
 * parameters: rhs priorityQ obj
 * return value: N/A
 */
template <class t1, class t2>
const priorityQ<t1, t2>& priorityQ<t1, t2>::operator=(const priorityQ<t1, t2>& rhs)
{
    if (this != &rhs)
    {   
        //same copy constructor code
        this->capacity = rhs.capacity;
        this->size = rhs.size;
        this->itemToPQ = rhs.itemToPQ;

        //except we check for previous mem and yeet it
        if (heapArray != nullptr) {
            delete[] heapArray;
        }

        heapArray = new priorityType[capacity];
        for (int i=1; i< capacity; i++) {
            this->heapArray[i] = rhs.heapArray[i];
        }
    }
    return *this;
}

/* 
 * ~priorityQ : Destructor
 * parameters: N/A
 * return value: N/A
 */
template <class t1, class t2>
priorityQ<t1, t2>::~priorityQ()
{
    delete[] heapArray;
    heapArray = nullptr;
}

/* 
 * push_back : Add a new value to queue
 * parameters: t1 object key and t2 object priority
 * return value: N/A
 */
template <class t1, class t2>
void priorityQ<t1, t2>::push_back(const t1& key, const t2& priority)
{   
    //check to full array and resize
    if (capacity-1 == size) {
        //resize (do I really need to explain this? no, I don't)
        priorityType * temp = new priorityType[capacity * 2];
        for (int i = 1; i< capacity; i++) {
            temp[i] = heapArray[i];
        }
        delete[] heapArray;
        heapArray = temp;
        temp = nullptr;

        capacity *= 2;
    }

    //increment size and add item to main array
    size++;
    heapArray[size].key = key;
    heapArray[size].priority = priority;

    //store item in hashmap and bubble up as needed
    itemToPQ[key] = size;
    bubbleUp(size);

    //for (int i =1; i<=size; i++) {
    //    cout << heapArray[i].key << "\t" << i << "\t" << heapArray[i].priority << endl;
    //}
    //cout << endl;
}

/* 
 * pop_front : yeets the front item from the queue
 * parameters: N/A
 * return value: N/A
 */
template <class t1, class t2>
void priorityQ<t1, t2>::pop_front()
{   
    //move item to front, decrement size, and bubbledown
    heapArray[1] = heapArray[size];
    size--;
    bubbleDown(1);

}

/* 
 * decrease_priority : change the priority of a queue member and then
        clean your room (your room is a priority queue)
 * parameters: t1 object key and t2 object priority
 * return value: N/A
 */
template <class t1, class t2>
void priorityQ<t1, t2>::decrease_priority(const t1& key, const t2& priority)
{   
    //pass key to hashmap to find index of heap to update priority
    heapArray[itemToPQ[key]].priority = priority;
    //bubble up to adjust the priority queue
    bubbleUp(itemToPQ[key]);

    //for (int i =1; i<=size; i++) {
    //    cout << heapArray[i].key << "\t" << i << "\t" << heapArray[i].priority << endl;
    //}
    //cout << endl;
}

/* 
 * get_front_priority : get the priority of front queue member
 * parameters: N/A
 * return value: t2 priority 
 */
template <class t1, class t2>
t2 priorityQ<t1, t2>::get_front_priority() const
{
   return heapArray[1].priority;
}

/* 
 * get_front_key : get the key of front queue member
 * parameters: N/A
 * return value: t1 key 
 */
template <class t1, class t2>
t1 priorityQ<t1, t2>::get_front_key() const
{
    return heapArray[1].key;
}

/* 
 * isEmpty : is the queue empty? lets find out
 * parameters: N/A
 * return value: a bool with the answer to our burning query
 */
template <class t1, class t2>
bool priorityQ<t1, t2>::isEmpty() const
{   
    //no comment
    if (size != 0) {
        return false;
    }
    else {
        return true;
    }
}

/* 
 * bubbleUp : move an item as high in the queue as possible via swapping
 * parameters: index to start with
 * return value: N/A 
 */
template <class t1, class t2>
void priorityQ<t1, t2>::bubbleUp(std::size_t index)
{
    //compute indexes
    size_t child = index, parent = child / 2;

    //if index is root, return
    if (index == 1) {
        return;
    }
    
    //loop until root is changed or parent is smaller
    while (true) {
        //check and or swap
        if (heapArray[child].priority < heapArray[parent].priority) {
            //swap
            priorityType temp = heapArray[child];
            heapArray[child] = heapArray[parent];
            heapArray[parent] = temp;

            //update hashmaps bb
            t1 a = heapArray[child].key;
            itemToPQ[a] = child;
            itemToPQ[heapArray[parent].key] = parent;
        }
        else {
            //end
            return;
        }

        //if we have reached root, return
        if (parent == 1) {
            return;
        }

        //update indexes (or indices - but that sucks tbh)
        child = parent;
        parent = child / 2;
    }
}

/* 
 * bubbleDown : like bubbleUp but in reverse; start from the top and go as far down 
        as you can with swaps
 * parameters: index to start with (preferably the root)
 * return value: N/A 
 */
template <class t1, class t2>
void priorityQ<t1, t2>::bubbleDown(std::size_t index)
{
    //compute indexes
    int curr = index, left = index * 2, right = left + 1;
    int small = left, big = right;

    //loop until leaf is changed or parent is smaller
    while (true) {

        //find the smaller leaf
        if (small <= capacity && big <= capacity && heapArray[small].priority > heapArray[big].priority) {
            small = right;
            big = left;
        }

        //check and swap with first leaf
        if (small <= size && heapArray[small].priority < heapArray[curr].priority) {
            //swap
            priorityType temp = heapArray[small];
            heapArray[small] = heapArray[curr];
            heapArray[curr] = temp;

            //update hashmaps bb
            itemToPQ[heapArray[curr].key] = curr;
            itemToPQ[heapArray[small].key] = small;

            curr = small;
        }
        //check and swap with second leaf
        else if (big <= size && heapArray[big].priority < heapArray[curr].priority) {
            //swap
            priorityType temp = heapArray[big];
            heapArray[big] = heapArray[curr];
            heapArray[curr] = temp;

            //update hashmaps bb
            itemToPQ[heapArray[curr].key] = curr;
            itemToPQ[heapArray[big].key] = big;

            curr = big;
        }
        else {
            //cout << endl;
            //for (int i =1; i<=size; i++) {
            //    cout << heapArray[i].key << "\t" << i << "\t" << heapArray[i].priority << endl;
            //}
            //cout << endl;

            //end
            return;
        }

        //if we have reached root, return
        if (curr * 2 > size) {
            //cout << endl;
            //for (int i =1; i<=size; i++) {
            //    cout << heapArray[i].key << "\t" << i << "\t" << heapArray[i].priority << endl;
            //}
            //cout << endl;

            return;
        }

        //adjust indexes
        left = curr * 2;
        right = left + 1;
        small = left;
        big = right;
    }
}