
#include <cstdint>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>

struct ID
{
    ID(const std::string& pair){
        size_t pos = pair.find('-');
        first = pair.substr(0,pos);
        last = pair.substr(pos+1, pair.length());
        // std::cout<<"first: "<< first<<std::endl;
        // std::cout<<"last: "<< last<<std::endl;

    }
    std::string first;
    std::string  last;
};

std::vector<ID> id_reader(const std::string& path){
    std::ifstream ifsr(path);

    // c++ shit
    std::string content( 
        (std::istreambuf_iterator<char>(ifsr)),
        (std::istreambuf_iterator<char>()) 
    );

    std::vector<ID> ids;

    size_t start,end = 0;
    while ( end != std::string::npos){
        end = content.find(',', start);
        auto pair =  content.substr(start, end - start);
        ids.emplace_back(ID(pair));
        start = end + 1;
    }

    return ids;
}

std::string solution(const std::vector<ID>& id){
    return "";
}


int main(){
    
    auto default_input = id_reader("day_2/default_input.txt");
    auto my_input = id_reader("day_2/my_input.txt");

    auto sol1 = solution(default_input);
    auto sol2 = solution(my_input);

    std::cout<<"default solution: "<<sol1<<std::endl;
    std::cout<<"mu solution: "<<sol2<<std::endl;

    return 0;
}