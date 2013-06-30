#include "cellarray.h"

Bc::Bc()
{
    // set dictionary
    dictionary_.push_back("periodic");
    dictionary_.push_back("prescribed");
    dictionary_.push_back("immersed");

    loc_ = -1;
    type_ = "periodic";
}

Bc::Bc(int loc, std::string type)
{
    // set dictionary
    dictionary_.push_back("periodic");
    dictionary_.push_back("prescribed");
    dictionary_.push_back("immersed");

    // check if type is in the dictionary
    bool is_known = false;
    for(unsigned int i=0;i<dictionary_.size() && !is_known;i++) is_known = (type == dictionary_[i]);

    if(!is_known) {
        std::cout << "Unknown boundary condition type at boundary " << loc << ". Assuming periodic..." << std::endl;
        print();
        type_ = "periodic";
    }
    else type_ = type;

    // check if loc is a correct location
    if(loc*loc == 1) loc_ = loc;
    else throw std::invalid_argument("loc must be -1 (left) or 1 (right)");
}

void Bc::print()
{
    std::cout << "Available boundary condition types are:" << std::endl;
    for(unsigned int i=0;i<dictionary_.size();i++) std::cout << dictionary_[i] << std::endl;
}

std::string Bc::type()
{
    return type_;
}

int Bc::loc()
{
    return loc_;
}

CellArray::CellArray(double L, int N, double llc, Bc left, Bc right) : l_(L), n_(N), llc_(llc), left_(left), right_(right)
{
}
