#ifndef FIBONACCI_HEAP_VIZ_HPP
#define FIBONACCI_HEAP_VIZ_HPP

#include <list>
#include <iostream>
#include "fibbonachi.hpp"

template<class T, class V>
class FibonacciHeapViz : public FibonacciHeap<T, V> {
private:
    T _id(Node<T, V> *x) {
        return x->getKey();
    }

    void _exportDotNode(std::ostream &out, Node<T, V> *x) {
        if (x == nullptr) return;

        if (x->isMarked()) {
            out << _id(x) << "[fillcolor=grey, style=filled]" << std::endl;
        }
        
        out << _id(x) << "[label=\"" << x->getKey() << " (" << x->getDegree() << ")\"]" << std::endl;

        out << _id(x) << " -> " << _id(x->getLeft()) << "[color=red]" << std::endl;
        out << _id(x) << " -> " << _id(x->getRight()) << "[color=blue]" << std::endl;

        if (x->getParent() != nullptr) {
            out << _id(x) << " -> " << _id(x->getParent()) << "[color=green]" << std::endl;
        }
    }

    void _exportDot(std::ostream &out, Node<T, V> *x, Node<T, V> *stop = nullptr, std::list<std::size_t> level = std::list<std::size_t>()) {
        if (x == nullptr) return;

        if (stop != nullptr && x == stop) {
            out << "{rank=same;";
            for (const auto &n : level) {
                out << " " << n;
            }
            out << ";}" << std::endl;

            return;
        }

        this->_exportDotNode(out, x);

        if (x->getChild() != nullptr) {
            out << _id(x) << " -> " << _id(x->getChild()) << "[color=black]" << std::endl;
            this->_exportDot(out, x->getChild());
        }

        if (stop == nullptr) {
            stop = x;
        }

        level.push_back(_id(x));
        this->_exportDot(out, x->getRight(), stop, level);
    }

public:
    void exportDOT(std::ostream &out = std::cout) {
        out << "digraph G {" << std::endl;
        if (this->minNode == nullptr) {
            out << "}" << std::endl;
            return;
        }

        out << "min -> " << _id(this->minNode) << std::endl;

        this->_exportDot(out, this->minNode);

        out << "}" << std::endl;
    }
};

#endif // FIBONACCI_HEAP_VIZ_HPP