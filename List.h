/******************************************************************************/
/*!
\file   List.h
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
       + void List::Merge(List& rhs)
       + int List::RemoveDuplicates()
       + ~List()
       
       
    
    
  Hours spent on this assignment: 4

  Specific portions that gave you the most trouble:
    Thinking for some reason second list would automatically null after moving
    all the nodes.

  

*/
/******************************************************************************/
////////////////////////////////////////////////////////////////////////////////
#ifndef LIST_H
#define LIST_H
////////////////////////////////////////////////////////////////////////////////

namespace CS170
{
  namespace ListLab
  {
    /**************************************************************************/
    /*!
    \struct Node
    \brief  
      a structure to create linked lists

    */
    /**************************************************************************/
    struct Node
    {
      int number; //!< data portion/number of node
      Node *next; //!< pointer to next node in list

      
      /************************************************************************/
      /*!
      \brief
        constructor conversion for Nodes
        
      \param value
        the value to store into the node
      */
      /************************************************************************/
      Node(int value)
      {
        number = value;
        next = 0;
      }
    };

    /**************************************************************************/
    /*!
    \class List
    \brief  
      Functions to manipulate linked lists

      Operations include:

      - Adding node to end
      - Adding node to front
      - adding node to given position
      - deleting nodes with given value
      - deleting first node with given value
      - concating two lists
      - merging two sorted lists

    */
    /**************************************************************************/
    class List
    {
      public:
          // Default constructor
        List();

          // Destructor
        ~List();

          // Adds a node to the end of the list
        void AddToEnd(int value);

          // Adds a node to the front of the list
        void AddToFront(int value);

          // Returns the number of nodes in the list
        int Count() const;

          // Finds an item and returns the node that contains it
          // Only finds the first occurrence of value
        Node *FindItem(int value) const;

          // Inserts a new node at the specified position
        void Insert(int value, int position);

          // Deletes a node with the specified value (first occurrence only)
        void Delete(int value);

          // Concatenates two lists
        void Concat(const List& Source);

          // Deletes all of the values in the list that are in Items
        void Delete(const List& Items);

          // Inserts a new node in the correct position (sorted small to large)
        void Insert(int value);

          // Displays the list
        friend std::ostream& operator<<(std::ostream &os, const List& rhs);
        
          // Merge two lists
        void Merge(List& rhs);
          
          //Removes duplicate values in a sorted list
        int RemoveDuplicates();

      private:
        Node *head_; //!< The first node in a list
        Node* MakeNode(int value) const;

          // Other private stuff ...
    };
  } // namespace ListLab
} // namespace CS170

#endif // LIST_H
