#include "referenceManager.hpp"

namespace gfx {

std::ostream& operator<<( std::ostream& out, Ref const& rhs )
{
    out << rhs.textual_id << std::endl;

    return out;
}

Ref& ReferenceManager::reference( std::string const& textual_id )
{
    /** First, investigate the textual_id.*/

    /**Dissect the textual id; note this procedure depends
     * on the behavior of find() returning the first occurrence
     * of '.'.
     *
     * Possibly use the regex standard header later.*/

    size_t first_period = textual_id.find( '.' );

    /** throw exception here if there is no package id!! */

    std::string package = textual_id.substr( 0, first_period );
    std::string content = textual_id.substr( first_period + 1 );

    std::cout << "package: " << package << std::endl;
    std::cout << "content: " << content << std::endl;

    unsigned int package_id = 0;
    /** First see if we have already made reference to the
     * content's package. */
    std::cout << "the count: " << packages_table->count( package ) << std::endl;
    if( 0 != packages_table->count( package ) ){

        /**We have, so inherit the numeric id*/
        package_id = (*packages_table)[package];
    } else {
        /**We haven't, so generate a new one*/
        package_id = next_package;
        /**And increment next_package; remember next_package
         * will have to go in order to avoid reference
         * fragmentation and leaks*/
        ++next_package;
        /**Now add a new entry in the packages table*/
        (*packages_table)[package] = package_id;

        /**Now we need a content table for the ref table under the
         * package ID*/
        CONTENT_TABLE* new_content_table = new CONTENT_TABLE;
        (*ref_table)[package_id] = new_content_table;
    }

    /** Create and insert a new content id.
     * This will have to be more interesting later, too*/
    unsigned int content_id = next_content;
    ++next_content;

    (*items_table)[content] = content_id;

    /** Create a new reference for this content. */
    std::cout << "textual_id: " << textual_id << std::endl;
    Ref* new_ref = new Ref( *this,
                            textual_id,
                            package_id,
                            content_id );
    std::cout << *new_ref << std::endl;
    /** Add the reference to the content table in the ref table */
    (*(*ref_table)[package_id])[content_id] = new_ref;

    /**This is going to have to be WAY more complicated later.*/
    return *new_ref;
}

ReferenceManager::~ReferenceManager()
{
}


std::ostream& operator<<( std::ostream& out, ReferenceManager const& rhs )
{
    REF_TABLE::iterator package;
    CONTENT_TABLE::iterator content;

    out << "next_package: " << rhs.next_package << '\n';
    out << "next_content: " << rhs.next_content << std::endl;

    out << "Reference Table:" << std::endl;

    for( package = rhs.ref_table->begin();
         package != rhs.ref_table->end();
         package++ ) {
        for( content = package->second->begin();
             content != package->second->end();
             content++) {
            out << "[" << package->first << ",";
            out << content->first << "] -> ";
            out << *(content->second) << std::endl;
        }
    }

    return out;
}

}
