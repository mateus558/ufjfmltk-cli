//
// Created by mateus on 31/05/2021.
//

#include "ClassifiersFactory.h"
#include "ufjfmltk/Visualize.hpp"
#include <chrono>

namespace factory{
    std::map<ClassifierPrimal, Classifier*> allocated_primal_classifiers;
    std::map<ClassifierDual, Classifier*> allocated_dual_classifiers;

    Classifier::Classifier(cppcli::CLWidget *parent) : cppcli::CLWidget(parent) {

    }

    Classifier::Classifier(mltk::Data<>& train, mltk::Data<>& test, cppcli::CLWidget *parent):
            cppcli::CLWidget(parent),
            m_train(train),
            m_test(test)
    {
    }

    Classifier * Classifier::make_primal_classifier(ClassifierPrimal classifier, mltk::Data<>& samples,
                                                   mltk::Data<>& train,
                                                   mltk::Data<>& test, cppcli::CLWidget *parent) {
        auto _train = (train.isEmpty())?samples.copy(): train.copy();
        auto _test = (test.isEmpty())?samples.copy(): test.copy();
        switch (classifier) {
            case ClassifierPrimal::IMAP:
                return new IMAp(_train, _test, parent);
            case ClassifierPrimal::PERCEPTRON:
                return new Perceptron(_train, _test, parent);
            case ClassifierPrimal::FMPP:
                return new FMP(_train, _test, parent);
            case ClassifierPrimal::KNN:
                return new KNNClassifier(_train, _test, parent);
            default:
                std::cerr << "Primal algorithm not registered" << std::endl;
                return nullptr;
        }
    }

    Classifier * Classifier::make_dual_classifier(ClassifierDual classifier, mltk::Data<>& samples,
                                                          mltk::Data<>& train,
                                                          mltk::Data<>& test, cppcli::CLWidget *parent) {
        auto _train = (train.isEmpty())?samples.copy(): train.copy();
        auto _test = (test.isEmpty())?samples.copy(): test.copy();
        switch (classifier) {
            case ClassifierDual::IMADUAL:
                return new IMADual(_train, _test, parent);
            case ClassifierDual::PERCEPTROND:
                return new PerceptronDual(_train, _test, parent);
            case ClassifierDual::FMPD:
                return new FMPDual(_train, _test, parent);
            case ClassifierDual::SMO:
                return new SMOClassifier(_train, _test, parent);
            default:
                std::cerr << "Dual algorithm not registered" << std::endl;
                return nullptr;
        }
    }

    std::vector<Classifier *> Classifier::get_primal_classifiers(mltk::Data<>& data, mltk::Data<>& train,
                                                                       mltk::Data<>& test, cppcli::CLWidget *parent) {
        std::vector<Classifier *> primals;
        for(int primal = factory::ClassifierPrimal::PHEAD; primal != factory::ClassifierPrimal::PTAIL; primal++){
            if(primal == factory::ClassifierPrimal::PHEAD) continue;
            auto alg = static_cast<factory::ClassifierPrimal>(primal);
            Classifier* obj_alg;
            if(allocated_primal_classifiers.find(alg) == allocated_primal_classifiers.end()) {
                obj_alg = factory::Classifier::make_primal_classifier(alg, data, train, test, parent);
                allocated_primal_classifiers[alg] = obj_alg;
            }else{
                obj_alg = allocated_primal_classifiers[alg];
            }
            primals.push_back(obj_alg);
        }
        return primals;
    }

    std::vector<Classifier *>
    Classifier::get_dual_classifiers(mltk::Data<> &data, mltk::Data<>& train, mltk::Data<>& test,
                                     cppcli::CLWidget *parent) {
        std::vector<Classifier *> duals;
        for(int dual = factory::ClassifierDual::DHEAD; dual != factory::ClassifierDual::DTAIL; dual++){
            if(dual == factory::ClassifierDual::DHEAD) continue;
            auto alg = static_cast<factory::ClassifierDual>(dual);
            Classifier* obj_alg;
            if(allocated_dual_classifiers.find(alg) == allocated_dual_classifiers.end()) {
                obj_alg = factory::Classifier::make_dual_classifier(alg, data, train, test, parent);
                allocated_dual_classifiers[alg] = obj_alg;
            }else{
                obj_alg = allocated_dual_classifiers[alg];
            }
            duals.push_back(obj_alg);
        }
        return duals;
    }


    std::string Classifier::option_selector() {
        return "";
    }

