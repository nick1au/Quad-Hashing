// Bigram.h

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : Nicholas Lau
// St.# : 301290893
// Email: nla52@sfu.ca
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

#include "Bigram_base.h"
#include <string>
#include <iostream>
#include <vector>
#include "cmpt_error.h"

using namespace std;
//
// Put any other standard includes or helper functions/classes you need ...
//



class Bigram : public Bigram_base {
private:
    // Bigram container
	struct B_container{
		Bigram_key b;
		int val;
	};
	int n; // size
    int N; // capacity
	vector<B_container*> hash_table;

    int max_vals; // First alphabetical Max value with locations in hash table
    int min_vals; // First alphabetical Min value with locations in hash table
public:

	Bigram(){
        //hash_table.reserve(20);
        for (int i = 0; i < 20; i++){
            create_empty();
        }
        N = 20;
        n = 0;
	}

	~Bigram(){
		while (N != 0 && hash_table.size() != 0){
            //if (hash_table.at(count-1)->b.first != ""){
                //del_replace_w_loc(count - 1, );
            //}
            B_container* to_del = hash_table.at(hash_table.size() - 1);
            delete to_del;
            hash_table.pop_back();
            N--;

        }
	}

	
    // Implement all the non-implemented methods from Bigram_base here. Be
    // sure to include a default constructor that creates a new empty Bigram.


