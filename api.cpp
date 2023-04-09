#include "api.h"
#include <filesystem>
namespace fs = std::filesystem;

// 用于储存，增删用函数实现以和 View 同步
std::vector<File> FileList;
std::vector<Tag> TagList;

// 专用于查询
std::vector<File>& FileView = FileList;
std::unordered_map<std::string, std::vector<Tag*>> TagView;

void add_to_tag(const Tag& new_tag) {
    TagList.push_back(new_tag);
    // 多线程需加锁，因为这个 TagList 可能已经被修改了
    Tag* last_data = TagList.data() + (TagList.size() - 1);
    auto res = TagView.find(new_tag.name);
    if (res == TagView.end()) {
        // means TagView doesn't have this tag name yet
        TagView[new_tag.name] = std::vector<Tag*>{last_data};
    } else {
        res->second.push_back(last_data);
    }
}

bool delete_from_tag(Tag* old_tag) {
    // 较为繁琐
    return false;
}

std::vector<string> dirshow(const site& Dir){
    std::vector<string> filename_dir;
    fs::path str(Dir);
    if (!fs::exists(str))
        return filename_dir;
    fs::directory_iterator list(str); 
    
    for (auto& it : list){
        filename_dir.push_back(it.path().filename().string());
    }
    return filename_dir;
}

std::vector<Tag*> fileshowtag(const File& file, const std::vector<File>& FILELIST){
    for(auto it:FILELIST){
        if((file.address==it.address)&&(file.name==it.name)){
            return file.F_taglist;
        }
    }
    throw "Can not find this file";
}

bool fileindir(File file){
    fs::path str(file.address + "//" +file.name );
    if(!fs::exists(str)){
        return 0;
    }
    return 1;
}

Tag* taginvec(string name, string explain){

}

File* fileinvec(string name, string addr){

}

File* fileinvec(string name){

}

bool fileaddtag(File file, Tag tag){
    
}

bool filedeltag(File* file, Tag* tagpoint){

}

bool tagdel(string name, string explain){

}

bool tagrename(string name, string explain){

}

bool tagexplain(string name, string explain){

}
