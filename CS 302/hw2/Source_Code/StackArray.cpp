//--------------------------------------------------------------------
//
//  StackArray.cpp
// 
//  Class implementation for the array declaration of the Stack ADT
//
//--------------------------------------------------------------------

#include <stdexcept>
#include <iostream>
#include "Stack.h"
#include "StackArray.h"

template<typename DataType>
StackArray<DataType>::StackArray( int maxNumber )
	: maxSize( maxNumber ), top( -1 ), dataItems( new DataType[ maxNumber ] ) {}

template<typename DataType>
StackArray<DataType>::StackArray( const StackArray& other )
	: maxSize( other.maxSize ), top( other.top ), dataItems( new DataType[ other.maxSize ] )
{
	for ( int i = 0; i <= other.top; i++ )
		dataItems[ i ] = other.dataItems[ i ];
}

template<typename DataType>
StackArray<DataType>& StackArray<DataType>::operator=( const StackArray& other )
{
	this->maxSize = other.maxSize;
	this->top = other.top;
	this->dataItems = other.dataItems;
	return *this;
}

template<typename DataType>
StackArray<DataType>::~StackArray()
{
	delete this->dataItems;
}

template<typename DataType>
void StackArray<DataType>::push( const DataType& newDataItem ) throw ( std::logic_error )
{
	if ( this->isFull() )
		throw std::logic_error( "StackArray object cannot push() due to full stack" );
	this->top++;
	this->dataItems[ this->top ] = newDataItem;
}

template<typename DataType>
DataType StackArray<DataType>::pop() throw ( std::logic_error )
{
	if ( this->isEmpty() )
		throw std::logic_error( "StackArray object cannot pop() due to empty stack" );
	DataType* dataItem = this->dataItems[ this->top ];
	this->top--;
	return *dataItem;
}

template<typename DataType>
void StackArray<DataType>::clear()
{
	this->top = -1;
}

template<typename DataType>
bool StackArray<DataType>::isEmpty() const
{
	return this->top < 0;
}

template<typename DataType>
bool StackArray<DataType>::isFull() const
{
	return this->top >= this->maxSize - 1;
}

template<typename DataType>
void StackArray<DataType>::showStructure() const
{
    if( this->isEmpty() )
		std::cout << "Empty stack." << std::endl;
    else
    {
		int j;
		std::cout << "Top = " << this->top << std::endl;
		for ( j = 0; j < maxSize; j++ )
		    std::cout << j << "\t";
		std::cout << std::endl;
		for ( j = 0; j <= top; j++ )
		{
		    if( j == this->top )
		        std::cout << '[' << dataItems[j] << ']'<< "\t"; // Identify top
		    else
				std::cout << dataItems[j] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
