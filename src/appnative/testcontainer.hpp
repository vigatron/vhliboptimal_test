#pragma once

#include "vhplatform.hpp"



class TestLibraryContainer {

    public:

        verr TestSingleFile(const std::string & filename) {

            return verror(1);
        }

        verr TestInternalExamples() {

            return verror(1);
        }

    private:

};
