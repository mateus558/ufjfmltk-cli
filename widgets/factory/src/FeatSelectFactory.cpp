//
// Created by mateus on 01/06/2021.
//

#include "FeatSelectFactory.h"

namespace factory{
    std::map<FeatSelects, FeatSelect*> allocated_featselects;

    FeatSelect::FeatSelect(cppcli::CLWidget *parent) : cppcli::CLWidget(parent) {

    }

    FeatSelect::FeatSelect(mltk::Data<> &data, const std::string& title, cppcli::CLWidget *parent) :
            cppcli::CLWidget(parent, title),
            m_samples(&data){

    }

    bool FeatSelect::build() {
        register_group("classifiers", "Select a classifier:\n");

        int opt = 1;
        auto primal_classifiers = factory::Classifier::get_primal_classifiers(*this->m_samples, mltk::Data<>(),
                                                                              mltk::Data<>(), this);

        for(const auto& pclassifier: primal_classifiers){
            auto fselect_primal = [this, pclassifier](){
                this->classifier = pclassifier->build_learner();
                this->build_learner();
                this->m_samples->copy(this->learner->selectFeatures());
                wait_action();
                return true;
            };
            register_action("classifiers", pclassifier->get_text(), std::to_string(opt++), fselect_primal);
        }

        auto dual_classifiers = factory::Classifier::get_dual_classifiers(*this->m_samples, mltk::Data<>(),
                                                                          mltk::Data<>(), this);

        for(const auto& dclassifier: dual_classifiers){
            auto fselect_dual = [this, dclassifier](){
                this->classifier = dclassifier->build_learner();
                this->build_learner();
                this->m_last_result = std::make_shared<mltk::Data<>>(this->learner->selectFeatures());
                wait_action();
                return true;
            };
            register_action("classifiers", dclassifier->get_text(), std::to_string(opt++), fselect_dual);
        }

        add_exit_group();
        return true;
    }

    FeatSelect *FeatSelect::make_featselect(FeatSelects featselect, mltk::Data<> &data, cppcli::CLWidget *parent) {
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

    std::vector<FeatSelect *> FeatSelect::get_featselect(mltk::Data<> &data, cppcli::CLWidget *parent) {
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

    void FeatSelect::set_classifier(const ClassifierPointer &m_classifier) {
        FeatSelect::classifier = m_classifier;
    }

    const std::shared_ptr<mltk::Data<>> &FeatSelect::getLastResult() const {
        return m_last_result;
    }


    Golub::Golub(mltk::Data<> &data, cppcli::CLWidget *parent) : FeatSelect(data, "Golub" , parent) {
        set_text("Golub");
    }

    void Golub::set_parameters() {
        std::cout << "Desired dimension (max. " << this->m_samples->dim() << "): ";
        std::cin >> final_dim;
    }

    FeatSelectPointer Golub::build_learner() {
        set_parameters();
        this->learner = std::make_shared<mltk::featselect::Golub<double>>(*this->m_samples, this->classifier.get(), final_dim);
        return this->learner;
    }


    Fisher::Fisher(mltk::Data<> &data, cppcli::CLWidget *parent) : FeatSelect(data, "Fisher", parent) {
        set_text("Fisher");
    }

    void Fisher::set_parameters() {
        std::cout << "Desired dimension (max. " << this->m_samples->dim() << "): ";
        std::cin >> final_dim;
    }

    FeatSelectPointer Fisher::build_learner() {
        set_parameters();
        this->learner = std::make_shared<mltk::featselect::Fisher<double>>(*this->m_samples, this->classifier.get(), final_dim);
        return this->learner;
    }


    RFEAlg::RFEAlg(mltk::Data<> &data, cppcli::CLWidget *parent) : FeatSelect(data, "Recursive Feature Elimination (RFE)", parent) {
        set_text("Recursive Feature Elimination (RFE)");
    }

    void RFEAlg::set_parameters() {
        std::cout << "Desired dimension (max. " << this->m_samples->dim() << "): ";
        std::cin >> final_dim;
        std::cout << "Features eliminated at a time: ";
        std::cin >> jump;
        std::cout << std::endl;
    }

    FeatSelectPointer RFEAlg::build_learner() {
        set_parameters();
        this->learner = std::make_shared<mltk::featselect::RFE<double>>(*this->m_samples, this->classifier.get(),
                final_dim, nullptr, 1, jump);
        return this->learner;
    }


    AOSAlg::AOSAlg(mltk::Data<> &data, cppcli::CLWidget *parent) : FeatSelect(data, "Admissible Ordered Search (AOS)", parent) {
        set_text("Admissible Ordered Search (AOS)");
    }

    void AOSAlg::set_parameters() {
        std::cout << "Desired dimension (max. " << this->m_samples->dim() << "): ";
        std::cin >> final_dim;
        std::cout << "Branching factor (max. " << this->m_samples->dim() << "): ";
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
    }

    FeatSelectPointer AOSAlg::build_learner() {
        set_parameters();
        this->learner = std::make_shared<mltk::featselect::AOS<double>>(*this->m_samples, this->classifier.get(),
                                                                        final_dim, nullptr, branching, branch_form,
                                                                        choice_form, prof_look_ahead, cut);
        return this->learner;
    }

}