#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <cstring>
#include "nutility.h"

void print_usage()
{
    std::cerr << "Kullanim: -s <dosya_ismi> <byte_sayisi>\n";
    std::cerr << "          -j <dosya_ismi>\n";
}

int main(int argc, char const *argv[])
{
    using namespace std;

    if (argc < 2)
    {
        print_usage();
        return 1;
    }

    if (strcmp("-s", argv[1]) == 0) {
        if (argc != 4)
        {
            print_usage();
            return 1;
        }
        cout << "splitting...\n";

        auto filename = string{ argv[2] };
        auto chunk_sz = std::atoi(argv[3]);

        ifstream ifs(filename, ios::binary);
        if (!ifs) {
            cerr << filename << " dosyasi acilamadi\n";
            return 3;
        }

        int byte_cnt{};
        int file_cnt{};
        char c{};

        ofstream ofs;
        while (ifs.get(c)) {
            if (!ofs.is_open()) {
                // ostringstream oss;
                // oss << setfill('0');
                // oss << "parca" << setw(3) << file_cnt + 1 << '.par';
                // auto out_file = oss.str();

                auto out_file = (ostringstream{} << setfill('0') << filename << setw(3) << file_cnt + 1 << ".par").str();
                ofs.open(out_file, ios::binary);
                if (!ofs) {
                    cerr << out_file << " dosyasi olusturulamadi\n";
                    return 3;
                }
                ++file_cnt;
            }

            ofs.put(c);
            ++byte_cnt;
            if (byte_cnt && byte_cnt % chunk_sz == 0) {
                ofs.close();
            }
        }

        cout << byte_cnt << " byte boyutunda " << filename << " dosyasi " << chunk_sz << "byte boyutunda " << file_cnt << " dosyaya bolundu.\n";
    }
    else if (strcmp("-j", argv[1]) == 0) {
        if (argc != 3)
        {
            print_usage();
            return 1;
        }
        cout << "joining...\n";
        auto filename = string{ argv[2] };

        ofstream ofs{ filename, ios::binary };
        if (!ofs) {
            cerr << filename << " dosyasi olusturulamadi\n";
            return 4;
        }

        int file_cnt{};
        int byte_cnt{};
        char c;

        while (true)
        {
            auto input_filename = (ostringstream{} << setfill('0') << filename << setw(3) << file_cnt + 1 << ".par").str();
            ifstream ifs{ input_filename, ios::binary };
            if (!ifs) {
                break;
            }
            ++file_cnt;

            while (ifs.get(c)) {
                ofs.put(c);
                ++byte_cnt;
            }

            ifs.close();


            if (!std::filesystem::remove(input_filename)) {
                cerr << input_filename << " dosyasi silinemedi\n";
                return 5;
            }
        }
    }
    else {
        print_usage();
        return 2;
    }
}
