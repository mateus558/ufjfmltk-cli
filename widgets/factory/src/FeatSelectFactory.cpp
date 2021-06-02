//
// Created by mateus on 01/06/2021.
//

#include "FeatSelectFactory.h"

namespace factory{
    std::map<FeatSelects, FeatSelect*> allocated_featselects;

    FeatSelect::FeatSelect(cppcli::CLWidget *parent) : cppcli::CLWidget(parent) {

    }

    FeatSelect::FeatSelect(const mltk::Data<> &data, cppcli::CLWidget *parent) :
            cppcli::CLWidget(parent),
            m_samples(data){

    }

    bool FeatSelect::build() {
        return true;
    }

    FeatSelect *FeatSelect::make_featselect(FeatSelects featselect, const mltk::Data<> &data, cppcli::CLWidget *parent) {
        switch (featselect) {
            case FeatSelects::GOLUB:
                return new Golub(data, parent);
            case FeatSelects::FISHER:
                return new Fisher(data, parent);
            case FeatSelects::RFE:
                return new RFEAlg(data, parent);
            case FeatSelects::AOS:
                return new AOSAlg(data, parent);
            default:
                return nullptr;
        }
    }

    std::vector<FeatSelect *> FeatSelect::get_featselect(const mltk::Data<> &data, cppcli::CLWidget *parent) {
        std::vector<FeatSelect *> algs;
        for(int feat = factory::FeatSelects::FHEAD; feat != factory::FeatSelects::FTAIL; feat++){
            if(feat == factory::FeatSelects::FHEAD) continue;
            auto alg = static_cast<factory::FeatSelects>(feat);
            FeatSelect* obj_alg;
            if(allocated_featselects.find(alg) == allocated_featselects.end()) {
                obj_alg = factory::FeatSelect::make_featselect(alg, data, parent);
                allocated_featselects[alg] = obj_alg;
            }else{
                obj_alg = allocated_featselects[alg];
            }
            algs.push_back(obj_alg);
        }
        return algs;
    }

    std::string FeatSelect::option_selector() {
        return "";
    }

    Golub::Golub(const mltk::Data<> &data, cppcli::CLWidget *parent) : FeatSelect(data, parent) {
        set_text("Golub");
    }

    bool Golub::operator()() {
        wait_action();
        return true;
    }


    Fisher::Fisher(const mltk::Data<> &data, cppcli::CLWidget *parent) : FeatSelect(data, parent) {
        set_text("Fisher");
    }

    bool Fisher::operator()() {
        wait_action();
        return true;
    }

    RFEAlg::RFEAlg(const mltk::Data<> &data, cppcli::CLWidget *parent) : FeatSelect(data, parent) {
        set_text("Recursive Feature Elimination (RFE)");
    }

    bool RFEAlg::operator()() {
        wait_action();
        return true;
    }

    AOSAlg::AOSAlg(const mltk::Data<> &data, cppcli::CLWidget *parent) : FeatSelect(data, parent) {
        set_text("Admissible Ordered Search (AOS)");
    }

    bool AOSAlg::operator()() {
        wait_action();
        return true;
    }
}