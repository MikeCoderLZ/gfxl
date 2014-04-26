#ifndef REFERENCE_MANAGER_HPP
#define REFERENCE_MANAGER_HPP
#include <map>
#include <string>
#include <iostream>

namespace gfx {

class ReferenceManager;

class Ref {
public:
    friend std::ostream& operator<<( std::ostream& out, Ref const& rhs );
private:
	Ref( ReferenceManager const& new_manager,
	     std::string const& new_textual_id,
	     unsigned int new_package,
	     unsigned int new_content ) : manager( new_manager ),
	     	 	 	 	 	 	 	  textual_id( new_textual_id ),
	    	 	 	 	 	 	 	  package( new_package ),
	     	 	 	 	 	 	 	  content( new_content ) {};
	friend class ReferenceManager;
	ReferenceManager const& manager;
	std::string textual_id;
	unsigned int package;
	unsigned int content;

};

std::ostream& operator<<( std::ostream& out, Ref const& rhs );


typedef std::map< std::string, unsigned int> PACKAGES_TABLE;
typedef std::map< std::string, unsigned int> ITEMS_TABLE;
typedef std::map< unsigned int, Ref*> CONTENT_TABLE;
typedef std::map< unsigned int, CONTENT_TABLE* > REF_TABLE;

class ReferenceManager {
public:
	ReferenceManager(): next_package(0), next_content(0)
	    {
	        //CONTENT_TABLE* content_table = new CONTENT_TABLE;
	        ref_table = new REF_TABLE;
	        //(*ref_table)[0] = content_table;
	        packages_table = new PACKAGES_TABLE;
	        items_table = new ITEMS_TABLE;
	    };
	Ref& reference( std::string const& textual_id );

	/** We'll need a destructor because we have a complicated allocation
	 * of the ref_table.*/
	~ReferenceManager();

	friend std::ostream& operator<<( std::ostream& out,
	                                  ReferenceManager const& rhs );
private:
	/** This is the main lookup table for ids; the first and second keys
	 *  correspond exactly to the first and second fields of a ref object.*/
	REF_TABLE* ref_table;
	PACKAGES_TABLE* packages_table;
	ITEMS_TABLE* items_table;
	unsigned int next_package;
	unsigned int next_content;

};

std::ostream& operator<<(std::ostream& out, ReferenceManager const& rhs );

}
#endif
