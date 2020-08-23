//--------------------------------------------------------------------
//
//  StackLinked.cpp
// 
//  Class implementation for the linked declaration of the Stack ADT
//
//--------------------------------------------------------------------

#include <stdexcept>
#include <iostream>
#include "Stack.h"
#include "StackLinked.h"

// Stackinked constructor
template<typename DataType>
StackLinked<DataType>::StackLinked( int maxNumber )
	: top( 0 ) { }

// StackLinked copy constructor
template<typename DataType>
StackLinked<DataType>::StackLinked( const StackLinked& other )
{
	// default head for empty stack
	this->top = 0;
	StackNode* other_node = other.top;
	if ( other_node != 0 )
	{	// initialization of first node and header
		StackNode* this_node = new StackNode( other_node->dataItem, 0 );
		this->top = this_node;
		// advance other node pointer
		other_node = other_node->next;
		while ( other_node != 0 )
		{	// appending nodes until end of other stack
			// initialization of next node
			StackNode* next_node = new StackNode( other_node->dataItem, 0 );
			// link next node to stack
			this_node->next = next_node;
			// advance node pointers
			this_node = next_node;
			other_node = other_node->next;
		}
	}
}

// shallow copy of data into other StackLinked object
template<typename DataType>
StackLinked<DataType>& StackLinked<DataType>::operator=( const StackLinked& other )
{
	this->top = other.top;
	return *this;
}

// deconstructor
template<typename DataType>
StackLinked<DataType>::~StackLinked()
{
	this->clear();
}

// create new node and set top to new node
template<typename DataType>
void StackLinked<DataType>::push( const DataType& newDataItem ) throw ( std::logic_error )
{
	StackNode* node = new StackNode( newDataItem, this->top );
	this->top = node;
}

// remove top node and returns its dataItem
template<typename DataType>
DataType StackLinked<DataType>::pop() throw ( std::logic_error )
{
	// throw error if stack is empty
	if ( this->isEmpty() )
		throw std::logic_error( "StackLinked object cannot pop() due to empty stack" );
	// obtain top node
	StackNode* top_node = this->top;
	// adavance top pointer
	this->top = top_node->next;
	// obtain dataItem to return
	DataType data_item = top_node->dataItem;
	// free memory
	delete top_node;
	return data_item;
}

// deallocate all nodes
template<typename DataType>
void StackLinked<DataType>::clear()
{
	// pop all nodes until stack is empty
	while ( !this->isEmpty() )
		this->pop();
}

// returns true if top is not pointing to a node
template<typename DataType>
bool StackLinked<DataType>::isEmpty() const
{
	return this->top == 0;
}

// linked list implementation cannot have maximum size
template<typename DataType>
bool StackLinked<DataType>::isFull() const
{
	return false;
}

// displays stack contents
template<typename DataType>
void StackLinked<DataType>::showStructure() const
{
    if( this->isEmpty() )
		std::cout << "Empty stack" << std::endl;
    else
    {
        std::cout << "Top\t";
		for ( StackNode* temp = this->top; temp != 0; temp = temp->next )
		{
		    if( temp == this->top )
				std::cout << "[" << temp->dataItem << "]\t";
		    else
				std::cout << temp->dataItem << "\t";
		}
	    std::cout << "Bottom" << std::endl;
    }
}

// StackNode constructor
template<typename DataType>
StackLinked<DataType>::StackNode::StackNode(const DataType& nodeData, StackNode* nextPtr)
	: dataItem( nodeData ), next( nextPtr ) {}
