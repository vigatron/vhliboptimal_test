#pragma once

#include <cstdint>


class VHCommandLineBuffer {
    public:

        VHCommandLineBuffer() : _pos(0) {}

        void reset() { _pos = 0; _avail = false; }
        bool avail() { return _avail; }

        void add(uint8_t byteval) {
            if(byteval == symLF) return;
            if(byteval == symCR) {
                _avail = true;
                _buff[_pos] = 0;
            } else {
                _buff[_pos++] = byteval;
                _pos &= BUFF_LEN-1;
            }
        }

        static constexpr char cmdi[] = "info";
        static constexpr char cmde[] = "run";
        static constexpr char cmdm[] = "mem";

        bool iscmd(const char * cmdtxt) {
            uint16_t i=0;
            for(;;i++) {
                if(cmdtxt[i] != _buff[i]) return false;
                if(!cmdtxt[i]) break;
            }
            return true;
        }

        const char * data() { return _buff; }

    private:

        static constexpr uint8_t symLF = 0x0A;
        static constexpr uint8_t symCR = 0x0D;

        static constexpr int    BUFF_LEN = (1<<5);
        char                    _buff[BUFF_LEN];
        uint8_t                 _pos;
        bool                    _avail;
};
