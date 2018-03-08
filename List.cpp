/******************************************************************************/
/*!
\file   List.cpp
\author Robb Cutrell
\par    email: r.cutrell\@digipen.edu
\par    DigiPen login: r.cutrell
\par    Course: CS170
\par    Section: B
\par    Lab #8
\date   3/7/2018
\brief  
    Lab to merge two lists together
      
    Functions include:
    
       + List::List()
       + Node* List::MakeNode(int value) const
       + struct Node* MakeNode(const int value)
       + int Count()
       + void AddToEnd(const int value)
       + void AddToFront(const int value)
       + Node *FindItem(const int value)
       + void Insert(const int value, int position)
       + void Insert(int value)
       + void Delete(int value)
       + void Delete(const List& Items)
       + void Concat(const List& Source)
       + std::ostream& operator<<(std::ostream &os, const List& rhs)
       + void Merge(List& rhs)
       + int RemoveDuplicates()
       + ~List()
       
       
    
    
  Hours spent on this assignment: 4

  Specific portions that gave you the most trouble:
    Thinking for some reason second list would automatically null after moving
    all the nodes.

  

*/
/******************************************************************************/
#include <iostream> // cout
#include "List.h"

/*******************************************************************/
/*******************************************************************/
namespace CS170
{
  namespace ListLab
  {
    /**************************************************************************/
    /*!
    \brief
      establish a variable to be used throughout the scope
      
    */
    /**************************************************************************/
    List::List()
    {
      head_ = 0; // set the head to nothing to start
    }

    /************************************************************************/
      /*!
      \brief
        creates a new node for linked list
      
      \param value
        the int value for the linked list to possess.
        
      \return struct Node
        returns a pointer to a new dynamically allocated Node struct
      
      */
      /************************************************************************/
    Node* List::MakeNode(int value) const
    {
        // The Node constructor sets the value, and sets next to 0.
      return new Node(value);
    }



    /**************************************************************************/
    /*!
    \brief
      counts the number of nodes in the list
      
    \return int
      returns the number of nodes in the linked list
      
    */
    /**************************************************************************/
    int List::Count() const
    {
      int count = 0;          // variable to return at the end of function
      Node *tempNode = head_; // a temp node to walk through the list
      
      //loop through the list counting the nodes
      while(tempNode)
      {
        count++;
        tempNode = tempNode->next;
      }
      return count; //return number of nodes found
    }
    
    /**************************************************************************/
    /*!
    \brief
      adds a node to the end of the linked list
      
    \param value
      the value to store inside the node being created
      
    */
    /**************************************************************************/
    void List::AddToEnd(const int value)
    {
      Node *newNode = head_; //set newNode to beginning of linked list
      
      if(newNode == 0) //if there is currently no nodes
      {
        newNode = MakeNode(value); //create a new node
        head_ = newNode; //set head_ to the new node
      }
      else
      {
        //loop through list until at the end of list and then create a new node
        while(newNode->next)
        {
          newNode = newNode->next;
        }
        
        newNode->next = MakeNode(value);
      }
    }
    
    /**************************************************************************/
    /*!
    \brief
      adds a node to the beginning of the linked list
      
    \param value
      the value to store inside the node being created
      
    */
    /**************************************************************************/
    void List::AddToFront(const int value)
    {
      Node *oldFrontNode = head_;           //store current front node
      Node *newFrontNode = MakeNode(value); //create a new node
      newFrontNode->next = oldFrontNode;    //have new node's next be old front
      head_ = newFrontNode;                 //have head_ set to new front node.
    }
    
    /**************************************************************************/
    /*!
    \brief
      finds an item and returns the node that contains it
      
    \param value
      the value that is being searched for in the nodes
      
    \return struct Node
      returns the node that has the searched value
      
    */
    /**************************************************************************/
    Node* List::FindItem(const int value) const
    {
      Node *nodeWithItem = head_; //begin at front of list
      
      //if there are any nodes
      while(nodeWithItem)
      {
        if(nodeWithItem->number == value) //check node to see if it has the item
        {
          return nodeWithItem;  //if it does, return node.
        }
        else
        {
          nodeWithItem = nodeWithItem->next; //otherwise look at next node
        }
      }
      
      //return NULL if there are no nodes to search
      return NULL;
    }
  
    /**************************************************************************/
    /*!
    \brief
      insert a node at the given position of the list

    \param value
      the value to give the new node
      
    \param position
      the position to place the new node in
      
    */
    /**************************************************************************/
    void List::Insert(const int value, int position)
    {
      int nodeCount = Count(); //find the number of nodes in list
      
      //if trying to insert a new node into a position past the end of the list
      if(position >= nodeCount + 1) 
      {
        return; //return null
      }
      else
      {
        //if being stored at front of list
        if(position == 0)
        {
          Node *oldNode = head_;           //store current front of list
          Node *newNode = MakeNode(value); //create new node
          
          newNode->next = oldNode; //set old front of list to next of new node
          head_ = newNode;         //set head to new front of list
        }
        else
        {
          Node *nodeCurrent;   //current node to become previous
          Node *nodeNext;      //next node that will follow new node
          
          nodeCurrent = head_; //set current node to front of list
          
          //while not at the current position for new node, walk through list
          while(position - 1)
          {
            nodeCurrent = nodeCurrent->next;
            position--;
          }
          
          nodeNext = nodeCurrent->next;         //set the next node
          nodeCurrent->next = MakeNode(value);  //create a new node
          nodeCurrent->next->next = nodeNext;   //tie next node to new node
        }
      }
    }

