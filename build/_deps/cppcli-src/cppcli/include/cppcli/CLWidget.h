#ifndef CPPCLI_CLWIDGET_H
#define CPPCLI_CLWIDGET_H

#include <string>
#include <utility>
#include <vector>
#include <unordered_map>

#include "cppcli/Options.h"

namespace cppcli{
    enum GroupType {WIDGET, ACTION};
    enum LogType {NORMAL, LOG, LOGERROR, CUSTOM};

    struct Log{
        Log(std::string _text, const LogType& _type, std::string _custom = ""):
                text(std::move(_text)),
                type(_type),
                custom(std::move(_custom)){};

        std::string text, custom;
        LogType type = LogType::NORMAL;
    };

    class CLWidget{
    public:
        explicit CLWidget(CLWidget* parent = nullptr, std::string  name = "");

        virtual bool show();

        virtual bool operator()();

        virtual bool build()=0;

        inline void set_header(const std::string& header) { this->m_header = header; }

        inline void set_cmd(const std::string& cmd) { this->m_cmd = cmd; }

        void set_text(const std::string &text);

        const std::string &get_header() const;

        const std::string &get_text() const;

        const std::string &get_name() const;

        bool register_group(std::string name, std::string header, const GroupType& type=GroupType::WIDGET,
                            bool hidden=false);

        bool register_widget(const std::string& group, const std::string& text, const std::string& opt,
                             CLWidget* widget = nullptr, Action::Type update_func = nullptr, bool hidden = false);

        bool register_action(const std::string& group, const std::string& text, const std::string& opt,
                             Action::Type action = nullptr, Action::Type update_func = nullptr, bool hidden = false);

        void push_message(const std::string& msg, const cppcli::LogType& type = cppcli::LogType::LOG,
                          const std::string& custom ="");

        virtual ~CLWidget() = default;

    protected:

        static void clear();

        CLWidget* parent() const;

        virtual std::string option_selector();

        bool group_exists(const std::string& name);

        static void print_log(const Log& log);

        static void wait_action();

        void add_exit_group();

        bool ask_run_action(const std::string& text, const Action::Type& action, const std::string& action_name="", bool verbose=true);

        void use_parent_header();

        void help(const std::string& group="");

        void exit(bool local = true);

    private:
        void show_console_title() const;
        bool control_loop_exit();

        void show_options();

        void process_messages();

    protected:
        static size_t m_level;
        static bool m_global_exit;
        static bool goto_main;
        bool m_local_exit = false;
        std::string m_text;

    protected:
        std::string m_name{};
        CLWidget* m_parent{nullptr};
        std::map<size_t, std::string> m_groups_position;
        std::unordered_map<std::string, OptionGroup<CLWidget>> m_options;
        std::unordered_map<std::string, cppcli::GroupType> m_groups_types;
        std::unordered_map<std::string, OptionGroup<Action::Type>> m_actions;

    private:
        int n_options;
        bool built_ui = false;
        std::string m_header, m_cmd;
        std::vector<cppcli::Log> messages;
    };
};

#endif //CPPCLI_CLWIDGET_H