#ifndef NODE_HPP
#define NODE_HPP

/*
 * Class that encapsule a single node of the network
*/
class Node{
    private:
        float value;
        float bias;

    public:
        float getValue() {return value;};
        float getBias() {return bias;};
        void setValue(float v) {this->value = v;};
        void setBias(float b) {this->bias = b;};

        Node(float v, float b): value(v), bias(b) { }
        Node();
};

#endif