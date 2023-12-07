/*
 *	A simple implementation of a hashmap that uses chaining to resolve conflicts.
 *	We have:
 *		i) a struct ListNode, that contains the key, value and the pointer to the next listnode.
 *		ii) a struct Slot, which contains the head of the linked list. The hashmap will contain
 *			an array of this type.
 *		iii) a class HashMap.
*/

#include <functional>
#include <stdint.h>

/*
 * A blueprint for each key-value pair that is to be stored.
 * It contains the key, value and the a pointer pointing to the next key-value pair.
*/
template <typename Key, typename Value>
struct ChainNode {
	// The key.
	Key _key;
	// The value associated to the key.
	Value _value;
	// The next chain node.
	struct ChainNode<Key, Value>* _next;
};

/*
 * A slot represents an index in the hash table array.
 * It holds a pointer pointing to the head of the chain of keys at this index.
*/
template <typename Key, typename Value>
struct Slot {
	// Pointer pointing to the head of the chain at a particular slot in the hash table array.
	struct ChainNode<Key, Value>* _head;
};

/*
 * Hashmap implementation.
*/
template <
	typename Key,
	typename Value, 
	typename Hash = std::hash<Key>, 
	typename KeyEquals = std::equal_to<Key>
>
class HashMap {
private:
	// Length of the hash table array.
	std::size_t _size;
	// Hash table array.
	std::vector<Slot<Key, Value>> _array;
public:
	
	HashMap(const uint32_t& sz) : _size{sz} {
		// TODO: I don't think this bit of code will work.
		_array.reserve(_size);
		for (int i = 0; i < _size; ++i) {
			_array[i]._head = nullptr;
		}
	}
};