    // Pre-condition:
    //    none
    // Post-condition:
    //    Returns the number of pairs in this map.
    // Performance:
    //    O(1) worst-case.
    int size() const {
    	return n;
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    Returns the size of the underlying vector for this map.
    // Performance:
    //    O(1) worst-case.
    int capacity() const{
    	return N;
        //return hash_table.size();
    }


    // Pre-condition:
    //    none
    // Post-condition:
    //    Returns true if there is a pair in this map with the given
    //    key, and false otherwise.
    // Performance:
    //    O(1) average-case number of comparisons.
    bool contains(const Bigram_key& key) const{
        if (n == 0){
            return false;
        }
        int str2int = convert_to_int(key.first, key.second);
        int i = 0;
        while(1){
            int hash_num = hash_func(i,str2int);
            const string test = hash_table.at(hash_num)->b.first;

            if (key <= hash_table.at(hash_num)->b && hash_table.at(hash_num)->b <= key){
                cout << "hash = " << hash_num;
                return true;
            
            }
            else if (hash_table.at(hash_num)->b.first == "" && hash_table.at(hash_num)->b.second == ""){
                return false;
            }
            i++;
        }
        
        return false;
    }

    // Pre-condition:
    //    contains(key)
    // Post-condition:
    //    Returns the value associated with key.
    // Performance:
    //    O(1) average-case number of comparisons.
    int value_of(const Bigram_key& key) const{
        if (!contains(key)){
            cmpt::error("CANNOT RETURN VALUE SINCE DNE");
        }
        else{
            int str2int = convert_to_int(key.first, key.second);
            int i = 0;
            while(1){
                int hash_num = hash_func(i,str2int);
                const string test = hash_table.at(hash_num)->b.first;

                if (key <= hash_table.at(hash_num)->b && hash_table.at(hash_num)->b <= key){
                    cout << hash_table.at(hash_num)->b.first;
                    return hash_table.at(hash_num)->val;
            
                }
                i++;
            }
        }

        return -1;
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    contains(key) and value_of(key) == val
    // Performance:
    //    O(1) average-case number of comparisons.
    void put(const Bigram_key& key, int val){
        if (key.first == "" && key.second == ""){
            cmpt::error("KEY CANNOT BE EMPTY. AT LEAST ONE STRING REQUIRED FOR HASHING.");
        }
        B_container* obj = new B_container;
        obj->b = key;
        obj->val = val;

        int str2int = convert_to_int(key.first, key.second);
        int hash_num = get_hash_num(str2int);

        del_replace_w_loc(hash_num, obj);
        cout << endl << "PUT" << "-" << key.first << " " << key.second << "-" << str2int << "-" << hash_num;

        if (n == 0){ // IF NO ELEMENTS, ASSIGN FIRST KEY TO BOTH MAX AND MIN
            min_vals = hash_num;
            max_vals = hash_num;
        }
        else{
            // CURR VAL < MIN IN TABLE
            if ((val < hash_table.at(min_vals)->val)){
                min_vals = hash_num;
            }
            // CURR VAL = MIN IN TABLE AND CURR BIGRAM STR IS ALPHABETICALLY BEFORE MIN IN TABLE
            else if ((val == hash_table.at(min_vals)->val) && (key <= hash_table.at(min_vals)->b)){
                min_vals = hash_num;
            }
            // CURR VAL > MAX IN TABLE
            if ((val > hash_table.at(max_vals)->val)){
                max_vals = hash_num;
            }
            // CURR VAL = MIN IN TABLE AND CURR BIGRAM STR IS ALPHABETICALLY BEFORE MIN IN TABLE
            else if ((val == hash_table.at(max_vals)->val) && (key <= hash_table.at(max_vals)->b)){
                max_vals = hash_num;
            }
        }
        n++; // SIZE + 1

        if (need_to_refactor()){
            cout << "REFACTOR";
            re_order_factor(); // RE-HASH IF NECESSARY
        }


    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    !contains(key)
    // Performance:
    //    O(1) average-case number of comparisons.
    void remove(const Bigram_key& key){
        if (n == 0){
            cmpt::error("EMPTY MAP. NOTHING TO REMOVE");
        }
        if (!contains(key)){
            cmpt::error("Given key DNE in hash table");
        }

        cout << "REMOVING CONTAINED IS " << contains(key);

        int str2int = convert_to_int(key.first, key.second);
        int i = 0;// REP COUNTER
        while(1){
            int hash_num = hash_func(i,str2int);

            if (key <= hash_table.at(hash_num)->b && hash_table.at(hash_num)->b <= key){
                B_container* to_del = hash_table.at(hash_num);

                // INSERT EMPTY KEY AT LOC
                B_container* empty = new B_container;
                empty->b.first = "";
                empty->b.second = "";
                hash_table.at(hash_num) = empty;
                //DELETE ORGIINAL
                delete to_del;
                n = n-1;
                return;
            }
            i++;
        }

    }

    // Pre-condition:
    //    !is_empty()
    // Post-condition:
    //    Returns the key in this map with the largest associated
    //    value. If there is more than one (key, value) pair tied
    //    for the largest value, then return the alphabetically
    //    first one.
    // Performance:
    //    O(1) worst-case (not average-case!) number of comparisons.
    Bigram_key max() const{
        if (size() == 0){
            cmpt::error("EMPTY MAP");
        }
        else{
            return hash_table.at(max_vals)->b;
        }
        
    }

    // Pre-condition:
    //    !is_empty()
    // Post-condition:
    //    Returns the key in this map with the smallest associated
    //    value. If there is more than one (key, value) pair tied
    //    for the smallest value, then return the alphabetically
    //    first one.
    // Performance:
    //    O(1) worst-case (not average-case!) number of comparisons.
    Bigram_key min() const{
        if (size() == 0){
            cmpt::error("EMPTY MAP");
        }
        else {
            return hash_table.at(min_vals)->b;
        }
    }

    // Pre-condition:
    //    NONE
    // Post-condition:
    /*    Return the hash number using the quadratic probing
    */   
    // Performance:
    //    O(1) worst case
    int hash_func(int i, int x) const{
        int sec = x + i^2; // quadratic
        int primary = sec%N;
        return primary;
    }

    // Pre-condition:
    //    NONE
    // Post-condition:
    /*    Reordered hash table with new size
    */   
    // Performance:
    //    O(n)
    void re_order_factor(){
        vector<B_container*> v = hash_table; // copy to new vector
        B_container* min = v.at(min_vals); // Bigram of min val
        B_container* max = v.at(max_vals); // bigram of max val
        
        int old_cap = capacity();
        for (int i = 0; i < capacity(); i++){ //delete entire hash_table
            hash_table.pop_back();
        }

        for (int i = 0; i < old_cap*2; i++){ // rebuild new table
            create_empty();
        }

        N = hash_table.size();

        for (int i = old_cap-1; i >= 0; i--){ // ITER DOWN OLD HASH TABLE
            if (v.at(i)->b.first != "" || v.at(i)->b.second != ""){ // FIND NON-EMPTY KEY
                int strnum = convert_to_int(v.at(i)->b.first, v.at(i)->b.second);
                int hash_num = get_hash_num(strnum);
                del_replace_w_loc(hash_num, v.at(i)); // PUT KEY IN OLD TABLE INTO NEW ONE W/ NEW HASH
                if (hash_table.at(hash_num) == min){ // SEE IF MIN KEY AND REASSIGN MIN_VAL LOC
                    min_vals = hash_num;
                }
                else if (hash_table.at(hash_num) == max){// SEE IF MAX KEY AND REASSIGN MAX_VAL LOC
                    max_vals = hash_num;
                }
            }
            
        }

        // DELETE OLD HASH TABLE
        for (int i = old_cap-1; i >= 0; i--){
            if (v.at(i)->b.first == "" && v.at(i)->b.second == ""){// DELETE POINTER TO EMPTY KEY AND VECTOR POS
                B_container* to_del = v.at(i);
                v.pop_back();
                delete to_del;
            }
            else{
                v.pop_back(); // POP BACK VECTOR ONLY IF NON-EMPTY
            }
            
        }
    }

    // Pre-condition:
    //    NONE
    // Post-condition:
    /*    Return boolean if re-factor is needed base on load factor
    */   
    // Performance:
    //    O(1) worst case
    bool need_to_refactor(){
        return load_factor() >= 0.5;
    }
    

    // Pre-condition:
    //    NONE
    // Post-condition:
    /*    Return int of the two strings converted by adding each character 
          together with an incrementing amount on the position of the string.

          CASE-SENSITIVE
    */   
    // Performance:
    //    O(1) worst case
    int convert_to_int(string first, string second) const{
        int first_int = 0, second_int = 0;
        if (first != ""){ // ADD FIRST STR
            for (int i = 0; i < first.size(); i++){
                first_int = first_int + first.at(i)*(i+1); // ADD ASCII CHAR * POS + 1
            }
            if (second.size() == 0){
                return first_int;
            }
        }
        if (second != ""){ // ADD SECOND STR
            for (int i = 0; i < second.size(); i++){
                second_int = second_int + second.at(i)*(i+1);
            }
        }
        return first_int + second_int;
    }

    // Pre-condition:
    //    NONE
    // Post-condition:
    /*    Have the hash table position given swapped with the new Bigram container
          and the original deleted
    */   
    // Performance:
    //    O(1) worst case
    void del_replace_w_loc(int loc, B_container* replace){
        B_container* to_del = hash_table.at(loc);
        hash_table.at(loc) = replace;
        delete to_del;
    }

    // Pre-condition:
    //    NONE
    // Post-condition:
    /*    Return the hash number needed to swap. If the location is not empty, then try again
    */   
    // Performance:
    //    O(1) worst case
    int get_hash_num(int strnum) const{
        int rep = 0; // NOT EMPTY, THEN LOOP WITH i = 1,2,3...
        int hash_num;
        while (1){
            hash_num = hash_func(rep,strnum);
            if (hash_table.at(hash_num)->b.first == "" && hash_table.at(hash_num)->b.second == ""){
                break;
            }
            rep++;
        }
        return hash_num;
    }

    // Pre-condition:
    //    NONE
    // Post-condition:
    /*    Hash table containing an empty Bigram container
    */   
    // Performance:
    //    O(1) worst case
    void create_empty(){
        B_container* obj = new B_container;
        obj->b.first = "";
        obj->b.second = "";
        hash_table.push_back(obj);
    }


}; // class Bigram