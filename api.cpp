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
     for(auto itr : old_tag->T_filelist) {
        auto ref = find(itr->F_taglist.begin(),itr->F_taglist.end(),old_tag);
        if(ref!=itr->F_taglist.end()+1) {itr->F_taglist.erase(ref);}
        else {return false;}
    }
    TagView.erase(TagView.find(old_tag->name));
    auto ref = find(TagList.begin(),TagList.end(),*old_tag);
    TagList.erase(ref);
    return true;
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
    std::unordered_map<std::string, std::vector<Tag*>>::iterator find_pos = TagView.find(name);
    if(find_pos != TagView.end())
    {
        for(auto& it : TagView[name])
        {
            if(it->explain == explain)
            {
                return it;    
            }
        }
    }
    Tag* it = new Tag;
    it->name = name, it->explain = explain;
    add_to_tag(*it);
    return it;
}

File* fileinvec(string name, string addr){
    for(auto& it : FileView) {
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
    //tag不存在则报错
    if(tagpoint==nullptr)return false;
    //tag存在则删除目标文件vector中的tag指针
    auto ref = find(file->F_taglist.begin(),file->F_taglist.end(),tagpoint);
    file->F_taglist.erase(ref);
    //删除tag中的文件指针
    auto itr = find(tagpoint->T_filelist.begin(),tagpoint->T_filelist.end(),file);
    tagpoint->T_filelist.erase(itr);
    //若该tag的vector中没有其他文件，删除之
    if(tagpoint->T_filelist.empty()){
        delete_from_tag(tagpoint);
    }
    return true;
}

bool tagdel(string name, string explain){
    Tag* object_tag;
    object_tag=taginvec(name, explain);
    delete_from_tag(object_tag);
    return true;
}

bool tagrename(string old_name, string new_name, string explain){
    Tag* object_tag;
    object_tag=taginvec(old_name, explain);
    if(object_tag->T_filelist.empty()){
        throw "Can not find this tag";
        return false;
    }
    else{
    object_tag->name==new_name;
    return true;
    }
    return false;
}

bool tagexplain(string name, string explain){
    Tag* object_tag;
    object_tag=taginvec(name,"0");
    if(object_tag->T_filelist.empty()){
        throw "Can not find this tag";
        return false;
    }
    else{
        object_tag->explain=explain;
        return true;
    }
    return false;
}
