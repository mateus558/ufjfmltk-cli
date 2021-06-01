//
// Created by mateus on 29/05/2021.
//

#include "DataWidget.h"

DataWidget::DataWidget(cppcli::CLWidget *parent) : CLWidget(parent, "Data") {

}

bool DataWidget::build() {
    set_header(this->m_parent->get_header());
    set_cmd("data");

    register_group("main", "Select an option:\n", cppcli::GroupType::ACTION);

    register_action("main", "Insert features", "1", insert_features());
    register_action("main", "Remove features", "2", remove_features());
    register_action("main", "Remove point", "3", remove_point());
    register_action("main", "Data variance", "4", data_variance());
    register_action("main", "Data radius", "5", data_radius());
    register_action("main", "Distance from the center of the classes", "6", centers_distance());
    register_action("main", "Normalize dataset", "7", normalize_dataset());
    register_action("main", "Print dataset", "8", print_dataset());

    add_exit_group();
    return false;
}

cppcli::Action::Type DataWidget::print_dataset() {
    cppcli::Action::Type print = [this](){
        if(!settings::data.isEmpty()){
            std::cout << settings::data << std::endl;
            wait_action();
        }else push_message("Load a dataset first...");
        clear();
        return true;
    };
    return print;
}

cppcli::Action::Type DataWidget::normalize_dataset() {
    cppcli::Action::Type normalize = [this](){
        if(!settings::data.isEmpty()){
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
            settings::data.normalize(p);
            std::cout << "The dataset was normalized." << std::endl;
            std::clock_t end = std::clock();

            double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
            std::cout << std::endl;
            std::cout << elapsed_secs << " seconds to compute.\n";
            wait_action();
        }else push_message("Load a dataset first...");
        return true;
    };
    return normalize;
}

cppcli::Action::Type DataWidget::insert_features() {
    cppcli::Action::Type feat_ins = [this](){
        if(!settings::data.isEmpty()){
            int i, j;
            int totalFeat, flag_feat, f, fnamesize;
            std::vector<int> feats;
            std::vector<int> fnames = settings::data.getFeaturesNames();

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
            mltk::Data<double> temp = settings::data.insertFeatures(feats);

            if(!temp.isEmpty()){
                settings::data.clear();
                settings::data = temp.copy();
            }else{
                std::cerr << "Something went wrong." << std::endl;
            }
            wait_action();
        }else push_message("Load a dataset first...");
        return true;
    };
    return feat_ins;
}

cppcli::Action::Type DataWidget::remove_point() {
    cppcli::Action::Type point_rem = [this](){
        if(!settings::data.isEmpty()){
            int i;
            std::cout << "Point to remove index (-1 to cancel): ";
            std::cin >> i;

            if((i < 0) || (i >= settings::data.size())){
                push_message("Invalid point index.", cppcli::LOGERROR);
            }

            settings::data.removePoint(i);
            wait_action();
        }else push_message("Load a dataset first...");
        return true;
    };
    return point_rem;
}

cppcli::Action::Type DataWidget::remove_features() {
    cppcli::Action::Type feat_rem = [this](){
        if(!settings::data.isEmpty()){
            int i, j;
            int totalFeat, flag_feat, f, fnamesize;
            std::vector<int> feats;
            std::vector<int> fnames = settings::data.getFeaturesNames();

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
            settings::data.removeFeatures(feats);

            fnames = settings::data.getFeaturesNames();

            wait_action();
        }else push_message("Load a dataset first...");
        return true;
    };
    return feat_rem;
}

cppcli::Action::Type DataWidget::data_variance() {
    cppcli::Action::Type var = [this](){
        if(!settings::data.isEmpty()){
            int index;

            std::cout << "Feature to be ignored (-1 doesnt ignore any feature): ";
            std::cin >> index;
            std::clock_t begin = std::clock();
            std::cout << std::endl;
            std::cout << "The variance values is: " << mltk::stats::var(settings::data, index) << std::endl;
            std::clock_t end = std::clock();

            double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
            std::cout << std::endl;
            std::cout << elapsed_secs << " seconds to compute.\n";
            wait_action();
        }else push_message("Load a dataset first...");
        return true;
    };
    return var;
}

cppcli::Action::Type DataWidget::data_radius() {
    cppcli::Action::Type radius = [this](){
        if(!settings::data.isEmpty()){
            int index, q;

            std::cout << "Feature to be ignored: ";
            std::cin >> index;
            std::cout << "Value of q [q = 1 | q = 2]: ";
            std::cin >> q;
            std::cout << std::endl;

            std::clock_t begin = std::clock();
            std::cout << "The value of the radius is: " << mltk::stats::radius(settings::data, index, q) << std::endl;
            std::clock_t end = std::clock();

            double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
            std::cout << std::endl;
            std::cout << elapsed_secs << " seconds to compute.\n";
            wait_action();
        }else push_message("Load a dataset first...");
        return true;
    };
    return radius;
}

cppcli::Action::Type DataWidget::centers_distance() {
    cppcli::Action::Type centers_dist = [this](){
        if(!settings::data.isEmpty()){
            int index;

            std::cout << "Feature to be ignored: ";
            std::cin >> index;
            std::cout << std::endl;

            std::clock_t begin = std::clock();
            std::cout << "The value of the center of the classes are: " << mltk::stats::distCenters(settings::data, index) << std::endl;
            std::cout << std::endl;
            std::clock_t end = std::clock();

            double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

            std::cout << elapsed_secs << " seconds to compute.\n";
            wait_action();
        }else push_message("Load a dataset first...");
        return true;
    };
    return centers_dist;
}
