#ifdef __unix__
#include <dirent.h>
#elif _WIN32
#include <windows.h>
#endif
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <memory>
#include <iomanip>

#include <ufjfmltk/ufjfmltk.hpp>

#define SEED 42


int verbose = 1;
bool sair = false, inva = false;
double max_time = 110.0f;
std::string data_folder = "../datasets/";
mltk::Data<double> samples;
mltk::Data<double> test_sample;
mltk::Data<double> train_sample;
mltk::Solution sol;
mltk::visualize::Visualization<double> plot(samples);

//Menus utilities
void clear();
std::vector<std::string> list_datasets(bool list);
bool valid_file(std::string file);
void waitUserAction();
void exitProgram();

//Prints that are common in all menus
void header();
int selector();

//Functions to show menus options
void mainMenu();
void datasetMenu();
void dataMenu();
void VisualizationMenu();
void classifiersMenu();
void regressorsMenu();
void clusterersMenu();
void featureSelectionMenu();
void validationMenu();

//Functions to call the execution of the menus options
void mainOption(int);
void datasetOption(int);
void dataOption(int);
void VisualizationOption(int);
void classifiersOption(int);
void featureSelectionOption(int);
void regressorsOption(int);
void clusterersOption(int);
void primalRegressorsOption(int);
void dualRegressorsOption(int);
void primalClassifiersOption(int);
void dualClassifiersOption(int);
void validationOption(int);

//Utils
mltk::KernelType getKernelType(int kernel_type);
template < typename Learner>
mltk::validation::ValidationReport runValidation(const mltk::Data<double>& data, Learner learner, int fold, int qtde=1, int verbose=1, size_t seed=SEED);

int main(int argc, char* argv[]){
    if(argc > 1){
        samples.load(std::string(argv[1]));
    }

    while (true) {
        if(sair) break;
        clear();
        mainMenu();
    }

    return 0;
}

bool valid_file(std::string file){
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

    for(std::string type : mltk::types){
        if(type == ext) flag = true;
    }

    return flag;
}

