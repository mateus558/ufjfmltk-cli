//
// Created by mateus on 29/05/2021.
//

#include "cppcli/CLWidget.h"
#include <iostream>
#include <algorithm>
#include <utility>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include "windows.h"
#undef max
#undef min
#endif
namespace cppcli {
    bool cppcli::CLWidget::m_global_exit = false;
    bool cppcli::CLWidget::goto_main = false;
    size_t cppcli::CLWidget::m_level = 0;

    CLWidget::CLWidget(CLWidget* parent, std::string  name):
            m_parent(parent),
            m_name(std::move(name)) {
        register_group("global", "", cppcli::GroupType::ACTION, true);

        register_action("global", "help", "help", [this](){
            help();
            wait_action();
            return true;
        }, nullptr, true);
    }

    bool CLWidget::show(){
        CLWidget::m_level++;
        if(!built_ui) {
            this->build();
            built_ui = true;
        }
        clear();
        while(true){
            if(control_loop_exit()){ return true; }

            show_console_title();
            if(!m_header.empty()){
                std::cout << m_header << std::endl;
            }

            show_options();
            std::cout << std::endl;
            process_messages();
            auto opt = option_selector();
            clear();
        }
    }

    bool CLWidget::control_loop_exit() {
        if(CLWidget::goto_main && CLWidget::m_level == 1){
            CLWidget::goto_main = false;
        }
        if(cppcli::CLWidget::m_global_exit || m_local_exit || (CLWidget::goto_main && CLWidget::m_level > 1)){
            CLWidget::m_level--;
            m_local_exit = false;
            return true;
        }
        return false;
    }

    void CLWidget::show_options() {
        for(const auto& [key, group]: m_groups_position){
            if((m_options.find(group) != m_options.end()) && !m_options[group].empty() &&
               m_groups_types[group] == cppcli::WIDGET){
                m_options[group].show();
                if(m_actions.find(group) != m_actions.end()){
                    m_actions[group].show(false);
                }
            }else if(m_actions.find(group) != m_actions.end()){
                m_actions[group].show();
            }
        }
    }

    void CLWidget::process_messages() {
        if(!messages.empty()) {
            for (const auto &msg: messages) {
                print_log(msg);
            }
            std::cout << std::endl;
            messages.clear();
        }
    }

