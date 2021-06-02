//
// Created by mateus on 01/06/2021.
//

#include "RegressorsFactory.h"

namespace factory {
    std::map<Regressors, Regressor*> allocated_regressors;


    Regressor::Regressor(cppcli::CLWidget *parent) : cppcli::CLWidget(parent) {

    }

    Regressor::Regressor(const mltk::Data<> &data, cppcli::CLWidget *parent):
            cppcli::CLWidget(parent),
            m_samples(data){

    }

    bool Regressor::build() {
        return true;
    }

    Regressor *Regressor::make_regressor(Regressors regressor, const mltk::Data<> &data, cppcli::CLWidget *parent) {
        switch (regressor) {
            case Regressors::LMS:
                return new LMSRegressor(data, parent);
            default:
                return nullptr;
        }
    }

    std::vector<Regressor *> Regressor::get_regressors(const mltk::Data<> &data, cppcli::CLWidget *parent) {
        std::vector<Regressor *> regs;
        for(int reg = factory::Regressors::RHEAD; reg != factory::Regressors::RTAIL; reg++){
            if(reg == factory::Regressors::RHEAD) continue;
            auto alg = static_cast<factory::Regressors>(reg);
            Regressor* obj_alg;
            if(allocated_regressors.find(alg) == allocated_regressors.end()) {
                obj_alg = factory::Regressor::make_regressor(alg, data, parent);
                allocated_regressors[alg] = obj_alg;
            }else{
                obj_alg = allocated_regressors[alg];
            }
            regs.push_back(obj_alg);
        }
        return regs;
    }

    std::string Regressor::option_selector() {
        return "";
    }

    LMSRegressor::LMSRegressor(const mltk::Data<> &data, cppcli::CLWidget *parent) : Regressor(data, parent) {
        set_text("Least Means Squares (LMS)");
    }

    bool LMSRegressor::operator()() {
        double rate = 0.01;
        std::cout << "Learning rate: ";
        std::cin >> rate;

        mltk::regressor::LMSPrimal<> lms(this->m_samples, rate, 1);
        lms.train();

        wait_action();
        return true;
    }
}