#include "benchmark.hpp"

#include <filesystem>
#include <fstream>
#include <string>


static const std::vector<std::string> hdrfields = {
    "File Name",
    "imgWidth / imgHeight<br>(pixels)",
    "CellSize<br>(pixels)",
    "CellsW * CellsH = CellsT<br>(cells)",
    "Buff Size<br>(bytes)",
    "Objects<br>count",
    "Sampling (ms)<br>tsmin / tsavg / tsmax",
    "Scanning (ms)<br>tsmin / tsavg / tsmax",
    "Total (ms)   <br>tsmin / tsavg / tsmax"
};

std::string strJoin(const std::vector<std::string> & arr) {
    std::string r;
    r += "| ";
    for( const std::string & str : arr ) { r += str + " |"; }
    return r;
}

std::string strSeparator(const std::vector<std::string> & arr) {
    std::string r;

    r += "|";
    for( int i=0; i < arr.size(); i++ ) { r += "---|"; }
    return r;

}

std::string strnz(int v) {
    return !v ? "<1" : std::to_string(v);
}

std::string strJoin(int v1, int v2, int v3) {
    std::string r;
    r += strnz(v1) + " / ";
    r += strnz(v2) + " / ";
    r += strnz(v3);
    return r;
}

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
        ofs << strJoin(hdrfields) << "\n";
        ofs << strSeparator(hdrfields) << "\n";

    } else {
        std::cout << "Appending Results file: " << fnameMarkdown << std::endl;
        if (!ofs) return verror(1);

        ofs.open(fnameMarkdown, std::ios::app);
    }


    // Строка таблицы — значения
    std::vector<std::string> params;

    params.push_back(fnameSource);

    std::string str_resolution = std::to_string(bench.imageWidth) + " x " + std::to_string(bench.imageHeight);
    params.push_back(str_resolution);

    params.push_back(std::to_string(bench.cellsize));

    std::string cellsw = std::to_string(bench.cellsw);
    std::string cellsh = std::to_string(bench.cellsh);
    std::string cellst = std::to_string(bench.cellst);
    params.push_back(cellsw + " * " + cellsh + " = " + cellst);

    params.push_back(std::to_string(bench.buffsize));

    params.push_back(std::to_string(bench.objscnt));

    std::string str_ts_smp = strJoin(bench.ts_smp_min, bench.ts_smp_avg, bench.ts_smp_max);
    params.push_back(str_ts_smp);

    std::string str_ts_scn = strJoin(bench.ts_scn_min, bench.ts_scn_avg, bench.ts_scn_max);
    params.push_back(str_ts_scn);

    std::string str_ts_fin = strJoin(bench.ts_fin_min, bench.ts_fin_avg, bench.ts_fin_max);
    params.push_back(str_ts_fin);

    ofs << strJoin(params) << "\n";

    ofs.close();

    return vok;
}