    void CLWidget::clear() {
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

    std::string CLWidget::option_selector() {
        std::string opt;

        std::cout << ((m_cmd.empty())?" ":m_cmd) << "> ";
        std::cin >> opt;
        std::cout << opt << std::endl;
        OptionGroup<CLWidget> *exec_widget = nullptr;
        OptionGroup<Action::Type> *exec_action = nullptr;
        for(auto& [key, group]: m_options){
            if(group.exist_option(opt)){
                exec_widget = &group;
                break;
            }
        }
        clear();
        if(!exec_widget){
            for(auto& [key, group]: m_actions){
                if(group.exist_option(opt)){
                    exec_action = &group;
                    break;
                }
            }
        }

        if(exec_widget && !(*exec_widget)(opt)) {
            push_message("there were errors executing this option.", cppcli::LogType::LOGERROR);
        }else if(exec_action && !(*exec_action)(opt)){
            push_message("there were errors executing this option.", cppcli::LogType::LOGERROR);
        }else if(!exec_widget && !exec_action){
            messages.emplace_back("Invalid option!", cppcli::LogType::LOGERROR);
        }

        return opt;
    }

    bool CLWidget::operator()() {
        return this->show();
    }

    bool CLWidget::register_group(std::string name, std::string header, const GroupType& type, bool hidden) {
        if(group_exists(name)) return false;

        m_groups_position[n_options++] = name;
        switch (type) {
            case GroupType::WIDGET:
                m_options[name] = OptionGroup<CLWidget>(name, header, hidden);
                m_actions[name] = OptionGroup<Action::Type>(name, header, hidden);
                break;
            case GroupType::ACTION:
                m_actions[name] = OptionGroup<Action::Type>(name, std::move(header), hidden);
                break;
            default:
                std::clog << "Invalid group type." << std::endl;
                return false;
        }
        this->m_groups_types[name] = type;
        return true;
    }

    bool CLWidget::register_widget(const std::string& group, const std::string& text, const std::string& opt,
                                   CLWidget *widget, Action::Type update_func, bool hidden) {
        if(!group_exists(group)) return false;
        return m_options[group].register_option(text, opt, *widget, std::move(update_func), hidden);
    }

    bool CLWidget::register_action(const std::string &group, const std::string &text, const std::string &opt,
                                   Action::Type action, Action::Type update_func, bool hidden) {
        if(!group_exists(group)) return false;
        return m_actions[group].register_option(text, opt, action, std::move(update_func), hidden);
    }

    bool CLWidget::group_exists(const std::string& name) {
        return (m_options.find(name) != m_options.end()) || (m_actions.find(name) != m_actions.end());
    }

    const std::string &CLWidget::get_header() const {
        return m_header;
    }

    const std::string &CLWidget::get_text() const {
        return m_text;
    }

    void CLWidget::print_log(const Log &log) {
        switch (log.type) {
            case cppcli::LogType::NORMAL:
                std::cout << "[MESSAGE]: " << log.text << std::endl;
                break;
            case cppcli::LogType::LOG:
                std::clog << "[LOG]: " << log.text << std::endl;
                break;
            case cppcli::LogType::LOGERROR:
                std::cerr << "[ERROR]: " << log.text << std::endl;
                break;
            case cppcli::LogType::CUSTOM:
                std::cerr << "["<< log.custom <<"]: " << log.text << std::endl;
                break;
            default:
                std::cout <<  log.text << std::endl;
                break;
        }
    }

    void CLWidget::wait_action() {
        std::cout << "\nPress ENTER to continue..." << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cin.get();
    }

    void CLWidget::add_exit_group() {
        register_group("exit", "\n--------------------------\n", cppcli::GroupType::ACTION);

        if(CLWidget::m_level > 1) {
            register_action("exit", "Back to the main menu", "m", [this]() {
                CLWidget::goto_main = true;
                return true;
            });
        }
        if(CLWidget::m_level > 2){
            register_action("exit", "Back to the previous menu", "b", [this]() {
                exit();
                return true;
            });
        }
        register_action("exit", "Exit", "e", [this](){
            exit(false);
            return true;
        });
    }

    void CLWidget::push_message(const std::string& msg, const cppcli::LogType& type,
                                const std::string& custom) {
        messages.emplace_back(msg, type, custom);
    }

    void CLWidget::use_parent_header() {
        set_header(this->m_parent->get_header());
    }

    bool CLWidget::ask_run_action(const std::string& text,const Action::Type& action, const std::string& action_name,
                                  bool verbose) {
        char y;
        clear();
        std::cout << text << " [y/n]: ";
        std::cin >> y;
        if(y == 'y'){
            std::cout << std::endl;
            if(verbose) push_message(action_name + " action executed.", cppcli::LogType::CUSTOM, "SYSTEM");
            action();
        }else{
            if(verbose) push_message(action_name + " action not executed.", cppcli::LogType::CUSTOM, "SYSTEM");
        }
        clear();
        return true;
    }

    const std::string &CLWidget::get_name() const {
        return m_name;
    }

    void CLWidget::help(const std::string &group_name) {
        if(group_name.empty()){
            for(const auto& [key, group]: m_groups_position){
                m_options[group].help();
                m_actions[group].help(false);
            }
        }else{
            if(m_options.find(group_name) != m_options.end()){
                m_options[group_name].help();
            }
            if(m_actions.find(group_name) != m_actions.end()){
                m_actions[group_name].help(false);
            }
        }
    }

    CLWidget *CLWidget::parent() const {
        return this->m_parent;
    }

    void CLWidget::exit(bool local) {
        if(local){
            this->m_local_exit = true;
        }else{
            cppcli::CLWidget::m_global_exit = true;
        }
    }

    void CLWidget::set_text(const std::string &text) {
        CLWidget::m_text = text;
    }

    void CLWidget::show_console_title() const {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        SetConsoleTitle(get_name().c_str());
#else
        std::cout << "\033]0;" << get_name() << "\007";
#endif
    }
};