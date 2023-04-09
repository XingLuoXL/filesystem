#include "api.h"

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

bool dirshow(const site& Dir) {

}

bool fileshowtag(const File& file, const std::vector<File>& FILELIST){

}

bool fileindir(File file){

}

Tag* taginvec(string name, string explain){
    for(auto& it : TagList) {
        if( it.name == name && it.explain == explain ) { 
            return &it;
        }
    }
    Tag* it = new Tag;
    it->name = name, it->explain = explain;
    add_to_tag(*it);
    return it;
}

File* fileinvec(string name, string addr){
    for(auto& it : FileList) {
        if( it.name == name && it.address == addr ) {
            return &it;
        }
    }
    File* it = new File;
    it->name = name, it->address = addr;
    FileList.push_back(*it);
    return it;
}

File* fileinvec(string name){
    for(auto& it : FileList) {
        if(it.name == name) {
            return &it;
        }
    }
    return nullptr;
}

bool fileaddtag(File& file, Tag& tag){
    file.F_taglist.push_back(&tag);
    tag.T_filelist.push_back(&file);
    return true;
}

bool filedeltag(File* file, Tag* tagpoint){

}

bool tagdel(string name, string explain){

}

bool tagrename(string name, string explain){

}

bool tagexplain(string name, string explain){

}
