#pragma once

#include "benchmark.hpp"
#include "cmatrix/cmatrix.hpp"

#include "timer/timeaverager.hpp"

#include <filesystem>
#include <fstream>
#include <string>


//
class VHReportGenerator {

    public:

        /**
         * 
         */
        void SetFileName(const std::string & fname) {
            filename = fname;
        }

        /**
         * 
         */
        void SetImgProps(uint16_t w, uint16_t h) {

            // Размер картинки в пикселях, длинна
            imageWidth    = w;

            // Размер картинки в пикселях, высота
            imageHeight   = h;

        }

        /**
         * 
         */
        void SetMisc(
            const vhliboptimal::CellsMatrix & cmtx,
            uint8_t levelcs,
            uint16_t objsCount) {

            cellsw        = cmtx.CellsX();
            cellsh        = cmtx.CellsY();
            cellst        = cmtx.CellsT();
            cellsize      = 1 << levelcs;
            buffsize      = cmtx.BitMaskSizeBytes();
            objscnt       = objsCount;

        }

        /**
         * 
         */
        void SetTimings(
            const TimerAverager & arrtsSampling,
            const TimerAverager & arrtsScanning) {

            // Sampling
            ts_smp_min    = arrtsSampling.resultmin();
            ts_smp_avg    = arrtsSampling.result(VHLIBOPTIMAL_TEST_PASS_COUNT);
            ts_smp_max    = arrtsSampling.resultmax();

            // Scanning
            ts_scn_min    = arrtsScanning.resultmin();
            ts_scn_avg    = arrtsScanning.result(VHLIBOPTIMAL_TEST_PASS_COUNT);
            ts_scn_max    = arrtsScanning.resultmax();

            // Summ
            ts_fin_min    = ts_smp_min + ts_scn_min;
            ts_fin_avg    = ts_smp_avg + ts_scn_avg;
            ts_fin_max    = ts_smp_max + ts_scn_max;

            // Stat
            std::cout << "Min: " << ts_fin_min << " uSec/frame" << std::endl;
            std::cout << "Avg: " << ts_fin_avg << " uSec/frame" << std::endl;
            std::cout << "Max: " << ts_fin_max << " uSec/frame" << std::endl;

        }

        /**
         * 
         */
        verr SaveResults() {

            // Basename Source File
            std::filesystem::path path_src(filename);
            std::string fnameSource = path_src.filename().string(); 

            // Markdown File
            std::filesystem::path path_mrk(filename);
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

            std::string str_resolution = std::to_string(imageWidth) + " x " + std::to_string(imageHeight);
            params.push_back(str_resolution);

            params.push_back(std::to_string(cellsize));

            std::string strcellsw = std::to_string((int)cellsw);
            std::string strcellsh = std::to_string((int)cellsh);
            std::string strcellst = std::to_string((int)cellst);
            params.push_back(strcellsw + " * " + strcellsh + " = " + strcellst);

            params.push_back(std::to_string(buffsize));

            params.push_back(std::to_string(objscnt));

            std::string str_ts_smp = strJoin(ts_smp_min, ts_smp_avg, ts_smp_max);
            params.push_back(str_ts_smp);

            std::string str_ts_scn = strJoin(ts_scn_min, ts_scn_avg, ts_scn_max);
            params.push_back(str_ts_scn);

            std::string str_ts_fin = strJoin(ts_fin_min, ts_fin_avg, ts_fin_max);
            params.push_back(str_ts_fin);

            ofs << strJoin(params) << "\n";

            ofs.close();

            return vok;
        }


    private:

        std::string     filename;
        int             imageWidth;
        int             imageHeight;

        int             cellsize;

        uint32_t        cellsw;
        uint32_t        cellsh;
        uint32_t        cellst;
        uint32_t        buffsize;

        uint16_t        objscnt;

        // Sampling
        long            ts_smp_min;
        long            ts_smp_avg;
        long            ts_smp_max;

        // Scanning
        long            ts_scn_min;
        long            ts_scn_avg;
        long            ts_scn_max;

        // Total
        long            ts_fin_min;
        long            ts_fin_avg;
        long            ts_fin_max;


        inline static const std::vector<std::string> hdrfields = {
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

        // MD related routines

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

};

extern VHReportGenerator gobjReport;