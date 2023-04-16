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
    std::string explain = "0";
    std::vector<File*>T_filelist;
    bool operator==(const Tag &T){
        return (this->name == T.name)&&(this->explain == T.explain)&&(this ->T_filelist == T.T_filelist);
    }
};

struct File {
    std::string address;
    std::string name;
    std::vector<Tag*>F_taglist;
};


std::vector<string> dirshow(const site&);  //展示目录文件
std::vector<Tag*> fileshowtag(const File&, const std::vector<File>&);  //展示单文件标签
bool fileindir(File file);  //确认输入文件存在于目录下
Tag* taginvec(string name, string explain);  //确认输入tag存在于vector中
File* fileinvec(string name, string addr);  //确认输入文件存在于vector中，用于给文件加标签
File* fileinvec(string name);  //确认输入文件存在于vector中，用于删标签
bool fileaddtag(File& file, Tag& tag);  //给文件添加标签
bool filedeltag(File* file, Tag* tagpoint);  //给文件删除标签
bool tagdel(string name, string explain);  //删除某标签
bool tagrename(string old_name, string new_name, string explain);  //标签改名
bool tagexplain(string name, string explain);  //给标签添加说明

