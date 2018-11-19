//
// Created by dan on 31/10/18.
//

#ifndef DANKERER_COMMANDBUFFER_H
#define DANKERER_COMMANDBUFFER_H

#include <variant>

#include "common.h"
#include "drawCommands.h"

namespace dk {
    namespace gfx {
        class CommandBuffer {
        public:
            CommandBuffer() = default;
            ~CommandBuffer() = default;

            void addDrawCommand(u64 materialKey, Draw d);
            void addDrawCommand(u64 materialKey, DrawIndexed di);

            void sort();

        private:
            std::vector<std::pair<u64, std::variant<Draw, DrawIndexed>>> m_commands;
        };
    }
}


#endif //DANKERER_COMMANDBUFFER_H
