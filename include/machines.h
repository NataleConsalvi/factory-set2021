#ifndef MACHINE_H
#define MACHINE_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <queue>

using std::string;
using std::stringstream;
using std::deque;

class Machine{
    private:
        string name;
        int maintenance;
        int cicle;
    public:

        Machine(){
            this->name = "";
            this->maintenance = 0;
            this->cicle = 0;
        }
        const string get_name() const{
            return this->name;
        }
        const int get_maintenance() const{
            return this->maintenance;
        }

        void set_name(string name){
            this->name = name;
        }

        void set_maintenance(int maintenance){
            this->maintenance = maintenance;
        }

        void increase_cicle(){
            this->cicle++;
        }

        const int get_cicle() const{
            return this->cicle;
        }

};

class Product{
    private:
        string name;
        vector<string> steps;
    public:
        void set_name(const string& name){
            this->name = name;
        }
        void set_steps(const vector<string>& steps){
            this->steps = steps;
        }

        const vector<string> get_steps() const{
            return this->steps;
        }

        string as_string() const{
            stringstream ss;
            ss << "product type " << this->name;
            ss << ", plan: ";
            for(int i = 0; i < this->steps.size() - 1; i++){
                ss << this->steps[i] << ", ";
            }
            ss << this->steps[this->steps.size() -1] << "\n";
            return ss.str();
        }
};

class AssemblyLine{
    private:
        string name;
        int maintenance;
        vector<Machine*> line;
        deque<Product*> products;
        vector<deque<Machine*>> steps;
    
    public:
        AssemblyLine(string name, int maintenance, vector<Machine*> line){
            this->name = name;
            this->maintenance = maintenance;
            this->line = line;
        }

        AssemblyLine(){
            this->name = "";
            this->maintenance = 0;
            this->line = {};
        }

        ~AssemblyLine(){
            cout << "DEBUG: AssemblyLine destructor" << endl;
            for (int i = 0; i < this->line.size() - 1; i++) {
                Machine* current = this->line[i];
                Machine* pnext = line[i + 1];
                delete current;
                current = pnext;
            }
        }

        void set_name(string name){
            this->name = name;
        }

        void set_maintenance(int maintenance){
            this->maintenance = maintenance;
        }

        void insert_machines(vector<string>& line, const unordered_map<string,Machine*>& machines){

            for(string s : line){
                if(machines.count(s) == 1){
                    this->line.push_back(machines.at(s));
                }else{
                    throw std::invalid_argument(string("in factory there is not the machine " + s));
                }
            }
        }
        
        deque<Machine*> analyze_product(Product* product){
            deque<Machine*> steps;
            for(string s : product->get_steps()){
                if(s != this->name){
                    
                    for(Machine* m : this->line){
                        if(m->get_name() == s){
                            steps.push_back(m);
                            break;
                        }
                    }

                }
            }
            return steps;
        }


        void add_product(Product* product){
            this->products.push_back(product);
        }

        void step_line(){            
            if(this->products.size() != 0){
                this->steps.push_back(this->analyze_product(this->products.front()));
                this->products.pop_front();
            }

            for(deque<Machine*> coda : this->steps){
                coda.front()->increase_cicle();
                coda.pop_front();
            }
            
            //stampa situazione
            for(deque<Machine*> coda : this->steps){
                for(Machine* m : coda){
                    cout << "\t" <<  m->get_name() << ": " << std::to_string(m->get_cicle()) << "/" << std::to_string(m->get_maintenance()) << endl;
                }
            }

        }

        string as_string() const{
            stringstream ss;
            ss << "assembly line " << this->name;
            ss << ", maintenance: " << this->maintenance;
            ss << ", machines: ";
            for(int i = 0; i < this->line.size() - 1; i++){
                ss << this->line[i]->get_name() << ", ";
            }
            ss << this->line[this->line.size() -1]->get_name() << "\n";

            return ss.str();
            //ss << "\t" << this->name << "\t"
        }
};


#endif // MACHINE_H