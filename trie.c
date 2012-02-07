#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "trie.h"

#ifdef DEBUG_ON
#define LOG(...) printf(__VA_ARGS__)
#else
#define LOG(...)
#endif

typedef struct tag_trie {
	char c;
	unsigned int n;
	void *value;
	struct tag_trie **next;
} trie;


static TRIE *st;


trie* trie_make(void) {
	trie *p = (trie*)malloc(sizeof(trie));
	if (p == NULL) return p;

	p->c = 0;
	p->n = 0;
	p->next = NULL;
	p->value = NULL;
	return p;
}


TRIE Trie_Make(void) {
	return (TRIE)trie_make();
}


static void trie_free(trie *p) {
	int i;
	for (i=0; i<p->n; i++) {
		trie_free(p->next[i]);
	}
	free(p);
}


void Trie_Free(TRIE vp) {
	trie_free((trie*)vp);
}


static trie* trie_put(trie *p, const char *key, void *value) {
	trie *match = NULL;
	int i;

	if (*key == 0) {
		p->value = value;
		return p;
	}

	for (i=0; i<p->n; i++) {
		if (p->next[i]->c == *key) {
			/*! Hit */
			match = p->next[i];
			break;
		}
	}

	if (!match) {
		/*! No Hit */
		trie **nodes;
		if (!(match = trie_make()))  return NULL;
		nodes = (trie**)realloc(p->next, (p->n+1) * sizeof(trie*));
		if (!nodes)  return NULL;
		p->next = nodes;
		for (i=0; i<p->n; i++) {
			trie *dp = p->next[i];
		}
		p->next[p->n] = match;
		for (i=0; i<=p->n; i++) {
			//int *dp = (int*)p->next[i];
			trie *dp = p->next[i];
		}
		p->next[p->n]->c = *key;
		p->n++;
	}

	return trie_put(match, key+1, value);
}

TRIE Trie_Put(TRIE vp, const char *key, void *value) {
	st = vp;
	return (TRIE)trie_put((trie*)vp, key, value);
}


void* trie_get(trie *p, const char *key) {
	int i;

	if (*key == 0) {
		return p->value;
	}

	for (i=0; i<p->n; i++) {
		if (*key == p->next[i]->c) {
			return trie_get(p->next[i], key+1);
		}
	}

	return NULL;
}


void* Trie_Get(TRIE vp, const char *key) {
	return (void *)trie_get((trie*)vp, key);
}


static void trie_show(trie *p, int depth, bool *cr) {
	int i;

	if (*cr) {
		for (i=0; i<depth-2; i++) {
			LOG("     ");
		}
		if (depth > 2) {
			LOG("   \\_");
		}
		*cr = false;
	}

	if (depth != 0) {
		LOG("\'%c\', ", p->c);
	}

	if (p->value != NULL) {
		LOG("! \t\t-> \"%s\" \n", (char*)p->value);
		*cr = true;
	} else if (p->n == 0) {
		LOG("\n");
		*cr = true;
	}

	for (i=0; i<p->n; i++) {
		trie_show(p->next[i], depth+1, cr);
	}
}


void Trie_Show(TRIE vp) {
	int i;
	trie *t = (trie*)vp;
	bool cr = false;
	trie_show((trie*)vp, 0, &cr);
}


