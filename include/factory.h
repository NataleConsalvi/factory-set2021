#ifndef FACTORY_H
#define FACTORY_H

#include "smart.h"
#include "machines.h"

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <queue>


using std::unordered_map;
using std::string;
using std::endl;
using std::cout;
using std::ostream;
using std::deque;


class Factory {
    private:
        unordered_map<string, AssemblyLine*> factory;   //linee presenti in factory
        unordered_map<string, Machine*> machines;       //macchine presenti in factory
        unordered_map<string, Product*> products;       //prodotti che si possono realizzare in factory

    public:
        /*
        Factory(){

        }  

        ~Factory(){

        }
        */

        //aggiungere macchina in factory
        void addMachine(const string& name, const int& maintenance){
            cout << "DEBUG: adding machine " << name << " maintenance: " << std::to_string(maintenance) << endl;
            Machine* new_machine = new Machine;
            new_machine->set_name(name);
            new_machine->set_maintenance(maintenance);
            this->machines[name] = new_machine;
        }

        //aggiungere una linea d'assemblaggio in factory
        void addAssemblyLine(string name, int maintenance, vector<string> line){
            AssemblyLine* new_line = new AssemblyLine;
            new_line->set_name(name);
            new_line->set_maintenance(maintenance);
            new_line->insert_machines(line, this->machines);
            this->factory[name] = new_line;
            cout << "DEBUG: adding " << new_line->as_string();
        }

        //aggiungere un prodotto realizzabile
        void addProduct(string name, vector<string> steps){
            if(this->products.count(name) == 1){
                cout << "DEBUG: prodotto già presente in inventario!"<< endl;
            }else{
                Product* new_product = new Product;
                new_product->set_name(name);
                new_product->set_steps(steps);
                this->products[name] = new_product;
                cout << "DEBUG: adding " << new_product->as_string();
            }

        }

        //aggiungere alla linea che lo produrrà il prodotto che si vuole realizzare
        void enqueue(string product_name){
            if(this->products.count(product_name) == 0){
                cout << "DEBUG: Prodotto non prensente nell'inventario!" << endl;
                return;
            }
            for(string line : this->products[product_name]->get_steps()){
                if(this->factory.count(line) == 1){
                    this->factory[line]->add_product(this->products[product_name]);
                }
            }
        }

        //avanzare con gli step
        void step(){
            cout << "DEBUG: start step" << endl;
            cout << this->factory["A"]->as_string();
            this->factory["A"]->step_line();
        }


        
};


#endif // FACTORY_H