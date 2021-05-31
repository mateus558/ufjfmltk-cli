//
// Created by mateus on 29/05/2021.
//

#include "MLTKApp.h"
#include <sstream>
#include "settings.h"


size_t settings::seed = 0;
size_t settings::verbose = 1;
size_t settings::max_time = 100;
std::string settings::data_folder = "datasets/";
mltk::Data<> settings::data;
mltk::Data<> settings::train;
mltk::Data<> settings::test;

MLTKApp::MLTKApp(cppcli::CLWidget *parent) : CLWidget(parent) {
    m_dataset = new DatasetWidget(this);
    m_data = new DataWidget(this);
    m_visual = new VisualizationWidget(this);
    m_classifiers = new ClassifiersWidget(this);
    m_featselect = new FeatSelectWidget(this);
    m_regressor = new RegressorWidget(this);
    m_clusterer = new ClustererWidget(this);
    m_validation = new ValidationWidget(this);
}

bool MLTKApp::build() {
    std::stringstream header;

    header << "         *----------------------------------------------------------* " << std::endl;
    header << "         *                 Machine Learning Toolkit                 * " << std::endl;
    header << "         *----------------------------------------------------------* " << std::endl;

    set_header(header.str());
    set_cmd("main");

    register_group("main", "Select an option:\n");

    register_widget("main", "Dataset", "1", m_dataset);
    register_widget("main", "Data", "2", m_data);
    register_widget("main", "Data visualization", "3", m_visual);
    register_widget("main", "Classifiers", "4", m_classifiers);
    register_widget("main", "Feature selection", "5", m_featselect);
    register_widget("main", "Regressors", "6", m_regressor);
    register_widget("main", "Clusterers", "7", m_clusterer);
    register_widget("main", "Validation", "8", m_validation);

    build_configs();

    return true;
}

void MLTKApp::build_configs() {
    register_group("configs", "\nConfigs:\n", cppcli::GroupType::ACTION);

    register_action("configs", "Set verbose", "v", [](){
        std::cout << "Verbose level [current: " << settings::verbose <<  "]: ";
        std::cin >> settings::verbose;
        wait_action();
        clear();
        return true;
    });

    register_action("configs", "Set max time", "t", [](){
        std::cout << "Max time [current: " << settings::max_time <<  "]: ";
        std::cin >> settings::max_time;
        wait_action();
        clear();
        return true;
    });

    register_action("configs", "Set seed", "s", [](){
        std::cout << "seed [current: " << settings::seed <<  "]: ";
        std::cin >> settings::seed;
        wait_action();
        clear();
        return true;
    });

    add_exit_group();

    register_action("exit", "Teste", "x", [this](){
        ask_run_action("continue?", [this](){
            push_message("A resposta é 42.", cppcli::LogType::CUSTOM, "COMPUTER");
            return true;
        }, "easter egg");
        return true;
    }, true);
}

MLTKApp::~MLTKApp() {
    delete m_dataset;
    delete m_data;
    delete m_visual;
    delete m_classifiers;
    delete m_featselect;
    delete m_regressor;
    delete m_clusterer;
    delete m_validation;
}