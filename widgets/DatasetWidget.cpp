//
// Created by mateus on 29/05/2021.
//
#ifdef __unix__
#include <dirent.h>
#elif _WIN32
#include <windows.h>
#endif
#include "DatasetWidget.h"

using namespace settings;

DatasetWidget::DatasetWidget(cppcli::CLWidget *parent) : cppcli::CLWidget(parent, "Dataset widget") {

}

bool DatasetWidget::build() {
    set_header(this->m_parent->get_header());
    set_cmd("dataset");

    register_group("main", "Select an option:\n", cppcli::GroupType::ACTION);

    register_action("main", "Load dataset", "1", load_dataset());
    register_action("main", "Dataset information", "2", show_info());
    register_action("main", "Features names", "3", show_feats());
    register_action("main", "Divide dataset in train/test", "4", divide_traintest());
    register_action("main", "Save train/test datasets", "5", save_traintest());

    add_exit_group();
    return true;
}

bool DatasetWidget::valid_file(const std::string& file) {
    size_t i;
    bool flag = false;
    std::string ext;

    if(file.empty() || file.size() < 4)
        return false;

    for(i = file.size()-1; i >= 0; i--){
        if(file[i] == '.') break;
        std::string f(1, file[i]);
        ext = f + ext;
    }

    for(const std::string& type : mltk::types){
        if(type == ext) flag = true;
    }

    return flag;
}

std::vector<std::string> DatasetWidget::list_datasets(bool list) {
    std::vector<std::string> files;

#ifdef __unix__
    DIR *dpdf;
    struct dirent *epdf;

    std::string temp = settings::data_folder;
    temp.erase(temp.begin() + temp.size()-1);
    std::string path = "./" + settings::data_folder;

    dpdf = opendir(path.c_str());
    if(dpdf != nullptr){
        while((epdf = readdir(dpdf))){
            std::string file = std::string(epdf->d_name);
            if(valid_file(file) && !file.empty()){

                if(list) std::cout << "[" << files.size() << "] " << file << std::endl;
                files.push_back(file);
            }
        }
    }

    closedir(dpdf);
#elif _WIN32
    HANDLE hFind;
    WIN32_FIND_DATA data1;
    std::string path = "..\\DB\\*.*";

    hFind = FindFirstFile(path.c_str(), &data1);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            std::string file_name(data1.cFileName);
            if(valid_file(file_name) && !file_name.empty()){
                if(list) std::cout << "[" << files.size() << "] " << file_name << std::endl;
                files.push_back(file_name);
            }
        } while (FindNextFile(hFind, &data1));
        FindClose(hFind);
    }
#else
    std::cout << "This system is not supported for this function..." << std::endl;
#endif

    return files;
}

cppcli::Action::Type DatasetWidget::load_dataset() {
    cppcli::Action::Type load = [this](){
        if(data.isEmpty()){
            std::string isReg;
            std::string sid, path;
            std::stringstream log;

            auto files = list_datasets(true);
            std::cout << std::endl;
            std::cout << "Enter the number of the DB (must be in the DB folder): ";
            std::cin >> sid;

            if(mltk::utils::stoin(sid) > files.size()){
                push_message("Invalid dataset number.", cppcli::LogType::ERROR);
                return false;
            }

            path = settings::data_folder + files[mltk::utils::stoin(sid)];
            std::clock_t begin = std::clock();
            std::cout << "\n" << path << std::endl;
            if(!data.load(path)){
                push_message("error loading the file " + files[mltk::utils::stoin(sid)], cppcli::LogType::ERROR);
                return false;
            }
            std::clock_t end = std::clock();
            double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
            log << data.name();
            push_message(log.str());
            log.str("");
            log.clear();
            log << elapsed_secs << " seconds to load.";
            push_message(log.str());
        }else{
            char y;
            std::cout << "Wish to load a new dataset?[y|n]" << std::endl;
            std::cout << " > ";
            std::cin >> y;

            if(y == 'y'){
                data.clear();
                if(!test.isEmpty()){
                    test.clear();
                    train.clear();
                }
                push_message("Old dataset erased, select this option again.", cppcli::LogType::LOG);
            }
        }
        return true;
    };
    return load;
}

