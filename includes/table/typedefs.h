#ifndef TYPEDEF_H
#define TYPEDEF_H

#include "../bplustree/map.h"
#include "../bplustree/multimap.h"
#include "../queue/MyQueue.h"
#include "../token/token.h"

#include<vector>
#include<queue>
using namespace std;

typedef Map <string, string> map_ss;
typedef Map <string, long> map_sl;
// typedef Map <string, MMap<string, long> > map_sl; //maybe

typedef MMap <string, string> mmap_ss;
typedef MMap <string, long> mmap_sl;

typedef vector <string> vectorstr;
typedef vector <long> vectorlong;

typedef Queue<string> queuestr;
// typedef Queue<Token *> queofTokens;

#endif