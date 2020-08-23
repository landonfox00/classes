
#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#include <memory>

#include "binary_tree_interface.h"
#include "binary_node.h"
#include "not_found_exception.h"
#include "precond_violated_exception.h"

template < class T >
class BinaryNodeTree : public BinaryTreeInterface< T >
{
public:
	BinaryNodeTree();
	BinaryNodeTree( const T& root_data );
	BinaryNodeTree( const T& root_data, const std::shared_ptr< BinaryNodeTree< T > > left, const std::shared_ptr< BinaryNodeTree< T > > right );
	BinaryNodeTree( const BinaryNodeTree< T >& tree );
	virtual ~BinaryNodeTree();

	bool IsEmpty() const;
	int get_height() const;
	int get_number_of_nodes() const;
	T get_root_data() const throw ( PrecondViolatedException );
	void set_root_data( const T& data );

	bool Add( const T& entry );
	bool Remove( const T& target );
	void Clear();

	T get_entry( const T& entry ) const throw ( NotFoundException );
	bool Contains( const T& entry ) const;

	void PreorderTraverse( void Visit( T& ) ) const;
	void InorderTraverse( void Visit( T& ) ) const;
	void PostorderTraverse( void Visit( T& ) ) const;

	BinaryNodeTree< T >& operator=( const BinaryNodeTree< T >& tree );

protected:
	int get_height_helper( std::shared_ptr< BinaryNode< T > > subtree ) const;
	int get_number_of_nodes_helper( std::shared_ptr< BinaryNode< T > > subtree) const;

	virtual std::shared_ptr< BinaryNode< T > > AddNode( std::shared_ptr< BinaryNode< T > > subtree, std::shared_ptr< BinaryNode< T > > node );

	virtual std::shared_ptr< BinaryNode< T > > RemoveValue( std::shared_ptr< BinaryNode< T > > subtree, const T target, bool& is_successful );

	virtual std::shared_ptr< BinaryNode< T > > RemoveNode( std::shared_ptr< BinaryNode< T > > node );

	virtual std::shared_ptr< BinaryNode< T > > FindNode( std::shared_ptr< BinaryNode< T > > subtree, const T& target, bool& is_successful ) const;

	std::shared_ptr< BinaryNode< T > > CopyTree( const std::shared_ptr< BinaryNode< T > > subtree ) const;

	void DestroyTree( std::shared_ptr< BinaryNode< T > > subtree );

	void Preorder( void Visit( T& ), std::shared_ptr< BinaryNode< T > > subtree ) const;
	void Inorder( void Visit( T& ), std::shared_ptr< BinaryNode< T > > subtree ) const;
	void Postorder( void Visit( T& ), std::shared_ptr< BinaryNode< T > > subtree ) const;

private:
	std::shared_ptr< BinaryNode< T > > root_;

};

#include "binary_node_tree.cc"

#endif
