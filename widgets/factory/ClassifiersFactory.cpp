//
// Created by mateus on 31/05/2021.
//

#include "ClassifiersFactory.h"
#include <chrono>

namespace factory{
    std::map<ClassifierPrimal, Classifier*> allocated_primal_classifiers;
    std::map<ClassifierDual, Classifier*> allocated_dual_classifiers;

    Classifier::Classifier(cppcli::CLWidget *parent) : cppcli::CLWidget(parent) {

    }

    Classifier::Classifier(const mltk::Data<> &train, const mltk::Data<> &test, cppcli::CLWidget *parent):
            cppcli::CLWidget(parent),
            m_train(train),
            m_test(test)
    {
    }

    Classifier * Classifier::make_primal_classifier(ClassifierPrimal classifier, const mltk::Data<>& samples,
                                                   const mltk::Data<>& train,
                                                   const mltk::Data<>& test, cppcli::CLWidget *parent) {
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

    Classifier * Classifier::make_dual_classifier(ClassifierDual classifier, const mltk::Data<>& samples,
                                                          const mltk::Data<>& train,
                                                          const mltk::Data<>& test, cppcli::CLWidget *parent) {
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

    std::vector<Classifier *> Classifier::get_primal_classifiers(const mltk::Data<>& data, const mltk::Data<>& train,
                                                                       const mltk::Data<>& test, cppcli::CLWidget *parent) {
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
    Classifier::get_dual_classifiers(const mltk::Data<> &data, const mltk::Data<> &train, const mltk::Data<> &test,
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

    std::shared_ptr<mltk::classifier::Classifier<double>> Classifier::get_built_classifier() {
        if(this->learner){
            return this->learner;
        }
        this->parent()->push_message("Classifier not initialized, call the widget show method first.", cppcli::LogType::ERROR);
        return nullptr;
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

    IMAp::IMAp(const mltk::Data<>& train, const mltk::Data<>& test, cppcli::CLWidget *parent) :
    Classifier(train, test, parent)
    {
        set_text("Incremental Margin Algorithm (IMAp)");
    }

    bool IMAp::operator()() {
        int p, q, flex;
        double alpha_aprox;
        bool ret = true;

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

        mltk::classifier::IMAp<double> imap(this->m_train, p, flex);
        if(this->m_train_learner) {
            imap.setAlphaAprox(alpha_aprox);
            ret = imap.train();
            wait_action();
        }
        this->learner = std::make_shared<mltk::classifier::IMAp<double>>(imap);
        return ret;
    }

    bool IMAp::build() {

        return true;
    }

    IMADual::IMADual(const mltk::Data<>& train, const mltk::Data<>& test, cppcli::CLWidget *parent) :
    Classifier(train, test, parent)
    {
        set_text("Incremental Margin Algorithm (IMA Dual)");
    }

    bool IMADual::build() {
        return true;
    }

    bool IMADual::operator()() {
        int qtde, fold;
        double rate, kernel_param = 0.0;
        int kernel_type;

        std::cout << "Learning rate: ";
        std::cin >> rate;
        std::cout << "Kernel [0]Inner Product [1]Polynomial [2]Gaussian: ";
        std::cin >> kernel_type;

        mltk::KernelType type = get_kernel_type(kernel_type);
        if(type != mltk::INNER_PRODUCT){
            if(kernel_type == mltk::POLYNOMIAL){
                std::cout << "Polynomial degree: ";
            }else{
                std::cout << "Gaussian gamma: ";
            }
            std::cin >> kernel_param;
        }

        std::clock_t begin = std::clock();
        mltk::classifier::IMADual<double> ima_dual(this->m_train, type, kernel_param);
        if(this->m_train_learner)
        {
            //ima_dual.setMaxTime(max_time);
            ima_dual.train();
            //val_sol = runValidation(samples, ima_dual, fold, qtde, verbose, SEED);
            std::clock_t end = std::clock();
            double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
            std::cout << std::endl;
            std::cout << elapsed_secs << " seconds to compute.\n";
            wait_action();
        }
        this->learner = std::make_shared<mltk::classifier::IMADual<double>>(ima_dual);
        return true;
    }


    Perceptron::Perceptron(const mltk::Data<> &train, const mltk::Data<> &test, cppcli::CLWidget *parent) :
    Classifier(train, test, parent) {
        set_text("Perceptron primal");
    }

    bool Perceptron::build() {
        return false;
    }

    bool Perceptron::operator()() {
        double rate;
        int q, i;
        bool ret = true;

        std::cout << "Value of the learning rate: ";
        std::cin >> rate;
        std::cout << "Value of the q norm: ";
        std::cin >> q;
        std::cout << std::endl;

        mltk::classifier::PerceptronPrimal<double> perc(this->m_train, q, rate);
        if(this->m_train_learner)
        {
            std::clock_t begin = std::clock();
            ret = perc.train();
            auto sol = perc.getSolution();

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
            wait_action();
        }
        this->learner = std::make_shared<mltk::classifier::PerceptronPrimal<double>>(perc);
        return ret;
    }

    PerceptronDual::PerceptronDual(const mltk::Data<> &train, const mltk::Data<> &test, cppcli::CLWidget *parent)
            : Classifier(train, test, parent) {
        set_text("Perceptron dual");
    }

    bool PerceptronDual::build() {
        return true;
    }

    bool PerceptronDual::operator()() {
        int i, kernel_type;
        double rate, kernel_param = 0.0;
        bool ret = true;
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
        mltk::KernelType type = get_kernel_type(kernel_type);
        mltk::classifier::PerceptronDual<double> perc_dual(this->m_train, type, kernel_param,rate);
        if(this->m_train_learner) {
            ret = perc_dual.train();

            auto sol = perc_dual.getSolution();

            std::cout << std::endl;
            std::cout << "Alpha vector:" << std::endl;
            std::cout << "[";

            for (i = 0; i < sol.alpha.size(); i++) {
                std::cout << sol.alpha[i] << ", ";
            }

            std::cout << sol.bias << "]" << std::endl;
            std::cout << std::endl;
            std::cout << "Weights vector:" << std::endl;
            std::cout << "[";

            for (i = 0; i < sol.w.size(); i++) {
                std::cout << sol.w[i] << ", ";
            }

            std::cout << sol.bias << "]" << std::endl;
            std::cout << std::endl;

            std::clock_t end = std::clock();

            double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
            std::cout << std::endl;
            std::cout << elapsed_secs << " seconds to compute.\n";
            wait_action();
        }
        this->learner = std::make_shared<mltk::classifier::PerceptronDual<double>>(perc_dual);
        return ret;
    }

    FMP::FMP(const mltk::Data<> &train, const mltk::Data<> &test, cppcli::CLWidget *parent) :
    Classifier(train, test, parent) {
        set_text("Fixed Margin Perceptron (FMP)");
    }

    bool FMP::build() {
        return false;
    }

    bool FMP::operator()() {
        int q, i;
        double gamma, rate;
        bool ret = true;
        std::cout << "Value of the learning rate: ";
        std::cin >> rate;
        std::cout << "Value of the q norm: ";
        std::cin >> q;
        std::cout << "Gamma value: ";
        std::cin >> gamma;
        std::cout << std::endl;

        mltk::classifier::PerceptronFixedMarginPrimal<double> perc(this->m_train, gamma, q, rate);
        if(this->m_train_learner) {
            std::clock_t begin = std::clock();
            ret = perc.train();
            auto sol = perc.getSolution();

            std::cout << "Number of steps through data: " << perc.getSteps() << std::endl;
            std::cout << "Number of updates: " << perc.getUpdates() << std::endl;
            std::cout << "Weights vector:" << std::endl;
            std::cout << "[";
            for (i = 0; i < sol.w.size(); i++) {
                std::cout << sol.w[i] << ", ";
            }
            std::cout << sol.bias << "]" << std::endl;
            std::cout << std::endl;

            std::clock_t end = std::clock();

            double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
            std::cout << std::endl;
            std::cout << elapsed_secs << " seconds to compute.\n";
            wait_action();
        }
        this->learner = std::make_shared<mltk::classifier::PerceptronFixedMarginPrimal<double>>(perc);
        return ret;
    }

    FMPDual::FMPDual(const mltk::Data<> &train, const mltk::Data<> &test, cppcli::CLWidget *parent) :
    Classifier(train, test, parent) {
        set_text("Fixed Margin Perceptron dual (FMP Dual)");
    }

    bool FMPDual::build() {
        return false;
    }

    bool FMPDual::operator()() {
        double gamma, rate, kernel_param=0;
        int i, kernel_type;
        bool ret = true;

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
        mltk::KernelType type = get_kernel_type(kernel_type);
        mltk::classifier::PerceptronFixedMarginDual<double> perc_fixmargin_dual(this->m_train, type, kernel_param, gamma, rate);
        if(this->m_train_learner) {
            perc_fixmargin_dual.train();

            auto sol = perc_fixmargin_dual.getSolution();
            std::cout << std::endl;
            std::cout << "Alpha vector:" << std::endl;
            std::cout << "[";
            for (i = 0; i < sol.alpha.size(); i++) {
                std::cout << sol.alpha[i] << ", ";
            }
            std::cout << sol.bias << "]" << std::endl;
            std::cout << std::endl;

            std::cout << "Weights vector:" << std::endl;
            std::cout << "[";
            for (i = 0; i < sol.w.size(); i++) {
                std::cout << sol.w[i] << ", ";
            }
            std::cout << sol.bias << "]" << std::endl;
            std::cout << std::endl;

            std::clock_t end = std::clock();

            double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
            std::cout << std::endl;
            std::cout << elapsed_secs << " seconds to compute.\n";
            wait_action();
        }
        this->learner = std::make_shared<mltk::classifier::PerceptronFixedMarginDual<double>>(perc_fixmargin_dual);
        return ret;
    }

    KNNClassifier::KNNClassifier(const mltk::Data<> &train, const mltk::Data<> &test, cppcli::CLWidget *parent)
            : Classifier(train, test, parent) {
        set_text("K-Nearest Neighbors (KNN)");
    }

    bool KNNClassifier::build() {
        return false;
    }

    bool KNNClassifier::operator()() {
        size_t k;
        bool ret = true;
        std::cout << "k value: ";
        std::cin >> k;
        std::cout << std::endl;

        mltk::classifier::KNNClassifier<double> knn(this->m_train, k);
        if(this->m_train_learner) {
            std::vector<std::string> class_names = this->m_train.classesNames();
            std::vector<int> classes = this->m_train.classes();
            ret = knn.train();
            //auto conf_matrix = mltk::validation::generateConfusionMatrix(samples, knn);
            std::cout << "Confusion Matrix: " << std::endl;
            //mltk::utils::printConfusionMatrix(classes, .classesNames(), conf_matrix);
            wait_action();
        }
        this->learner = std::make_shared<mltk::classifier::KNNClassifier<double>>(knn);
        return ret;
    }

    SMOClassifier::SMOClassifier(const mltk::Data<> &train, const mltk::Data<> &test, cppcli::CLWidget *parent)
            : Classifier(train, test, parent) {
        set_text("Sequential Minimal Optimization (SMO)");
    }

    bool SMOClassifier::build() {
        return false;
    }

    bool SMOClassifier::operator()() {
        bool ret = true;
        int kernel_type, verbose = 1;
        double kernel_param = 0;

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

        mltk::KernelType type = get_kernel_type(kernel_type);
        std::clock_t begin = std::clock();
        mltk::classifier::SMO<double> smo(this->m_train, type, kernel_param, verbose);
        if(this->m_train_learner) {
            //        smo.setMaxTime(max_time);
            //        smo.setVerbose(verbose);
            smo.train();
            std::clock_t end = std::clock();

            double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
            std::cout << std::endl;
            std::cout << elapsed_secs << " seconds to compute.\n";

            auto sol = smo.getSolution();
            wait_action();
        }
        this->learner = std::make_shared<mltk::classifier::SMO<double>>(smo);
        return ret;
    }
}