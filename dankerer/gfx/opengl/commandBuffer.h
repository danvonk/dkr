//
// Created by dan on 31/10/18.
//

#ifndef DANKERER_COMMANDBUFFER_H
#define DANKERER_COMMANDBUFFER_H

#include <boost/variant.hpp>

#include "common.h"
#include "drawCommands.h"

namespace dk {
    namespace gfx {
        class CommandBuffer {
            friend class Device;
        public:
            CommandBuffer() = default;
            ~CommandBuffer() = default;

            void addDrawCommand(u64 materialKey, DrawIndexed di);

            void sort();
            void clear();

        private:
            std::vector<std::pair<u64, DrawIndexed>> m_commands;
        };
    }
}


#endif //DANKERER_COMMANDBUFFER_H
