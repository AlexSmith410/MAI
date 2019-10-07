#include "TTrie.h"

TNode::TNode() : suffLink(nullptr), exitLink(nullptr), leaf(false) {}

void addPattern(TNode* root, vector<uint32_t>& pat, size_t patSize) {
    TNode* curNode = root;
    for (auto it : pat) {
        if (curNode->child.find(it) == curNode->child.end())
            curNode->child.insert(make_pair(it, new TNode()));
        curNode = curNode->child.find(it)->second;
    }
    curNode->leaf = true;
    curNode->patSize.push_back(patSize);
}

void CreateLinks(TNode* root, TNode* parent, TNode* node, uint32_t symToNode) {
    TNode* link = parent->suffLink;
    auto findChild = link->child.find(symToNode);
    while (link != root && findChild == link->child.end()) {
        link = link->suffLink;
        findChild = link->child.find(symToNode);
    }
    if (findChild == link->child.end())
        node->suffLink = root;
    else {
        node->suffLink = findChild->second;
        link = node->suffLink;
        if (link->leaf)
            node->exitLink = link;
        else if (link->exitLink)
            node->exitLink = link->exitLink;
    }
}

void processTrie(TNode* root, TNode* node, size_t lvl) {
    if (lvl != 1)
        for (auto it : node->child)
            processTrie(root, it.second, lvl - 1);
    else
        for (auto it : node->child)
            CreateLinks(root, node, it.second, it.first);
}

void processTrie(TNode* root, size_t maxLen) {
    root->suffLink = root;
    for (auto it : root->child)
        it.second->suffLink = root;
    for (size_t i = 1; i < maxLen; i++)
        for (auto it : root->child)
            processTrie(root, it.second, i);
}

void Search(TNode* root, vector< pair<int32_t, pair<size_t, size_t> > >& text, size_t patLen, size_t patCount) {
    size_t textSize = text.size();
    vector<size_t> patInd(textSize, 0);
    TNode* curNode = root;
    TNode* link;
    for (int i = 0; i < (int)textSize; i++) {
        auto findChild = curNode->child.find(text[i].first);
        if (findChild != curNode->child.end())
            curNode = findChild->second;
        else {
            curNode = curNode->suffLink;
            findChild = curNode->child.find(text[i].first);
            while (curNode->suffLink != root && findChild == curNode->child.end()) {
                curNode = curNode->suffLink;
                findChild = curNode->child.find(text[i].first);
            }
            if (findChild != curNode->child.end())
                curNode = findChild->second;
            else curNode = root;
        }
        if (curNode->leaf)
            for (auto it : curNode->patSize)
                if (i - (int)it + 1 >= 0)
                    patInd[i - (int)it + 1]++;
        link = curNode->exitLink;
        while (link) {
            for (auto it : link->patSize)
                if (i - (int)it + 1 >= 0)
                    patInd[i - (int)it + 1]++;
            link = link->exitLink;
        }
        if (!curNode->child.size()) {
            if (curNode->exitLink)
                curNode = curNode->exitLink;
            else
                curNode = curNode->suffLink;
        }
    }
    for (int i = 0; i < (int)textSize - (int)patLen + 1; i++)
        if (patInd[i] == patCount)
            cout << text[i].second.first << ", " << text[i].second.second << endl;
}

void DeleteTrie(TNode* node) {
    for (auto it : node->child)
        DeleteTrie(it.second);
    delete node;
}
