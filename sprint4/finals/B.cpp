// accepted parcel ID: 83264636
//
// Fixed size hash table realisation.
// 
// Hash table itslelf is incapsulated in HashTable class. CLI class is used to 
// handle HashTable -- CommandLine interaction.
//
// The table is implemented via buckets as a collection (std::vector) of 
// std::lists. Any hash function may be used. To choose a bucket Knuth's 
// multiplication strategy is used.
//
// As any regular realiziation of hash table, given the data of size n, 
// HashTable would use O(n) memory space to store it, and would need O(1) 
// time at average for search, insert and removal operations.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <functional>
#include <algorithm>
#include <cmath>

const uint32_t DEFAULT_P = 21; //default hash table size 2^21

//______________________________Record_struct___________________________________

template<class Key, class Value>
struct Record {
    Key   key;
    Value value;

    Record(const Key &key = Key(), const Value &value = Value()) :
                                                                key(key), 
                                                                value(value) {};
};

template<class Key, class Value>
inline bool operator==( const Record<Key,Value> &lhs, 
                        const Record<Key,Value> &rhs) {
    return lhs.key == rhs.key;
}
//______________________________________________________________________________


//_________________________Hash_Table_definition________________________________

template<class Key, class Value, class Hash = std::hash<Key>>
class HashTable {
    typedef Record<Key, Value> TableRecord;
    typedef std::list<TableRecord> Bucket;
    static const uint32_t s = 2654435769;

    uint32_t p;
    uint32_t bucket_count;
    std::vector<Bucket> buckets;
    Hash hash;
    
          Bucket& get_bucket(Key key);
    const Bucket& get_bucket(Key key) const;

public:
    HashTable(int p = DEFAULT_P) :  p(p),
                                    bucket_count(pow(2,p)),
                                    buckets(bucket_count), 
                                    hash(Hash()) {};
    
    void    put(Key key, Value value);
    Value   get(Key key) const;
    Value   pop(Key key);
};

//______________________________________________________________________________


//_________________________CLI_definition_______________________________________

template<class Key, class Value, class Hash = std::hash<Key>>
class CLI {
    struct Command {    std::string         name;
                        Record<Key, Value>  args;
    };
    struct Response{    Value   value;    
                        bool    non_void;

        Response(const Value &value = Value(), const bool &non_void = false) :
                                        value(value), non_void(non_void) {};
    };

    HashTable<Key, Value, Hash> &hash_table;
    std::ifstream &in;
    std::ofstream &out;

    Command  readLine();
    Response executeCommand(const Command &command);

public:
    CLI(HashTable<Key, Value, Hash> &hash_table, std::ifstream &in,
                                                 std::ofstream &out) :
                                     hash_table(hash_table),    in(in),
                                                                out(out) {};
    void runSession(int session_length);
};
//______________________________________________________________________________


//==============================================================================

struct RJ_hash {
    uint32_t operator() (uint32_t a) const {
        a = (a+0x7ed55d16) + (a<<12);
        a = (a^0xc761c23c) ^ (a>>19);
        a = (a+0x165667b1) + (a<<5);
        a = (a+0xd3a2646c) ^ (a<<9);
        a = (a+0xfd7046c5) + (a<<3);
        a = (a^0xb55a4f09) ^ (a>>16);
        return a;
    }
};

int readNum(std::ifstream &in);

int main() {
    std::ifstream in;  in.open ("input.txt" );
    std::ofstream out; out.open("output.txt");

    HashTable<int,int, RJ_hash> hash_table;
    CLI cli(hash_table, in, out);

    int n = readNum(in);
    cli.runSession(n);

    in.close();
    out.close();
    return 0;
}

//==============================================================================


//_____________________Hash_Table_implementation________________________________

template<class Key, class Value, class Hash>
typename HashTable<Key, Value, Hash>::Bucket& 
         HashTable<Key, Value, Hash>::get_bucket(Key key) {

    return buckets[(uint32_t(hash(key))*s) >> (32-p)];
}

template<class Key, class Value, class Hash>
const typename HashTable<Key, Value, Hash>::Bucket& 
               HashTable<Key, Value, Hash>::get_bucket(Key key) const {

    return buckets[(uint32_t(hash(key))*s) >> (32-p)];
}

template<class Key, class Value, class Hash>
void HashTable<Key, Value, Hash>::put(Key key, Value value) {

    auto &bucket = get_bucket(key);
    auto pos = std::find(bucket.begin(), bucket.end(), TableRecord(key));
    if (pos == bucket.end()) {
        bucket.push_front(TableRecord(key, value));
    } else {
        pos->value = value;
    }
    return;
}

template<class Key, class Value, class Hash>
Value HashTable<Key, Value, Hash>::get(Key key) const {
    
    auto &bucket = get_bucket(key);
    auto pos = std::find(bucket.begin(), bucket.end(), TableRecord(key));
    if (pos == bucket.end()) {
        throw "None";
    }
    
    Value found_value = pos->value;
    return found_value;
}

template<class Key, class Value, class Hash>
Value HashTable<Key, Value, Hash>::pop(Key key) {

    auto &bucket = get_bucket(key);
    auto pos = std::find(bucket.begin(), bucket.end(), TableRecord(key));
    if (pos == bucket.end()) {
        throw "None";
    }

    Value popped_value = pos->value;
    bucket.erase(pos);
    return popped_value;
}
//______________________________________________________________________________


//_________________________CLI_implementation___________________________________

template<class Key, class Value, class Hash>
void CLI<Key, Value, Hash>::runSession(int session_length) {

    for (int i = 0; i < session_length; ++i) {
        auto command = readLine();

        try {
            auto result = executeCommand(command);
            if (result.non_void) {
                out << result.value << std::endl;
            }
        } catch (const char* err) {
            out << err << std::endl;
        }
    }
    return;
}

template<class Key, class Value, class Hash>
typename CLI<Key, Value, Hash>::Command 
         CLI<Key, Value, Hash>::readLine() {

    std::string line;
    getline(in, line);
    auto iss = std::istringstream(line);
    
    Command command;
    iss >>  command.name;
    iss >>  command.args.key;
    iss >>  command.args.value;
    return  command;
}

template<class Key, class Value, class Hash>
typename CLI<Key, Value, Hash>::Response
         CLI<Key, Value, Hash>::executeCommand
  (const CLI<Key, Value, Hash>::Command &command) {

    if (command.name == "get") {
        return Response(hash_table.get(command.args.key), true);
    }
    if (command.name == "put") {
        hash_table.put(command.args.key, command.args.value);
        return Response(Value(), false);
    }
    if (command.name == "delete") {
        return Response(hash_table.pop(command.args.key), true);
    }
    throw "error: invalid command";
}
//______________________________________________________________________________

int readNum(std::ifstream &in) {
    int x;
    in >> x;
    in.ignore();
    return x;
}