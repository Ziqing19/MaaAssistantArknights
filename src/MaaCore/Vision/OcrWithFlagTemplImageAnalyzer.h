#pragma once
#include "AbstractImageAnalyzer.h"
#include "Config/MatcherConfig.h"
#include "Config/OCRerConfig.h"

namespace asst
{
    class OcrWithFlagTemplImageAnalyzer : public AbstractImageAnalyzer, public OCRerConfig, public MatcherConfig
    {
    public:
        struct Result : public TextRect
        {
            Rect flag_rect;
            double flag_score = .0;
        };

        using ResultsVec = std::vector<Result>;
        using ResultsVecOpt = std::optional<ResultsVec>;

    public:
        using AbstractImageAnalyzer::AbstractImageAnalyzer;
        virtual ~OcrWithFlagTemplImageAnalyzer() override = default;

        void set_task_info(const std::string& templ_task_name, const std::string& ocr_task_name);
        void set_flag_rect_move(Rect flag_rect_move);

        ResultsVecOpt analyze() const;
        // FIXME: 老接口太难重构了，先弄个这玩意兼容下，后续慢慢全删掉
        const auto& get_result() const noexcept { return m_result; }

    protected:
        // from Config
        virtual void _set_roi(const Rect& roi) override { std::ignore = roi; }

    protected:
        using MatcherConfig::set_task_info;
        using OCRerConfig::set_task_info;

    private:
        Rect m_flag_rect_move;

    private:
        // FIXME: 老接口太难重构了，先弄个这玩意兼容下，后续慢慢全删掉
        mutable ResultsVec m_result;
    };
}
