#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <filesystem>
#include <algorithm>

using std::string;
class File;
struct Tag;

typedef string site;

struct Tag {
    std::string name;
    std::string explain;
    std::vector<File*>T_filelist;
};

struct File {
    std::string address;
    std::string name;
    std::vector<Tag*>F_taglist;
};

std::vector<string> dirshow(const site&);
std::vector<Tag*> fileshowtag(const File&, const std::vector<File>&);
bool fileindir(File file);
Tag* taginvec(string name, string explain);
File* fileinvec(string name, string addr);
File* fileinvec(string name);
bool fileaddtag(File& file, Tag& tag);
bool filedeltag(File* file, Tag* tagpoint);
bool tagdel(string name, string explain);
bool tagrename(string name, string explain);
bool tagexplain(string name, string explain);