std::vector<std::string> list_datasets(bool list){
    std::vector<std::string> files;

#ifdef __unix__
    DIR *dpdf;
    struct dirent *epdf;

    std::string temp = data_folder;
    temp.erase(temp.begin() + temp.size()-1);
    std::string path = "./" + data_folder;

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

void clear(){
#ifdef __unix__
    system("clear");
#elif _WIN32
    system("CLS");
#else
    int n;
        for (n = 0; n < 10; n++)
          printf( "\n\n\n\n\n\n\n\n\n\n" );
#endif
}

void exitProgram(){
    exit(0);
}

void waitUserAction(){
    std::cout << "\nPress ENTER to continue..." << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    std::cin.get();
}

void header(){
    std::cout << "         *----------------------------------------------------------* " << std::endl;
    std::cout << "         *                 Machine Learning Toolkit                 * " << std::endl;
    std::cout << "         *----------------------------------------------------------* " << std::endl;
    std::cout << std::endl;
    std::cout << "Select an option:\n" << std::endl;
}

int selector(){
    int o;
    std::string opt;

    if(inva){
        std::cout << std::endl;
        std::cout << "Invalid option." << std::endl;
        inva = false;
        std::cout << std::endl;
    }
    std::cout << " > ";
    std::cin >> opt;
    if(opt != "m") {
        std::istringstream iss(opt);
        iss >> o;
    }else{
        o = 109;
    }
    clear();
    return o;
}

void mainMenu(){
    int option;

    clear();
    header();

    std::cout << "1 - Dataset" << std::endl;
    std::cout << "2 - Data" << std::endl;
    std::cout << "3 - Data Visualization" << std::endl;
    std::cout << "4 - Classifiers" << std::endl;
    std::cout << "5 - Feature Selection" << std::endl;
    std::cout << "6 - Regressors" << std::endl;
    std::cout << "7 - Clusteres" << std::endl;
    std::cout << "8 - Validation" << std::endl;
    std::cout << std::endl;
    std::cout << "9 - Set Verbose" << std::endl;
    std::cout << "10 - Set Max Time" << std::endl;
    std::cout << std::endl;
    std::cout << "--------------------------" <<std::endl;
    std::cout << "0 - Exit" << std::endl;

    option = selector();
    mainOption(option);
}

void datasetMenu(){
    int option;

    clear();
    header();

    std::cout << "1 - Load a dataset" << std::endl;
    std::cout << "2 - Dataset information " << std::endl;
    std::cout << "3 - Features names" << std::endl;
    std::cout << "4 - Divide dataset in Train/Test" << std::endl;
    std::cout << "5 - Save Train/Test dataset" << std::endl;
    std::cout << std::endl;
    std::cout << "0 - Back to the main menu" << std::endl;

    option = selector();
    datasetOption(option);
}

void dataMenu(){
    int option;

    clear();
    header();

    std::cout << "1 - Insert features" << std::endl;
    std::cout << "2 - Remove features" << std::endl;
    std::cout << "3 - Remove point" << std::endl;
    std::cout << "4 - Data variance" << std::endl;
    std::cout << "5 - Data radius" << std::endl;
    std::cout << "6 - Distance from the center of the classes" << std::endl;
    std::cout << "7 - Normalize dataset" << std::endl;
    std::cout << "8 - Print dataset" << std::endl;
    std::cout << std::endl;
    std::cout << "0 - Back to the main menu" << std::endl;

    option = selector();
    dataOption(option);
}

void VisualizationMenu(){
    int option;

    clear();
    header();

    std::cout << "1 - Plot features in 2D" << std::endl;
    std::cout << "2 - Plot features in 3D" << std::endl;
    std::cout << "3 - Plot features in 2D with hyperplane" << std::endl;
    std::cout << "4 - Plot features in 3D with hyperplane" << std::endl;
    std::cout << std::endl;
    std::cout << "0 - Back to the main menu" << std::endl;

    option = selector();
    VisualizationOption(option);
}

void classifiersMenu(){
    int option;

    clear();
    header();

    std::cout << "1 - Primal Classifiers" << std::endl;
    std::cout << "2 - Dual Classifiers" << std::endl;
    std::cout << std::endl;
    std::cout << "0 - Back to the main menu" << std::endl;

    option = selector();
    classifiersOption(option);
}

void featureSelectionMenu(){
    int option;

    clear();
    header();

    std::cout << "1 - Recursive Feature Elimination (RFE)" << std::endl;
    std::cout << "2 - Golub" << std::endl;
    std::cout << "3 - Fisher" << std::endl;
    std::cout << "4 - Admissible Ordered Search (AOS)" << std::endl;
    std::cout << std::endl;
    std::cout << "0 - Back to the main menu" << std::endl;

    option = selector();
    featureSelectionOption(option);
}

void regressorsMenu() {
    int option;

    clear();
    header();

    std::cout << "1 - Primal Regressors" << std::endl;
    std::cout << "2 - Dual Regressors" << std::endl;
    std::cout << std::endl;
    std::cout << "0 - Back to the main menu" << std::endl;

    option = selector();
    regressorsOption(option);
}

void clusterersMenu(){
    int option;

    clear();
    header();

    std::cout << "1 - K-means" << std::endl;
    std::cout << std::endl;
    std::cout << "0 - Back to the main menu" << std::endl;

    option = selector();
    clusterersOption(option);
}

void validationMenu(){
    int opt;

    clear();
    header();

    std::cout << "1 - IMAp" << std::endl;
    std::cout << "2 - IMA Dual" << std::endl;
    std::cout << "3 - SMO" << std::endl;
    std::cout << std::endl;
    std::cout << "0 - Back to main menu." << std::endl;

    opt = selector();
    validationOption(opt);
}


void mainOption(int option){
    switch(option){
        case 1:
            datasetMenu();
            break;
        case 2:
            dataMenu();
            break;
        case 3:
            VisualizationMenu();
            break;
        case 4:
            classifiersMenu();
            break;
        case 5:
            featureSelectionMenu();
            break;
        case 6:
            regressorsMenu();
            break;
        case 7:
            clusterersMenu();
            break;
        case 8:
            validationMenu();
            waitUserAction();
            break;
        case 9:
            std::cout << "Actual Verbose = " << verbose << std::endl;
            std::cout << "Set verbose: ";
            std::cin >> verbose;
            waitUserAction();
            break;
        case 10:
            std::cout << "Actual MAX_TIME = " << max_time << std::endl;
            std::cout << "Enter the max time: ";
            std::cin >> max_time;

            waitUserAction();
            break;
        case 0:
            exitProgram();
            break;
        default:
            inva = true;
            break;
    }
    mainMenu();
}

void datasetOption(int option){
    size_t i = 0;
    bool list = false;
    std::vector<std::string> files;

    switch(option){
        case 1:
            if(samples.isEmpty()){
                std::string isReg;
                std::string sid, path;

                files = list_datasets(true);
                std::cout << std::endl;
                std::cout << "Enter the number of the DB (must be in the DB folder): ";
                std::cin >> sid;

                path = data_folder + files[mltk::utils::stoin(sid)];
                std::clock_t begin = std::clock();
                std::cout << "\n" << path << std::endl;
                samples.load(path);
                std::clock_t end = std::clock();

                double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
                std::cout << std::endl;
                std::cout << elapsed_secs << " seconds to load.\n";
            }else{
                char y;
                std::cout << "Wish to load a new dataset?[y|n]" << std::endl;
                std::cout << " > ";
                std::cin >> y;

                if(y == 'y'){
                    samples.clear();
                    if(!test_sample.isEmpty()){
                        test_sample.clear();
                        train_sample.clear();
                    }
                    std::cout << "\nOld dataset erased, select this option again."<< std::endl;
                }
            }

            waitUserAction();
            break;
        case 2:
            if(!samples.isEmpty()){
                std::cout << "Dataset type: " << samples.getType() << std::endl;
                std::cout << "Number of features: " << samples.dim() << std::endl;
                std::cout << "Number of samples: " << samples.size() << std::endl;
                if(samples.getType() == "Classification") {
                    std::vector<std::string> class_names = samples.classesNames();
                    std::vector<size_t> class_frequency = samples.classesDistribution();
                    if(class_names.size() == 2) {
                        auto classes = samples.classes();
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
                if(!test_sample.isEmpty()){
                    std::cout << "\n\nTest sample information\n\n";
                    std::cout << "Number of features: " << test_sample.dim() << std::endl;
                    std::cout << "Number of samples: " << test_sample.size() << std::endl;
                    if(samples.getType() == "Classification") {
                        std::vector<std::string> class_names = samples.classesNames();
                        std::vector<size_t> class_frequency = samples.classesDistribution();
                        if(class_names.size() == 2) {
                            auto classes = samples.classes();
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

                if(!train_sample.isEmpty()){
                    std::cout << "\n\nTrain sample information\n\n";
                    std::cout << "Number of features: " << train_sample.dim() << std::endl;
                    std::cout << "Number of samples: " << train_sample.size() << std::endl;
                    if(samples.getType() == "Classification") {
                        std::vector<std::string> class_names = samples.classesNames();
                        std::vector<size_t> class_frequency = samples.classesDistribution();
                        if(class_names.size() == 2) {
                            auto classes = samples.classes();
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
            }else std::cout << "Load a dataset first...\n\n";

            waitUserAction();
            break;

        case 3:
            if(!samples.isEmpty()){
                std::vector<int> fnames = samples.getFeaturesNames();

                for(int f : fnames){
                    std::cout << f << " : ";
                }
                std::cout << std::endl;
            }else std::cout << "Load a dataset first...\n\n";

            waitUserAction();
            break;
        case 4:
            if(!samples.isEmpty()){
                int fold;
                unsigned int seed;

                if(test_sample.isEmpty()){
                    std::cout << "K-Fold: ";
                    std::cin >> fold;
                    std::cout << "Seed for timestamps: ";
                    std::cin >> seed;

                    std::clock_t begin = std::clock();
                    auto valid_data = mltk::validation::partTrainTest(samples, 10, true, SEED);
                    test_sample = valid_data.test;
                    train_sample = valid_data.train;
                    std::clock_t end = std::clock();

                    std::cout << "\nDone!" << std::endl;
                    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
                    std::cout << "Size of the test sample: " << test_sample.size() << std::endl;
                    std::cout << std::endl;
                    std::cout << elapsed_secs << " seconds to compute.\n";

                }else std::cout << "Test sample already divided...\n";
            }else std::cout << "Load a dataset first...\n\n";

            waitUserAction();
            break;
        case 5:
            /*if(_data != NULL && !_data->empty()){
                if(!test_sample){
                    std::cerr << "Divide the train/test datasets first...\n" << std::endl;
                }else{
                    std::string outfile = _data->get_dataset_name();
                    Sample *sample = Sample::copy(_data->get_samples());

                    outfile = outfile + "_train";
                    _data->write(outfile, sample, 0);
                    outfile = _data->get_dataset_name();
                    outfile = outfile + "_test";
                    _data->write(outfile, test_sample, 0);

                    delete sample;
                }
            }else std::cout << "Load a dataset first...\n\n";
            */
            waitUserAction();
            break;
        case 0:
            mainMenu();
            break;
        default:
            inva = true;
            break;
    }
    datasetMenu();
}

void dataOption(int option){
    int i = 0, j = 0;

    switch(option){
        case 1:
            if(!samples.isEmpty()){
                int totalFeat, flag_feat, f, fnamesize;
                std::vector<int> feats;
                std::vector<int> fnames = samples.getFeaturesNames();

                fnamesize = fnames.size();
                std::cout << "Insert how many features: ";
                std::cin >> totalFeat;
                feats.resize(totalFeat);

                for(i = 0; i < totalFeat; i++){
                    std::cout << "Feature " << i + 1 << ": ";
                    std::cin >> f;
                    feats[i] = f;

                    for(flag_feat = 0, j = 0; j < fnamesize; j++){
                        if(feats[i] == fnames[j]){
                            flag_feat = 1;
                        }
                    }

                    if(!flag_feat){
                        std::cout << "Feature " << feats[i] << " does not belongs to the set.\n";
                        i--;
                        std::cin.clear();
                    }
                }
                mltk::Data<double> temp = samples.insertFeatures(feats);

                if(!temp.isEmpty()){
                    samples.clear();
                    samples = temp.copy();
                }else{
                    std::cerr << "Something went wrong." << std::endl;
                }
            }else std::cout << "Load a dataset first...\n\n";

            waitUserAction();
            break;
        case 2:
            if(!samples.isEmpty()){
                int totalFeat, flag_feat, f, fnamesize;
                std::vector<int> feats;
                std::vector<int> fnames = samples.getFeaturesNames();

                fnamesize = fnames.size();

                std::cout << std::endl;
                while(true){
                    std::cout << "Remove how many features (-1 to cancel): ";
                    std::cin >> totalFeat;
                    if(totalFeat > fnamesize - 1){
                        clear();
                        std::cout << "Can't remove more features than exist." << std::endl;
                    }else if(totalFeat >= 0){
                        break;
                    }
                }

                for(i = 0; i < totalFeat; i++){
                    std::cout << "Feature " << i + 1 << ": ";
                    std::cin >> f;
                    feats.push_back(f);
                    for(flag_feat = 0, j = 0; j < fnamesize; j++){
                        if(feats[i] == fnames[j]){
                            flag_feat = 1;
                        }
                    }

                    if(!flag_feat){
                        std::cout << "Feature " << feats[i] << " does not belongs to the set.\n";
                        i--;
                    }
                }
                std::cout << std::endl;
                samples.removeFeatures(feats);

                fnames = samples.getFeaturesNames();

            }else std::cout << "Load a dataset first...\n\n";

            waitUserAction();
            break;
        case 3:
            if(!samples.isEmpty()){
                std::cout << "Point to remove index (-1 to cancel): ";
                std::cin >> i;

                if(i < 0){
                    break;
                }

                samples.removePoint(i);
            }else std::cout << "Load a dataset first...\n\n";

            waitUserAction();
            break;
        case 4:
            if(!samples.isEmpty()){
                int index;

                std::cout << "Feature to be ignored (-1 doesnt ignore any feature): ";
                std::cin >> index;
                std::clock_t begin = std::clock();
                std::cout << std::endl;
                std::cout << "The variance values is: " << mltk::stats::var(samples, index) << std::endl;
                std::clock_t end = std::clock();

                double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
                std::cout << std::endl;
                std::cout << elapsed_secs << " seconds to compute.\n";
            }else std::cout << "Load a dataset first...\n\n";

            waitUserAction();
            break;
        case 5:
            if(!samples.isEmpty()){
                int index, q;

                std::cout << "Feature to be ignored: ";
                std::cin >> index;
                std::cout << "Value of q [q = 1 | q = 2]: ";
                std::cin >> q;
                std::cout << std::endl;

                std::clock_t begin = std::clock();
                std::cout << "The value of the radius is: " << mltk::stats::radius(samples, index, q) << std::endl;
                std::clock_t end = std::clock();

                double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
                std::cout << std::endl;
                std::cout << elapsed_secs << " seconds to compute.\n";
            }else std::cout << "Load a dataset first...\n\n";

            waitUserAction();
            break;
        case 6:
            if(!samples.isEmpty()){
                int index;

                std::cout << "Feature to be ignored: ";
                std::cin >> index;
                std::cout << std::endl;

                std::clock_t begin = std::clock();
                std::cout << "The value of the center of the classes are: " << mltk::stats::distCenters(samples, index) << std::endl;
                std::cout << std::endl;
                std::clock_t end = std::clock();

                double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

                std::cout << elapsed_secs << " seconds to compute.\n";
            }else std::cout << "Load a dataset first...\n\n";

            waitUserAction();
            break;
        case 7:
            if(!samples.isEmpty()){
                int q, p;

                std::cout << "Value of q: ";
                std::cin >> q;
                std::cout << std::endl;

                if(q == -1.0){
                    p = 1.0;
                }else if(q == 1.0){
                    p = 100.0;
                }else{
                    p = q/(q-1.0);
                }

                std::clock_t begin = std::clock();
                samples.normalize(p);
                std::cout << "The dataset was normalized." << std::endl;
                std::clock_t end = std::clock();

                double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
                std::cout << std::endl;
                std::cout << elapsed_secs << " seconds to compute.\n";
            }else std::cout << "Load a dataset first...\n\n";

            waitUserAction();
            break;
        case 8:
            if(!samples.isEmpty()){
                std::cout << samples << std::endl;
            }else std::cout << "Load a dataset first...\n\n";

            waitUserAction();
            break;
        case 0:
            mainMenu();
            break;
        default:
            inva = true;
            break;
    }
    dataMenu();
}

void VisualizationOption(int opt){
    int x, y, z;

    plot.setSample(samples);
    switch (opt) {
        case 1:
            std::cout << "Enter the feature to plot in the x-axis: ";
            std::cin >> x;
            std::cout << "Enter the feature to plot in the y-axis: ";
            std::cin >> y;

            plot.plot2D(x, y);
            break;
        case 2:
            std::cout << "Enter the feature to plot in the x-axis: ";
            std::cin >> x;
            std::cout << "Enter the feature to plot in the y-axis: ";
            std::cin >> y;
            std::cout << "Enter the feature to plot in the z-axis: ";
            std::cin >> z;
            plot.plot3D(x, y, z);
            break;
        case 3:
            if(sol.w.empty()){
                std::cout << "Run a classifier in the data first." << std::endl;
                waitUserAction();
                break;
            }
            std::cout << "Enter the feature to plot in the x-axis: ";
            std::cin >> x;
            std::cout << "Enter the feature to plot in the y-axis: ";
            std::cin >> y;

            plot.plot2DwithHyperplane(x, y, sol);
            break;
        case 4:
            if(sol.w.empty()){
                std::cout << "Run a classifier in the data first." << std::endl;
                waitUserAction();
                break;
            }
            std::cout << "Enter the feature to plot in the x-axis: ";
            std::cin >> x;
            std::cout << "Enter the feature to plot in the y-axis: ";
            std::cin >> y;
            std::cout << "Enter the feature to plot in the z-axis: ";
            std::cin >> z;

            plot.plot3DwithHyperplane(x, y, z, sol);
            break;
        case 0:
            mainMenu();
            break;
        default:
            inva = true;
            break;
    }
    VisualizationMenu();
}

void classifiersOption(int option){
    int opt;

    switch (option) {
        case 1:
            clear();
            header();

            std::cout << "1 - Perceptron Primal" << std::endl;
            std::cout << "2 - Perceptron Primal with fixed margin" << std::endl;
            std::cout << "3 - Incremental Margin Algorithm Primal (IMAp)" << std::endl;
            std::cout << "4 - K-Nearest Neighbors (KNN)" << std::endl;
            std::cout << std::endl;
            std::cout << "0 - Back to classifiers menu" << std::endl;
            std::cout << "m - Back to main menu." << std::endl;

            opt = selector();
            primalClassifiersOption(opt);
            break;
        case 2:
            clear();
            header();

            std::cout << "1 - Perceptron Dual" << std::endl;
            std::cout << "2 - Perceptron Dual with fixed margin" << std::endl;
            std::cout << "3 - Incremental Margin Algorithm Dual (IMA Dual)" << std::endl;
            std::cout << "4 - Sequential Minimal Optimization (SMO)" << std::endl;
            std::cout << std::endl;
            std::cout << "0 - Back to classifiers menu" << std::endl;
            std::cout << "m - Back to main menu." << std::endl;

            opt = selector();
            dualClassifiersOption(opt);
            break;
        case 0:
            mainMenu();
            break;
        default:
            inva = true;
            break;
    }
    classifiersMenu();
}

void featureSelectionOption(int option){
    double p, q, alpha_aprox, kernel_param = 0;
    int opt, flex, kernel_type, ddim, jump, branching, branch_form, choice_form, prof_look_ahead, cut;
    mltk::Timer time;
    mltk::classifier::IMAp<double> imap(samples);
    mltk::classifier::IMADual<double> imadual(samples);
    mltk::classifier::SMO<double> smo;
    mltk::validation::CrossValidation cv;
    mltk::featselect::RFE<double> rfe;
    mltk::featselect::Golub<double> golub;
    mltk::featselect::Fisher<double> fisher;
    mltk::featselect::AOS<double> aos;
    mltk::Data<double> res;
    mltk::KernelType type;

    clear();
    header();

    switch (option){
        case 1:
            if(!samples.isEmpty()) {
                std::cout << "Recursive Feature Elimination (RFE)" << std::endl;
                std::cout << "1 - IMAp" << std::endl;
                std::cout << "2 - IMA Dual" << std::endl;
                std::cout << "3 - SMO" << std::endl;
                std::cout << std::endl;
                std::cout << "0 - Back to Feature Selection menu" << std::endl;
                std::cout << "m - Back to Main menu" << std::endl;
                opt = selector();
                switch (opt) {
                    case 1:
                        std::cout << "q-norm value: ";
                        std::cin >> q;
                        std::cout << "Flexibilization value (0 - no flexibilization): ";
                        std::cin >> flex;
                        std::cout << "Alpha aproximation: ";
                        std::cin >> alpha_aprox;

                        if(q == -1.0){
                            p = 1.0;
                        }else if(q == 1.0){
                            p = 100.0;
                        }else{
                            p = q/(q-1.0);
                        }

                        imap.setqNorm(q);
                        imap.setFlexible(flex);
                        imap.setAlphaAprox(alpha_aprox);
                        imap.setMaxTime(max_time);
                        rfe.setClassifier(&imap);
                        break;
                    case 2:
                        std::cout << "Kernel (0)Inner Product (1)Polynomial (2)Gaussian: ";
                        std::cin >> kernel_type;

                        if (kernel_type == 1) {
                            std::cout << "Polynomial degree: ";
                        } else if (kernel_type == 2) {
                            std::cout << "Gaussian gamma: ";
                        }

                        if (kernel_type != 0) {
                            std::cin >> kernel_param;
                        }
                        type = getKernelType(kernel_type);
                        imadual.setKernelParam(kernel_param);
                        imadual.setKernelType(type);
                        imadual.setMaxTime(max_time);
                        rfe.setClassifier(&imadual);
                        break;
                    case 3:
                        std::cout << "Kernel (0)Inner Product (1)Polynomial (2)Gaussian: ";
                        std::cin >> kernel_type;

                        if (kernel_type == 1) {
                            std::cout << "Polynomial degree: ";
                        } else if (kernel_type == 2) {
                            std::cout << "Gaussian gamma: ";
                        }

                        if (kernel_type != 0) {
                            std::cin >> kernel_param;
                        }
                        type = getKernelType(kernel_type);
                        smo.setKernelParam(kernel_param);
                        smo.setKernelType(type);
                        rfe.setClassifier(&smo);
                        break;
                    case 0:
                        featureSelectionMenu();
                        break;
                    case 109:
                        mainMenu();
                        break;
                    default:
                        featureSelectionOption(1);
                        break;
                }
                clear();
                std::cout << std::endl;
                std::cout << "Desired dimension (max. " << samples.dim() << "): ";
                std::cin >> ddim;
                std::cout << "Features eliminated at a time: ";
                std::cin >> jump;
                std::cout << std::endl;

                rfe.setJump(jump);
                rfe.setDepth(samples.dim() - ddim);

                clear();
                std::cout << "\n--------- Cross-Validation ---------\n" << std::endl;
                std::cout << "Number of Cross-Validation: ";
                std::cin >> cv.qtde;

                if (cv.qtde > 0) {
                    std::cout << "K-Fold: ";
                    std::cin >> cv.fold;
                    std::cout << "From how many in how many dimensions: ";
                    std::cin >> cv.jump;
                    std::cout << "Error margin: ";
                    std::cin >> cv.limit_error;
                }
                rfe.setCrossValidation(&cv);
                rfe.setVerbose(verbose);
                rfe.setSamples(mltk::make_data<double>(samples));
                clear();
                time.reset();
                res = rfe.selectFeatures();
                samples.clear();
                samples = res;

                std::cout << time.elapsed()/1000 << " seconds to compute.\n";
            }else{
                std::cout << "Load a dataset first..." << std::endl;
            }
            waitUserAction();
            featureSelectionOption(1);
            break;
        case 2:
            if(!samples.isEmpty()) {
                std::cout << "Golub" << std::endl;
                std::cout << "1 - IMAp" << std::endl;
                std::cout << "2 - IMA Dual" << std::endl;
                std::cout << "3 - SMO" << std::endl;
                std::cout << std::endl;
                std::cout << "0 - Back to Feature Selection menu" << std::endl;
                std::cout << "m - Back to Main menu" << std::endl;
                opt = selector();
                switch (opt) {
                    case 1:
                        std::cout << "q-norm value: ";
                        std::cin >> q;
                        std::cout << "Flexibilization value (0 - no flexibilization): ";
                        std::cin >> flex;
                        std::cout << "Alpha aproximation: ";
                        std::cin >> alpha_aprox;

                        if(q == -1.0){
                            p = 1.0;
                        }else if(q == 1.0){
                            p = 100.0;
                        }else{
                            p = q/(q-1.0);
                        }

                        imap.setqNorm(q);
                        imap.setFlexible(flex);
                        imap.setAlphaAprox(alpha_aprox);
                        imap.setMaxTime(max_time);
                        golub.setClassifier(&imap);
                        break;
                    case 2:
                        std::cout << "Kernel (0)Inner Product (1)Polynomial (2)Gaussian: ";
                        std::cin >> kernel_type;

                        if (kernel_type == 1) {
                            std::cout << "Polynomial degree: ";
                        } else if (kernel_type == 2) {
                            std::cout << "Gaussian gamma: ";
                        }

                        if (kernel_type != 0) {
                            std::cin >> kernel_param;
                        }
                        type = getKernelType(kernel_type);
                        imadual.setKernelParam(kernel_param);
                        imadual.setKernelType(type);
                        imadual.setMaxTime(max_time);
                        golub.setClassifier(&imadual);
                        break;
                    case 3:
                        std::cout << "Kernel (0)Inner Product (1)Polynomial (2)Gaussian: ";
                        std::cin >> kernel_type;

                        if (kernel_type == 1) {
                            std::cout << "Polynomial degree: ";
                        } else if (kernel_type == 2) {
                            std::cout << "Gaussian gamma: ";
                        }

                        if (kernel_type != 0) {
                            std::cin >> kernel_param;
                        }
                        type = getKernelType(kernel_type);
                        smo.setKernelParam(kernel_param);
                        smo.setKernelType(type);
                        golub.setClassifier(&smo);
                        break;
                    case 0:
                        featureSelectionMenu();
                        break;
                    case 109:
                        mainMenu();
                        break;
                    default:
                        featureSelectionOption(2);
                        break;
                }
                clear();
                std::cout << std::endl;
                std::cout << "Desired dimension (max. " << samples.dim() << "): ";
                std::cin >> ddim;
                golub.setVerbose(verbose);
                golub.setFinalDimension(ddim);
                golub.setSamples(mltk::make_data<double>(samples));
                clear();
                time.reset();
                res = golub.selectFeatures();
                samples.clear();
                samples = res;

                std::cout << time.elapsed()/1000 << " seconds to compute.\n";
            }else{
                std::cout << "Load a dataset first..." << std::endl;
            }
            waitUserAction();
            featureSelectionMenu();
            break;
        case 3:
            if(!samples.isEmpty()) {
                std::cout << "Fisher" << std::endl;
                std::cout << "1 - IMAp" << std::endl;
                std::cout << "2 - IMA Dual" << std::endl;
                std::cout << "3 - SMO" << std::endl;
                std::cout << std::endl;
                std::cout << "0 - Back to Feature Selection menu" << std::endl;
                std::cout << "m - Back to Main menu" << std::endl;
                opt = selector();
                switch (opt) {
                    case 1:
                        std::cout << "q-norm value: ";
                        std::cin >> q;
                        std::cout << "Flexibilization value (0 - no flexibilization): ";
                        std::cin >> flex;
                        std::cout << "Alpha aproximation: ";
                        std::cin >> alpha_aprox;

                        if(q == -1.0){
                            p = 1.0;
                        }else if(q == 1.0){
                            p = 100.0;
                        }else{
                            p = q/(q-1.0);
                        }

                        imap.setqNorm(q);
                        imap.setFlexible(flex);
                        imap.setAlphaAprox(alpha_aprox);
                        imap.setMaxTime(max_time);
                        fisher.setClassifier(&imap);
                        break;
                    case 2:
                        std::cout << "Kernel (0)Inner Product (1)Polynomial (2)Gaussian: ";
                        std::cin >> kernel_type;

                        if (kernel_type == 1) {
                            std::cout << "Polynomial degree: ";
                        } else if (kernel_type == 2) {
                            std::cout << "Gaussian gamma: ";
                        }

                        if (kernel_type != 0) {
                            std::cin >> kernel_param;
                        }
                        type = getKernelType(kernel_type);
                        imadual.setKernelParam(kernel_param);
                        imadual.setKernelType(type);
                        imadual.setMaxTime(max_time);
                        fisher.setClassifier(&imadual);
                        break;
                    case 3:
                        std::cout << "Kernel (0)Inner Product (1)Polynomial (2)Gaussian: ";
                        std::cin >> kernel_type;

                        if (kernel_type == 1) {
                            std::cout << "Polynomial degree: ";
                        } else if (kernel_type == 2) {
                            std::cout << "Gaussian gamma: ";
                        }

                        if (kernel_type != 0) {
                            std::cin >> kernel_param;
                        }
                        type = getKernelType(kernel_type);
                        smo.setKernelParam(kernel_param);
                        smo.setKernelType(type);
                        fisher.setClassifier(&smo);
                        break;
                    case 0:
                        featureSelectionMenu();
                        break;
                    case 109:
                        mainMenu();
                        break;
                    default:
                        featureSelectionOption(3);
                        break;
                }
                clear();
                std::cout << std::endl;
                std::cout << "Desired dimension (max. " << samples.dim() << "): ";
                std::cin >> ddim;
                fisher.setVerbose(verbose);
                fisher.setFinalDimension(ddim);
                fisher.setSamples(mltk::make_data<double>(samples));
                clear();
                time.reset();
                res = fisher.selectFeatures();
                samples.clear();
                samples = res;

                std::cout << time.elapsed()/1000 << " seconds to compute.\n";
            }else{
                std::cout << "Load a dataset first..." << std::endl;
            }
            waitUserAction();
            featureSelectionMenu();
            break;
        case 4:

            if(!samples.isEmpty()) {
                std::cout << "Admissible Ordered Search (AOS)" << std::endl;
                std::cout << "1 - IMAp" << std::endl;
                std::cout << "2 - IMA Dual" << std::endl;
                std::cout << "3 - SMO" << std::endl;
                std::cout << std::endl;
                std::cout << "0 - Back to Feature Selection menu" << std::endl;
                std::cout << "m - Back to Main menu" << std::endl;
                opt = selector();
                switch (opt) {
                    case 1:
                        std::cout << "q-norm value: ";
                        std::cin >> q;
                        std::cout << "Flexibilization value (0 - no flexibilization): ";
                        std::cin >> flex;
                        std::cout << "Alpha aproximation: ";
                        std::cin >> alpha_aprox;

                        if(q == -1.0){
                            p = 1.0;
                        }else if(q == 1.0){
                            p = 100.0;
                        }else{
                            p = q/(q-1.0);
                        }

                        imap.setqNorm(q);
                        imap.setFlexible(flex);
                        imap.setAlphaAprox(alpha_aprox);
                        imap.setMaxTime(max_time);
                        aos.setClassifier(&imap);
                        break;
                    case 2:
                        std::cout << "Kernel (0)Inner Product (1)Polynomial (2)Gaussian: ";
                        std::cin >> kernel_type;

                        if (kernel_type == 1) {
                            std::cout << "Polynomial degree: ";
                        } else if (kernel_type == 2) {
                            std::cout << "Gaussian gamma: ";
                        }

                        if (kernel_type != 0) {
                            std::cin >> kernel_param;
                        }
                        type = getKernelType(kernel_type);
                        imadual.setKernelParam(kernel_param);
                        imadual.setKernelType(type);
                        imadual.setMaxTime(max_time);
                        aos.setClassifier(&imadual);
                        break;
                    case 3:
                        std::cout << "Kernel (0)Inner Product (1)Polynomial (2)Gaussian: ";
                        std::cin >> kernel_type;

                        if (kernel_type == 1) {
                            std::cout << "Polynomial degree: ";
                        } else if (kernel_type == 2) {
                            std::cout << "Gaussian gamma: ";
                        }

                        if (kernel_type != 0) {
                            std::cin >> kernel_param;
                        }
                        type = getKernelType(kernel_type);
                        smo.setKernelParam(kernel_param);
                        smo.setKernelType(type);
                        aos.setClassifier(&smo);
                        break;
                    case 0:
                        featureSelectionMenu();
                        break;
                    case 109:
                        mainMenu();
                        break;
                    default:
                        featureSelectionOption(4);
                        break;
                }

                std::cout << std::endl;
                std::cout << "Desired dimension (max. " << samples.dim() << "): ";
                std::cin >> ddim;
                std::cout << "Branching factor (max. " << samples.dim() << "): ";
                std::cin >> branching;
                std::cout << std::endl;
                std::cout << "Branching sorting: (1)W (2)W/center (3)W*radius/center (4)W*radius (5)W*Golub (6)W*Fisher: ";
                std::cin >> branch_form;
                std::cout << "Choice: (1)Margin (2)Margin*Dist.Centers: ";
                std::cin >> choice_form;
                std::cout << "Look-Ahead depth: ";
                std::cin >> prof_look_ahead;
                std::cout << "Cut depth: ";
                std::cin >> cut;

                aos.setVerbose(verbose);
                aos.setFinalDimension(ddim);
                aos.setSamples(mltk::make_data<double>(samples));
                aos.setCrossValidation(&cv);
                aos.setBreadth(branching);
                aos.setChoiceShape(choice_form);
                aos.setSortingShape(branch_form);
                aos.setLookAheadDepth(prof_look_ahead);
                aos.setCut(cut);

                clear();
                time.reset();
                res = aos.selectFeatures();

                samples.clear();
                samples = res;

                std::cout << time.elapsed()/1000 << " seconds to compute.\n";

            }else{
                std::cout << "Load a dataset first..." << std::endl;
            }

            waitUserAction();
            featureSelectionMenu();
            break;
        case 0:
            mainMenu();
            break;
        default:
            featureSelectionMenu();
            break;
    }
}

void regressorsOption(int option) {
    int opt;
    switch (option){
        case 1:
            clear();
            header();

            std::cout << "1 - Least Mean Squares Primal (LMS Primal)" << std::endl;
            std::cout << "2 - K-nearest neighbors (KNN)" << std::endl;
            std::cout << std::endl;
            std::cout << "0 - Back to regressors menu" << std::endl;
            std::cout << "m - Back to main menu." << std::endl;

            opt = selector();
            primalRegressorsOption(opt);
            break;
        case 2:
            clear();
            header();

            std::cout << "1 - Least Mean Squares Dual (LMS Dual)" << std::endl;
            std::cout << std::endl;
            std::cout << "0 - Back to regressors menu" << std::endl;
            std::cout << "m - Back to main menu." << std::endl;

            opt = selector();
            dualRegressorsOption(opt);
            break;
        case 0:
            mainMenu();
            break;
        default:
            inva = true;
            break;
    }
    regressorsMenu();
}

void clusterersOption(int option){
    switch (option){
        case 1:
            if(!samples.isEmpty()) {
                size_t k;
                size_t initialization;
                std::cout << "k value: ";
                std::cin >> k;
                std::cout << std::endl;
                std::cout << "Initialization [0 - random; 1 - kmeanspp]: ";
                std::cin >> initialization;
                mltk::clusterer::KMeans<double> kmeans(samples, k, (initialization == 0) ? "random" : "kmeanspp");
                kmeans.setMaxTime(max_time);
                kmeans.train();
                auto conf_m = mltk::validation::generateConfusionMatrix(samples, kmeans);

                mltk::Data<double> _data;
                _data.copy(samples);
                for(size_t i = 0; i < _data.size(); i++){
                    auto point = _data[i];
                    point->Y() = kmeans.evaluate(*point);
                }
                mltk::visualize::Visualization<double> vis(_data);
                std::vector<int> classes(_data.classes().size());
                iota(classes.begin(), classes.end(), 1);
                _data.setClasses(classes);
                std::cout << std::endl;
                mltk::utils::printConfusionMatrix(classes, samples.classesNames(), conf_m);
                if(_data.dim() >= 3 )
                    vis.plot3D(1,2,3);
                if(_data.dim() == 2)
                    vis.plot2D(1, 2);
                waitUserAction();
            }else{
                std::cout << "Load a dataset first..." << std::endl;
            }
            break;
        case 0:
            clusterersMenu();
            break;
        case 109:
            mainMenu();
            break;
        default:
            inva = true;
            break;
    }
}

void primalRegressorsOption(int option) {
    double eta = 0.5;

    switch (option) {
        case 1:
            if(!samples.isEmpty()){
                std::cout << "Value of the learning rate: ";
                std::cin >> eta;

                mltk::regressor::LMSPrimal<double> lms(samples, eta, 2);

                lms.setMaxIterations(20);
                lms.setMaxTime(max_time);
                lms.train();
                sol = lms.getSolution();

                waitUserAction();
            }else{
                std::cout << "Load a dataset first..." << std::endl;
            }
            break;
        case 2:
            if(!samples.isEmpty()) {
                size_t k;
                std::cout << "k value: ";
                std::cin >> k;
                std::cout << "Enter a point to evaluate:" << std::endl;
                std::vector<double> feats(samples.dim());
                for(size_t i = 0; i < samples.dim(); i++){
                    std::cout << "Dim " << i << ": ";
                    std::cin >> feats[i];
                }
                std::cout << std::endl;

                mltk::regressor::KNNRegressor<double> knn(samples, k);
                double value = knn.evaluate(mltk::Point<double>(feats));

                std::cout << "Evaluated value: " << value << std::endl;

            }else{
                std::cout << "Load a dataset first..." << std::endl;
            }
            break;
        case 0:
            regressorsMenu();
            break;
        case 109:
            mainMenu();
            break;
        default:
            inva = true;
            break;
    }
    regressorsOption(1);
}

void dualRegressorsOption(int option) {
    switch (option) {
        case 1:
            if(!samples.isEmpty()){
                waitUserAction();
            }else{
                std::cout << "Load a dataset first..." << std::endl;
            }
            break;
        case 0:
            regressorsMenu();
            break;
        case 109:
            mainMenu();
            break;
        default:
            inva = true;
            break;
    }
    regressorsOption(2);
}

void validationOption(int option){
    int fold, qtde, kernel_type;
    int p, q, i, norm, flexible, svs;
    double rate, gamma, alpha_prox, kernel_param = 0;
    mltk::validation::ValidationReport val_sol;

    switch(option){
        case 1:
            if(!samples.isEmpty()){
                mltk::classifier::IMAp<double> imap(samples);

                std::cout << "Quantity of K-fold: ";
                std::cin >> qtde;
                std::cout << "Number of folds: ";
                std::cin >> fold;

                std::cout << "[1]p or [2]q norm: ";
                std::cin >> norm;
                std::cout << std::endl;

                if(norm == 1){
                    std::cout << "p-norm value: ";
                    std::cin >> p;
                    if(p == 1.0){
                        q = -1.0;
                    }else{
                        q = (int)(p/(p-1.0));
                    }
                }else{
                    std::cout << "q-norm value: ";
                    std::cin >> q;
                    if(q == -1.0){
                        p = 1.0;
                    }else if(q == 1.0){
                        p = 100.0;
                    }else{
                        p = (int)(q/(q-1.0));
                    }
                }
                std::cout << std::endl;
                std::cout << "Flexibilization value [0 - no flexibilization]: ";
                std::cin >> flexible;
                std::cout << std::endl;
                std::cout << "Alpha aproximation value [1 - alpha]: ";
                std::cin >> alpha_prox;
                std::cout << std::endl;
                std::cout << max_time << std::endl;

                imap.setMaxTime(max_time);
                imap.setpNorm(p);
                imap.setqNorm(q);
                imap.setVerbose(verbose);
                imap.setFlexible(flexible);
                imap.setAlphaAprox(alpha_prox);

                std::clock_t begin = std::clock();
//                val_sol = validate.validation(fold, qtde);
                std::clock_t end = std::clock();
//
//                std::cout << "\n\n   " << fold << "-Fold Cross Validation stats:" << std::endl;
//                std::cout << "\nAccuracy: "<< val_sol.accuracy << std::endl;
//                std::cout << "Precision: "<< val_sol.precision << std::endl;
//                std::cout << "Recall: "<< val_sol.recall << std::endl;
//                std::cout << std::endl;

                double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
                std::cout << std::endl;
                std::cout << elapsed_secs << " seconds to compute.\n";
            }else{
                std::cout << "Load a dataset first..." << std::endl;
            }
            waitUserAction();
            break;
        case 2:
            if(!samples.isEmpty()){
                std::cout << "Quantity of K-fold: ";
                std::cin >> qtde;
                std::cout << "Number of folds: ";
                std::cin >> fold;

                std::cout << "Learning rate: ";
                std::cin >> rate;
                std::cout << "Kernel [0]Inner Product [1]Polynomial [2]Gaussian: ";
                std::cin >> kernel_type;

                if(kernel_type != 0){
                    if(kernel_type == 1){
                        std::cout << "Polynomial degree: ";
                    }else{
                        std::cout << "Gaussian gamma: ";
                    }
                    std::cin >> kernel_param;
                }

                std::clock_t begin = std::clock();
                mltk::KernelType type = getKernelType(kernel_type);
                mltk::classifier::IMADual<double> ima_dual(samples, type, kernel_param);
                ima_dual.setMaxTime(max_time);

//                Validation<double> validate(*samples, &ima_dual, 10);
//
//                validate.setVerbose(verbose);
//                validate.partTrainTest(fold);
//                val_sol = validate.validation(fold, qtde);
                std::clock_t end = std::clock();

//                std::cout << "\nAccuracy: "<< val_sol.accuracy << std::endl;
//                std::cout << "Precision: "<< val_sol.precision << std::endl;
//                std::cout << "Recall: "<< val_sol.recall << std::endl;
                std::cout << std::endl;

                double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
                std::cout << std::endl;
                std::cout << elapsed_secs << " seconds to compute.\n";
            }else{
                std::cout << "Load a dataset first..." << std::endl;
            }
            waitUserAction();
            break;
        case 3:
            if(!samples.isEmpty()){
                std::cout << "Quantity of K-fold: ";
                std::cin >> qtde;
                std::cout << "Number of folds: ";
                std::cin >> fold;

                std::cout << "Kernel [0]Inner Product [1]Polynomial [2]Gaussian: ";
                std::cin >> kernel_type;

                if(kernel_type != 0){
                    if(kernel_type == 1){
                        std::cout << "Polynomial degree: ";
                    }else{
                        std::cout << "Gaussian gamma: ";
                    }
                    std::cin >> kernel_param;
                }

                std::clock_t begin = std::clock();
                mltk::KernelType type = getKernelType(kernel_type);
                mltk::classifier::SMO<double> smo(samples, type, kernel_param, verbose);
                
                smo.setMaxTime(max_time);
//                Validation<double> validate(*samples, &smo, 10);
//
//                validate.setVerbose(verbose);
//                validate.partTrainTest(fold);
//                val_sol = validate.validation(fold, qtde);
                std::clock_t end = std::clock();

                // std::cout << "\nAccuracy: "<< val_sol.accuracy << std::endl;
                // std::cout << "Precision: "<< val_sol.precision << std::endl;
                // std::cout << "Recall: "<< val_sol.recall << std::endl;
                // std::cout << std::endl;

                double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
                std::cout << std::endl;
                std::cout << elapsed_secs << " seconds to compute.\n";
            }else{
                std::cout << "Load a dataset first..." << std::endl;
            }
            waitUserAction();
            break;
        case 0: case 109:
            mainMenu();
            break;
        default:
            inva = true;
            break;
    }
    mainOption(8);
}

void primalClassifiersOption(int option){
    int p, q, i, norm, flexible, svs;
    double rate, gamma, alpha_prox;

    switch (option) {
        case 1:
            if(!samples.isEmpty()){
                std::cout << "Value of the learning rate: ";
                std::cin >> rate;
                std::cout << "Value of the q norm: ";
                std::cin >> q;
                std::cout << std::endl;

                mltk::classifier::PerceptronPrimal<double> perc(samples, q, rate);

                std::clock_t begin = std::clock();
                perc.train();
                sol = perc.getSolution();

                std::cout << "Number of steps through data: " << perc.getSteps() << std::endl;
                std::cout << "Number of updates: " << perc.getUpdates() << std::endl;
                std::cout << "Weights vector:" << std::endl;
                std::cout << "[";
                for(i = 0; i < sol.w.size(); i++){
                    std::cout << sol.w[i] << ", ";
                }
                std::cout << sol.bias <<  "]" << std::endl;
                std::cout << std::endl;

                std::clock_t end = std::clock();

                double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
                std::cout << std::endl;
                std::cout << elapsed_secs << " seconds to compute.\n";

                waitUserAction();
            }else{
                std::cout << "Load a dataset first..." << std::endl;
            }
            break;
        case 2:
            if(!samples.isEmpty()){
                std::cout << "Value of the learning rate: ";
                std::cin >> rate;
                std::cout << "Value of the q norm: ";
                std::cin >> q;
                std::cout << "Gamma value: ";
                std::cin >> gamma;
                std::cout << std::endl;

                mltk::classifier::PerceptronFixedMarginPrimal<double> perc(samples, gamma, q, rate);

                std::clock_t begin = std::clock();
                perc.train();
                sol = perc.getSolution();

                std::cout << "Number of steps through data: " << perc.getSteps() << std::endl;
                std::cout << "Number of updates: " << perc.getUpdates() << std::endl;
                std::cout << "Weights vector:" << std::endl;
                std::cout << "[";
                for(i = 0; i < sol.w.size(); i++){
                    std::cout << sol.w[i] << ", ";
                }
                std::cout << sol.bias <<  "]" << std::endl;
                std::cout << std::endl;

                std::clock_t end = std::clock();

                double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
                std::cout << std::endl;
                std::cout << elapsed_secs << " seconds to compute.\n";

                waitUserAction();
            }else{
                std::cout << "Load a dataset first..." << std::endl;
            }
            break;
        case 3:
            if(!samples.isEmpty()){
                std::cout << "[1]p or [2]q norm: ";
                std::cin >> norm;
                std::cout << std::endl;

                if(norm == 1){
                    std::cout << "p-norm value: ";
                    std::cin >> p;
                    if(p == 1.0){
                        q = -1.0;
                    }else{
                        q = p/(p-1.0);
                    }
                }else{
                    std::cout << "q-norm value: ";
                    std::cin >> q;
                    if(q == -1.0){
                        p = 1.0;
                    }else if(q == 1.0){
                        p = 100.0;
                    }else{
                        p = (int)(q/(q-1.0));
                    }
                }
                std::cout << std::endl;
                std::cout << "Flexibilization value [0 - no flexibilization]: ";
                std::cin >> flexible;
                std::cout << std::endl;

                std::cout << "Alpha aproximation value [1 - alpha]: ";
                std::cin >> alpha_prox;
                std::cout << std::endl;

                mltk::classifier::IMAp<double> imap(samples);

                imap.setMaxTime(max_time);
                imap.setpNorm(p);
                imap.setqNorm(q);
                imap.setFlexible(flexible);
                imap.setAlphaAprox(alpha_prox);

                std::clock_t begin = std::clock();

                if(imap.train()){
                    sol = imap.getSolution();
                    std::cout << "Training successful..." << std::endl;
                    std::cout << "\nMargin = " << sol.margin << ", Support Vectors = " << sol.svs << "\n" << std::endl;
                }

                std::clock_t end = std::clock();

                double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
                std::cout << std::endl;
                std::cout << elapsed_secs << " seconds to compute.\n";

                waitUserAction();
            }else{
                std::cout << "Load a dataset first..." << std::endl;
            }
            break;
        case 4:
            if(!samples.isEmpty()) {
                size_t k;
                std::cout << "k value: ";
                std::cin >> k;
                std::cout << std::endl;

                mltk::classifier::KNNClassifier<double> knn(samples, k);
                std::vector<std::string> class_names = samples.classesNames();
                std::vector<int> classes = samples.classes();

                auto conf_matrix = mltk::validation::generateConfusionMatrix(samples, knn);
                std::cout << "Confusion Matrix: " << std::endl;
                mltk::utils::printConfusionMatrix(classes, samples.classesNames(), conf_matrix);
                waitUserAction();
            }else{
                std::cout << "Load a dataset first..." << std::endl;
            }
            break;
        case 0:
            classifiersMenu();
            break;
        case 109:
            mainMenu();
            break;
        default:
            inva = true;
            break;
    }
    classifiersOption(1);
}

void dualClassifiersOption(int option){
    int i, kernel_type = 0, kernel_param = 0;
    double rate;

    switch (option) {
        case 1:
            if(!samples.isEmpty()){
                std::cout << "Learning rate: ";
                std::cin >> rate;
                std::cout << "Kernel [0]Inner Product [1]Polynomial [2]Gaussian: ";
                std::cin >> kernel_type;

                if(kernel_type != 0){
                    if(kernel_type == 1){
                        std::cout << "Polynomial degree: ";
                    }else{
                        std::cout << "Gaussian gamma: ";
                    }
                    std::cin >> kernel_param;
                }

                std::clock_t begin = std::clock();
                mltk::KernelType type = getKernelType(kernel_type);
                mltk::classifier::PerceptronDual<double> perc_dual(samples, type, kernel_param,rate);
                perc_dual.train();

                sol = perc_dual.getSolution();

                std::cout << std::endl;
                std::cout << "Alpha vector:" << std::endl;
                std::cout << "[";

                for(i = 0; i < sol.alpha.size(); i++){
                    std::cout << sol.alpha[i] << ", ";
                }

                std::cout << sol.bias <<  "]" << std::endl;
                std::cout << std::endl;
                std::cout << "Weights vector:" << std::endl;
                std::cout << "[";

                for(i = 0; i < sol.w.size(); i++){
                    std::cout << sol.w[i] << ", ";
                }

                std::cout << sol.bias <<  "]" << std::endl;
                std::cout << std::endl;

                std::clock_t end = std::clock();

                double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
                std::cout << std::endl;
                std::cout << elapsed_secs << " seconds to compute.\n";
            }else{
                std::cout << "Load a dataset first..." << std::endl;
            }
            waitUserAction();
            break;
        case 2:
            if(!samples.isEmpty()){
                double gamma;
                std::cout << "Learning rate: ";
                std::cin >> rate;
                std::cout << "Gamma value: ";
                std::cin >> gamma;
                std::cout << "Kernel [0]Inner Product [1]Polynomial [2]Gaussian: ";
                std::cin >> kernel_type;

                if(kernel_type != 0){
                    if(kernel_type == 1){
                        std::cout << "Polynomial degree: ";
                    }else{
                        std::cout << "Gaussian gamma: ";
                    }
                    std::cin >> kernel_param;
                }

                std::clock_t begin = std::clock();
                mltk::KernelType type = getKernelType(kernel_type);
                mltk::classifier::PerceptronFixedMarginDual<double> perc_fixmargin_dual(samples, type, kernel_param, gamma, rate);
                perc_fixmargin_dual.train();

                sol = perc_fixmargin_dual.getSolution();
                std::cout << std::endl;
                std::cout << "Alpha vector:" << std::endl;
                std::cout << "[";
                for(i = 0; i < sol.alpha.size(); i++){
                    std::cout << sol.alpha[i] << ", ";
                }
                std::cout << sol.bias <<  "]" << std::endl;
                std::cout << std::endl;

                std::cout << "Weights vector:" << std::endl;
                std::cout << "[";
                for(i = 0; i < sol.w.size(); i++){
                    std::cout << sol.w[i] << ", ";
                }
                std::cout << sol.bias <<  "]" << std::endl;
                std::cout << std::endl;

                std::clock_t end = std::clock();

                double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
                std::cout << std::endl;
                std::cout << elapsed_secs << " seconds to compute.\n";
            }else{
                std::cout << "Load a dataset first..." << std::endl;
            }
            waitUserAction();
            break;
        case 3:
            if(!samples.isEmpty()){
                std::cout << "Learning rate: ";
                std::cin >> rate;
                std::cout << "Kernel [0]Inner Product [1]Polynomial [2]Gaussian: ";
                std::cin >> kernel_type;

                if(kernel_type != 0){
                    if(kernel_type == 1){
                        std::cout << "Polynomial degree: ";
                    }else{
                        std::cout << "Gaussian gamma: ";
                    }
                    std::cin >> kernel_param;
                }

                std::clock_t begin = std::clock();
                mltk::KernelType type = getKernelType(kernel_type);
                mltk::classifier::IMADual<double> ima_dual(samples, type, kernel_param, rate);

                ima_dual.setMaxTime(max_time);
                ima_dual.setVerbose(verbose);
                ima_dual.train();
                std::clock_t end = std::clock();

                double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
                std::cout << std::endl;
                std::cout << elapsed_secs << " seconds to compute.\n";

                sol = ima_dual.getSolution();
            }else{
                std::cout << "Load a dataset first..." << std::endl;
            }
            waitUserAction();
            break;
        case 4:
            if(!samples.isEmpty()){
                std::cout << "Kernel [0]Inner Product [1]Polynomial [2]Gaussian: ";
                std::cin >> kernel_type;

                if(kernel_type != 0){
                    if(kernel_type == 1){
                        std::cout << "Polynomial degree: ";
                    }else{
                        std::cout << "Gaussian gamma: ";
                    }
                    std::cin >> kernel_param;
                }

                mltk::KernelType type = getKernelType(kernel_type);
                std::clock_t begin = std::clock();
                mltk::classifier::SMO<double> smo(samples, type, kernel_param, verbose);

                smo.setMaxTime(max_time);
                smo.setVerbose(verbose);
                smo.train();
                std::clock_t end = std::clock();

                double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
                std::cout << std::endl;
                std::cout << elapsed_secs << " seconds to compute.\n";

                sol = smo.getSolution();
                waitUserAction();
                classifiersOption(2);
            }else{
                std::cout << "Load a dataset first..." << std::endl;
            }
            waitUserAction();
            break;
        case 0:
            classifiersMenu();
            break;
        case 109:
            mainMenu();
            break;
        default:
            break;
    }
    classifiersOption(2);
}

mltk::KernelType getKernelType(int kernel_type){
    switch(kernel_type){
        case 0:
            return mltk::KernelType::INNER_PRODUCT;
        case 1:
            return mltk::KernelType::POLYNOMIAL;
        case 2:
            return mltk::KernelType::GAUSSIAN;
        default:
            return mltk::KernelType::INVALID_TYPE;
    }
}

template < typename Learner>
mltk::validation::ValidationReport runValidation(const mltk::Data<double>& data, Learner learner, int fold, int qtde, int verbose, size_t seed){
    mltk::validation::ValidationReport report;

    if(qtde > 1){
        report = mltk::validation::kkfold(data, learner, qtde, fold, true, seed, verbose);
    }else{
        report = mltk::validation::kfold(data, learner, fold, true, seed, verbose);
    }
    std::cout << fold << "-fold accuracy: " << report.accuracy << std::endl;
    std::cout << fold << "-fold error: " << report.error << std::endl;
    return report;
}