    mltk::KernelType Classifier::get_kernel_type(int kernel_type){
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

    bool Classifier::is_primal() const {
        assert(this->learner);
        return this->learner->getFormulationString() == "Primal";
    }

    bool Classifier::build() {
        return true;
    }

    void Classifier::set_train(mltk::Data<> &mTrain) {
        m_train = mTrain;
    }

    void Classifier::visualize_options(mltk::classifier::Classifier<double> &learner, bool only_decision) {
        if(!only_decision) {
            ask_run_action("Visualize results", [this, &learner]() {
                mltk::visualize::Visualization<double> vis(this->m_train, false);
                int x = 0, y = 1, z = 2;

                if (this->m_train.dim() == 2) {
                    vis.plot2DwithHyperplane(x, y, learner.getSolution());
                    ask_run_action("Show decision surface", [this, &learner, x, y, &vis]() {
                        this->m_train.setFeaturesNames({x + 1, y + 1});
                        vis.plotDecisionSurface2D(learner, x, y);
                        return true;
                    });
                } else if (this->m_train.dim() == 3) {
                    this->m_train.setFeaturesNames({x + 1, y + 1, z + 1});
                    vis.plot3DwithHyperplane(x, y, z, learner.getSolution());
                } else {
                    std::cout << "Feature on x axis: ";
                    std::cin >> x;
                    std::cout << "Feature on y axis: ";
                    std::cin >> y;
                    std::cout << "Feature on z axis: ";
                    std::cin >> z;
                    vis.plot3DwithHyperplane(x, y, z, learner.getSolution());
                }
                return true;
            });
        }else{
            ask_run_action("Show decision surface", [this, &learner]() {
                mltk::visualize::Visualization<double> vis(this->m_train, false);
                int x = 0, y = 1;
                this->m_train.setFeaturesNames({x + 1, y + 1});
                vis.plotDecisionSurface2D(learner, x, y);
                return true;
            });
        }
    }

    IMAp::IMAp(mltk::Data<>& train, mltk::Data<>& test, cppcli::CLWidget *parent) :
    Classifier(train, test, parent)
    {
        set_text("Incremental Margin Algorithm (IMAp)");
    }

    bool IMAp::operator()() {
        set_parameters();

        mltk::classifier::IMAp<double> imap(this->m_train, p, flex);
        imap.setAlphaAprox(alpha_aprox);
        imap.train();

        wait_action();
        visualize_options(imap);
        return true;
    }

    void IMAp::set_parameters() {
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
    }

    ClassifierPointer IMAp::build_learner() {
        set_parameters();
        auto ima = std::make_shared<mltk::classifier::IMAp<double>>(this->m_train, p, flex);
        ima->setAlphaAprox(alpha_aprox);
        this->learner = ima;
        return this->learner;
    }

    IMADual::IMADual(mltk::Data<>& train, mltk::Data<>& test, cppcli::CLWidget *parent) :
    Classifier(train, test, parent)
    {
        set_text("Incremental Margin Algorithm (IMA Dual)");
    }

    bool IMADual::operator()() {
        set_parameters();
        std::clock_t begin = std::clock();
        mltk::classifier::IMADual<double> ima_dual(this->m_train, type, kernel_param);

        //ima_dual.setMaxTime(max_time);
        ima_dual.train();
        //val_sol = runValidation(samples, ima_dual, fold, qtde, verbose, SEED);
        std::clock_t end = std::clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        wait_action();
        visualize_options(ima_dual, true);
        return true;
    }

    void IMADual::set_parameters() {
        int kernel_type;
        std::cout << "Learning rate: ";
        std::cin >> rate;
        std::cout << "Kernel [0]Inner Product [1]Polynomial [2]Gaussian: ";
        std::cin >> kernel_type;
        type = get_kernel_type(kernel_type);
        if(type != mltk::INNER_PRODUCT){
            if(kernel_type == mltk::POLYNOMIAL){
                std::cout << "Polynomial degree: ";
            }else{
                std::cout << "Gaussian gamma: ";
            }
            std::cin >> kernel_param;
        }
    }

    ClassifierPointer IMADual::build_learner() {
        set_parameters();
        this->learner = std::make_shared<mltk::classifier::IMADual<double>>(this->m_train, type, kernel_param);
        return this->learner;
    }


    Perceptron::Perceptron(mltk::Data<>& train, mltk::Data<>& test, cppcli::CLWidget *parent) :
    Classifier(train, test, parent) {
        set_text("Perceptron primal");
    }

    bool Perceptron::operator()() {
        bool ret = true;
        set_parameters();
        mltk::classifier::PerceptronPrimal<double> perc(this->m_train, q, rate);

        std::clock_t begin = std::clock();
        ret = perc.train();
        auto sol = perc.getSolution();

        std::cout << "Number of steps through data: " << perc.getSteps() << std::endl;
        std::cout << "Number of updates: " << perc.getUpdates() << std::endl;
        std::cout << "Weights vector:" << std::endl;
        std::cout << "[";
        for(int i = 0; i < sol.w.size(); i++){
            std::cout << sol.w[i] << ", ";
        }
        std::cout << sol.bias <<  "]" << std::endl;
        std::cout << std::endl;

        std::clock_t end = std::clock();

        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        std::cout << std::endl;
        std::cout << elapsed_secs << " seconds to compute.\n";
        wait_action();
        visualize_options(perc);
        return ret;
    }

    void Perceptron::set_parameters() {
        std::cout << "Value of the learning rate: ";
        std::cin >> rate;
        std::cout << "Value of the q norm: ";
        std::cin >> q;
        std::cout << std::endl;
    }

    ClassifierPointer Perceptron::build_learner() {
        set_parameters();
        this->learner = std::make_shared<mltk::classifier::PerceptronPrimal<double>>(this->m_train, q, rate);
        return this->learner;
    }

    PerceptronDual::PerceptronDual(mltk::Data<>& train, mltk::Data<>& test, cppcli::CLWidget *parent)
            : Classifier(train, test, parent) {
        set_text("Perceptron dual");
    }

    bool PerceptronDual::operator()() {
        bool ret = true;
        set_parameters();
        std::clock_t begin = std::clock();
        mltk::classifier::PerceptronDual<double> perc_dual(this->m_train, type, kernel_param,rate);
        ret = perc_dual.train();

        auto sol = perc_dual.getSolution();

        std::cout << std::endl;
        std::cout << "Alpha vector:" << std::endl;
        std::cout << "[";

        for (int i = 0; i < sol.alpha.size(); i++) {
            std::cout << sol.alpha[i] << ", ";
        }

        std::cout << sol.bias << "]" << std::endl;
        std::cout << std::endl;
        std::cout << "Weights vector:" << std::endl;
        std::cout << "[";

        for (int i = 0; i < sol.w.size(); i++) {
            std::cout << sol.w[i] << ", ";
        }

        std::cout << sol.bias << "]" << std::endl;
        std::cout << std::endl;

        std::clock_t end = std::clock();

        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        std::cout << std::endl;
        std::cout << elapsed_secs << " seconds to compute.\n";
        wait_action();
        visualize_options(perc_dual, true);
        return ret;
    }

    void PerceptronDual::set_parameters() {
        int kernel_type;
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
        type = get_kernel_type(kernel_type);
    }

    ClassifierPointer PerceptronDual::build_learner() {
        set_parameters();
        this->learner = std::make_shared<mltk::classifier::PerceptronDual<double>>(this->m_train, type, kernel_param,rate);
        return this->learner;
    }

    FMP::FMP(mltk::Data<>& train, mltk::Data<>& test, cppcli::CLWidget *parent) :
    Classifier(train, test, parent) {
        set_text("Fixed Margin Perceptron (FMP)");
    }

    bool FMP::operator()() {
        bool ret = true;

        set_parameters();

        mltk::classifier::PerceptronFixedMarginPrimal<double> perc(this->m_train, gamma, q, rate);
        std::clock_t begin = std::clock();
        ret = perc.train();
        auto sol = perc.getSolution();

        std::cout << "Number of steps through data: " << perc.getSteps() << std::endl;
        std::cout << "Number of updates: " << perc.getUpdates() << std::endl;
        std::cout << "Weights vector:" << std::endl;
        std::cout << "[";
        for (int i = 0; i < sol.w.size(); i++) {
            std::cout << sol.w[i] << ", ";
        }
        std::cout << sol.bias << "]" << std::endl;
        std::cout << std::endl;

        std::clock_t end = std::clock();

        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        std::cout << std::endl;
        std::cout << elapsed_secs << " seconds to compute.\n";
        wait_action();
        visualize_options(perc);
        return ret;
    }

    void FMP::set_parameters() {
        std::cout << "Value of the learning rate: ";
        std::cin >> rate;
        std::cout << "Value of the q norm: ";
        std::cin >> q;
        std::cout << "Gamma value: ";
        std::cin >> gamma;
        std::cout << std::endl;
    }

    ClassifierPointer FMP::build_learner() {
        set_parameters();
        this->learner = std::make_shared<mltk::classifier::PerceptronFixedMarginPrimal<double>>(this->m_train, gamma, q, rate);
        return this->learner;
    }

    FMPDual::FMPDual(mltk::Data<>& train, mltk::Data<>& test, cppcli::CLWidget *parent) :
    Classifier(train, test, parent) {
        set_text("Fixed Margin Perceptron dual (FMP Dual)");
    }

    bool FMPDual::operator()() {
        bool ret = true;

        set_parameters();

        std::clock_t begin = std::clock();
        mltk::classifier::PerceptronFixedMarginDual<double> perc_fixmargin_dual(this->m_train, type, kernel_param, gamma, rate);
        perc_fixmargin_dual.train();

        auto sol = perc_fixmargin_dual.getSolution();
        std::cout << std::endl;
        std::cout << "Alpha vector:" << std::endl;
        std::cout << "[";
        for (int i = 0; i < sol.alpha.size(); i++) {
            std::cout << sol.alpha[i] << ", ";
        }
        std::cout << sol.bias << "]" << std::endl;
        std::cout << std::endl;

        std::cout << "Weights vector:" << std::endl;
        std::cout << "[";
        for (int i = 0; i < sol.w.size(); i++) {
            std::cout << sol.w[i] << ", ";
        }
        std::cout << sol.bias << "]" << std::endl;
        std::cout << std::endl;

        std::clock_t end = std::clock();

        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        std::cout << std::endl;
        std::cout << elapsed_secs << " seconds to compute.\n";
        wait_action();
        visualize_options(perc_fixmargin_dual, true);
        return ret;
    }

    void FMPDual::set_parameters() {
        int kernel_type;

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
        type = get_kernel_type(kernel_type);
    }

    ClassifierPointer FMPDual::build_learner() {
        set_parameters();
        this->learner = std::make_shared<mltk::classifier::PerceptronFixedMarginDual<double>>(this->m_train, type, kernel_param, gamma, rate);
        return this->learner;
    }

    KNNClassifier::KNNClassifier(mltk::Data<>& train, mltk::Data<>& test, cppcli::CLWidget *parent)
            : Classifier(train, test, parent) {
        set_text("K-Nearest Neighbors (KNN)");
    }

    bool KNNClassifier::operator()() {
        bool ret = true;

        set_parameters();

        mltk::classifier::KNNClassifier<double> knn(this->m_train, k);
        std::vector<std::string> class_names = this->m_train.classesNames();
        std::vector<int> classes = this->m_train.classes();
        ret = knn.train();
        //auto conf_matrix = mltk::validation::generateConfusionMatrix(samples, knn);
        std::cout << "Confusion Matrix: " << std::endl;
        //mltk::utils::printConfusionMatrix(classes, .classesNames(), conf_matrix);
        wait_action();
        visualize_options(knn, true);
        return ret;
    }

    void KNNClassifier::set_parameters() {
        std::cout << "k value: ";
        std::cin >> k;
        std::cout << std::endl;
    }

    ClassifierPointer KNNClassifier::build_learner() {
        set_parameters();
        this->learner = std::make_shared<mltk::classifier::KNNClassifier<double>>(this->m_train, k);
        return this->learner;
    }

    SMOClassifier::SMOClassifier(mltk::Data<>& train, mltk::Data<>& test, cppcli::CLWidget *parent)
            : Classifier(train, test, parent) {
        set_text("Sequential Minimal Optimization (SMO)");
    }

    bool SMOClassifier::operator()() {
        bool ret = true;
        int verbose = 1;

        set_parameters();

        std::clock_t begin = std::clock();
        mltk::classifier::SMO<double> smo(this->m_train, type, kernel_param, verbose);
        //        smo.setMaxTime(max_time);
        //        smo.setVerbose(verbose);
        smo.train();
        std::clock_t end = std::clock();

        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        std::cout << std::endl;
        std::cout << elapsed_secs << " seconds to compute.\n";

        auto sol = smo.getSolution();
        wait_action();
        visualize_options(smo, true);
        return ret;
    }

    void SMOClassifier::set_parameters() {
        int kernel_type;
        std::cout << "Learning rate: ";
        std::cin >> rate;
        std::cout << "Kernel [0]Inner Product [1]Polynomial [2]Gaussian: ";
        std::cin >> kernel_type;
        type = get_kernel_type(kernel_type);
        if(type != mltk::INNER_PRODUCT){
            if(kernel_type == mltk::POLYNOMIAL){
                std::cout << "Polynomial degree: ";
            }else{
                std::cout << "Gaussian gamma: ";
            }
            std::cin >> kernel_param;
        }
    }

    ClassifierPointer SMOClassifier::build_learner() {
        set_parameters();
        this->learner = std::make_shared<mltk::classifier::SMO<double>>(this->m_train, type, kernel_param, 1);
        return this->learner;
    }
}