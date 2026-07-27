#include "benchmark.hpp"

#include <filesystem>
#include <fstream>
#include <string>


verr SaveBenchmark(const stBenchmarkParams & bench) {

    // Basename Source File
    std::filesystem::path path_src(bench.filename);
    std::string fnameSource = path_src.filename().string(); 

    // Markdown File
    std::filesystem::path path_mrk(bench.filename);
    std::string pfx = "_" + std::to_string(bench.cellsize);
    std::string ext = ".md";
    std::string fnameMarkdown = path_mrk.stem().filename().string() + pfx + ext;

    std::cout << "Results file: " << fnameMarkdown << std::endl;

    std::ofstream ofs(fnameMarkdown);
    if (!ofs) return 1;

    ofs << "# Значения структуры stBenchmarkParams\n\n";

    // Заголовок таблицы — имена полей
    ofs << "| filename "
        << "| imageWidth<br>(pixels) "
        << "| imageHeight<br>(pixels) "
        << "| cellsize<br>(pixels) "
        << "| cellsw<br>(cells) "
        << "| cellsh<br>(cells) "
        << "| total<br>(cells) "
        << "| buffsize<br>(bytes) "
        << "| pass<br>count "
        << "| tsavg<br>(ms) "
        << "| tsmin<br>(ms) "
        << "| tsmax<br>(ms) "
        << " |\n";

    ofs << "|----------|------------|-------------|----------|--------|--------|--------|----------|---------|-------|-------|-------|\n";

    // Строка таблицы — значения
    ofs << "| "  << fnameSource
        << " | " << bench.imageWidth
        << " | " << bench.imageHeight
        << " | " << bench.cellsize
        << " | " << bench.cellsw
        << " | " << bench.cellsh
        << " | " << bench.cellst
        << " | " << bench.buffsize
        << " | " << bench.passcnt
        << " | " << bench.tsavg
        << " | " << bench.tsmin
        << " | " << bench.tsmax
        << " |\n";

    ofs.close();

    return vok;
}