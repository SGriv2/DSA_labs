#include "sfTree.h"

SuffixTree::SuffixTree(string& str) : text(str)
{
        BuildSuffixTree();
}

void SuffixTree::BuildSuffixTree()
{
    activeNode = root;
    for (size_t i = 0; i <= text.length(); i++) {
        ExtendSuffixTree(i);
    }
}

int SuffixTree::EdgeLength(Node* node)
{
    return *(node->end) - (node->start) + 1;
}

void SuffixTree::ExtendSuffixTree(int phase)
{
    lastCreatedInternalNode = nullptr;
    leafEnd++;
    remainingSuffixCount++;

    while (remainingSuffixCount > 0)
    {
        if (activeLength == 0)
            activeEdge = phase; 

        auto find = activeNode->children.find(text[activeEdge]);
        if (find == activeNode->children.end())
        {
                activeNode->children.insert(make_pair(         
                text[activeEdge],
                new Node(root, phase, &leafEnd, phase - remainingSuffixCount + 1)));

            if (lastCreatedInternalNode != nullptr)
            {
                lastCreatedInternalNode->suffix_link = activeNode;
                lastCreatedInternalNode = nullptr;
            }
        }
        else
        {
            Node* next = find->second;     
            int edge_length = EdgeLength(next);

            if (activeLength >= edge_length)
            {
                activeEdge += edge_length;
                activeLength -= edge_length;
                activeNode = next;
                continue;
            }

            if (text[next->start + activeLength] == text[phase])
            {
                if (lastCreatedInternalNode != nullptr && activeNode != root)    
                    lastCreatedInternalNode->suffix_link = activeNode;           
                     activeLength++;                                             
                break; 
            }

            Node* split = new Node(root, next->start, new int(next->start + activeLength - 1));
            activeNode->children[text[activeEdge]] = split;            
            next->start += activeLength;                               
            split->children.insert(make_pair(text[phase], new Node(root, phase, &leafEnd, phase - remainingSuffixCount + 1)));
            split->children.insert(make_pair(text[next->start], next));
            if (lastCreatedInternalNode != nullptr)
                lastCreatedInternalNode->suffix_link = split;
            lastCreatedInternalNode = split;
        }

        remainingSuffixCount--;

        if (activeNode == root && activeLength > 0)
        {
            activeLength--;
            activeEdge++;
        }
        else if (activeNode != root) 
            activeNode = activeNode->suffix_link;
    }
}

void SuffixTree::GetSuffixIndexs(Node* node, vector<int>& vec)
{
    if (!node)
        return;
    for (auto it : node->children) 
        GetSuffixIndexs(it.second, vec);
    if (node->suffix_index != -1) 
        vec.push_back(node->suffix_index);
}

void SuffixTree::PrintSuffixs() {
     vector <int> VecSuffTree;
     GetSuffixIndexs(root, VecSuffTree);
    for (int i = 0; i < VecSuffTree.size(); i++) {
        cout << "\"";
        for (int j = 0; j < VecSuffTree[i]; j++) {
            cout << text[j];
        }
        cout << "\"" << endl;
    }
}

bool SuffixTree::Find(string Pstr) {
    if (Pstr.empty()) {
        return true;
    } 
    Node* current_node = root;
    string finded_str = "";
    int depth_edge = 0;
    int total_depth = 0;

    // èùåì ðåáðî
    auto finded_edge = current_node->children.find(Pstr[0]);
    if (finded_edge == current_node->children.end()) {
        return false;
    }
    Node* finded_node = finded_edge->second;

    while (Pstr != finded_str) {
        
        if (finded_edge == current_node->children.end()) {
            return false;
        }
        
        while (depth_edge <= EdgeLength(finded_node)) {
            if (finded_str == Pstr) {
                return true;
            }
            if (depth_edge != EdgeLength(finded_node)) {    
                finded_str += text[finded_node->start + depth_edge];
                if (finded_str[depth_edge] != Pstr[depth_edge]) {
                    return false;
                }
                depth_edge++;
                continue;
            }
            break;
        }
        
        current_node = finded_node;
        total_depth += depth_edge;
        depth_edge = 0;
        finded_edge = current_node->children.find(Pstr[total_depth]);
        if (finded_edge == current_node->children.end()) {
            return false;
        }
        finded_node = finded_edge->second;
    }
    return true;
}