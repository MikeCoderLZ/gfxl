#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <string>
#include <ifstream>

namespace gfx {

/**
 * The ResourceManager and it's satellite classes deals with the loading of
 * raw resource files.  Thus, it does not distinguish between script files,
 * dialogue files, or initialization files because they are all a "text"
 * resource.
 *
 * */

class ResourceManager;

class ResourceHandle {
public:

	friend class ResourceManager;
protected:
	inline void init( ResourceManager* const newManager,
					  std::string& newFilepath ) { manager = newManager;
												   filepath = newFilepath; };
	// This is the owner of the handle
	ResourceManager* const manager;
	std::string& filepath;
private:
	// Only ResourceManagers may create ResourceHandles and there is no
	// default state for a handle; all handles are owned.
	ResourceHandle( ResourceManager* const newManager,
					std::string& newFilepath ) { init( newManager, newFilepath ); };

};

class TextResource : public ResourceHandle {
public:
	std::string& get();
	friend class ResourceManger;
private:
	TextResource( ResourceManager* const newManger,
				  std::string& newFilepath ) { init( newManager, newFilepath ); };
	std::string* contents;
};

class ResourceManager {
public:
	ResourceManager();
	TextResource get_text_resource( std::string& filename );
	// Texture get_texture( std::string& filename );
	// Shader get_shader( std::string& filename );
	// Script get_script( std::string& filename );
	// Mesh get_mesh( std::string& filename );

};

}

#endif
