#include "benchmark.hpp"

#include <filesystem>
#include <fstream>
#include <string>


static std::string fields[] = {
    "1",
    "2"
};

verr SaveBenchmark(const stBenchmarkParams & bench) {

    // Basename Source File
    std::filesystem::path path_src(bench.filename);
    std::string fnameSource = path_src.filename().string(); 

    // Markdown File
    std::filesystem::path path_mrk(bench.filename);
    std::string ext = ".md";
    std::string fnameMarkdown = path_mrk.stem().filename().string() + ext;

    // Выходной поток
    std::ofstream ofs;

    // Create or append ?
    if (!std::filesystem::exists(fnameMarkdown)) {
        std::cout << "Creating Results file: " << fnameMarkdown << std::endl;

        ofs.open(fnameMarkdown, std::ios::out);
        if (!ofs) return verror(1);

        // Заголовок таблицы — имена полей
        ofs << "| filename "
            << "| imageWidth / imageHeight<br>(pixels) "
            << "| cellsize<br>(pixels) "
            << "| cellsw<br>(cells) "
            << "| cellsh<br>(cells) "
            << "| total<br>(cells) "
            << "| buffsize<br>(bytes) "
            << "| objects<br>count "
            << "| tsmin / tsavg / tsmax (ms) "
            << " |\n";

        ofs << "|----------"
            << "|----------"
            << "|----------"
            << "|----------"
            << "|----------"
            << "|----------"
            << "|----------"
            << "|----------"
            << "|----------"
            << "|\n";

    } else {
        std::cout << "Appending Results file: " << fnameMarkdown << std::endl;
        if (!ofs) return verror(1);

        ofs.open(fnameMarkdown, std::ios::app);
    }

    std::string str_resolution = std::to_string(bench.imageWidth) + " x " + std::to_string(bench.imageHeight);

    std::string strtm = std::to_string(bench.tsmin) + " / ";
    strtm += std::to_string(bench.tsavg) + " / ";
    strtm += std::to_string(bench.tsmax);

    // Строка таблицы — значения
    ofs << "| "  << fnameSource
        << " | " << str_resolution
        << " | " << bench.cellsize
        << " | " << bench.cellsw
        << " | " << bench.cellsh
        << " | " << bench.cellst
        << " | " << bench.buffsize
        << " | " << bench.objscnt
        << " | " << strtm
        << " |\n";

    ofs.close();

    return vok;
}