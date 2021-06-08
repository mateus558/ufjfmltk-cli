//
// Created by mateus on 01/06/2021.
//

#include "RegressorsFactory.h"
#include "ufjfmltk/Visualize.hpp"

namespace factory {
    std::map<Regressors, Regressor*> allocated_regressors;


    Regressor::Regressor(cppcli::CLWidget *parent) : AlgorithmFactory(parent) {

    }

    Regressor::Regressor(const mltk::Data<> &data, cppcli::CLWidget *parent):
            AlgorithmFactory(parent),
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

        mltk::regressor::LMSPrimal<> lms(this->m_samples, rate, this->m_verbose);
        lms.setMaxTime(this->m_maxtime);
        lms.setSeed(this->m_seed);
        lms.train();

        auto real = this->m_samples.getLabels();
        mltk::Point<double> predicted(this->m_samples.size());
        std::for_each(this->m_samples.begin(), this->m_samples.end(), [&lms](const auto& point) {
            return lms.evaluate(*point);
            });
        double mse = mltk::metrics::MSE(real, predicted);
        std::cout << "\nMSE: " << mse << std::endl;
        wait_action();
        ask_run_action("Visualize results", [this, &lms]() {
            mltk::visualize::Visualization<double> vis(this->m_samples, false);
            int x = 0, y = 1;

            if (this->m_samples.dim() == 1) {
                vis.plot1DRegresionHyperplane(x, lms.getSolution());
            }
            else if (this->m_samples.dim() == 2) {
                this->m_samples.setFeaturesNames({ x + 1, y + 1});
                vis.plot2DRegresionHyperplane(x, y, lms.getSolution());
            }
            
            return true;
            });
        return true;
    }
}