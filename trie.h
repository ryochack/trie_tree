#ifndef __TRIE_H__
#define __TRIE_H__

typedef void* TRIE;

TRIE Trie_Make(void);

void Trie_Free(TRIE p);

TRIE Trie_Put(TRIE p, const char* key, void* value);

void* Trie_Get(TRIE p, const char* key);

void Trie_Show(TRIE p);

#endif