cppcli::Action::Type DatasetWidget::show_info() {
    cppcli::Action::Type info = [this](){
        int i;
        if(!data.isEmpty()){
            std::cout << "Name: " << data.name() << std::endl;
            std::cout << "Type: " << data.getType() << std::endl;
            std::cout << "Number of features: " << data.dim() << std::endl;
            std::cout << "Number of samples: " << data.size() << std::endl;
            if(data.getType() == "Classification") {
                std::vector<std::string> class_names = data.classesNames();
                std::vector<size_t> class_frequency = data.classesDistribution();
                if(class_names.size() == 2) {
                    auto classes = data.classes();
                    auto neg_id = std::find(classes.begin(), classes.end(), -1) - classes.begin();
                    auto pos_id = std::find(classes.begin(), classes.end(), 1) - classes.begin();
                    std::cout << "Negative points: " << class_frequency[neg_id] << std::endl;
                    std::cout << "Positive points: " << class_frequency[pos_id] << std::endl;
                }else {
                    std::cout << "Class names and frequency [name - freq]: \n[";
                    for (i = 0; i < class_names.size() - 1; i++) {
                        std::cout << class_names[i] << " - "<< class_frequency[i] << ", ";
                    }
                    std::cout << class_names[i] << " - "<< class_frequency[i] << "]\n";
                }
            }
            if(!test.isEmpty()){
                std::cout << "\n\nTest sample information\n\n";
                std::cout << "Number of features: " << test.dim() << std::endl;
                std::cout << "Number of samples: " << test.size() << std::endl;
                if(data.getType() == "Classification") {
                    std::vector<std::string> class_names = data.classesNames();
                    std::vector<size_t> class_frequency = data.classesDistribution();
                    if(class_names.size() == 2) {
                        auto classes = data.classes();
                        auto neg_id = std::find(classes.begin(), classes.end(), -1) - classes.begin();
                        auto pos_id = std::find(classes.begin(), classes.end(), 1) - classes.begin();
                        std::cout << "Negative points: " << class_frequency[neg_id] << std::endl;
                        std::cout << "Positive points: " << class_frequency[pos_id] << std::endl;
                    }else {
                        std::cout << "Class names and frequency [name - freq]: \n[";
                        for (i = 0; i < class_names.size() - 1; i++) {
                            std::cout << class_names[i] << " - "<< class_frequency[i] << ", ";
                        }
                        std::cout << class_names[i] << " - "<< class_frequency[i] << "]\n";
                    }
                }
            }

            if(!train.isEmpty()){
                std::cout << "\n\nTrain sample information\n\n";
                std::cout << "Number of features: " << train.dim() << std::endl;
                std::cout << "Number of samples: " << train.size() << std::endl;
                if(data.getType() == "Classification") {
                    std::vector<std::string> class_names = data.classesNames();
                    std::vector<size_t> class_frequency = data.classesDistribution();
                    if(class_names.size() == 2) {
                        auto classes = data.classes();
                        auto neg_id = std::find(classes.begin(), classes.end(), -1) - classes.begin();
                        auto pos_id = std::find(classes.begin(), classes.end(), 1) - classes.begin();
                        std::cout << "Negative points: " << class_frequency[neg_id] << std::endl;
                        std::cout << "Positive points: " << class_frequency[pos_id] << std::endl;
                    }else {
                        std::cout << "Class names and frequency [name - freq]: \n[";
                        for (i = 0; i < class_names.size() - 1; i++) {
                            std::cout << class_names[i] << " - "<< class_frequency[i] << ", ";
                        }
                        std::cout << class_names[i] << " - "<< class_frequency[i] << "]\n";
                    }
                }
            }
            wait_action();
        }else push_message("Load a dataset first...", cppcli::LogType::LOG);
        return true;
    };
    return info;
}

cppcli::Action::Type DatasetWidget::show_feats() {
    cppcli::Action::Type feats = [this](){
        if(!data.isEmpty()){
            std::vector<int> fnames = data.getFeaturesNames();

            for(int f : fnames){
                std::cout << f << " : ";
            }
            std::cout << std::endl;
            wait_action();
        }else push_message("Load a dataset first...");
        return true;
    };
    return feats;
}

cppcli::Action::Type DatasetWidget::divide_traintest() {
    cppcli::Action::Type divide = [this](){
        if(!data.isEmpty()){
            int fold;

            if(test.isEmpty()){
                std::cout << "Folds: ";
                std::cin >> fold;

                std::clock_t begin = std::clock();
                auto valid_data = mltk::validation::partTrainTest(data, 10, true, settings::seed);
                test = valid_data.test;
                train = valid_data.train;
                std::clock_t end = std::clock();

                std::cout << "\nDone!" << std::endl;
                double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
                std::cout << "Size of the settings::test sample: " << test.size() << std::endl;
                std::cout << std::endl;
                std::cout << elapsed_secs << " seconds to compute.\n";
            }else push_message("Test sample already divided...");
            wait_action();
        }else push_message("Load a dataset first...");
        return true;
    };
    return divide;
}

cppcli::Action::Type DatasetWidget::save_traintest() {
    cppcli::Action::Type save = [this](){
        if(!data.isEmpty()){
            if(test.isEmpty()){
                std::cerr << "Divide the settings::train/settings::test settings::datasets first...\n" << std::endl;
            }else{
                std::string outfile = data.name()+"_"+mltk::utils::timestamp();
                train.write(outfile+"_settings::train", "csv");
                test.write(outfile+"_settings::test", "csv");
            }
            wait_action();
        }else push_message("Load a dataset first...");
        return true;
    };
    return save;
}