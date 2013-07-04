#include "cellarray.h"

#include <boost/lexical_cast.hpp> // int to string

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

CellArray::CellArray(double L, int N, double llc) : l_(L), ni_(N), llc_(llc)
{
    // using a 3 points method: need 2 ghost cells
    no_ = 2;

    n_ = ni_ + no_;

    dx_ = l_/ni_;

    create();
    link();
    initialize();
}

void CellArray::create()
{
    dt_ = 0.8*(Cell (dx_, 1)).get_max_dt();

    grid_.resize(n_);

    // periodic boundary conditions
    grid_[0] = new Cell(dx_, dt_);
    grid_[n_-1] = new Cell(dx_, dt_);

    // OK for every boundary condition type
    for(int i=1;i<n_-1;i++)
    {
        grid_[i] = new Cell(dx_, dt_);
    }
}

void CellArray::link()
{
    // OK for every boundary condition type
    grid_[0]->cr = grid_[n_-1];
    grid_[n_-1]->cl = grid_[n_-2];

    // periodic boundary conditions
    grid_[0]->cl = grid_[n_-1];
    grid_[n_-1]->cr = grid_[0];

    // OK for every boundary condition type
    for(int i=1;i<n_-1;i++)
    {
        grid_[i]->cl = grid_[i-1];
        grid_[i]->cr = grid_[i+1];
    }
}

void CellArray::initialize()
{
    for(int i=0;i<n_;i++)
    {
        grid_[i]->set_u( sin(i*dx_) );
    }
}

std::vector<Cell *> CellArray::get_grid()
{
    return grid_;
}

void CellArray::solve(double T, double t, std::string name)
{
    // current time
    double ct = 0;

    // number of written files
    double wf = 0;

    std::string path;
    std::fstream data;

    while(ct < T)
    {
        update();
        evolve();

        // update every 0.2 seconds
        if( int(ct*10) % 2  == 0 )
        {
            std::cout << "Temps simule : " << ct << "\r";
        }

        // write in file
        if( (int)(ct/t) == wf )
        {
            path =  "Results/" + name + "_" + boost::lexical_cast<std::string>(wf) + ".tsv";
            data.open(path.c_str(), std::ios::out);
            print(data);
            data.close();
            wf++;
        }

        ct += dt_;
    }
}

void CellArray::update()
{
    for(int i=0;i<n_;i++)
    {
        grid_[i]->update();
    }
}

void CellArray::evolve()
{
    for(int i=0;i<n_;i++)
    {
        grid_[i]->evolve();
    }
}

void CellArray::print(std::fstream &data)
{
    for(int i=0;i<ni_;i++)
    {
        data << i*dx_ << "\t" << grid_[i+no_/2]->u << std::endl;
    }
}
