#pragma once
#include <functional>

#include "object.hpp"

namespace engine {
    class Timer final{
        public:
            explicit Timer(double length, const std::function<void()> & = {});
            ~Timer();

            void start();
            [[nodiscard]] bool isDone() const;
            void update();

            double length;
            bool started = false;
            bool finished = false;
        private:
            std::function<void()> onComplete;
            double startTime = 0.0;
            std::shared_ptr<engine::Timer> thisPointer;
    };
}
