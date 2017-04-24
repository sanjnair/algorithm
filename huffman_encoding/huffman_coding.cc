struct Symbol {
    char c;
    double prob;
    string code;
};

struct Node {
    double prob;
    Symbol* s;
    shared_ptr<Node> left;
    shared_ptr<Node> right;
};

void assignHuffmanCode(
    const shared_ptr<Node>& r,
    const string& s)
{
    if (r) {
        // This node (i.e. leaf contains symbol)
        if (r->s) {
            r->s->code = s;
        }
        else { // non-leaf node
            assignHuffmanCode(r->left, s + '0');
            assignHuffmanCode(r->right, s + '1');
        }
    }
}

void huffmanCoding(vector<Symbol>* symbols) {
    // initially assign each symbol into a min_heap
    priority_queue<
        shared_ptr<Node>, vector<shared_ptr<Node>>,
        function<bool(shared_ptr<Node>, shared_ptr<Node>)>>
    min_heap([](const shared_ptr<Node>& lhs,
                const shared_ptr<Node>& rhs) -> bool {
        return lhs->prob > rhs->prob;
    });

    for (auto& s : *symbols) {
        min_heap.emplace(new Node{ s.prob, &s, nullptr, nullptr });
    }

    // keep combining two node until there is one node left
    while (min_heap.size() > 1) {
        shared_ptr<Node> l = min_heap.top(); min_heap.pop();
        shared_ptr<Node> r = min_heap.top(); min_heap.pop();

        min_heap.emplace(new Node{ l->prob + r->prob, nullptr, l, r });
    }

    // Traverse the binary tree, assigning codes to nodes
    assignHuffmanCode(min_heap.top(), string());
}