    /**************************************************************************/
    /*!
    \brief
      insert a node with the given value at a position equal to value

    \param value
      the value to give the new node
      
      
    */
    /**************************************************************************/
    void List::Insert(int value)
    {
      Node *nodeCurrent = head_;   //current node to become previous
      Node *nodeNext = NULL;       //next node that will follow new node
      Node *nodePrev = NULL;       //previous node in the list
      
      //if there is no list yet, make a new node and make it the head
      if(head_ == NULL)
      {
        head_ = MakeNode(value);
        head_->next = NULL;
      }
      //if the new node goes at the front of the list
      else if (head_->number > value)
      {
        nodeNext = head_;
        head_ = MakeNode(value);
        head_->next = nodeNext;
      }
      //loop through the list to find where the new node belongs
      else
      {
        while(nodeCurrent->number < value)
        {
          nodePrev = nodeCurrent;
          nodeCurrent = nodeCurrent->next;
          //if you've reached the end of the list break out
          if (nodeCurrent == NULL)
          {
            break;
          }
        }
        //if the previous node was null place new node at front of list
        //and assigned next node to null
        if (nodePrev == NULL)
        {
          head_ = MakeNode(value);
          head_->next = nodeCurrent;
        }
        //assign the new node to be next in list after current node
        //and assign current's next node to be follow behind the new node
        else
        {
          nodePrev->next = MakeNode(value);
          nodePrev->next->next = nodeCurrent;
        }
      }
    }
  
    /**************************************************************************/
      /*!
      \brief
        Deletes a node with the specified value (first occurrence only)

      \param value
        the value of node to delete
      
      
       */
    /**************************************************************************/
    void List::Delete(int value)
    {
      if (!head_)
      {
        return;
      }

      int nodeCount = Count();   //number of nodes in list
      Node *nodeCurrent = head_; //establish current node being looked at
      Node *nodeNext;            //node after the node with searched value
      Node *nodePrev;            //node before the node with searched value
     
      //if the first node is the value being deleted

      if(nodeCurrent->number == value)
      {
        head_ = nodeCurrent->next; //set head_ to point at second node
        delete nodeCurrent;        //delete first node
        return;                    //end function
      }
    
      //searched throughout the list for node with value to delete
      for(int counter = 0; counter < nodeCount - 1; counter++)
      {
        //if the node after current node has the value to be deleted
        if(nodeCurrent->next->number == value)
        {
          nodePrev = nodeCurrent;          //Set 'previous' node as current
          nodeCurrent = nodeCurrent->next; //Set current node to node with value
        
          //If there's a node after the node with searched value
          nodeNext = nodeCurrent->next;  //Set 'next' node to node after current
          nodePrev->next = nodeNext;     //Sets the next node to follow previous

      
          delete nodeCurrent; //deletes the node with the searched value 
          return;             //end function
        }
        else
        {
          //if there's a next node set that to current
          if(nodeCurrent->next)
          {
            nodeCurrent = nodeCurrent->next;
          }
          //If the end of the node list is reached
          else
          {
            return; //return without deleting anything if value was never found
          }
        }
      }
    }

    /**************************************************************************/
    /*!
    \brief
      Deletes all of the values in the list that are in Items

    \param Items
      the node to be deleted
       
    */
    /**************************************************************************/
    void List::Delete(const List& Items)
    {
      if (!head_)
      {
        return;
      }

      Node *itemsToDelete = Items.head_; //Looks at nodes with values to delete
      Node *searchedList = head_;   //Var to go through list being deleted
      Node *nextNode = NULL;
    

    
      //While there are still nodes to be searched and deleted
      while(itemsToDelete)
      {
        //While the searchedList still has nodes to go through
        while(searchedList)
        {
          nextNode = searchedList->next;
          //if the current searched node has the value to be deleted
          if(searchedList->number == itemsToDelete->number)
          {
            //delete node
            Delete(itemsToDelete->number);
          }
          //set up next node in searched list to be looked at
          searchedList = nextNode;
        }
      
        //look at the next node that has the next value to delete
        itemsToDelete = itemsToDelete->next;
        //Set the searchedList back to the first node of the list
        searchedList = head_;
      }
    }
  

    /**************************************************************************/
    /*!
    \brief
      Concatenates two lists

    \param Source
      the nodes to be concatenated to the list
       
    */
    /**************************************************************************/
    void List::Concat(const List& Source)
    {
      //temp copy for the node being concatenated
      Node *nodeToConcat = Source.head_;
    
      //if the node to be concatenated has no head, break out
      if(!nodeToConcat)
      {
        return;
      }
      
      //while there are still more nodes to be concatenated loop through
      //list and copy nodes to end of linked list being added to
      while(nodeToConcat)
      {
        AddToEnd(nodeToConcat->number);
        nodeToConcat = nodeToConcat->next;
      }
     
    }

