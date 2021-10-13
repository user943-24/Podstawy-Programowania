#include <iostream>
#include <list>
#include <string>

struct options {
    bool n = false;
    bool r = false;
    bool l = false;
    unsigned short len = 0;
} options;

auto main(int argc, char *argv[]) -> int {
    if(argc <= 1) {
        std::cout << "No arguments specified!\n";
        return 1;
    }

    auto tmp = std::string{};
    for(auto i=1; i < 4 && i < argc-2; ++i) {
        tmp = argv[i];
        if(tmp == "-n") {
            options.n = true;
            options.len++;
        } else if(tmp == "-r") {
            options.r = true;
            options.len++;
        } else if(tmp == "-l") {
            options.l = true;
            options.len++;
        } else
            break;
    }

    std::list<std::string> contents;
    std::list<std::string>::iterator it;

    for(auto i = options.len+1; i < argc-1; ++i) {
        tmp = argv[i];
        tmp.append(" ");
        contents.push_back(tmp);
    }
    tmp = argv[argc-1];
    tmp.append("\n");
    contents.push_back(tmp);

    auto i = contents.size();

    if(options.l) {
        i = 0;
        for(it=contents.begin(); i < contents.size()-1; ++it) {
            (*it).replace((*it).length()-1, 1, "\n");
            ++i;
        }
    }
    if(options.r) {
        contents.reverse();
        it=contents.begin();
        if((*it)[(*it).length()-1] == '\n' && !options.l)
            (*it).replace((*it).length()-1, 1, " ");
        it=contents.end();
        it--;
        if((*it)[(*it).length()-1] != '\n')
            (*it).append("\n");
    }
    if(options.n) {
        it=contents.end();
        it--;
        if((*it)[(*it).length()-1] == '\n')
            (*it).erase((*it).length()-1, 1);
    }


    for(it=contents.begin(); it != contents.end(); ++it)
        std::cout << *it;

    return 0;
}

