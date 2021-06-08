//
// Created by mateus on 01/06/2021.
//

#include "ClusterersFactory.h"

namespace factory{
    std::map<Clusterers, Clusterer*> allocated_clusterers;


    Clusterer::Clusterer(cppcli::CLWidget *parent) : AlgorithmFactory(parent) {

    }

    Clusterer::Clusterer(const mltk::Data<> &data, cppcli::CLWidget *parent) :
            AlgorithmFactory(parent),
    m_samples(data){

    }

    bool Clusterer::build() {
        return true;
    }

    Clusterer *Clusterer::make_clusterer(Clusterers clusterer, const mltk::Data<> &data, cppcli::CLWidget* parent) {
        switch (clusterer) {
            case KMEANS:
                return new KMeans(data, parent);
            default:
                return nullptr;
        }
    }

    std::vector<Clusterer *> Clusterer::get_clusterers(const mltk::Data<> &data, cppcli::CLWidget *parent) {
        std::vector<Clusterer *> clusts;
        for(int clust = factory::Clusterers::CHEAD; clust != factory::Clusterers::CTAIL; clust++){
            if(clust == factory::Clusterers::CHEAD) continue;
            auto alg = static_cast<factory::Clusterers>(clust);
            Clusterer* obj_alg;
            if(allocated_clusterers.find(alg) == allocated_clusterers.end()) {
                obj_alg = factory::Clusterer::make_clusterer(alg, data, parent);
                allocated_clusterers[alg] = obj_alg;
            }else{
                obj_alg = allocated_clusterers[alg];
            }
            clusts.push_back(obj_alg);
        }
        return clusts;
    }

    std::string Clusterer::option_selector() {
        return "";
    }

    KMeans::KMeans(const mltk::Data<> &data, cppcli::CLWidget *parent) : Clusterer(data, parent) {
        set_text("KMeans");
    }

    bool KMeans::operator()() {
        int init = 0;
        std::cout << "Number of clusters: ";
        std::cin >> this->clusters;
        std::cout << "Initialization [0 - random, 1 - kmeanspp]: ";
        std::cin >> init;

        initialization = (init == 0)?"random":"kmeanspp";
        mltk::clusterer::KMeans kmeans(this->m_samples, clusters, initialization, this->m_seed, this->m_verbose);
        kmeans.setMaxTime(this->m_maxtime);
        kmeans.train();
        wait_action();
        return true;
    }
}