    /**************************************************************************/
    /*!
      \brief
        overloads << operator to print output to screen
        
      \param os
        the std output stream
        
      \param rhs
        node with the value's being printed

      \return os
        returns the std stream
      
    */
    /**************************************************************************/
    std::ostream& operator<<(std::ostream& os, const List& rhs)
    {
      // Use this line to print out each value in the list.
      // You will need to create a while loop here to walk
      // through all of the nodes.
      Node *nodePrint = rhs.head_;
      while(nodePrint)
      {
        os << nodePrint->number << "   ";
        nodePrint = nodePrint->next;
      }
      return os;
    }
    
    /**************************************************************************/
    /*!
    \brief
      Merges two lists into one

    \param rhs
      list to be merged with the first list
       
    */
    /**************************************************************************/
    void List::Merge(List& rhs)
    {
      //if there is no second list return first list
      if (!rhs.head_)
      {
        return;
      }
      
      //if there is not first list, set second list to first and return
      if (!head_)
      {
        head_ = rhs.head_;
        rhs.head_ = NULL;
        return;
      }
      
      Node *lhsHead = head_;      //pointer to head of LHS
      Node *rhsHead = rhs.head_;  //pointer to head of RHS
      Node *newHead = NULL;       //pointer to head of new list
      Node *newTail = NULL;       //pointer to tail of new list
      
      
      while(lhsHead && rhsHead) //when both lists still have values
      {
        //if lhs value is less than or equal to rhs set it to new list
        if(lhsHead->number < rhsHead->number) 
        {
          //if new list has no nodes yet, establish first node
          if(newHead == NULL)
          {
            //head of new list is equal to head of lhs
            newHead = lhsHead;
            //tail of new list is equal to head of lhs
            newTail = lhsHead;
          }
          else //if there is already a node in new list
          {
            //have the last node in list point to current lhs head
            newTail->next = lhsHead;
            //set new trail for new list
            newTail = newTail->next;
          }
          //set the lhs head to next node
          lhsHead = lhsHead->next;
        }
        //if rhs value is less than lhs set it to new list
        else
        {
          //if new list has no nodes yet, establish first node
          if(newHead == NULL)
          {
            //head of new list is equal to head of lhs
            newHead = rhsHead;
            //tail of new list is equal to head of lhs
            newTail = rhsHead;
          }
          else //if there is already a node in new list
          {
            //have the last node in list point to current lhs head
            newTail->next = rhsHead;
            //set new trail for new list
            newTail = newTail->next;
          }
          //set the rhs head to next node
          rhsHead = rhsHead->next;
        }
      }
      
      //when only first list has nodes, add them all to end of new list
      while(lhsHead && !rhsHead)
      {
        newTail->next = lhsHead;
        newTail = newTail->next;
        lhsHead = lhsHead->next;
      }
      
      //when only second list has nodes, add them all to end of new list
      while(!lhsHead && rhsHead)
      {
        newTail->next = rhsHead;
        newTail = newTail->next;
        rhsHead = rhsHead->next;
      }

      head_ = newHead;  //sets the new list to first list
      rhs.head_ = NULL; //nulls out second list
    }
    
    /**************************************************************************/
    /*!
    \brief
      Removes the duplicate nodes in a sorted list

    \return int numRemoved
      number of nodes deleted
       
    */
    /**************************************************************************/
    int List::RemoveDuplicates()
    {
      int numRemoved = 0;    // Number of nodes removed
      
      //if the list is blank
      if(head_ == NULL)
      {
        return numRemoved; // return 0
      }
      
      Node *listTail = head_; // The current/last node being looked at
      
      while(listTail != NULL)
      {
        //if there are no more nodes after one being looked at, return.
        if (listTail->next == NULL)
        {
          return numRemoved;
        }

        // if current node number is the same as the next number
        while(listTail->number == listTail->next->number)
        {
          Node *removedNode = listTail->next;    // pull the node to be removed
          listTail->next = listTail->next->next; // set the new next node
          delete removedNode;                    // delete the pulled node
          ++numRemoved;                          // increment numRemoved

          //if there are no more nodes after one being looked at, return.
          if (listTail->next == NULL)
          {
            return numRemoved;
          }
        }
        
        listTail = listTail->next; // proceed to next node
      }
      
      return numRemoved;
    }

    /**************************************************************************/
    /*!
    \brief
      deletes the set aside allocated memory for the linked list
      
    */
    /**************************************************************************/
    List::~List()
    {
      
      Node *nodeCurrent = head_; //start at beginning of list
      Node *nodeNext;            //next node in list
      
      while(nodeCurrent)
      {
        nodeNext = nodeCurrent->next; //set next node in list
        delete nodeCurrent;           //delete current note
        nodeCurrent = nodeNext;       //set next node to current node
      }
    }
  }
}
