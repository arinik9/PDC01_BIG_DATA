#ifndef __HASHMAP_H__
#define __HASHMAP_H__

class HashMap
{

	public :

	int hash(std::string s);

	void* insert(std::string s);

	void* search(std::string s);

	HashMap();
	HashMap(int size);

	~HashMap();
			
	private :

	void* table;

};

#endif __HASHMAP_H__ 
